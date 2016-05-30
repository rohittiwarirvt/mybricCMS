
var CMS = CMS || {};

(function ($) {

    // Global Declaration of CMS utils

    CMS.PSPutils = {

      tenant_configure : {
        '1' : {
          username_regex : "^[\\w\\.-]*[a-zA-Z0-9_]@[\\w\\.-]*[a-zA-Z0-9]\\.[a-zA-Z][a-zA-Z\\.]*[a-zA-Z]$",
          username_message :"Please enter your email." ,
          username_invalid_message : "Please enter a valid email." ,
          password_message :"Please enter your password.",
          password_invalid_message : "Please enter a password with minimum 7 characters to maximum 30 characters with at least one capital letter." ,
          password_confirm_invalid_message : "The password and confirming password don’t match." ,
          password_regex : "^(?=.*[A-Z])(?=.*[^a-zA-Z]).{7,30}$",
          api_static_error_msg: "Please enter the correct email and password and try again.",
          unexpectedApiFailErrorMessage :"An error occurred while processing your request (API error)",
              }
      },

      reloadPageOrRedirect : function () {
        var redirectUrl = $(".redirecturl-active input[name=redirecturl]").attr("value");
        if (redirectUrl && typeof redirectUrl === typeof "string") {
          Drupal.CTools.Modal.dismiss();
          $("#isloading-overlay-d").show();
          window.location.href = redirectUrl;
        }
        else {
          Drupal.CTools.Modal.dismiss();
          $("#isloading-overlay-d").show();
          window.location.reload(true);
        }
      },

       validateUsername :  function (name) {
            var regex = new RegExp(CMS.PSPutils.tenant_configure[Drupal.settings.tenant.community_id]['username_regex']);
            return regex.test(name);
      },
       validatePassword :  function (name) {
            var regex = new RegExp(CMS.PSPutils.tenant_configure[Drupal.settings.tenant.community_id]['password_regex']);
            return regex.test(name);
      },
      fieldValidationAttachField :  function(field) {
          var error = field.parent().find('.dfs-error');
          var error_text = field.parent().find('.error');
          var cond;
          field.bind('keyup change',function() {
            var field_val = field.val().trim();
            if(field.parent().hasClass('form-item-name')) {
              var valid_phone = CMS.PSPutils.validateUsername(field_val);
              cond = field_val.length && valid_phone;
              if(field_val.length && !valid_phone) {
                  error_text.text(CMS.PSPutils.tenant_configure[Drupal.settings.tenant.community_id]['username_invalid_message']);
              }
              else{
                  error_text.text(CMS.PSPutils.tenant_configure[Drupal.settings.tenant.community_id]['username_message']);
              }
            }
            else if(field.parent().hasClass('form-item-pass1')){
              var valid_pass = CMS.PSPutils.validatePassword(field_val);
              cond = field_val.length && valid_pass;
              if(field_val.length && !valid_pass) {
                  error_text.text(CMS.PSPutils.tenant_configure[Drupal.settings.tenant.community_id]['password_invalid_message']);
              }
              else{
                  error_text.text(CMS.PSPutils.tenant_configure[Drupal.settings.tenant.community_id]['password_message']);
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
        },

        getQueryParameterByName : function (name) {
          name = name.replace(/[\[]/, "\\[").replace(/[\]]/, "\\]");
          var regex = new RegExp("[\\?&]" + name + "=([^&#]*)"),
          results = regex.exec(location.search);
          return results === null ? "" : decodeURIComponent(results[1].replace(/\+/g, " "));
        },
         attachPressEnterSubmitBehaviours : function () {
          $(document).keydown(function(event) {
            if (event.keyCode == 13) {
              $('.form-submit').click();
              event.preventDefault();
              event.stopPropagation();
            }

           });
        },
        invalidFieldCheck : function($wrapper) {
          var prevent = 1;
          $wrapper.find(".invalid" ).each(function(index) {
            if (index==0) {
             $(this).focus();
             prevent = 0;
             }
          });
          return prevent;
        },

    }

  Drupal.behaviors.initPsPGlobalthemejs = {
    attach: function(context, settings) {
      if(!$(".isloading-wrapper-drupal").length) {
      $('body.html', context).prepend('<div id="isloading-overlay-d" class="isloading-wrapper-drupal"><div class="isloading-show-d  isloading-overlay-d"></div></div>');
      }

      if(typeof String.prototype.trim !== 'function') {
        String.prototype.trim = function() {
          return this.replace(/^\s+|\s+$/g, '');
        }
      }
      subscription_submit();

      function subscription_submit() {
        $('.subscribe-form').keydown(function (event) {
          if(event.keyCode == 13) {
            event.preventDefault();
            $(event.currentTarget).submit();
          }
        });

        $('.subscribe-form').submit(function (event) {
          event.preventDefault();
          SignUp();
        });
      }
      function SignUp() {
        var $email = $('#SignUpEmail');
        var email_val = $email.val().trim()
        var prevent = 1;
        CMS.PSPutils.fieldValidationAttachField($email);
        $email.keyup();

        prevent = CMS.PSPutils.invalidFieldCheck($('.subscribe-section'));
        prevent  = Boolean(prevent);
        if (prevent) {
          subscription_api_call(email_val);
        }

      }

      function subscription_api_call(email) {
        $subscription_loader = $('.throbber-signup');
        $subscription_loader.show();
                // ajax call for subscription
           $.ajax({
            'url': settings.tenant.subscription,
            'type': 'POST',
            'dataType': 'json',
            'data': {
              "email" : email,
            },
            'success': function(data) {
               $subscription_loader.hide();
              if(data.data.success) {
                window.sessionStorage.signUpEmail = email;
                window.location.href= "/signupconfirmation";
              }
              else {
                alert(data.error.message);
              }
            },
            'error':function(data) {
               $subscription_loader.hide();
              alert(data.error.message);
             }
          });
      }


    }
  };
})(jQuery);


Drupal.theme.prototype.PSPModalFormsPopup = function () {
  var html = '';

  html += '<div id="ctools-modal" class="popups-box">';
  html += '  <div class="ctools-modal-content modal-forms-modal-content">';
  html += '    <div class="popups-container ' + Drupal.CTools.Modal.currentSettings.modalOptions.modaClass + '">';
  html += '      <div class="modal-header popups-title">';
  html += '        <span id="modal-title" class="modal-title"></span>';
  html += '        <span class="popups-close close">' + Drupal.CTools.Modal.currentSettings.closeText + '</span>';
  html += '        <div class="clear-block"></div>';
  html += '      </div>';
  html += '      <div class="modal-scroll"><div id="modal-content" class="modal-content popups-body"></div></div>';
  html += '    </div>';
  html += '  </div>';
  html += '</div>';

  return html;
}
