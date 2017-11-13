(function ($) {
  Drupal.behaviors.delivery_messages = {
    attach: function (context, settings) {
      $('input:checkbox', context).click(function () {
        $('input:checkbox', context).attr('checked', false);
        $(this, context).attr('checked', true);
      });
    },
  };
}(jQuery));
