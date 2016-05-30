(function($){
  Drupal.behaviors.initDFSLogin = {
    attach:function(context, settings) {
      var tenant_configure = {
        '13' : {
          username_regex : "^[0-9]+$" ,
          username_message :"Please enter Company Phone number." ,
          username_invalid_message : "Please enter valid Company Phone number." ,
          api_static_error_msg: "Invalid Dealer Phone/Password",
              },
        '11' : {
          username_regex : "^[\\w\\.-]*[a-zA-Z0-9_]@[\\w\\.-]*[a-zA-Z0-9]\\.[a-zA-Z][a-zA-Z\\.]*[a-zA-Z]$",
          username_message :"Please enter Email address." ,
          username_invalid_message : "Please enter valid Email address." ,
          api_static_error_msg: "Login failed. Please enter correct email address/password and try again.",
              }
      };
      var community_id =  Drupal.settings.tenant.community_id;
      $('#dfs-user-form', context).once('dfs-user-form',function (){
          var static_error_msg = tenant_configure[community_id]['api_static_error_msg'];
          attachBehaviours();
          attachCloseTrigger();
          $(document).bind("ajaxSend", function(){
            $(".ajax-loader").show();
            }).bind("ajaxComplete", function(){
            $(".ajax-loader").hide();
          });
          var unexpectedErrorMessage = "An error occurred while processing your request.";
          var username = $('#dfs-user-form .form-item-name input', context);
          var username_error = $('#dfs-user-form .form-item-name .dfs-error', context);
          var username_error_text = $('#dfs-user-form .form-item-name .dfs-error span', context);
          var password = $('#dfs-user-form  .form-item-pass input', context);
          var password_error = $('#dfs-user-form .form-item-pass .dfs-error', context);
          var password_error_text = $('#dfs-user-form .form-item-pass .dfs-error span', context);

          function validateUsername(name) {
            var regex = new RegExp(tenant_configure[community_id]['username_regex']);
            return regex.test(name);
          }


          /*
            for login api integration
          */
          $(" #dfs-user-form .form-item-name input").focus();
            $(".sign-in-service-call").click(function(event) {
              var prevent = 1;
              $('.service-error-message.form-item').hide();
              var uname = username.val().trim();
              var pass = password.val().trim();
              attachValidations();
              username.keyup();
              password.keyup();
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
              var url = Drupal.settings.tenant.login_api;
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
                  window.location.href = '/'+getParameterByName('destination');
                } else {
                  $(".service-error-message").show().html("<b>*</b> " + static_error_msg);
                }
              })
              .fail(function(){
                $(".service-error-message").show().html("<b>*</b> " + unexpectedErrorMessage );
              })
            });

        function getParameterByName(name) {
          name = name.replace(/[\[]/, "\\[").replace(/[\]]/, "\\]");
          var regex = new RegExp("[\\?&]" + name + "=([^&#]*)"),
          results = regex.exec(location.search);
          return results === null ? "" : decodeURIComponent(results[1].replace(/\+/g, " "));
        }

        function attachBehaviours() {
          $(document).keydown(function(event) {
            if (event.keyCode == 13) {
              $('.form-submit').click();
              event.preventDefault();
              event.stopPropagation();
            }

           });
        }
        function attachCloseTrigger() {
          $('.close-wrapper.close').click(function(){
             window.location.reload(true);
          });
        }
        function attachValidations() {
          var UserName = $('#dfs-user-form .form-item-name input', context);
          var Pass = $('#dfs-user-form .form-item-pass input', context);
          attachField(UserName);
          attachField(Pass);
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
      });
   }
  };
})(jQuery);
