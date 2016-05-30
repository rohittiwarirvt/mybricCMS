<?php

/**
 * @file
 * Plugin to provide access control based upon role membership.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t("Community: Access"),
  'description' => t('Control access by community.'),
  'callback' => 'dc_visibility_ctools_access_check',
  'default' => array('community' => array()),
  'settings form' => 'dc_visibility_ctools_access_settings',
  'settings form submit' => 'dc_visibility_ctools_access_settings_submit',
  'summary' => 'dc_visibility_ctools_access_summary',
  'all contexts' => TRUE,
);

/**
 * Settings form for the 'by role' access plugin
 */
function dc_visibility_ctools_access_settings($form, &$form_state, $conf) {
  $communities_options = array();
  $communities = node_load_multiple(array(), array('type' => 'community'));

  foreach ($communities as $key => $community) {
    $community_name = $community->field_community_code['und'][0]['value'];
    $communities_options[strtolower($community_name)] = $community_name;
  }


  $form['settings']['community'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Community'),
    '#default_value' => $conf['community'],
    '#options' => $communities_options,
    '#description' => t('Only the checked Community will be granted access.'),
  );
  return $form;
}

/**
 * Compress the community allowed to the minimum.
 */
function dc_visibility_ctools_access_settings_submit($form, &$form_state) {
  $form_state['values']['settings']['community'] = array_keys(array_filter($form_state['values']['settings']['community']));
}

/**
 * Check for access.
 */
function dc_visibility_ctools_access_check($conf, $context) {
  // As far as I know there should always be a context at this point, but this
  // is safe.
  $tanent_info = &drupal_static('tanent_info');
  foreach ($conf as $key => $community){

    if (in_array(strtolower($tanent_info['tenant_name']), $community)) {
      return TRUE;
    }else{
      return FALSE;
    }
  }
}

function dc_visibility_ctools_access_summary($conf, $context){
  if (!isset($conf['community'])) {
    $conf['community'] = array();
  }

  $communities_options = array();
  $communities = node_load_multiple(array(), array('type' => 'community'));

  foreach ($communities as $key => $community) {
    $community_name = $community->field_community_code['und'][0]['value'];
    $communities_options[strtolower($community_name)] = $community_name;
  }

  $communities = $communities_options;

  $names = array();
  foreach (array_filter($conf['community']) as $community) {
    $names[] = check_plain($communities[$community]);
  }
  if (empty($names)) {
    return t('@identifier can have any role', array('@identifier' => $community));
  }
  return format_plural(count($names), 'Site  has community "@community"', 'Site has one of "@community"', array('@community' => implode(', ', $names), '@identifier' => $community));
}
