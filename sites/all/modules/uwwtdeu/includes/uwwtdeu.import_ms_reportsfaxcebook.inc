<?php

define('UWWTDEU_IMPORT_MS_URL', 'http://uwwtd.oieau.fr/services/ows?service=wfs&version=1.1.0&request=GetFeature&typename=UWWTD:UWWTD_FeedMSLevel_');
define('UWWTDEU_IMPORT_MS_COUNTRIES', 'at,be,bg,hr,cy,cz,dk,ee,fi,fr,de,el,hu,ie,it,lv,lt,lu,mt,nl,pl,pt,ro,sk,si,es,se,uk');

/**
 * Implements hook_form().
 */
function uwwtdeu_import_form($form, &$form_state) {
  $title = array('%title' => 'Import uwwtdeu data');
  $description = t('This operation will delete all existing uwwtdeu data and will reimport it.');

  return confirm_form($form, t('Are you sure you want to delete all existing uwwtdeu data and reimport it?', $title), '<front>', $description, t('Delete existing uwwtdeu data and reimport it'));
}

/**
 * Form submission handler for uwwtdeu_import_form().
 */
function uwwtdeu_import_form_submit($form, &$form_state) {
  _uwwtdeu_import_execute();
  $form_state['redirect'] = array('path' => 'admin/content');
}

/**
 * Executes the import procedure.
 */
function _uwwtdeu_import_execute() {
  watchdog('uwwtdeu', 'UWWTD EU import started.', array(), WATCHDOG_NOTICE);

  // Load all nids of nodes to be deleted
  $nids = db_select('node', 'n')
    ->fields('n', array('nid'))
    ->condition('n.type', 'eu_ms_report')
    ->execute()
    ->fetchCol();

  // Prepare a batch operation
  $batch = array(
    'operations' => array(
      array('_uwwtdeu_import_delete_existing_nodes', array($nids)),
      array('_uwwtdeu_import_create_eu_ms_reports', array(explode(',', UWWTDEU_IMPORT_MS_COUNTRIES))),
    ),
    'finished' => '_uwwtdeu_import_finished',
    'title' => t('Importing uwwtdeu data...'),
    'file' => drupal_get_path('module', 'uwwtdeu') . '/includes/uwwtdeu.import_data.inc',
  );

  // Execute the batch operation
  batch_set($batch);
}

/**
 * A batch operation that deletes all existing uwwtdeu data.
 */
function _uwwtdeu_import_delete_existing_nodes($nids, &$context) {
  $context['message'] = 'Deleting existing UWWTD EU data.';

  // Instantiate the batch sandbox
  if (!isset($context['sandbox']['progress'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['max'] = count($nids);
    $context['results']['deleted'] = 0;
  }

  // We will be deleting 5 nodes at a time
  $limit = 5;

  // Loop the next batch of nodes and delete them
  for ($i = 0; $i < $limit; $i++) {
    if (isset($nids[$context['sandbox']['progress']])) {
      node_delete($nids[$context['sandbox']['progress']]);
      $context['results']['deleted']++;
    }
    else {
      break;
    }

    $context['sandbox']['progress']++;
  }

  // Set the finished value so Drupal can update the progress bar
  if ($context['sandbox']['progress'] < $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

/**
 * A batch operation that imports member state report uwwtdeu data.
 */
function _uwwtdeu_import_create_eu_ms_reports($countries, &$context) {
  global $user;

  $context['message'] = 'Importing UWWTD EU member state report data.';

  // Instantiate the batch sandbox
  if (!isset($context['sandbox']['progress'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['max'] = count($countries);
    $context['results']['created'] = 0;
  }

  // We will be handling 3 countries at a time
  $limit = 3;

  // Import the new batch of countries
  for ($i = 0; $i < $limit; $i++) {
    if (isset($countries[$context['sandbox']['progress']])) {
      $country = $countries[$context['sandbox']['progress']];
      $xml = simplexml_load_file(UWWTDEU_IMPORT_MS_URL . $country);

      // Get the member state report data from the xml
      $msReports = $xml->xpath('//UWWTD:UWWTD_FeedMSLevel_' . $country);

      if (empty($msReports)) {
        drupal_set_message('No data or invalid xml for ' . $country, 'error');
      }
      else {
        foreach ($msReports as $msReport) {
          // Map the xml attributes to node fields
          $msReportDataMapping = array(
            'field_eu_repcode' => array($msReport->xpath('UWWTD:repCode'), 'string'),
            'field_eu_repreportedperiod' => array($msReport->xpath('UWWTD:repReportedPerdiod'), 'float'),
            'field_eu_mslsludgeproduction' => array($msReport->xpath('UWWTD:mslSludgeProduction'), 'float'),
            'field_eu_mslreusesoilagriculture' => array($msReport->xpath('UWWTD:mslReUseSoilAgriculture'), 'float'),
            'field_eu_mslreuseothers' => array($msReport->xpath('UWWTD:mslReUseOthers'), 'float'),
            'field_eu_msldisposallandfill' => array($msReport->xpath('UWWTD:mslDisposalOthers'), 'float'),
            'field_eu_msldisposalincineration' => array($msReport->xpath('UWWTD:mslDisposalIncineration'), 'float'),
            'field_eu_msldisposalothers' => array($msReport->xpath('UWWTD:mslDisposalLandfill'), 'float'),
          );

          // Create the new "eu_ms_report" node
          $node = new stdClass();
          $node->title = $country;
          $node->type = 'eu_ms_report';
          node_object_prepare($node);
          $node->language = LANGUAGE_NONE;
          $node->uid = $user->uid;
          $node->status = 1;
          $node->promote = 0;
          $node->comment = 0;
          foreach ($msReportDataMapping as $fieldName => $fieldData) {
            if (!empty($fieldData[0])) {
              settype($fieldData[0][0], $fieldData[1]);
              $node->{$fieldName}[$node->language][]['value'] = $fieldData[0][0];
              if ($fieldName == 'field_eu_repreportedperiod') {
                $node->title .= ' (' . $fieldData[0][0] . ')';
              }
            }
          }
          $node = node_submit($node);
          node_save($node);

          $context['results']['created']++;
        }
      }
    }
    else {
      break;
    }

    $context['sandbox']['progress']++;
  }

  // Set the finished value so Drupal can update the progress bar
  if ($context['sandbox']['progress'] < $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

/**
 * A callback that is called after the import is completed.
 */
function _uwwtdeu_import_finished($success, $results, $operations) {
  if ($success) {
    if (isset($results['deleted'])) {
      drupal_set_message($results['deleted'] . ' existing nodes were deleted.');
    }
    if (isset($results['created'])) {
      drupal_set_message($results['created'] . ' member state reports were imported.');
    }

    watchdog('uwwtdeu', 'UWWTD EU import completed.', array(), WATCHDOG_NOTICE);
  }
  else {
    $error_operation = reset($operations);
    $message = t('An error occurred while processing %error_operation with arguments: @arguments', array(
      '%error_operation' => $error_operation[0],
      '@arguments' => print_r($error_operation[1], TRUE)
    ));
    drupal_set_message($message, 'error');
    watchdog('uwwtdeu', 'UWWTD EU import failed.', array(), WATCHDOG_ERROR);
  }
}

