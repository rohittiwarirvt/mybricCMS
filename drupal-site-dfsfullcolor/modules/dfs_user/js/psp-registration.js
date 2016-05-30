(function($){
  Drupal.behaviors.initPSPRegistration = {
    attach:function(context, settings) {
          var error_message_override;
          var community_id =  Drupal.settings.tenant.community_id;
          $('#psp-user-register-form', context).once('psp-registration',function(){
             register_load_tracker();
              CMS.PSPutils.attachPressEnterSubmitBehaviours();
              attachRegistration();

            });


          function attachRegistration() {
              var unexpectedErrorMessage = "An error occurred while processing your request.";
              var url = settings.tenant.registration_api;
              $(".register-user-service-call", context).click(function(event) {
                $('.service-error-message.form-item').hide();
                register_click_tracker();
                var UserName = $('#psp-user-register-form  .form-item-name input', context);
                var Passwords = $('#psp-user-register-form .form-item-pass1 input', context);
                var ConfirmPassword = $('#psp-user-register-form  .form-item-pass2 input', context);
                var FirstName = $('#psp-user-register-form .form-item-firstname input', context);
                var LastName = $('#psp-user-register-form .form-item-lastname input', context);
                var Industry = $('#psp-user-register-form .form-item-industry select option:selected', context);
                var Role = $('#psp-user-register-form .form-item-role select option:selected', context);
                var IndustryOther = $('#psp-user-register-form .form-item-industry-other input', context);
                var RoleOther = $('#psp-user-register-form .form-item-role-other input', context);
                var EmailSubscriptionChecked = $('#psp-user-register-form .form-item-subscription input').is(':checked');
                CMS.PSPutils.fieldValidationAttachField(UserName);
                CMS.PSPutils.fieldValidationAttachField(FirstName);
                CMS.PSPutils.fieldValidationAttachField(LastName);
                CMS.PSPutils.fieldValidationAttachField(Passwords);

                password_conform_validation();
                UserName.keyup();
                Passwords.keyup();
                ConfirmPassword.keyup();
                FirstName.keyup();
                LastName.keyup();

                prevent = CMS.PSPutils.invalidFieldCheck($("#psp-user-register-form"));

                if(!prevent) {
                  return false;
                }


                $.ajax({
                'url': url,
                'type': 'POST',
                'dataType': 'json',
                'data': {
                  "FirstName": FirstName.val().trim(),
                  "LastName": LastName.val().trim(),
                  "Email": UserName.val().trim(),
                  "Password": Passwords.val().trim(),
                  "ConfirmPassword": ConfirmPassword.val().trim(),
                  "Industry": Industry.val().trim(),
                  "Role": Role.val().trim(),
                  "IndustryOther": Industry.val().trim(),
                  "RoleOther": Role.val().trim(),
                  "EmailSubscriptionChecked": EmailSubscriptionChecked,
                },
                'xhrFields': {
                      withCredentials: true
                  }
              })
              .done(function (webApiResponse) {
                  if (webApiResponse.data) {
                      _paq.push(["trackEvent", "Login", "Button Click", "Create an Account"]);
                      CMS.PSPutils.reloadPageOrRedirect();
                  } else {
                    $(".service-error-message").show().html("<b>*</b> " + webApiResponse.error.message);
                  }
              })
              .fail(function(webApiResponse){
                  $(".service-error-message").show().html("<b>*</b> " + CMS.PSPutils.tenant_configure[community_id].unexpectedApiFailErrorMessage );
              });
            });
          }

          function register_load_tracker() {
            trackBasicPixel(3, settings.tenant.environment, 904596, settings.tenant.sitename, 1, getCookieTrack('_ph_ps_session_id'), 'document.ready');
            window.universal_variable.events.push({
              'category': 'popup',
              'action': 'create-account'
            });
            dataLayer.push({
              'popup': {
              'title': 'create-account'
              },
             'event': 'popup'
            });
          }
        function register_click_tracker() {
            window.universal_variable.events.push({
              'category': 'login',
              'action': 'create-account'
            });
            dataLayer.push({
              'form': {
              'title': 'create-account'
            },
              'event': 'submit-form'
            });
        };
        function password_conform_validation() {
          var pass = $('#psp-user-register-form .form-item-pass1', context);
          var pass_confirm = $('#psp-user-register-form .form-item-pass2', context);
          var pass_val = pass.find('input').val().trim();
          var pass_confirm_input = pass_confirm.find('input');
          var pass_confirm_val = pass_confirm.find('input').val().trim();
          var pass_confirm_error_text = pass_confirm.find('.dfs-error span');
          var pass_confirm_error = pass_confirm.find('.dfs-error');
          pass_confirm_input.bind('keyup change',function() {
            if(!pass_confirm_val.length) {
                 pass_confirm_error.show();
                 pass_confirm_error_text.text(CMS.PSPutils.tenant_configure[community_id]['password_message']);
                 pass_confirm.addClass('invalid');
            }
            else if (pass_confirm_val.length && pass_val !== pass_confirm_val){
              pass_confirm_error.show();
              pass_confirm_error_text.text(CMS.PSPutils.tenant_configure[community_id]['password_confirm_invalid_message']);
              pass_confirm.addClass('invalid');
            }
            else {
              $(this).addClass('valid');
              pass_confirm_error.hide();
              $('.service-error-message.form-item').hide();
              pass_confirm.removeClass('invalid');
            }
          });
        }
    }
  };
})(jQuery);
