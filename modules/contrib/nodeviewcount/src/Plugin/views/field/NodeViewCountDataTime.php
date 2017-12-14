<?php

namespace Drupal\nodeviewcount\Plugin\views\field;

use Drupal\views\Plugin\views\field\FieldPluginBase;
use Drupal\views\ResultRow;

/**
 * @ingroup views_field_handlers
 *
 * @ViewsField("node_view_count_data_time")
 */
class NodeViewCountDataTime extends FieldPluginBase {

  /**
   * {@inheritdoc}
   */
  public function query () {
    $this->ensureMyTable();
    $this->query->addField('nodeviewcount', 'datetime', 'date');
  }

  /**
   * {@inheritdoc}
   */
  public function render (ResultRow $values) {
    if ($values->date != '') {
      $date = \Drupal::service('date.formatter')->format($values->date, 'short');
      return [
        '#markup' => $date,
      ];
    }
  }
}