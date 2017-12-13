<?php

namespace Drupal\nodeviewcount\Plugin\views\field;

use Drupal\views\Plugin\views\field\FieldPluginBase;
use Drupal\views\ResultRow;
use Drupal\views\Views;

/**
 * @ingroup views_field_handlers
 *
 * @ViewsField("node_view_count_user_name")
 */
class NodeViewCountUserId extends FieldPluginBase {

  /**
   * {@inheritdoc}
   */
  public function query () {
    $configuration = [
      'table' => 'users_field_data',
      'field' => 'uid',
      'left_table' => 'nodeviewcount',
      'left_field' => 'uid',
      'operator' => '=',
    ];
    $join = Views::pluginManager('join')->createInstance('standard', $configuration);

    $this->ensureMyTable();
    $this->query->addRelationship('users_field_data', $join, 'users_field_data');
    $this->query->addField('users_field_data', 'name', 'username');
  }

  /**
   * {@inheritdoc}
   */
  public function render (ResultRow $values) {
    return [
      '#markup' => $values->username,
    ];
  }
}
