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
  'title' => t('Deluxe: SEM SEO block'),
  'description' => t('Display the SEM product seo data from SeoData table.'),
  'category' => t('Deluxe'),
  'required context' => new ctools_context_required(t('Node'), 'node'),
  'render callback'  => 'deluxe_core_sem_seoblock_content_type_render',
  'edit form'        => 'deluxe_core_sem_seoblock_content_type_edit_form',
);

function deluxe_core_sem_seoblock_content_type_render($subtype, $conf, $panel_args, &$context) {
  $block = new stdClass();
  $variables = array();
  $attributes = array();
  $block->title = '';
  $node = $context->data;
  $tanent = _deluxe_core_tenantinfo($node->field_tanents['und']);
  $seocopy_block = _seo_data_display_by_pageid($tanent['webpage_id']);
  if ($seocopy_block['SeoCopyBlock']!='n/a'):
    $build = array();

    // Add Seo Copy Block markup .
    $build[0]['#markup'] = $seocopy_block['SeoCopyBlock'];
    $build['#items'][0]['value'] = $build[0]['#markup'];
    $block->content = $build;
    return $block;
  endif;

}

/* hook_content_type_edit_form */

function  deluxe_core_sem_seoblock_content_type_edit_form($form, &$form_state) {
 return $form;
}

/* hook_content_type_edit_form_submit */
function deluxe_core_sem_seoblock_content_type_edit_form_submit(&$form, &$form_state) {

}
