(function ($, Drupal, drupalSettings) {

  'use strict'

  Drupal.behaviors.message = {

    attach: function (context, settings) {

      $('#message').ready(function () {
        var window = $('#message');
        var windowSettings = drupalSettings.message;
        if(windowSettings){
          window.css('width', windowSettings.width);
          window.css('height', windowSettings.height);
          window.css('background', windowSettings.background);
          window.css('border', windowSettings.border + 'px solid');
          window.css('border-color', windowSettings.borderColor);
          window.css('font-size', windowSettings.fontSize + 'px');
          window.css('color', windowSettings.color);
        }
        $('#overlay').fadeIn(400, function () {
          window.css('display', 'block').animate({opacity: 1, top: '50%'}, 200);
        });
      });

      $('.close').click(function () {
        $('#message').animate({opacity: 0, top: '45%'}, 200, function () {
          $('#message').css('display', 'none');
          $('#overlay').fadeOut(400);
        });
      });
    }
  }

  Drupal.behaviors.drag = {
    attach: function (context, settings) {
      var elem = $('.modal-message');
      var title = $('.modal-message .modal-title');

      var drag = {
        x: 0,
        y: 0,
        isDragging: false
      };

      var delta = {
        x: 0,
        y: 0
      };

      title.on('mousedown', function (e) {
        if (!drag.isDragging) {
          drag.isDragging = true;
          drag.x = e.pageX;
          drag.y = e.pageY;
        }
      });

      $(document).mousemove(function(e) {
        if (drag.isDragging) {
          var borderTop = 0;
          var borderBottom = screen.height - 450;
          var borderLeft = 0;
          var borderRight = screen.width - 300;

          delta.x = e.pageX - drag.x;
          delta.y = e.pageY - drag.y;

          var currentOffset = $(elem).offset();
          if((currentOffset.left + delta.x >= borderLeft) && (currentOffset.left + delta.x<= borderRight)){
            $(elem).offset({
              left: (currentOffset.left + delta.x)
            });
          }
          if((currentOffset.top + delta.y >= borderTop) && (currentOffset.top + delta.y <= borderBottom)){
            $(elem).offset({
              top: (currentOffset.top + delta.y)
            });
          }

          drag.x = e.pageX;
          drag.y = e.pageY;
        }
      });

      $(document).mouseup(function() {
        drag.isDragging = false;
      });
    }
  }
})(jQuery, Drupal, drupalSettings)