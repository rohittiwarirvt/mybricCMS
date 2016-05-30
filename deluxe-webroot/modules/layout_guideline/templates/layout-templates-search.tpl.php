<div class="views-widget-filter">
  <?php $pos = 0;  ?>
  <?php foreach ($templates_data['filter'] as $key => $filter_group):?>
    <?php $type = array_keys($filter_group); ?>
    <?php if (count($filter_group[$type[0]]) > 1): ?>

      <?php if (in_array(array_keys($filter_group), $filter_hide)):?>
        <?php $hide_class = "hideme";?>
      <?php else: ?>
        <?php $hide_class = "";?>
      <?php endif; ?>
      <div class="<?php print $key ." " . $hide_class; ?>">
      <?php foreach ($filter_group as $filter_key => $filter):?>
        <?php if ($result_count  < 9 ): ?>
          <?php if ($filter_key == 'File Type') : ?>
            <label id="filter-type"> <?php print $filter_key; ?> </label>
            <?php foreach ($filter as  $filter_options): ?>
              <?php  $filter_url = '~' . $filter_options['path']; ?>
              <div class="views-widget-option">
               <?php if (in_array($filter_options['path'],$filetype) ): ?>
                <?php $active = "class='active'";?>
              <?php else: $active="";?>
              <?php endif;?>
              <a <?php print  $active .' href=' . $current_url . $filter_url; ?>>
               <?php print $filter_options['name']; ?>
             </a>
           </div>
            <?php endforeach; ?>
          <?php endif; ?>
        <?php else:?>
        <label id="filter-type"> <?php print $filter_key; ?> </label>
          <?php foreach ($filter as  $filter_options): ?>
            <?php if (count($product_attributes) >= 2 && $filter_key != 'File Type'): ?>
              <?php  $filter_url =  _layout_guidelines_filter_path_url($filter_count, $pos, $filter_options['path'], $product_attributes, $default_options);?>
            <?php elseif ($filter_key == 'File Type'):?>
              <?php $filter_url = '~' . $filter_options['path'];?>
            <?php else:?>
              <?php $filter_url =  _layout_guidelines_filter_path_url($filter_count , $pos, $filter_options['path'], $filetype, $default_options); ?>
            <?php endif;?>
          <div class="views-widget-option">
            <?php if (in_array($filter_options['path'], $product_attributes) || in_array($filter_options['path'],$filetype)): ?>
              <?php $active = "class='active'";?>
            <?php elseif ((!in_array($filter_options['path'], $product_attributes) && count($product_attributes)<2) && in_array($filter_options['path'], $default_options)): ?>
              <?php $active = "class='active'";?>
            <?php else:?>
              <?php $active="";?>
            <?php endif;?>
              <a <?php print  $active .' href=' . $current_url . $filter_url; ?>>
              <?php print $filter_options['name']; ?>
              </a>
          </div>
          <?php endforeach; ?>
        <?php endif;?>
        <?php $pos++; ?>
      <?php endforeach; ?>
      </div>
    <?php endif; ?>
  <?php endforeach; ?>
