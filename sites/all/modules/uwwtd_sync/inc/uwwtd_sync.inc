<?php 

require_once(drupal_get_path('module', 'uwwtd_sync') . '/inc/uwwtd_sync.config.inc');

/*

============ TODO : make this module more user-friendly : provide UI in admin, allow sync only for one country, add confim form...

*/

/*
UWWTD:UWWTD_FeedAggloLevel_ee

http://www.uwwtd.oieau.fr/services/ows/?service=WFS&version=1.1.0&request=GetFeature&typeName=UWWTD:UWWTD_recette_Estonia_Agglomeration&CQL_FILTER=UWWTD:repReportedPerdiod=2014
http://www.uwwtd.oieau.fr/services/ows/?service=WFS&version=1.1.0&request=GetFeature&typeName=UWWTD:UWWTD_recette_France_Agglomeration&CQL_FILTER=UWWTD:repReportedPerdiod=2014
http://www.uwwtd.oieau.fr/services/ows/?service=WFS&version=1.1.0&request=GetFeature&typeName=UWWTD:UWWTD_recette_Poland_Agglomeration&CQL_FILTER=UWWTD:repReportedPerdiod=2014

CREATE TABLE harvest.eu_8th_agglomeration_all AS TABLE harvest.eu_9th_agglomeration_all WITH NO DATA;
CREATE TABLE harvest.eu_8th_mslevel AS TABLE harvest.eu_9th_mslevel WITH NO DATA;

*/



function uwwtd_sync_harvest_form($form, &$form_state){
    $country = array();
    //$GLOBALS['uwwtd_sync_conf'] is in uwwtd_sync.config.inc file
    foreach($GLOBALS['uwwtd_sync_conf']['country'] as $cc=>$val){
        $country[$cc] = $val['CountryName'];
    }
    //Sort the table
    asort($country);
    
    $form['report'] = array(
        '#title'=>t('Report'),
        '#type'=>'select',
        '#options'=>[
            '9th'=>"9th report (2014-2015)",
            '10th'=>"10th report (2016)",
        ],
        '#require'=>true,
        '#default_value'=>'10th',
    );
    
    $form['country'] = array(
        '#title'=>t('Countries'),
        '#type'=>'checkboxes',
        '#options'=>$country,
        '#default_value'=>array_keys($country),
        '#checkall' =>'country-checkboxes'
    );
    $form['force_geo'] = array(
        '#title'=>t('Force crossing with NUTS and RBD layers'),
        '#type'=>'select',
        '#options'=>[1=>t('Yes'), 0=>t('No')],
        '#default_value'=>0,
        '#description'=>"<div>If yes, the crossing will be done on all entities, in no, only entities with empty value will be processed</div>"
    );
    
    $form['submit'] = array(
        '#type'=>'submit',
        '#value'=>t('Harvest now')
    );
    
    return $form;
}
function uwwtd_sync_harvest_form_validate($form, &$form_state){
    //do nothing
}
function uwwtd_sync_harvest_form_submit($form, &$form_state){
    $cc = array_flip($form_state['values']['country']);
    $report = $form_state['values']['report'];
    $force_geo = $form_state['values']['force_geo'];
    unset($cc[0]);
    $cc = array_flip($cc);
    $operations = array();
    
    if(!empty($cc)){ 
    /*
$operations[] = array('uwwtd_sync_harvest_art17_batch', array('ccs'=>array_values($cc), 'report'=>$report));
$operations[] = array('uwwtd_sync_aggregate_art17_mslevel_batch', array('ccs'=>array_values($cc), 'report'=>$report));
$operations[] = array('uwwtd_sync_aggregate_art17_agglomeration_batch', array('ccs'=>array_values($cc), 'report'=>$report));
$operations[] = array('uwwtd_sync_aggregate_art17_uwwtp_batch', array('ccs'=>array_values($cc), 'report'=>$report));
$operations[] = array('uwwtd_sync_calculate_stats_batch', array('report'=>$report));
*/

       //=========== 1. bulk load of WFS data foreach country in database 
        $operations[] = array('uwwtd_sync_harvest_agg_batch', array('ccs'=>array_values($cc), 'report'=>$report));
        $operations[] = array('uwwtd_sync_harvest_art17_batch', array('ccs'=>array_values($cc), 'report'=>$report));
        $operations[] = array('uwwtd_sync_harvest_uwwtp_batch', array('ccs'=>array_values($cc), 'report'=>$report));
        $operations[] = array('uwwtd_sync_harvest_dcp_batch', array('ccs'=>array_values($cc), 'report'=>$report));
        $operations[] = array('uwwtd_sync_harvest_agg_uwwtp_batch', array('ccs'=>array_values($cc), 'report'=>$report));
        
        //=========== 2. Aggregate MS Level  => harvest.eu_9th_mslevel
        $operations[] = array('uwwtd_sync_aggregate_mslevel_batch', array('ccs'=>array_values($cc), 'report'=>$report));
        
        //=========== 3. Aggregate Agglo, UWWTP & DCP  => harvest.eu_9th_agglomeration_all
        $operations[] = array('uwwtd_sync_aggregate_agglo_batch', array('ccs'=>array_values($cc), 'report'=>$report));
        $operations[] = array('uwwtd_sync_aggregate_uwwtp_batch', array('ccs'=>array_values($cc), 'report'=>$report));
        $operations[] = array('uwwtd_sync_aggregate_dcp_batch', array('ccs'=>array_values($cc), 'report'=>$report));
        $operations[] = array('uwwtd_sync_aggregate_agg_uwwtp_batch', array('ccs'=>array_values($cc), 'report'=>$report));
        
        //=========== 4. Aggregate Art 17  
        $operations[] = array('uwwtd_sync_aggregate_art17_mslevel_batch', array('ccs'=>array_values($cc), 'report'=>$report));
        $operations[] = array('uwwtd_sync_aggregate_art17_agglomeration_batch', array('ccs'=>array_values($cc), 'report'=>$report));
        $operations[] = array('uwwtd_sync_aggregate_art17_uwwtp_batch', array('ccs'=>array_values($cc), 'report'=>$report));

        //=========== 5. fill blank data in agglo table base on geo data
        $operations[] = array('uwwtd_sync_fill_blank_data_nuts_batch', array('ccs'=>array_values($cc), 'report'=>$report, 'force_geo'=>$force_geo));
        $operations[] = array('uwwtd_sync_fill_blank_data_rbd_batch', array('ccs'=>array_values($cc), 'report'=>$report,  'force_geo'=>$force_geo ));

        //=========== 6. calculate statistics at eu level
        $operations[] = array('uwwtd_sync_calculate_stats_batch', array('report'=>$report));
        
  ///    
    }
  
    //Start operation 
    if(!empty($operations)){
        $batch = array(
            'operations' => $operations,
            'finished' => 'uwwtd_sync_harvest_finish',
            'title' => t('Processing Batch'),
            'init_message' => t('Batch is starting.'),
            'progress_message' => t('Processed @current out of @total.'),
            'error_message' => t('Harvesting Batch has encountered an error.'),
            'file' => drupal_get_path('module', 'uwwtd_sync') . '/inc/uwwtd_sync.inc',
        );
        batch_set($batch); //Starting the Batch
        batch_process('admin/config/uwwtd/harvest'); 
    }
    
}

function uwwtd_sync_harvest_agg_batch($ccs, $report, &$context){   
    //Initialisation du batch
    if (!isset($context['sandbox']['progress'])) {

        $context['sandbox']['max'] = count($ccs);
        $context['results']['data']['list'] = $ccs;
        $context['sandbox']['progress']=0;
    }
    
    //Process
    $cc = $context['results']['data']['list'][$context['sandbox']['progress']];
    $output = uwwtd_sync_harvest_agg($cc, $report);
    $context['sandbox']['progress']++;
    $context['message'] = '<h3>Harvest data for '.$GLOBALS['uwwtd_sync_conf']['country'][$cc]['CountryName'].' Ok </h3>';
    $context['message'].= '<p>Data store in : '.$output['MSLEVEL']['store'].'</p>';
    $context['message'].= 'with following stdout : </p>';
    $context['message'].= '<pre>'.print_r($output['MSLEVEL']['out'], true).'</pre>';
    
    //Condition d'arret
    if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
        $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
    } 
}
function uwwtd_sync_harvest_uwwtp_batch($ccs, $report, &$context){   
    //Initialisation du batch
    if (!isset($context['sandbox']['progress'])) {

        $context['sandbox']['max'] = count($ccs);
        $context['results']['data']['list'] = $ccs;
        $context['sandbox']['progress']=0;
    }
    
    //Process
    $cc = $context['results']['data']['list'][$context['sandbox']['progress']];
    $output = uwwtd_sync_harvest_uwwtp($cc, $report);
    $context['sandbox']['progress']++;
    $context['message'] = '<h3>Harvest data for '.$GLOBALS['uwwtd_sync_conf']['country'][$cc]['CountryName'].' Ok </h3>';
    $context['message'].= '<p>Data store in : '.$output['uwwtp']['store'].'</p>';
    $context['message'].= 'with following stdout : </p>';
    $context['message'].= '<pre>'.print_r($output['uwwtp']['out'], true).'</pre>';
    
    //Condition d'arret
    if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
        $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
    } 
}
function uwwtd_sync_harvest_dcp_batch($ccs, $report, &$context){   
    //Initialisation du batch
    if (!isset($context['sandbox']['progress'])) {

        $context['sandbox']['max'] = count($ccs);
        $context['results']['data']['list'] = $ccs;
        $context['sandbox']['progress']=0;
    }
    
    //Process
    $cc = $context['results']['data']['list'][$context['sandbox']['progress']];
    $output = uwwtd_sync_harvest_dcp($cc, $report);
    $context['sandbox']['progress']++;
    $context['message'] = '<h3>Harvest data for '.$GLOBALS['uwwtd_sync_conf']['country'][$cc]['CountryName'].' Ok </h3>';
    $context['message'].= '<p>Data store in : '.$output['dcp']['store'].'</p>';
    $context['message'].= 'with following stdout : </p>';
    $context['message'].= '<pre>'.print_r($output['dcp']['out'], true).'</pre>';
    
    //Condition d'arret
    if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
        $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
    } 
}
function uwwtd_sync_harvest_agg_uwwtp_batch($ccs, $report, &$context){   
    //Initialisation du batch
    if (!isset($context['sandbox']['progress'])) {

        $context['sandbox']['max'] = count($ccs);
        $context['results']['data']['list'] = $ccs;
        $context['sandbox']['progress']=0;
    }
    
    //Process
    $cc = $context['results']['data']['list'][$context['sandbox']['progress']];
    $output = uwwtd_sync_harvest_agg_uwwtp($cc, $report);
    $context['sandbox']['progress']++;
    $context['message'] = '<h3>Harvest data for '.$GLOBALS['uwwtd_sync_conf']['country'][$cc]['CountryName'].' Ok </h3>';
    $context['message'].= '<p>Data store in : '.$output['agg_uwwtp']['store'].'</p>';
    $context['message'].= 'with following stdout : </p>';
    $context['message'].= '<pre>'.print_r($output['agg_uwwtp']['out'], true).'</pre>';
    
    //Condition d'arret
    if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
        $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
    } 
}
function uwwtd_sync_harvest_art17_batch($ccs, $report, &$context){   
    //Initialisation du batch
    if (!isset($context['sandbox']['progress'])) {

        $context['sandbox']['max'] = count($ccs);
        $context['results']['data']['list'] = $ccs;
        $context['sandbox']['progress']=0;
    }
    
    //Process
    $cc = $context['results']['data']['list'][$context['sandbox']['progress']];
    $output = uwwtd_sync_harvest_art17($cc, $report);
    $context['sandbox']['progress']++;
    $context['message'] = '<h3>Harvest data for '.$GLOBALS['uwwtd_sync_conf']['country'][$cc]['CountryName'].' Ok </h3>';
    $context['message'].= '<p>Data store in : '.$output['MSLEVEL']['store'].'</p>';
    $context['message'].= 'with following stdout : </p>';
    $context['message'].= '<pre>'.print_r($output['MSLEVEL']['out'], true).'</pre>';
    
    //Condition d'arret
    if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
        $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
    } 
}

function uwwtd_sync_aggregate_mslevel_batch($ccs, $report, &$context){   
    //Initialisation du batch
    if (!isset($context['sandbox']['progress'])) {

        $context['sandbox']['max'] = count($ccs);
        $context['results']['data']['list'] = $ccs;
        $context['sandbox']['progress']=0;
    }
    
    //Process
    $cc = $context['results']['data']['list'][$context['sandbox']['progress']];
    $output = uwwtd_sync_aggregate_mslevel($cc, $report);
    $context['sandbox']['progress']++;
    $context['message'] = '<h3>Aggregate MS level for '.$GLOBALS['uwwtd_sync_conf']['country'][$cc]['CountryName'].' Ok </h3>';
    
    //Condition d'arret
    if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
        $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
    } 
}

