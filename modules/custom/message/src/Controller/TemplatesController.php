<?php

namespace Drupal\message\Controller;

use Drupal\Core\Controller\ControllerBase;

class TemplatesController extends ControllerBase {
  public function content() {
    // the {name} in the route gets captured as $name variable
    // in the function called
    return [
    '#theme' => 'hello_page',
      //'#name' => $name,
      /*
      '#attached' => [
        'library' => [
          'acme/acme-styles', //include our custom library for this response

        ]

      ]
      */
    ];
  }
}