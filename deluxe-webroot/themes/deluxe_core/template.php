<?php

/**
 * @file
 * This file is empty by default because the base theme chain (Alpha & Omega) provides
 * all the basic functionality. However, in case you wish   to customize the output that Drupal
 * generates through Alpha & Omega this file is a good place to do so.
 *
 * Alpha comes with a neat solution for keeping this file as clean as possible while the code
 * for your subtheme grows. Please read the README.txt in the /preprocess and /process subfolders
 * for more information on this topic.
 */

function deluxe_core_preprocess_html(&$vars) {
  $tanent_info = &drupal_static('tanent_info');
  $vars['classes_array'][] = 'domain-' . strtolower($tanent_info['community']);
  drupal_add_css(drupal_get_path('theme', 'deluxe_core') . '/css/global-'. strtolower($tanent_info['community']) . '.css');
  if ($tanent_info['community_id'] == 1) {
    drupal_add_js(drupal_get_path('theme', 'deluxe_core') . '/js/global-'. strtolower($tanent_info['community']) . '.js', array('weight' => -15));
  }

  $pagetitle = &drupal_static('page_title');
  $vars['head_title'] = strip_tags($pagetitle);
  // Added nodeclass into body tag
  $node = menu_get_object();
  if(isset($node)) {
     $node_class = node_class($node);
     $vars['classes_array'][] = $node_class;
  }
  // Body class for resources front page
  if($_GET['q']=="resources" && !isset($_GET['page'])) {
    $vars['classes_array'][] = 'resources-front';
  }
}

function deluxe_core_breadcrumb($variables) {
  $breadcrumbs_variables = _deluxe_core_initialize_breadcrumbs();
  $node = $breadcrumbs_variables['node'];
  if(isset($node) && ($node->type == 'product' || $node->type == "rating_reviews")) {
    $variables['breadcrumb'] = _deluxe_core_generate_breadcrumb($node);
  }
  else if (arg(0) == 'layout-templates') {
    $variables['breadcrumb'] =_deluxe_core_generate_breadcrumb_lgpages();
  }
  else{
    unset($variables['breadcrumb']);
  }
  if(!empty($variables['breadcrumb'])) {
    if(isset($node) && isset($node->is_review)){
      return $variables['breadcrumb'];

    } else {
      return '<div itemscope itemtype="http://schema.org/WebPage"><div class="breadcrumb"  itemprop="breadcrumb">' . implode(' &gt; ',$variables['breadcrumb']) . '</div></div>';
    }
  }
}

/**
  *  To overide the functionality of default flexslider to attach video link
 */
function deluxe_core_flexslider_list_item(&$vars) {
  $tanent_info = &drupal_static('tanent_info');
    ctools_include('ajax');
    ctools_include('modal');
    ctools_modal_add_js();
    static $i = 1;

    if($i == 1) {
      $doc = new DOMDocument();
      @$doc->loadHTML($vars['item']);
      $imageTags = $doc->getElementsByTagName('img');
      foreach($imageTags as $tag){
          $imgsrc =  $tag->getAttribute('src');
          $imgalt =  $tag->getAttribute('alt');
          $imgwidth = $tag->getAttribute('width');
          $imgheight = $tag->getAttribute('height');
          $imgtitle = $tag->getAttribute('title');
      }
    if ( $tanent_info['community_id'] == 13){
       $vars['item'] = '<div class="views-field views-field-field-banner"> <div class="field-content">
        <img src="'. $imgsrc.'" width="'.$imgwidth .'" height="'.$imgwidth.'" alt="'.$imgalt.'" title="'.$imgtitle.'" usemap="#Image-Map-dfs-welcome" />
        <map name="Image-Map-dfs-welcome" id="Image-Map-dfs-welcome">
        <area alt="" title="" href="/node/nojs/video" shape="rect" coords="650,213,769,337" style="outline: none;" target="_self" class="ctools-use-modal ctools-modal-modal-popup-small " />
        <area shape="rect" coords="803,368,805,370" alt="Image Map" style="outline: none;" title="Image Map" href="/node/nojs/video" class="ctools-use-modal ctools-modal-modal-popup-small" /> </map>
        </div> </div>';
      }
    }
  $i++;
  return '<li' . drupal_attributes($vars['settings']['attributes']) . '>' . $vars['item'] . $vars['caption'] . "</li>\n";
}

