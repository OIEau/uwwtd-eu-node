<?php 

require_once(drupal_get_path('module', 'uwwtd') . '/inc/uwwtd.config.inc');
require_once(drupal_get_path('module', 'uwwtd') . '/lib/PHPExcel-1.8.1/Classes/PHPExcel/IOFactory.php');
require_once(drupal_get_path('module', 'uwwtd_sync') . '/inc/uwwtd_sync.config.inc');
require_once(drupal_get_path('module', 'uwwtdeu') . '/includes/uwwtdeu.config.inc');

function uwwtdeu_stats_art17_form($form, &$form_state){
  $year = $GLOBALS['current_year'];
  $form['#prefix'] = '<h1 align="center">' . t('Article 17 - European stats') . '</h1>';
  
    $years = array();
      foreach($GLOBALS['years'] as $k=>$v){
        $years[$k] = $k.' reporting ('.implode(', ', $v).')';  
      }
  
    $form['yearselected'] = array(
      '#title' => t('Reporting'),
      '#type' => 'select',
      '#options' => $years,
      '#default_value' => isset($form_state['values']['year']) ? $form_state['values']['year'] : $year,
    );
    
    $form['submit'] = array(
      '#type' => 'submit',
      '#attributes' => array('class' => array('btn-primary', 'btn')),
      '#value' => t('Get Art 17 data')
    );
    
    return $form;
}

function uwwtdeu_stats_art17_form_submit($form, &$form_state){
    $report = $form_state['values']['yearselected'];
    
    $content_types=['article_17_ms_level', 'article_17_agglomeration', 'article_17_uwwtp'];
    
    try {
        // Load de excel model
        $objReader = PHPExcel_IOFactory::createReader("Excel2007");
        $objPHPExcel = $objReader->load(drupal_get_path('module', 'uwwtdeu') . '/model/'."Article_17_model.xlsx");

        // Foreach article 17 content type
        foreach ($content_types as $content_type) {
             if (function_exists("uwwtdeu_stats_" . $content_type )) {
                 $csvarray = call_user_func("uwwtdeu_stats_" . $content_type, $report);
             }
            // Export to excel sheets
            $sheet = $objPHPExcel->getSheetByName($content_type);
            foreach ($csvarray as $line => $row) {
                foreach ($row as $col => $val) {
                    $sheet->setCellValueByColumnAndRow($col, $line+1, $val);
                }
            }
            
        }

        // Write the excel output to browser
        
        $writer = new PHPExcel_Writer_Excel2007($objPHPExcel);
        header('Content-type: application/vnd.openxmlformats-officedocument.spreadsheetml.sheet');
        header('Content-Disposition:inline;filename=Article_17_EU_'.$report.'_'.time().'.xlsx');
        $writer->save('php://output');
        exit;
        
    } catch (Exception $e) {
        dsm($e->getMessage());
        return "";
    }
    
}

function uwwtdeu_stats_article_17_ms_level($report){
    $table = "eu_".$report."_art17_mslevel";
    
    $data = [];
    $result = db_select($table, 'c')
        ->fields('c', array_keys($GLOBALS['art17']['ms_level']))
        ->orderby('cc')
        ->execute();
    
    $data[] =array_values($GLOBALS['art17']['ms_level']);
    
    while($row = $result->fetchAssoc()){
        if(empty($data)){
             array_keys($row);
        }
        $row['soecperiod'] = $GLOBALS['article17']['glossary'][$row['soecperiod']];
        $row['cc'] = $GLOBALS['uwwtd_sync_conf']['country'][$row['cc']]['CountryName'];
        if($row['soecstartyear']!='') $row['soecstartyear'] =date('Y-m-d', strtotime($row['soecstartyear']));
        if($row['soecendyear']!='') $row['soecendyear'] =date('Y-m-d', strtotime($row['soecendyear']));
        
        //Change format of dates
        
        $data[] = array_values($row);
    }    
    
    return $data;  
}


function uwwtdeu_stats_article_17_agglomeration($report){
    $table = "eu_".$report."_art17_agglomeration";
    $data = [];
    $query = db_select($table, 'c')
        ->fields('c', array_keys($GLOBALS['art17']['agglomeration']))
        ->orderby('cc');
    $result = $query->execute();
    $data[] =array_values($GLOBALS['art17']['agglomeration']);
    while($row = $result->fetchAssoc()){
        $row['cc'] = $GLOBALS['uwwtd_sync_conf']['country'][$row['cc']]['CountryName'];
        if($row['flaggexpecdatestart']!='') $row['flaggexpecdatestart'] =date('Y-m-d', strtotime($row['flaggexpecdatestart']));
        if($row['flaggexpecdatestartw']!='') $row['flaggexpecdatestartw'] =date('Y-m-d', strtotime($row['flaggexpecdatestartw']));
        if($row['flaggexpecdatecomple']!='') $row['flaggexpecdatecomple'] =date('Y-m-d', strtotime($row['flaggexpecdatecomple']));
         
        $data[] = array_values($row);
    }    
    return $data;  
}


function uwwtdeu_stats_article_17_uwwtp($report){
    $table = "eu_".$report."_art17_uwwtp";
    $data = [];
    $query = db_select($table, 'c')
        ->fields('c', array_keys($GLOBALS['art17']['uwwtp']))
        ->orderby('cc');
    $result = $query->execute();
    $data[] =array_values($GLOBALS['art17']['uwwtp']);
    while($row = $result->fetchAssoc()){
        $row['cc'] = $GLOBALS['uwwtd_sync_conf']['country'][$row['cc']]['CountryName'];
        if($row['flatpexpecdatecomple']!='') $row['flatpexpecdatecomple'] =date('Y-m-d', strtotime($row['flatpexpecdatecomple']));
        if($row['flatpexpecdateperfor']!='') $row['flatpexpecdateperfor'] =date('Y-m-d', strtotime($row['flatpexpecdateperfor']));
        if($row['flatpexpecdatestart']!='') $row['flatpexpecdatestart'] =date('Y-m-d', strtotime($row['flatpexpecdatestart']));
        if($row['flatpexpecdatestartw']!='') $row['flatpexpecdatestartw'] =date('Y-m-d', strtotime($row['flatpexpecdatestartw']));
        $data[] = array_values($row);
    }    
    return $data;  
}




    
