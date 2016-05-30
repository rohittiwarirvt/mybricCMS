<?php

function _deluxe_tracker_meta_vars(&$vars) {
  $tanent_info = &drupal_static('tanent_info');
  $meta_attributes_array = array();
  switch ($tanent_info['community']) {
    case 'DFSFullColor':
    case 'Safeguard':
        $meta_attributes_array = array(
          "http-equiv" => "X-UA-Compatible",
          "content" => "IE=edge",
          );
      break;
    case 'PsPrint':
            $meta_attributes_array = array(
          "charset" => "utf-8",
          );
      break;
    default:
       # code...
       break;
   }

  $vars['metaattributes'] = drupal_attributes($meta_attributes_array);

}
