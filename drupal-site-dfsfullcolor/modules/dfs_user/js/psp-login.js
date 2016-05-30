(function($){
  Drupal.behaviors.initPSPLogin = {
    attach:function(context, settings) {
      var community_id =  Drupal.settings.tenant.community_id;
      $('#psp-user-login-form', context).once('psp-user-login-form',function (){
        login_loading_tracker();
        var static_error_msg = CMS.PSPutils.tenant_configure[community_id]['api_static_error_msg'];
        CMS.PSPutils.attachPressEnterSubmitBehaviours();
        var unexpectedErrorMessage = "An error occurred while processing your request.";
        var username = $('#psp-user-login-form .form-item-name input', context);
        var username_error = $('#psp-user-login-form .form-item-name .dfs-error', context);
        var username_error_text = $('#psp-user-login-form .form-item-name .dfs-error span', context);
        var password = $('#psp-user-login-form  .form-item-pass input', context);
        var password_error = $('#psp-user-login-form .form-item-pass .dfs-error', context);
        var password_error_text = $('#psp-user-login-form .form-item-pass .dfs-error span', context);




          /*
            for login api integration
          */
          $(" #psp-user-login-form .form-item-name input").focus();
            $(".sign-in-service-call").click(function(event) {

              signin_click_tracker();
              $('.service-error-message.form-item').hide();
              var uname = username.val().trim();
              var pass = password.val().trim();
              attachValidations();
              username.keyup();
              password.keyup();
              prevent = CMS.PSPutils.invalidFieldCheck($('#psp-user-login-form'));
              console.log(prevent);
              if(!prevent) {
                return false;
              }

              var other_user;
              var url = settings.tenant.login_api;
              $.ajax({
                'url': url,
                'type' : 'POST',
                'dataType': 'json',
                'data': {
                  "username" : uname,
                  "password" : pass,
                },
                'xhrFields': {
                    withCredentials: true
                }
              })
              .done(function (webApiResponse) {
                if (webApiResponse.data) {
                  _paq.push(['trackEvent', 'Login','Button Click', 'Sign In']);
                  CMS.PSPutils.reloadPageOrRedirect();
                } else {
                  $(".service-error-message").show().html("<b>*</b> " + static_error_msg);
                }
              })
              .fail(function(){
                $(".service-error-message").show().html("<b>*</b> " + CMS.PSPutils.unexpectedApiFailErrorMessage );
              })
            });





        function attachValidations() {
          var UserName = $('#psp-user-login-form .form-item-name input', context);
          var Pass = $('#psp-user-login-form .form-item-pass input', context);
          CMS.PSPutils.fieldValidationAttachField(UserName);
          CMS.PSPutils.fieldValidationAttachField(Pass);
          }


        $('.close-guest-checkout-box').on('click',function(){
          continue_guest_login_tracker();
          $("#isloading-overlay-d").show();
           Drupal.CTools.Modal.dismiss();
           window.location.reload();
        });

        $('.create-account').on('click',function(){
          create_account_click_tracker();
        });

        $('.forgot-password a').on('click',function(){
          forgot_pass_click_tracker();
        });
        function create_account_click_tracker() {
          s.events='event7';
          s.t();
          window.universal_variable.events.push({'category': 'login', 'action': 'create-account'});
          dataLayer.push({'form': {'title': 'create-account'}, 'event': 'submit-form'});
        }

        function continue_guest_login_tracker(){
          s.events='event8';
          s.t();
          _paq.push(['trackEvent', 'Login','Button Click', 'Continue as Guest']);
          window.universal_variable.events.push({'category': 'login', 'action': 'guest-login'});
          dataLayer.push({'button': {'title': 'guest-login'}, 'event': 'button'});
        }

        function forgot_pass_click_tracker() {
          s.events='event48';
          s.t();
        }

        function signin_click_tracker() {
          s.events='event6';
          s.t();
          window.universal_variable.events.push({'category': 'login', 'action': 'account-signin'});
          dataLayer.push({'form': {'title': 'account-signin'}, 'event': 'submit-form'});
        }

        function login_loading_tracker() {
            /**omniture code * */
           s.pageName = "PsPrint:Home:Login";
           s.channel = "Checkout:Login";
           s.prop1 = "PsPrint";
           s.prop2="PsPrint:Main";
           s.prop3 = "PsPrint:Main:Login";
           s.prop4 = "Checkout:Login";
           s.events = 'event20';
           s.eVar10="Small Business";
           s.eVar42="PsPrint:Login";
           s.eVar46 = "PsPrint:Login";
           s.eVar4 = null;
           s.products = null;
           s.t();
           trackBasicPixel(3, settings.tenant.environment, 904595, settings.tenant.sitename, 1, getCookieTrack('_ph_ps_session_id'),'document.ready');
           window.universal_variable.events.push({'category': 'popup', 'action': 'login'});
           dataLayer.push({'popup': {'title': 'login'}, 'event': 'popup'});
        }
      });
   }
  };
})(jQuery);
