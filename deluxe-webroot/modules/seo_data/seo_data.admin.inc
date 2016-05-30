<?php
/**
 * Form builder; Form for advanced module form.
 */
function seo_form() {
    
    $values = seo_data_get_values();
    $form = array();

    $form['SeoDataID'] = array(
    '#title' => t('SeoDataID'),
    '#type' => 'textfield',
    '#default_value' => isset($values['SeoDataID']) ? t($values['SeoDataID']) : '',
    '#disabled' => TRUE,
    '#required' => FALSE,
    ); 

    $form['WebPageID'] = array(
    '#title' => t('WebPageID'),
    '#type' => 'textfield',
    '#default_value' => isset($values['WebPageID']) ? t($values['WebPageID']) : '',
    '#disabled' => TRUE,
    '#required' => FALSE,
    ); 
 
    $form['Title'] = array(
    '#title' => t('Title'),
    '#type' => 'textarea',
    '#rows' => 1,
    '#default_value' => isset($values['Title']) ? t($values['Title']) : '',
    '#required' => FALSE,
    );

    $form['Description'] = array(
    '#title' => t('Description'),
    '#type' => 'textarea',
    '#rows' => 1,
    '#default_value' => isset($values['Description']) ? utf8_encode($values['Description']) : '',
    '#required' => FALSE,
    );

    $form['Canonical'] = array(
    '#title' => t('Canonical'),
    '#type' => 'textarea',
    '#rows' => 1,
    '#default_value' => isset($values['Canonical']) ? t($values['Canonical']) : '',
    '#required' => FALSE,
    );

    $form['SeoCopyBlock'] = array(
    '#title' => t('SeoCopyBlock'),
    '#type' => 'text_format',
    '#rows' => 1,
    '#format' => 'full_html',
    '#default_value' => isset($values['SeoCopyBlock']) ? utf8_encode($values['SeoCopyBlock']) : 'n/a',
    '#required' => FALSE,
    );
    
    $form['Robots'] = array(
    '#title' => t('Robots'),
    '#type' => 'textarea',
    '#rows' => 1,
    '#default_value' => isset($values['Robots']) ? t($values['Robots']) : 'n/a',
    '#required' => FALSE,
    );
    
    $form['PageType'] = array(
    '#title' => t('PageType'),
    '#type' => 'textarea',
    '#rows' => 1,
    '#default_value' => isset($values['PageType']) ? t($values['PageType']) : '',
    '#required' => FALSE,
    );

    $form['Authorship'] = array(
    '#title' => t('Authorship'),
    '#type' => 'textarea',
    '#rows' => 1,
    '#default_value' => isset($values['Authorship']) ? t($values['Authorship']) : 'n/a',
    '#required' => FALSE,
    );

    $form['OpenGraphType'] = array(
    '#title' => t('OpenGraphType'),
    '#type' => 'textarea',
    '#rows' => 1,
    '#default_value' => isset($values['OpenGraphType']) ? t($values['OpenGraphType']) : 'website',
    '#required' => FALSE,
    );

    $form['OpenGraphTitle'] = array(
    '#title' => t('OpenGraphTitle'),
    '#type' => 'textarea',
    '#rows' => 1,
    '#default_value' => isset($values['OpenGraphTitle']) ? t($values['OpenGraphTitle']) : '',
    '#required' => FALSE,
    );

    $form['OpenGraphDescription'] = array(
    '#title' => t('OpenGraphDescription'),
    '#type' => 'textarea',
    '#rows' => 1,
    '#default_value' => isset($values['OpenGraphDescription']) ? utf8_encode($values['OpenGraphDescription']) : '',
    '#required' => FALSE,
    );

    $form['OpenGraphUrl'] = array(
    '#title' => t('OpenGraphUrl'),
    '#type' => 'textarea',
    '#rows' => 1,
    '#default_value' => isset($values['OpenGraphUrl']) ? t($values['OpenGraphUrl']) : '',
    '#required' => FALSE,
    );

    $form['OpenGraphImage'] = array(
    '#title' => t('OpenGraphImage'),
    '#type' => 'textarea',
    '#rows' => 1,
    '#default_value' => isset($values['OpenGraphImage']) ? t($values['OpenGraphImage']) : 'n/a',
    '#required' => FALSE,
    );

    $form['TwitterCard'] = array(
    '#title' => t('TwitterCard'),
    '#type' => 'textarea',
    '#rows' => 1,
    '#description'  => t('Max Characters: 30'),
    '#default_value' => isset($values['TwitterCard']) ? t($values['TwitterCard']) : 'summary',
    '#required' => FALSE,
    );

    $form['TwitterTitle'] = array(
    '#title' => t('TwitterTitle'),
    '#type' => 'textarea',
    '#rows' => 1,
    '#default_value' => isset($values['TwitterTitle']) ? t($values['TwitterTitle']) : '',
    '#required' => FALSE,
    ); 
    
    $form['TwitterDescription'] = array(
    '#title' => t('TwitterDescription'),
    '#type' => 'textarea',
    '#rows' => 1,
    '#default_value' => isset($values['TwitterDescription']) ? utf8_encode($values['TwitterDescription']) : '',
    '#required' => FALSE,
    ); 

    $form['TwitterImage'] = array(
    '#title' => t('TwitterImage'),
    '#type' => 'textarea',
    '#rows' => 1,
    '#default_value' => isset($values['TwitterImage']) ? t($values['TwitterImage']) : 'n/a',
    '#required' => FALSE,
    ); 

    $form['TwitterUrl'] = array(
    '#title' => t('TwitterUrl'),
    '#type' => 'textarea',
    '#rows' => 1,
    '#default_value' => isset($values['TwitterUrl']) ? t($values['TwitterUrl']) : '',
    '#required' => FALSE,
    ); 

    $form['SchemaType'] = array(
    '#title' => t('SchemaType'),
    '#type' => 'textarea',
    '#rows' => 1,
    '#default_value' => isset($values['SchemaType']) ? t($values['SchemaType']) : 'https://schema.org/Article',
    '#required' => FALSE,
    ); 

    $form['SchemaName'] = array(
    '#title' => t('SchemaName'),
    '#type' => 'textarea',
    '#rows' => 1,
    '#default_value' => isset($values['SchemaName']) ? t($values['SchemaName']) : '',
    '#required' => FALSE,
    );  

    $form['SchemaDescription'] = array(
    '#title' => t('SchemaDescription'),
    '#type' => 'textarea',
    '#rows' => 1,
    '#default_value' => isset($values['SchemaDescription']) ? utf8_encode($values['SchemaDescription']) : '',
    '#required' => FALSE,
    ); 

    $form['SchemaImage'] = array(
    '#title' => t('SchemaImage'),
    '#type' => 'textarea',
    '#rows' => 1,
    '#default_value' => isset($values['SchemaImage']) ? t($values['SchemaImage']) : 'n/a',
    '#required' => FALSE,
    ); 

    $form['SeoCopyBlockTop'] = array(
    '#title' => t('SeoCopyBlockTop'),
    '#type' => 'textarea',
    '#rows' => 1,
    '#default_value' => isset($values['SeoCopyBlockTop']) ? t($values['SeoCopyBlockTop']) : 'n/a',
    '#required' => FALSE,
    ); 

    $form['H1'] = array(
    '#title' => t('H1'),
    '#type' => 'textarea',
    '#rows' => 1,
    '#default_value' => isset($values['H1']) ? t($values['H1']) : '',
    '#required' => FALSE,
    ); 

    $form['CreatedBy'] = array(
    '#title' => t('created By'),
    '#type' => 'textfield',
    '#default_value' => isset($values['CreatedBy']) ? t($values['CreatedBy']) : '',
    '#required' => FALSE,
    '#disabled' => TRUE,
    );

    $form['Created'] = array(
    '#title' => t('Created'),
    '#type' => 'textfield',
    '#default_value' => isset($values['Updated']) ? t($values['Updated']) : '',
    '#required' => FALSE,
    '#disabled' => TRUE,
    );  
   
    $form['IsActive'] = array(
    '#title' => t('Is Active'),
    '#type' => 'textfield',
    '#description'  => t('Example value: 0 or 1'),
    '#default_value' => isset($values['IsActive']) ? t($values['IsActive']) : 1,
    '#required' => FALSE,
    '#element_validate' => array('element_validate_integer'),
    );

    $form['Updated'] = array(
    '#title' => t('Updated'),
    '#type' => 'textfield',
    '#default_value' => isset($values['Updated']) ? t($values['Updated']) : '',
    '#required' => FALSE,
    );  

    $form['Version'] = array(
    '#title' => t('Version'),
    '#type' => 'textfield',
    '#description'  => t('Example value: 1'),
    '#default_value' => isset($values['Version']) ? t($values['Version']) : 1,
    '#required' => FALSE,
    '#element_validate' => array('element_validate_integer'),
    );

    $form['UpdatedBy'] = array(
    '#title' => t('UpdatedBy'),
    '#type' => 'textfield',
    '#default_value' => isset($values['UpdatedBy']) ? t($values['UpdatedBy']) : '',
    '#required' => FALSE,
    );

    $form['CommunityID'] = array(
    '#title' => t('CommunityID'),
    '#type' => 'textfield',
    '#number_type' => 'decimal',
    '#description'  => t('Example value: 1, 13 or 12'),
    '#default_value' => isset($values['CommunityID']) ? t($values['CommunityID']) : 1,
    '#required' => FALSE,
    '#element_validate' => array('element_validate_integer'),
    );

    $form['FriendlyUrl'] = array(
    '#title' => t('FriendlyUrl'),
    '#type' => 'textarea',
    '#rows' => 1,
    '#default_value' => isset($values['FriendlyUrl']) ? t($values['FriendlyUrl']) : '',
    '#required' => FALSE,
    );
    
    return $form;
}

