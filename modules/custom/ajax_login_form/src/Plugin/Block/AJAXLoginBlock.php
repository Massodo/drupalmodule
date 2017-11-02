<?php
/**
 * @file
 * Contains \Drupal\ajax_login_form\Plugin\Block\AJAXLoginForm
 */

namespace Drupal\ajax_login_form\Plugin\Block;

use Drupal\Core\Block\BlockBase;

/**
 * Provides a 'AJAXLogin' Block
 *
 * @Block(
 *   id = "AJAXLoginBlock",
 *   admin_label = @Translation("Login Block"),
 * )
 */
class AJAXLoginBlock extends BlockBase{

  /**
   * {@inheritdoc}
   */
  public function build()
  {
    return $form = \Drupal::formBuilder()->getForm('Drupal\ajax_login_form\Form\AJAXLoginForm');
  }
}