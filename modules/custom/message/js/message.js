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

      var window = $('#message');

      window.onmousedown = function (e) {
        window.css('position', 'absolute');
        moveAt(e, window);
        alert(321);

        window.ondragstart = function () {
          return false;
        }

        window.onmousemove = function (e) {
          moveAt(e, $('#message'))
        }

        window.onmouseup = function () {
          window.onmousemove = null;
          window.mousedown = null
        }

        function moveAt(e) {
          //alert(123);
          window.css('left', e.pageX - window.offsetWidth / 2 + 'px');
          window.css('top', e.pageY - window.offsetHeight / 2 + 'px');
        }
      }
    }
  }
})(jQuery, Drupal, drupalSettings)