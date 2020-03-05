<?php

$GLOBALS['uwwtd_map']['maps']=[
    //Compliance
    'mslevel_art3_comp_10th'=>['title'=>"Degree of compliance with Article 3 at MS level for 10th report (2016)", 'map_scale'=>'MS Level', 'map_type'=>'Compliance'],
    'mslevel_art4_comp_10th'=>['title'=>"Degree of compliance with Article 4 at MS level for 10th report (2016)", 'map_scale'=>'MS Level', 'map_type'=>'Compliance'],
    'mslevel_art5_comp_10th'=>['title'=>"Degree of compliance with Article 5 at MS level for 10th report (2016)", 'map_scale'=>'MS Level', 'map_type'=>'Compliance'],
    'nuts2level_art3_comp_10th'=>['title'=>"Degree of compliance with Article 3 at Nuts 2 level for 10th report (2016)", 'map_scale'=>'Nuts 2', 'map_type'=>'Compliance - SUB'],
    'nuts2level_art4_comp_10th'=>['title'=>"Degree of compliance with Article 4 at Nuts 2 level for 10th report (2016)", 'map_scale'=>'Nuts 2', 'map_type'=>'Compliance - SUB'],
    'nuts2level_art5_comp_10th'=>['title'=>"Degree of compliance with Article 5 at Nuts 2 level for 10th report (2016)", 'map_scale'=>'Nuts 2', 'map_type'=>'Compliance - SUB'],
    'rbdlevel_art3_comp_10th'=>['title'=>"Degree of compliance with Article 3 at RBD level for 10th report (2016)", 'map_scale'=>'RBD', 'map_type'=>'Compliance - SUB'],
    'rbdlevel_art4_comp_10th'=>['title'=>"Degree of compliance with Article 4 at RBD level for 10th report (2016)", 'map_scale'=>'RBD', 'map_type'=>'Compliance - SUB'],
    'rbdlevel_art5_comp_10th'=>['title'=>"Degree of compliance with Article 5 at RBD level for 10th report (2016)", 'map_scale'=>'RBD', 'map_type'=>'Compliance - SUB'],
    //Distance To Target
    'mslevel_art3_dtt_10th'=>['title'=>"Degree of distance to target with Article 3 at MS level for 10th report (2016)", 'map_scale'=>'MS Level', 'map_type'=>'Distance to target'],
    'mslevel_art4_dtt_10th'=>['title'=>"Degree of distance to target with Article 4 at MS level for 10th report (2016)", 'map_scale'=>'MS Level', 'map_type'=>'Distance to target'],
    'mslevel_art5_dtt_10th'=>['title'=>"Degree of distance to target with Article 5 at MS level for 10th report (2016)", 'map_scale'=>'MS Level', 'map_type'=>'Distance to target'],
    'nuts2level_art3_dtt_10th'=>['title'=>"Degree of distance to target with Article 3 at Nuts 2 level for 10th report (2016)", 'map_scale'=>'Nuts 2', 'map_type'=>'Distance to target - SUB'],
    'nuts2level_art4_dtt_10th'=>['title'=>"Degree of distance to target with Article 4 at Nuts 2 level for 10th report (2016)", 'map_scale'=>'Nuts 2', 'map_type'=>'Distance to target - SUB'],
    'nuts2level_art5_dtt_10th'=>['title'=>"Degree of distance to target with Article 5 at Nuts 2 level for 10th report (2016)", 'map_scale'=>'Nuts 2', 'map_type'=>'Distance to target - SUB'],
    'rbdlevel_art3_dtt_10th'=>['title'=>"Degree of distance to target with Article 3 at RBD level for 10th report (2016)", 'map_scale'=>'RBD', 'map_type'=>'Distance to target - SUB'],
    'rbdlevel_art4_dtt_10th'=>['title'=>"Degree of distance to target with Article 4 at RBD level for 10th report (2016)", 'map_scale'=>'RBD', 'map_type'=>'Distance to target - SUB'],
    'rbdlevel_art5_dtt_10th'=>['title'=>"Degree of distance to target with Article 5 at RBD level for 10th report (2016)", 'map_scale'=>'RBD', 'map_type'=>'Distance to target - SUB'],
];
$GLOBALS['uwwtd_map']['legend']=[
    'Compliance'=>[
        [
            'title'=>'Degree of compliance',
            'items'=>[
                ['label'=>'97-100 %', 'color'=>'#2b83ba'],
                ['label'=>'95-97 %', 'color'=>'#75de5d'],
                ['label'=>'85-95 %', 'color'=>'#f0f018'],
                ['label'=>'70-85 %', 'color'=>'#fdae61'],
                ['label'=>'0-70 %', 'color'=>'#d7191c'],
            ]
        ],
        [
            'title'=>'',
            'items'=>[
                ['label'=>'Not Subject to compliance due to ongoing transitional period', 'color'=>'#808080'],
                ['label'=>'Non EU countries', 'color'=>'#e3e3e3'],
            ]
        ]
    ],
    'Compliance - SUB'=>[
        [
            'title'=>'Degree of compliance',
            'items'=>[
                ['label'=>'97-100 %', 'color'=>'#2b83ba'],
                ['label'=>'95-97 %', 'color'=>'#75de5d'],
                ['label'=>'85-95 %', 'color'=>'#f0f018'],
                ['label'=>'70-85 %', 'color'=>'#fdae61'],
                ['label'=>'0-70 %', 'color'=>'#d7191c'],
            ]
        ],
        [
            'title'=>'',
            'items'=>[
                ['label'=>'Compliance assesment on whole territory only', 'color'=>'#4b4b4b'],
                ['label'=>'Not Subject to compliance due to ongoing transitional period', 'color'=>'#808080'],
                ['label'=>'Non EU countries', 'color'=>'#e3e3e3'],
            ]
        ]
    ],
    'Distance to target'=>[
        [
            'title'=>'Degree of distance to target',
            'items'=>[
                ['label'=>'0-3 %', 'color'=>'#2b83ba'],
                ['label'=>'3-5 %', 'color'=>'#75de5d'],
                ['label'=>'5-15 %', 'color'=>'#f0f018'],
                ['label'=>'15-30 %', 'color'=>'#fdae61'],
                ['label'=>'30-100 %', 'color'=>'#d7191c'],
            ]
        ],
        [
            'title'=>'',
            'items'=>[
                ['label'=>'Not Subject to compliance due to ongoing transitional period', 'color'=>'#808080'],
                ['label'=>'Non EU countries', 'color'=>'#e3e3e3'],
            ]
        ]
    ],
    'Distance to target - SUB'=>[
        [
            'title'=>'Degree of distance to target',
            'items'=>[
                ['label'=>'0-3 %', 'color'=>'#2b83ba'],
                ['label'=>'3-5 %', 'color'=>'#75de5d'],
                ['label'=>'5-15 %', 'color'=>'#f0f018'],
                ['label'=>'15-30 %', 'color'=>'#fdae61'],
                ['label'=>'30-100 %', 'color'=>'#d7191c'],
            ]
        ],
        [
            'title'=>'',
            'items'=>[
                ['label'=>'Compliance assesment on whole territory only', 'color'=>'#4b4b4b'],
                ['label'=>'Not Subject to compliance due to ongoing transitional period', 'color'=>'#808080'],
                ['label'=>'Non EU countries', 'color'=>'#e3e3e3'],
            ]
        ]
    ]
];