/* Generate seo data tags for website*/
function deluxe_core_preprocess_page(&$variables){
  /* add SEO meta tags on page id basichead_title*/
  /*update site_name varible as per current community*/



  $site_name = _deluxe_core_get_domain();
  $community_info = _deluxe_core_community_code($site_name);
  if ($variables['is_front'] == FALSE):
  $metaifo = _seo_data_display_generate_tags();
  $i = 0;
  $page_keywords = array();
  $pagetitle = &drupal_static('page_title');
  $pagetitle = $metaifo['page_title'];
  unset($metaifo['page_title']);
  foreach($metaifo as $key => $meta_tag){
    $meta_keys = array_keys($meta_tag);
    $meta_meta_links = current($meta_keys);
    $meta_name = next($meta_keys);
    $meta_content = next($meta_keys);
    $meta_page_data[$i] = array(
        '#type' => 'html_tag',
        '#tag' => $meta_tag[$meta_meta_links],
        '#attributes' => array(
            $meta_name => $meta_tag[$meta_name],
            $meta_content => $meta_tag[$meta_content]
        ),
        '#weight' => 999 + $i
    );

    if(!empty($meta_tag[$meta_content]))
    drupal_add_html_head($meta_page_data[$i],'$meta_page_data' . $i);
    $i++;
  }
  endif;

 $tanent_info = &drupal_static('tanent_info');

 // Add template for Equantum view and DeluxeFullColor pages
 if((strstr(drupal_get_path_alias(), '/', TRUE) == 'equantum') || (isset($variables['node']) && $variables['node']->type == 'equantum_product') || $tanent_info['community']=="DeluxeFullColor") {
       $variables['theme_hook_suggestions'][] = 'page__equantum_category';
       unset($_COOKIE['_psp_ecommerce_sid']);
       drupal_add_css(drupal_get_path('theme', 'deluxe_core') . '/css/equantum.css');
       drupal_add_js('jQuery(document).ready(function () { jQuery(".field-collection-item-field-product-tabs .content a").click(function(event){
  event.preventDefault ? event.preventDefault() : (event.returnValue = false);
})});',
    array('type' => 'inline', 'scope' => 'footer', 'weight' => 5)
  );
 }

  // Add css for Resources  pages

  $path_alias = drupal_get_path_alias(current_path());
  $arg = arg(NULL, $path_alias);
  if(isset($arg[0]) && $arg[0] == 'resources') {
     drupal_add_css(drupal_get_path('theme', 'deluxe_core') . '/css/resources.css');
     drupal_add_js(drupal_get_path('theme','deluxe_core') . '/js/resources.js');
  }

 if(isset($arg[0]) && $arg[0] == 'special') {
     drupal_add_css(drupal_get_path('theme', 'deluxe_core') . '/css/special.css');
  }

  // Add JS for Die-cut Pdp pages
   if (isset($variables['node']) && $variables['node']->type == 'product'){
    $array_pdp = array('62','91', '146');
    if($variables['node']->nid == in_array($variables['node']->nid, $array_pdp)){
    drupal_add_js(drupal_get_path('theme', 'deluxe_core') . '/js/pdp.js');
    }
  }
}

