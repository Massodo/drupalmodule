<?php

namespace Drupal\nodeviewcount\Plugin\views\field;

use Drupal\Core\Form\FormStateInterface;
use Drupal\views\Annotation\ViewsJoin;
use Drupal\views\Plugin\views\field\FieldPluginBase;
use Drupal\views\ResultRow;

/**
 * @ingroup views_field_handlers
 *
 * @ViewsField("node_view_count_count_of_views")
 */
class NodeViewCountCountOfViews extends FieldPluginBase {

  /**
   * {@inheritdoc}
   */
  public function query () {
    $this->ensureMyTable();
    $this->query->addField('nodeviewcount', 'nid', 'count');
    $this->query->addWhere(0, 'nodeviewcount.nid', 180);
  }

  public function render (ResultRow $values) {
    return [
      '#markup' => count($values->count),
    ];
  }
}