$GLOBALS['uwwtd_map']['europe'] = array(
  'wkhtmlpath_command' => "/opt/wkhtmltox.0.12.4/bin/wkhtmltoimage --crop-y 10 --crop-w 700 --crop-h 1170 --javascript-delay 7000 '[#SOURCE#]' [#TARGET#]",
  'url_source' => url('map/europe'),
  'main_map' => 'uwwtd_map_europe',
  'list_minimap' =>   array(
    
    'topleft' => array(
      //Açores  PT
      'Açores (PT)' => array(
        'title' => 'Açores (PT)',
        'map_name' => 'acore',
        'class'    => 'acore',
      ),
      //MAdeira  PT
      'Madeira (PT)' => array(
        'title' => 'Madeira (PT)',
        'map_name' => 'madeira',
        'class'    => 'madeira',
      ),
  
      //Islas Canriass  ES
      'Islas Canariass (ES)' => array(
        'title' => 'Islas Canariass (ES)',
        'map_name' => 'canariass',
        'class'    => 'canariass',
      ),
    ),

    'topright' => array(
      //FR
      'La Réunion (FR)' => array(
        'title' => 'La Réunion (FR)',
        'map_name' => 'reunion',
        'class'    => 'reunion',
      ),
      'Guadeloupe (FR)' => array(
        'title' => 'Guadeloupe (FR)',
        'map_name' => 'guadeloupe',
        'class'    => 'guadeloupe',
      ),
      'Martinique (FR)' => array(
        'title' => 'Martinique (FR)',
        'map_name' => 'martinique',
        'class'    => 'martinique',
      ),
      'Guyane (FR)' => array(
        'title' => 'Guyane (FR)',
        'map_name' => 'guyane',
        'class'    => 'guyane',
      ),
    ),

    'bottomleft' => array(
      //Malta 
      'Malta' => array(
        'title' => 'Malta',
        'map_name' => 'malta',
        'class'    => 'malta',
      ),
    ),
  ),
);