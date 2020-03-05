<?php 
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

function uwwtdeu_import_settings(){
    $output = 'aaaa';
    $report = '10th';
    $limit = 100;
$mslevels = db_query("SELECT m.*, c.*, a.*
                              FROM harvest.eu_".$report."_mslevel m
                              LEFT JOIN calcul.cc_stat_by_size_".$report." c ON c.cc = m.cc
                              LEFT JOIN calcul.cc_stat_art_".$report." a ON a.cc = m.cc
                              ORDER BY m.cc")->fetchAll();
    dsm("SELECT m.*, c.*, a.*
                              FROM harvest.eu_".$report."_mslevel m
                              LEFT JOIN calcul.cc_stat_by_size_".$report." c ON c.cc = m.cc
                              LEFT JOIN calcul.cc_stat_art_".$report." a ON a.cc = m.cc
                              ORDER BY m.cc");
    dsm($mslevels);
    return $output;
}