function uwwtd_sync_aggregate_agglo_batch($ccs, $report, &$context){   
    //Initialisation du batch
    if (!isset($context['sandbox']['progress'])) {

        $context['sandbox']['max'] = count($ccs);
        $context['results']['data']['list'] = $ccs;
        $context['sandbox']['progress']=0;
    }
    
    //Process
    $cc = $context['results']['data']['list'][$context['sandbox']['progress']];
    $output = uwwtd_sync_aggregate_agglo($cc, $report);
    $context['sandbox']['progress']++;
    $context['message'] = '<h3>Aggregate Agglo level for '.$GLOBALS['uwwtd_sync_conf']['country'][$cc]['CountryName'].' Ok </h3>';
    
    //Condition d'arret
    if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
        $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
    } 
}

function uwwtd_sync_aggregate_art17_mslevel_batch($ccs, $report, &$context){   
    //Initialisation du batch
    if (!isset($context['sandbox']['progress'])) {

        $context['sandbox']['max'] = count($ccs);
        $context['results']['data']['list'] = $ccs;
        $context['sandbox']['progress']=0;
    }
    
    //Process
    $cc = $context['results']['data']['list'][$context['sandbox']['progress']];
    $output = uwwtd_sync_aggregate_art17_mslevel($cc, $report);
    $context['sandbox']['progress']++;
    $context['message'] = '<h3>Aggregate Art 17 MS level for '.$GLOBALS['uwwtd_sync_conf']['country'][$cc]['CountryName'].' Ok </h3>';
    
    //Condition d'arret
    if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
        $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
    } 
}

function uwwtd_sync_aggregate_art17_agglomeration_batch($ccs, $report, &$context){   
    //Initialisation du batch
    if (!isset($context['sandbox']['progress'])) {

        $context['sandbox']['max'] = count($ccs);
        $context['results']['data']['list'] = $ccs;
        $context['sandbox']['progress']=0;
    }
    
    //Process
    $cc = $context['results']['data']['list'][$context['sandbox']['progress']];
    $output = uwwtd_sync_aggregate_art17_agglomeration($cc, $report);
    $context['sandbox']['progress']++;
    $context['message'] = '<h3>Aggregate Art 17 Agglomeration level for '.$GLOBALS['uwwtd_sync_conf']['country'][$cc]['CountryName'].' Ok </h3>';
    
    //Condition d'arret
    if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
        $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
    } 
}

function uwwtd_sync_aggregate_art17_uwwtp_batch($ccs, $report, &$context){   
    //Initialisation du batch
    if (!isset($context['sandbox']['progress'])) {

        $context['sandbox']['max'] = count($ccs);
        $context['results']['data']['list'] = $ccs;
        $context['sandbox']['progress']=0;
    }
    
    //Process
    $cc = $context['results']['data']['list'][$context['sandbox']['progress']];
    $output = uwwtd_sync_aggregate_art17_uwwtp($cc, $report);
    $context['sandbox']['progress']++;
    $context['message'] = '<h3>Aggregate Art 17 UWWTP level for '.$GLOBALS['uwwtd_sync_conf']['country'][$cc]['CountryName'].' Ok </h3>';
    
    //Condition d'arret
    if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
        $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
    } 
}
function uwwtd_sync_aggregate_uwwtp_batch($ccs, $report, &$context){   
    //Initialisation du batch
    if (!isset($context['sandbox']['progress'])) {

        $context['sandbox']['max'] = count($ccs);
        $context['results']['data']['list'] = $ccs;
        $context['sandbox']['progress']=0;
    }
    
    //Process
    $cc = $context['results']['data']['list'][$context['sandbox']['progress']];
    $output = uwwtd_sync_aggregate_uwwtp($cc, $report);
    $context['sandbox']['progress']++;
    $context['message'] = '<h3>Aggregate UWWTP  for '.$GLOBALS['uwwtd_sync_conf']['country'][$cc]['CountryName'].' Ok </h3>';
    
    //Condition d'arret
    if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
        $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
    } 
}
function uwwtd_sync_aggregate_dcp_batch($ccs, $report, &$context){   
    //Initialisation du batch
    if (!isset($context['sandbox']['progress'])) {

        $context['sandbox']['max'] = count($ccs);
        $context['results']['data']['list'] = $ccs;
        $context['sandbox']['progress']=0;
    }
    
    //Process
    $cc = $context['results']['data']['list'][$context['sandbox']['progress']];
    $output = uwwtd_sync_aggregate_dcp($cc, $report);
    $context['sandbox']['progress']++;
    $context['message'] = '<h3>Aggregate DCP  for '.$GLOBALS['uwwtd_sync_conf']['country'][$cc]['CountryName'].' Ok </h3>';
    
    //Condition d'arret
    if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
        $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
    } 
}
function uwwtd_sync_aggregate_agg_uwwtp_batch($ccs, $report, &$context){   
    //Initialisation du batch
    if (!isset($context['sandbox']['progress'])) {

        $context['sandbox']['max'] = count($ccs);
        $context['results']['data']['list'] = $ccs;
        $context['sandbox']['progress']=0;
    }
    
    //Process
    $cc = $context['results']['data']['list'][$context['sandbox']['progress']];
    $output = uwwtd_sync_aggregate_agg_uwwtp($cc, $report);
    $context['sandbox']['progress']++;
    $context['message'] = '<h3>Aggregate agg_uwwtp  for '.$GLOBALS['uwwtd_sync_conf']['country'][$cc]['CountryName'].' Ok </h3>';
    
    //Condition d'arret
    if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
        $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
    } 
}

function uwwtd_sync_fill_blank_data_nuts_batch($ccs, $report, $force_geo, &$context){
    if (!isset($context['sandbox']['progress'])) {

        //manage version of NUTS
        if($report=='10th'){
            $version = '_v2016';
        }else{
            $version = '';
        }
        $context['results']['data']['list'] = array();
        foreach($ccs as $cc){

            //NUTS 1
            $context['results']['data']['list'][] = [
            'query'=>"
                UPDATE harvest.eu_".$report."_agglomeration_all SET nust1code = nuts_1".$version.".nuts_id
                FROM data.nuts_1".$version."
                WHERE ".($force_geo==1?'':'nust1code IS NULL AND')." 
                    eu_".$report."_agglomeration_all.cc = '".$cc."' AND nuts_1".$version.".nuts_id LIKE '".strtoupper($cc)."%' 
                    AND wkb_geometry && nuts_1".$version.".geom 
                    AND st_intersects(wkb_geometry,nuts_1".$version.".geom);
            ",
            'report'=>$report,
            'cc'=>$cc
            ];
            //NUTS 2
            $context['results']['data']['list'][] = [
            'query'=>"
                UPDATE harvest.eu_".$report."_agglomeration_all SET nust2code = nuts_2".$version.".nuts_id
                FROM data.nuts_2".$version."
                WHERE ".($force_geo==1?'':'nust2code IS NULL AND')."
                    eu_".$report."_agglomeration_all.cc = '".$cc."' AND nuts_2".$version.".nuts_id LIKE '".strtoupper($cc)."%' 
                    AND wkb_geometry && nuts_2".$version.".geom 
                    AND st_intersects(wkb_geometry,nuts_2".$version.".geom);
            ",
            'report'=>$report,
            'cc'=>$cc
            ];
            //NUTS 3
            $context['results']['data']['list'][] = [
            'query'=>"
                UPDATE harvest.eu_".$report."_agglomeration_all SET nust3code = nuts_3".$version.".nuts_id
                FROM data.nuts_3".$version."
                WHERE ".($force_geo==1?'':'nust3code IS NULL AND')."
                    eu_".$report."_agglomeration_all.cc = '".$cc."' AND nuts_3".$version.".nuts_id LIKE '".strtoupper($cc)."%' 
                    AND wkb_geometry && nuts_3".$version.".geom 
                    AND st_intersects(wkb_geometry,nuts_3".$version.".geom)
            ",
            'report'=>$report,
            'cc'=>$cc
            ];
        }
        $context['sandbox']['max'] = count($context['results']['data']['list']);
        $context['sandbox']['progress']=0;
    }
    
    $query = $context['results']['data']['list'][$context['sandbox']['progress']];
    db_query($query['query']);
    //======== fill blank data in agglo table base on geo data
    $context['sandbox']['progress']++;
    $context['message'] = '<h3>Fill blank NUTS data in agglo table base on geo data : '.$query['cc'].' - '.$query['report'] .'</h3>';
    
    //Condition d'arret
    if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
        $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
    } 
}

