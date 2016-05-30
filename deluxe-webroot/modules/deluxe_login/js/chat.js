(function ($) {
  Drupal.behaviors.initChat = {
    attach: function (context, settings) {
          function showChatPopup(e) {
                  e.preventDefault();
                  window.open("https://server.iad.liveperson.net/hc/90150254/?cmd=file&file=visitorWantsToChat&site=90150254&byhref=1&imageUrl=https://server.iad.liveperson.net/hcp/Gallery/ChatButton-Gallery/English/General/1a/"
                      + "&VISITORVAR!Current%20Page=" + window.location.href
                      + "&VISITORVAR!Customer%20Name="
                      + "&VISITORVAR!Customer%20Email=",
                      "chat90150254",
                      "width=475,height=400,resizable=yes");
              }

            $('.chat').on('click', function(e){
                showChatPopup(e);
            });
    }
  };
})(jQuery);
