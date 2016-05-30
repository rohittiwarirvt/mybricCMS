<?php

/**
 *   user login form
 * @return [type] [description]
 */

function psp_ctools_login_form_build($ajax) {
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');
    $form_state = array('ajax' => TRUE, 'title' => t('Login') );
    $output = ctools_modal_form_wrapper('psp_user_login_form', $form_state);
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax-commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }
  else {
    return drupal_get_form('psp_user_login_form');
  }
}

/**
 *psp user login form render array
 */
function psp_user_login_form($form, $form_state) {
  global $user;
  $tanent_info = &drupal_static('tanent_info');
  drupal_set_title('Login');
  $settings = array('tenant' =>  array(
                  'login_api' => variable_get('login_' .  $tanent_info['community']),
                  ),
              );
  drupal_add_js($settings, 'setting');
  // If we are already logged on, go to the user page instead.
  if ($user->uid && isset($_GET['destination'])) {
    drupal_goto($_GET['destination']);
  }
  else if($user->uid){
    drupal_goto('/myaccount');
  }


  $form['left_container'] = array(
            '#type' => 'container',
            '#attributes' => array (
                'class' => array('left-container', 'login-container'),
            ),

         );

  $form['left_container']['login-subtitle'] = array(
          '#type' => "item",
          '#title' => t("Returning Customer"),
          );

  $form['left_container']['login-meta'] = array(
          '#markup' => t('<div><span class="login-meta">Please login to your account now.</span></div>'),
          );
  $form['left_container']['name'] = array(
          '#type' => 'textfield',
          '#title' => t('Username (Email address used to create account)'),
          '#maxlength' => 60,
          '#required' => TRUE,
          '#error' => '<span class="error">Please enter your email.</span>',
          );

  $form['left_container']['pass'] = array(
          '#type' => 'password',
          '#title' => t('Password'),
          '#required' => TRUE,
          '#error' => '<span class="error">Please enter your password.</span>',
          );

  $form['left_container']['actions'] = array(
          '#type' => 'actions',
          '#prefix' => t('<div class="service-error-message form-item"></div>'),
        );
  $form['left_container']['actions']['submit'] = array(
          '#type' => 'button',
          '#value' => t('Sign In'),
          '#attributes' => array( 'class' => array('sign-in-service-call')),
          '#suffix' => t("<div class='forgot-password'><a class='special-link ctools-use-modal ctools-modal-modal-popup-forgot user-dfs-register' href='@forgot-password'>Forgot your password?</a></div>", array('@forgot-password' => url('user/nojs/psprint/resetpassword'))),
        );

  $form['right_container'] = array(
            '#type' => 'container',
            '#attributes' => array (
                'class' => array('right-container', 'service-user-register-block'),
            ),
         );
  $form['right_container']['cust-guest-subtitle'] = array(
          '#type' => "item",
          '#title' => t("New Customer"),
          );
  $form['right_container']['cust-guest-meta'] = array(
          '#type' => "item",
          '#markup' => t('<div><span class ="guest-meta-title"><strong>In a hurry? Create an account later.
                          </strong></span><span class="guest-meta">Complete your order as a guest.</span></div>'),
          );

  $form['right_container']['continue-guest'] = array(
          '#type' => "item",
          '#markup' => t('<a href="javascript:void(0);" class="close-guest-checkout-box">Continue as Guest</a>'),
          );


  $form['right_container']['cust-create-subtitle'] = array(
          '#type' => "item",
          '#markup' => t('<div><span class ="create-acc-meta-title"><strong>Got a minute? Create an account now.
                          </strong></span><p class="create-acc-meta">It only takes a minute to
                          create a PsPrint account for faster checkout, exclusive
                          deals and the easiest way to access your orders.</p></div>'),
          );

  $form['right_container']['create-account'] = array(
          '#type' => "item",
          '#markup' => t('<a href="/user/nojs/psprint/register" class="create-account ctools-use-modal ctools-modal-modal-popup-register">Create an Account</a>'),
          );

  return $form;
}


/**
 *   user login form
 * @return [type] [description]
 */

function psp_ctools_register_form_build ($ajax) {
  if($ajax) {
    ctools_include('ajax');
    ctools_include('modal');
    $form_state = array('ajax' => TRUE);
    $output = ctools_modal_form_wrapper('psp_user_register_form', $form_state);
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax-commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }
  else {
    return drupal_get_form('psp_user_register_form');
  }
}

/**
 *   user registration form
 * @return [type] [description]
 */

function psp_user_register_form($form, $form_state) {

  drupal_set_title('Create PsPrint Account');
  $tanent_info = &drupal_static('tanent_info');
  $form = array();
  $industry = _psp_industry_array();
  $role = _psp_role_array();
  $settings = array('tenant' =>  array(
                  'registration_api' => variable_get('registration_' . $tanent_info['community'])
                  ),
              );
  drupal_add_js($settings, 'setting');

  $form['prefix_info'] = array (
            '#type' =>'item',
            '#markup' => t("<p>It only takes a minute to create a PsPrint account for fast checkout, exclusive deals and <br/> the best way to access your orders.</p>"),
          );

  $form['left_container'] = array(
            '#type' => 'container',
            '#attributes' => array (
                'class' => array('left-container'),
            ),
          );

  $form['left_container']['firstname'] = array(
            '#type' => 'textfield',
            '#title' => t('First Name <span class= "required">*</span>'),
            '#maxlength' => 15,
            '#error' => '<span class="error">Please enter your first name</span>',
          );

  $form['left_container']['lastname'] = array(
            '#type' => 'textfield',
            '#title' => t('Last Name <span class= "required">*</span>'),
            '#error' =>t('<span class= "error">Please enter your last name.</span>'),
          );

  $form['left_container']['name'] = array(
          '#type' => 'textfield',
          '#title' => t('Username<span class= "required">*</span> (Email address used to create account) '),
          '#maxlength' => 60,
          '#error' => '<span class="error">Please enter your email.</span>',
          );

  $form['left_container']['pass1'] = array(
    '#type' => 'password',
    '#title' => t('Password <span class= "required">*</span>'),
    '#attributes' => array('class' => array('pass-field')),
    '#error' =>t('<span class= "error">Please Enter your password</span>'),
    );

  $form['left_container']['pass2'] = array(
    '#type' => 'password',
    '#title' => t('Confirm Password <span class= "required">*</span>'),
    '#attributes' => array('class' => array('pass-confirm')),
    '#error' =>t('<span class= "error">Please Enter Confirm Password. </span>'),
    );
  $form['left_container']['password_desc'] = array(
        '#markup' => '<div class="register-form-password-desc"> Please enter a password with:
          <ul>
          <li>Minimum of 7 characters</li>
          <li>Maximum of 30 characters</li>
          <li>At least one capital letter</li>
          <li>At least one special character</li></ul></div>',
                  '#weight'=> 36,
    );
        /** right container */
  $form['right_container'] = array(
         '#type' => 'container',
            '#attributes' => array (
                'class' => array('right-container'),
            ),
          );

  $form['right_container']['industry'] = array(
      '#type' => 'select',
       '#title' => t('Industry (Optional)'),
       '#options' => $industry,
       '#default_value' => $industry['Pick One...'],
   );

  $form['right_container']['industry-other'] = array(
  '#type' => 'textfield',
  '#title' => t('Please specify:'),
  '#size' => 60,
  '#maxlength' => 128,
  '#states' => array(
      'visible' => array(
        'select[name="industry"]' => array('value' => 'Other'),
        ),
    ),
  );

  $form['right_container']['role'] = array(
      '#type' => 'select',
       '#title' => t('Role (Optional)'),
       '#options' => $role,
       '#default_value' => $role['Pick One...'],
   );

  $form['right_container']['role-other'] = array(
  '#type' => 'textfield',
  '#title' => t('Please specify:'),
  '#size' => 60,
  '#maxlength' => 128,
  '#states' => array(
      'visible' => array(
        'select[name="role"]' => array('value' => 'Other'),
        ),
    ),

  );

  $form['right_container']['subscription'] = array(
  '#type' => 'checkboxes',
  '#options' => array('1' => ''),
  '#title' => t('Yes! I want PsPrint deals, design tips, and new product announcements via email?'),
  '#default_value' => array("1" ),
  );

  $form['right_container']['actions'] = array(
      '#type' => 'actions',
    );

  $form['right_container']['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Create an Account'),
      '#attributes' => array('class' => array('register-user-service-call')),
      );

  $form['right_container']['actions']['register_form_footer_text'] = array(
        '#markup' => '<div class="register-form-bottom-title">Already have an account?<a href="/user/nojs/psprint/login" class ="special-link ctools-use-modal ctools-modal-modal-popup-login">Log in</a></div>',
    );

  $form['service_error'] = array(
      '#type' => 'item',
      '#markup' => t('<div  class="service-error-message form-item"></div>'),
      );

  return $form;
}



/**
 *   user login form
 * @return [type] [description]
 */

function psp_ctools_reset_form_build($ajax) {
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');
    $form_state = array('ajax' => TRUE, 'title' => t('Forgot Password') );
    $output = ctools_modal_form_wrapper('psp_forgot_pass_form', $form_state);
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax-commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }
  else {
    return drupal_get_form('psp_forgot_pass_form');
  }
}

