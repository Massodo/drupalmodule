<?php

/**
 * @file
 * Provide views data for nodeviewcount.module.
 */

/**
 * Implements hook_views_data_alter().
 *
 * Alter DB tables defined via hook_views_data().
 */
function nodeviewcount_views_data_alter (array &$data) {
  $data['nodeviewcount']['table']['group'] = t('Node count');
  $data['nodeviewcount']['table']['base'] = [
    'field' => 'nid',
    'title' => t('Node view count'),
    'help' => t('This table is containing the data about count view of node.'),
    'weight' => -10,
  ];
  $data['nodeviewcount']['table']['join'] = [
    'node_field_data' => [
      'left_field' => 'nid',
      'field' => 'nid',
    ],
  ];
  $data['nodeviewcount']['nid'] = [
    'title' => t('Node id'),
    'field' => [
      'title' => t('Node id'),
      'help' => t('Node id'),
      'id' => 'node_view_count_node_id',
      'click sortable' => TRUE,
    ],
    'filter' => [
      'id' => 'numeric',
    ],
    'sort' => [
      'id' => 'standard',
    ],
    'argument' => [
      'id' => 'numeric',
    ],
  ];
  $data['nodeviewcount']['datetime'] = [
    'title' => t('Data time'),
    'help' => t('When user view of node.'),
    'field' => [
      'id' => 'date',
      'click sortable' => TRUE,
    ],
    'filter' => [
      'id' => 'date',
    ],
    'sort' => [
      'id' => 'date',
    ],
  ];
  $data['nodeviewcount']['uid'] = [
    'title' => t('User name'),
    'field' => [
      'title' => t('User name'),
      'help' => t('User name'),
      'id' => 'node_view_count_user_name'
    ],
    'relationship' => [
      'base' => 'users_field_data',
      'base field' => 'uid',
      'id' => 'standard',
      'label' => t('Node View Count Node'),
    ],
    'filter' => [
      'id' => 'name',
    ],
    'sort' => [
      'id' => 'standard',
    ],
  ];
  return $data;
}