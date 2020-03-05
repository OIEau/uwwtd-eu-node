<?php

//TODO : nd@oieau.fr : 23/01/2019 : find a solution in order to limit the reimport to only selected country by user
 
/**
 * Implements hook_form().
 */
function uwwtdeu_import_nuts2_regions_form($form, &$form_state) {
  $title = array('%title' => 'Import uwwtdeu nuts2 regions');
  $description = t('This operation will delete all existing uwwtdeu nuts2 regions and will reimport them.');

  $form = confirm_form($form, t('Are you sure you want to delete all existing uwwtdeu nuts2 regions and reimport them?', $title), '<front>', $description, t('Delete existing uwwtdeu nuts2 regions and reimport it'));
  
  $form['report'] = array(
    '#type'=>'select',
    '#title'=>t('Report'),
    '#options'=>[
        '9th'=>"9th report (2014-2015)",
        '10th'=>"10th report (2016)",
        '11th'=>"11th report (2018)",
    ],
    '#require'=>true,
    '#default_value'=>'10th',
  );
  return $form;
  
}

/**
 * Form submission handler for uwwtdeu_import_nuts2_regions_form().
 */
function uwwtdeu_import_nuts2_regions_form_submit($form, &$form_state) {
  _uwwtdeu_import_nuts2_regions_execute($form_state['values']['report']);
  $form_state['redirect'] = array('path' => 'admin/content');
}

/**
 * Executes the import procedure.
 */
