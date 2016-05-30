(function($){
  Drupal.behaviors.emailDFSConfirm = {
    attach:function(context, settings) {
          var email = $('.form-item-email-confirm-email1 input', context);
          var email_error = $('.form-item-email-confirm-email1 .dfs-error', context)
          var email_error_text = $('.form-item-email-confirm-email1 .dfs-error span', context);
          var email_confirm = $('.form-item-email-confirm-email2 input', context);
          var email_confirm_error = $('.form-item-email-confirm-email2 .dfs-error', context);
          var email_confirm_error_text = $('.form-item-email-confirm-email2 .dfs-error span', context);
          $(".register-user-service-call", context).click(function(event) {

            email.bind('keyup change',function() {
              var email_reg = /^[\w\.-]*[a-zA-Z0-9_]@[\w\.-]*[a-zA-Z0-9]\.[a-zA-Z][a-zA-Z\.]*[a-zA-Z]$/;
              var email_val = $(this).val().trim();
              email_confirm.keyup();
              $(this).removeClass('valid');
              if(email_val.length && email_val.match(email_reg)) {
                email_error.hide();
                $(this).addClass('valid');
                $('.service-error-message.form-item').hide();
                email.removeClass('invalid');
                return true;
              }
              else if (email_val.length) {
                email_error.show();
                $(this).removeClass('valid');
                email_error_text.text(" Please enter Valid Email Address.");
                email.addClass('invalid');
               }
               else {
                 email_error.show();
                 email_error_text.text("Please enter Email Address.");
                 $(this).removeClass('valid');
                 email.addClass('invalid');
               }
            });

                /**
                       *  Password Confirm validation
                       */
            email_confirm.bind('keyup change ',function() {
              var email_val = email.val().trim();
              var email_confirm_val = $(this).val().trim();
              $(this).removeClass('valid');
              if(!email_confirm_val.length) {
                 email_confirm_error.show();
                 email_confirm_error_text.text("Please enter Email Address.");
                 email_confirm.addClass('invalid');
              }
              else if (email_confirm_val.length && email_val !== email_confirm_val){
                email_confirm_error.show();
                email_confirm_error_text.text("The Email Address must be same as Default email.");
                email_confirm.addClass('invalid');
              }
              else {
                $(this).addClass('valid');
                email_confirm_error.hide();
                $('.service-error-message.form-item').hide();
                email_confirm_error_text.text("");
                email_confirm.removeClass('invalid');
                return true;
              }
            });
            email.keyup();
          });
    }
  };
})(jQuery);
