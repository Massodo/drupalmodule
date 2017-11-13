(function ($) {
  Drupal.behaviors.popup_window = {
    attach: function (context, settings) {
      var posX;
      var posY;

      $('.popup-bar', context).bind('mousedown', mouseDown, false);
      $(window, context).bind('mouseup', mouseUp, false);

      $(document, context).ready(function () {
        if (settings.popup_window.message) {
          $('#popup-overlay', context).show();
          $('#popup', context).show();
          $('#popup', context).css('min-height', settings.popup_window.height + '.px');
          $('#popup', context).css('width', settings.popup_window.width + '.px');
          $('#popup', context).css('top', ($(window).height() / 2 - $('#popup').outerHeight() / 2));
          $('#popup', context).css('left', $(window).width() / 2 - $('#popup').outerWidth() / 2);
          $('body', context).css('overflow', 'hidden');
        }
      });

      $('#popup-overlay', context).click(function () {
        close();
      });

      $('.btn-close', context).click(function () {
        close();
      });

      function close() {
        $('#popup-overlay', context).hide();
        $('#popup', context).hide();
        $('body', context).css('overflow', 'auto');
      }

      function mouseDown(e) {
        var offset = $('#popup', context).offset();
        posX = e.clientX - offset.left;
        posY = e.clientY - offset.top;
        $(window, context).bind('mousemove', popupMove, true);

      };

      function mouseUp() {
        $(window, context).unbind('mousemove', popupMove, true);
      };

      function popupMove(e) {
        var top = e.clientY - posY;
        var left = e.clientX - posX;
        var borderTop = 0;
        var borderBottom = $(window).height() - $('#popup').outerHeight();
        var borderLeft = 0;
        var borderRight = $(window).width() - $('#popup').outerWidth();
        if (top >= borderTop && top <= borderBottom) {
          $('#popup', context).css('top', top);
        }

        if (left >= borderLeft && left <= borderRight) {
          $('#popup', context).css('left', left);
        }
      }
    },
  };
}(jQuery));
