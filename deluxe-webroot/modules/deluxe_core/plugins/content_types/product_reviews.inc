<?php
/**
 * @file
 *
 * This software is open-source licensed under the GNU Public License Version 2 or later
 * The full license is available in the LICENSE.TXT file at the root of this repository
 */

$plugin = array (
  'single' => TRUE,
  'icon' => 'icon_node_form.png',
  'title' => t('Deluxe: Products review & ratings'),
  'description' => t('Display Products review & ratings.'),
  'category' => t('Deluxe'),
  'required context' => new ctools_context_required(t('Node'), 'node'),
  'render callback'  => 'deluxe_core_reviews_rating_content_type_render',
  'edit form'        => 'deluxe_core_reviews_rating_content_type_edit_form',
);

function deluxe_core_reviews_rating_content_type_render($subtype, $conf, $panel_args, &$context) {
  $block = new stdClass();
  $variables = array();
  $attributes = array();
  $block->title = '';
  $node = $context->data;
  $friendly_url = drupal_get_path_alias("node/".$node->nid);
  $response = file_get_contents('http://design.psprint.com/reviewWidget?json={"bucket_name":"/'.$friendly_url.'","format":"html","widget":"md-2c-g-list"}');

  $build = array();
  $build[0]['#markup'] = $response;
  $block->content = $build;
  return $block;
}

/* hook_content_type_edit_form */
function  deluxe_core_reviews_rating_content_type_edit_form($form, &$form_state) {
 return $form;
}

/* hook_content_type_edit_form_submit */
function deluxe_core_reviews_rating_content_type_edit_form_submit(&$form, &$form_state) {

}

