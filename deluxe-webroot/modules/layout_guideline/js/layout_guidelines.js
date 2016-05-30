(function ($) {
  Drupal.behaviors.initLG = {
    attach: function (context, settings) {
      $('.page-diecut-shape-templates', '.full-cell-wrapper').each(function() {
         $(this).find('td', '.views-field').mouseover(function(){
         $(this).find('img.nonrollover').addClass('hideme');
         $(this).find('img.rollover').removeClass('hideme');
         $(this).find('img.rollover').addClass('showme');
         $(this).find('.views-field-title a').css('color', '#00aadd');
          }),
         $(this).find('td', '.views-field').mouseout(function(){
         $(this).find('.views-field-title a').css('color', '#333');
         $(this).find('img.rollover').removeClass('showme');
         $(this).find('img.rollover').addClass('hideme');
         $(this).find('img.nonrollover').removeClass('hideme');
        });
      });
    $('.views-widget-filter').append(jQuery('.field_mailing'));
    }
  };
})(jQuery);

