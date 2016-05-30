<?php

/**
 * PreProcess variables for dfs-auth-page.tpl.php
 *
 * @param $variables
 *   An array of variables from the theme system.
 */
function template_preprocess_dfs_auth_page(&$vars) {

  $tanent_info = &drupal_static('tanent_info');
  variable_set('site_name', $tanent_info['community']);
  $vars['messages'] = !empty($vars['show_messages']) ? theme('status_messages') : '';
  $vars['page']['#children'] = NULL;
  $css = drupal_get_css();
  $vars['styles'] = $css;
  $head = drupal_add_html_head();
  $vars['head'] = drupal_render($head);
  $js = drupal_get_js();
  $vars['scripts'] = $js;
   if (!isset($vars['title'])) {
    $vars['title'] = drupal_get_title();
  }
  template_preprocess_html($vars);
  $curr_path = current_path();
  $path = drupal_get_path('module', 'dfs_user');


  $img_attributes = array(
      'path' => $path . '/images/loading_animation.gif',
      'alt' => 'Loading...',
      'title' => 'Loading...',
      'attributes' => array('class' => 'ajax-loader'),
      );
  $vars['loader'] = theme('image', $img_attributes);
}

/**
 * Process variables for dfs-auth-page.tpl.php
 *
 * @param $variables
 *   An array of variables from the theme system.
 */

function template_process_dfs_auth_page(&$vars) {
  template_process_html($vars);

}


function theme_dfs_form_element($variables) {
  $element = &$variables ['element'];

  // This function is invoked as theme wrapper, but the rendered form element
  // may not necessarily have been processed by form_builder().
  $element += array(
    '#title_display' => 'before',
  );

  // Add element #id for #type 'item'.
  if (isset($element ['#markup']) && !empty($element ['#id'])) {
    $attributes ['id'] = $element ['#id'];
  }
  // Add element's #type and #name as class to aid with JS/CSS selectors.
  $attributes ['class'] = array('form-item');
  if (!empty($element ['#type'])) {
    $attributes ['class'][] = 'form-type-' . strtr($element ['#type'], '_', '-');
  }
  if (!empty($element ['#name'])) {
    $attributes ['class'][] = 'form-item-' . strtr($element ['#name'], array(' ' => '-', '_' => '-', '[' => '-', ']' => ''));
  }
  // Add a class for disabled elements to facilitate cross-browser styling.
  if (!empty($element ['#attributes']['disabled'])) {
    $attributes ['class'][] = 'form-disabled';
  }
  $output = '<div' . drupal_attributes($attributes) . '>' . "\n";

  // If #title is not set, we don't display any label or required marker.
  if (!isset($element ['#title'])) {
    $element ['#title_display'] = 'none';
  }
  $prefix = isset($element ['#field_prefix']) ? '<span class="field-prefix">' . $element ['#field_prefix'] . '</span> ' : '';
  $suffix = isset($element ['#field_suffix']) ? ' <span class="field-suffix">' . $element ['#field_suffix'] . '</span>' : '';

  switch ($element ['#title_display']) {
    case 'before':
    case 'invisible':
      $output .= ' ' . theme('form_element_label', $variables);
      $output .= ' ' . $prefix . $element ['#children'] . $suffix . "\n";
      break;

    case 'after':
      $output .= ' ' . $prefix . $element ['#children'] . $suffix;
      $output .= ' ' . theme('form_element_label', $variables) . "\n";
      break;

    case 'none':
    case 'attribute':
      // Output no label and no required marker, only the children.
      $output .= ' ' . $prefix . $element ['#children'] . $suffix . "\n";
      break;
  }

  if (!empty($element ['#description'])) {
    $output .= '<div class="description">' . $element ['#description'] . "</div>\n";
  }
  if (!empty($element ['#error'])) {
    $output .= '<div class="dfs-error">' . $element ['#error'] . "</div>\n";
  }

  $output .= "</div>\n";

  return $output;
}

/**
 * We changed the type from input type=submit to type=button  .
 * as login form was notwoking in ie
 * @param $variables
 *   An associative array containing:
 *   - element: An associative array containing the properties of the element.
 *     Properties used: #attributes, #button_type, #name, #value.
 *
 * @ingroup themeable
 */
function theme_dfs_button($variables) {
  static $path_prevent_redirect = array('login.aspx','dfs/user/register','passwordreset',
                                    'user/ajax/psprint/login','user/ajax/psprint/register','user/ajax/psprint/resetpassword');
  $path = drupal_strtolower(current_path());
  $element = $variables['element'];

  if (in_array($path, $path_prevent_redirect))
    $element['#attributes']['type'] = 'button';
  else
    $element ['#attributes']['type'] = 'submit';
  element_set_attributes($element, array('id', 'name', 'value'));
  $element ['#attributes']['class'][] = 'form-' . $element ['#button_type'];
  if (!empty($element ['#attributes']['disabled'])) {
    $element ['#attributes']['class'][] = 'form-button-disabled';
  }

  return '<input' . drupal_attributes($element ['#attributes']) . ' />';
}


