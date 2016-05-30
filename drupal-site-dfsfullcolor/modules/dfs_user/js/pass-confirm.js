(function($) {
  /**
   * Attache handlers to evaluate the strength of any password fields and to check
   * that it confirmation is correct
   */

  Drupal.behaviors.passDFSConfirm = {
    attach: function (context, settings) {
          var pass = $('.form-item-pass-confirm-pass1 input', context);
          var pass_error = $('.form-item-pass-confirm-pass1 .dfs-error', context)
          var pass_error_text = $('.form-item-pass-confirm-pass1 .dfs-error span', context);
          var pass_confirm = $('.form-item-pass-confirm-pass2 input', context);
          var pass_confirm_error = $('.form-item-pass-confirm-pass2 .dfs-error', context);
          var pass_confirm_error_text = $('.form-item-pass-confirm-pass2 .dfs-error span', context);
          $(".register-user-service-call", context).click(function(event) {
            pass.bind('keyup change',function() {
              var pass_val = $(this).val().trim();
              $(this).removeClass('valid');
              if (!pass_val.length) {
                pass_error.show();
                $(this).removeClass('valid');
                pass.addClass('invalid');
               }
               else {
                pass_error.hide();
                $('.service-error-message.form-item').hide();
                 pass.removeClass('invalid');
               }
            });
            pass.keyup();                    /**
                     *  Password Confirm validation
                     */
            var pass_val = pass.val().trim();
            var pass_confirm_val = pass_confirm.val().trim();
            if(!pass_confirm_val.length) {
               pass_confirm_error.show();
               pass_confirm_error_text.text("Please Enter Password.");
               pass_confirm.addClass('invalid');
            }
            else if (pass_confirm_val.length && pass_val !== pass_confirm_val){
              pass_confirm_error.show();
              pass_confirm_error_text.text("The password and confirming password don’t match.");
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
  };
})(jQuery);
