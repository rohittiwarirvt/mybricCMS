<?php

/**
 * form array builder
 */

function dfs_register_form() {
  $tanent_info = &drupal_static('tanent_info');
  $form = array();
    $form['button_close'] = array (
    '#type' =>'item',
    '#markup' => t('<span class="close-wrapper close">Close</span>'),
   );

  $settings = array('tenant' =>  array(
                  'registration_api' => variable_get('registration_' . $tanent_info['community'])
                  ),
              );
  drupal_add_js($settings, 'setting');

   switch ($tanent_info['community_id']) {
      case '13':
        {
          $form['prefix_info'] = array (
            '#type' =>'item',
            '#markup' => t("<p>Please complete this form to gain access to DFS' Full Color program  designed exclusively for dealers. If you are already a DFS dealer, please indicate that below. If you are new to DFS, welcome! Please note that this site is for resellers only. Registrations will be reviewed to verify you are a reseller (ie: printer, graphic designer, etc.)</p>"),
          );

          $form['checkbox_first'] = array(
            '#type' => 'checkbox',
            '#title' => t('I am currently a DFS Dealer'),
          );

          $form['checkbox_second'] = array(
            '#type' => 'checkbox',
            '#default_value' => TRUE,
            '#title' => t('I would like to sign-up to become a DFS Dealer'),
          );

          $form['form_wrapper_title'] = array(
            '#type' =>'item',
            '#markup' => t("<h2> Create DFS Full Color Site Access </h2>"),
          );

          $form['left_container'] = array(
            '#type' => 'container',
            '#attributes' => array (
                'class' => array('left-container'),
            ),
          );

        $form['left_container']['phone'] = array(
            '#type' => 'phone_confirm',
            '#title' => t('Company Phone Number'),
            '#required' => TRUE,
            '#description' => t('Please do not include special characters like (, ), -, <space>'),
            '#maxlength' => 15,

          );

          $form['left_container']['company_name'] = array(
            '#type' => 'textfield',
            '#title' => t('Company Name'),
            '#required' => TRUE,
            '#error' =>t('<span>Please enter Company Name.</span>'),
          );

          $form['left_container']['first_name'] = array(
            '#type' => 'textfield',
            '#title' => t('First Name'),
            '#required' => TRUE,
            '#error' =>t('<span>Please Enter Contact Name.</span>'),
          );

          $form['left_container']['last_name'] = array(
            '#type' => 'textfield',
            '#title' => t('Last Name'),
            '#required' => TRUE,
            '#error' =>t('<span>Please Enter Last Name.</span>'),
          );

          $form['left_container']['email_confirm'] = array(
            '#type' => 'email_confirm',
            '#title' => t('Default Email address'),
            '#required' => TRUE,

          );


        /** right container */
         $form['right_container'] = array(
            '#type' => 'container',
            '#attributes' => array (
                'class' => array('right-container'),
            ),
          );

          $form['right_container']['address1'] = array(
            '#type' => 'textfield',
            '#title' => t('Billing Address'),
            '#required' => TRUE,
            '#error' =>t('<span>Please Enter Billing Address1.</span>'),
          );

          $form['right_container']['address2'] = array(
            '#type' => 'textfield',
            '#title' => t('Address 2'),
            '#error' =>t('<span></span>'),
          );

          $form['right_container']['extensions_wrapper'] = array(
            '#type' => 'container',
            '#attributes' => array(
              'class' => array('extension-wrapper')
             ),
            '#required' => TRUE,

          );

          $form['right_container']['extensions_wrapper']['city'] = array(
            '#type' => 'textfield',
            '#size' => '5',
            '#prefix' => t('<label for="extension">City, State, Zipcode <span class="form-required" title="This field is required.">*</span></label>'),
                '#required' => TRUE,
            '#error' =>t('<span>Please Enter City.</span>'),
          );

          $form['right_container']['extensions_wrapper']['state'] = array(
            '#type' => 'textfield',
            '#size' => '5',
            '#required' => TRUE,
            '#error' =>t('<span>Please Enter State.</span>'),
          );

          $form['right_container']['extensions_wrapper']['zipcode'] = array(
            '#type' => 'textfield',
            '#size' => '10',
            '#required' => TRUE,
            '#error' =>t('<span>Please Enter Zipcode.</span>'),
          );

          $form['right_container']['dealer_type'] = array(
            '#type' => 'textfield',
            '#title' => t('Dealer type (i.e. printer, graphic, designer, etc.)'),
            '#required' => TRUE,
            '#error' =>t('<span> Please Enter Dealer Type.</span>'),
          );

          $form['right_container']['pass_confirm'] = array(
            '#type' => 'pass_confirm',
            '#title' => t('Registration Password'),
            '#required' => TRUE,
          );

          $form['right_container']['actions'] = array(
            '#type' => 'actions',
            );

          $form['right_container']['actions']['submit'] = array(
            '#type' => 'submit',
            '#value' => t('Create DFS Full Color Registration'),
            '#attributes' => array('class' => array('register-user-service-call')),
            );
          $form['service_error'] = array(
            '#type' => 'item',
            '#markup' => t('<div class="service-error-message form-item"></div>'),
          );
      }

        break;
      case '11': {
          $form['prefix_info'] = array (
            '#type' =>'item',
            '#markup' => t("<p>Please complete this form to gain access to The SFS Group’s full color program  designed exclusively for dealers. If you are already a DFS dealer, please indicate that below. If you are new to DFS, welcome! Please note that this site is for resellers only. Registrations will be reviewed to verify you are a reseller (ie: printer, graphic designer, etc.)</p>"),
          );

          $form['checkbox_first'] = array(
            '#type' => 'checkbox',
            '#title' => t('I am currently a DFS Dealer'),
          );

          $form['checkbox_second'] = array(
            '#type' => 'checkbox',
            '#default_value' => TRUE,
            '#title' => t('I would like to sign-up to become a DFS Dealer'),
          );

          $form['form_wrapper_title'] = array(
            '#type' =>'item',
            '#markup' => t("<h2> Create DFS Full Color Site Access </h2>"),
          );

          $form['left_container'] = array(
            '#type' => 'container',
            '#attributes' => array (
                'class' => array('left-container'),
            ),
          );

        $form['left_container']['phone'] = array(
            '#type' => 'phone_confirm',
            '#title' => t('Company Phone Number'),
            '#required' => TRUE,
            '#description' => t('Please do not include special characters like (, ), -, <space>'),
            '#maxlength' => 15,

          );

          $form['left_container']['company_name'] = array(
            '#type' => 'textfield',
            '#title' => t('Company Name'),
            '#required' => TRUE,
            '#error' =>t('<span>Please enter Company Name.</span>'),
          );

          $form['left_container']['first_name'] = array(
            '#type' => 'textfield',
            '#title' => t('First Name'),
            '#required' => TRUE,
            '#error' =>t('<span>Please Enter Contact Name.</span>'),
          );

          $form['left_container']['last_name'] = array(
            '#type' => 'textfield',
            '#title' => t('Last Name'),
            '#required' => TRUE,
            '#error' =>t('<span>Please Enter Last Name.</span>'),
          );

          $form['left_container']['email_confirm'] = array(
            '#type' => 'email_confirm',
            '#title' => t('Default Email address'),
            '#required' => TRUE,

          );


        /** right container */
         $form['right_container'] = array(
            '#type' => 'container',
            '#attributes' => array (
                'class' => array('right-container'),
            ),
          );

          $form['right_container']['address1'] = array(
            '#type' => 'textfield',
            '#title' => t('Billing Address'),
            '#required' => TRUE,
            '#error' =>t('<span>Please Enter Billing Address1.</span>'),
          );

          $form['right_container']['address2'] = array(
            '#type' => 'textfield',
            '#title' => t('Address 2'),
            '#error' =>t('<span></span>'),
          );

          $form['right_container']['extensions_wrapper'] = array(
            '#type' => 'container',
            '#attributes' => array(
              'class' => array('extension-wrapper')
             ),
            '#required' => TRUE,

          );

          $form['right_container']['extensions_wrapper']['city'] = array(
            '#type' => 'textfield',
            '#size' => '5',
            '#prefix' => t('<label for="extension">City, State, Zipcode <span class="form-required" title="This field is required.">*</span></label>'),
                '#required' => TRUE,
            '#error' =>t('<span>Please Enter City.</span>'),
          );

          $form['right_container']['extensions_wrapper']['state'] = array(
            '#type' => 'textfield',
            '#size' => '5',
            '#required' => TRUE,
            '#error' =>t('<span>Please Enter State.</span>'),
          );

          $form['right_container']['extensions_wrapper']['zipcode'] = array(
            '#type' => 'textfield',
            '#size' => '10',
            '#required' => TRUE,
            '#error' =>t('<span>Please Enter Zipcode.</span>'),
          );

          $form['right_container']['dealer_type'] = array(
            '#type' => 'textfield',
            '#title' => t('Dealer type (i.e. printer, graphic, designer, etc.)'),
            '#required' => TRUE,
            '#error' =>t('<span> Please Enter Dealer Type.</span>'),
          );

          $form['right_container']['pass_confirm'] = array(
            '#type' => 'pass_confirm',
            '#title' => t('Registration Password'),
            '#required' => TRUE,
          );

          $form['right_container']['actions'] = array(
            '#type' => 'actions',
            );

          $form['right_container']['actions']['submit'] = array(
            '#type' => 'submit',
            '#value' => t('Create DFS Full Color Registration'),
            '#attributes' => array('class' => array('register-user-service-call')),
            );
          $form['service_error'] = array(
            '#type' => 'item',
            '#markup' => t('<div class="service-error-message form-item"></div>'),
          );
      }
        break;
      default:
        # code...
        break;
    }


  return $form;
}


