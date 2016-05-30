(function ($) {
  Drupal.behaviors.initResoucesTheme = {
    attach: function (context, settings) {
      var expandAuto = function() {
          var category = [];
          var indexToReturn = [] ;
          var $category = $('.resources-category .field__item');
          var $headerCategory = $('.category-title');
          //view-header
          var currHeaderActive = function($headerCategory) {
            $headerCategory.each(function(index) {
              if ($(this).find('.active').length) {
                indexToReturn.push(index);
                $(this).addClass('active-header');
              }
            });
            return indexToReturn;
          }
          var curreNodeCategory = function ($category) {
            $category.each(function() {
              category.push($(this).find('a').text());
            });
          }
          var categoryAccordion = function(category) {

            $accordion = $('.ui-accordion');
            $accordionHeader = $accordion.children('.ui-accordion-header');
            $accordionHeaderChilds = new Array($accordionHeader.length);
            for(var i=0; i < $accordionHeaderChilds.length; i++) {
                 var currentValue = [];

                 $($accordionHeader[i]).next().find('.views-field-name a').each(function(index){
                  if (!currentValue[i]) {
                    currentValue[i] = [];
                  }
                    currentValue[i][index] = ($(this).text());
                  if ($.inArray(currentValue[i][index], category) != -1) {
                    $(this).addClass('active');
                    indexToReturn.push(i);
                    console.log(indexToReturn);
                  }
                });

                 $($accordionHeader[i]).prev().each(function(index){
                  if (!currentValue[i]) {
                    currentValue[i] = [];
                  }
                    currentValue[i][index] = ($(this).find('a').text());
                  if ($.inArray(currentValue[i][index], category) != -1) {
                    $(this).addClass('active-header');
                    indexToReturn.push(i);
                    console.log(indexToReturn);
                  }
                });


            }
            return indexToReturn;
          }
          var accordionTrigger = function(index) {
            if( typeof index !== undefined && index.length) {
              $(".ui-accordion").accordion({
                  active: index[0]
              });
            }
          };
          if ($category.length) {
            curreNodeCategory($category);
            index = categoryAccordion(category);
            console.log(index);
            accordionTrigger(index);
          }
          if ($headerCategory.length) {
            index = currHeaderActive($headerCategory);
            console.log(index);
            accordionTrigger(index);
          }

      };
      expandAuto();

      //For Webform validation message
      $('.webform-client-form').attr('novalidate', 'novalidate');
      // resources tabing width issue fix
      var $tab = $(".ckeditor-tabber > dt");
      if ( $tab.length ) {
        $tab.css({
              'width': 'auto',
            });
        var $tabWidth = 0;
        $tab.each(function(index){
          if(index){
            $(this).css({'left' : $tabWidth});
          }
          $tabWidth += $(this).width();
        });
      }
    }


  };
})(jQuery);
