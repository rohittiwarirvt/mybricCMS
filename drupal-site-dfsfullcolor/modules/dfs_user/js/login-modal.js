
var CMS = CMS || {};

(function ($) {
  Drupal.behaviors.initloginModal = {
    attach: function (context, settings) {
      var login_url = "/user/nojs/psprint/login";
      $("#login-dropdown .login-action", context).attr("href", login_url);
      $('#login-dropdown a',context).once('init-modal-forms-login',function(){
        if ($(this).attr('href') != login_url){
          var str = $(this).attr('href');
          destination = str.replace(/https?:[\/]{2}\S*?(\/\S*)/,"$1");
          $(this).attr('href', login_url);
          $(this).append($("<input type=hidden name=redirecturl value="+destination+">"));
          $('redirecturl-active').removeClass("redirecturl-active");
          $(this).click(function(){
              $(this).addClass("redirecturl-active");
          });
        }
        else if ($(this).attr('href') != login_url) {
          $(this).attr('href', login_url);
        }
      }).addClass('ctools-use-modal ctools-modal-modal-popup-login');

    $('#modalContent').bind("ajaxSend", function(){
              $("#isloading-overlay-d").show();
            }).bind("ajaxComplete", function(){
              $("#isloading-overlay-d").hide();
    });
                }
  };

})(jQuery);