function uwwtd_sync_fill_blank_data_rbd_batch($ccs, $report, $force_geo, &$context){
    if (!isset($context['sandbox']['progress'])) {

            //manage version of RBD
        $context['results']['data']['list'] = array();
        foreach($ccs as $cc){
            if($report=='10th'){
                $context['results']['data']['list'][] = array(
                    'query'=>"
                        UPDATE harvest.eu_".$report."_agglomeration_all SET rbdcode = rbd_v2016.thematicid
                        FROM data.rbd_v2016
                        WHERE ".($force_geo==1?'':"(thematicid IS NULL OR thematicid='Array') AND ")."
                            eu_".$report."_agglomeration_all.cc = '".$cc."' AND rbd_v2016.country = '".strtoupper($cc)."' 
                            AND wkb_geometry && rbd_v2016.geom
                            AND st_intersects(wkb_geometry,rbd_v2016.geom)
                    ",
                    'report'=>$report,
                    'cc'=>$cc
                );
            }else{
                $context['results']['data']['list'][] = array(
                    'query'=>"
                        UPDATE harvest.eu_".$report."_agglomeration_all SET rbdcode = rbd.eurbdcode
                        FROM data.rbd
                        WHERE ".($force_geo==1?'':"(rbdcode IS NULL OR rbdcode='Array') AND ")." 
                            eu_".$report."_agglomeration_all.cc = '".$cc."' AND rbd.c_cd = '".strtoupper($cc)."'
                            AND wkb_geometry && rbd.geom4258 
                            AND st_intersects(wkb_geometry,rbd.geom4258)
                    ",
                    'report'=>$report,
                    'cc'=>$cc
                );
            }
        }
        
        $context['sandbox']['max'] = count($context['results']['data']['list']);
        $context['sandbox']['progress']=0;
    }
    
    $query = $context['results']['data']['list'][$context['sandbox']['progress']];
    db_query($query['query']);
    //======== fill blank data in agglo table base on geo data
    $context['sandbox']['progress']++;
    $context['message'] = '<h3>Fill blank RBD data in agglo table base on geo data: '.$query['cc'].' - '.$query['report'] .'</h3>';
    
    //Condition d'arret
    if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
        $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
    } 
}
function uwwtd_sync_calculate_stats_batch($report, &$context){
    if (!isset($context['sandbox']['progress'])) {

        $context['results']['data']['calcul'] = array();
        
        //--Article 3
        //        -- nat
        $context['results']['data']['calcul'][] = "drop table if exists calcul.cc_art3_".$report;
        $context['results']['data']['calcul'][] = "
            SELECT cc as cc, aticle3compliance as art3, SUM(generatedload) as generatedload, SUM(dtt3) as dtt3
            INTO calcul.cc_art3_".$report."
            FROM harvest.eu_".$report."_agglomeration_all
            WHERE aggstate = '1' 
                AND generatedload >= 2000
                AND aticle3compliance !='?'
            GROUP BY cc, aticle3compliance
            ORDER BY cc, aticle3compliance;
        ";
                
        //        -- nuts 2
        $context['results']['data']['calcul'][] = "drop table if exists calcul.nuts2_art3_".$report;
        $context['results']['data']['calcul'][] = "
            SELECT nust2code as nuts2, aticle3compliance as art3, SUM(generatedload) as generatedload, SUM(dtt3) as dtt3
            INTO calcul.nuts2_art3_".$report."
            FROM harvest.eu_".$report."_agglomeration_all
            WHERE aggstate = '1' 
                AND generatedload >= 2000
                AND aticle3compliance !='?'
            GROUP BY nust2code, aticle3compliance
            ORDER BY nust2code, aticle3compliance;
        ";        
        //        -- rbd
        $context['results']['data']['calcul'][] = "drop table if exists calcul.rbd_art3_".$report;
        $context['results']['data']['calcul'][] = "
            SELECT rbdcode as rbd, aticle3compliance as art3, SUM(generatedload) as generatedload, SUM(dtt3) as dtt3
            INTO calcul.rbd_art3_".$report."
            FROM harvest.eu_".$report."_agglomeration_all
            WHERE aggstate = '1' 
                AND generatedload >= 2000
                AND aticle3compliance !='?'
            GROUP BY rbdcode, aticle3compliance
            ORDER BY rbdcode, aticle3compliance;
        ";
        //    --Article 4
        //        -- nat
        $context['results']['data']['calcul'][] = "drop table if exists calcul.cc_art4_".$report;
        $context['results']['data']['calcul'][] = "
            SELECT cc as cc, article4compliance as art4, SUM(connectedload) as connectedload, SUM(dtt4t) as dtt4t, SUM(dtt4p) as dtt4p 	
                INTO calcul.cc_art4_".$report."
                FROM harvest.eu_".$report."_agglomeration_all
                WHERE aggstate = '1' 
                    AND generatedload >= 2000
                    AND article4compliance !='?'
                GROUP BY cc, article4compliance
                ORDER BY cc, article4compliance;
        ";
        // nd@oieau.fr , 02/12/2019 
        //SPecial case for CY on 10th report, we have to add the DTT of art3 in DTT of art 4 (target & subjected load)
        if($report == '10th'){
            $context['results']['data']['calcul'][] = "
                UPDATE calcul.cc_art4_10th 
                SET
                    connectedload = connectedload + cc_art3_10th.dtt3,
                    dtt4t = dtt4t + cc_art3_10th.dtt3,
                    dtt4p = dtt4p + cc_art3_10th.dtt3
                FROM calcul.cc_art3_10th 
                WHERE cc_art4_10th.cc='cy' 
                    AND cc_art4_10th.art4='NC'
                    AND cc_art4_10th.cc = cc_art3_10th.cc
                    AND cc_art4_10th.art4=cc_art3_10th.art3;
            ";
        }
        
        //        -- nuts 2
        $context['results']['data']['calcul'][] = "drop table if exists calcul.nuts2_art4_".$report;
        $context['results']['data']['calcul'][] = "
            SELECT nust2code as nuts2, article4compliance as art4, SUM(connectedload) as connectedload, SUM(dtt4t) as dtt4t, SUM(dtt4p) as dtt4p 
            INTO calcul.nuts2_art4_".$report."
            FROM harvest.eu_".$report."_agglomeration_all
            WHERE aggstate = '1' 
                AND generatedload >= 2000
                AND article4compliance !='?'
            GROUP BY nust2code, article4compliance
            ORDER BY nust2code, article4compliance;
        ";
        //        -- rbd
        $context['results']['data']['calcul'][] = "drop table if exists calcul.rbd_art4_".$report;
        $context['results']['data']['calcul'][] = "
            SELECT rbdcode as rbd, article4compliance as art4, SUM(connectedload) as connectedload, SUM(dtt4t) as dtt4t, SUM(dtt4p) as dtt4p 
                INTO calcul.rbd_art4_".$report."
                FROM harvest.eu_".$report."_agglomeration_all
                WHERE aggstate = '1' 
                    AND generatedload >= 2000
                    AND article4compliance !='?'
                GROUP BY rbdcode, article4compliance
                ORDER BY rbdcode, article4compliance;
         ";       
        //    --Article 5
        //=============================================== FIX ME : nd@oieau.fr : 22/02/2019
        // If the RCA is under article 5.4, the compliance must be NR at Agglomeration level, and the compliance is define at RCA level
        //        -- nat
        $context['results']['data']['calcul'][] = "drop table if exists calcul.cc_art5_".$report;
        $context['results']['data']['calcul'][] = "
            SELECT cc as cc, article5compliance as art5, SUM(connectedload) as connectedload, SUM(dtt5t) as dtt5t, SUM(dtt5p) as dtt5p 
            INTO calcul.cc_art5_".$report."
            FROM harvest.eu_".$report."_agglomeration_all
            WHERE aggstate = '1' 
                AND generatedload >= 2000
                AND article5compliance !='?'
            GROUP BY cc, article5compliance
            ORDER BY cc, article5compliance;
        ";
        //        -- nuts 2
        $context['results']['data']['calcul'][] = "drop table if exists calcul.nuts2_art5_".$report;
        $context['results']['data']['calcul'][] = "
            SELECT nust2code as nuts2, article5compliance as art5, SUM(connectedload) as connectedload, SUM(dtt5t) as dtt5t, SUM(dtt5p) as dtt5p 
            INTO calcul.nuts2_art5_".$report."
            FROM harvest.eu_".$report."_agglomeration_all
            WHERE aggstate = '1' 
                AND generatedload >= 2000
                AND article5compliance !='?'
            GROUP BY nust2code, article5compliance
            ORDER BY nust2code, article5compliance;
        ";
        //        -- rbd
        $context['results']['data']['calcul'][] = "drop table if exists calcul.rbd_art5_".$report;
        $context['results']['data']['calcul'][] = "
            SELECT rbdcode as rbd, article5compliance as art5, SUM(connectedload) as connectedload, SUM(dtt5t) as dtt5t, SUM(dtt5p) as dtt5p 
            INTO calcul.rbd_art5_".$report."
            FROM harvest.eu_".$report."_agglomeration_all
            WHERE aggstate = '1' 
                AND generatedload >= 2000
                AND article5compliance !='?'
            GROUP BY rbdcode, article5compliance
            ORDER BY rbdcode, article5compliance; 
        ";
        //    --Article 6
        //        -- nat
        $context['results']['data']['calcul'][] = "drop table if exists calcul.cc_art6_".$report;
        $context['results']['data']['calcul'][] = "
            SELECT cc as cc, article6compliance as art6, SUM(connectedload) as connectedload
            INTO calcul.cc_art6_".$report."
            FROM harvest.eu_".$report."_agglomeration_all
            WHERE aggstate = '1' 
                AND generatedload >= 2000
                AND article6compliance !='?'
            GROUP BY cc, article6compliance
            ORDER BY cc, article6compliance;
        ";
        //        -- nuts 2
        $context['results']['data']['calcul'][] = "drop table if exists calcul.nuts2_art6_".$report;
        $context['results']['data']['calcul'][] = "
            SELECT nust2code as nuts2, article6compliance as art6, SUM(connectedload) as connectedload
            INTO calcul.nuts2_art6_".$report."
            FROM harvest.eu_".$report."_agglomeration_all
            WHERE aggstate = '1' 
                AND generatedload >= 2000
                AND article6compliance !='?'
            GROUP BY nust2code, article6compliance
            ORDER BY nust2code, article6compliance;
        ";

        
        //        -- rbd
        $context['results']['data']['calcul'][] = "drop table if exists calcul.rbd_art6_".$report;
        $context['results']['data']['calcul'][] = "
            SELECT rbdcode as rbd, article6compliance as art6, SUM(connectedload) as connectedload
            INTO calcul.rbd_art6_".$report."
            FROM harvest.eu_".$report."_agglomeration_all
            WHERE aggstate = '1' 
                AND generatedload >= 2000
                AND article6compliance !='?'
            GROUP BY rbdcode, article6compliance
            ORDER BY rbdcode, article6compliance ;
        ";      
  
        //    --Global compliance
        //        -- nat
        $context['results']['data']['calcul'][] = "drop table if exists calcul.cc_compliance_".$report;
        $context['results']['data']['calcul'][] = "
            SELECT cc as cc, globalcompliance as compliance, SUM(generatedload) as generatedload
            INTO calcul.cc_compliance_".$report."
            FROM harvest.eu_".$report."_agglomeration_all
            WHERE aggstate = '1' 
                AND generatedload >= 2000
                AND globalcompliance !='?'
            GROUP BY cc, globalcompliance
            ORDER BY cc, globalcompliance;
        ";
        //        -- nuts 2
        $context['results']['data']['calcul'][] = "drop table if exists calcul.nuts2_compliance_".$report;
        $context['results']['data']['calcul'][] = "
            SELECT nust2code as nuts2, globalcompliance as compliance, SUM(generatedload) as generatedload
            INTO calcul.nuts2_compliance_".$report."
            FROM harvest.eu_".$report."_agglomeration_all
            WHERE aggstate = '1' 
                AND generatedload >= 2000
                AND globalcompliance !='?'
            GROUP BY nust2code, globalcompliance
            ORDER BY nust2code, globalcompliance;
        ";
        //        -- rbd
        $context['results']['data']['calcul'][] = "drop table if exists calcul.rbd_compliance_".$report;
        $context['results']['data']['calcul'][] = "
            SELECT rbdcode as rbd, globalcompliance as compliance, SUM(generatedload) as generatedload
            INTO calcul.rbd_compliance_".$report."
            FROM harvest.eu_".$report."_agglomeration_all
            WHERE aggstate = '1' 
                AND generatedload >= 2000
                AND globalcompliance !='?'
            GROUP BY rbdcode, globalcompliance
            ORDER BY rbdcode, globalcompliance; 
        ";
        //    -- Main tables 
        //        -- cc
        $context['results']['data']['calcul'][] = "drop table if exists calcul.cc_stat_art_".$report;
        $context['results']['data']['calcul'][] = "
            WITH art3 AS(
                    SELECT cc, 
                        SUM(generatedload) as generatedload,
                        SUM(CASE WHEN art3 IN ('NR','PD') THEN 0 ELSE generatedload END) as art3_target,
                        SUM(CASE WHEN art3 IN ('C', 'QC') THEN generatedload ELSE 0 END) as art3_compliant,
                        SUM(CASE WHEN art3 = 'PD' THEN dtt3 ELSE 0 END) as dtt3_pd,
                        SUM(CASE WHEN art3 = 'NC' THEN dtt3 ELSE 0 END) as dtt3_exp
                    FROM calcul.cc_art3_".$report."
                    GROUP BY cc
                ),
                art4 AS(
                    SELECT cc, 
                        SUM(connectedload) as connectedload,
                        SUM(CASE WHEN art4 IN ('NR','PD') THEN 0 ELSE connectedload END) as art4_target,
                        SUM(CASE WHEN art4 = 'C' THEN connectedload ELSE 0 END) as art4_compliant,
                        SUM(CASE WHEN art4 IN ('NR','PD') THEN 0 ELSE dtt4p END) as dtt4p_pd,
                        SUM(CASE WHEN art4 = 'NC' THEN dtt4p ELSE 0 END) as dtt4p_exp,
                        SUM(CASE WHEN art4 IN ('NR','PD') THEN 0 ELSE dtt4t END) as dtt4t_pd,
                        SUM(CASE WHEN art4 = 'NC' THEN dtt4t ELSE 0 END) as dtt4t_exp
                    FROM calcul.cc_art4_".$report."
                    GROUP BY cc
                ),
                art5 AS(
                    SELECT cc, 
                        SUM(connectedload) as connectedload,
                        SUM(CASE WHEN art5 IN ('NR','PD') THEN 0 ELSE connectedload END) as art5_target,
                        SUM(CASE WHEN art5 = 'C' THEN connectedload ELSE 0 END) as art5_compliant,
                        SUM(CASE WHEN art5 IN ('NR','PD') THEN dtt5p ELSE 0 END) as dtt5p_pd,
                        SUM(CASE WHEN art5 = 'NC' THEN dtt5p ELSE 0 END) as dtt5p_exp,
                        SUM(CASE WHEN art5 IN ('NR','PD') THEN dtt5t ELSE 0 END) as dtt5t_pd,
                        SUM(CASE WHEN art5 = 'NC' THEN dtt5t ELSE 0 END) as dtt5t_exp 
                    FROM calcul.cc_art5_".$report."
                    GROUP BY cc
                ),
                art6 AS(
                    SELECT cc, 
                        SUM(connectedload) as connectedload,
                        SUM(CASE WHEN art6 IN ('NR','PD') THEN 0 ELSE connectedload END) as art6_target,
                        SUM(CASE WHEN art6 = 'C' THEN connectedload ELSE 0 END) as art6_compliant 
                    FROM calcul.cc_art6_".$report."
                    GROUP BY cc
                ),
                gp AS(
                    SELECT cc, 
                        SUM(generatedload) as generatedload,
                        SUM(CASE WHEN compliance IN ('NR','PD') THEN 0 ELSE generatedload END) as compliance_target,
                        SUM(CASE WHEN compliance = 'C' THEN generatedload ELSE 0 END) as compliance_compliant 
                    FROM calcul.cc_compliance_".$report."
                    GROUP BY cc
                )
                SELECT gp.cc, gp.generatedload, art4.connectedload,
                    gp.compliance_target, gp.compliance_compliant, 
                    art3.art3_target, art3.art3_compliant,
                    art4.art4_target, art4.art4_compliant,
                    art5.art5_target, art5.art5_compliant,
                    art6.art6_target, art6.art6_compliant,
                    art3.dtt3_pd,art3.dtt3_exp,
                    art4.dtt4t_pd,art4.dtt4t_exp,art4.dtt4p_pd,art4.dtt4p_exp,
                    art5.dtt5t_pd,art5.dtt5t_exp,art5.dtt5p_pd,art5.dtt5p_exp
                INTO calcul.cc_stat_art_".$report."
                FROM gp 
                    LEFT JOIN art3 ON gp.cc=art3.cc
                    LEFT JOIN art4 ON gp.cc=art4.cc
                    LEFT JOIN art5 ON gp.cc=art5.cc
                    LEFT JOIN art6 ON gp.cc=art6.cc
                ORDER BY gp.cc;    
        ";  
        
        // nd@oieau.fr , 02/12/2019 
        //SPecial case for IT on 10th report,
        // pour Italy il faudrait que la valeur target soit de 33,917,998 au lieu de 33 903 754 et la valeur Value de 3,262,803 au lieu de 890 852 
        //... oui, ce qui va suivre est très moche
        if($report == '10th'){
            $context['results']['data']['calcul'][] = "
                UPDATE calcul.cc_stat_art_10th
                SET 
                    art5_target = '33917998',
                    dtt5t_exp = '3262803'
                WHERE cc='it'
            ";
        }
        
        //        --nuts2
        $context['results']['data']['calcul'][] = "drop table if exists calcul.nuts2_stat_art_".$report;
        $context['results']['data']['calcul'][] = "
            WITH art3 AS(
                    SELECT nuts2, 
                        SUM(generatedload) as generatedload,
                        SUM(CASE WHEN art3 IN ('NR','PD') THEN 0 ELSE generatedload END) as art3_target,
                        SUM(CASE WHEN art3 IN ('C', 'QC') THEN generatedload ELSE 0 END) as art3_compliant,
                        SUM(CASE WHEN art3 = 'PD' THEN dtt3 ELSE 0 END) as dtt3_pd,
                        SUM(CASE WHEN art3 = 'NC' THEN dtt3 ELSE 0 END) as dtt3_exp 
                    FROM calcul.nuts2_art3_".$report."
                    GROUP BY nuts2
                ),
                art4 AS(
                    SELECT nuts2, 
                        SUM(connectedload) as connectedload,
                        SUM(CASE WHEN art4 IN ('NR','PD') THEN 0 ELSE connectedload END) as art4_target,
                        SUM(CASE WHEN art4 = 'C' THEN connectedload ELSE 0 END) as art4_compliant,
                        SUM(CASE WHEN art4 IN ('NR','PD') THEN 0 ELSE dtt4p END) as dtt4p_pd,
                        SUM(CASE WHEN art4 = 'NC' THEN dtt4p ELSE 0 END) as dtt4p_exp,
                        SUM(CASE WHEN art4 IN ('NR','PD') THEN 0 ELSE dtt4t END) as dtt4t_pd,
                        SUM(CASE WHEN art4 = 'NC' THEN dtt4t ELSE 0 END) as dtt4t_exp
                    FROM calcul.nuts2_art4_".$report."
                    GROUP BY nuts2
                ),
                art5 AS(
                    SELECT nuts2, 
                        SUM(connectedload) as connectedload,
                        SUM(CASE WHEN art5 IN ('NR','PD') THEN 0 ELSE connectedload END) as art5_target,
                        SUM(CASE WHEN art5 = 'C' THEN connectedload ELSE 0 END) as art5_compliant,
                        SUM(CASE WHEN art5 IN ('NR','PD') THEN dtt5p ELSE 0 END) as dtt5p_pd,
                        SUM(CASE WHEN art5 = 'NC' THEN dtt5p ELSE 0 END) as dtt5p_exp,
                        SUM(CASE WHEN art5 IN ('NR','PD') THEN dtt5t ELSE 0 END) as dtt5t_pd,
                        SUM(CASE WHEN art5 = 'NC' THEN dtt5t ELSE 0 END) as dtt5t_exp  
                    FROM calcul.nuts2_art5_".$report."
                    GROUP BY nuts2
                ),
                art6 AS(
                    SELECT nuts2, 
                        SUM(connectedload) as connectedload,
                        SUM(CASE WHEN art6 IN ('NR','PD') THEN 0 ELSE connectedload END) as art6_target,
                        SUM(CASE WHEN art6 = 'C' THEN connectedload ELSE 0 END) as art6_compliant 
                    FROM calcul.nuts2_art6_".$report."
                    GROUP BY nuts2
                ),
                gp AS(
                    SELECT nuts2, 
                        SUM(generatedload) as generatedload,
                        SUM(CASE WHEN compliance IN ('NR','PD') THEN 0 ELSE generatedload END) as compliance_target,
                        SUM(CASE WHEN compliance = 'C' THEN generatedload ELSE 0 END) as compliance_compliant 
                    FROM calcul.nuts2_compliance_".$report."
                    GROUP BY nuts2
                )
                SELECT gp.nuts2, gp.generatedload, art4.connectedload,
                    gp.compliance_target, gp.compliance_compliant, 
                    art3.art3_target, art3.art3_compliant,
                    art4.art4_target, art4.art4_compliant,
                    art5.art5_target, art5.art5_compliant,
                    art6.art6_target, art6.art6_compliant,
                    art3.dtt3_pd,art3.dtt3_exp,
                    art4.dtt4t_pd,art4.dtt4t_exp,art4.dtt4p_pd,art4.dtt4p_exp,
                    art5.dtt5t_pd,art5.dtt5t_exp,art5.dtt5p_pd,art5.dtt5p_exp
                INTO calcul.nuts2_stat_art_".$report."
                FROM gp 
                    LEFT JOIN art3 ON gp.nuts2=art3.nuts2
                    LEFT JOIN art4 ON gp.nuts2=art4.nuts2
                    LEFT JOIN art5 ON gp.nuts2=art5.nuts2
                    LEFT JOIN art6 ON gp.nuts2=art6.nuts2
                ORDER BY gp.nuts2; 
        ";
        //Case of Romania : compliance is calculated at MS Level => so nuts 2 is not relevant 
       //$context['results']['data']['calcul'][] = "UPDATE calcul.nuts2_stat_art_".$report." WHERE nuts2 LIKE 'RO%' ";   
                
        //        --rbd
        $context['results']['data']['calcul'][] = "drop table if exists calcul.rbd_stat_art_".$report;
        $context['results']['data']['calcul'][] = "
            WITH art3 AS(
                    SELECT rbd, 
                        SUM(generatedload) as generatedload,
                        SUM(CASE WHEN art3 IN ('NR','PD') THEN 0 ELSE generatedload END) as art3_target,
                        SUM(CASE WHEN art3 IN ('C', 'QC') THEN generatedload ELSE 0 END) as art3_compliant,
                        SUM(CASE WHEN art3 = 'PD' THEN dtt3 ELSE 0 END) as dtt3_pd,
                        SUM(CASE WHEN art3 = 'NC' THEN dtt3 ELSE 0 END) as dtt3_exp 
                    FROM calcul.rbd_art3_".$report."
                    GROUP BY rbd
                ),
                art4 AS(
                    SELECT rbd, 
                        SUM(connectedload) as connectedload,
                        SUM(CASE WHEN art4 IN ('NR','PD') THEN 0 ELSE connectedload END) as art4_target,
                        SUM(CASE WHEN art4 = 'C' THEN connectedload ELSE 0 END) as art4_compliant,
                        SUM(CASE WHEN art4 IN ('NR','PD') THEN 0 ELSE dtt4p END) as dtt4p_pd,
                        SUM(CASE WHEN art4 = 'NC' THEN dtt4p ELSE 0 END) as dtt4p_exp,
                        SUM(CASE WHEN art4 IN ('NR','PD') THEN 0 ELSE dtt4t END) as dtt4t_pd,
                        SUM(CASE WHEN art4 = 'NC' THEN dtt4t ELSE 0 END) as dtt4t_exp
                    FROM calcul.rbd_art4_".$report."
                    GROUP BY rbd
                ),
                art5 AS(
                    SELECT rbd, 
                        SUM(connectedload) as connectedload,
                        SUM(CASE WHEN art5 IN ('NR','PD') THEN 0 ELSE connectedload END) as art5_target,
                        SUM(CASE WHEN art5 = 'C' THEN connectedload ELSE 0 END) as art5_compliant,
                        SUM(CASE WHEN art5 IN ('NR','PD') THEN dtt5p ELSE 0 END) as dtt5p_pd,
                        SUM(CASE WHEN art5 = 'NC' THEN dtt5p ELSE 0 END) as dtt5p_exp,
                        SUM(CASE WHEN art5 IN ('NR','PD') THEN dtt5t ELSE 0 END) as dtt5t_pd,
                        SUM(CASE WHEN art5 = 'NC' THEN dtt5t ELSE 0 END) as dtt5t_exp 
                    FROM calcul.rbd_art5_".$report."
                    GROUP BY rbd
                ),
                art6 AS(
                    SELECT rbd, 
                        SUM(connectedload) as connectedload,
                        SUM(CASE WHEN art6 IN ('NR','PD') THEN 0 ELSE connectedload END) as art6_target,
                        SUM(CASE WHEN art6 = 'C' THEN connectedload ELSE 0 END) as art6_compliant 
                    FROM calcul.rbd_art6_".$report."
                    GROUP BY rbd
                ),
                gp AS(
                    SELECT rbd, 
                        SUM(generatedload) as generatedload,
                        SUM(CASE WHEN compliance IN ('NR','PD') THEN 0 ELSE generatedload END) as compliance_target,
                        SUM(CASE WHEN compliance = 'C' THEN generatedload ELSE 0 END) as compliance_compliant 
                    FROM calcul.rbd_compliance_".$report."
                    GROUP BY rbd
                )
                SELECT gp.rbd, gp.generatedload, art4.connectedload,
                    gp.compliance_target, gp.compliance_compliant, 
                    art3.art3_target, art3.art3_compliant,
                    art4.art4_target, art4.art4_compliant,
                    art5.art5_target, art5.art5_compliant,
                    art6.art6_target, art6.art6_compliant,
                    art3.dtt3_pd,art3.dtt3_exp,
                    art4.dtt4t_pd,art4.dtt4t_exp,art4.dtt4p_pd,art4.dtt4p_exp,
                    art5.dtt5t_pd,art5.dtt5t_exp,art5.dtt5p_pd,art5.dtt5p_exp
                INTO calcul.rbd_stat_art_".$report."
                FROM gp 
                    LEFT JOIN art3 ON gp.rbd=art3.rbd
                    LEFT JOIN art4 ON gp.rbd=art4.rbd
                    LEFT JOIN art5 ON gp.rbd=art5.rbd
                    LEFT JOIN art6 ON gp.rbd=art6.rbd
                ORDER BY gp.rbd; 
            ";

                
            //-- Stat by size : [2 000-10 000[ | [10 000-100 000[ | [100 000 - inf]
            $context['results']['data']['calcul'][] = "drop table if exists calcul.cc_stat_by_size_".$report;
            $context['results']['data']['calcul'][] = "
                SELECT cc, 
                    SUM(CASE WHEN generatedload <= 10000 THEN 1 ELSE 0 END) number_2000_10000,
                    SUM(CASE WHEN generatedload > 10000 AND generatedload<= 100000 THEN 1 ELSE 0 END) number_10000_100000,
                    SUM(CASE WHEN generatedload > 100000 THEN 1 ELSE 0 END) number_more_100000,
                    SUM(CASE WHEN generatedload <= 10000 THEN generatedload ELSE 0 END) load_2000_10000,
                    SUM(CASE WHEN generatedload > 10000 AND generatedload <= 100000 THEN generatedload ELSE 0 END) load_100000,
                    SUM(CASE WHEN generatedload < 100000 THEN generatedload ELSE 0 END) load_more_100000
                INTO calcul.cc_stat_by_size_".$report."
                FROM harvest.eu_".$report."_agglomeration_all
                WHERE aggstate = '1' 
                    AND generatedload >= 2000
                GROUP BY cc
                ORDER BY cc;
            ";
            //-- Stat by size : [2 000-10 000[ & [10 000-15 000[ & [15 000 - 100 000[ & [100 000 - 150 000[ & [150 000 - inf[
            $context['results']['data']['calcul'][] = "drop table if exists calcul.cc_stat_by_size_5_class_".$report;
            $context['results']['data']['calcul'][] = "
                SELECT cc, 
                    SUM(CASE WHEN generatedload <= 10000 THEN 1 ELSE 0 END) number_2000_10000,
                    SUM(CASE WHEN generatedload > 10000 AND generatedload<= 15000 THEN 1 ELSE 0 END) number_10000_15000,
                    SUM(CASE WHEN generatedload > 15000  AND generatedload<= 100000 THEN 1 ELSE 0 END) number_15000_100000,
                    SUM(CASE WHEN generatedload > 100000  AND generatedload<= 150000 THEN 1 ELSE 0 END) number_100000_150000,
                    SUM(CASE WHEN generatedload > 150000  THEN 1 ELSE 0 END) number_more_150000,
                    SUM(CASE WHEN generatedload <= 10000 THEN generatedload ELSE 0 END) load_2000_10000,
                    SUM(CASE WHEN generatedload > 10000 AND generatedload<= 15000 THEN generatedload ELSE 0 END) load_10000_15000,
                    SUM(CASE WHEN generatedload > 15000  AND generatedload<= 100000 THEN generatedload ELSE 0 END) load_15000_100000,
                    SUM(CASE WHEN generatedload > 100000  AND generatedload<= 150000 THEN generatedload ELSE 0 END) load_100000_150000,
                    SUM(CASE WHEN generatedload > 150000  THEN generatedload ELSE 0 END) load_more_150000
                INTO calcul.cc_stat_by_size_5_class_".$report."
                FROM harvest.eu_".$report."_agglomeration_all
                WHERE aggstate = '1' 
                    AND generatedload >= 2000
                GROUP BY cc
                ORDER BY cc;
            ";
        $context['results']['data']['calcul'][] = "drop table if exists calcul.uwwtp_stats_".$report;
        $context['results']['data']['calcul'][] = "
            SELECT cc, count(*) as nb, sum(uwwloadenteringuwwtp) loadentering, sum(uwwcapacity) as capacity
            INTO calcul.uwwtp_stats_".$report."
            FROM harvest.eu_".$report."_uwwtp 
            WHERE  	uwwstate = '1' 
                AND uwwcollectingsystem ='ISCON'
            group by cc 
            order by cc;
         ";   
            
        $context['sandbox']['max'] = count($context['results']['data']['calcul']);
        $context['sandbox']['progress']=0;
    }
    
    $query = $context['results']['data']['calcul'][$context['sandbox']['progress']];
    db_query($query);
    //======== fill blank data in agglo table base on geo data
    $context['sandbox']['progress']++;
    $context['message'] = '<h3>Create "calcul tables"</h3>';
    //Condition d'arret
    if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
        $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
    } 
}

