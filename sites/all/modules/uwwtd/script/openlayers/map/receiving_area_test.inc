<?php

$openlayers_maps = new stdClass();
$openlayers_maps->disabled = FALSE; /* Edit this to true to make a default openlayers_maps disabled initially */
$openlayers_maps->api_version = 1;
$openlayers_maps->name = 'receiving_area_test';
$openlayers_maps->title = 'receiving area test';
$openlayers_maps->description = date('Y-m-d H:i:s');
$openlayers_maps->data = array(
  'width' => 'auto',
  'height' => '400px',
  'image_path' => 'sites/all/modules/openlayers/themes/default_dark/img/',
  'css_path' => 'sites/all/modules/openlayers/themes/default_dark/style.css',
  'proxy_host' => '',
  'hide_empty_map' => 0,
  'center' => array(
    'initial' => array(
      'centerpoint' => '-8.437500005675144, 53.120405280654516',
      'zoom' => '6',
    ),
    'restrict' => array(
      'restrictextent' => 0,
      'restrictedExtent' => '',
    ),
  ),
  'behaviors' => array(
//     'openlayers_behavior_keyboarddefaults' => array(),     
    'openlayers_behavior_attribution' => array(
      'separator' => '',
    ),
    'openlayers_behavior_layerswitcher' => array(
      'ascending' => 1,
      'sortBaseLayer' => '0',
      'roundedCorner' => 1,
      'roundedCornerColor' => '#222222',
      'maximizeDefault' => 0,
      'div' => '',
    ),
    'openlayers_behavior_navigation' => array(
      'zoomWheelEnabled' => 1,
      'zoomBoxEnabled' => 1,
      'documentDrag' => 0,
    ),
    'openlayers_behavior_panzoombar' => array(
      'zoomWorldIcon' => 0,
      'panIcons' => 1,
    ),
    'openlayers_behavior_popup' => array(
      'layers' => array(
        'test_receiving_areas_openlayers_1' => 'test_receiving_areas_openlayers_1',
      ),
      'panMapIfOutOfView' => 0,
      'keepInMap' => 1,
      'zoomToPoint' => 0,
      'zoomToCluster' => 0,
    ),
  ),
  'default_layer' => 'osm_mapnik',
  'layers' => array(
    'google_satellite' => 'google_satellite',
    'google_hybrid' => 'google_hybrid',
    'google_normal' => 'google_normal',
    'test_receiving_areas_openlayers_1' => 'test_receiving_areas_openlayers_1',
  ),
  'layer_weight' => array(
    'uwwtp_map_openlayers_1' => '0',
    'agglomeration_openlayers_1' => '0',
    'uwwtp_treatment_openlayers_2' => '0',
    'postgis_formatter_layer' => '0',
    'test_receiving_areas_openlayers_1' => '0',
    'agglomeration_conformity_openlayers_1' => '0',
    'openlayers_geojson_picture_this' => '0',
    'waste_water_network_openlayers_2' => '0',
    'waste_water_network_openlayers_3' => '0',
    'geofield_formatter' => '0',
    'openlayers_kml_example' => '0',
    'waste_water_network_openlayers_1' => '0',
  ),
  'layer_styles' => array(
    'waste_water_network_openlayers_1' => '0',
    'waste_water_network_openlayers_2' => '0',
    'waste_water_network_openlayers_3' => '0',
    'geofield_formatter' => '0',
    'openlayers_kml_example' => '0',
    'openlayers_geojson_picture_this' => '0',
    'agglomeration_conformity_openlayers_1' => '0',
    'agglomeration_openlayers_1' => '0',
    'uwwtp_map_openlayers_1' => '0',
    'uwwtp_treatment_openlayers_2' => '0',
    'postgis_formatter_layer' => '0',
    'test_receiving_areas_openlayers_1' => 'waste_water_treatment_plant_style',
  ),
  'layer_styles_select' => array(
    'waste_water_network_openlayers_1' => '0',
    'waste_water_network_openlayers_2' => '0',
    'waste_water_network_openlayers_3' => '0',
    'geofield_formatter' => '0',
    'openlayers_kml_example' => '0',
    'openlayers_geojson_picture_this' => '0',
    'agglomeration_conformity_openlayers_1' => '0',
    'agglomeration_openlayers_1' => '0',
    'uwwtp_map_openlayers_1' => '0',
    'uwwtp_treatment_openlayers_2' => '0',
    'postgis_formatter_layer' => '0',
    'test_receiving_areas_openlayers_1' => 'waste_water_treatment_plant_style',
  ),
  'layer_styles_temporary' => array(
    'waste_water_network_openlayers_1' => '0',
    'waste_water_network_openlayers_2' => '0',
    'waste_water_network_openlayers_3' => '0',
    'geofield_formatter' => '0',
    'openlayers_kml_example' => '0',
    'openlayers_geojson_picture_this' => '0',
    'agglomeration_conformity_openlayers_1' => '0',
    'agglomeration_openlayers_1' => '0',
    'uwwtp_map_openlayers_1' => '0',
    'uwwtp_treatment_openlayers_2' => '0',
    'postgis_formatter_layer' => '0',
    'test_receiving_areas_openlayers_1' => 'waste_water_treatment_plant_style',
  ),
  'layer_activated' => array(
    'test_receiving_areas_openlayers_1' => 'test_receiving_areas_openlayers_1',
    'waste_water_network_openlayers_1' => 0,
    'waste_water_network_openlayers_2' => 0,
    'waste_water_network_openlayers_3' => 0,
    'geofield_formatter' => 0,
    'openlayers_kml_example' => 0,
    'openlayers_geojson_picture_this' => 0,
    'agglomeration_conformity_openlayers_1' => 0,
    'agglomeration_openlayers_1' => 0,
    'uwwtp_map_openlayers_1' => 0,
    'uwwtp_treatment_openlayers_2' => 0,
    'postgis_formatter_layer' => 0,
  ),
  'layer_switcher' => array(
    'test_receiving_areas_openlayers_1' => 'test_receiving_areas_openlayers_1',
    'waste_water_network_openlayers_1' => 0,
    'waste_water_network_openlayers_2' => 0,
    'waste_water_network_openlayers_3' => 0,
    'geofield_formatter' => 0,
    'openlayers_kml_example' => 0,
    'openlayers_geojson_picture_this' => 0,
    'agglomeration_conformity_openlayers_1' => 0,
    'agglomeration_openlayers_1' => 0,
    'uwwtp_map_openlayers_1' => 0,
    'uwwtp_treatment_openlayers_2' => 0,
    'postgis_formatter_layer' => 0,
  ),
  'projection' => 'EPSG:3857',
  'displayProjection' => 'EPSG:4326',
  'styles' => array(
    'default' => 'default',
    'select' => 'default_select',
    'temporary' => 'default',
  ),
);