/**
 * forgot password
 */
function psp_forgot_pass_form($form, $form_state) {
  $tanent_info = &drupal_static('tanent_info');
  $settings = array('tenant' =>  array(
            'forgot_password_api' => variable_get('forgot_password_' .  $tanent_info['community']),
                ),
            );
  drupal_add_js($settings, 'setting');
  $form['request'] = array(
            '#type' => 'container',
            '#attributes' => array (
                'class' => array('request-container'),
            ),
          );
  $form['request']['description'] = array(
            '#type' => 'item',
            '#markup' => t('<div class="forgot-desc">Forgot your password? No worries. We can help. Please enter your email address, and we\'ll email you a link to reset your password.</div>'),
            );
  $form['request']['name'] = array(
            '#type' => 'textfield',
            '#title' => t('Email Address <span class= "required">*</span>'),
            '#description' => '',
            '#maxlength' => 60,
            '#error' => '<span class= "error">Please enter your email.</span>',
            );

  $form['request']['actions'] = array(
            '#type' => 'actions',
            '#prefix' => t('<div class="service-error-message form-item"></div>'),
          );
  $form['request']['actions']['submit'] = array(
            '#type' => 'button',
            '#value' => t('Submit'),
            '#attributes' => array( 'class' => array('forgot-password-service-call')),
            );

  $form['success'] = array(
            '#type' => 'container',
            '#attributes' => array (
                'class' => array('success-container'),
            ),
          );
  $form['success']['title'] = array(
            '#type' => 'item',
            '#markup' => t('<h2 class="title">Thank you</h2>'),
          );
  $form['success']['description'] = array(
            '#type' => 'item',
            '#markup' => t('<div class="section-action">
                            <div class="sub-title">Your password reset link has been emailed to you.</div>
                            <div class="description">
                                If you don\'t receive your new password email please make sure to check your spam or junk folder.
                            </div>
                        </div>'),
          );

  return $form;
}



function _psp_pages_modal_header () {
  ctools_include('modal');
  ctools_modal_add_js();
  // modal form settings
  $throbber = theme('image', array('path' => ctools_image_path('loading_animation.gif', 'dfs_user'), 'alt' => t('Loading...'), 'title' => t('Loading')));
  $js_settings = array(
    'modal-popup-login' => array(
      'modalSize' => array(
        'type' => 'fixed',
        'width' => floatval(830),
        'height' => floatval(480),
      ),
      'modalOptions' => array(
        'opacity' => floatval(0.5),
        'background' => '#666',
        'modaClass' => "psp-login",
      ),
      'animation' => 'fadeIn',
      'modalTheme' => 'PSPModalFormsPopup',
      'throbber' => $throbber,
      'closeText' => t('Close'),
    ),
    'modal-popup-register' => array(
      'modalSize' => array (
        'type' => 'fixed',
        'width' => floatval(722),
        'height' => floatval(600),
      ),
      'modalOptions' => array(
        'opacity' => floatval(0.5),
        'background' => '#666',
        'modaClass' => "psp-registration",
      ),
      'animation' => 'fadeIn',
      'modalTheme' => 'PSPModalFormsPopup',
      'throbber' => $throbber,
      'closeText' => t('Close'),

    ),
    'modal-popup-forgot' => array (
      'modalSize' => array(
        'type' => 'fixed',
        'width' => floatval(620),
        'height' => floatval(297),
      ),
      'modalOptions' => array(
        'opacity' => floatval(0.5),
        'background' => '#666',
        'modaClass' => "psp-forgot-pass",
      ),
      'animation' => 'fadeIn',
      'modalTheme' => 'PSPModalFormsPopup',
      'throbber' => $throbber,
      'closeText' => t('Close'),
    ),
  );

  drupal_add_js($js_settings, 'setting');
  drupal_add_css(drupal_get_path('module', 'dfs_user') . '/css/psp-modal.css' );
  drupal_add_js(drupal_get_path('module', 'dfs_user') . '/js/psp-login.js');
  drupal_add_js(drupal_get_path('module', 'dfs_user') . '/js/psp-registration.js');
  drupal_add_js(drupal_get_path('module', 'dfs_user') . '/js/psp-forgot-pass.js');
  drupal_add_css(drupal_get_path('module', 'dfs_user') . '/css/psp-login-registration.css');
  drupal_add_js(drupal_get_path('module', 'dfs_user') . '/js/login-modal.js',array('weight'=>-20));
}

function _psp_industry_array() {
  $industry = array('Pick One...', 'Advertising/Marketing/PR', 'Arts/Entertainment/Media/Promotion',
  'Education', 'Government', 'Graphic Design', 'Healthcare', 'Non-profit', 'None/Personal Use',
  'Print Reseller/Broker','Real Estate','Retail','Technology','Other');
  return drupal_map_assoc($industry);

}
function _psp_role_array() {
  $role = array('Pick One...','Business (General)','Designer','Manager/Director','Marketer','Owner','Promoter','Other');
  return drupal_map_assoc($role);
}
