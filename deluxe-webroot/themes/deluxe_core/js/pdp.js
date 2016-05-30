(function ($) {
  Drupal.behaviors.pdpBehaviour = {
    attach: function (context, settings) {
		$('.field-collection-tabs').tabs({ active: 3 });
	}
}
})(jQuery);
