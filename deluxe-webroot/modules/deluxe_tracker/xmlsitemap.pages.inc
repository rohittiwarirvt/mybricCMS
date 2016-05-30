<?php

// Generate sitemap.xml

function _deluxe_tracker_xmlsitemap_output() {
  $headers = array();
  $mtime = filemtime($file);
  $last_modified = gmdate(DATE_RFC1123, $mtime);
  $etag = '"' . md5($last_modified) . '"';

  // See if the client has provided the required HTTP headers.
  $if_modified_since = isset($_SERVER['HTTP_IF_MODIFIED_SINCE']) ? stripslashes($_SERVER['HTTP_IF_MODIFIED_SINCE']) : FALSE;
  $if_none_match = isset($_SERVER['HTTP_IF_NONE_MATCH']) ? stripslashes($_SERVER['HTTP_IF_NONE_MATCH']) : FALSE;
   if ($if_modified_since && $if_none_match && $if_none_match == $etag && $if_modified_since == $last_modified) {
    header('HTTP/1.1 304 Not Modified');
    // All 304 responses must send an etag if the 200 response for the same object contained an etag
    header('Etag: ' . $etag);
    exit;
  }
 $headers += array(
    'Content-type' => 'text/xml; charset=utf-8',
    //'Content-length' => filesize($file),
    'Last-modified' => $last_modified,
    'Etag' => $etag,
    'Expires' => gmdate(DATE_RFC1123, $mtime),
    'Cache-Control' => 'must-revalidate',
    'X-Robots-Tag' => 'noindex, follow',
  );
  foreach ($headers as $name => $value) {
    drupal_add_http_header($name, $value);
  }
  drupal_send_headers();
  print   theme('deluxe_tracker_xmlsitemap_page');

}


function writeRecord($object){
  $absolute_url = "https://www.psprint.com";
  static $last_modified;
  $last_modified = empty($last_modified) ? variable_get('xmlsitemaptime') : $last_modified;
  $xmlurl = $absolute_url . $object->FriendlyUrl;
  if (!preg_match("/.*\/$/", $xmlurl) &&  substr_count( $xmlurl, '~') ==0 ) {
    $xmlurl = $xmlurl.'/'; //The canicol URL with trailing slash to the item
  }else{
    $xmlurl = $xmlurl; //The canicol URL to the item
  }
  $html ="";
  $html .= '<url>';
  $html .= '<loc>'.$xmlurl.'</loc>';
  $html .= '<lastmod>'. $last_modified .'</lastmod>';
  $html .= '<changefreq>Weekly</changefreq>';
  $html .= '<priority>0.5</priority>';
  $html .= '</url>';
  return $html;
}


function _deluxe_tracker_resourcesurls_for_xml(){
  $community_id = 1;
  $query = db_select('WebPage_design_tool', 'wpdt');
  $query->innerJoin('SeoData_design_tool', 'sddt', 'wpdt.WebPageID=sddt.WebPageID');
  $query->fields('wpdt', array('FriendlyUrl', 'Updated'));
  $query->addExpression("DATE_FORMAT(wpdt.Updated,  '%Y-%m-%d')", 'Updated');
  $query->condition('wpdt.CommunityID', $community_id, '=');
  $query->condition('wpdt.IsActive', 1 , '=');
  $query->condition('wpdt.FriendlyUrl', '_' . db_like("resources") . '%',  "LIKE");
  $query->condition('sddt.Robots', 'n/a', 'LIKE');
  $result = $query->execute()->fetchAll();
  return $result;
}
