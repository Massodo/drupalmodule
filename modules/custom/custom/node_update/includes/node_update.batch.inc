<?php

/**
 * @file
 * Run batch for node_update.
 */

/**
 * Update the fields in the nodes.
 */
function node_update_update($nodes, &$context) {
  if (empty($context['sandbox'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['prev_nid'] = 0;
    $context['sandbox']['max'] = db_select('node')->countQuery()->execute()->fetchField();
  }

  $nid = db_select('node', 'n')
    ->fields('n', array('nid'))
    ->condition('nid', $context['sandbox']['prev_nid'], '>')
    ->execute()
    ->fetchField();
  $node = node_load($nid);
  try {
    $wrapper = entity_metadata_wrapper('node', $node);
    $wrapper->field_latest_updates = time();
    $wrapper->save();

    $node_wrapper = entity_metadata_wrapper('node', $node);
    foreach ($node_wrapper->field_rate_date as $field_collection_wrapper) {
      $raw_collection = $field_collection_wrapper->value();
      $raw_collection = entity_metadata_wrapper('field_collection_item', $raw_collection);
      if (date('Ymd', $raw_collection->field_date->value()) != date('Ymd', time())) {
        $raw_collection->field_rate->set(rand(0, 100));
        $raw_collection->field_date->set(time());
      }
      $raw_collection->save();
    }

    $context['sandbox']['progress']++;
    $context['sandbox']['prev_nid'] = $nid;
    $context['results']['titles'][] = $node->title;
    $context['message'] = 'Update <em>' . check_plain($node->title) . '</em>';

    if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
      $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
    }
  }
  catch (EntityMetadataWrapperException $exc) {
    watchdog(
      'MODULE_NAME',
      'EntityMetadataWrapper exception in %function() <pre>@trace</pre>',
      array('%function' => __FUNCTION__, '@trace' => $exc->getTraceAsString()),
      WATCHDOG_ERROR
    );
  }
}

/**
 * Finish callback for Batch.
 */
function node_update_batch_finished($success, $results, $operations) {
  if ($success) {
    drupal_set_message(t('Update finished'));
  }
  else {
    drupal_set_message(t('Finished with an error.'));
  }
}
