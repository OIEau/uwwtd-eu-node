<?php

define('UWWTDEU_IMPORT_MS_URL', 'https://uwwtd.eu/services/ows?service=wfs&version=1.1.0&request=GetFeature&typename=UWWTD:UWWTD_FeedMSLevel_');
define('UWWTDEU_IMPORT_MS_COUNTRIES', serialize(
  array(
    'at' => 'https://uwwtd.eu/Austria/',
    'be' => 'https://uwwtd.eu/Belgium/',
    'bg' => 'https://uwwtd.eu/Bulgaria/',
    'cy' => 'https://uwwtd.eu/Cyprus/',
    'cz' => 'https://uwwtd.eu/Czech-Republic/',
    'dk' => 'https://uwwtd.eu/Denmark/',
    'ee' => 'https://uwwtd.eu/Estonia/',
    'fi' => 'https://uwwtd.eu/Finland/',
    'fr' => 'https://uwwtd.eu/France/',
    'de' => 'https://uwwtd.eu/Germany/',
    'gr' => 'https://uwwtd.eu/Greece/',
    'hr' => 'https://uwwtd.eu/Croatia/',
    'hu' => 'https://uwwtd.eu/Hungary/',
    'ie' => 'https://uwwtd.eu/Ireland/',
    'it' => 'https://uwwtd.eu/Italia/',
    'lv' => 'https://uwwtd.eu/Latvia/',
    'lt' => 'https://uwwtd.eu/Lithuania/',
    'lu' => 'https://uwwtd.eu/Luxembourg/',
    'mt' => 'https://uwwtd.eu/Malta/',
    'nl' => 'https://uwwtd.eu/Netherlands/',
    'pl' => 'https://uwwtd.eu/Poland/',
    'pt' => 'https://uwwtd.eu/Portugal/',
    'ro' => 'https://uwwtd.eu/Romania/',
    'sk' => 'https://uwwtd.eu/Slovakia/',
    'si' => 'https://uwwtd.eu/Slovenia/',
    'es' => 'https://uwwtd.eu/Spain/',
    'se' => 'https://uwwtd.eu/Sweden/',
    'uk' => 'https://uwwtd.eu/United-Kingdom/'
  )
));

/**
 * Implements hook_form().
 */
function uwwtdeu_import_ms_levels_form($form, &$form_state) {
  $title = array('%title' => 'Import uwwtdeu member state levels');
  $description = t('This operation will delete all existing uwwtdeu member state levels and will reimport them.<br /><strong>IMPORTANT NOTE:</strong> Please import all agglomerations first, as this importer aggregates some agglomeration data.');

  $form = confirm_form($form, t('Are you sure you want to delete all existing uwwtdeu member state levels and reimport them?', $title), '<front>', $description, t('Delete existing uwwtdeu member state levels and reimport it'));
  
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
  
  //add country code filter 
  module_load_include('inc', 'uwwtd_sync', 'inc/uwwtd_sync.config');
  //require_once(drupal_get_path('module', 'uwwtd_sync') . '/inc/uwwtd_sync.config.inc');
  $country = array();
    //$GLOBALS['uwwtd_sync_conf'] is in uwwtd_sync.config.inc file
    foreach($GLOBALS['uwwtd_sync_conf']['country'] as $cc=>$val){
        $country[$cc] = $val['CountryName'];
    }
    //Sort the table
    asort($country);
    $form['country'] = array(
        '#title'=>t('Countries'),
        '#type'=>'checkboxes',
        '#options'=>$country,
        '#default_value'=>array_keys($country),
        '#checkall' =>'country-checkboxes'
    );
  
  return $form;
  
}

/**
 * Form submission handler for uwwtdeu_import_ms_levels_form().
 */
function uwwtdeu_import_ms_levels_form_submit($form, &$form_state) {
    $cc = array_flip($form_state['values']['country']);
    $report = $form_state['values']['report'];
    unset($cc[0]);
    $cc = array_flip($cc);
  _uwwtdeu_import_ms_levels_execute($report, $cc);
  $form_state['redirect'] = array('path' => 'admin/content');
}

