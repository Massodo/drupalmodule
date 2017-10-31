<?php
/**
@file
Contains \Drupal\internet_reception.links.menu.yml\Controller\moduleController.
 */

namespace Drupal\internet_reception\Controller;

use Drupal\Core\Controller\ControllerBase;

class moduleController extends ControllerBase {

  public function content(){
    return [
      '#type' => 'markup',
      '#markup' => t('Hello, World!'),
    ];

  }

}
