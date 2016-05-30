(function($){
  Drupal.behaviors.initDFSRegistration = {
    attach:function(context, settings) {
          var errorCodes  = { 20: 'Duplicate Company Phone number.'}
          var error_message_override;
          $(document).ajaxComplete(function() {
            $('#content').once('dfs-registration',function(){
              attachBehaviours();
              attachRegistration();

            });

          });

          function attachBehaviours() {
            $(document).keydown(function(event) {
              if (event.keyCode == 13) {
                $('.form-submit').click();
                event.preventDefault();
                event.stopPropagation();
              }
             });
           }

           function getParameterByName(name) {
             name = name.replace(/[\[]/, "\\[").replace(/[\]]/, "\\]");
             var regex = new RegExp("[\\?&]" + name + "=([^&#]*)"),
             results = regex.exec(location.search);
             return results === null ? "" : decodeURIComponent(results[1].replace(/\+/g, " "));
           }

          function attachRegistration() {
              var unexpectedErrorMessage = "An error occurred while processing your request.";
              var url = Drupal.settings.tenant.registration_api;
              $(".register-user-service-call", context).click(function(event) {
                $('.service-error-message.form-item').hide();
                var UserName = $('#dfs-register-form  .form-item-phone-phone1 input', context);
                var ConfirmUserName = $('#dfs-register-form  .form-item-phone-phone2 input', context);
                var Passwords = $('#dfs-register-form .form-item-pass-confirm-pass1 input', context);
                var ConfirmPassword = $('#dfs-register-form  .form-item-pass-confirm-pass2 input', context);
                var CompanyName = $('#dfs-register-form .form-item-company-name input', context);
                var FirstName = $('#dfs-register-form .form-item-first-name input', context);
                var LastName = $('#dfs-register-form .form-item-last-name input', context);
                var Email = $('#dfs-register-form .form-item-email-confirm-email1 input', context);
                var ConfirmEmail = $('#dfs-register-form .form-item-email-confirm-email2 input', context);
                var Address1 = $('#dfs-register-form .form-item-address1 input', context);
                var Address2 = $('#dfs-register-form .form-item-address2 input', context);
                var City = $('#dfs-register-form .form-item-city input', context);
                var State = $('#dfs-register-form .form-item-state input', context);
                var ZipCode = $('#dfs-register-form .form-item-zipcode input', context);
                var DealerType = $('#dfs-register-form .form-item-dealer-type input', context);
                attachField(CompanyName);
                attachField(FirstName);
                attachField(LastName);
                attachField(Address1);
                attachField(City);
                attachField(State);
                attachField(ZipCode);
                attachField(DealerType);

                var fields = [DealerType, ZipCode, State, City, Address1, LastName, FirstName, CompanyName];

                var i = 0 ;
                var prevent = 1;
                while( i < fields.length ) {
                  errorAttach(fields[i]);
                  i++;
                }


                $(".invalid" ).each(function(index) {
                  if(index==0) {
                    $(this).focus();
                    prevent = 0;
                  }
                });

                if(!prevent) {
                  return false;
                }


                $.ajax({
                'url': url,
                'type': 'POST',
                'dataType': 'json',
                'data': {
                  "UserName": UserName.val().trim(),
                  "ConfirmUserName": ConfirmUserName.val().trim(),
                  "Password": Passwords.val().trim(),
                  "ConfirmPassword": ConfirmPassword.val().trim(),
                  "CompanyName": CompanyName.val().trim(),
                  "FirstName": FirstName.val().trim(),
                  "LastName": LastName.val().trim(),
                  "Email": Email.val().trim(),
                  "ConfirmEmail": ConfirmEmail.val().trim(),
                  "Address1": Address1.val().trim(),
                  "Address2": Address2.val().trim(),
                  "City": City.val().trim(),
                  "State": State.val().trim(),
                  "ZipCode": ZipCode.val().trim(),
                  "DealerType": DealerType.val().trim(),
                  "ConfirmEmail": ConfirmEmail.val().trim(),
                },
                'xhrFields': {
                      withCredentials: true
                  }
              })
              .done(function (webApiResponse) {
                  if (webApiResponse.data) {
                      window.location.href = '/'+getParameterByName('destination');
                  } else {
                    error_message_override = errorCodes[webApiResponse.error.code];
                    if(typeof(error_message_override) === 'undefined') {
                      error_message_override = webApiResponse.error.message;
                    }
                    $(".service-error-message").show().html("<b>*</b> " + error_message_override);
                  }
              })
              .fail(function(webApiResponse){
                  $(".service-error-message").show().html("<b>*</b> " + unexpectedErrorMessage );
              });
            });
          }


          function attachField(field) {
            field.keyup(function() {
              errorAttach(field);
            });
          }

          function errorAttach(field) {
            var field_val = field.val().trim();
            var error = field.parent().find('.dfs-error');
            if (field_val.length) {
                error.hide();
                $('.service-error-message.form-item').hide();
                field.removeClass('invalid');
              }
              else {
                error.show();
                field.addClass('invalid');
              }
          }
    }
  };
})(jQuery);
