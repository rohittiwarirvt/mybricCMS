(function ($) {
  Drupal.behaviors.initGlobalJS = {
    attach: function (context, settings) {
      $('#page').prepend($('.site-notification-msg'));
      $('#sitewide-message-close').click(function(){
        $('.site-notification-msg').addClass('hideme');
        setHollidayCookie();
      });
      if(typeof(readCookie('_psp_ecommerce_hmu'))!== 'undefined') {
        $('.site-notification-msg').addClass('hideme');
      }
      else{
        $('.site-notification-msg').removeClass('hideme');
      }
      var cookies;
      function setHollidayCookie() {
        var hollidayCookieValue = "_psp_ecommerce_hmu=holiday;"
        document.cookie = hollidayCookieValue;
      }
      if(typeof String.prototype.trim !== 'function') {
        String.prototype.trim = function() {
          return this.replace(/^\s+|\s+$/g, '');
          };
      }
      function readCookie(name,c,C,i){
        if(cookies){ return cookies[name]; }
          c = document.cookie.split('; ');
          cookies = {};
          for(i=c.length-1; i>=0; i--){
            C = c[i].split('=');
            cookies[C[0]] = C[1];
          }
          return cookies[name];
      }
      // rollover
      $('.page-diecut-shape-templates').each(function() {
         $(this).find('td').mouseover(function(){
         $(this).find('img.nonrollover').addClass('hideme');
         $(this).find('img.rollover').removeClass('hideme');
         $(this).find('img.rollover').addClass('showme');
         $(this).find('.views-field-title a').css('color', '#00aadd');
          }),
         $(this).find('td').mouseout(function(){
         $(this).find('.views-field-title a').css('color', '#333');
         $(this).find('img.rollover').removeClass('showme');
         $(this).find('img.rollover').addClass('hideme');
         $(this).find('img.nonrollover').removeClass('hideme');
        });
      });
      $('.view-layout-guideline').each(function() {
         $(this).find('.view-content .views-row').mouseover(function(){
           $(this).find('img.nonrollover').addClass('hideme');
           $(this).find('img.rollover').removeClass('hideme');
           $(this).find('img.rollover').addClass('showme');
           $(this).find('.views-field-name a').css('color', '#00aadd');
            }),
          $(this).find('.view-content .views-row').mouseout(function(){
           $(this).find('.views-field-name a').css('color', '#333');
           $(this).find('img.rollover').removeClass('showme');
           $(this).find('img.rollover').addClass('hideme');
           $(this).find('img.nonrollover').removeClass('hideme');
        });
      });
  /* Filter page */
      $('.page-layout-templates').each(function() {
         $(this).find('.full-cell-wrapper').mouseover(function(){
           $(this).find('img.nonrollover').addClass('hideme');
           $(this).find('img.rollover').removeClass('hideme');
           $(this).find('img.rollover').addClass('showme');
           $(this).find('.views-field-title a').css('color', '#00aadd');
            }),
         $(this).find('.full-cell-wrapper').mouseout(function(){
           $(this).find('.views-field-title a').css('color', '#333');
           $(this).find('img.rollover').removeClass('showme');
           $(this).find('img.rollover').addClass('hideme');
           $(this).find('img.nonrollover').removeClass('hideme');
        });
      });
      $('.pane-seocopyblock .pane-content h1').each(function() {
         $(".node-type-product .pane-seocopyblock .pane-content" ).addClass('pane-h1-title');
      });
    }
  };
})(jQuery);

