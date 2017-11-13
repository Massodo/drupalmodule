<?php

/**
 * @file
 * Build admin form for delivery_messages.
 */

/**
 * Delivery Messages config form.
 */
function delivery_messages_config_form($form, &$form_state) {
  $form['field_container'] = array(
    '#type' => 'container',
    '#weight' => 80,
    '#tree' => TRUE,
    '#prefix' => '<div id="js-ajax-elements-wrapper">',
    '#suffix' => '</div>',
  );

  $form['#attached']['css'] = array(
    drupal_get_path('module', 'delivery_messages') . '/theme/css/delivery_messages.css',
  );

  $form['#attached']['js'] = array(
    drupal_get_path('module', 'delivery_messages') . '/theme/js/delivery_messages.js',
  );

  $messages = variable_get('delivery_messages_messages');

  if (empty($messages)) {
    $array[] = array(
      'message' => '',
      'active' => 0,
    );
    variable_set('delivery_messages_messages', $array);
  }

  $messages = variable_get('delivery_messages_messages');

  foreach ($messages as $key => $value) {
    $form['field_container'][$key] = array(
      '#type' => 'container',
      '#tree' => TRUE,
    );

    $form['field_container'][$key]['fieldset'] = array(
      '#type' => 'fieldset',
      '#collapsible' => FALSE,
      '#collapsed' => FALSE,
    );

    $form['field_container'][$key]['fieldset']['spoiler'] = array(
      '#type' => 'fieldset',
      '#title' => t('Delivery Message') . ' ' . $key,
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $form['field_container'][$key]['fieldset']['spoiler']['delivery_messages_message ' . $value['message']] = array(
      '#type' => 'textarea',
      '#title' => t('Delivery Message'),
      '#default_value' => $value['message'],
      '#format' => 'full_html',
      '#pre_render' => array('ckeditor_pre_render_text_format'),
    );

    $form['field_container'][$key]['fieldset']['remove_'] = array(
      '#type' => 'submit',
      '#value' => t('Remove'),
      '#submit' => array('delivery_messages_remove_message'),
      '#ajax' => array(
        'callback' => 'delivery_messages_remove_message_callback',
        'wrapper' => 'js-ajax-elements-wrapper',
      ),
      '#attributes' => array(
        'class' => array('button-small'),
      ),
      '#name' => 'remove_' . $key,
    );

    $form['field_container'][$key]['fieldset']['checkbox'] = array(
      '#type' => 'checkbox',
      '#title' => t('Active'),
      '#default_value' => $value['active'],
    );
  }


  $form['field_container']['token_tree'] = array(
    '#type' => 'fieldset',
    '#title' => t('Replacement patterns'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => theme('token_tree', array('token_types' => array('user'))),
    '#weight' => 10,
  );

  $form = system_settings_form($form);
  $form['#submit'] = array('delivery_messages_submit');
  $form['field_container']['add_item'] = array(
    '#type' => 'submit',
    '#value' => t('Add item'),
    '#submit' => array('delivery_messages_add_message'),
    '#ajax' => array(
      'callback' => 'delivery_messages_add_message_callback',
      'wrapper' => 'js-ajax-elements-wrapper',
    ),
    '#weight' => 10,
  );

  $form['field_container']['remove_all_item'] = array(
    '#type' => 'submit',
    '#value' => t('Remove all'),
    '#submit' => array('delivery_messages_remove_all_messages'),
    '#ajax' => array(
      'callback' => 'delivery_messages_remove_all_messages_callback',
      'wrapper' => 'js-ajax-elements-wrapper',
    ),
    '#weight' => 10,
  );
  return $form;
}

/**
 * Remove field button submit callback.
 */
function delivery_messages_remove_message($form, &$form_state) {
  $remove = $form_state['triggering_element']['#parents'][1];
  $messages = variable_get('delivery_messages_messages');

  unset($messages[$remove]);
  variable_set('delivery_messages_messages', $messages);

  $form_state['rebuild'] = TRUE;
  drupal_get_messages();
}

/**
 * Remove field button ajax callback.
 */
function delivery_messages_remove_message_callback($form, &$form_state) {
  return $form['field_container'];
}

/**
 * Add more button submit callback.
 */
function delivery_messages_add_message($form, &$form_state) {
  $messages = variable_get('delivery_messages_messages');

  foreach ($messages as $key => $value) {
    $array[] = array(
      'message' => $form_state['values']['field_container'][$key]['fieldset']['spoiler']['delivery_messages_message ' . $value['message']],
      'active' => $form_state['values']['field_container'][$key]['fieldset']['checkbox'],
    );
  }

  $array[] = array(
    'message' => '',
    'active' => 0,
  );

  variable_set('delivery_messages_messages', $array);

  $form_state['rebuild'] = TRUE;
  drupal_get_messages();
}

/**
 * Add more button ajax callback.
 */
function delivery_messages_add_message_callback($form, $form_state) {
  return $form['field_container'];
}

/**
 * Remove all item button submit callback.
 */
function delivery_messages_remove_all_messages($form, &$form_state) {
  $messages = variable_get('delivery_messages_messages');
  $messages = array();
  variable_set('delivery_messages_messages', $messages);

  $form_state['rebuild'] = TRUE;
  drupal_get_messages();
}

/**
 * Remove all item button ajax callback.
 */
function delivery_messages_remove_all_messages_callback($form, $form_state) {
  return $form['field_container'];
}

/**
 * Submit function for delivery_messages form.
 */
function delivery_messages_submit($form, $form_state) {
  $messages = variable_get('delivery_messages_messages');
  $active_count = 0;

  foreach ($messages as $key => $value) {
    $array[] = array(
      'message' => $form_state['values']['field_container'][$key]['fieldset']['spoiler']['delivery_messages_message ' . $value['message']],
      'active' => $form_state['values']['field_container'][$key]['fieldset']['checkbox'],
    );

    if ($form_state['values']['field_container'][$key]['fieldset']['checkbox'] == 1) {
      $active_count++;
    }
  }

  if ($active_count > 1) {
    drupal_set_message('Select no more than one message!', 'error');
  }
  else {
    variable_set('delivery_messages_messages', $array);
    drupal_set_message('Save successfully!', 'status');
  }
}
