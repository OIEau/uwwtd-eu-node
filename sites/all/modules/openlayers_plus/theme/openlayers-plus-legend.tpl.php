<?php
/**
 * @file
 * Legend template.
 */

/**
 * @param $layer_id The layer's id
 * @param $layer layer array
 * @param $legend an array of legend items
 */
?>
<script type"text/javascript">
  if(jQuery(".legend-item").length > 0 && jQuery(".toggleLegend").html() == "[ + ]") {
    jQuery(".toggleLegend").html("[ - ]");
  }

  removeDuplicateLegend();

  function removeDuplicateLegend() {
    var i = 0;
    jQuery('.toggleLegend').each(function(){
      if(i > 0) {
        jQuery(this).remove();
      }
      i++;        
    });
  }

  function toggleLegend() {
    removeDuplicateLegend();
    
    if(jQuery(".toggleLegend").html() == "[ - ]") {
      jQuery(".toggleLegend").html("[ + ]");
      jQuery("div.openlayers-legends .legend").hide("slow");
    } else {
      jQuery(".toggleLegend").html("[ - ]");
      jQuery("div.openlayers-legends .legend").show("slow");
    }
  }
</script>
<a onclick="toggleLegend();" class="toggleLegend">[ - ]</a>
<div class='legend legend-count-<?php print count($legend) ?> clear-block' id='openlayers-legend-<?php print $layer_id ?>'>
  <?php foreach ($legend as $key => $item): ?>
    <?php if (!empty($item['data']['fillColor']) && !empty($item['data']['strokeColor']) && !isset($item['data']['externalGraphic'])): ?>    
        <div class="legend-item clear-block">
          <!-- <span style="background-color:<?php print check_plain($item['data']['fillColor']) ?>;border:1px solid <?php print check_plain($item['data']['strokeColor']) ?>;width:20px;height:12px;float:left;margin-right:7px;"></span> -->
          <?php print check_plain($item['title']) ?>
        </div>
    <?php endif; ?>      
    <?php if (!empty($item['data']['externalGraphic'])): ?>    
      <div class="legend-item clear-block">
      <img class="swatch" src='<?php print file_create_url($item['data']['externalGraphic']); ?>' style='height: 15px; width: <?php print 'auto'; ?>'/>
      <?php if (!empty($layer['title'])): ?>
        <?php print check_plain($item['title']) ?>
      <?php endif; ?>
      </div>      
    <?php endif; ?>
  <?php endforeach; ?>
  <!--
  <svg style="float:left" height="25" width="25">
    <circle cx="12" cy="12" r="10" stroke="black" stroke-width="1" fill="white" />
  </svg>
  <div style="height: 30px;padding: 3px 0 0 27px;">Périmètre calculé</div>
  -->
</div>