</div>
<div class="search-result-wrapper">
  <?php if (isset($templates_data['groupby'])): ?>
    <?php $row =0;?>
    <div>
      <?php foreach ($templates_data['result'] as  $key =>$values): ?>
        <div class="group-by group_<?php print $row; $row++ ?> " >
          <div class="title-wrapper"><h2 class="left">By <?php print key($templates_data['filter'][$key]) .' - '. strtoupper($filetype[0]);  ?></h2></div>
          <?php $n =0;?>
          <?php  foreach ($values as $value):?>
            <?php if ($n == 0):?>
              <?php print '<div class="row-wrapper">';?>
            <?php endif;?>
            <?php $term_name_vid = get_filter_name_by_tid($value->{$key}['und'][0]['tid']) ;?>
            <?php $res = get_filter_path_by_tid($value->{$key}['und'][0]['tid']); ?>
            <?php $pos = array_search($key, array_keys($templates_data['filter'])); ?>
            <?php  $filter_options['path'] = $res['field_layout_guideline_url_value']; ?>
            <?php $url = _layout_guidelines_filter_path_url($filter_count, $pos, $filter_options['path'], $filetype, $default_options); ?>
            <?php $layout_image = get_image_url_path($value->field_layout_image['und']['0']['uri']); ?>
            <?php  $template_image_rollover = get_image_url_path($value->field_layout_image_rollover['und']['0']['uri']); ?>
            <?php $img_alt = isset($value->dynamic_alt) ? $value->dynamic_alt :""; ?>
            <div class="full-cell-wrapper full-cell-<?php print $key ?>">
              <div class="views-field views-field-field-prollover-image ">
                <div class="field-content">
                  <a href="<?php print $current_url . $url;?>">
                    <img src="<?php print $template_image_rollover; ?>" class="rollover hideme" alt='<?php print $img_alt ?>' title='<?php print $img_alt ?>' width="230" height="157">
                  </a>
                </div>
              </div>
              <div class="views-field views-field-field-product-image">
                <div class="field-content">
                  <a href="<?php print $current_url . $url; ?>">
                   <img src="<?php print $layout_image; ?>" class="nonrollover" alt='<?php print $img_alt ?>' title='<?php print $img_alt ?>'  width="230" height="157">
                 </a>
               </div>
             </div>
             <div class="views-field views-field-title">
              <span class="field-content">
                <a href="<?php print $current_url . $url  ?>"> <?php print $term_name_vid['name']; ?> </a>
              </span>
            </div>
          </div>
            <?php $n=$n+1; ?>
            <?php if ($n == 3): ?>
              <?php  print "</div>"; $n=0; ?>
            <?php endif;?>
          <?php endforeach; ?>
          <?php if ($n != 0): ?>
            <?php  print "</div>"; $n=0; ?>
          <?php endif;?>
      </div>
    <?php endforeach; ?>
  </div>
<?php elseif (isset($templates_data['result'])): ?>
  <div>
    <div class="group-by" >
      <div class="title-wrapper"><h1 class="left"> <?php print $label; ?></h1></div>
      <?php $n = 0;?>
      <?php foreach ($templates_data['result'] as $key => $data): ?>
        <?php if ($n == 0):?>
          <?php print '<div class="row-wrapper">';?>
        <?php endif;?>
        <?php $ftype = (isset($arg[1]) && !empty($arg[1])) ? $arg[1] : ''?>
        <?php  switch ($ftype) {
          case 'psd':
          $url = get_image_url_path($data->field_layout_psd_file['und']['0']['uri']);
          break;
          case 'ai':
          $url = get_image_url_path($data->field_layout_ai_file['und']['0']['uri']);
          break;
          case 'indesign':
          $url = get_image_url_path($data->field_layout_indesign_file['und']['0']['uri']);
          break;
          default:
          $url = get_image_url_path($data->field_layout_pdf_file['und']['0']['uri']);
          break;
        } ?>
        <?php $layout_image = get_image_url_path($data->field_layout_image['und']['0']['uri']); ?>
        <?php  $template_image_rollover = get_image_url_path($data->field_layout_image_rollover['und']['0']['uri']); ?>
        <?php $img_alt = isset($data->dynamic_alt) ? $data->dynamic_alt :""; ?>
        <div class="full-cell-wrapper full-cell-<?php print $key ?>">
          <div class="views-field views-field-field-prollover-image ">
            <div class="field-content">
              <a href="<?php print $url;?>">
                <img src="<?php print $template_image_rollover; ?>" class="rollover hideme" alt='<?php print $img_alt ?>' title='<?php print $img_alt ?>' width="230" height="157">
              </a>
            </div>
          </div>
          <div class="views-field views-field-field-product-image">
            <div class="field-content">
              <a href="<?php print $url; ?>">
               <img src="<?php print $layout_image; ?>" class="nonrollover" alt='<?php print $img_alt ?>' title='<?php print $img_alt ?>'  width="230" height="157">
             </a>
           </div>
         </div>
         <div class="views-field views-field-title">
          <span class="field-content">
            <a href="<?php print $url;  ?>"> <?php print $data->title ?> </a>
          </span>
        </div>
      </div>
      <?php $n = $n+1; ?>
      <?php if ($n == 3): ?>
        <?php  print "</div>"; $n = 0; ?>
      <?php endif;?>
    <?php endforeach;?>
    <?php if ($n != 0): ?>
      <?php  print "</div>"; $n = 0; ?>
    <?php endif;?>
  </div>
</div>
<?php else:?>
  <div class="view-empty"><p>Sorry no templates available for selected options.</p></div>
<?php endif;?>
</div>
