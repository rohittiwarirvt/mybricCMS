<?php

function _deluxe_tracker_ga_vars(&$vars) {
  $arg = arg();
  $tanent_info = &drupal_static('tanent_info');
  $meta_noscript = array(
      '#theme' => 'html_tag',
      '#tag' => 'iframe',
      '#attributes' => array(
          'src' => "//www.googletagmanager.com/ns.html?id=GTM-D7J6",
          'height' => "0",
          'width' => "0",
          'style' => "display:none;visibility:hidden"
      )
  );
  $noscript = array(
      '#theme' => 'html_tag',
      '#tag' => 'noscript',
      '#value' => drupal_render($meta_noscript),
      '#weight' => 9999
  );
  $vars['noscript'] = drupal_render($noscript);

  $noscript_inline = array(
      '#theme' => 'html_tag',
      '#tag' => 'script',
      '#value' => "(function(w,d,s,l,i){w[l]=w[l]||[];w[l].push({'gtm.start':new Date().getTime(),event:'gtm.js'});var f=d.getElementsByTagName(s)[0], j=d.createElement(s),dl=l!='dataLayer'?'&l='+l:'';j.async=true;j.src='//www.googletagmanager.com/gtm.js?id='+i+dl;f.parentNode.insertBefore(j,f);
})(window,document,'script','dataLayer','GTM-D7J6')",
  );

  $vars['noscript_inline'] = drupal_render($noscript_inline);
  $user_data = _deluxe_tracker_get_loggedin_userdetails();
  $user_id = !empty($user_data['userid']) ? $user_data['userid'] : '';
  $user_name = !empty($user_data['username']) ? $user_data['username'] : '';
  $erro_var_type = "";
  $needle = drupal_get_path_alias(current_path());
  $uname_universal = NULL;
  if(drupal_match_path($needle, 'Error/NotFound')){
    $uname_universal = !empty($user_name) ? $user_name:'';
    $erro_var_type ="Error: 404";
  }
  $field_name = array('PageType');
  $page_type = _seo_data_display_generate_tags($field_name);
  $seo_result['PageType'] = !empty($page_type['PageType']) ? $page_type['PageType'] : '';
  $page_type_string = $seo_result['PageType'];
  // escaping { comma, ", ',} from page type
  $page_type_string = str_replace(',', '\,', $page_type_string);
  $page_type_string = str_replace('"', '\"', $page_type_string);
  $page_type_string = str_replace("'", "\'", $page_type_string);
  $community_name = $tanent_info['community'];
  $univ_community_name = !empty($community_name) ? "window.CommunityName='$community_name'": "";
  $univ_var_page_type = !empty($seo_result['PageType']) ? $page_type_string : '';
  $univ_var_user_id =!empty($user_id) ? $user_id:'';

  // ga for pdp and category pages of reviews
  $node = menu_get_object();

  if(isset($node) && $node->type == "rating_reviews") {
    $current_path = drupal_get_path_alias(current_path());
    // $current_path = trim(str_replace("reviews", "", $current_path) , '/');
    $product_name = arg(0, $current_path);
    $ga_vars = _deluxe_tracker_ga_initialize($product_name);
  }
  if ($arg['0'] == 'layout-templates') {
    $current_path = current_path();
    $product_name = isset($arg['1']) && $arg['1'] !== 'direct-mail' ? arg(1, $current_path) : "" ;
    if($arg['1'] == 'direct-mail' && isset($arg['2'])){
      $product_name = arg(2, $current_path);
    }

    $product_name = substr(trim($product_name, '/'), 0,-9);
    if(!empty($product_name)) {
      $ga_vars = _deluxe_tracker_ga_initialize($product_name);
      $uname_universal = !empty($user_name) ? $user_name:'';
    }
    else {
       $ga_vars = _deluxe_tracker_ga_initialize($product_name);
      $uname_universal = !empty($user_name) ? $user_name:'';
    }
  }

  $window_universal = array( "version"=> "1.2.0",
                             "page" => array(
                               'type' => $univ_var_page_type,
                               'error-code' => $erro_var_type,
                              ),
                             "basket" => array(
                              "id" => isset($ga_vars['shoppingCartId']) ? $ga_vars['shoppingCartId'] : NULL
                              ),
                             "user" => array(
                                'user_id' => $univ_var_user_id,
                                'name' => $uname_universal,
                              ),
                             "product" => array(
                                "id" => isset($ga_vars['catalogId']) ? $ga_vars['catalogId'] : NULL,
                                "name" => isset($ga_vars['catalogName']) ? $ga_vars['catalogName'] : NULL,
                              )
                      );
  // code for removing empty arrays
  foreach( $window_universal as $key => $value ) {
    if( is_array( $value ) ) {
        foreach( $value as $key2 => $value2 ) {
            if( empty( $value2 ) )
                unset( $window_universal[ $key ][ $key2 ] );
        }
    }
    if( empty( $window_universal[ $key ] ) )
        unset( $window_universal[ $key ] );
  }
  $wuot ="";
  foreach ($window_universal as $univ_key => $univ_value) {
    if (is_array($univ_value)) {
        if(!empty($univ_value)) {
    $wuot .=<<<GA

                "{$univ_key}" : {
GA;
      foreach ($univ_value as $key => $value) {
        if(!empty($value)) {
    $wuot .=<<<GA

                    "{$key}" : "{$value}",
GA;
        }
      }
    $wuot .=<<<GA

                },
GA;
        }
    }
    else {
    $wuot .=<<<GA
      "{$univ_key}" : "{$univ_value}",
GA;
    }

  }

  $ga_js = <<<EOF

        window.universal_variable = {
          {$wuot}
        }
           {$univ_community_name};
EOF;

  $vars['ga_universal_variables'] = $ga_js;
}



function _deluxe_tracker_ga_initialize($friendlyUrl) {
  global $base_url;
  $url = $base_url.'/api/internal/catalog/tracking';
  $data = array(
    'friendlyUrl' =>$friendlyUrl,
  );
  $data = array_filter($data);
  $api_url = url($url, array('query' => $data));
  $cookies = _deluxe_tracker_get_cookie();
  $curl = curl_init ();
  curl_setopt ($curl, CURLOPT_SSL_VERIFYPEER, 0);
  curl_setopt ($curl, CURLOPT_SSL_VERIFYHOST, 0);
  curl_setopt ($curl, CURLOPT_HEADER, 0);
  curl_setopt ($curl, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt ($curl, CURLOPT_COOKIE, $cookies);
  curl_setopt ($curl, CURLOPT_URL, $api_url);

  $result = curl_exec ($curl);
  $api_response = drupal_json_decode($result);
  if(empty($api_response['error'])) {
    $response_res = current(array_values($api_response));
    $catalog_api_res = &drupal_static(__FUNCTION__);
    $catalog_api_res = $response_res;
    return $catalog_api_res;
  }
}


function _deluxe_tracker_get_cookie() {
  $data = &drupal_static(__FUNCTION__);
  if (!isset($data)) {
    $cookie = "";
    foreach ($_COOKIE as $key => $value) {
      $cookie .= "$key=$value;";
    }
    $data = $cookie;
  }
  return $data;
}
