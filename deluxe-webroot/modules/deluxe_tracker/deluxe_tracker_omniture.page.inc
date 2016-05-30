<?php

function _deluxe_tracker_omniture_vars($vars) {

  $omni_page_title_id = "";
  $var_omi_section = "";
  $omi_sect = "";
  $field_name = array('PageType','Title');
  $seo_result = _seo_data_display_generate_tags($field_name);
  $arg = arg();
  $WebPageID = _seo_data_get_webpageid_url();
  $page_type_string = $seo_result['PageType'];
  $meta_title = $seo_result['Title'];
  switch ($page_type_string) {
    case 'General':
        $omi_sect = 'about_us';
        $var_omi_section = 'About Page';
        if ($WebPageID >= 900163 && $WebPageID <= 900167) {
          $var_omi_section = 'General Page';
        }

        $omni_page_title_id .= !empty($var_omi_section) ? $var_omi_section : '';
        $omni_page_title_id .= !empty($meta_title) ? ': ' . $meta_title : '';
        $omni_page_title_id .= ':' . !empty($WebPageID) ? ':' . $WebPageID: '';
      break;
    case 'Helpcenter':
        $var_omi_section = 'Help Center Page';
        if ( implode('/', array($arg[0], $arg[1], $arg[2]) == 'shared/html/fileprep') || in_array($WebPageID, array(900190, 900191) )) {
          $var_omi_section='Pop-Up Page';
        }
        $omi_sect = 'help_center_pages';
        $omni_page_title_id .= !empty($var_omi_section) ? $var_omi_section : '';
        $omni_page_title_id .= !empty($meta_title) ? ':' . $meta_title : '';
        $omni_page_title_id .= ':' . !empty($WebPageID) ? ':'.$WebPageID : '';
      break;
    case 'Layout Guideline':
        $omi_sect = 'layout_template_pages';
        $var_omi_section = 'Layout Template Page';
        if ($arg[0] == 'diecut-shape-templates') {
          $var_omi_section = 'Die Gallery Page';
        }
        else if (isset($arg[1]) && $arg[1] == 'direct_mail') {
          $var_omi_section = 'Layout Template Page:Direct Mail';
        }

        $omni_page_title_id .= !empty($var_omi_section) ? $var_omi_section : '';
        $omni_page_title_id .= !empty($meta_title) ? ':' . $meta_title : '';
        $omni_page_title_id .= ':' . !empty($WebPageID) ? ':' . $WebPageID: '';
      break;
    case 'Printing Services':
        $omi_sect = 'printing_services_pages';
        $var_omi_section = 'Printing Services Page';
        $omni_page_title_id .= !empty($var_omi_section) ? $var_omi_section : '';
        $omni_page_title_id .= !empty($meta_title) ? ':' . $meta_title : '';
        $omni_page_title_id .= ':' . !empty($WebPageID) ? ':' . $WebPageID : '';
      break;
    case 'SiteInfo':
        $omi_sect = 'feature_pages';
        $var_omi_section = 'General Page';
        $omni_page_title_id .= !empty($var_omi_section) ? $var_omi_section : '';
        $omni_page_title_id .= !empty($meta_title) ? ':' . $meta_title : '';
        $omni_page_title_id .= ':' . !empty($WebPageID) ? ':' . $WebPageID : '';
      break;
    case 'SiteNavigation':
        $omi_sect = 'SiteNavigation';
        $var_omi_section = 'General Page';
        $omni_page_title_id .= !empty($var_omi_section) ? $var_omi_section : '';
        $omni_page_title_id .= !empty($meta_title) ? ':' . $meta_title : '';
        $omni_page_title_id .= ':' . !empty($WebPageID) ? ':' . $WebPageID : '';
      break;
    default:
      # code...
      break;
  }






  $omniture_array = array(
          's.pageName' => $omni_page_title_id,
          's.channel' => $var_omi_section,
          's.prop1' => "PsPrint",
          's.prop2' => "PsPrint:Main",
          's.prop3' => "PsPrint:Main:" . $var_omi_section,
          's.prop4' => $var_omi_section,
          's.eVar10' => "Small Business",
          's.eVar42' => $omni_page_title_id,
          's.eVar46' => $omni_page_title_id,
      );

  // if($page_type_string) {
  //   $dt_array =   array(
  //         's.event' => $event,
  //         's.products' => $var_omi_dt_products_val,
  //         's.eVar4' => $var_omi_prod_name,
  //         );
  //   $ominture_array = array_slice($ominture_array, 0,6,true) + $dt_array + array_slice($ominture_array, 6, count($ominture_array) -1, true);
  // }

  $omni_string="";
  if(!empty($omi_sect))
  foreach($omniture_array as $index => $values) {
      $omni_string.="$index =\"".$values."\";\n";

  }

$js_omniture =<<<EOF

 <!--


        /* You may give each page an identifying name, server, and channel on
        the next lines. */

 {$omni_string}
/************* DO NOT ALTER ANYTHING BELOW THIS LINE ! **************/
        var chkurl = window.location.href;
        if (chkurl.indexOf("searchresults.aspx") == -1) {

            var s_code = s.t(); if (s_code) document.write(s_code)
        }
        //--></script>
    <script>
EOF;
  drupal_add_js($js_omniture,array(
      'type' => 'inline',
      'scope' => 'header',
      'weight' => 10004
  ));

}
