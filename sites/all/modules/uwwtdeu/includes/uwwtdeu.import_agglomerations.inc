<?php

/**
 * Implements hook_form().
 */
function uwwtdeu_import_agglomerations_form($form, &$form_state) {
  $title = array('%title' => 'Import uwwtdeu agglomerations');
  $description = t('This operation will delete all existing uwwtdeu agglomerations and will reimport them.');
  $form =  confirm_form($form, t('Are you sure you want to delete all existing uwwtdeu agglomerations and reimport them?', $title), '<front>', $description, t('Delete existing uwwtdeu agglomerations and reimport it'));
  
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
 * Form submission handler for uwwtdeu_import_agglomerations_form().
 */
function uwwtdeu_import_agglomerations_form_submit($form, &$form_state) {
    $cc = array_flip($form_state['values']['country']);
    $report = $form_state['values']['report'];
    unset($cc[0]);
    $cc = array_flip($cc);
  _uwwtdeu_import_agglomerations_execute($report, $cc);
  $form_state['redirect'] = array('path' => 'admin/content');
}

/**
 * Executes the import procedure.
 */
function _uwwtdeu_import_agglomerations_execute($report, $ccs=[]) {
  watchdog('uwwtdeu', 'UWWTD EU agglomerations import started for report : '.$report, array(), WATCHDOG_NOTICE);
   if(!empty($ccs)){
       
      // Load all nids of nodes to be deleted
      $query = db_select('node', 'n');
        $query->fields('n', array('nid'));
        $query->join('field_data_field_reporting', 'r', 'n.nid=r.entity_id');
        $query->join('field_data_field_countrycode', 'c', 'n.nid=c.entity_id');
        $query->condition('n.type', 'agglomeration');
        $query->condition('r.field_reporting_value', $report);
        $query->condition('c.field_countrycode_value', $ccs, 'IN');
        $query->groupBy('n.nid');
        
        $nids = $query->execute()->fetchCol();

      // Prepare a batch operation
      $batch = array(
        'operations' => array(
          array('_uwwtdeu_import_agglomerations_delete', array($nids)),
          array('_uwwtdeu_import_agglomerations_create', array($report, $ccs)),
        ),
        'finished' => '_uwwtdeu_import_agglomerations_finished',
        'title' => t('Importing uwwtdeu agglomerations...'),
        'file' => drupal_get_path('module', 'uwwtdeu') . '/includes/uwwtdeu.import_agglomerations.inc',
      );

      // Execute the batch operation
      batch_set($batch);
   }
}

/**
 * A batch operation that deletes all existing uwwtdeu agglomerations.
 */
function _uwwtdeu_import_agglomerations_delete($nids, &$context) {
  $context['message'] = 'Deleting existing UWWTD EU agglomerations.';

  // Instantiate the batch sandbox
  if (!isset($context['sandbox']['progress'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['max'] = count($nids);
    $context['results']['deleted'] = 0;
  }

  // We will be deleting 200 nodes at a time
  $limit = 100;

  // Loop the next batch of nodes and delete them
  for ($i = 0; $i < $limit; $i++) {
    if (isset($nids[$context['sandbox']['progress']])) {
      node_delete($nids[$context['sandbox']['progress']]);
      $context['results']['deleted']++;
    }
    else {
      break;
    }
    $context['message'] = 'Deleting existing UWWTD EU agglomerations : '.$context['results']['deleted'].'/'.$context['sandbox']['max'];
    $context['sandbox']['progress']++;
  }

  // Set the finished value so Drupal can update the progress bar
  if ($context['sandbox']['progress'] < $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

/**
 * A batch operation that imports agglomeration uwwtdeu agglomerations.
 */
function _uwwtdeu_import_agglomerations_create($report, $ccs, &$context) {
  global $user;

  

  // Instantiate the batch sandbox
  if (!isset($context['sandbox']['progress'])) {
    $count = db_query("
        SELECT COUNT(aggcode) FROM harvest.eu_".$report."_agglomeration_all  WHERE aggstate = '1' AND cc IN ('".implode("', '", $ccs)."')
    ")->fetchField();
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['max'] = $count;
    $context['results']['created'] = 0;
  }

  // We will be handling 100 agglomerations at a time
  $limit = 100;

  // Load the agglomerations source data
  $agglomerations = db_query_range("
    SELECT * 
    FROM harvest.eu_".$report."_agglomeration_all 
    WHERE aggstate = '1' 
        AND cc IN ('".implode("', '", $ccs)."')
    ORDER BY aggcode
    ",
  $context['sandbox']['progress'], $limit)->fetchAll();

  // Import the new batch of agglomerations
  foreach ($agglomerations as $agglomeration) {
    // Create the new "agglomeration" node
    $node = new stdClass();
    $node->title = $agglomeration->aggname;
    $node->type = 'agglomeration';
    node_object_prepare($node);
    $node->language = LANGUAGE_NONE;
    $node->uid = $user->uid;
    $node->status = 1;
    $node->promote = 0;
    $node->comment = 0;
    $node->field_reporting[$node->language][0]['value'] = $report;
    $node->field_countrycode[$node->language][0]['value'] = (string) $agglomeration->cc;
    $node->field_repcode[$node->language][0]['value'] = (string) $agglomeration->repcode;
    $node->field_anneedata[$node->language][0]['value'] = (string) $agglomeration->repreportedperdiod;
    $node->field_inspireidlocalid[$node->language][0]['value'] = (string) $agglomeration->aggcode;
//    $node->field_inspireidnamespace[$node->language][0]['value'] = (string) $agglomeration->;
    $node->field_status[$node->language][0]['value'] = (string) $agglomeration->aggstate;
//    $node->field_inspireidversionid[$node->language][0]['value'] = (string) $agglomeration->;
//    $node->field_namelanguage[$node->language][0]['value'] = (string) $agglomeration->;
//    $node->field_namenativeness[$node->language][0]['value'] = (string) $agglomeration->;
//    $node->field_namestatus[$node->language][0]['value'] = (string) $agglomeration->;
//    $node->field_sourceofname[$node->language][0]['value'] = (string) $agglomeration->;
//    $node->field_namepronunciation[$node->language][0]['value'] = (string) $agglomeration->;
//    $node->field_namegrammaticalgender[$node->language][0]['value'] = (string) $agglomeration->;
//    $node->field_namegrammaticalnumber[$node->language][0]['value'] = (string) $agglomeration->;
//    $node->field_aggmunicipalities[$node->language][0]['value'] = (string) $agglomeration->;
//    $node->field_aggsuccessor[$node->language][0]['value'] = (string) $agglomeration->;
//    $node->field_agglatitude[$node->language][0]['value'] = (float) $agglomeration->;
//    $node->field_agglongitude[$node->language][0]['value'] = (float) $agglomeration->;
    $node->field_agggenerated[$node->language][0]['value'] = (int) $agglomeration->generatedload;
    $node->field_aggconnected[$node->language][0]['value'] = (int) $agglomeration->connectedload;
    $node->field_aggias[$node->language][0]['value'] = (int) $agglomeration->iasload;
    $node->field_aggbigid[$node->language][0]['value'] = (string) $agglomeration->bigcitycode;
    $node->field_aggcalculation[$node->language][0]['value'] = (string) $agglomeration->aggcalculation;
    $node->field_aggchanges[$node->language][0]['value'] = (string) $agglomeration->aggchanges;
    $node->field_aggchangescomment[$node->language][0]['value'] = (string) $agglomeration->aggchangescomment;
    $node->field_aggperiodover3[$node->language][0]['value'] = (string) $agglomeration->aggperiodover3;
//    $node->field_aggdatecompliance3[$node->language][0]['value'] = (string) $agglomeration->;
    $node->field_aggperiodover4[$node->language][0]['value'] = (string) $agglomeration->aggperiodover4;
//    $node->field_aggdatecompliance4[$node->language][0]['value'] = (string) $agglomeration->;
    $node->field_aggperiodover5[$node->language][0]['value'] = (string) $agglomeration->aggperiodover5;
//    $node->field_aggdatecompliance5[$node->language][0]['value'] = (string) $agglomeration->;
    $node->field_aggperiodover6[$node->language][0]['value'] = (string) $agglomeration->aggperiodover6;
//    $node->field_aggdatecompliance6[$node->language][0]['value'] = (string) $agglomeration->;
    $node->field_aggc1[$node->language][0]['value'] = (float) $agglomeration->aggc1;
    $node->field_aggmethodc1[$node->language][0]['value'] = (string) $agglomeration->aggmethodc1;
    $node->field_aggc2[$node->language][0]['value'] = (float) $agglomeration->aggc2;
    $node->field_aggmethodc2[$node->language][0]['value'] = (string) $agglomeration->aggmethodc2;
    $node->field_aggpercwithouttreatment[$node->language][0]['value'] = (float) $agglomeration->aggpercwithouttreatment;
    $node->field_aggmethodwithouttreatment[$node->language][0]['value'] = (string) $agglomeration->aggmethodwithouttreatment;
    $node->field_aggpercprimtreatment[$node->language][0]['value'] = (float) $agglomeration->aggpercprimtreatment;
    $node->field_aggpercsectreatment[$node->language][0]['value'] = (float) $agglomeration->aggpercsectreatment;
    $node->field_aggpercstringenttreatment[$node->language][0]['value'] = (float) $agglomeration->aggperstringenttreatment;
    $node->field_aggsewagenetwork[$node->language][0]['value'] = (string) $agglomeration->aggsewagenetwork;
    $node->field_aggbesttechnicalknowledge[$node->language][0]['value'] = (string) $agglomeration->aggbesttechnicalknowledge;
    $node->field_aggseweroverflows_m3[$node->language][0]['value'] = (int) $agglomeration->aggseweroverflows_m3;
    $node->field_aggseweroverflows_pe[$node->language][0]['value'] = (int) $agglomeration->aggseweroverflows_pe;
    $node->field_agghaveregistrationsystem[$node->language][0]['value'] = (string) $agglomeration->agghaveregistrationsystem;
    $node->field_aggexistmaintenanceplan[$node->language][0]['value'] = (string) $agglomeration->aggexistmaintenanceplan;
    $node->field_aggpressuretest[$node->language][0]['value'] = (int) $agglomeration->aggpressuretest;
    $node->field_aggvideoinspections[$node->language][0]['value'] = (int) $agglomeration->aggvideoinspections;
    $node->field_aggothermeasures[$node->language][0]['value'] = (int) $agglomeration->aggothermeasures;
    $node->field_aggexplanationother[$node->language][0]['value'] = (string) $agglomeration->aggexplanationother;
    $node->field_agginhabitant[$node->language][0]['value'] = (int) $agglomeration->agginhabitants;
//    $node->field_agginhabitantsconnectedias[$node->language][0]['value'] = (string) $agglomeration->;
//    $node->field_agginhabitantswithouttreat[$node->language][0]['value'] = (string) $agglomeration->;
    $node->field_aggremarks[$node->language][0]['value'] = (string) $agglomeration->aggremarks;
//    $node->field_aggnathyperlink[$node->language][0]['value'] = (string) $agglomeration->;
//    $node->field_aggdateexported[$node->language][0]['value'] = (string) $agglomeration->;
//    $node->field_zonetype[$node->language][0]['value'] = (string) $agglomeration->;
//    $node->field_environmentaldomain1[$node->language][0]['value'] = (string) $agglomeration->;
//    $node->field_environmentaldomain2[$node->language][0]['value'] = (string) $agglomeration->;
//    $node->field_thematicid[$node->language][0]['value'] = (string) $agglomeration->;
//    $node->field_specialisedzonetype[$node->language][0]['value'] = (string) $agglomeration->;
//    $node->field_designationperiod[$node->language][0]['value'] = (string) $agglomeration->;
//    $node->field_beginlifespanversion[$node->language][0]['value'] = (string) $agglomeration->;
//    $node->field_endlifespanversion[$node->language][0]['value'] = (string) $agglomeration->;
//    $node->field_competentauthority[$node->language][0]['value'] = (string) $agglomeration->;
//    $node->field_legislationcitation[$node->language][0]['value'] = (string) $agglomeration->;
//    $node->field_documentationcitation[$node->language][0]['value'] = (string) $agglomeration->;
    $node->field_position_geo[$node->language][0] = array(
      'geom' => $agglomeration->wkb_geometry,
    );
    $node->field_sensitiveareatype[$node->language][0]['value'] = (string) $agglomeration->typeofsensitivearea;
//    $node->field_siteid[$node->language][0]['value'] = (string) $agglomeration->;
    $node->field_aggcompliance[$node->language][0]['value'] = (string) $agglomeration->globalcompliance;
//    $node->field_aggcritca[$node->language][0]['value'] = (string) $agglomeration->;
//    $node->field_aggcritcb[$node->language][0]['value'] = (string) $agglomeration->;
//    $node->field_aggcritb[$node->language][0]['value'] = (string) $agglomeration->;
    $node->field_aggart3compliance[$node->language][0]['value'] = (string) $agglomeration->aticle3compliance; // the R is omitted intentionally
    $node->field_aggart4compliance[$node->language][0]['value'] = (string) $agglomeration->article4compliance;
    $node->field_aggart5compliance[$node->language][0]['value'] = (string) $agglomeration->article5compliance;
    $node->field_regionnuts[$node->language][0]['value'] = (string) $agglomeration->nutscode;
//    $node->field_compliance_explication[$node->language][0]['value'] = (string) $agglomeration->;
//    $node->field_article_3_compliance_expli[$node->language][0]['value'] = (string) $agglomeration->;
//    $node->field_article_4_compliance_expli[$node->language][0]['value'] = (string) $agglomeration->;
//    $node->field_article_5_compliance_expli[$node->language][0]['value'] = (string) $agglomeration->;
    $node->field_aggaccoverflows[$node->language][0]['value'] = (int) $agglomeration->aggaccoverflows;
//    $node->field_aggcapacity[$node->language][0]['value'] = (string) $agglomeration->;
    $node->field_agg_dilution_rates[$node->language][0]['value'] = (int) $agglomeration->aggdilutionrates;
    $node->field_aggaccoverflownumber[$node->language][0]['value'] = (int) $agglomeration->aggaccoverflownumber;
    $node->field_aggforecast[$node->language][0]['value'] = (string) $agglomeration->aggforecast;
    $node->field_aggart6compliance[$node->language][0]['value'] = (string) $agglomeration->article6compliance;
//    $node->field_aggart3addcompliance[$node->language][0]['value'] = (string) $agglomeration->;
//    $node->field_aggbeginlife[$node->language][0]['value'] = (string) $agglomeration->;
//    $node->field_aggendlife[$node->language][0]['value'] = (string) $agglomeration->;
    $node = node_submit($node);
    node_save($node);

    $context['sandbox']['progress']++;
    $context['results']['created']++;
  }
    $context['message'] = 'Importing UWWTD EU agglomerations : '.$context['sandbox']['progress'] .'/'. $context['sandbox']['max'];
  // Set the finished value so Drupal can update the progress bar
  if ($context['sandbox']['progress'] < $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

/**
 * A callback that is called after the import is completed.
 */
function _uwwtdeu_import_agglomerations_finished($success, $results, $operations) {
  if ($success) {
    if (isset($results['deleted'])) {
      drupal_set_message($results['deleted'] . ' existing agglomerations were deleted.');
    }
    if (isset($results['created'])) {
      drupal_set_message($results['created'] . ' agglomerations were imported.');
    }

    watchdog('uwwtdeu', 'UWWTD EU agglomerations import completed.', array(), WATCHDOG_NOTICE);
  }
  else {
    $error_operation = reset($operations);
    $message = t('An error occurred while processing %error_operation with arguments: @arguments', array(
      '%error_operation' => $error_operation[0],
      '@arguments' => print_r($error_operation[1], TRUE)
    ));
    drupal_set_message($message, 'error');
    watchdog('uwwtdeu', 'UWWTD EU agglomerations import failed.', array(), WATCHDOG_ERROR);
  }
}

