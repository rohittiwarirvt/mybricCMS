(function ($) {
  Drupal.behaviors.initLGTracking = {
    attach: function (context, settings) {
      var page_type;
       _paq.push(['addDownloadExtensions', "ai|indd|psd"]);
      if(typeof window.universal_variable !== 'undefined' && typeof window.universal_variable.page !== 'undefined' && typeof window.universal_variable.page.type !== 'undefined') {
        page_type = window.universal_variable.page.type;
        $('.search-result-wrapper .full-cell-wrapper').each(function(){
          $(this).find('a').each(function(){
            var downloadString = $(this).attr('href');
            var split_string = downloadString.split("/");
            var fileName = split_string[split_string.length-1];
              $(this).on('click', function(event){
                //event.preventDefault();
                _paq.push(['trackEvent',page_type,'Download',fileName]);
                window.universal_variable.events.push({'category': 'layout-guideline','action': 'download', 'fileName':fileName});
                s.events="event22";
                s.t();
              });
          });
        });
       }
    }
  };
})(jQuery);