/**
 * Executes the import procedure.
 */
function _uwwtdeu_import_ms_levels_execute($report, $ccs=[]) {
  watchdog('uwwtdeu', 'UWWTD EU member state levels import started for report : '.$report, array(), WATCHDOG_NOTICE);

  // Load all nids of nodes to be deleted
    
  $query = db_select('node', 'n');
    $query->fields('n', array('nid'));
    $query->join('field_data_field_reporting', 'r', 'n.nid=r.entity_id');
    $query->join('field_data_field_countrycode', 'c', 'n.nid=c.entity_id');
    $query->condition('n.type', 'ms_level');
    $query->condition('r.field_reporting_value', $report);
    $query->condition('c.field_countrycode_value', $ccs, 'IN');
    $query->groupBy('n.nid');
    $nids = $query->execute()->fetchCol();

  // Build a list of all countries (with data per country)
  $countries = array();
  $countryDataJsonFile = drupal_get_path('module', 'uwwtdeu') . '/utils/countries.json';
  $countryData = json_decode(file_get_contents($countryDataJsonFile));
  $euCountries = unserialize(UWWTDEU_IMPORT_MS_COUNTRIES);
  foreach ($countryData as $country) {
    if (array_key_exists(strtolower($country->CountryCode), $euCountries) ) {
      $countries[strtolower($country->CountryCode)] = array(
        'code' => strtolower($country->CountryCode),
        'name' => $country->CountryName,
        'latitude' => $country->CapitalLatitude,
        'longitude' => $country->CapitalLongitude,
        'nationalsite' => $euCountries[strtolower($country->CountryCode)],
      );
    }
  }

  // Prepare a batch operation
  $batch = array(
    'operations' => array(
      array('_uwwtdeu_import_ms_levels_delete', array($nids)),
      array('_uwwtdeu_import_ms_levels_create', array($report, $ccs, $countries)),
    ),
    'finished' => '_uwwtdeu_import_ms_levels_finished',
    'title' => t('Importing uwwtdeu ms levels...'),
    'file' => drupal_get_path('module', 'uwwtdeu') . '/includes/uwwtdeu.import_ms_levels.inc',
  );

  // Execute the batch operation
  batch_set($batch);
}

/**
 * A batch operation that deletes all existing uwwtdeu member state levels.
 */