/* unset drupal core generate seo data */
function deluxe_core_html_head_alter(&$head_elements){
  /* get current community info*/
  $site_name = _deluxe_core_get_domain();
  $community_info = _deluxe_core_community_code($site_name);
  $favicon = $community_info->field_favorite_icon['und'][0]['uri'];
  $url = file_create_url($favicon);
  $url = parse_url($url);
  $favicon_path = $url['path'];

  /*end*/

  unset($head_elements['system_meta_generator']);
  foreach($head_elements as $key => $element){
    if (strpos($key,'drupal_add_html_head_link:canonical:') !== false) {
      unset($head_elements[$key]);
    }
    if(isset($element['#attributes']['rel']) && $element['#attributes']['rel'] == 'shortlink'){
      unset($head_elements[$key]);
    }
    if ( isset($element['#attributes']['href']) && strpos($element['#attributes']['href'], 'misc/favicon.ico') > 0){
      // Change the URL
      $head_elements[$key]['#attributes']['href'] = $favicon_path;
    }
  }
}

function deluxe_core_preprocess_views_view_fields__products_promotion__products_promotion(&$vars) {
  $lg_page_type = ' Layout Guidelines';
  if(arg(1) == 'direct-mail') {
    $lg_page_type = " Mailing Layout Guidelines";
  }
  $template_count = &drupal_static('template_count');
  $level = array_slice(explode('~', current_path()),1);
  $span = theme('html_tag', array(
    'element' => array(
      '#tag' => 'span',
      '#attributes' => array(
        'class' => 'layout-title',
        ),
      '#value' => $lg_page_type,
    ),
  ));
  if(count($level) >1 || $template_count< 10) {
    $heading = "h2";
  }
  else{
    $heading = "h1";
  }
  $head_title = theme('html_tag', array(
    'element' => array(
      '#tag' => $heading,
      '#attributes' => array(
        'class' => 'layout-title',
        ),
      '#value' => $vars['fields']['title']->raw . $span,
    ),
  ));

  $div_wrapper = theme('html_tag', array(
    'element' => array(
      '#tag' => 'div',
      '#attributes' => array(
        'class' => 'product-title',
        ),
      '#value' => $head_title,
    ),
  ));

    $vars['fields']['title']->content = $div_wrapper;

}

/**
  * Generic preprocess that is still working on D7
  */
function deluxe_core_preprocess_views_view_fields(&$vars) {
  if (isset($vars['view']->name)) {
    $function = __FUNCTION__ . '__' . $vars['view']->name . '__' . $vars['view']->current_display;
    if (function_exists($function)) {
     $function($vars);
    }
  }
}


function deluxe_core_preprocess(&$variables, $hook){
  if (arg(0) == 'admin'){
    return false;
  }

  $hook_to_exclude = array('block', 'html','page','region','section','zone');
  $current_theme = 'omega';
  $merge = array_unique(array_merge($variables['classes_array'], $variables['attributes_array']['class']));
  if (in_array($hook, $hook_to_exclude) || strpos($current_theme, 'omega') === TRUE) {
    unset($variables['classes_array']);
    $variables['attributes_array']['class'] = $merge;
  }
  else{
    $variables['classes_array'] = $merge;
    unset($variables['attributes_array']['class']);
  }
}

function deluxe_core_process(&$variables, $hook) {
  // Flatten out classes.
  if(isset($variables['classes_array'])) {
    $variables['classes'] = implode(' ', $variables['classes_array']);
  }
  else if(isset($variables['attributes_array']['class'])){
     $variables['classes']     = implode(' ', $variables['attributes_array']['class']);
  }


  // Flatten out attributes, title_attributes, and content_attributes.
  // Because this function can be called very often, and often with empty
  // attributes, optimize performance by only calling drupal_attributes() if
  // necessary.
  $variables['attributes'] = $variables['attributes_array'] ? drupal_attributes($variables['attributes_array']) : '';
  $variables['title_attributes'] = $variables['title_attributes_array'] ? drupal_attributes($variables['title_attributes_array']) : '';
  $variables['content_attributes'] = $variables['content_attributes_array'] ? drupal_attributes($variables['content_attributes_array']) : '';
}

