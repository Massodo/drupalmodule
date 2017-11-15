<?php

namespace Drupal\user_discount_code\Controller;

use Drupal\Core\Controller\ControllerBase;

class CodePageController extends ControllerBase {
  public function pageController(){

    //$a =  token_replace();


    return [
      '#theme' => 'discountPage',
      '#title' => 'Title',
      '#message' => t('123'),
    ];
  }
}