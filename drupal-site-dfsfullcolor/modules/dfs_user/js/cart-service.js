(function ($) {
  Drupal.behaviors.initCart = {
    attach: function (context, settings) {
    $('body', context).once('cart-count-ajax',function (){
      $(context).load(function() {
          updateCartCount(context, settings);
        });
      });
        updateCartCount(context, settings);
        /**
        * update cart count function
        */
      function updateCartCount(context, settings) {
        $.ajax({
          type: "GET",
          url: Drupal.settings.tenant.cart_count_api,
        })
        .done(function (webApiResponse) {
          if (webApiResponse.data){
            $('#CartItemsCount').text(webApiResponse.data.cartItemsCount);
         }
       });
     }
    }
  };
})(jQuery);