function deluxe_core_theme_registry_alter(&$registry) {
  foreach ($registry as $hook => $item) {
    $index_process = array_search('template_process',$item['process functions']);
    if ($index_process !== FALSE) {
      unset($registry[$hook]['process functions'][$index_process]);
    }
    $index = array_search('deluxe_core_preprocess',$item['preprocess functions']);
    if ($index !== FALSE) {
      unset($registry[$hook]['preprocess functions'][$index]);
      array_push($registry[$hook]['preprocess functions'], 'deluxe_core_preprocess');
    }
  }
}
function deluxe_core_menu_link($variables) {
  $current_path = drupal_get_path_alias();
  $menu_path = drupal_get_path_alias($variables['element']['#href']);
  if (strstr($current_path, $menu_path)){
    $variables['element']['#attributes']['class'][] = 'active-trail';
    $variables['element']['#localized_options']['attributes']['class'][] = 'active-trail active';
  }
  return theme_menu_link($variables);
}

function deluxe_core_process_region(&$vars) {

  switch ($vars['elements']['#region']) {
    case 'branding':
      $tanent_info = &drupal_static('tanent_info');
      if (in_array($tanent_info['community_id'], array('13', '11'))) {
        $vars['front_url'] = "/home";
      }
      else {
        $vars['front_url'] = "/";
      }
      break;

    default:
      # code...
      break;
  }
}

/**
 * Function  to remove 'Print Guidelines' tab from Equantum page
**/
function deluxe_core_field_collection_tabs($variables) {
  $titles = $tabs = array();
  $node = menu_get_object();

  foreach ($variables['titles'] as $delta => $title) {

      $tab_id = drupal_clean_css_identifier($variables['field_name'] . '-tab-' . $delta);
      $titles[] = theme('field_collection_tabs_tab_title', array(
        'title' => $title,
        'tab_id' => $tab_id
      ));
      $tabs[] = theme('field_collection_tabs_tab', array(
        'tab' => $variables['tabs'][$delta],
        'tab_id' => $tab_id
      ));

      $title_text = strip_tags($title);
      if(strpos($title_text, 'Print Guidelines') == TRUE && $node->type == 'equantum_product'){
         unset($tabs[$delta]);
         unset($titles[$delta]);
      }
  }
  return theme('item_list', array('items' => $titles)) . implode('', $tabs);
}

function deluxe_core_process_block(&$variables) {
$variables['itemscope'] = NULL;
$variables['itemtype'] = NULL;
  switch ($variables['elements']['#block']->bid) {
    case '172':
      $breadcrumbs_variables = _deluxe_core_initialize_breadcrumbs();
      $node = $breadcrumbs_variables['node'];
      if (isset($node) && isset($node->is_review)  ) {
        $variables['itemscope'] = 'itemscope';
        $variables['itemtype'] = drupal_attributes(array('itemtype' => 'http://schema.org/Product'));
      }
      break;

    default:
      # code...
      break;
  }
}