//Fonction de fin de process
function uwwtd_sync_harvest_finish($success, $results, $operations){
  if ($success) {
  // Here we do something meaningful with the results.
    //$message = t('@count items successfully processed:', array('@count' => count($results['log'])));
    //$message .= theme('item_list', array('items' => $results['log']));
    //drupal_set_message($message);     
    
    drupal_set_message("uwwtd_sync_harvest_finish");
    
  }
  else {
  // An error occurred.
  // $operations contains the operations that remained unprocessed.
    $error_operation = reset($operations);
    $message = t('An error occurred while processing %error_operation with arguments: @arguments', array('%error_operation' => $error_operation[0], '@arguments' => print_r($error_operation[1], TRUE)));
    drupal_set_message($message, 'error');
  }
}


//A usefull function for dev & debug
function uwwtd_sync_debug(){
    
    return "see you later !!! ";
    
    $ccs = array_keys($GLOBALS['uwwtd_sync_conf']['country']);
    
    //==> Note : 25/01/2017 PL doesn't work => no available data
    //if(true){
    if(false){
        //=========== 1. bulk load of WFS data foreach country in database 
        //dsm(uwwtd_sync_harvest('it', '9th'));
        
        foreach($ccs as $cc){
                $out[$cc] = uwwtd_sync_harvest_agg($cc, '9th');
        }
        
        //dsm($out);
        
        //=========== 2. Aggregate MS Level  => harvest.eu_9th_mslevel
        
        foreach($ccs as $cc){
            $out[$cc] = uwwtd_sync_aggregate_mslevel($cc, '9th');
        }
        
        //=========== 3. Aggregate Agglo  => harvest.eu_9th_agglomeration_all
        
        foreach($ccs as $cc){
            $out[$cc] = uwwtd_sync_aggregate_agglo($cc, '9th');
        }
    }
    
    //======== fill blank data in agglo table base on geo data
    if(false){
    //if(true){
        //NUTS 1
        db_query("
            UPDATE harvest.eu_9th_agglomeration_all SET nust1code = nuts_1.nuts_id
            FROM data.nuts_1
            WHERE wkb_geometry && nuts_1.geom 
                AND st_intersects(wkb_geometry,nuts_1.geom);
        ");
        
        //NUTS 2
        
        db_query("
            UPDATE harvest.eu_9th_agglomeration_all SET nust2code = nuts_2.nuts_id
            FROM data.nuts_2
            WHERE wkb_geometry && nuts_2.geom 
                AND st_intersects(wkb_geometry,nuts_2.geom);
        ");
        
        
        //NUTS 3
        
        db_query("
            UPDATE harvest.eu_9th_agglomeration_all SET nust3code = nuts_3.nuts_id
            FROM data.nuts_3
            WHERE wkb_geometry && nuts_3.geom 
                AND st_intersects(wkb_geometry,nuts_3.geom)
        ");
    }
    //RBD
    //if(false){
    if(false){
        db_query("
            UPDATE harvest.eu_9th_agglomeration_all SET rbdcode = rbd.eurbdcode
            FROM data.rbd
            WHERE (rbdcode IS NULL OR rbdcode='Array')
                AND wkb_geometry && rbd.geom4258 
                AND st_intersects(wkb_geometry,rbd.geom4258)
        ");
    }
    return 'debug';
}


function uwwtd_sync_aggregate_agglo($cc, $report = '9th'){
    
    db_query("
        CREATE TABLE IF NOT EXISTS  harvest.".$cc."_".$report."_agglomeration (
            ogc_fid integer NOT NULL,
            gml_id character varying NOT NULL,
            aggcode character varying,
            repcode character varying,
            aggname character varying,
            aggstate character varying,
            aggnuts character varying,
            agglatitude double precision,
            agglongitude double precision,
            agggenerated integer,
            bigid character varying,
            aggcalculation character varying,
            aggchanges character varying,
            aggchangescomment character varying,
            aggperiodover3 character varying,
            aggperiodover4 character varying,
            aggperiodover5 character varying,
            aggperiodover6 character varying,
            aggc1 double precision,
            aggmethodc1 character varying,
            aggc2 double precision,
            aggmethodc2 character varying,
            aggpercwithouttreatment double precision,
            aggmethodwithouttreatment character varying,
            aggpercprimtreatment double precision,
            aggpercsectreatment double precision,
            aggperstringenttreatment double precision,
            aggsewagenetwork character varying,
            aggbesttechnicalknowledge character varying,
            aggseweroverflows_m3 integer,
            aggseweroverflows_pe integer,
            aggremarks character varying,
            agghaveregistrationsystem character varying,
            aggexistmaintenanceplan character varying,
            aggexplanationother character varying,
            agginhabitants integer,
            aggforecast character varying,
            aggaccoverflownumber integer,
            aggdilutionrates integer,
            aggaccoverflows integer,
            aggothermeasures integer,
            aggpressuretest integer,
            aggvideoinspections integer,
            dtt3 integer,
            dtt4t integer,
            dtt4p integer,
            dtt5t integer,
            dtt5p integer,
            repreportedperdiod character varying,
            wkb_geometry public.geometry(Geometry,4258)
        );
    ");
    
    db_query("
        CREATE TABLE IF NOT EXISTS  harvest.eu_".$report."_agglomeration_all (
            cc character(2),
            aggcode character varying,
            repcode character varying,
            aggname character varying,
            aggstate character varying,
            rbdcode character varying,
            nutscode character varying,
            nust1code character varying,
            nust2code character varying,
            nust3code character varying,
            bigcitycode character varying,
            generatedload integer,
            aggcalculation character varying,
            aggc1 double precision,
            aggmethodc1 character varying,
            aggc2 double precision,
            aggmethodc2 character varying,
            aggpercwithouttreatment double precision,
            aggmethodwithouttreatment character varying,
            aggpercprimtreatment double precision,
            aggpercsectreatment double precision,
            aggperstringenttreatment double precision,
            aggsewagenetwork character varying,
            aggbesttechnicalknowledge character varying,
            aggseweroverflows_m3 integer,
            aggseweroverflows_pe integer,
            agghaveregistrationsystem character varying,
            aggexistmaintenanceplan character varying,
            aggexplanationother character varying,
            agginhabitants integer,
            aggforecast character varying,
            aggaccoverflownumber integer,
            aggdilutionrates integer,
            aggaccoverflows integer,
            aggothermeasures integer,
            aggpressuretest integer,
            aggvideoinspections integer,
            connectedload integer,
            iasload integer,
            dischargewithouttreatment integer,
            aticle3compliance character varying,
            article4compliance character varying,
            article5compliance character varying,
            article6compliance character varying,
            globalcompliance character varying,
            typeofsensitivearea character varying,
            articleapplied character varying,
            secondaryequipementinplace integer,
            secondaryperformanceok integer,
            morestringentequipmentmet integer,
            morestringentperformancemet integer,
            morestringentequipmentinplance integer,
            morestringentperformanceok integer,
            bigcitynotreatmentperc double precision,
            bigcityprimaryperc double precision,
            bigcitysecondayperc double precision,
            bigcitymorestringentnandpperc double precision,
            bigcitymorestringentotherperc double precision,
            aggchanges character varying,
            aggchangescomment character varying,
            aggremarks character varying,
            aggperiodover3 character varying,
            aggperiodover4 character varying,
            aggperiodover5 character varying,
            aggperiodover6 character varying,
            dtt3 integer,
            dtt4t integer,
            dtt4p integer,
            dtt5t integer,
            dtt5p integer,
            repreportedperdiod character varying,
            changed integer,
            wkb_geometry public.geometry(Geometry,4258)
        );
    ");
    db_query("
        CREATE TABLE IF NOT EXISTS harvest.".$cc."_".$report."_feedagglolevel (
            ogc_fid integer NOT NULL,
            gml_id character varying NOT NULL,
            repcode character varying,
            repreportedperdiod character varying,
            agglomerationcode character varying,
            agglomerationname character varying,
            status character varying,
            nutscode character varying,
            nust1code character varying,
            nust2code character varying,
            nust3code character varying,
            bigcitycode character varying,
            generatedload integer,
            connectedload integer,
            iasload integer,
            dischargewithouttreatment integer,
            aticle3compliance character varying,
            article4compliance character varying,
            article5compliance character varying,
            article6compliance character varying,
            globalcompliance character varying,
            typeofsensitivearea character varying,
            articleapplied character varying,
            rbdcode character varying,
            secondaryequipementinplace integer,
            secondaryperformanceok integer,
            morestringentequipmentmet integer,
            morestringentperformancemet integer,
            morestringentequipmentinplance integer,
            morestringentperformanceok integer,
            bigcitynotreatmentperc double precision,
            bigcityprimaryperc double precision,
            bigcitysecondayperc double precision,
            bigcitymorestringentnandpperc double precision,
            bigcitymorestringentotherperc double precision,
            changed integer
        );

    ");
    //
    
    
    //Delete old data 
    db_query("DELETE FROM harvest.eu_".$report."_agglomeration_all WHERE cc = :cc", array(':cc'=>$cc));
    
    //INSERT Data in the global table
    db_query("
    INSERT INTO harvest.eu_".$report."_agglomeration_all (cc, aggcode, repcode, aggname, aggstate, rbdcode, nutscode, nust1code, nust2code, nust3code, bigcitycode, generatedload, aggcalculation, aggc1, aggmethodc1, aggc2, aggmethodc2, aggpercwithouttreatment, aggmethodwithouttreatment, aggpercprimtreatment, aggpercsectreatment, aggperstringenttreatment, aggsewagenetwork, aggbesttechnicalknowledge, aggseweroverflows_m3, aggseweroverflows_pe, agghaveregistrationsystem, aggexistmaintenanceplan, aggexplanationother, agginhabitants, aggforecast, aggaccoverflownumber, aggdilutionrates, aggaccoverflows, aggothermeasures, aggpressuretest, aggvideoinspections, connectedload, iasload, dischargewithouttreatment, aticle3compliance, article4compliance, article5compliance, article6compliance, globalcompliance, typeofsensitivearea, articleapplied, secondaryequipementinplace, secondaryperformanceok, morestringentequipmentmet, morestringentperformancemet, morestringentequipmentinplance, morestringentperformanceok, bigcitynotreatmentperc, bigcityprimaryperc, bigcitysecondayperc, bigcitymorestringentnandpperc, bigcitymorestringentotherperc, aggchanges, aggchangescomment, aggremarks, aggperiodover3, aggperiodover4, aggperiodover5, aggperiodover6, dtt3,dtt4t,dtt4p,dtt5t,dtt5p,repreportedperdiod, changed, wkb_geometry)
    SELECT '".$cc."' as cc,
        a.aggcode, a.repcode, a.aggname, a.aggstate,
        c.rbdcode,
        c.nutscode, c.nust1code, c.nust2code, c.nust3code, c.bigcitycode, 
        c.generatedload, a.aggcalculation,    
        a.aggc1, a.aggmethodc1, a.aggc2, a.aggmethodc2, a.aggpercwithouttreatment, a.aggmethodwithouttreatment, a.aggpercprimtreatment, a.aggpercsectreatment, a.aggperstringenttreatment, a.aggsewagenetwork, a.aggbesttechnicalknowledge, a.aggseweroverflows_m3, a.aggseweroverflows_pe, a.agghaveregistrationsystem, a.aggexistmaintenanceplan, a.aggexplanationother, a.agginhabitants, a.aggforecast, a.aggaccoverflownumber, a.aggdilutionrates, a.aggaccoverflows, a.aggothermeasures, a.aggpressuretest, a.aggvideoinspections,
        c.connectedload, c.iasload, c.dischargewithouttreatment, c.aticle3compliance, c.article4compliance, c.article5compliance, c.article6compliance, c.globalcompliance, c.typeofsensitivearea, c.articleapplied, c.secondaryequipementinplace, c.secondaryperformanceok, c.morestringentequipmentmet, c.morestringentperformancemet, morestringentequipmentinplance, morestringentperformanceok, c.bigcitynotreatmentperc, c.bigcityprimaryperc, c.bigcitysecondayperc, c.bigcitymorestringentnandpperc, c.bigcitymorestringentotherperc,
        a.aggchanges, a.aggchangescomment, a.aggremarks,
        a.aggperiodover3, a.aggperiodover4, a.aggperiodover5, a.aggperiodover6,
        a.dtt3,a.dtt4t,a.dtt4p,a.dtt5t,a.dtt5p,
        a.repreportedperdiod,
        ".time().",
        a.wkb_geometry
    
    FROM harvest.".$cc."_".$report."_agglomeration a JOIN harvest.".$cc."_".$report."_feedagglolevel c ON a.aggcode=c.agglomerationcode
    ");
    //c.changed --> doesn't work for ee
    
    
}

function uwwtd_sync_aggregate_mslevel($cc, $report = '9th'){
    db_query("
        CREATE TABLE IF NOT EXISTS harvest.eu_".$report."_mslevel (
            cc character(2),
            gml_id character varying,
            repcode character varying,
            repreportedperdiod character varying,
            mslsludgeproduction real,
            mslreusesoilagriculture real,
            mslreuseothers real,
            msldisposalothers real,
            msldisposalincineration real,
            msldisposallandfill real
        );
    ");
    db_query("
        CREATE TABLE IF NOT EXISTS harvest.".$cc."_".$report."_mslevel (
            gml_id character varying,
            repcode character varying,
            repreportedperdiod character varying,
            mslsludgeproduction real,
            mslreusesoilagriculture real,
            mslreuseothers real,
            msldisposalothers real,
            msldisposalincineration real,
            msldisposallandfill real
        );
    ");
    
    //Delete old data 
    db_query("DELETE FROM harvest.eu_".$report."_mslevel WHERE cc = :cc", array(':cc'=>$cc));
    //INSERT NEW ONES in the aggregated table
    
    //INSERT Data in the global table
    db_query("
        INSERT INTO harvest.eu_".$report."_mslevel (cc, gml_id, repcode, repreportedperdiod, mslsludgeproduction, mslreusesoilagriculture, mslreuseothers, msldisposalothers, msldisposalincineration, msldisposallandfill)
        SELECT   '".$cc."' as cc, gml_id, repcode, repreportedperdiod, mslsludgeproduction, mslreusesoilagriculture, mslreuseothers, msldisposalothers, msldisposalincineration, msldisposallandfill
        FROM harvest.".$cc."_".$report."_mslevel
        "
    );
    
}

function uwwtd_sync_aggregate_art17_mslevel($cc, $report = '9th'){
    //Create the aggregation table
    db_query("
        CREATE TABLE IF NOT EXISTS harvest.eu_".$report."_art17_mslevel (
            cc character(2),
            year_of_datas integer,
            soeccode character varying,
            soecinvcol double precision,
            soecinvcomments 	character varying,
            soecnumbias 	integer,
            soecperiod character varying,
            soeclenghtcocs double precision,
            soecinvias double precision,
            soeceufunds double precision,
            soecjobs integer,
            soecopcosts double precision,
            soecpop 	integer,
            soeclenghtstcs double precision,
            soeclenghtsacs double precision,
            soecinvtp double precision,
            soeccapacity integer,
            soecendyear character varying,
            soecstartyear character varying
        );
    ");
    //Create the source table if needed (skip errors)
        db_query("
        CREATE TABLE IF NOT EXISTS harvest.".$cc."_".$report."_art17_mslevel (
            year_of_datas integer,
            soeccode character varying,
            soecinvcol double precision,
            soecinvcomments 	character varying,
            soecnumbias 	integer,
            soecperiod character varying,
            soeclenghtcocs double precision,
            soecinvias double precision,
            soeceufunds double precision,
            soecjobs integer,
            soecopcosts double precision,
            soecpop 	integer,
            soeclenghtstcs double precision,
            soeclenghtsacs double precision,
            soecinvtp double precision,
            soeccapacity integer,
            soecendyear character varying,
            soecstartyear character varying
        );
    ");
    //Delete old data 
    db_query("DELETE FROM harvest.eu_".$report."_art17_mslevel WHERE cc = :cc", array(':cc'=>$cc));
    
    //INSERT Data in the global table
    db_query("
        INSERT INTO harvest.eu_".$report."_art17_mslevel (cc, year_of_datas, soeccode, soecinvcol, soecinvcomments, soecnumbias, soecperiod, soeclenghtcocs, soecinvias, soeceufunds, soecjobs, soecopcosts, soecpop, soeclenghtstcs, soeclenghtsacs, soecinvtp, soeccapacity, soecendyear, soecstartyear)
        SELECT   '".$cc."' as cc, year_of_datas, soeccode, soecinvcol, soecinvcomments, soecnumbias, soecperiod, soeclenghtcocs, soecinvias, soeceufunds, soecjobs, soecopcosts, soecpop, soeclenghtstcs, soeclenghtsacs, soecinvtp, soeccapacity, soecendyear, soecstartyear
        FROM harvest.".$cc."_".$report."_art17_mslevel
        "
    );
}
function uwwtd_sync_aggregate_art17_agglomeration($cc, $report = '9th'){
    //Create the aggregation table
    db_query("
        CREATE TABLE IF NOT EXISTS harvest.eu_".$report."_art17_agglomeration (
            cc character(2),
            year_of_data character varying,
            aggcode character varying,
            aggname character varying,
            flaggstatus character varying,
            flaggloan double precision,
            flaggloanname character varying,
            flaggotherfundname character varying,
            flaggreasons character varying,
            flaggmeasures character varying,
            flagginv double precision,
            flaggeufundname character varying,
            flaggeufund double precision,
            flaggcomments character varying,
            flaggexpload integer,
            flaggexploadcoll double precision,
            flaggotherfund double precision,
            flaggexploadias double precision,
            flaggexpecdatestart character varying,
            flaggexpecdatestartw character varying,
            flaggexpecdatecomple character varying
        );
    ");
    //Create the source table if needed (skip errors)
        db_query("
        CREATE TABLE IF NOT EXISTS harvest.".$cc."_".$report."_art17_agglomeration (
            year_of_data character varying,
            aggcode character varying,
            aggname character varying,
            flaggstatus character varying,
            flaggloan double precision,
            flaggloanname character varying,
            flaggotherfundname character varying,
            flaggreasons character varying,
            flaggmeasures character varying,
            flagginv double precision,
            flaggeufundname character varying,
            flaggeufund double precision,
            flaggcomments character varying,
            flaggexpload integer,
            flaggexploadcoll double precision,
            flaggotherfund double precision,
            flaggexploadias double precision,
            flaggexpecdatestart character varying,
            flaggexpecdatestartw character varying,
            flaggexpecdatecomple character varying
        );
    ");
    //Delete old data 
    db_query("DELETE FROM harvest.eu_".$report."_art17_agglomeration WHERE cc = :cc", array(':cc'=>$cc));
    
    //INSERT Data in the global table
    db_query("
        INSERT INTO harvest.eu_".$report."_art17_agglomeration (cc, year_of_data, aggcode, aggname, flaggstatus, flaggloan, flaggloanname, flaggotherfundname, flaggreasons, flaggmeasures, flagginv, flaggeufundname, flaggeufund, flaggcomments, flaggexpload, flaggexploadcoll, flaggotherfund, flaggexploadias, flaggexpecdatestart, flaggexpecdatestartw, flaggexpecdatecomple)
        SELECT   '".$cc."' as cc, year_of_data, aggcode, aggname, flaggstatus, flaggloan, flaggloanname, flaggotherfundname, flaggreasons, flaggmeasures, flagginv, flaggeufundname, flaggeufund, flaggcomments, flaggexpload, flaggexploadcoll, flaggotherfund, flaggexploadias, flaggexpecdatestart, flaggexpecdatestartw, flaggexpecdatecomple
        FROM harvest.".$cc."_".$report."_art17_agglomeration
        "
    );
}
function uwwtd_sync_aggregate_art17_uwwtp($cc, $report = '9th'){
    //Create the aggregation table
    db_query("
        CREATE TABLE IF NOT EXISTS harvest.eu_".$report."_art17_uwwtp(
            cc character(2),
            year_of_data character varying,
            uwwcode character varying,
            uwwname character varying,
            flatpstatus character varying,
            flatpmeasures character varying,
            flatpeufundname character varying,
            aggcode character varying,
            aggname character varying,
            flatpexpload integer,
            flatpexpcapacity integer,
            flatptexpectreatment character varying,
            flatpreasons character varying,
            flatpinv double precision,
            flatpeufund double precision,
            flatpcomments character varying,
            flatpexploadtruck double precision,
            flatpotherfund double precision,
            flatpotherfundname character varying,
            flatploan double precision,
            flatploanname character varying,
            flatpexpecdatestart character varying,
            flatpexpecdatestartw character varying,
            flatpexpecdatecomple character varying,
            flatpexpecdateperfor character varying
        );
    ");
    //Create the source table if needed (skip errors)
        db_query("
        CREATE TABLE IF NOT EXISTS harvest.".$cc."_".$report."_art17_uwwtp (
            year_of_data character varying,
            uwwcode character varying,
            uwwname character varying,
            flatpstatus character varying,
            flatpmeasures character varying,
            flatpeufundname character varying,
            aggcode character varying,
            aggname character varying,
            flatpexpload integer,
            flatpexpcapacity integer,
            flatptexpectreatment character varying,
            flatpreasons character varying,
            flatpinv double precision,
            flatpeufund double precision,
            flatpcomments character varying,
            flatpexploadtruck double precision,
            flatpotherfund double precision,
            flatpotherfundname character varying,
            flatploan double precision,
            flatploanname character varying,
            flatpexpecdatestart character varying,
            flatpexpecdatestartw character varying,
            flatpexpecdatecomple character varying,
            flatpexpecdateperfor character varying
        );
    ");
    //Delete old data 
    db_query("DELETE FROM harvest.eu_".$report."_art17_uwwtp WHERE cc = :cc", array(':cc'=>$cc));
    
    //INSERT Data in the global table
    db_query("
        INSERT INTO harvest.eu_".$report."_art17_uwwtp (cc, year_of_data, uwwcode, uwwname, flatpstatus, flatpmeasures, flatpeufundname, aggcode, aggname, flatpexpload, flatpexpcapacity, flatptexpectreatment, flatpreasons, flatpinv, flatpeufund, flatpcomments, flatpexploadtruck, flatpotherfund, flatpotherfundname, flatploan, flatploanname, flatpexpecdatestart, flatpexpecdatestartw, flatpexpecdatecomple, flatpexpecdateperfor)
        SELECT   '".$cc."' as cc, year_of_data, uwwcode, uwwname, flatpstatus, flatpmeasures, flatpeufundname, aggcode, aggname, flatpexpload, flatpexpcapacity, flatptexpectreatment, flatpreasons, flatpinv, flatpeufund, flatpcomments, flatpexploadtruck, flatpotherfund, flatpotherfundname, flatploan, flatploanname, flatpexpecdatestart, flatpexpecdatestartw, flatpexpecdatecomple, flatpexpecdateperfor
        FROM harvest.".$cc."_".$report."_art17_uwwtp
        "
    );
}

function uwwtd_sync_aggregate_uwwtp($cc, $report = '9th'){
    //Create the aggregation table
    db_query("
        CREATE TABLE IF NOT EXISTS harvest.eu_".$report."_uwwtp(
            cc character(2),
            ogc_fid 	integer NOT NULL,
            gml_id 	character varying,	
            uwwcode 	character varying,	
            repcode 	character varying,	
            uwwname 	character varying,	
            uwwstate 	character varying,	
            uwwe_prtrcode 	character varying,	
            uwwcollectingsystem 	character varying,	
            uwwnuts 	character varying,	
            uwwloadenteringuwwtp 	integer, 	
            uwwcapacity 	integer, 	
            uwwprimarytreatment 	integer, 	
            uwwsecondarytreatment 	integer, 	
            uwwnremoval 	integer, 	
            uwwpremoval 	integer, 	
            uwwuv 	integer, 	
            uwwchlorination 	integer, 	
            uwwozonation 	integer, 	
            uwwsandfiltration 	integer, 	
            uwwmicrofiltration 	integer, 	
            uwwspecification 	character varying,	
            uwwbod5perf 	character varying,	
            uwwcodperf 	character varying,	
            uwwtssperf 	character varying,	
            uwwntotperf 	character varying,	
            uwwptotperf 	character varying,	
            uwwotherperf 	character varying,	
            uwwbadperfdesign 	character varying,	
            uwwlatitude 	double precision, 	
            uwwlongitude 	double precision, 	
            uwwbodincomingmeasured 	double precision, 	
            uwwcodincomingmeasured 	double precision, 	
            uwwnincomingmeasured 	double precision, 	
            uwwpincomingmeasured 	double precision, 	
            uwwboddischargemeasured 	double precision, 	
            uwwcoddischargemeasured 	double precision, 	
            uwwndischargemeasured 	double precision, 	
            uwwpdischargemeasured 	double precision, 	
            uwwwastewatertreated 	double precision, 	
            uwwmethodwastewatertreated 	character varying,	
            uwwremarks 	character varying,	
            uwwdateclosing 	character varying,	
            uwwaccidents 	integer, 	
            uwwbadperformance 	integer, 	
            uwwboddischargecalculated 	double precision, 	
            uwwboddischargeestimated 	double precision, 	
            uwwbodincomingcalculated 	double precision, 	
            uwwbodincomingestimated 	double precision, 	
            uwwcoddischargecalculated 	double precision, 	
            uwwcoddischargeestimated 	double precision, 	
            uwwcodincomingcalculated 	double precision, 	
            uwwcodincomingestimated 	double precision, 	
            uwwhistorie 	character varying,	
            uwwinformation 	character varying,	
            uwwndischargecalculated 	double precision, 	
            uwwndischargeestimated 	double precision, 	
            uwwnincomingcalculated 	double precision, 	
            uwwnincomingestimated 	double precision, 	
            uwwpdischargecalculated 	double precision, 	
            uwwpdischargeestimated 	double precision, 	
            uwwpincomingcalculated 	double precision, 	
            uwwpincomingestimated 	double precision, 	
            uwwother 	character varying,	
            uwwtreatmenttype 	character varying,	
            repreportedperdiod 	character varying,
            wkb_geometry 	public.geometry(Geometry,4258)
        );
    ");
    //Create the source table if needed (skip errors)
        db_query("
        CREATE TABLE IF NOT EXISTS harvest.".$cc."_".$report."_uwwtp (
            ogc_fid 	integer NOT NULL,
            gml_id 	character varying,	
            uwwcode 	character varying,	
            repcode 	character varying,	
            uwwname 	character varying,	
            uwwstate 	character varying,	
            uwwe_prtrcode 	character varying,	
            uwwcollectingsystem 	character varying,	
            uwwnuts 	character varying,	
            uwwloadenteringuwwtp 	integer, 	
            uwwcapacity 	integer, 	
            uwwprimarytreatment 	integer, 	
            uwwsecondarytreatment 	integer, 	
            uwwnremoval 	integer, 	
            uwwpremoval 	integer, 	
            uwwuv 	integer, 	
            uwwchlorination 	integer, 	
            uwwozonation 	integer, 	
            uwwsandfiltration 	integer, 	
            uwwmicrofiltration 	integer, 	
            uwwspecification 	character varying,	
            uwwbod5perf 	character varying,	
            uwwcodperf 	character varying,	
            uwwtssperf 	character varying,	
            uwwntotperf 	character varying,	
            uwwptotperf 	character varying,	
            uwwotherperf 	character varying,	
            uwwbadperfdesign 	character varying,	
            uwwlatitude 	double precision, 	
            uwwlongitude 	double precision, 	
            uwwbodincomingmeasured 	double precision, 	
            uwwcodincomingmeasured 	double precision, 	
            uwwnincomingmeasured 	double precision, 	
            uwwpincomingmeasured 	double precision, 	
            uwwboddischargemeasured 	double precision, 	
            uwwcoddischargemeasured 	double precision, 	
            uwwndischargemeasured 	double precision, 	
            uwwpdischargemeasured 	double precision, 	
            uwwwastewatertreated 	double precision, 	
            uwwmethodwastewatertreated 	character varying,	
            uwwremarks 	character varying,	
            uwwdateclosing 	character varying,	
            uwwaccidents 	integer, 	
            uwwbadperformance 	integer, 	
            uwwboddischargecalculated 	double precision, 	
            uwwboddischargeestimated 	double precision, 	
            uwwbodincomingcalculated 	double precision, 	
            uwwbodincomingestimated 	double precision, 	
            uwwcoddischargecalculated 	double precision, 	
            uwwcoddischargeestimated 	double precision, 	
            uwwcodincomingcalculated 	double precision, 	
            uwwcodincomingestimated 	double precision, 	
            uwwhistorie 	character varying,	
            uwwinformation 	character varying,	
            uwwndischargecalculated 	double precision, 	
            uwwndischargeestimated 	double precision, 	
            uwwnincomingcalculated 	double precision, 	
            uwwnincomingestimated 	double precision, 	
            uwwpdischargecalculated 	double precision, 	
            uwwpdischargeestimated 	double precision, 	
            uwwpincomingcalculated 	double precision, 	
            uwwpincomingestimated 	double precision, 	
            uwwother 	character varying,	
            uwwtreatmenttype 	character varying,	
            repreportedperdiod 	character varying,
            wkb_geometry 	public.geometry(Geometry,4258)
        );
    ");
    //Delete old data 
    db_query("DELETE FROM harvest.eu_".$report."_uwwtp WHERE cc = :cc", array(':cc'=>$cc));
    
    //INSERT Data in the global table
    db_query("
        INSERT INTO harvest.eu_".$report."_uwwtp (cc,ogc_fid,gml_id,uwwcode,repcode,uwwname,uwwstate,uwwe_prtrcode,uwwcollectingsystem,uwwnuts,uwwloadenteringuwwtp,uwwcapacity,uwwprimarytreatment,uwwsecondarytreatment,uwwnremoval,uwwpremoval,uwwuv,uwwchlorination,uwwozonation,uwwsandfiltration,uwwmicrofiltration,uwwspecification,uwwbod5perf,uwwcodperf,uwwtssperf,uwwntotperf,uwwptotperf,uwwotherperf,uwwbadperfdesign,uwwlatitude,uwwlongitude,uwwbodincomingmeasured,uwwcodincomingmeasured,uwwnincomingmeasured,uwwpincomingmeasured,uwwboddischargemeasured,uwwcoddischargemeasured,uwwndischargemeasured,uwwpdischargemeasured,uwwwastewatertreated,uwwmethodwastewatertreated,uwwremarks,uwwdateclosing,uwwaccidents,uwwbadperformance,uwwboddischargecalculated,uwwboddischargeestimated,uwwbodincomingcalculated,uwwbodincomingestimated,uwwcoddischargecalculated,uwwcoddischargeestimated,uwwcodincomingcalculated,uwwcodincomingestimated,uwwhistorie,uwwinformation,uwwndischargecalculated,uwwndischargeestimated,uwwnincomingcalculated,uwwnincomingestimated,uwwpdischargecalculated,uwwpdischargeestimated,uwwpincomingcalculated,uwwpincomingestimated,uwwother,uwwtreatmenttype,repreportedperdiod,wkb_geometry)
        SELECT   '".$cc."' as cc, ogc_fid,gml_id,uwwcode,repcode,uwwname,uwwstate,uwwe_prtrcode,uwwcollectingsystem,uwwnuts,uwwloadenteringuwwtp,uwwcapacity,uwwprimarytreatment,uwwsecondarytreatment,uwwnremoval,uwwpremoval,uwwuv,uwwchlorination,uwwozonation,uwwsandfiltration,uwwmicrofiltration,uwwspecification,uwwbod5perf,uwwcodperf,uwwtssperf,uwwntotperf,uwwptotperf,uwwotherperf,uwwbadperfdesign,uwwlatitude,uwwlongitude,uwwbodincomingmeasured,uwwcodincomingmeasured,uwwnincomingmeasured,uwwpincomingmeasured,uwwboddischargemeasured,uwwcoddischargemeasured,uwwndischargemeasured,uwwpdischargemeasured,uwwwastewatertreated,uwwmethodwastewatertreated,uwwremarks,uwwdateclosing,uwwaccidents,uwwbadperformance,uwwboddischargecalculated,uwwboddischargeestimated,uwwbodincomingcalculated,uwwbodincomingestimated,uwwcoddischargecalculated,uwwcoddischargeestimated,uwwcodincomingcalculated,uwwcodincomingestimated,uwwhistorie,uwwinformation,uwwndischargecalculated,uwwndischargeestimated,uwwnincomingcalculated,uwwnincomingestimated,uwwpdischargecalculated,uwwpdischargeestimated,uwwpincomingcalculated,uwwpincomingestimated,uwwother,uwwtreatmenttype,repreportedperdiod,wkb_geometry
        FROM harvest.".$cc."_".$report."_uwwtp
        "
    );
}

function uwwtd_sync_aggregate_dcp($cc, $report = '9th'){
    //Create the aggregation table
    db_query("
        CREATE TABLE IF NOT EXISTS harvest.eu_".$report."_dcp(
            cc character(2),
            ogc_fid	integer NOT NULL,
            gml_id	character varying	,	
            dcpcode	character varying	,	
            repcode	character varying	,	
            dcpname	character varying	,	
            dcpstate	character varying	,	
            uwwid	character varying	,	
            dcpnuts	character varying	,	
            dcpwaterbodytype	character varying	,	
            dcpwaterbodyname	character varying	,	
            dcpirrigation	character varying	,	
            dcpwaterbodyid	character varying	,	
            dcpwfdrbd	character varying	,	
            rcaid	character varying	,	
            dcpnotaffect	character varying	,	
            dcpmsprovide	character varying	,	
            dcpcomaccept	character varying	,	
            dcpremarks	character varying	,	
            dcptypeofreceivingarea	character varying	,	
            dcpwaterbodyreferencedate	character varying	,	
            dcplatitude	double precision	,	
            dcplongitude	double precision	,	
            dcpgroundwater	character varying	,	
            dcpgroundwaterreferencedate	character varying	,	
            dcpreceivingwater	character varying	,	
            dcpreceivingwaterreferencedate	character varying	,	
            dcpsurfacewaters	character varying	,	
            dcpwfdrbdreferencedate	character varying	,	
            dcpwfdsubunit	character varying	,	
            dcpwfdsubunitreferencedate	character varying	,	
            repreportedperdiod	character varying	,
            wkb_geometry	public.geometry(Geometry,4258)
        );
    ");
    //Create the source table if needed (skip errors)
        db_query("
        CREATE TABLE IF NOT EXISTS harvest.".$cc."_".$report."_dcp (
            ogc_fid	integer NOT NULL,
            gml_id	character varying	,	
            dcpcode	character varying	,	
            repcode	character varying	,	
            dcpname	character varying	,	
            dcpstate	character varying	,	
            uwwid	character varying	,	
            dcpnuts	character varying	,	
            dcpwaterbodytype	character varying	,	
            dcpwaterbodyname	character varying	,	
            dcpirrigation	character varying	,	
            dcpwaterbodyid	character varying	,	
            dcpwfdrbd	character varying	,	
            rcaid	character varying	,	
            dcpnotaffect	character varying	,	
            dcpmsprovide	character varying	,	
            dcpcomaccept	character varying	,	
            dcpremarks	character varying	,	
            dcptypeofreceivingarea	character varying	,	
            dcpwaterbodyreferencedate	character varying	,	
            dcplatitude	double precision	,	
            dcplongitude	double precision	,	
            dcpgroundwater	character varying	,	
            dcpgroundwaterreferencedate	character varying	,	
            dcpreceivingwater	character varying	,	
            dcpreceivingwaterreferencedate	character varying	,	
            dcpsurfacewaters	character varying	,	
            dcpwfdrbdreferencedate	character varying	,	
            dcpwfdsubunit	character varying	,	
            dcpwfdsubunitreferencedate	character varying	,	
            repreportedperdiod	character varying	,
            wkb_geometry	public.geometry(Geometry,4258)
        );
    ");
    //Delete old data 
    db_query("DELETE FROM harvest.eu_".$report."_dcp WHERE cc = :cc", array(':cc'=>$cc));
    
    //INSERT Data in the global table
    db_query("
        INSERT INTO harvest.eu_".$report."_dcp (cc,ogc_fid,gml_id,dcpcode,repcode,dcpname,dcpstate,uwwid,dcpnuts,dcpwaterbodytype,dcpwaterbodyname,dcpirrigation,dcpwaterbodyid,dcpwfdrbd,rcaid,dcpnotaffect,dcpmsprovide,dcpcomaccept,dcpremarks,dcptypeofreceivingarea,dcpwaterbodyreferencedate,dcplatitude,dcplongitude,dcpgroundwater,dcpgroundwaterreferencedate,dcpreceivingwater,dcpreceivingwaterreferencedate,dcpsurfacewaters,dcpwfdrbdreferencedate,dcpwfdsubunit,dcpwfdsubunitreferencedate,repreportedperdiod,wkb_geometry)
        SELECT   '".$cc."' as cc, ogc_fid,gml_id,dcpcode,repcode,dcpname,dcpstate,uwwid,dcpnuts,dcpwaterbodytype,dcpwaterbodyname,dcpirrigation,dcpwaterbodyid,dcpwfdrbd,rcaid,dcpnotaffect,dcpmsprovide,dcpcomaccept,dcpremarks,dcptypeofreceivingarea,dcpwaterbodyreferencedate,dcplatitude,dcplongitude,dcpgroundwater,dcpgroundwaterreferencedate,dcpreceivingwater,dcpreceivingwaterreferencedate,dcpsurfacewaters,dcpwfdrbdreferencedate,dcpwfdsubunit,dcpwfdsubunitreferencedate,repreportedperdiod,wkb_geometry
        FROM harvest.".$cc."_".$report."_dcp
        "
    );
}

function uwwtd_sync_aggregate_agg_uwwtp($cc, $report = '9th'){
    //Create the aggregation table
    db_query("
        CREATE TABLE IF NOT EXISTS harvest.eu_".$report."_agg_uwwtp(
            cc character(2),
            repcode 	character varying ,
            uwwsiteid 	character varying,	
            uwwcode 	character varying,
            uwwname 	character varying, 	
            aggsiteid 	character varying,	 	
            aggcode 	character varying,
            aggname 	character varying, 	 	
            year 	character varying 	
        );
    ");
    //Create the source table if needed (skip errors)
        db_query("
        CREATE TABLE IF NOT EXISTS harvest.".$cc."_".$report."_agg_uwwtp (
            repcode 	character varying ,
            uwwsiteid 	character varying,	
            uwwcode 	character varying,
            uwwname 	character varying, 	
            aggsiteid 	character varying,	 	
            aggcode 	character varying,
            aggname 	character varying, 	 	
            repreportedperdiod 	character varying
        );
    ");
    //Delete old data 
    db_query("DELETE FROM harvest.eu_".$report."_agg_uwwtp WHERE cc = :cc", array(':cc'=>$cc));
    
    //INSERT Data in the global table
    db_query("
        INSERT INTO harvest.eu_".$report."_agg_uwwtp (cc, repcode,uwwsiteid,uwwcode,uwwname,aggsiteid,aggcode,aggname,year)
        SELECT   '".$cc."' as cc, repcode,uwwsiteid,uwwcode,uwwname,aggsiteid,aggcode,aggname,repreportedperdiod as year
        FROM harvest.".$cc."_".$report."_agg_uwwtp
        "
    );
}



function uwwtd_sync_harvest_agg($countryCode, $report = '9th'){
    global $databases;
    //dsm($GLOBALS['databases']);
    //We check if we really have a postgres database
    $output = array();
    if($databases['default']['default']['driver']=='pgsql'){
        
        $country_params = $GLOBALS['uwwtd_sync_conf']['country'][$countryCode];
        $search = array_keys($country_params['wfs'][$report]['mask']);
        $replace = array_values($country_params['wfs'][$report]['mask']);
        
        
        //================ Agglomeration ====================
        $wfs = str_replace(
            $search,
            $replace,
            $country_params['wfs'][$report]['Agglomeration']
        );
        
        $store = $GLOBALS['uwwtd_sync_conf']['store_schema'].'.'.$countryCode.'_'.$report.'_agglomeration';
        
        //Drop the old datastorage table
        db_query('DROP TABLE IF EXISTS '.$store);
        
        //Call ogr2ogr
        $output['Agglomeration']['store'] = $store;
        $output['Agglomeration']['out'] = uwwtd_sync_harvest_run_ogr($databases['default']['default'], $wfs, $store);
                
        //================ UWWTD_FeedAggloLevel ====================
        $wfs = str_replace(
            $search,
            $replace,
            $country_params['wfs'][$report]['UWWTD_FeedAggloLevel']
        );
        
        $store = $GLOBALS['uwwtd_sync_conf']['store_schema'].'.'.$countryCode.'_'.$report.'_feedagglolevel';
        
        //Drop the old datastorage table
        db_query('DROP TABLE IF EXISTS '.$store);
        
        //Call ogr2ogr
        $output['UWWTD_FeedAggloLevel']['store'] = $store;
        $output['UWWTD_FeedAggloLevel']['out'] = uwwtd_sync_harvest_run_ogr($databases['default']['default'], $wfs, $store);
        
        //================ MSLEVEL ====================
        $wfs = str_replace(
            $search,
            $replace,
            $country_params['wfs'][$report]['MSLEVEL']
        );
        
        $store = $GLOBALS['uwwtd_sync_conf']['store_schema'].'.'.$countryCode.'_'.$report.'_mslevel';
        
        //Drop the old datastorage table
        db_query('DROP TABLE IF EXISTS '.$store);
        
        //Call ogr2ogr
        $output['MSLEVEL']['store'] = $store;
        $output['MSLEVEL']['out'] = uwwtd_sync_harvest_run_ogr($databases['default']['default'], $wfs, $store);

    } 
    return $output;
}
function uwwtd_sync_harvest_uwwtp($countryCode, $report = '9th'){
    global $databases;
    //dsm($GLOBALS['databases']);
    //We check if we really have a postgres database
    $output = array();
    if($databases['default']['default']['driver']=='pgsql'){
        
        $country_params = $GLOBALS['uwwtd_sync_conf']['country'][$countryCode];
        $search = array_keys($country_params['wfs'][$report]['mask']);
        $replace = array_values($country_params['wfs'][$report]['mask']);
        
        
        //================ UWWTP ====================
        $wfs = str_replace(
            $search,
            $replace,
            $country_params['wfs'][$report]['uwwtp']
        );
        
        $store = $GLOBALS['uwwtd_sync_conf']['store_schema'].'.'.$countryCode.'_'.$report.'_uwwtp';
        
        //Drop the old datastorage table
        db_query('DROP TABLE IF EXISTS '.$store);
        
        //Call ogr2ogr
        $output['uwwtp']['store'] = $store;
        $output['uwwtp']['out'] = uwwtd_sync_harvest_run_ogr($databases['default']['default'], $wfs, $store);
        
    } 
    return $output;
}
function uwwtd_sync_harvest_dcp($countryCode, $report = '9th'){
    global $databases;
    //dsm($GLOBALS['databases']);
    //We check if we really have a postgres database
    $output = array();
    if($databases['default']['default']['driver']=='pgsql'){
        
        $country_params = $GLOBALS['uwwtd_sync_conf']['country'][$countryCode];
        $search = array_keys($country_params['wfs'][$report]['mask']);
        $replace = array_values($country_params['wfs'][$report]['mask']);
        
        
        //================ DCP ====================
        $wfs = str_replace(
            $search,
            $replace,
            $country_params['wfs'][$report]['dcp']
        );
        
        $store = $GLOBALS['uwwtd_sync_conf']['store_schema'].'.'.$countryCode.'_'.$report.'_dcp';
        
        //Drop the old datastorage table
        db_query('DROP TABLE IF EXISTS '.$store);
        
        //Call ogr2ogr
        $output['uwwtp']['store'] = $store;
        $output['uwwtp']['out'] = uwwtd_sync_harvest_run_ogr($databases['default']['default'], $wfs, $store);
        
    } 
    return $output;
}
function uwwtd_sync_harvest_agg_uwwtp($countryCode, $report = '9th'){
    global $databases;
    //dsm($GLOBALS['databases']);
    //We check if we really have a postgres database
    $output = array();
    if($databases['default']['default']['driver']=='pgsql'){
        
        $country_params = $GLOBALS['uwwtd_sync_conf']['country'][$countryCode];
        $search = array_keys($country_params['wfs'][$report]['mask']);
        $replace = array_values($country_params['wfs'][$report]['mask']);
        
        
        //================ agg_uwwtp ====================
        $wfs = str_replace(
            $search,
            $replace,
            $country_params['wfs'][$report]['agg_uwwtp']
        );
        
        $store = $GLOBALS['uwwtd_sync_conf']['store_schema'].'.'.$countryCode.'_'.$report.'_agg_uwwtp';
        
        //Drop the old datastorage table
        db_query('DROP TABLE IF EXISTS '.$store);
        
        //Call ogr2ogr
        $output['uwwtp']['store'] = $store;
        $output['uwwtp']['out'] = uwwtd_sync_harvest_run_ogr($databases['default']['default'], $wfs, $store);
        
    } 
    return $output;
}
function uwwtd_sync_harvest_art17($countryCode, $report = '9th'){
    global $databases;
    //dsm($GLOBALS['databases']);
    //We check if we really have a postgres database
    $output = array();
    if($databases['default']['default']['driver']=='pgsql'){
        
        $country_params = $GLOBALS['uwwtd_sync_conf']['country'][$countryCode];
        $search = array_keys($country_params['wfs'][$report]['mask']);
        $replace = array_values($country_params['wfs'][$report]['mask']);                
        
         //================ ART 17 MS LEVEL ====================
        $wfs = str_replace(
            $search,
            $replace,
            $country_params['wfs'][$report]['art17_mslevel']
        );
        
        $store = $GLOBALS['uwwtd_sync_conf']['store_schema'].'.'.$countryCode.'_'.$report.'_art17_mslevel';
        
        //Drop the old datastorage table
        db_query('DROP TABLE IF EXISTS '.$store);
        
        //Call ogr2ogr
        $output['art17_mslevel']['store'] = $store;
        $output['art17_mslevel']['out'] = uwwtd_sync_harvest_run_ogr($databases['default']['default'], $wfs, $store);
        
        //================ ART 17 Agglomeration ====================
        $wfs = str_replace(
            $search,
            $replace,
            $country_params['wfs'][$report]['art17_agglomeration']
        );
        
        $store = $GLOBALS['uwwtd_sync_conf']['store_schema'].'.'.$countryCode.'_'.$report.'_art17_agglomeration';
        
        //Drop the old datastorage table
        db_query('DROP TABLE IF EXISTS '.$store);
        
        //Call ogr2ogr
        $output['art17_agglomeration']['store'] = $store;
        $output['art17_agglomeration']['out'] = uwwtd_sync_harvest_run_ogr($databases['default']['default'], $wfs, $store);
        
        //================ ART 17 UWWTP ====================
        $wfs = str_replace(
            $search,
            $replace,
            $country_params['wfs'][$report]['art17_uwwtp']
        );
        
        $store = $GLOBALS['uwwtd_sync_conf']['store_schema'].'.'.$countryCode.'_'.$report.'_art17_uwwtp';
        
        //Drop the old datastorage table
        db_query('DROP TABLE IF EXISTS '.$store);
        
        //Call ogr2ogr
        $output['art17_uwwtp']['store'] = $store;
        $output['art17_uwwtp']['out'] = uwwtd_sync_harvest_run_ogr($databases['default']['default'], $wfs, $store);
    } 
    return $output;
}


function uwwtd_sync_harvest_run_ogr($con, $wfs, $store){
    //Shell command with ogr2ogr
    $cmd = $GLOBALS['uwwtd_sync_conf']['ogr2ogr'];
    $cmd.= ' -overwrite';
    $cmd.= ' -f';
    $cmd.= ' "PostgreSQL" PG:"host='.$con['host'].' user='.$con['username'].' password='.$con['password'].' dbname='.$con['database'].'"';
    $cmd.= ' "WFS:'.$wfs.'"';
    $cmd.= ' -nln "'.$store.'"';
    
    //dsm($cmd);
    
    //Run command
    /*
    if ($output_sh = shell_exec($cmd)) {
        return $output_sh;
    }
    else {
      throw new Exception('ogr2ogr could not execute: '.cmd);
      return false;
    }
    */
    //echo $cmd."<br/>";
    watchdog('uwwtd_harvest', $cmd);
    return uwwtd_sync_haverst_exec($cmd, "", 300);
    
}

/**
* executes command
*
* @param string $cmd command to execute
* @param string $input other input (not arguments)
* @return array
*/
function uwwtd_sync_haverst_exec($cmd, $input = "", $timeout=1000){
    $result = array('stdout' => '', 'stderr' => '', 'return' => '');
    $timeout += time();
    $descriptorspec = array(
          0 => array("pipe", "r"),
          1 => array("pipe", "w"),
          2 => array("pipe", "w")
    );
    $pipes = array();
    
    //exit($cmd);
    
    $process = proc_open($cmd, $descriptorspec, $pipes);
    fwrite($pipes[0], $input);
    
    if (!is_resource($process)) {
        throw new Exception("proc_open failed on: " . $cmd);
    }
    
    $output = '';
    do {
        $timeleft = $timeout - time();
        $read = array($pipes[1]);
        $write = Null;
        $exeptions = Null;
        stream_select($read, $write, $exeptions, $timeleft, NULL);
     
        if (!empty($read)) {
          $output .= fread($pipes[1], 8192);
        }
    } while (!feof($pipes[1]) && $timeleft > 0);
     
      if ($timeleft <= 0) {
        proc_terminate($process);
        throw new Exception("command timeout on: " . $cmd);
      } else {
        
        $result['stdout'] = $output;
        $result['stderr'] = stream_get_contents($pipes[2]);
        
        fclose($pipes[0]);
        fclose($pipes[1]);
        fclose($pipes[2]);
        
        $result['return'] = proc_close($process);
        
        
        
        return $result;
    }
}


