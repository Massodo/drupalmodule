(function ($, Drupal, drupalSettings) {

  "use strict";

  Drupal.behaviors.message = {
    attach: function (context, settings) {

      $(context).find('h1').ready(function (event) {
        //event.preventDefault();
        $('#overlay').fadeIn(400, function () {
          $('#modal').css('display' , 'block').animate({opacity: 1, top: '50%'}, 200);
        })
      });

      $(context).find('#modal > #title').mousedown(function () {
        $(context).find('#modal').draggable({
          containment: "#page", handle: '#title'});
      });

      $(context).find('#close, #overlay').click(function () {
        $('#modal').animate({opacity: 0, top: '45%'}, 200, function () {
          $(this).css('display', 'none');
          $('#overlay').fadeOut(400);
          }
        )
      })
    }
  };
})(jQuery, Drupal, drupalSettings);

/*
    attach: function (context, settings) {
      Database.getTemplate();
      $(context).find('.content').click(function (event) {
        var frontpageModal = Drupal.dialog(Database.getTemplate('hello'), {
          title: '123'
        });
        /*
        var frontpageModal = Drupal.dialog(/*'<div>Modal content</div>', {
          title: 'Modal on frontpage',
          dialogClass: 'front-modal',
          width: 400,
          height: 400,
          autoResize: true,
          close: function (event) {
            $(event.target).remove();
          }
        });
        frontpageModal.showModal();

      });
    }
    */

