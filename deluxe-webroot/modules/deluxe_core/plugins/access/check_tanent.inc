<?php

/**
 * @file
 * Plugin to provide access control based on evaluated PHP.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t("Deluxe Core"),
  'description' => t('Control access of node by checking current tanent.'),
  'callback' => 'deluxe_core_ctools_php_ctools_access_check',
  'settings form' => 'deluxe_core_ctools_php_ctools_access_settings',
  'required context' => new ctools_context_required(t('Node'), 'node'),
);

/**
 * Settings form for the 'by perm' access plugin
 *
 * @todo Need a way to provide a list of all available contexts to be used by
 *       the eval-ed PHP.
 */
function deluxe_core_ctools_php_ctools_access_settings($form, &$form_state, $conf) {
  $perms = array();
  return $form;
}

/**
 * Check for access.
 */
function deluxe_core_ctools_php_ctools_access_check($__conf, $contexts) {
  $node = $contexts->data;
    return TRUE;
}