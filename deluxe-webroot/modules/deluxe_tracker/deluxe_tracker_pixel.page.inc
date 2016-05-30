<?php

function _deluxe_tracker_pixel_vars(&$vars){
  $environment = variable_get('subdomain');
  $site_name = _deluxe_core_get_domain();
  $WebPageID = _seo_data_get_webpageid_url();
  drupal_add_js(drupal_get_path('module', 'deluxe_tracker') . '/js/BasicPixel.js',array(
      'type' => 'file',
      'weight' => -101,
  ));
  $js_prosearch = <<<EOF

        jQuery(document).ready(function() {
           try{
                           _paq.push(["setSiteId", 3]);
                    _paq.push(["setSiteEnv","{$environment}"]);
                        (function () {
                        var configarray = ['{$environment}.{$site_name}'];
                        if (configarray.indexOf(window.location.hostname)!=-1)
                               {
                                _paq.push(['setCustomVariable', '1','webPageId',$WebPageID,'page']);
                                _paq.push(["trackPageView"]);
                        }
                        })();
                        }
                        catch(ex){
                        }
                        })

EOF;
  drupal_add_js($js_prosearch, array('type' => 'inline', 'scope' => 'header', 'weight' => -100));

  if ($environment == 'production') {
        $vars['adobetag_script'] = '<script type="text/javascript" src="//assets.adobedtm.com/d02c64e2db8f586d3bb03873b98163465438136e/satelliteLib-f9d6270aaa28537cb3db2d781b37e1ab2eedbdf5.js" async defer></script>';
  }
  else {
      $vars['adobetag_script'] = '<script type="text/javascript" src="//assets.adobedtm.com/d02c64e2db8f586d3bb03873b98163465438136e/satelliteLib-f9d6270aaa28537cb3db2d781b37e1ab2eedbdf5-staging.js" async defer></script>';
  }
  $vars['adobetag'] = '<script type="text/javascript">_satellite.pageBottom();</script>';
  $arg = arg();
  if ($arg[0] == 'layout-templates') {
    drupal_add_js(drupal_get_path('module', 'deluxe_tracker') . '/js/lg-tracking.js');
  }
}
