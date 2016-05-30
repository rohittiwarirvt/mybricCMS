<?php



$plugin = array(
  'single' => TRUE,
  'icon' => 'icon_node_form.png',
  'title' => t('Review Widget'),
  'description' => t('Get Reviews Widget From File API'),
  'category' => t('Deluxe'),
  'required context' => new ctools_context_required(t('Node'), 'node'),
  'render callback' => 'deluxe_core_review_widget_render',
  'admin info' => 'deluxe_core_review_widget_admin_info',
  'edit form' => 'deluxe_core_review_widget_edit_form',
);


function deluxe_core_review_widget_render($subtype, $conf, $panel_args, &$context) {

  drupal_add_css(drupal_get_path('module', 'deluxe_core') . '/css/review-style.css');
  drupal_add_js(drupal_get_path('module', 'deluxe_core') . '/js/review-js.js',array(
      'type' => 'file',
  ));
    drupal_add_js(drupal_get_path('module', 'deluxe_core') . '/js/scrollLoad.js',array(
      'type' => 'file',
  ));
  $block = new stdClass();
  $variables = array();
  $attributes = array();
  $block ->title = "";
  //print_r($context);

  $datainfo = $context->data;

  $review_widget_api = variable_get("design_review_widget", "http://design.psprint.com/reviewWidget");

  $nid = $datainfo->nid;

  $node_alias = str_replace('/reviews', '', drupal_get_path_alias("node/$nid")) ;

  $widget_bucket_types = variable_get('review_bucket_types',array('GENERAL' => 'reviews','RECOMMEND_US' => 'recommended-us', 'CUSTOMER_SERVICE' => 'customer-service', 'PRODUCT' => 'PRODUCT', 'Default' => 'Default'));
  $bucket = array_filter($widget_bucket_types, function($item) use ($node_alias) {
            if($item == $node_alias) {
              return TRUE;
            }
          });
    if($bucket) {
      $temp = array_keys($bucket);
      $bucket = current($temp);

    }
    else {
      $bucket = "/" . $node_alias;
    }

   $link = in_array($conf['widget_type'], array('lg-2l-stripe', 'lg-3l-stripe'))  ? 0 : 1 ;
   drupal_add_js(array('bucket_name' =>$bucket, "widget" => $conf['widget_type'] ), 'setting');
   $review_per_page ="";
   $review_id = "";
   if(isset($_GET['review_id'])){
      $options['review_id'] = $_GET['review_id'];
      $review_id =   $_GET['review_id'];

    }
    $review_id = "";
    $default_args = array(
    "1_CustomerReview",$bucket, $conf['widget_type'], $review_per_page, $link, $review_id
    );
    $key = implode("_", $default_args);
    $redis = _deluxe_core_predis_client();
    if (isset($redis)) {
      $result = _deluxe_core_predis_get($redis, $key);
    }
    if (isset($result)) {
      $build[0]['#markup'] =  "<div class='{$conf['widget_type']}'> $result</div>";
      $buid[0]['#items'][0]['value'] = $build[0]['#markup'];
      $block->content = $build;
      if(!empty($result))
        return  $block;
      }
      else {
       $replacements = array('@error' => "Redis", '@widget' => $conf['widget_type']);
       $message = 'Error @error  occured for @widget ';
       watchdog('reviews', $message, $replacements, WATCHDOG_ERROR);
      }
}





function deluxe_core_review_widget_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];
  // Review Widgets
  $widget_types = variable_get('review_widget_types', array('lg-stripe', 'md-stripe', 'md-boxed', 'lg-3l-stripe','md-stripe', 'md-2c-list', 'lg-2l-stripe', 'md-list','md-2c-g','lg-2l-stripe','md-boxed-list', 'lg-2l-stripe','md-2c-g-list'));

  $widget_types_options = drupal_map_assoc($widget_types);


  $form['widget_type'] =  array(
    '#type' => 'radios',
    '#title' => t("Select Review Widget"),
    '#default_value' => !empty($conf['widget_type']) ? $conf['widget_type'] : FALSE,
    '#options' => $widget_types_options,
    '#description' => t("Creates Pane for the Given Review Widget"),
    '#required' => TRUE,
    );

  return $form;
}

function deluxe_core_review_widget_edit_form_submit(&$form, &$form_state) {
  $form_state['conf']['widget_type'] = $form_state['values']['widget_type'];
}

function deluxe_core_review_widget_admin_info($subtype, $conf, $contexts) {
  if(!empty($conf)) {
    $bucket_widget_type = isset($conf['bucket_widget_type']) ? $conf['bucket_widget_type'] : NULL;
    $widget_type = isset($conf['widget_type']) ? $conf['widget_type'] : NULL;
    $block = new stdClass();
    $block ->title = t("@type widget @bucket", array('@type' => $widget_type, '@bucket' => $bucket_widget_type));
    $block ->content = t("Showing reivew @type widget", array('@type' => $widget_type, '@bucket' => $bucket_widget_type));
    return $block;
  }
}