function _uwwtdeu_import_nuts2_regions_execute($report) {
  watchdog('uwwtdeu', 'UWWTD EU nuts2 regions import started.', array(), WATCHDOG_NOTICE);

  // Load all nids of nodes to be deleted
    $query = db_select('node', 'n');
    $query->fields('n', array('nid'));
    $query->join('field_data_field_reporting', 'r', 'n.nid=r.entity_id');
    $query->condition('n.type', 'nuts2_region');
    $query->condition('r.field_reporting_value', $report);
    
    $nids = $query->execute()->fetchCol();
  // Load all NUTS 2 regions
  $field_regionnuts = field_info_field('field_regionnuts');
  $nuts2List = list_allowed_values($field_regionnuts);

  // Load all generated load by article/compliance
  $artLoad = array();
  foreach (range(3, 6) as $artNumber) {
    $loadName = ($artNumber == 3) ? 'generatedload' : 'connectedload';
    $artName = "art".$artNumber;
    $artLoad[$artName] = array();
    $artData = db_query("
        SELECT * 
        FROM calcul.nuts2_".$artName."_".$report."
        ORDER BY nuts2
    ")->fetchAll();
    foreach ($artData as $artRow) {
      if (!array_key_exists($artRow->nuts2, $artLoad[$artName])) {
        $artLoad[$artName][$artRow->nuts2] = array();
      }
      $artLoad[$artName][$artRow->nuts2][$artRow->{$artName}] = $artRow->{$loadName};
    }
  }

  // Prepare a batch operation
  $batch = array(
    'operations' => array(
      array('_uwwtdeu_import_nuts2_regions_delete', array($nids)),
      array('_uwwtdeu_import_nuts2_regions_create', array($report, $nuts2List, $artLoad)),
    ),
    'finished' => '_uwwtdeu_import_nuts2_regions_finished',
    'title' => t('Importing uwwtdeu nuts2 regions...'),
    'file' => drupal_get_path('module', 'uwwtdeu') . '/includes/uwwtdeu.import_nuts2_regions.inc',
  );

  // Execute the batch operation
  batch_set($batch);
}

/**
 * A batch operation that deletes all existing uwwtdeu nuts2 regions.
 */
function _uwwtdeu_import_nuts2_regions_delete($nids, &$context) {
  $context['message'] = 'Deleting existing UWWTD EU nuts2 regions.';

  // Instantiate the batch sandbox
  if (!isset($context['sandbox']['progress'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['max'] = count($nids);
    $context['results']['deleted'] = 0;
  }

  // We will be deleting 200 nodes at a time
  $limit = 500;

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
 * A batch operation that imports nuts2_region uwwtdeu nuts2 regions.
 */
function _uwwtdeu_import_nuts2_regions_create($report,$nuts2List, $artLoad, &$context) {
  global $user;

  $context['message'] = 'Importing UWWTD EU nuts2 regions.';

  // Instantiate the batch sandbox
  if (!isset($context['sandbox']['progress'])) {
    $count = db_query("SELECT COUNT(gid) FROM data.nuts_2")->fetchField();
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['max'] = $count;
    $context['results']['created'] = 0;
  }

  // We will be handling 500 nuts2 regions at a time
  $limit = 1000;

  // Load the nuts2 regions source data
  $nuts2_regions = db_query_range("SELECT d.gid, d.nuts_id, public.ST_centroid(d.geom) AS point, c.*
                                   FROM data.nuts_2 d
                                   LEFT JOIN calcul.nuts2_stat_art_".$report." c ON d.nuts_id = c.nuts2
                                   ORDER BY d.gid", $context['sandbox']['progress'], $limit)->fetchAll();

  // Import the new batch of nuts2 regions
  foreach ($nuts2_regions as $nuts2_region) {
    // Only create the node if the nuts id is known to us
    if (array_key_exists($nuts2_region->nuts_id, $nuts2List)) {
      // Create the new "nuts2_region" node
      $node = new stdClass();
      $node->title = $nuts2List[$nuts2_region->nuts_id];
      $node->type = 'nuts2_region';
      node_object_prepare($node);
      $node->language = LANGUAGE_NONE;
      $node->uid = $user->uid;
      $node->status = 1;
      $node->promote = 0;
      $node->comment = 0;
      $node->field_reporting[$node->language][0]['value'] = $report;
      $node->field_countrycode[$node->language][0]['value'] = substr((string) $nuts2_region->nuts_id, 0, 2);
      $node->field_regionnuts[$node->language][0]['value'] = (string) $nuts2_region->nuts_id;
      $node->field_position_geo[$node->language][0] = array('geom' => $nuts2_region->point);
      $node->field_generatedload[$node->language][0]['value']= (float) $nuts2_region->generatedload;
      $node->field_connectedload[$node->language][0]['value']= (float) $nuts2_region->connectedload;
      $node->field_compliance_target[$node->language][0]['value']= (float) $nuts2_region->compliance_target;
      $node->field_compliance_compliant[$node->language][0]['value']= (float) $nuts2_region->compliance_compliant;
      $node->field_compliance_percentage[$node->language][0]['value'] = _uwwtdeu_import_nuts2_regions_compliance_percentage_category((float) $nuts2_region->compliance_compliant, (float) $nuts2_region->compliance_target);
      $node->field_art3_target[$node->language][0]['value']= (float) $nuts2_region->art3_target;
      $node->field_art3_compliant[$node->language][0]['value']= (float) $nuts2_region->art3_compliant;
      $node->field_art3_percentage[$node->language][0]['value'] = _uwwtdeu_import_nuts2_regions_compliance_percentage_category((float) $nuts2_region->art3_compliant, (float) $nuts2_region->art3_target);
      $node->field_art4_target[$node->language][0]['value']= (float) $nuts2_region->art4_target;
      $node->field_art4_compliant[$node->language][0]['value']= (float) $nuts2_region->art4_compliant;
      $node->field_art4_percentage[$node->language][0]['value'] = _uwwtdeu_import_nuts2_regions_compliance_percentage_category((float) $nuts2_region->art4_compliant, (float) $nuts2_region->art4_target);
      $node->field_art5_target[$node->language][0]['value']= (float) $nuts2_region->art5_target;
      $node->field_art5_compliant[$node->language][0]['value']= (float) $nuts2_region->art5_compliant;
      $node->field_art5_percentage[$node->language][0]['value'] = _uwwtdeu_import_nuts2_regions_compliance_percentage_category((float) $nuts2_region->art5_compliant, (float) $nuts2_region->art5_target);
      $node->field_art6_target[$node->language][0]['value']= (float) $nuts2_region->art6_target;
      $node->field_art6_compliant[$node->language][0]['value']= (float) $nuts2_region->art6_compliant;
      $node->field_art6_percentage[$node->language][0]['value'] = _uwwtdeu_import_nuts2_regions_compliance_percentage_category((float) $nuts2_region->art6_compliant, (float) $nuts2_region->art6_target);
      foreach ($artLoad as $artName => $nutsRegions) {
        if (array_key_exists($nuts2_region->nuts_id, $nutsRegions)) {
          foreach ($nutsRegions[$nuts2_region->nuts_id] as $complianceCode => $generatedLoad) {
            if (in_array($complianceCode, array('C', 'NC'))) {
              $fieldName = 'field_' . $artName . '_' . strtolower($complianceCode) . '_load';
              $node->{$fieldName}[$node->language][0]['value'] = $generatedLoad;
            }
          }
        }
      }
      $node = node_submit($node);
      node_save($node);
      $context['results']['created']++;
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
function _uwwtdeu_import_nuts2_regions_finished($success, $results, $operations) {
  if ($success) {
    if (isset($results['deleted'])) {
      drupal_set_message($results['deleted'] . ' existing nuts2 regions were deleted.');
    }
    if (isset($results['created'])) {
      drupal_set_message($results['created'] . ' nuts2 regions were imported.');
    }

    watchdog('uwwtdeu', 'UWWTD EU nuts2 regions import completed.', array(), WATCHDOG_NOTICE);
  }
  else {
    $error_operation = reset($operations);
    $message = t('An error occurred while processing %error_operation with arguments: @arguments', array(
      '%error_operation' => $error_operation[0],
      '@arguments' => print_r($error_operation[1], TRUE)
    ));
    drupal_set_message($message, 'error');
    watchdog('uwwtdeu', 'UWWTD EU nuts2 regions import failed.', array(), WATCHDOG_ERROR);
  }
}

function _uwwtdeu_import_nuts2_regions_compliance_percentage_category($compliant, $target) {
  if ((float) $target == 0) {
    $value = 100;
  }
  else {
    $value = ((float) $compliant / (float) $target) * 100;
  }

  switch ((float) $value) {
    case $value <= 70:
      return '0_70';
    case $value <= 85:
      return '70_85';
    case $value <= 95:
      return '85_95';
    case $value <= 97:
      return '95_97';
    default:
      return '97_100';
  }
}