/**
 *  login form arrays
 */

function dfs_user_form($form, &$form_state) {
  global $user;
  $tanent_info = &drupal_static('tanent_info');
  drupal_set_title('Welcome to ' . $tanent_info['community']);
  $settings = array('tenant' =>  array(
                  'login_api' => variable_get('login_' .  $tanent_info['community']),
                  ),
              );
  drupal_add_js($settings, 'setting');
  // If we are already logged on, go to the user page instead.
  if ($user->uid && isset($_GET['destination'])) {
    drupal_goto($_GET['destination']);
  }else if($user->uid){
    drupal_goto('/myaccount');
  }
  switch ($tanent_info['community_id']) {
    case '13':
      {
        $form['returning_delar'] = array(
          '#markup' => t('<div class="login-form-title">Returning Dealer <br /><span class="login-subtitle">Please login to your account now.</span></div>'),
          );
        $form['name'] = array(
          '#type' => 'textfield',
          '#title' => t('Dealer Phone Number'),
          '#description' => t('(Please do not include special characters like (, ), -, &lt;space&gt;)'),
          '#maxlength' => 60,
          '#required' => TRUE,
          '#error' => '<span class="name-error">Please enter Company Phone number.</span>',
          );

        $form['pass'] = array(
          '#type' => 'password',
          '#title' => t('Dealer Password'),
          '#required' => 'true',
          '#error' => '<span class="password-error">Please enter Password.</span>',
          );
        $form['forgot-pass'] = array(
          '#type' => 'item',
          '#markup' => t("<div class='forgot-password'><a class='ajax-link user-dfs-register' href='@forgot-password'>Forgot your password?</a></div>", array('@forgot-password' => url('PasswordReset'))),
         );
        $form['actions'] = array(
          '#type' => 'actions',
          '#prefix' => t('<div class="service-error-message form-item"></div>'),
        );
        $form['actions']['submit'] = array(
          '#type' => 'button',
          '#value' => t('Enter ' . $tanent_info['community']),
          '#attributes' => array( 'class' => array('sign-in-service-call')),
          '#suffix' => t("<div class='edit-register'> <p>New to DFS Full Color. <a class='ajax-link user-dfs-register' href='@register'>Click Here</a></p></div>", array('@register' =>url('dfs/user/register'))),

          );
      }
      # code...
      break;
    case '11':
      {
        $form['returning_delar'] = array(
          '#markup' => t('<div class="login-form-title">Returning Distributor <br /><span class="login-subtitle">Please login to your account now.</span></div>'),
          );
        $form['name'] = array(
          '#type' => 'textfield',
          '#title' => t('Distributor email.'),
          '#maxlength' => 60,
          '#required' => TRUE,
          '#error' => '<span class="name-error">Please enter Email Address.</span>',
          );

        $form['pass'] = array(
          '#type' => 'password',
          '#title' => t('Distributor password.'),
          '#required' => 'true',
          '#error' => '<span class="password-error">Please enter Password.</span>',
          );
        $form['forgot-pass'] = array(
          '#type' => 'item',
          '#markup' => t("<div class='forgot-password'><a class='ajax-link user-dfs-register' href='@forgot-password'>Forgot your password?</a></div>", array('@forgot-password' => url('PasswordReset'))),
         );
        $form['actions'] = array(
          '#type' => 'actions',
          '#prefix' => t('<div class="service-error-message form-item"></div>'),
        );
        $form['actions']['submit'] = array(
          '#type' => 'button',
          '#value' => t('Enter ' . $tanent_info['community']),
          '#attributes' => array( 'class' => array('sign-in-service-call')),
        );
      }
      break;
    default:
      # code...
      break;
  }


  return $form;
}