function _uwwtdeu_import_ms_levels_delete($nids, &$context) {
  $context['message'] = 'Deleting existing UWWTD EU member state levels.';

  // Instantiate the batch sandbox
  if (!isset($context['sandbox']['progress'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['max'] = count($nids);
    $context['results']['deleted'] = 0;
  }

  // We will be deleting 10 nodes at a time
  $limit = 10;

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
 * A batch operation that imports member state level uwwtdeu member state levels.
 */
function _uwwtdeu_import_ms_levels_create($report, $ccs, $countries, &$context) {
  global $user;

  $context['message'] = 'Importing UWWTD EU ms levels.';

  // Instantiate the batch sandbox
  if (!isset($context['sandbox']['progress'])) {
    $count = db_query("SELECT COUNT(cc) FROM harvest.eu_".$report."_mslevel WHERE  cc IN ('".implode("', '", $ccs)."')")->fetchField();
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['max'] = $count;
    $context['results']['created'] = 0;
  }

  // We will be handling 500 MS levels at a time
  $limit = 100;

  // Load the MS levels source data
  $mslevels = db_query("SELECT 
        m.cc,m.gml_id,m.repcode,m.repreportedperdiod,m.mslsludgeproduction,m.mslreusesoilagriculture,m.mslreuseothers,m.msldisposalothers,m.msldisposalincineration,m.msldisposallandfill,
        c.number_2000_10000,c.number_10000_100000,c.number_more_100000,c.load_2000_10000,c.load_100000,c.load_more_100000,
        a.generatedload,a.connectedload,a.compliance_target,a.compliance_compliant,a.art3_target,a.art3_compliant 	art4_target,a.art4_compliant,a.art5_target,a.art5_compliant,a.art6_target,a.art6_compliant
    FROM harvest.eu_".$report."_mslevel m
        LEFT JOIN calcul.cc_stat_by_size_".$report." c ON c.cc = m.cc
        LEFT JOIN calcul.cc_stat_art_".$report." a ON a.cc = m.cc
    WHERE m.cc IN ('".implode("', '", $ccs)."')
    ORDER BY m.cc")->fetchAll();

  // Import the new batch of ms levels
  foreach ($mslevels as $mslevel) {
  // Aggregate agglomerations data for "Evolution of the load destination" graph
  $loadDestination = db_query("SELECT SUM(ias.field_aggias_value) AS \"ias\", SUM(con.field_aggconnected_value) AS \"connected\", SUM(gen.field_agggenerated_value) AS \"generated\", (SUM(gen.field_agggenerated_value) - SUM(ias.field_aggias_value) - SUM(con.field_aggconnected_value)) AS \"other\"
                        FROM {node} n
                            JOIN {field_data_field_reporting} r ON r.entity_id = n.nid
                            JOIN {field_data_field_aggias} ias ON ias.entity_id = n.nid
                            JOIN {field_data_field_agggenerated} gen ON gen.entity_id = n.nid
                            JOIN {field_data_field_aggconnected} con ON con.entity_id = n.nid
                            JOIN {field_data_field_countrycode} cc ON cc.entity_id = n.nid
                        WHERE cc.field_countrycode_value = :cc
                            AND r.field_reporting_value = :report
                            AND gen.field_agggenerated_value >= 2000", array(':report'=>$report,':cc' => $mslevel->cc))->fetchAll();
                        
    $country = $countries[$mslevel->cc];

    // Create the new "ms_level" node
    $node = new stdClass();
    $node->title = $country['name'] .' - '.$report;
    $node->type = 'ms_level';
    node_object_prepare($node);
    $node->language = LANGUAGE_NONE;
    $node->uid = $user->uid;
    $node->status = 1;
    $node->promote = 0;
    $node->comment = 0;
    $node->field_reporting[$node->language][0]['value'] = $report;
    $node->field_countrycode[$node->language][0]['value'] = $country['code'];
    $node->field_countryname[$node->language][0]['value'] = $country['name'];
    $node->field_msnationalsite[$node->language][0]['value'] = $country['nationalsite'];
    $node->field_position_geo[$node->language][0] = geofield_compute_values(
      array(
        'lat' => $country['latitude'],
        'lon' => $country['longitude'],
      ), GEOFIELD_INPUT_LAT_LON);

    $node->field_repcode[$node->language][0]['value'] = (string) $mslevel->repcode;
    $node->field_anneedata[$node->language][0]['value'] = (string) $mslevel->repreportedperdiod;
    $node->field_mslsludgeproduction[$node->language][0]['value'] = (float) $mslevel->mslsludgeproduction;
    $node->field_mslreusesoilagriculture[$node->language][0]['value'] = (float) $mslevel->mslreusesoilagriculture;
    $node->field_mslreuseothers[$node->language][0]['value'] = (float) $mslevel->mslreuseothers;
    $node->field_msldisposallandfill[$node->language][0]['value'] = (float) $mslevel->msldisposallandfill;
    $node->field_msldisposalincineration[$node->language][0]['value'] = (float) $mslevel->msldisposalincineration;
    $node->field_msldisposalothers[$node->language][0]['value'] = (float) $mslevel->msldisposalothers;
    $node->field_mslnotreported[$node->language][0]['value'] = (float) $mslevel->mslsludgeproduction - ((float) $mslevel->mslreusesoilagriculture + (float) $mslevel->mslreuseothers + (float) $mslevel->msldisposallandfill + (float) $mslevel->msldisposalincineration + (float) $mslevel->msldisposalothers);
    $node->field_mslnotreported[$node->language][0]['value'] = ($node->field_mslnotreported[$node->language][0]['value'] < 0) ? 0 : $node->field_mslnotreported[$node->language][0]['value'];
    $node->field_number_2000_10000[$node->language][0]['value'] = (float) $mslevel->number_2000_10000;
    $node->field_number_10000_100000[$node->language][0]['value'] = (float) $mslevel->number_10000_100000;
    $node->field_number_more_100000[$node->language][0]['value'] = (float) $mslevel->number_more_100000;
    $node->field_generatedload[$node->language][0]['value']= (float) $mslevel->generatedload;
    $node->field_connectedload[$node->language][0]['value']= (float) $mslevel->connectedload;
    $node->field_compliance_target[$node->language][0]['value']= (float) $mslevel->compliance_target;
    $node->field_compliance_compliant[$node->language][0]['value']= (float) $mslevel->compliance_compliant;
    $node->field_compliance_percentage[$node->language][0]['value'] = _uwwtdeu_import_ms_levels_compliance_percentage_category((float) $mslevel->compliance_compliant, (float) $mslevel->compliance_target);
    $node->field_art3_target[$node->language][0]['value']= (float) $mslevel->art3_target;
    $node->field_art3_compliant[$node->language][0]['value']= (float) $mslevel->art3_compliant;
    $node->field_art3_percentage[$node->language][0]['value'] = _uwwtdeu_import_ms_levels_compliance_percentage_category((float) $mslevel->art3_compliant, (float) $mslevel->art3_target);
    $node->field_art4_target[$node->language][0]['value']= (float) $mslevel->art4_target;
    $node->field_art4_compliant[$node->language][0]['value']= (float) $mslevel->art4_compliant;
    $node->field_art4_percentage[$node->language][0]['value'] = _uwwtdeu_import_ms_levels_compliance_percentage_category((float) $mslevel->art4_compliant, (float) $mslevel->art4_target);
    $node->field_art5_target[$node->language][0]['value']= (float) $mslevel->art5_target;
    $node->field_art5_compliant[$node->language][0]['value']= (float) $mslevel->art5_compliant;
    $node->field_art5_percentage[$node->language][0]['value'] = _uwwtdeu_import_ms_levels_compliance_percentage_category((float) $mslevel->art5_compliant, (float) $mslevel->art5_target);
    $node->field_art6_target[$node->language][0]['value']= (float) $mslevel->art6_target;
    $node->field_art6_compliant[$node->language][0]['value']= (float) $mslevel->art6_compliant;
    $node->field_art6_percentage[$node->language][0]['value'] = _uwwtdeu_import_ms_levels_compliance_percentage_category((float) $mslevel->art6_compliant, (float) $mslevel->art6_target);
    $node->field_load_destination_ias[$node->language][0]['value']= ((int) $loadDestination[0]->ias < 0) ? 0 : (int) $loadDestination[0]->ias;
    $node->field_load_destination_connected[$node->language][0]['value']= ((int) $loadDestination[0]->connected < 0) ? 0 : (int) $loadDestination[0]->connected;
    $node->field_load_destination_other[$node->language][0]['value']= (int) ((int) $loadDestination[0]->other < 0) ? 0 : (int) $loadDestination[0]->other;
    $node->field_load_destination_generated[$node->language][0]['value']= ((int) $loadDestination[0]->generated < 0) ? 0 : (int) $loadDestination[0]->generated;
    $node = node_submit($node);
    node_save($node);
    $context['results']['created']++;
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
function _uwwtdeu_import_ms_levels_finished($success, $results, $operations) {
  if ($success) {
    if (isset($results['deleted'])) {
      drupal_set_message($results['deleted'] . ' existing member state levels were deleted.');
    }
    if (isset($results['created'])) {
      drupal_set_message($results['created'] . ' member state levels were imported.');
    }

    watchdog('uwwtdeu', 'UWWTD EU member state levels import completed.', array(), WATCHDOG_NOTICE);
  }
  else {
    $error_operation = reset($operations);
    $message = t('An error occurred while processing %error_operation with arguments: @arguments', array(
      '%error_operation' => $error_operation[0],
      '@arguments' => print_r($error_operation[1], TRUE)
    ));
    drupal_set_message($message, 'error');
    watchdog('uwwtdeu', 'UWWTD EU member state levels import failed.', array(), WATCHDOG_ERROR);
  }
}

function _uwwtdeu_import_ms_levels_compliance_percentage_category($compliant, $target) {
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