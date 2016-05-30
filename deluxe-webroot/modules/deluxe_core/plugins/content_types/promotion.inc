<?php



$plugin = array(
    'single' => TRUE,
    'icon' => 'icon_node_form.png',
    'title' => t('Tenant Plugin'),
    'description' => t('Give promotion markup for the products from its catalog it'),
    'category' => t('Deluxe'),
    'required context' => new ctools_context_required(t('Node'), 'node'),
    'render callback' => 'deluxe_core_promotion_render',
    'edit form' => 'deluxe_core_promotion_edit_form',
);


function deluxe_core_promotion_render($subtype, $conf, $panel_args, &$context) {
  $block = new stdClass();
  $variables = array();
  $attributes = array();
  $block ->title = "";
  $node = $context->data;
  if(isset($node->field_select_product['und'])) {
    $tanent = isset($node->field_select_product['und']) ? $node->field_select_product['und'][0]['node']->field_tanents['und'] : $node->field_tanents['und'];
    $catalog_info = _deluxe_core_tenantinfo($tanent);
    $catalog_id = isset($catalog_info['catalog_id']) ? $catalog_info['catalog_id'] : NULL;
  }
  else if (isset($node->field_select_product_category) && !empty($node->field_category_id['und'])) {
    $category_id = $node->field_category_id['und'][0]['value'];
    $catalog_id = _deluxe_promotion_get_catalogids_from_category_id($category_id);
  }
   if(isset($catalog_id)) {
    $promotion = _deluxe_promotion_get_max_promo_for_catalog($catalog_id);
    if (!empty($promotion['Discount'])) {
        $build = array();
        $endDate = format_date(strtotime($promotion['EndDate']) ,'custom','m.d.y');
        $build[0]['#markup'] = '<div class="label-start"></div>
                                <div class="label-content">
                                  <span class="promo-value">' .$promotion['Discount'] . ' % Off</span>
                                  <span class= "promo-date"> Ends ' .$endDate . '</span>
                                  </div><div class="label-end"></div>';
        $buid[0]['#items'][0]['value'] = $build[0]['#markup'];
        $block->content = $build;
        return  $block;
      }
   }


}


function deluxe_core_promotion_edit_form($form, &$form_state) {
  return $form;
}
