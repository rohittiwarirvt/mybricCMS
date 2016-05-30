(function($){
  Drupal.behaviors.initDFSForgotPass = {
    attach:function(context, settings) {
          var tenant_configure = {
            '13' : {
              username_regex : "^[0-9]+$" ,
              username_message :"Please enter Company Phone number." ,
              username_invalid_message : "Please enter valid Company Phone number." ,
              api_static_error_msg: "Invalid Dealer Phone/Password",
                  },
            '11' : {
              username_regex : "^[\\w\\.-]*[a-zA-Z0-9_]@[\\w\\.-]*[a-zA-Z0-9]\\.[a-zA-Z][a-zA-Z\\.]*[a-zA-Z]$" ,
              username_message :"Please enter Email address." ,
              username_invalid_message : "Please enter valid Email address." ,
              api_static_error_msg : "Login failed. Please enter correct email address/password and try again."
                  }
          };
          var community_id =  Drupal.settings.tenant.community_id;
          attachBehaviours();
          attachCloseTrigger();
          $(document).bind("ajaxSend", function(){
            $(".ajax-loader").show();
            }).bind("ajaxComplete", function(){
            $(".ajax-loader").hide();
          });
          var unexpectedErrorMessage = "An error occurred while processing your request.";
          var username = $('#dfs-user-forgot-password .form-item-name input', context);
          var username_error = $('#dfs-user-forgot-password .form-item-name .dfs-error', context);
          var username_error_text = $('#dfs-user-forgot-password .form-item-name .dfs-error span', context);

          /*For forgot password api integration*/
           $("#dfs-user-forgot-password .forgot-password-service-call").off("click").click(function(event) {
            var prevent = 1;
            $('.service-error-message.form-item').hide();
            attachValidations();
            username.keyup();
            var number = username.val();
            $(".invalid" ).each(function(index) {
              if (index==0) {
                $(this).focus();
                prevent = 0;
              }
            });
            if(!prevent) {
                return false;
            }
              var other_user;


              var url = Drupal.settings.tenant.forgot_password_api;
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
                  if( webApiResponse.error.message ==="Please enter a valid email.") {
                    webApiResponse.error.message = tenant_configure[community_id]['username_invalid_message'];
                  }
                  $(".service-error-message").show().html("<b>*</b> " + webApiResponse.error.message);

                }
              })
              .fail(function(){
                $(".service-error-message").show().html("<b>*</b> " + unexpectedErrorMessage );
              });

           });

          function validateUsername(name) {
            var regex = new RegExp(tenant_configure[community_id]['username_regex']);
            return regex.test(name);
          }
          function attachValidations() {
            var UserName = $('#dfs-user-forgot-password .form-item-name input', context);
            attachField(UserName);

          }

        function attachField(field) {
          var error = field.parent().find('.dfs-error');
          var error_text = field.parent().find('.name-error');
          var cond;
          field.bind('keyup change',function() {
            var field_val = field.val().trim();
            if(field.parent().hasClass('form-item-name')) {
              var valid_phone = validateUsername(field_val);
              cond = field_val.length && valid_phone;
              if(field_val.length && !valid_phone) {
                  error_text.text(tenant_configure[community_id]['username_invalid_message']);
              }
              else{
                  error_text.text(tenant_configure[community_id]['username_message']);
              }
            }
            else {
              cond = field_val.length;
            }
            if (cond) {
              error.hide();
              $('.service-error-message.form-item').hide();
              field.removeClass('invalid');
            }
            else {
              error.show();
              field.addClass('invalid');
            }
          });
        }

        function attachBehaviours() {
          $(this).keydown(function(event) {
            if (event.keyCode == 13) {
              event.preventDefault();
              $('.form-submit').click();
            }
           });
        }
        function attachCloseTrigger() {
          $('.close-wrapper.close').click(function(){
             window.location.reload(true);
          });
        }
   }
  };
})(jQuery);
