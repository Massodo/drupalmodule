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
  $data['nodeviewcount']['count_of_views'] = [
    'title' => t('Count view'),
    'field' => [
      'title' => t('Count view'),
      'help' => t('Count view'),
      'id' => 'node_view_count_count_of_views',
      'click sortable' => TRUE,
    ],
    'sort' => [
      'id' => 'standard',
    ],
  ];
  $data['nodeviewcount']['nid'] = [
    'title' => t('Node id'),
    'field' => [
      'title' => t('Node id'),
      'help' => t('Node id'),
      'id' => 'node_view_count_node_id'
    ],
  ];
  $data['nodeviewcount']['datetime'] = [
    'title' => t('Data time'),
    'field' => [
      'title' => t('Data time'),
      'help' => t('Data time'),
      'id' => 'node_view_count_data_time',
      'click sortable' => TRUE,
    ],
    'sort' => [
      'id' => 'standard',
    ],
  ];
  $data['nodeviewcount']['uid'] = [
    'title' => t('User id'),
    'field' => [
      'title' => t('User id'),
      'help' => t('User id'),
      'id' => 'node_view_count_user_name'
    ],
    'relationship' => [
      'base' => 'users_field_data',
      'base field' => 'uid',
      'id' => 'standard',
      'label' => t('Node View Count Node'),
    ],
  ];
  return $data;
}