<?php

/**
 * @file
 * Build admin form for popup_window.
 */

 /**
  * PopUp Window config form.
  */
function popup_window_config_form($form, &$form_state) {
  $form = array();

  $form['popup_window_popup_width'] = array(
    '#type' => 'textfield',
    '#title' => t('PopUp Window Width'),
    '#default_value' => variable_get('popup_window_popup_width', 200),
    '#required' => TRUE,
  );
  $form['popup_window_popup_height'] = array(
    '#type' => 'textfield',
    '#title' => t('PopUp Window Height'),
    '#default_value' => variable_get('popup_window_popup_height', 100),
    '#required' => TRUE,
  );

  return system_settings_form($form);
}
