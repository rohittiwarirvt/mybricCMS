(function ($) {
  Drupal.behaviors.initPixelGATracking = {
    attach: function (context, settings) {
      var myAccountHeader = function() {
        var $headerBlock = $('.block-header-user-menu')  ;
        // logout fire
        var $logoutLink = $headerBlock.find('.logout-action');
        $logoutLink.on('click', function() {
          dataLayer.push({'link': {'title': 'log-out', 'category': 'account', 'location': 'account-menu'}, 'event': 'link'});
        });


        //login fire
        var $myAccount = $headerBlock.find('.my-account > a'), $loginLink = $headerBlock.find('.login-action');
        $myAccount.on('click', function(){
          gaLogin();
        });
        $loginLink.on('click', function(){
          gaLogin();
        });
      };


      var topNavMenus = function() {
        var $topNav = $('.block-menu-psprint-header');
        $topNav.find('a').each(function() {
          $(this).on('click', function(event){
            topNavGA(event, this);
          }) ;
        });
      };

      var gaLogin = function() {
        dataLayer.push({'link': {'title': 'my-account', 'category': 'account', 'location': 'account-menu'}, 'event': 'link'});
      };

      var topNavGA = function(event, _this) {
        var linkText =$(_this).text(),
        linkType = $(_this).find('img').length ? 'img':'text',
         linkDestination = $(_this).attr('href');
        dataLayer.push({'link': {'title': linkText, 'link type': linkType, 'category': 'top nav', 'location': 'nav-menu', 'destination': linkDestination, 'action': 'click'}, 'event': 'link'});
      };
      $('body', context).once("ga-tracking", function(){
        myAccountHeader();
        topNavMenus();
      });
    }
  };
})(jQuery);

