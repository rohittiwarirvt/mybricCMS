(function($){
  Drupal.behaviors.phoneDFSConfirm = {
    attach: function(context, setting) {
          var phone = $('.form-item-phone-phone1 input', context);
          var phone_error = $('.form-item-phone-phone1 .dfs-error', context)
          var phone_error_text = $('.form-item-phone-phone1 .dfs-error span', context);
          var phone_confirm = $('.form-item-phone-phone2 input', context);
          var phone_confirm_error = $('.form-item-phone-phone2 .dfs-error', context);
          var phone_confirm_error_text = $('.form-item-phone-phone2 .dfs-error span', context);
          $(".register-user-service-call", context).click(function(event) {

              phone.bind('keyup change',function() {
              var phone_reg = /^[0-9]+$/;
              var phone_val = $(this).val().trim();
              phone_confirm.keyup();
              $(this).removeClass('valid');
              if(phone_val.length && phone_val.match(phone_reg)) {
                phone_error.hide();
                $('.service-error-message.form-item').hide();
                $(this).addClass('valid');
                phone.removeClass('invalid');
                return true;
              }
              else if (phone_val.length) {
                phone_error.show();
                $(this).removeClass('valid');
                phone_error_text.text(" Please enter Valid Company Phone number.");
                phone.addClass('invalid');
               }
               else {
                 phone_error.show();
                 phone_error_text.text("Please enter Company Phone number.");
                 $(this).removeClass('valid');
                 phone.addClass('invalid');
               }
            });

                      /**
                       *  Password Confirm validation
                       */
            phone_confirm.bind('keyup change ',function() {
              var phone_val = phone.val().trim();
              var phone_confirm_val = $(this).val().trim();
              $(this).removeClass('valid');
              if(!phone_confirm_val.length) {
                 phone_confirm_error.show();
                 phone_confirm_error_text.text("Please re-enter Company Phone number.");
                 phone_confirm.addClass('invalid');
              }
              else if (phone_confirm_val.length && phone_val !== phone_confirm_val){
                phone_confirm_error.show();
                phone_confirm_error_text.text(" The Company phone number must be same as Default phone number.");
                phone_confirm.addClass('invalid');
              }
              else {
                $(this).addClass('valid');
                phone_confirm_error.hide();
                phone_confirm_error_text.text("");
                $('.service-error-message.form-item').hide();
                phone_confirm.removeClass('invalid');
                return true;
              }
            });
            phone.keyup();
          });
     }
  };
})(jQuery);
