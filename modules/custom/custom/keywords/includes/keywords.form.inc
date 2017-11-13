<?php

/**
 * @file
 * Build form for keywords.
 */

/**
 * Build keywords form.
 */
function keywords_form($form, &$form_state, $keywords, $op = 'edit') {
  $form['keyword'] = array(
    '#title' => 'Keyword',
    '#type' => 'textfield',
    '#default_value' => isset($keywords->keyword) ? $keywords->keyword : '',
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
 * Submit button for keywords.
 */
function keywords_form_submit(&$form, &$form_state) {
  $keywords = entity_ui_form_submit_build_entity($form, $form_state);
  $keywords->save();
  $form_state['redirect'] = 'admin/config/custom/keywords';
}
