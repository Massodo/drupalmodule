<?php

namespace Drupal\message\Controller;

use Drupal\Core\Controller\ControllerBase;


class TemplatesController extends ControllerBase {
  public function content() {
    // the {name} in the route gets captured as $name variable
    // in the function called;

    $form = [
      '#theme' => 'hello_page',
      '#content' => [
        '#type' => 'markup',
        '#markup' => t('click on me'),
        ],
      '#title' => \Drupal::config('message.settings')->get('title'),
      '#message' => \Drupal::config('message.settings')->get('message'),
      '#attributes' => [
        'style' => [
          //'display: none'
        ]
      ]
    ];
    $form['#attached']['library'][] = 'message/message';
    $form['#attributes']['style'] = [
      //'display:none'
    ];
    return $form;
  }

}