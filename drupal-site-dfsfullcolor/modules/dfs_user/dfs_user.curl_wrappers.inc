<?php

function _dfs_session_maintain() {
  $tanent_info = &drupal_static('tanent_info');
  if($tanent_info['community_id'] == 12){
    return false;
  }
  global $user;
  global $base_url;

 $path_url = request_uri();
    if (array_key_exists('_psp_ecommerce_sid',$_COOKIE)) {
      $psprint_session_id = $_COOKIE['_psp_ecommerce_sid'];
      $cookies = '_psp_ecommerce_sid=' . $psprint_session_id . ';';
      $curl_obj = &drupal_static("curl_obj");
      $curl_obj = new cUrl($cookies);

      $json_result = _dfs_user_loggedin_state();
      $fields = $json_result['data'];
      $_SESSION['FirstName'] = ($fields['firstName']!='') ? $fields['firstName'] : 'Guest';
      if (isset($fields) && !empty($fields['userID']) && user_is_logged_in()){
        $user_obj = user_load($user->uid);
        $user_obj->field_user_first_name[LANGUAGE_NONE][0]['value'] = $fields['firstName'];
        user_save($user_obj);
      }
      else if(isset($fields) && !user_is_logged_in()){
       _dfs_user_session_state($fields);
      }
      else {
       $user_logout = _dfs_user_logout();
      }
    }
  }

function _dfs_user_load_by_UserId($UserId) {
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'user')
   ->fieldCondition('field_userid', 'value', $UserId);
  $result = $query->execute();
  $users_id = array_keys($result['user']);
  return $users_id;
}

function _dfs_user_session_state($fields) {
  $users_id =_dfs_user_load_by_UserId($fields['userID']);
  if ($users_id) {
    $form_state = array ();
    $form_state ['uid'] = $users_id;
    $form_state['redirect'] = false;
    user_login_submit ( array (), $form_state );
  }
  else  {
      _dfs_user_create_account($fields);
  }
}


function _dfs_user_loggedin_state() {
  $tanent_info = &drupal_static('tanent_info');
  global $base_url;
  $session_state_api = $base_url .  variable_get('loggedin_session_' . $tanent_info['community']);
  $curl_obj = &drupal_static("curl_obj");
  $result = $curl_obj->get($session_state_api);
  return $result;
}



/**
 * Curl class
 */

class cURL {
  var $headers;
  var $user_agent;
  var $compression;
  var $cookies;
  var $proxy;

  function cURL($cookies='',$compression='gzip',$proxy='') {
    $this->headers[] = 'Connection: Keep-Alive';
    $this->headers[] = 'Content-type: application/x-www-form-urlencoded;charset=UTF-8';
    //$this->user_agent = $_SERVER['HTTP_USER_AGENT'];
    $this->compression = $compression;
    $this->proxy = $proxy;
    $this->cookies = $cookies;
  }

  function get($url) {
    $process = curl_init($url);
    curl_setopt($process, CURLOPT_HTTPHEADER, $this->headers);
    curl_setopt($process, CURLOPT_HEADER, 0);
    curl_setopt ($process, CURLOPT_SSL_VERIFYPEER, 0);
    curl_setopt ($process, CURLOPT_SSL_VERIFYHOST, 0);
    curl_setopt ($process, CURLOPT_COOKIE,$this->cookies);
    curl_setopt($process,CURLOPT_ENCODING , $this->compression);
    curl_setopt($process, CURLOPT_TIMEOUT, 30);
    if ($this->proxy) curl_setopt($process, CURLOPT_PROXY, $this->proxy);
    curl_setopt($process, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($process, CURLOPT_FOLLOWLOCATION, 1);
    $return = curl_exec($process);
    curl_close($process);
    return drupal_json_decode($return);
  }

  function post($url,$data) {
    $process = curl_init($url);
    curl_setopt($process, CURLOPT_HTTPHEADER, $this->headers);
    curl_setopt($process, CURLOPT_HEADER, 0);
    curl_setopt ($process, CURLOPT_SSL_VERIFYPEER, 0);
    curl_setopt ($process, CURLOPT_SSL_VERIFYHOST, 0);
    curl_setopt ($process, CURLOPT_COOKIE,$this->cookies);
    curl_setopt($process, CURLOPT_ENCODING , $this->compression);
    curl_setopt($process, CURLOPT_TIMEOUT, 30);
    if ($this->proxy) curl_setopt($process, CURLOPT_PROXY, $this->proxy);
    if (!empty($data)) curl_setopt($process, CURLOPT_POSTFIELDS, $data);
    curl_setopt($process, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($process, CURLOPT_POST,1 );
    curl_setopt($process, CURLOPT_FOLLOWLOCATION, 1);
    $return = curl_exec($process);
    curl_close($process);
    return drupal_json_decode($return);
  }

  function error($error) {
    echo "<center><div style='width:500px;border: 3px solid #FFEEFF; padding: 3px; background-color: #FFDDFF;font-family: verdana; font-size: 10px'><b>cURL Error</b><br>$error</div></center>";
    die;
  }
}

