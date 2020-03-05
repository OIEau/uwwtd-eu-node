<?php 

$openlayers_maps = new stdClass();
$openlayers_maps->disabled = FALSE; /* Edit this to true to make a default openlayers_maps disabled initially */
$openlayers_maps->api_version = 1;
$openlayers_maps->name = 'dcp_reuse_map';
$openlayers_maps->title = 'Discharge points - Reuse';
$openlayers_maps->description = '2018/10/23 14:34:41
2017/02/24 15:19:04
2016/02/12 15:25:03
2016/01/20 16:23:11
2016/01/13 11:48:26';
$openlayers_maps->data = array(
  'width' => 'auto',
  'height' => '700px',
  'image_path' => 'sites/all/modules/openlayers/themes/default_white/img/',
  'css_path' => 'sites/all/modules/openlayers/themes/default_white/style.css',
  'proxy_host' => '',
  'hide_empty_map' => 0,
  'center' => array(
    'initial' => array(
      'centerpoint' => '-7.186510064978123e-9, 7.186501469422994e-9',
      'zoom' => '8',
    ),
    'restrict' => array(
      'restrictextent' => 0,
      'restrictedExtent' => '',
    ),
  ),
  'behaviors' => array(
    'openlayers_behavior_fullscreen' => array(
      'activated' => 0,
    ),
    'openlayers_behavior_wmsgetfeatureinfo' => array(
      'getfeatureinfo_usevisiblelayers' => 1,
      'getfeatureinfo_layers' => 'osm_mapnik',
      'getfeatureinfo_info_format' => 'application/geojson',
      'getfeatureinfo_highlight' => 0,
      'getfeatureinfo_htmlelement' => 'getfeatureinfo',
      'getfeatureinfo_properties' => '',
      'getfeatureinfo_feature_count' => '5',
      'getfeatureinfo_layer_oieau_rbdsu' => 'application/geojson',
      'getfeatureinfo_layer_oieau_rbd' => 'application/geojson',
      'getfeatureinfo_layer_oieau_eprtr_ptot' => 'application/geojson',
      'getfeatureinfo_layer_soe_nh3' => 'application/geojson',
      'getfeatureinfo_layer_wise_soe_nitrate' => 'application/geojson',
      'getfeatureinfo_layer_wise_soe_phosphorus' => 'application/geojson',
      'getfeatureinfo_layer_oieau_eprtr_ntot' => 'application/geojson',
      'getfeatureinfo_layer_oieau_nuts_0' => 'application/geojson',
      'getfeatureinfo_layer_oieau_eprtr_toc' => 'application/geojson',
      'getfeatureinfo_layer_soe_bod' => 'application/geojson',
      'getfeatureinfo_layer_bathing_water' => 'application/geojson',
      'getfeatureinfo_layer_oieau_nuts_1' => 'application/geojson',
      'getfeatureinfo_layer_oieau_nuts_2' => 'application/geojson',
      'getfeatureinfo_layer_natura_2000' => 'application/geojson',
      'getfeatureinfo_layer_corine_land_cover_2012' => 'application/geojson',
      'getfeatureinfo_layer_oieau_nuts_3' => 'application/geojson',
    ),
    'openlayers_behavior_wmsgetlegend' => array(
      'getlegend_htmlelement' => 'div.openlayers-legends',
    ),
    'openlayers_behavior_attribution' => array(
      'separator' => '; ',
    ),
    'openlayers_behavior_gazetteer' => array(
      'restriction_query' => 'country=BE',
    ),
    'openlayers_behavior_mouseposition' => array(
      'prefix' => 'Cursor position : ',
      'separator' => ', ',
      'suffix' => ' (EPSG:4326)',
      'numDigits' => '6',
      'emptyString' => '',
    ),
    'openlayers_behavior_navigation' => array(
      'zoomWheelEnabled' => 1,
      'zoomBoxEnabled' => 1,
      'documentDrag' => 0,
    ),
    'openlayers_plus_behavior_blockswitcher_plus' => array(
      'enabled' => 0,
      'open' => 1,
      'overlay_style' => 'checkbox',
      'sort_layers' => 1,
      'layers_dcp' => 1,
      'layers_dcp_groupname' => 'UWWTD',
      'layers_oieau_rbdsu' => 1,
      'layers_oieau_rbdsu_groupname' => 'Basins',
      'layers_oieau_rbd' => 1,
      'layers_oieau_rbd_groupname' => 'Basins',
      'layers_oieau_eprtr_ptot' => 1,
      'layers_oieau_eprtr_ptot_groupname' => 'EPRTR',
      'layers_soe_nh3' => 1,
      'layers_soe_nh3_groupname' => 'WISE SoE',
      'layers_wise_soe_nitrate' => 1,
      'layers_wise_soe_nitrate_groupname' => 'WISE SoE',
      'layers_wise_soe_phosphorus' => 1,
      'layers_wise_soe_phosphorus_groupname' => 'WISE SoE',
      'layers_oieau_eprtr_ntot' => 1,
      'layers_oieau_eprtr_ntot_groupname' => 'EPRTR',
      'layers_oieau_nuts_0' => 1,
      'layers_oieau_nuts_0_groupname' => 'Administrative units (NUTS)',
      'layers_oieau_eprtr_toc' => 1,
      'layers_oieau_eprtr_toc_groupname' => 'EPRTR',
      'layers_soe_bod' => 1,
      'layers_soe_bod_groupname' => 'WISE SoE',
      'layers_bathing_water' => 1,
      'layers_bathing_water_groupname' => 'Others',
      'layers_oieau_nuts_1' => 1,
      'layers_oieau_nuts_1_groupname' => 'Administrative units (NUTS)',
      'layers_oieau_nuts_2' => 1,
      'layers_oieau_nuts_2_groupname' => 'Administrative units (NUTS)',
      'layers_natura_2000' => 1,
      'layers_natura_2000_groupname' => 'Others',
      'layers_corine_land_cover_2012' => 1,
      'layers_corine_land_cover_2012_groupname' => 'Others',
      'layers_oieau_nuts_3' => 1,
      'layers_oieau_nuts_3_groupname' => 'Administrative units (NUTS)',
    ),
    'openlayers_plus_behavior_legend' => array(
      'layers' => array(
        'dcp' => 'dcp',
      ),
    ),
    'openlayers_plus_behavior_permalink' => array(),
    'openlayers_plus_behavior_scalepoints' => array(
      'min' => array(
        'value' => '0',
        'pointRadius' => '4',
        'fillOpacity' => '0.8',
        'strokeWidth' => '1',
      ),
      'max' => array(
        'value' => '100000',
        'pointRadius' => '15',
        'fillOpacity' => '0.8',
        'strokeWidth' => '1',
      ),
      'distinct' => '4',
      'arbitrary_classes' => '0|2000
2000|10000
10000|150000
150000|',
      'method' => 'area',
      'layers' => array(
        'dcp' => 'dcp',
      ),
      'fields' => 'field_uwwwastewatertreated_value',
      'min_label' => '',
      'fields_colors' => 'field_dcpirrigation_value_format',
      'fields_colors_values' => 'Irrigation|Irrigation|#459436
Infiltration|Industry|#334D5C
Other|Other|#02658C',
    ),
    'openlayers_behavior_panzoombar' => array(
      'zoomWorldIcon' => 0,
      'panIcons' => 1,
    ),
    'openlayers_behavior_popup' => array(
      'layers' => array(
        'dcp' => 'dcp',
      ),
      'panMapIfOutOfView' => 0,
      'keepInMap' => 1,
      'zoomToPoint' => 0,
      'zoomToCluster' => 0,
    ),
    'openlayers_behavior_scaleline' => array(),
    'openlayers_behavior_zoomtolayer' => array(
      'zoomtolayer' => array(
        'dcp' => 'dcp',
        'osm_mapnik' => 0,
        'osm_cycle' => 0,
        'oieau_rbdsu' => 0,
        'oieau_rbd' => 0,
        'oieau_eprtr_ptot' => 0,
        'soe_nh3' => 0,
        'wise_soe_nitrate' => 0,
        'wise_soe_phosphorus' => 0,
        'oieau_eprtr_ntot' => 0,
        'oieau_nuts_0' => 0,
        'oieau_eprtr_toc' => 0,
        'soe_bod' => 0,
        'bathing_water' => 0,
        'oieau_nuts_1' => 0,
        'oieau_nuts_2' => 0,
        'natura_2000' => 0,
        'corine_land_cover_2012' => 0,
        'oieau_nuts_3' => 0,
      ),
      'point_zoom_level' => '8',
      'zoomtolayer_scale' => '1',
    ),
  ),
  'default_layer' => 'osm_mapnik',
  'layers' => array(
    'osm_mapnik' => 'osm_mapnik',
    'osm_cycle' => 'osm_cycle',
    'dcp' => 'dcp',
    'oieau_rbdsu' => 'oieau_rbdsu',
    'oieau_rbd' => 'oieau_rbd',
    'oieau_eprtr_ntot' => 'oieau_eprtr_ntot',
    'soe_bod' => 'soe_bod',
    'oieau_eprtr_toc' => 'oieau_eprtr_toc',
    'oieau_nuts_0' => 'oieau_nuts_0',
    'soe_nh3' => 'soe_nh3',
    'wise_soe_phosphorus' => 'wise_soe_phosphorus',
    'wise_soe_nitrate' => 'wise_soe_nitrate',
    'oieau_eprtr_ptot' => 'oieau_eprtr_ptot',
    'bathing_water' => 'bathing_water',
    'oieau_nuts_1' => 'oieau_nuts_1',
    'oieau_nuts_2' => 'oieau_nuts_2',
    'corine_land_cover_2012' => 'corine_land_cover_2012',
    'natura_2000' => 'natura_2000',
    'oieau_nuts_3' => 'oieau_nuts_3',
  ),
  'layer_weight' => array(
    'uwwtp_n_pressure_' => '0',
    'uwwtp_bod_pressure_' => '0',
    'dcp' => '0',
    'wms_highlight_layer' => '0',
    'waste_water_network_openlayers_3' => '0',
    'waste_water_network_openlayers_2' => '0',
    'waste_water_network_openlayers_1' => '0',
    'uwwtp_treatment_openlayers_2' => '0',
    'uwwtp_p_pressure_' => '0',
    'agglomeration_conformity_openlayers_1' => '0',
    'agglomeration_openlayers_1' => '0',
    'openlayers_geojson_picture_this' => '0',
    'openlayers_kml_example' => '0',
    'geofield_formatter' => '0',
    'test_receiving_areas_openlayers_1' => '0',
    'uwwtp_compliance_map' => '0',
    'uwwtp' => '0',
    'rca' => '0',
    'compliance_map' => '0',
    'agglomeration_treatment' => '0',
    'uwwtp_treatment' => '0',
    'uwwtp_cod_pressure_' => '0',
    'agglomerations' => '0',
    'soe_nitrates_2011' => '0',
    'soe_phosphate_2011' => '0',
    'oieau_rbd_rbdsu' => '5',
    'oieau_rbdsu' => '5',
    'oieau_rbd' => '5',
    'oieau_nuts' => '6',
    'oieau_eprtr_ntot' => '6',
    'soe_bod' => '6',
    'oieau_eprtr_toc' => '6',
    'oieau_nuts_0' => '6',
    'soe_nh3' => '6',
    'wise_soe_phosphorus' => '6',
    'wise_soe_nitrate' => '6',
    'oieau_eprtr_ptot' => '6',
    'bathing_water' => '7',
    'oieau_nuts_1' => '7',
    'soe_monitoring_stations' => '8',
    'oieau_nuts_2' => '8',
    'corine_land_cover_2012' => '9',
    'uwwtp_map_openlayers_1' => '9',
    'natura_2000' => '9',
    'oieau_nuts_3' => '9',
  ),
  'layer_styles' => array(
    'uwwtp_n_pressure_' => '0',
    'uwwtp_p_pressure_' => '0',
    'agglomerations' => '0',
    'compliance_map' => '0',
    'agglomeration_treatment' => '0',
    'uwwtp_treatment' => '0',
    'uwwtp_cod_pressure_' => '0',
    'uwwtp' => '0',
    'oieau_nuts' => '0',
    'oieau_rbd_rbdsu' => '0',
    'soe_monitoring_stations' => '0',
    'soe_nitrates_2011' => '0',
    'soe_phosphate_2011' => '0',
    'rca' => '0',
    'uwwtp_compliance_map' => '0',
    'uwwtp_bod_pressure_' => '0',
    'geofield_formatter' => '0',
    'openlayers_kml_example' => '0',
    'openlayers_geojson_picture_this' => '0',
    'agglomeration_openlayers_1' => '0',
    'agglomeration_conformity_openlayers_1' => '0',
    'test_receiving_areas_openlayers_1' => '0',
    'uwwtp_map_openlayers_1' => '0',
    'uwwtp_treatment_openlayers_2' => '0',
    'waste_water_network_openlayers_1' => '0',
    'waste_water_network_openlayers_2' => '0',
    'waste_water_network_openlayers_3' => '0',
    'wms_highlight_layer' => '0',
    'dcp' => '0',
    'oieau_rbdsu' => '0',
    'oieau_rbd' => '0',
    'oieau_eprtr_ptot' => '0',
    'soe_nh3' => '0',
    'wise_soe_nitrate' => '0',
    'wise_soe_phosphorus' => '0',
    'oieau_eprtr_ntot' => '0',
    'oieau_nuts_0' => '0',
    'oieau_eprtr_toc' => '0',
    'soe_bod' => '0',
    'bathing_water' => '0',
    'oieau_nuts_1' => '0',
    'oieau_nuts_2' => '0',
    'natura_2000' => '0',
    'corine_land_cover_2012' => '0',
    'oieau_nuts_3' => '0',
  ),
  'layer_styles_select' => array(
    'uwwtp_n_pressure_' => '0',
    'uwwtp_p_pressure_' => '0',
    'agglomerations' => '0',
    'compliance_map' => '0',
    'agglomeration_treatment' => '0',
    'uwwtp_treatment' => '0',
    'uwwtp_cod_pressure_' => '0',
    'uwwtp' => '0',
    'oieau_nuts' => '0',
    'oieau_rbd_rbdsu' => '0',
    'soe_monitoring_stations' => '0',
    'soe_nitrates_2011' => '0',
    'soe_phosphate_2011' => '0',
    'rca' => '0',
    'uwwtp_compliance_map' => '0',
    'uwwtp_bod_pressure_' => '0',
    'geofield_formatter' => '0',
    'openlayers_kml_example' => '0',
    'openlayers_geojson_picture_this' => '0',
    'agglomeration_openlayers_1' => '0',
    'agglomeration_conformity_openlayers_1' => '0',
    'test_receiving_areas_openlayers_1' => '0',
    'uwwtp_map_openlayers_1' => '0',
    'uwwtp_treatment_openlayers_2' => '0',
    'waste_water_network_openlayers_1' => '0',
    'waste_water_network_openlayers_2' => '0',
    'waste_water_network_openlayers_3' => '0',
    'wms_highlight_layer' => '0',
    'dcp' => '0',
    'oieau_rbdsu' => '0',
    'oieau_rbd' => '0',
    'oieau_eprtr_ptot' => '0',
    'soe_nh3' => '0',
    'wise_soe_nitrate' => '0',
    'wise_soe_phosphorus' => '0',
    'oieau_eprtr_ntot' => '0',
    'oieau_nuts_0' => '0',
    'oieau_eprtr_toc' => '0',
    'soe_bod' => '0',
    'bathing_water' => '0',
    'oieau_nuts_1' => '0',
    'oieau_nuts_2' => '0',
    'natura_2000' => '0',
    'corine_land_cover_2012' => '0',
    'oieau_nuts_3' => '0',
  ),
  'layer_styles_temporary' => array(
    'uwwtp_n_pressure_' => '0',
    'uwwtp_p_pressure_' => '0',
    'agglomerations' => '0',
    'compliance_map' => '0',
    'agglomeration_treatment' => '0',
    'uwwtp_treatment' => '0',
    'uwwtp_cod_pressure_' => '0',
    'uwwtp' => '0',
    'oieau_nuts' => '0',
    'oieau_rbd_rbdsu' => '0',
    'soe_monitoring_stations' => '0',
    'soe_nitrates_2011' => '0',
    'soe_phosphate_2011' => '0',
    'rca' => '0',
    'uwwtp_compliance_map' => '0',
    'uwwtp_bod_pressure_' => '0',
    'geofield_formatter' => '0',
    'openlayers_kml_example' => '0',
    'openlayers_geojson_picture_this' => '0',
    'agglomeration_openlayers_1' => '0',
    'agglomeration_conformity_openlayers_1' => '0',
    'test_receiving_areas_openlayers_1' => '0',
    'uwwtp_map_openlayers_1' => '0',
    'uwwtp_treatment_openlayers_2' => '0',
    'waste_water_network_openlayers_1' => '0',
    'waste_water_network_openlayers_2' => '0',
    'waste_water_network_openlayers_3' => '0',
    'wms_highlight_layer' => '0',
    'dcp' => '0',
    'oieau_rbdsu' => '0',
    'oieau_rbd' => '0',
    'oieau_eprtr_ptot' => '0',
    'soe_nh3' => '0',
    'wise_soe_nitrate' => '0',
    'wise_soe_phosphorus' => '0',
    'oieau_eprtr_ntot' => '0',
    'oieau_nuts_0' => '0',
    'oieau_eprtr_toc' => '0',
    'soe_bod' => '0',
    'bathing_water' => '0',
    'oieau_nuts_1' => '0',
    'oieau_nuts_2' => '0',
    'natura_2000' => '0',
    'corine_land_cover_2012' => '0',
    'oieau_nuts_3' => '0',
  ),
  'layer_activated' => array(
    'dcp' => 'dcp',
    'uwwtp_n_pressure_' => 0,
    'uwwtp_p_pressure_' => 0,
    'agglomerations' => 0,
    'compliance_map' => 0,
    'agglomeration_treatment' => 0,
    'uwwtp_treatment' => 0,
    'uwwtp_cod_pressure_' => 0,
    'oieau_nuts_0' => 0,
    'oieau_nuts_2' => 0,
    'oieau_rbd' => 0,
    'oieau_eprtr_ntot' => 0,
    'oieau_eprtr_toc' => 0,
    'uwwtp' => 0,
    'oieau_nuts' => 0,
    'oieau_rbd_rbdsu' => 0,
    'natura_2000' => 0,
    'soe_monitoring_stations' => 0,
    'soe_nitrates_2011' => 0,
    'soe_phosphate_2011' => 0,
    'soe_nh3' => 0,
    'wise_soe_phosphorus' => 0,
    'rca' => 0,
    'uwwtp_compliance_map' => 0,
    'uwwtp_bod_pressure_' => 0,
    'oieau_nuts_1' => 0,
    'oieau_nuts_3' => 0,
    'oieau_rbdsu' => 0,
    'oieau_eprtr_ptot' => 0,
    'bathing_water' => 0,
    'corine_land_cover_2012' => 0,
    'soe_bod' => 0,
    'wise_soe_nitrate' => 0,
    'geofield_formatter' => 0,
    'openlayers_kml_example' => 0,
    'openlayers_geojson_picture_this' => 0,
    'agglomeration_openlayers_1' => 0,
    'agglomeration_conformity_openlayers_1' => 0,
    'test_receiving_areas_openlayers_1' => 0,
    'uwwtp_map_openlayers_1' => 0,
    'uwwtp_treatment_openlayers_2' => 0,
    'waste_water_network_openlayers_1' => 0,
    'waste_water_network_openlayers_2' => 0,
    'waste_water_network_openlayers_3' => 0,
    'wms_highlight_layer' => 0,
  ),
  'layer_switcher' => array(
    'dcp' => 'dcp',
    'oieau_rbdsu' => 'oieau_rbdsu',
    'oieau_rbd' => 'oieau_rbd',
    'oieau_eprtr_ptot' => 'oieau_eprtr_ptot',
    'soe_nh3' => 'soe_nh3',
    'wise_soe_nitrate' => 'wise_soe_nitrate',
    'wise_soe_phosphorus' => 'wise_soe_phosphorus',
    'oieau_eprtr_ntot' => 'oieau_eprtr_ntot',
    'oieau_nuts_0' => 'oieau_nuts_0',
    'oieau_eprtr_toc' => 'oieau_eprtr_toc',
    'soe_bod' => 'soe_bod',
    'bathing_water' => 'bathing_water',
    'oieau_nuts_1' => 'oieau_nuts_1',
    'oieau_nuts_2' => 'oieau_nuts_2',
    'natura_2000' => 'natura_2000',
    'corine_land_cover_2012' => 'corine_land_cover_2012',
    'oieau_nuts_3' => 'oieau_nuts_3',
    'uwwtp_n_pressure_' => 0,
    'uwwtp_p_pressure_' => 0,
    'agglomerations' => 0,
    'compliance_map' => 0,
    'agglomeration_treatment' => 0,
    'uwwtp_treatment' => 0,
    'uwwtp_cod_pressure_' => 0,
    'uwwtp' => 0,
    'oieau_nuts' => 0,
    'oieau_rbd_rbdsu' => 0,
    'soe_monitoring_stations' => 0,
    'soe_nitrates_2011' => 0,
    'soe_phosphate_2011' => 0,
    'rca' => 0,
    'uwwtp_compliance_map' => 0,
    'uwwtp_bod_pressure_' => 0,
    'geofield_formatter' => 0,
    'openlayers_kml_example' => 0,
    'openlayers_geojson_picture_this' => 0,
    'agglomeration_openlayers_1' => 0,
    'agglomeration_conformity_openlayers_1' => 0,
    'test_receiving_areas_openlayers_1' => 0,
    'uwwtp_map_openlayers_1' => 0,
    'uwwtp_treatment_openlayers_2' => 0,
    'waste_water_network_openlayers_1' => 0,
    'waste_water_network_openlayers_2' => 0,
    'waste_water_network_openlayers_3' => 0,
    'wms_highlight_layer' => 0,
  ),
  'projection' => 'EPSG:3857',
  'displayProjection' => 'EPSG:4326',
  'styles' => array(
    'default' => 'default',
    'select' => 'default_select',
    'temporary' => 'default',
  ),
);