/**
 * Get default values
 */
function seo_data_get_values() {
    
    global $user;
    $user_name = $user->name;
    $date = date('Y-m-d h:i:s');
    $seo_values = $object = array(); 

    if(arg(0)=='node' && is_numeric(arg(1))) {
        $object = menu_get_object();
        $community = deluxe_core_field_tanent_info($object->nid, 'node', TRUE);
        $friendly_url = "/" . drupal_get_path_alias('node/' . $object->nid);
    }
    elseif(arg(0)=='taxonomy' && arg(1)=="term"){
        $object = menu_get_object('taxonomy_term',2);
        $community = deluxe_core_field_tanent_info($object->tid, 'taxonomy_term', TRUE);
        $friendly_url = "/" . drupal_get_path_alias('taxonomy/term/'. $object->tid);
    }
   
    if(!empty($community) && isset($friendly_url)) {        /* node/term mode: edit */
       
        //Get data by WebPageID saved in node - node edit action
        $query = db_select('WebPage_design_tool', 'wb');
        $query->join('SeoData_design_tool', 'se', 'se.WebPageID = wb.WebPageID');
        $query->fields('wb');
        $query->fields('se');
        $query->condition('wb.CommunityID', $community, 'IN');
        $query->condition('wb.FriendlyUrl',$friendly_url, '=');
        $seo_values = $query->execute()->fetchAssoc();
    }
    else{                        /* node/term mode: add */

        $SeoData_WebPage_ID = get_last_webpage_id();
        $seo_values['WebPageID'] = $SeoData_WebPage_ID['WebPageID'];
        $seo_values['SeoDataID'] = $SeoData_WebPage_ID['SeoDataID'];
        $seo_values['CommunityID'] = 1;
        $seo_values['CreatedBy'] = $user_name;
        $seo_values['UpdatedBy'] = $user_name;
        $seo_values['Created'] = $date;
        $seo_values['Updated'] = $date;
    }
    return $seo_values; 
}


