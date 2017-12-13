<?php

namespace Drupal\nodeviewcount\Plugin\views\field;

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
  }

  public function render (ResultRow $values) {
    $query = \Drupal::database()->select('nodeviewcount','count');
    $query->addField('count','nid');
    $query->condition('count.nid', $values->_entity->id(), '=');
    $result = count($query->execute()->fetchAll());

    return [
      '#markup' => $result,
    ];
  }
}