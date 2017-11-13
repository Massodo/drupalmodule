<?php

/**
 * @file
 * Build form for user_discount.
 */

/**
 * Build user_discount form for redirect after user register.
 */
function user_discount_form_alter(&$form, &$form_state, $form_id) {
  if ($form_id == 'user_register_form') {
    $form['#submit'][] = 'user_discount_user_register_submit';
  }
}

/**
 * Custom function Register Submit for user_discount.
 */
function user_discount_user_register_submit($form, &$form_state) {
  $form_state['redirect'] = 'successful';
}

/**
 * Build node_views_entity form.
 */
function user_discount_list_form($form, &$form_state, $user_discount, $op = 'edit') {
  global $user;
  $form['uid'] = array(
    '#title' => 'UID',
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => isset($user->uid) ? $user->uid : '',
  );
  $form['discount_code'] = array(
    '#title' => 'Discount Code',
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => isset($user_discount->discount_code) ? $user_discount->discount_code : '',
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
function user_discount_form_submit(&$form, &$form_state) {
  $user_discount = entity_ui_form_submit_build_entity($form, $form_state);
  $user_discount->save();
  $form_state['redirect'] = 'admin/config/custom/user_discount_list';
}
