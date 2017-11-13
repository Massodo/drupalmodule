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
          window.css('display', 'block');//.animate({opacity: 1, top: '50%'}, 200);
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

      var windowX;
      var windowY;
      var drag = false;

      $('#title').mousedown(function (e) {
        var offset = $('#message').offset();
        windowX = e.clientX - (offset.left + 110);
        windowY = e.clientY - (offset.top + 140);
        drag = true;
      })

      $('#message').mouseup(function () {
        drag = false;
      })

      $('#message').mousemove(function (e) {
        if(drag){
          var top = e.clientY - windowY;
          var left = e.clientX - windowX;
          var borderTop = 0 + drupalSettings.message.height / 2;
          var borderBottom = $(window).height() - drupalSettings.message.height / 2;
          var borderLeft = 0 + drupalSettings.message.width / 2;
          var borderRight = $(window).width() - drupalSettings.message.width / 2;

          if (top >= borderTop && top <= borderBottom) {
            $('#message', context).css('top', top);
          }

          if (left >= borderLeft && left <= borderRight) {
            $('#message', context).css('left', left);
          }
        }
      })
    },
  }
})(jQuery, Drupal, drupalSettings)