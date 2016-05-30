
  function rev_showStarRatingList (ele) {
    jQuery(ele).parents("div.psp-rating-review-wrap").find("div.star_rating_list").show();
  }
  function rev_Readmore(ele) {
    jQuery(ele).parents("div.psp-review-item").find("div.div_read_more").show();
    jQuery(ele).parents("div.psp-review-item").find("div.div_read_less").hide();
    jQuery(ele).parents("div.psp-review-item").find("p.text_readmore").show();
    jQuery(ele).parents("div.psp-review-item").find("p.text_readless").hide();
 }
 function rev_Readless(ele) {
    jQuery(ele).parents("div.psp-review-item").find("div.div_read_more").hide();
    jQuery(ele).parents("div.psp-review-item").find("div.div_read_less").show();
    jQuery(ele).parents("div.psp-review-item").find("p.text_readmore").hide();
    jQuery(ele).parents("div.psp-review-item").find("p.text_readless").show();
 }

  function rev_ReadmoreById(id) {
    jQuery(".div_read_more_"+id).show();
    jQuery(".div_read_less_"+id).hide();
    jQuery("p.text_readmore_"+id).show();
    jQuery("p.text_readless_"+id).hide();
    if(typeof jQuery(".div_read_more_"+id).offset()!="undefined"){
        jQuery('html,body').animate({
            scrollTop: jQuery(".div_read_more_"+id).offset().top-40
        }, 600);
     }

 }
 jQuery(document).mouseup(function (e){
    var container = jQuery("div.star_rating_list");
    if (!container.is(e.target)
        && container.has(e.target).length === 0){
        container.hide();
    }
});

function pointToReview(id) {
  //  if(typeof jQuery(".div_read_more_"+id).offset()!="undefined"){
        jQuery('html,body').animate({
            scrollTop: jQuery(".div_read_more_"+id).offset().top-50
        }, 600);
     //}
}

function getURLParameter(name) {
  return decodeURIComponent((new RegExp('[?|&]' + name + '=' + '([^&;]+?)(&|#|;|jQuery)').exec(location.search)||[,""])[1].replace(/\+/g, '%20'))||null
}




(function ($) {
/**
 * Provide the summary information for the block settings vertical tabs.
 */
Drupal.behaviors.infiniteScroll = {
  attach: function (context,settings) {

    var params =  {"bucket_name":settings.bucket_name,"format":"html","widget":settings.widget,"offset":10};
    $("#review_scroller_div").rScroll({
    url:"https://design.psprint.com/loadMoreReviews",
    params  :params,
    loaderDom : '<div class="dt_review_loader"></div>',
    appendDom : function(data){
        $('#review_scroller_div').append(data);
    }
     });

   // Set Review widget on top on product review page 
    var promo_plugin = jQuery('.promotion-plugin');
     if(promo_plugin.length == 0) 
        jQuery('.content-reviews-page .review-widget-banner-product .pane-content').css("bottom", "6em");

    $('body').on('click','.backtotop',function(){
      $("html, body").animate({ scrollTop: "0" });
    });
  }
};
  var url = window.location.href;
  var getQueryString = url.split('=');
  if(getQueryString[1]){
    setTimeout(function(){
        pointToReview(getQueryString[1]);
      },1000);
  }
})(jQuery);
