(function($){
  Drupal.behaviors.initPSPForgotPass = {
    attach:function(context, settings) {
          var community_id =  settings.tenant.community_id;
          CMS.PSPutils.attachPressEnterSubmitBehaviours();
          var username = $('#psp-forgot-pass-form .form-item-name input', context);
          var username_error = $('#psp-forgot-pass-form .form-item-name .dfs-error', context);
          var username_error_text = $('#psp-forgot-pass-form .form-item-name .dfs-error span', context);

          /*For forgot password api integration*/
           $("#psp-forgot-pass-form .forgot-password-service-call").off("click").click(function(event) {
            $('.service-error-message.form-item').hide();
            attachValidations();
            username.keyup();
            var number = username.val();
            prevent = CMS.PSPutils.invalidFieldCheck($("#psp-forgot-pass-form"));
            if(!prevent) {
                return false;
            }
              var other_user;
              var url = settings.tenant.forgot_password_api;
              $.ajax({
                'url': url,
                'type' : 'POST',
                'data': {
                  "username" : number,
                },
                'xhrFields': {
                    withCredentials: true
                }
              })
              .done(function (webApiResponse) {
                if (webApiResponse.data) {
                  $('.success-container ').show();
                  $('.request-container').hide();

                } else {
                  $(".service-error-message").show().html("<b>*</b> " + webApiResponse.error.message);

                }
              })
              .fail(function(){
                   $(".service-error-message").show().html("<b>*</b> " + CMS.PSPutils.unexpectedApiFailErrorMessage );
              });

           });


          function attachValidations() {
            var UserName = $('#psp-forgot-pass-form .form-item-name input', context);
            CMS.PSPutils.fieldValidationAttachField(UserName);
          }
   }
  };
})(jQuery);
