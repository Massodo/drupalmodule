<?php

/**
 * @file
 * Build form for node_views_entity.
 */

/**
 * Build node_views_entity form.
 */
function node_views_entity_form($form, &$form_state, $node_views_entity, $op = 'edit') {
  global $user;
  $nodetitle = node_load($node_views_entity->nid);
  $form['nid'] = array(
    '#title' => 'Node Title',
    '#type' => 'textfield',
    '#default_value' => isset($nodetitle->title) ? $nodetitle->title : '',
    '#required' => TRUE,
  );
  $form['uid'] = array(
    '#title' => 'Username',
    '#type' => 'textfield',
    '#default_value' => isset($user->name) ? $user->name : '',
    '#required' => TRUE,
  );
  $form['created'] = array(
    '#title' => 'Date Create',
    '#type' => 'textfield',
    '#default_value' => isset($node_views_entity->created) ? $node_views_entity->created : '',
    '#required' => TRUE,
  );

  $form['actions'] = array(
    '#type' => 'actions',
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Сохранить',
  );

  return $form;
}

/**
 * Submit button for node_views_entity.
 */
function node_views_entity_form_submit(&$form, &$form_state) {
  $node_views_entity = entity_ui_form_submit_build_entity($form, $form_state);
  $node_views_entity->save();
  $form_state['redirect'] = 'admin/config/custom/node_views_entity';
}