function dfs_user_forgot_password($form, &$form_state) {
  $tanent_info = &drupal_static('tanent_info');
  $settings = array('tenant' =>  array(
            'forgot_password_api' => variable_get('forgot_password_' .  $tanent_info['community']),
                ),
            );
  drupal_add_js($settings, 'setting');
    $form['button_close'] = array (
    '#type' =>'item',
    '#markup' => t('<span class="close-wrapper close">Close</span>'),
   );
  switch ($tanent_info['community_id']) {
      case '13':
        {
          $form['request'] = array(
            '#type' => 'container',
            '#attributes' => array (
                'class' => array('request-container'),
            ),
          );
          $form['request']['description'] = array(
            '#type' => 'item',
            '#markup' => t('<div class="register-desc">Please enter the phone number used when setting up the account. We will send a link to the profile email address on the account to a page where you can reset your password.</div>'),
            );
          $form['request']['name'] = array(
            '#type' => 'textfield',
            '#title' => t('Dealer Phone Number'),
            '#description' => '',
            '#maxlength' => 60,
            '#required' => TRUE,
            '#error' => '<span class="name-error">Please enter a Phone number.</span>',
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
        }
        break;
      case '11':
        {
          $form['request'] = array(
            '#type' => 'container',
            '#attributes' => array (
                'class' => array('request-container'),
            ),
          );
          $form['request']['description'] = array(
            '#type' => 'item',
            '#markup' => t('<div class="register-desc">Please enter the email address used when setting up the account. We will send a link to the profile email address on the account to a page where you can reset your password.</div>'),
            );
          $form['request']['name'] = array(
            '#type' => 'textfield',
            '#title' => t('Username (Email address used to create account)'),
            '#description' => '',
            '#maxlength' => 60,
            '#required' => TRUE,
            '#error' => '<span class="name-error">Please enter a Phone number.</span>',
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
        }
        break;
      default:
        # code...
        break;
    }

  return $form;
}
/**
 * [dfs_user_authenticate description]
 * @param  [integer] $name     [description]
 * @param  [varchar] $password [description]
 * @return            []
 */
function _dfs_user_authenticate($name, $password) {
  $uid = FALSE;
  if (!empty($name) && !empty($password)) {
    $account = user_load_by_name($name);
    if ($account) {
      // Allow alternate password hashing schemes.
      require_once DRUPAL_ROOT . '/' . variable_get('password_inc', 'includes/password.inc');
      if (user_check_password($password, $account)) {
        // Successful authentication.
        $uid = $account->uid;

        // Update user to new password scheme if needed.
        if (user_needs_new_hash($account)) {
          user_save($account, array('pass' => $password));
        }
      }
    }
  }
  return $uid;
}

function dfs_auth_register_form_build() {
  $dfs_register_login = drupal_get_form('dfs_register_form');
  $output = render($dfs_register_login);
  $pageout = theme('dfs_auth_page', array('content'=> $output));
  print $pageout;
}

/**
 * Page call back for authenticate user
 */

function dfs_auth_user_form_build() {
  $dfs_user_login = drupal_get_form('dfs_user_form');
  $output = render($dfs_user_login);
  $pageout = theme('dfs_auth_page', array('content'=> $output));
  print $pageout;
}

function dfs_auth_forgot_password_form_build() {
  $dfs_forgot_password = drupal_get_form('dfs_user_forgot_password');
  $output = render($dfs_forgot_password);
  $pageout = theme('dfs_auth_page', array('content' => $output));
  print $pageout;
}


function _dfs_user_authentication_api(){
  return array('_dfs_user_validate','_dfs_user_login_authenticate_validate');
}

function _dfs_user_validate( $form, &$form_state ){
  if(!empty($form_state['values']['name']) && !empty($form_state['values']['pass'])) {
    $form_state['result'] = _dfs_user_authenticate_api($form_state['values']['name'], $form_state['values']['pass']);
  }
}


/**
 * A validate handler on the login form. Check supplied username/password
 * against local users table. If successful, $form_state['uid']
 * is set to the matching user ID.
 */
function _dfs_user_login_authenticate_validate($form, &$form_state) {
  $password = trim($form_state['values']['pass']);
  if (isset($form_state['result']) && !empty($form_state['result']['Data'])) {
    $password= $form_state['result']['Data']['UserID'];
  }
  if (!empty($form_state['values']['name']) && !empty($password)) {
    $account = db_query("SELECT * FROM {users} WHERE name = :name AND status = 1", array(':name' => $form_state['values']['name']))->fetchObject();
    // We are not limited by flood control, so try to authenticate.
    // Set $form_state['uid'] as a flag for user_login_final_validate().
    $form_state['uid'] = _dfs_user_authenticate($form_state['values']['name'], $password);
  }
  if (isset($form_state['result']) && is_int($form_state['result']['Error']['Code']) && empty($form_state['uid'])) {
    form_set_error('authentication',t('%error',array('%error' => $form_state['result']['Error']['Message'])));
  }
  else if(isset($form_state['result']) && isset($form_state['result']['Data']['UserID']) && empty($form_state['uid'])) {
    _dfs_user_create_account($form_state);
  }
  else if(empty($form_state['uid'])){
        form_set_error('name',t('Enter Correct username and password'));
  }
}


/**
 * Creates a new account
 * @return [type] [description]
 */
function _dfs_user_create_account($fields) {
  require_once DRUPAL_ROOT . '/' . variable_get ( 'password_inc', 'includes/password.inc' );
    // Register this new user.
  $account = new stdClass ();
  $account->is_new = TRUE;
  $account->name = $fields['userID'];
  $account->pass = user_hash_password ($fields['userID']);
  $account->mail = $fields['firstName'];
  $account->init = $fields['firstName'];
  $account->field_user_first_name[LANGUAGE_NONE][0]['value'] = $fields['firstName'];
  $account->field_userid[LANGUAGE_NONE][0]['value'] = $fields['userID'];
  $account->status = TRUE;
  $account->roles = array (
                      DRUPAL_AUTHENTICATED_RID => 'authenticated user'
                    );
  $user_obj = user_save ($account);
  $form_state['uid'] = $user_obj->uid;
}



function _dfs_user_registeration_api() {
  return array("_dfs_user_reg_validation", "_dfs_user_registration");
}

function _dfs_user_reg_validation($form, &$form_state) {

}

function _dfs_user_registration($form, &$form_state) {

}
