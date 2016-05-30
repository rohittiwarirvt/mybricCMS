<?php
/**
 * Form builder; Form for advanced module form.
 */
function wordpress_data_migrate_form() {

  $vocabularies = taxonomy_vocabulary_get_names();
  $content_types = node_type_get_types();

 // Get all content types
   $node_types = array();
  foreach ($content_types as $key => $value) {
      $node_types["content_type.".$value->type] = "Content Type: " . $value->name;
  }

 // Get all Taxonomies
  $taxonomies = array();
  foreach ($vocabularies as $key => $value) {

     $taxonomies["taxonomy.".$value->machine_name.".".$value->vid] = "Taxonomy: " . $value->name;
  }
   $array  = $node_types + $taxonomies;
   $array['featured_image.resources'] = 'Resources: Featured Image';
   $array['user.create'] = 'User: Create User';
   $array['url_redirect'] = 'URL Redirect';

    $form = array();
    $form['wordpress_data_migrate'] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
      '#title' => '<b style="color:blue"> Wordpress Data Migration</b>',
    );

    $form['wordpress_data_migrate']['wordpress_data_uploadin'] = array(
    '#title' => t('Upload In '),
    '#type' => 'select',
    '#options' => $array,
    '#required' => TRUE,
    );

    $form['wordpress_data_migrate']['wordpress_data_file'] = array(
      '#type' => 'managed_file',
      '#title' => t('Upload File '),
      '#description'  => t('File must be XML format for Content and XLS for Users.'),
      '#size' => 30,
      '#required' => true,
      '#upload_location' => 'public://wordpress_data_files',
      "#upload_validators"  => array("file_validate_extensions" => array("xml xls"))
    );

     $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Submit'),
    );
    return $form;
}
