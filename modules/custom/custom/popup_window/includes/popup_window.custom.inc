<?php

/**
 * @file
 * Custom functions for popup_window.
 */

/**
 * Custom function for render template.
 */
function popup_window_render_template() {
  $status_heading = array(
    'status' => t('Status message'),
    'error' => t('Error message'),
    'warning' => t('Warning message'),
  );
  $status_messages = drupal_get_messages();

  $message = NULL;
  foreach ($status_messages as $key) {
    $message = $key;
  }

  drupal_add_js(array(
    'popup_window' => array(
      'height' => variable_get('popup_window_popup_height', 100),
      'width' => variable_get('popup_window_popup_width', 200),
      'message' => $message,
    ),
  ),
    array('type' => 'setting')
  );

  return theme('popup_window', array(
    'status_messages' => $status_messages,
    'status_heading' => $status_heading,
  ));
}