function  deluxe_core_pager__resources(&$vars) {
  global $pager_page_array, $pager_total,$pager_total_items;
  $tags = $vars['tags'];
  $element = $vars['element'];
  $parameters = $vars['parameters'];
  $quantity = $vars['quantity'];
  $tags[4] = $pager_total[0];

  _resources_set_quantity($pager_total, $quantity);

  // Calculate various markers within this pager piece:
  // Middle is used to "center" pages around the current page.
  $pager_middle = ceil($quantity / 2);
  // current is the page we are currently paged to
  $pager_current = $pager_page_array[$element] + 1;
  // first is the first page listed by this pager piece (re quantity)
  $pager_first = $pager_current - $pager_middle + 1;
  $tags[0] = '1';
  // last is the last page listed by this pager piece (re quantity)
  $pager_last = $pager_current + $quantity - $pager_middle;

  // max is the maximum page number
  $pager_max = $pager_total[$element];
  // End of marker calculations.

  // Prepare for generation loop.
  $i = $pager_first;
  if ($pager_last > $pager_max) {
    // Adjust "center" if at end of query.
    $i = $i + ($pager_max - $pager_last);
    $pager_last = $pager_max;
  }
  if ($i <= 0) {
    // Adjust "center" if at start of query.
    $pager_last = $pager_last + (1 - $i);
    $i = 1;
  }

  // End of generation loop preparation.
  $li_first = theme('pager_first', array('text' => (isset($tags[0]) ? $tags[0] : t('« first')), 'element' => $element, 'parameters' => $parameters));
  $li_previous = theme('pager_previous', array('text' => (isset($tags[1]) ? $tags[1] : t('‹ previous')), 'element' => $element, 'interval' => 1, 'parameters' => $parameters));
  $li_next = theme('pager_next', array('text' => (isset($tags[3]) ? $tags[3] : t('next ›')), 'element' => $element, 'interval' => 1, 'parameters' => $parameters));
  $li_last = theme('pager_last', array('text' => (isset($tags[4]) ? $tags[4] : t('last »')), 'element' => $element, 'parameters' => $parameters));

  if ($pager_total[$element] > 1) {

    if ($li_previous) {
      $items[] = array(
        'class' => array('pager-previous'),
        'data' => $li_previous,
      );
    }

    if ($li_first ) {
      $items[] = array(
        'class' => array('pager-first'),
        'data' => $li_first,
      );
    }
    // When there is more than one page, create the pager list.
    if ($i != $pager_max) {
      if ($i > 2) {
        $items[] = array(
          'class' => array('pager-ellipsis'),
          'data' => '…',
        );
      }
      // Now generate the actual pager piece.
      for (; $i <= $pager_last && $i <= $pager_max; $i++) {
        if ($i < $pager_current && $i != $tags[0]) {
          $items[] = array(
            'class' => array('pager-item'),
            'data' => theme('pager_previous', array('text' => $i, 'element' => $element, 'interval' => ($pager_current - $i), 'parameters' => $parameters)),
          );
        }
        if ($i == $pager_current) {
          $items[] = array(
            'class' => array('pager-current'),
            'data' => $i,
          );
        }
        if ($i > $pager_current && $i != $tags[4]) {
          $items[] = array(
            'class' => array('pager-item'),
            'data' => theme('pager_next', array('text' => $i, 'element' => $element, 'interval' => ($i - $pager_current), 'parameters' => $parameters)),
          );
        }
      }
      if ($i < $pager_max) {
        $items[] = array(
          'class' => array('pager-ellipsis'),
          'data' => '…',
        );
      }
    }
    // End generation.

    if ($li_last) {
      $items[] = array(
        'class' => array('pager-last'),
        'data' => $li_last,
      );
    }
    if ($li_next) {
      $items[] = array(
        'class' => array('pager-next'),
        'data' => $li_next,
      );
    }

    return '<h2 class="element-invisible">' . t('Pages') . '</h2>' . theme('item_list', array(
      'items' => $items,
      'attributes' => array('class' => array('pager')),
    ));
  }


}


function _resources_set_quantity($pager_total, &$quantity) {
  if (!isset($_GET['page']) ||
   (isset($_GET['page']) && in_array($_GET['page'], array('1', $pager_total[0]-1)))){
    $quantity = 2;
  }

}

function deluxe_core_preprocess_views_view_accordion(&$vars){
  $vars['accordian_class'] = $vars['classes_array'];
}

function deluxe_core_css_alter(&$css) {
  $node_path = drupal_get_path_alias(current_path());
  if($node_path == 'helpcenter/colorbar/' || $node_path == 'helpcenter/faq') {
    unset($css[drupal_get_path('themes','omega').'sites/all/themes/omega/omega/css/omega-visuals.css']);
  }
}

