<?php

/**
 * @file
 * Build form for node_update.
 */

/**
 * Node Update form. Allows to start Batch operations.
 */
function node_update_form() {
  $form = array();

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('GO'),
  );

  return $form;
}

/**
 * Submit callback for title changer form.
 */
function node_update_form_submit($form, &$form_state) {
  $result = db_select('node', 'n')
    ->fields('n', array('nid'))
    ->orderBy('nid')
    ->execute();

  foreach ($result as $row) {
    $operations[] = array('node_update_update', array($row->nid));
  }

  $batch = array(
    'operations' => $operations,
    'title' => t('Node processing'),
    'finished' => 'node_update_batch_finished',
  );

  batch_set($batch);
}
