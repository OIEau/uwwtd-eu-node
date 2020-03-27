<?php 

$fields_instance = array (
  'field_aggdatecompliance3' => 
  array (
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'date',
        'settings' => 
        array (
          'format_type' => 'long',
          'fromto' => 'both',
          'multiple_from' => '',
          'multiple_number' => '',
          'multiple_to' => '',
          'show_remaining_days' => false,
        ),
        'type' => 'date_default',
        'weight' => 75,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'date of compliance for article 3',
    'required' => 0,
    'settings' => 
    array (
      'default_value' => 'now',
      'default_value2' => 'same',
      'default_value_code' => '',
      'default_value_code2' => '',
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'date',
      'settings' => 
      array (
        'increment' => 1,
        'input_format' => 'm/d/Y - H:i:s',
        'input_format_custom' => '',
        'label_position' => 'above',
        'text_parts' => 
        array (
        ),
        'year_range' => '-3:+3',
      ),
      'type' => 'date_text',
      'weight' => '27',
    ),
    'id' => '1128',
    'field_id' => '1023',
    'field_name' => 'field_aggdatecompliance3',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggbeginlife' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'above',
        'module' => 'date',
        'settings' => 
        array (
          'format_type' => 'long',
          'fromto' => 'both',
          'multiple_from' => '',
          'multiple_number' => '',
          'multiple_to' => '',
          'show_remaining_days' => false,
        ),
        'type' => 'date_default',
        'weight' => 138,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Agglomeration begin life',
    'required' => false,
    'settings' => 
    array (
      'default_value' => 'now',
      'default_value2' => 'same',
      'default_value_code' => '',
      'default_value_code2' => '',
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'module' => 'text',
      'settings' => 
      array (
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => '94',
    ),
    'id' => '1115',
    'field_id' => '1010',
    'field_name' => 'field_aggbeginlife',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggdatecompliance6' => 
  array (
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 81,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'date of compliance for article 6',
    'required' => 0,
    'settings' => 
    array (
      'default_value' => 'now',
      'default_value2' => 'same',
      'default_value_code' => '',
      'default_value_code2' => '',
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'date',
      'settings' => 
      array (
        'increment' => 1,
        'input_format' => 'm/d/Y - H:i:s',
        'input_format_custom' => '',
        'label_position' => 'above',
        'text_parts' => 
        array (
        ),
        'year_range' => '-3:+3',
      ),
      'type' => 'date_text',
      'weight' => '34',
    ),
    'id' => '1131',
    'field_id' => '1026',
    'field_name' => 'field_aggdatecompliance6',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggcritca' => 
  array (
    'default_value' => 
    array (
      0 => 
      array (
        'value' => 0,
      ),
    ),
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'list',
        'settings' => 
        array (
        ),
        'type' => 'list_default',
        'weight' => 68,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Article 5 criterion c a',
    'required' => 0,
    'settings' => 
    array (
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'options',
      'settings' => 
      array (
        'checkall' => false,
      ),
      'type' => 'options_buttons',
      'weight' => '76',
    ),
    'id' => '1126',
    'field_id' => '1021',
    'field_name' => 'field_aggcritca',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggvideoinspections' => 
  array (
    'default_value' => 
    array (
    ),
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'list',
        'settings' => 
        array (
        ),
        'type' => 'list_default',
        'weight' => 98,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'What type of best technical knowledge/measures are used for building and maintanance of collecting system to prevent leaks: Regu',
    'required' => 0,
    'settings' => 
    array (
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'options',
      'settings' => 
      array (
        'display_label' => 0,
        'checkall' => false,
      ),
      'type' => 'options_buttons',
      'weight' => '51',
    ),
    'id' => '1164',
    'field_id' => '1059',
    'field_name' => 'field_aggvideoinspections',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggcritcb' => 
  array (
    'default_value' => 
    array (
      0 => 
      array (
        'value' => 0,
      ),
    ),
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'list',
        'settings' => 
        array (
        ),
        'type' => 'list_default',
        'weight' => 69,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Article 5 criterion c b',
    'required' => 0,
    'settings' => 
    array (
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'options',
      'settings' => 
      array (
        'checkall' => false,
      ),
      'type' => 'options_buttons',
      'weight' => '77',
    ),
    'id' => '1127',
    'field_id' => '1022',
    'field_name' => 'field_aggcritcb',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggcritb' => 
  array (
    'default_value' => 
    array (
      0 => 
      array (
        'value' => 0,
      ),
    ),
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'list',
        'settings' => 
        array (
        ),
        'type' => 'list_default',
        'weight' => 67,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Article 5 criterion b',
    'required' => 0,
    'settings' => 
    array (
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'options',
      'settings' => 
      array (
        'checkall' => false,
      ),
      'type' => 'options_buttons',
      'weight' => '78',
    ),
    'id' => '1125',
    'field_id' => '1020',
    'field_name' => 'field_aggcritb',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggart5compliance' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'list',
        'settings' => 
        array (
        ),
        'type' => 'list_default',
        'weight' => 9,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => '3rd treatment compliance',
    'required' => 0,
    'settings' => 
    array (
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'options',
      'settings' => 
      array (
      ),
      'type' => 'options_select',
      'weight' => '81',
    ),
    'id' => '1113',
    'field_id' => '1008',
    'field_name' => 'field_aggart5compliance',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_anneedata' => 
  array (
    'default_value' => 
    array (
      0 => 
      array (
        'value' => 2014,
      ),
    ),
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'list',
        'settings' => 
        array (
        ),
        'type' => 'list_default',
        'weight' => 7,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Year of data',
    'required' => 1,
    'settings' => 
    array (
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'options',
      'settings' => 
      array (
      ),
      'type' => 'options_select',
      'weight' => '73',
    ),
    'id' => '1165',
    'field_id' => '995',
    'field_name' => 'field_anneedata',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_agglongitude' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'number',
        'settings' => 
        array (
          'decimal_separator' => '.',
          'prefix_suffix' => true,
          'scale' => 2,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_decimal',
        'weight' => 66,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Longitude',
    'required' => 0,
    'settings' => 
    array (
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 0,
      'module' => 'number',
      'settings' => 
      array (
      ),
      'type' => 'number',
      'weight' => '18',
    ),
    'id' => '1143',
    'field_id' => '1038',
    'field_name' => 'field_agglongitude',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_agginhabitantswithouttreat' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'number',
        'settings' => 
        array (
          'decimal_separator' => '.',
          'prefix_suffix' => true,
          'scale' => 0,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_integer',
        'weight' => 103,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'No of inhabitants without treatment per agglomeration',
    'required' => 0,
    'settings' => 
    array (
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 0,
      'module' => 'number',
      'settings' => 
      array (
      ),
      'type' => 'number',
      'weight' => '56',
    ),
    'id' => '1141',
    'field_id' => '1036',
    'field_name' => 'field_agginhabitantswithouttreat',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggseweroverflows_m3' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'number',
        'settings' => 
        array (
          'decimal_separator' => '.',
          'prefix_suffix' => true,
          'scale' => 0,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_integer',
        'weight' => 93,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'How much raw sewage has been discharged through combined sewer overflows (CSOs) in the year reported: m3/y',
    'required' => 0,
    'settings' => 
    array (
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 0,
      'module' => 'number',
      'settings' => 
      array (
      ),
      'type' => 'number',
      'weight' => '46',
    ),
    'id' => '1161',
    'field_id' => '1056',
    'field_name' => 'field_aggseweroverflows_m3',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggpercwithouttreatment' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'number',
        'settings' => 
        array (
          'decimal_separator' => '.',
          'prefix_suffix' => true,
          'scale' => 2,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_decimal',
        'weight' => 86,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Discharged without treatment',
    'required' => 0,
    'settings' => 
    array (
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 0,
      'module' => 'number',
      'settings' => 
      array (
      ),
      'type' => 'number',
      'weight' => '39',
    ),
    'id' => '1153',
    'field_id' => '1048',
    'field_name' => 'field_aggpercwithouttreatment',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggc2' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'number',
        'settings' => 
        array (
          'decimal_separator' => '.',
          'prefix_suffix' => true,
          'scale' => 2,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_decimal',
        'weight' => 84,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Individual or Appropriate Systems (IAS)',
    'required' => 0,
    'settings' => 
    array (
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 0,
      'module' => 'number',
      'settings' => 
      array (
      ),
      'type' => 'number',
      'weight' => '37',
    ),
    'id' => '1119',
    'field_id' => '1014',
    'field_name' => 'field_aggc2',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggpercprimtreatment' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'number',
        'settings' => 
        array (
          'decimal_separator' => '.',
          'prefix_suffix' => true,
          'scale' => 2,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_decimal',
        'weight' => 88,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'IAS - in situ and/ or transported to UWWTPs by trucks: How much in % of generated load of agglomeration with primary treatment',
    'required' => 0,
    'settings' => 
    array (
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 0,
      'module' => 'number',
      'settings' => 
      array (
      ),
      'type' => 'number',
      'weight' => '41',
    ),
    'id' => '1150',
    'field_id' => '1045',
    'field_name' => 'field_aggpercprimtreatment',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggpercstringenttreatment' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'number',
        'settings' => 
        array (
          'decimal_separator' => '.',
          'prefix_suffix' => true,
          'scale' => 2,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_decimal',
        'weight' => 90,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'IAS - in situ and/ or transported to UWWTPs by trucks: How much in % of generated load of agglomeration with more stringent trea',
    'required' => 0,
    'settings' => 
    array (
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 0,
      'module' => 'number',
      'settings' => 
      array (
      ),
      'type' => 'number',
      'weight' => '43',
    ),
    'id' => '1152',
    'field_id' => '1047',
    'field_name' => 'field_aggpercstringenttreatment',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_agglatitude' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'number',
        'settings' => 
        array (
          'decimal_separator' => '.',
          'prefix_suffix' => true,
          'scale' => 2,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_decimal',
        'weight' => 65,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Latitude',
    'required' => 0,
    'settings' => 
    array (
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 0,
      'module' => 'number',
      'settings' => 
      array (
      ),
      'type' => 'number',
      'weight' => '17',
    ),
    'id' => '1142',
    'field_id' => '1037',
    'field_name' => 'field_agglatitude',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_agginhabitantsconnectedias' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'number',
        'settings' => 
        array (
          'decimal_separator' => '.',
          'prefix_suffix' => true,
          'scale' => 0,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_integer',
        'weight' => 102,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'No of inhabitants served by IAS per agglomeration',
    'required' => 0,
    'settings' => 
    array (
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 0,
      'module' => 'number',
      'settings' => 
      array (
      ),
      'type' => 'number',
      'weight' => '55',
    ),
    'id' => '1140',
    'field_id' => '1035',
    'field_name' => 'field_agginhabitantsconnectedias',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_documentationcitation' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'text',
        'settings' => 
        array (
        ),
        'type' => 'text_default',
        'weight' => 117,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'DocumentationCitation',
    'required' => 0,
    'settings' => 
    array (
      'text_processing' => 0,
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'text',
      'settings' => 
      array (
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => '70',
    ),
    'id' => '1173',
    'field_id' => '1067',
    'field_name' => 'field_documentationcitation',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_inspireidlocalid' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'text',
        'settings' => 
        array (
        ),
        'type' => 'text_default',
        'weight' => 3,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Identifier of the agglomeration',
    'required' => 0,
    'settings' => 
    array (
      'text_processing' => 0,
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'text',
      'settings' => 
      array (
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => '4',
    ),
    'id' => '1177',
    'field_id' => '1071',
    'field_name' => 'field_inspireidlocalid',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_namenativeness' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'text',
        'settings' => 
        array (
        ),
        'type' => 'text_default',
        'weight' => 15,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'nameNativeness',
    'required' => 0,
    'settings' => 
    array (
      'text_processing' => 0,
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'text',
      'settings' => 
      array (
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => '9',
    ),
    'id' => '1184',
    'field_id' => '1078',
    'field_name' => 'field_namenativeness',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggmethodc1' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'text',
        'settings' => 
        array (
        ),
        'type' => 'text_default',
        'weight' => 83,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Method used to obtain the %-value (calculated or estimated, for aggC1)',
    'required' => 0,
    'settings' => 
    array (
      'text_processing' => 0,
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'text',
      'settings' => 
      array (
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => '36',
    ),
    'id' => '1144',
    'field_id' => '1039',
    'field_name' => 'field_aggmethodc1',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_endlifespanversion' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'text',
        'settings' => 
        array (
        ),
        'type' => 'text_default',
        'weight' => 114,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'endLifespanVersion',
    'required' => 0,
    'settings' => 
    array (
      'text_processing' => 0,
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'text',
      'settings' => 
      array (
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => '67',
    ),
    'id' => '1174',
    'field_id' => '1068',
    'field_name' => 'field_endlifespanversion',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_zonetype' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'text',
        'settings' => 
        array (
        ),
        'type' => 'text_default',
        'weight' => 107,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'zoneType',
    'required' => 0,
    'settings' => 
    array (
      'text_processing' => 0,
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'text',
      'settings' => 
      array (
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => '60',
    ),
    'id' => '1197',
    'field_id' => '1089',
    'field_name' => 'field_zonetype',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_namepronunciation' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'text',
        'settings' => 
        array (
        ),
        'type' => 'text_default',
        'weight' => 17,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'NamePronunciation',
    'required' => 0,
    'settings' => 
    array (
      'text_processing' => 0,
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'text',
      'settings' => 
      array (
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => '12',
    ),
    'id' => '1185',
    'field_id' => '1079',
    'field_name' => 'field_namepronunciation',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggcapacity' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'above',
        'module' => 'list',
        'settings' => 
        array (
        ),
        'type' => 'list_default',
        'weight' => 131,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'What are the measures based on: Capacity in relation to dry weather flow',
    'required' => 0,
    'settings' => 
    array (
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'options',
      'settings' => 
      array (
        'checkall' => false,
      ),
      'type' => 'options_buttons',
      'weight' => '88',
    ),
    'id' => '1121',
    'field_id' => '1016',
    'field_name' => 'field_aggcapacity',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggaccoverflows' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'above',
        'module' => 'list',
        'settings' => 
        array (
        ),
        'type' => 'list_default',
        'weight' => 130,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'What are the measures based on: Acceptable number of overflows per year',
    'required' => 0,
    'settings' => 
    array (
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'options',
      'settings' => 
      array (
        'checkall' => false,
      ),
      'type' => 'options_buttons',
      'weight' => '87',
    ),
    'id' => '1109',
    'field_id' => '1004',
    'field_name' => 'field_aggaccoverflows',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggothermeasures' => 
  array (
    'default_value' => 
    array (
    ),
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'list',
        'settings' => 
        array (
        ),
        'type' => 'list_default',
        'weight' => 99,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'What type of best technical knowledge/measures are used for building and maintanance of collecting system to prevent leaks: Othe',
    'required' => 0,
    'settings' => 
    array (
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'options',
      'settings' => 
      array (
        'display_label' => 0,
        'checkall' => false,
      ),
      'type' => 'options_buttons',
      'weight' => '52',
    ),
    'id' => '1149',
    'field_id' => '1044',
    'field_name' => 'field_aggothermeasures',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_legislationcitation' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'text',
        'settings' => 
        array (
        ),
        'type' => 'text_default',
        'weight' => 116,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'LegislationCitation',
    'required' => 0,
    'settings' => 
    array (
      'text_processing' => 0,
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'text',
      'settings' => 
      array (
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => '69',
    ),
    'id' => '1180',
    'field_id' => '1074',
    'field_name' => 'field_legislationcitation',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggseweroverflows_pe' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'number',
        'settings' => 
        array (
          'decimal_separator' => '.',
          'prefix_suffix' => true,
          'scale' => 0,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_integer',
        'weight' => 94,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'How much raw sewage has been discharged through combined sewer overflows (CSOs) in the year reported: p.e.',
    'required' => 0,
    'settings' => 
    array (
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 0,
      'module' => 'number',
      'settings' => 
      array (
      ),
      'type' => 'number',
      'weight' => '47',
    ),
    'id' => '1162',
    'field_id' => '1057',
    'field_name' => 'field_aggseweroverflows_pe',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_specialisedzonetype' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'text',
        'settings' => 
        array (
        ),
        'type' => 'text_default',
        'weight' => 111,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'specialisedZoneType',
    'required' => 0,
    'settings' => 
    array (
      'text_processing' => 0,
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'text',
      'settings' => 
      array (
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => '64',
    ),
    'id' => '1194',
    'field_id' => '1086',
    'field_name' => 'field_specialisedzonetype',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggchanges' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'text',
        'settings' => 
        array (
        ),
        'type' => 'text_default',
        'weight' => 72,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Are there any significant changes of the generated load compared to the previous Report?',
    'required' => 0,
    'settings' => 
    array (
      'text_processing' => 0,
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'text',
      'settings' => 
      array (
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => '24',
    ),
    'id' => '1122',
    'field_id' => '1017',
    'field_name' => 'field_aggchanges',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggbigid' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'text',
        'settings' => 
        array (
        ),
        'type' => 'text_default',
        'weight' => 70,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'ID of the big city/ big discharger',
    'required' => 0,
    'settings' => 
    array (
      'text_processing' => 0,
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'text',
      'settings' => 
      array (
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => '22',
    ),
    'id' => '1117',
    'field_id' => '1012',
    'field_name' => 'field_aggbigid',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_inspireidnamespace' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'text',
        'settings' => 
        array (
        ),
        'type' => 'text_default',
        'weight' => 12,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'inspireIdNamespace',
    'required' => 0,
    'settings' => 
    array (
      'text_processing' => 0,
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'text',
      'settings' => 
      array (
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => '5',
    ),
    'id' => '1178',
    'field_id' => '1072',
    'field_name' => 'field_inspireidnamespace',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggexplanationother' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'text',
        'settings' => 
        array (
        ),
        'type' => 'text_default',
        'weight' => 100,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Short explanation of other measures',
    'required' => 0,
    'settings' => 
    array (
      'text_processing' => 0,
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'text',
      'settings' => 
      array (
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => '53',
    ),
    'id' => '1135',
    'field_id' => '1030',
    'field_name' => 'field_aggexplanationother',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggperiodover5' => 
  array (
    'description' => 'Date of the relevant deadline of UWWTD or Transitional Period article 5',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'date',
        'settings' => 
        array (
          'format_type' => 'short',
          'fromto' => 'both',
          'multiple_from' => '',
          'multiple_number' => '',
          'multiple_to' => '',
          'show_remaining_days' => false,
        ),
        'type' => 'date_default',
        'weight' => 78,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Deadline 3rd treatment compliance',
    'required' => 0,
    'settings' => 
    array (
      'default_value' => 'now',
      'default_value2' => 'same',
      'default_value_code' => '',
      'default_value_code2' => '',
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'date',
      'settings' => 
      array (
        'increment' => 1,
        'input_format' => 'm/d/Y - H:i:s',
        'input_format_custom' => '',
        'label_position' => 'above',
        'text_parts' => 
        array (
        ),
        'year_range' => '-3:+3',
      ),
      'type' => 'date_text',
      'weight' => '30',
    ),
    'id' => '1156',
    'field_id' => '1051',
    'field_name' => 'field_aggperiodover5',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_position_geo' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'hidden',
        'module' => 'geofield_map',
        'settings' => 
        array (
          'geofield_map_baselayers_hybrid' => 1,
          'geofield_map_baselayers_map' => 1,
          'geofield_map_baselayers_physical' => 0,
          'geofield_map_baselayers_satellite' => 1,
          'geofield_map_center' => 
          array (
            'lat' => 0,
            'lon' => 0,
          ),
          'geofield_map_controltype' => 'default',
          'geofield_map_draggable' => 0,
          'geofield_map_height' => '200px',
          'geofield_map_maptype' => 'satellite',
          'geofield_map_max_zoom' => 0,
          'geofield_map_min_zoom' => 0,
          'geofield_map_mtc' => 'standard',
          'geofield_map_overview' => 0,
          'geofield_map_overview_opened' => 0,
          'geofield_map_pancontrol' => 1,
          'geofield_map_scale' => 0,
          'geofield_map_scrollwheel' => 0,
          'geofield_map_streetview_show' => 0,
          'geofield_map_width' => '100%',
          'geofield_map_zoom' => 16,
        ),
        'type' => 'geofield_map_map',
        'weight' => 1,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Position',
    'required' => false,
    'settings' => 
    array (
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'module' => 'geofield',
      'settings' => 
      array (
      ),
      'type' => 'geofield_wkt',
      'weight' => '71',
    ),
    'id' => '1187',
    'field_id' => '1081',
    'field_name' => 'field_position_geo',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggpressuretest' => 
  array (
    'default_value' => 
    array (
    ),
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'list',
        'settings' => 
        array (
        ),
        'type' => 'list_default',
        'weight' => 97,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'What type of best technical knowledge/measures are used for building and maintanance of collecting system to prevent leaks: Pres',
    'required' => 0,
    'settings' => 
    array (
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'options',
      'settings' => 
      array (
        'display_label' => 0,
        'checkall' => false,
      ),
      'type' => 'options_buttons',
      'weight' => '50',
    ),
    'id' => '1158',
    'field_id' => '1053',
    'field_name' => 'field_aggpressuretest',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_agg_dilution_rates' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'above',
        'module' => 'list',
        'settings' => 
        array (
        ),
        'type' => 'list_default',
        'weight' => 132,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'What are the measures based on: Dilution rates',
    'required' => 0,
    'settings' => 
    array (
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'options',
      'settings' => 
      array (
        'checkall' => false,
      ),
      'type' => 'options_buttons',
      'weight' => '89',
    ),
    'id' => '1107',
    'field_id' => '1002',
    'field_name' => 'field_agg_dilution_rates',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_reporting' => 
  array (
    'label' => 'Reporting',
    'widget' => 
    array (
      'weight' => '1',
      'type' => 'options_select',
      'module' => 'options',
      'active' => 1,
      'settings' => 
      array (
      ),
    ),
    'settings' => 
    array (
      'user_register_form' => false,
    ),
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'above',
        'type' => 'list_default',
        'settings' => 
        array (
        ),
        'module' => 'list',
        'weight' => 140,
      ),
      'teaser' => 
      array (
        'type' => 'hidden',
        'label' => 'above',
        'settings' => 
        array (
        ),
        'weight' => 0,
      ),
    ),
    'required' => 1,
    'description' => '',
    'default_value' => NULL,
    'id' => '1207',
    'field_id' => '1093',
    'field_name' => 'field_reporting',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggart3addcompliance' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'above',
        'module' => 'list',
        'settings' => 
        array (
        ),
        'type' => 'list_default',
        'weight' => 136,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Additionnal Compliance article3',
    'required' => false,
    'settings' => 
    array (
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'module' => 'options',
      'settings' => 
      array (
      ),
      'type' => 'options_select',
      'weight' => '93',
    ),
    'id' => '1110',
    'field_id' => '1005',
    'field_name' => 'field_aggart3addcompliance',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggcompliance' => 
  array (
    'default_value' => 
    array (
      0 => 
      array (
        'value' => 'NI',
      ),
    ),
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'list',
        'settings' => 
        array (
        ),
        'type' => 'list_default',
        'weight' => 6,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Compliance',
    'required' => 0,
    'settings' => 
    array (
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'options',
      'settings' => 
      array (
      ),
      'type' => 'options_select',
      'weight' => '75',
    ),
    'id' => '1124',
    'field_id' => '1019',
    'field_name' => 'field_aggcompliance',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_status' => 
  array (
    'default_value' => 
    array (
      0 => 
      array (
        'value' => 0,
      ),
    ),
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'list',
        'settings' => 
        array (
        ),
        'type' => 'list_default',
        'weight' => 4,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Status of the agglomeration',
    'required' => 0,
    'settings' => 
    array (
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'options',
      'settings' => 
      array (
        'checkall' => false,
      ),
      'type' => 'options_buttons',
      'weight' => '6',
    ),
    'id' => '1195',
    'field_id' => '1087',
    'field_name' => 'field_status',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggart4compliance' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'list',
        'settings' => 
        array (
        ),
        'type' => 'list_default',
        'weight' => 8,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => '2nd treatment compliance',
    'required' => 0,
    'settings' => 
    array (
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'options',
      'settings' => 
      array (
      ),
      'type' => 'options_select',
      'weight' => '80',
    ),
    'id' => '1112',
    'field_id' => '1007',
    'field_name' => 'field_aggart4compliance',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggart6compliance' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'list',
        'settings' => 
        array (
        ),
        'type' => 'list_default',
        'weight' => 135,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Article 6 compliance',
    'required' => false,
    'settings' => 
    array (
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'module' => 'options',
      'settings' => 
      array (
      ),
      'type' => 'options_select',
      'weight' => '92',
    ),
    'id' => '1114',
    'field_id' => '1009',
    'field_name' => 'field_aggart6compliance',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggart3compliance' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'list',
        'settings' => 
        array (
        ),
        'type' => 'list_default',
        'weight' => 7,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Connection compliance',
    'required' => 0,
    'settings' => 
    array (
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'options',
      'settings' => 
      array (
      ),
      'type' => 'options_select',
      'weight' => '79',
    ),
    'id' => '1111',
    'field_id' => '1006',
    'field_name' => 'field_aggart3compliance',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggc1' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'number',
        'settings' => 
        array (
          'decimal_separator' => '.',
          'prefix_suffix' => true,
          'scale' => 2,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_decimal',
        'weight' => 82,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Connected to collecting system',
    'required' => 0,
    'settings' => 
    array (
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 0,
      'module' => 'number',
      'settings' => 
      array (
      ),
      'type' => 'number',
      'weight' => '35',
    ),
    'id' => '1118',
    'field_id' => '1013',
    'field_name' => 'field_aggc1',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggpercsectreatment' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'number',
        'settings' => 
        array (
          'decimal_separator' => '.',
          'prefix_suffix' => true,
          'scale' => 2,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_decimal',
        'weight' => 89,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'IAS - in situ and/or transported to UWWTPs by trucks: How much in % of generated load of agglomeration with secondary treatment',
    'required' => 0,
    'settings' => 
    array (
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 0,
      'module' => 'number',
      'settings' => 
      array (
      ),
      'type' => 'number',
      'weight' => '42',
    ),
    'id' => '1151',
    'field_id' => '1046',
    'field_name' => 'field_aggpercsectreatment',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_agginhabitant' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'number',
        'settings' => 
        array (
          'decimal_separator' => '.',
          'prefix_suffix' => true,
          'scale' => 0,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_integer',
        'weight' => 101,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Population (inhabitants) of the agglomeration',
    'required' => 0,
    'settings' => 
    array (
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 0,
      'module' => 'number',
      'settings' => 
      array (
      ),
      'type' => 'number',
      'weight' => '54',
    ),
    'id' => '1139',
    'field_id' => '1034',
    'field_name' => 'field_agginhabitant',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_agggenerated' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'number',
        'settings' => 
        array (
          'decimal_separator' => '.',
          'prefix_suffix' => true,
          'scale' => 0,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_integer',
        'weight' => 5,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Generated load (p.e.)',
    'required' => 0,
    'settings' => 
    array (
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 0,
      'module' => 'number',
      'settings' => 
      array (
      ),
      'type' => 'number',
      'weight' => '19',
    ),
    'id' => '1137',
    'field_id' => '1032',
    'field_name' => 'field_agggenerated',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggconnected' => 
  array (
    'label' => 'Connected load (p.e.)',
    'widget' => 
    array (
      'weight' => '20',
      'type' => 'number',
      'module' => 'number',
      'active' => 0,
      'settings' => 
      array (
      ),
    ),
    'settings' => 
    array (
      'min' => '',
      'max' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => false,
    ),
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'above',
        'type' => 'number_integer',
        'settings' => 
        array (
          'thousand_separator' => '',
          'decimal_separator' => '.',
          'scale' => 0,
          'prefix_suffix' => true,
        ),
        'module' => 'number',
        'weight' => 141,
      ),
      'teaser' => 
      array (
        'type' => 'hidden',
        'label' => 'above',
        'settings' => 
        array (
        ),
        'weight' => 0,
      ),
    ),
    'required' => 0,
    'description' => '',
    'default_value' => NULL,
    'id' => '1260',
    'field_id' => '1128',
    'field_name' => 'field_aggconnected',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggias' => 
  array (
    'label' => 'IAS load (p.e.)',
    'widget' => 
    array (
      'weight' => '21',
      'type' => 'number',
      'module' => 'number',
      'active' => 0,
      'settings' => 
      array (
      ),
    ),
    'settings' => 
    array (
      'min' => '',
      'max' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => false,
    ),
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'above',
        'type' => 'number_integer',
        'settings' => 
        array (
          'thousand_separator' => '',
          'decimal_separator' => '.',
          'scale' => 0,
          'prefix_suffix' => true,
        ),
        'module' => 'number',
        'weight' => 142,
      ),
      'teaser' => 
      array (
        'type' => 'hidden',
        'label' => 'above',
        'settings' => 
        array (
        ),
        'weight' => 0,
      ),
    ),
    'required' => 0,
    'description' => '',
    'default_value' => NULL,
    'id' => '1261',
    'field_id' => '1129',
    'field_name' => 'field_aggias',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_countrycode' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 6,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Country code',
    'required' => 0,
    'settings' => 
    array (
      'text_processing' => 0,
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'text',
      'settings' => 
      array (
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => '2',
    ),
    'id' => '1190',
    'field_id' => '993',
    'field_name' => 'field_countrycode',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_beginlifespanversion' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'text',
        'settings' => 
        array (
        ),
        'type' => 'text_default',
        'weight' => 113,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'beginLifespanVersion',
    'required' => 0,
    'settings' => 
    array (
      'text_processing' => 0,
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'text',
      'settings' => 
      array (
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => '66',
    ),
    'id' => '1169',
    'field_id' => '1063',
    'field_name' => 'field_beginlifespanversion',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggexistmaintenanceplan' => 
  array (
    'default_value' => NULL,
    'description' => 'Is a maintenance plan (quality assurance) in place?',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'text',
        'settings' => 
        array (
        ),
        'type' => 'text_default',
        'weight' => 96,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Maintenance plan',
    'required' => 0,
    'settings' => 
    array (
      'text_processing' => 0,
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'text',
      'settings' => 
      array (
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => '49',
    ),
    'id' => '1134',
    'field_id' => '1029',
    'field_name' => 'field_aggexistmaintenanceplan',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggbesttechnicalknowledge' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'text',
        'settings' => 
        array (
        ),
        'type' => 'text_default',
        'weight' => 92,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Is best technical knowledge to limit pollution applied?',
    'required' => 0,
    'settings' => 
    array (
      'text_processing' => 0,
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'text',
      'settings' => 
      array (
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => '45',
    ),
    'id' => '1116',
    'field_id' => '1011',
    'field_name' => 'field_aggbesttechnicalknowledge',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_competentauthority' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'text',
        'settings' => 
        array (
        ),
        'type' => 'text_default',
        'weight' => 115,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'competentAuthority',
    'required' => 0,
    'settings' => 
    array (
      'text_processing' => 0,
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'text',
      'settings' => 
      array (
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => '68',
    ),
    'id' => '1170',
    'field_id' => '1064',
    'field_name' => 'field_competentauthority',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_designationperiod' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'text',
        'settings' => 
        array (
        ),
        'type' => 'text_default',
        'weight' => 112,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'designationPeriod',
    'required' => 0,
    'settings' => 
    array (
      'text_processing' => 0,
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'text',
      'settings' => 
      array (
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => '65',
    ),
    'id' => '1172',
    'field_id' => '1066',
    'field_name' => 'field_designationperiod',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_namegrammaticalgender' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'text',
        'settings' => 
        array (
        ),
        'type' => 'text_default',
        'weight' => 18,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'NameGrammaticalGender',
    'required' => 0,
    'settings' => 
    array (
      'text_processing' => 0,
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'text',
      'settings' => 
      array (
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => '13',
    ),
    'id' => '1181',
    'field_id' => '1075',
    'field_name' => 'field_namegrammaticalgender',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_sourceofname' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'text',
        'settings' => 
        array (
        ),
        'type' => 'text_default',
        'weight' => 16,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'sourceOfName',
    'required' => 0,
    'settings' => 
    array (
      'text_processing' => 0,
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'text',
      'settings' => 
      array (
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => '11',
    ),
    'id' => '1193',
    'field_id' => '1085',
    'field_name' => 'field_sourceofname',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_namelanguage' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'text',
        'settings' => 
        array (
        ),
        'type' => 'text_default',
        'weight' => 14,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'nameLanguage',
    'required' => 0,
    'settings' => 
    array (
      'text_processing' => 0,
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'text',
      'settings' => 
      array (
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => '8',
    ),
    'id' => '1183',
    'field_id' => '1077',
    'field_name' => 'field_namelanguage',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_environmentaldomain2' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'text',
        'settings' => 
        array (
        ),
        'type' => 'text_default',
        'weight' => 109,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'environmentalDomain2',
    'required' => 0,
    'settings' => 
    array (
      'text_processing' => 0,
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'text',
      'settings' => 
      array (
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => '62',
    ),
    'id' => '1176',
    'field_id' => '1070',
    'field_name' => 'field_environmentaldomain2',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggnathyperlink' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'text',
        'settings' => 
        array (
        ),
        'type' => 'text_default',
        'weight' => 105,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Agglomeration national Internet hyperlink',
    'required' => 0,
    'settings' => 
    array (
      'text_processing' => 0,
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'text',
      'settings' => 
      array (
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => '58',
    ),
    'id' => '1148',
    'field_id' => '1043',
    'field_name' => 'field_aggnathyperlink',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggmethodwithouttreatment' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'text',
        'settings' => 
        array (
        ),
        'type' => 'text_default',
        'weight' => 87,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Method used to obtain the %-value (calculated or estimated, for aggPercWithoutTreatment)',
    'required' => 0,
    'settings' => 
    array (
      'text_processing' => 0,
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'text',
      'settings' => 
      array (
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => '40',
    ),
    'id' => '1146',
    'field_id' => '1041',
    'field_name' => 'field_aggmethodwithouttreatment',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_environmentaldomain1' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'text',
        'settings' => 
        array (
        ),
        'type' => 'text_default',
        'weight' => 108,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'environmentalDomain1',
    'required' => 0,
    'settings' => 
    array (
      'text_processing' => 0,
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'text',
      'settings' => 
      array (
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => '61',
    ),
    'id' => '1175',
    'field_id' => '1069',
    'field_name' => 'field_environmentaldomain1',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_namestatus' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'text',
        'settings' => 
        array (
        ),
        'type' => 'text_default',
        'weight' => 11,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'nameStatus',
    'required' => 0,
    'settings' => 
    array (
      'text_processing' => 0,
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'text',
      'settings' => 
      array (
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => '10',
    ),
    'id' => '1186',
    'field_id' => '1080',
    'field_name' => 'field_namestatus',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_sensitiveareatype' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'text',
        'settings' => 
        array (
        ),
        'type' => 'text_default',
        'weight' => 118,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'sensitiveAreaType',
    'required' => 0,
    'settings' => 
    array (
      'text_processing' => 0,
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'text',
      'settings' => 
      array (
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => '72',
    ),
    'id' => '1191',
    'field_id' => '1083',
    'field_name' => 'field_sensitiveareatype',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_repcode' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 6,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Report ID',
    'required' => 0,
    'settings' => 
    array (
      'text_processing' => 0,
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'text',
      'settings' => 
      array (
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => '3',
    ),
    'id' => '1189',
    'field_id' => '994',
    'field_name' => 'field_repcode',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_namegrammaticalnumber' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'text',
        'settings' => 
        array (
        ),
        'type' => 'text_default',
        'weight' => 19,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'NameGrammaticalNumber',
    'required' => 0,
    'settings' => 
    array (
      'text_processing' => 0,
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'text',
      'settings' => 
      array (
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => '14',
    ),
    'id' => '1182',
    'field_id' => '1076',
    'field_name' => 'field_namegrammaticalnumber',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggmethodc2' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'text',
        'settings' => 
        array (
        ),
        'type' => 'text_default',
        'weight' => 85,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Method used to obtain the %-value (calculated or estimated, for aggC2)',
    'required' => 0,
    'settings' => 
    array (
      'text_processing' => 0,
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'text',
      'settings' => 
      array (
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => '38',
    ),
    'id' => '1145',
    'field_id' => '1040',
    'field_name' => 'field_aggmethodc2',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_agghaveregistrationsystem' => 
  array (
    'default_value' => NULL,
    'description' => 'Is a registration system for leaks in place?',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'text',
        'settings' => 
        array (
        ),
        'type' => 'text_default',
        'weight' => 95,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Leaks registration',
    'required' => 0,
    'settings' => 
    array (
      'text_processing' => 0,
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'text',
      'settings' => 
      array (
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => '48',
    ),
    'id' => '1138',
    'field_id' => '1033',
    'field_name' => 'field_agghaveregistrationsystem',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_article_4_compliance_expli' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'above',
        'module' => 'text',
        'settings' => 
        array (
        ),
        'type' => 'text_default',
        'weight' => 123,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Article 4 compliance explication',
    'required' => 0,
    'settings' => 
    array (
      'text_processing' => 0,
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'text',
      'settings' => 
      array (
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => '85',
    ),
    'id' => '1167',
    'field_id' => '1061',
    'field_name' => 'field_article_4_compliance_expli',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggchangescomment' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'text',
        'settings' => 
        array (
        ),
        'type' => 'text_default',
        'weight' => 73,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Comments on significant changes of the generated load compared to the previous reported load',
    'required' => 0,
    'settings' => 
    array (
      'text_processing' => 0,
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'text',
      'settings' => 
      array (
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => '25',
    ),
    'id' => '1123',
    'field_id' => '1018',
    'field_name' => 'field_aggchangescomment',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggcalculation' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'text',
        'settings' => 
        array (
        ),
        'type' => 'text_default',
        'weight' => 71,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Methods used for calculation of the generated load of the agglomeration',
    'required' => 0,
    'settings' => 
    array (
      'text_processing' => 0,
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'text',
      'settings' => 
      array (
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => '23',
    ),
    'id' => '1120',
    'field_id' => '1015',
    'field_name' => 'field_aggcalculation',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_article_3_compliance_expli' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'above',
        'module' => 'text',
        'settings' => 
        array (
        ),
        'type' => 'text_default',
        'weight' => 122,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Article 3 compliance explication',
    'required' => 0,
    'settings' => 
    array (
      'text_processing' => 0,
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'text',
      'settings' => 
      array (
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => '84',
    ),
    'id' => '1166',
    'field_id' => '1060',
    'field_name' => 'field_article_3_compliance_expli',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggremarks' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'text',
        'settings' => 
        array (
        ),
        'type' => 'text_default',
        'weight' => 104,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Remarks',
    'required' => 0,
    'settings' => 
    array (
      'text_processing' => 0,
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'text',
      'settings' => 
      array (
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => '57',
    ),
    'id' => '1159',
    'field_id' => '1054',
    'field_name' => 'field_aggremarks',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggsuccessor' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'text',
        'settings' => 
        array (
        ),
        'type' => 'text_default',
        'weight' => 21,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'ID of the successor',
    'required' => 0,
    'settings' => 
    array (
      'text_processing' => 0,
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'text',
      'settings' => 
      array (
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => '16',
    ),
    'id' => '1163',
    'field_id' => '1058',
    'field_name' => 'field_aggsuccessor',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_thematicid' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'text',
        'settings' => 
        array (
        ),
        'type' => 'text_default',
        'weight' => 110,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'thematicId',
    'required' => 0,
    'settings' => 
    array (
      'text_processing' => 0,
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'text',
      'settings' => 
      array (
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => '63',
    ),
    'id' => '1196',
    'field_id' => '1088',
    'field_name' => 'field_thematicid',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_siteid' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'text',
        'settings' => 
        array (
        ),
        'type' => 'text_default',
        'weight' => 6,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Site unique ID',
    'required' => 0,
    'settings' => 
    array (
      'text_processing' => 0,
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'text',
      'settings' => 
      array (
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => '74',
    ),
    'id' => '1192',
    'field_id' => '1084',
    'field_name' => 'field_siteid',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggmunicipalities' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'text',
        'settings' => 
        array (
        ),
        'type' => 'text_default',
        'weight' => 20,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Name of municipalities/communes of this agglomeration',
    'required' => 0,
    'settings' => 
    array (
      'text_processing' => 0,
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'text',
      'settings' => 
      array (
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => '15',
    ),
    'id' => '1147',
    'field_id' => '1042',
    'field_name' => 'field_aggmunicipalities',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_regionnuts' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'list',
        'settings' => 
        array (
        ),
        'type' => 'list_default',
        'weight' => 10,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Region (NUTS)',
    'required' => 0,
    'settings' => 
    array (
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'options',
      'settings' => 
      array (
      ),
      'type' => 'options_select',
      'weight' => '82',
    ),
    'id' => '1188',
    'field_id' => '1082',
    'field_name' => 'field_regionnuts',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggperiodover6' => 
  array (
    'description' => 'Date of the relevant deadline of UWWTD or Transitional Period article 6',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 80,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Deadline article 6',
    'required' => 0,
    'settings' => 
    array (
      'default_value' => 'now',
      'default_value2' => 'same',
      'default_value_code' => '',
      'default_value_code2' => '',
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'date',
      'settings' => 
      array (
        'increment' => 1,
        'input_format' => 'm/d/Y - H:i:s',
        'input_format_custom' => '',
        'label_position' => 'above',
        'text_parts' => 
        array (
        ),
        'year_range' => '-3:+3',
      ),
      'type' => 'date_text',
      'weight' => '32',
    ),
    'id' => '1157',
    'field_id' => '1052',
    'field_name' => 'field_aggperiodover6',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggperiodover4' => 
  array (
    'description' => 'Date of the relevant deadline of UWWTD or Transitional Period article 4',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'date',
        'settings' => 
        array (
          'format_type' => 'short',
          'fromto' => 'both',
          'multiple_from' => '',
          'multiple_number' => '',
          'multiple_to' => '',
          'show_remaining_days' => false,
        ),
        'type' => 'date_default',
        'weight' => 76,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Deadline 2nd treatment compliance',
    'required' => 0,
    'settings' => 
    array (
      'default_value' => 'now',
      'default_value2' => 'same',
      'default_value_code' => '',
      'default_value_code2' => '',
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'date',
      'settings' => 
      array (
        'increment' => 1,
        'input_format' => 'm/d/Y - H:i:s',
        'input_format_custom' => '',
        'label_position' => 'above',
        'text_parts' => 
        array (
        ),
        'year_range' => '-3:+3',
      ),
      'type' => 'date_text',
      'weight' => '28',
    ),
    'id' => '1155',
    'field_id' => '1050',
    'field_name' => 'field_aggperiodover4',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggperiodover3' => 
  array (
    'description' => 'Date of the relevant deadline of UWWTD or Transitional Period article 3',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'date',
        'settings' => 
        array (
          'format_type' => 'short',
          'fromto' => 'both',
          'multiple_from' => '',
          'multiple_number' => '',
          'multiple_to' => '',
          'show_remaining_days' => false,
        ),
        'type' => 'date_default',
        'weight' => 74,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Deadline connection compliance',
    'required' => 0,
    'settings' => 
    array (
      'default_value' => 'now',
      'default_value2' => 'same',
      'default_value_code' => '',
      'default_value_code2' => '',
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'date',
      'settings' => 
      array (
        'increment' => 1,
        'input_format' => 'm/d/Y - H:i:s',
        'input_format_custom' => '',
        'label_position' => 'above',
        'text_parts' => 
        array (
        ),
        'year_range' => '-3:+3',
      ),
      'type' => 'date_text',
      'weight' => '26',
    ),
    'id' => '1154',
    'field_id' => '1049',
    'field_name' => 'field_aggperiodover3',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggforecast' => 
  array (
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'above',
        'module' => 'date',
        'settings' => 
        array (
          'format_type' => 'long',
          'fromto' => 'both',
          'multiple_from' => '',
          'multiple_number' => '',
          'multiple_to' => '',
          'show_remaining_days' => false,
        ),
        'type' => 'date_default',
        'weight' => 134,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'When will the total generated load of the agglomeration be collected through collecting systems or adressed through IAS?',
    'required' => 0,
    'settings' => 
    array (
      'default_value' => 'now',
      'default_value2' => 'same',
      'default_value_code' => '',
      'default_value_code2' => '',
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'date',
      'settings' => 
      array (
        'increment' => 1,
        'input_format' => 'd/m/Y - H:i:s',
        'input_format_custom' => '',
        'label_position' => 'above',
        'text_parts' => 
        array (
        ),
        'year_range' => '-3:+3',
      ),
      'type' => 'date_text',
      'weight' => '91',
    ),
    'id' => '1136',
    'field_id' => '1031',
    'field_name' => 'field_aggforecast',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggendlife' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'above',
        'module' => 'date',
        'settings' => 
        array (
          'format_type' => 'long',
          'fromto' => 'both',
          'multiple_from' => '',
          'multiple_number' => '',
          'multiple_to' => '',
          'show_remaining_days' => false,
        ),
        'type' => 'date_default',
        'weight' => 139,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Agglomeration end life',
    'required' => false,
    'settings' => 
    array (
      'default_value' => 'now',
      'default_value2' => 'same',
      'default_value_code' => '',
      'default_value_code2' => '',
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'module' => 'text',
      'settings' => 
      array (
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => '95',
    ),
    'id' => '1133',
    'field_id' => '1028',
    'field_name' => 'field_aggendlife',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggdatecompliance5' => 
  array (
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'date',
        'settings' => 
        array (
          'format_type' => 'long',
          'fromto' => 'both',
          'multiple_from' => '',
          'multiple_number' => '',
          'multiple_to' => '',
          'show_remaining_days' => false,
        ),
        'type' => 'date_default',
        'weight' => 79,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'date of compliance for article 5',
    'required' => 0,
    'settings' => 
    array (
      'default_value' => 'now',
      'default_value2' => 'same',
      'default_value_code' => '',
      'default_value_code2' => '',
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'date',
      'settings' => 
      array (
        'increment' => 1,
        'input_format' => 'm/d/Y - H:i:s',
        'input_format_custom' => '',
        'label_position' => 'above',
        'text_parts' => 
        array (
        ),
        'year_range' => '-3:+3',
      ),
      'type' => 'date_text',
      'weight' => '31',
    ),
    'id' => '1130',
    'field_id' => '1025',
    'field_name' => 'field_aggdatecompliance5',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggdatecompliance4' => 
  array (
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'date',
        'settings' => 
        array (
          'format_type' => 'long',
          'fromto' => 'both',
          'multiple_from' => '',
          'multiple_number' => '',
          'multiple_to' => '',
          'show_remaining_days' => false,
        ),
        'type' => 'date_default',
        'weight' => 77,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'date of compliance for article 4',
    'required' => 0,
    'settings' => 
    array (
      'default_value' => 'now',
      'default_value2' => 'same',
      'default_value_code' => '',
      'default_value_code2' => '',
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'date',
      'settings' => 
      array (
        'increment' => 1,
        'input_format' => 'm/d/Y - H:i:s',
        'input_format_custom' => '',
        'label_position' => 'above',
        'text_parts' => 
        array (
        ),
        'year_range' => '-3:+3',
      ),
      'type' => 'date_text',
      'weight' => '29',
    ),
    'id' => '1129',
    'field_id' => '1024',
    'field_name' => 'field_aggdatecompliance4',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggdateexported' => 
  array (
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'date',
        'settings' => 
        array (
          'format_type' => 'long',
          'fromto' => 'both',
          'multiple_from' => '',
          'multiple_number' => '',
          'multiple_to' => '',
          'show_remaining_days' => false,
        ),
        'type' => 'date_default',
        'weight' => 106,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Time of creation of correct export data set',
    'required' => 0,
    'settings' => 
    array (
      'default_value' => 'now',
      'default_value2' => 'same',
      'default_value_code' => '',
      'default_value_code2' => '',
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'date',
      'settings' => 
      array (
        'increment' => 1,
        'input_format' => 'm/d/Y - H:i:s',
        'input_format_custom' => '',
        'label_position' => 'above',
        'text_parts' => 
        array (
        ),
        'year_range' => '-3:+3',
      ),
      'type' => 'date_text',
      'weight' => '59',
    ),
    'id' => '1132',
    'field_id' => '1027',
    'field_name' => 'field_aggdateexported',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggaccoverflownumber' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'above',
        'module' => 'number',
        'settings' => 
        array (
          'decimal_separator' => '.',
          'prefix_suffix' => true,
          'scale' => 0,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_integer',
        'weight' => 133,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Indicate number of overflows',
    'required' => 0,
    'settings' => 
    array (
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 0,
      'module' => 'number',
      'settings' => 
      array (
      ),
      'type' => 'number',
      'weight' => '90',
    ),
    'id' => '1108',
    'field_id' => '1003',
    'field_name' => 'field_aggaccoverflownumber',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_aggsewagenetwork' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'text',
        'settings' => 
        array (
        ),
        'type' => 'text_default',
        'weight' => 91,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Type of sewage network',
    'required' => 0,
    'settings' => 
    array (
      'text_processing' => 0,
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'text',
      'settings' => 
      array (
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => '44',
    ),
    'id' => '1160',
    'field_id' => '1055',
    'field_name' => 'field_aggsewagenetwork',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_inspireidversionid' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'inline',
        'module' => 'text',
        'settings' => 
        array (
        ),
        'type' => 'text_default',
        'weight' => 13,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'inspireIdVersionId',
    'required' => 0,
    'settings' => 
    array (
      'text_processing' => 0,
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'text',
      'settings' => 
      array (
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => '7',
    ),
    'id' => '1179',
    'field_id' => '1073',
    'field_name' => 'field_inspireidversionid',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_compliance_explication' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'above',
        'module' => 'text',
        'settings' => 
        array (
        ),
        'type' => 'text_default',
        'weight' => 121,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Compliance explication',
    'required' => 0,
    'settings' => 
    array (
      'text_processing' => 0,
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'text',
      'settings' => 
      array (
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => '83',
    ),
    'id' => '1171',
    'field_id' => '1065',
    'field_name' => 'field_compliance_explication',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
  'field_article_5_compliance_expli' => 
  array (
    'default_value' => NULL,
    'description' => '',
    'display' => 
    array (
      'default' => 
      array (
        'label' => 'above',
        'module' => 'text',
        'settings' => 
        array (
        ),
        'type' => 'text_default',
        'weight' => 124,
      ),
      'teaser' => 
      array (
        'label' => 'above',
        'settings' => 
        array (
        ),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'label' => 'Article 5 compliance explication',
    'required' => 0,
    'settings' => 
    array (
      'text_processing' => 0,
      'user_register_form' => false,
    ),
    'widget' => 
    array (
      'active' => 1,
      'module' => 'text',
      'settings' => 
      array (
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => '86',
    ),
    'id' => '1168',
    'field_id' => '1062',
    'field_name' => 'field_article_5_compliance_expli',
    'entity_type' => 'node',
    'bundle' => 'agglomeration',
    'deleted' => '0',
  ),
);