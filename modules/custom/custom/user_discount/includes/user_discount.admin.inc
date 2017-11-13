<?php

/**
 * @file
 * Build admin form for user_discount.
 */

 /**
  * User Discount config form.
  */
function user_discount_config_form($form, &$form_state) {
  $form = array();

  $form['user_discount_message'] = array(
    '#type' => 'textarea',
    '#title' => t('User Discount Message'),
    '#default_value' => variable_get('user_discount_message', 'Hello!'),
    '#required' => TRUE,
  );
  $form['token_tree'] = array(
    '#type' => 'fieldset',
    '#title' => t('Replacement patterns'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => theme('token_tree', array('token_types' => array('user'))),
    '#weight' => 10,
  );

  return system_settings_form($form);
}

/**
 * Custom controller for the administrator UI.
 */
class UserDiscountUIController extends EntityDefaultUIController {

  /**
   * Override the menu hook for default ui controller.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['title'] = t('User Discount');
    $items[$this->path]['description'] = t('Manage user discount, including fields.');
    $items[$this->path]['access callback'] = 'user_discount_access';
    $items[$this->path]['type'] = MENU_LOCAL_TASK;
    return $items;
  }

  /**
   * Admin form for searching and doing bulk operations.
   */
  public function overviewForm($form, &$form_state) {
    $header = array(
      'uid' => array('data' => t('Username'), 'field' => 'uid'),
      'discount_code' => array('data' => t('Discount code'), 'field' => 'discount_code'),
      'operations' => array('data' => t('Operations'), 'field' => 'operations'),
    );

    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'user_discount_list');

    $result = $query->execute();
    $user_discount_results = !empty($result['user_discount_list']) ? $result['user_discount_list'] : array();
    $user_discount_array = !empty($user_discount_results) ? user_discount_load_multiple(array_keys($user_discount_results)) : array();
    foreach ($user_discount_array as $tid => $user_discount) {
      $username = user_load($user_discount->uid);
      $options[$tid] = array(
        'uid' => l($username->name, 'user/' . $user_discount->uid),
        'discount_code' => $user_discount->discount_code,
        'operations' =>
        l(t('Edit'), ADMIN_CONTENT_USER_DISCOUNT_MANAGE_URI . $tid) . ' ' .
        l(t('Delete'), ADMIN_CONTENT_USER_DISCOUNT_MANAGE_URI . $tid . '/delete', array(
          'attributes' => array(
            'class' => array('user-discount-delete-' . $user_discount->tid),
          ),
          'query' => array(
            'destination' => ADMIN_CONTENT_USER_DISCOUNT_URI,
          ),
        )),
      );
    }

    $form['entities'] = array(
      '#type' => 'tableselect',
      '#header' => $header,
      '#options' => $options,
      '#attributes' => array('class' => array('entity-sort-table')),
      '#empty' => t('There are no user discount.'),
    );

    return $form;
  }

}
