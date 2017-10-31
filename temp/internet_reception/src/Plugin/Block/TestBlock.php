<?php
/**
 * @file
 * Contains \Drupal\first_module\Plugin\Block\TestBlock.
 */
namespace Drupal\internet_reception\Plugin\Block;
use Drupal\Core\Block\BlockBase;

/**
 * Provides a 'Test' Block
 *
 * @Block(
 *   id = "test_block",
 *   admin_label = @Translation("Test block"),
 *   category = @Translation("Test"),
 * )
 */

class TestBlock extends BlockBase{
  /**
   * {@inheritdoc}
   */
  public function build() {
    return array(
      '#theme' => 'my-test-template',
      '#test_var' => $this->t('Hello world'),
    );
  }
}