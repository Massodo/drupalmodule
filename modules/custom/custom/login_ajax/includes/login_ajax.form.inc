<?php

/**
 * @file
 * Build form for login_ajax.
 */

/**
 * Function Submit for login_ajax.
 */
function login_ajax_user_login_submit($form, $form_state) {
  $name = $form_state['values']['name'];
  $pass = $form_state['values']['pass'];
  if (user_authenticate($name, $pass)) {
    drupal_set_message(t('Hello,') . (' ') . $name . t('! To see the website as a registered user go to this link.'));

    $form['name'] = array(
      '#type' => 'value',
    );
    $form['pass'] = array(
      '#type' => 'value',
    );
    $form['actions']['submit'] = array(
      '#type' => 'value',
    );
  }

  return $form;
}
