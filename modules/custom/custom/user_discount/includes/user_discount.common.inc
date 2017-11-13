<?php

/**
 * @file
 * Create custom function for user_discount.
 */

 /**
  * Custom function for add new record fo user_discount table.
  */
function user_discount_record() {
  global $user;

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'user_discount_list');
  $result = $query->execute();

  foreach ($result['user_discount_list'] as $record) {
    $records[] = $record->tid;
  }

  $tids = entity_load('user_discount_list', $records);

  foreach ($tids as $tid) {
    $uids[] = $tid->uid;
  }

  /* Check user existence in user_discount */
  $token = '';
  if (in_array($user->uid, $uids) == FALSE) {
    /* Record discount_codes in user_discount */
    foreach ($tids as $tid) {
      $discount_codes[] = $tid->discount_code;
    }

    $temp = user_discount_generate_token();

    if (in_array($temp, $discount_codes) == FALSE) {
      $token = $temp;
    }

    $table_name = 'user_discount_list';
    $row = new stdClass();
    $row->uid = $user->uid;
    $row->discount_code = $token;
    drupal_write_record($table_name, $row);
  }
}

/**
 * Custom function for generate token.
 */
function user_discount_generate_token() {
  $characters = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ';
  $charactersLength = strlen($characters);
  $token = '';

  for ($i = 0; $i < 10; $i++) {
    $token .= $characters[rand(0, $charactersLength - 1)];
  }

  return $token;
}

/**
 * Get users count.
 */
function user_discount_get_user_token() {
  user_discount_record();

  global $user;
  $token = '';
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'user_discount_list');
  $result = $query->execute();

  $records = array();

  foreach ($result['user_discount_list'] as $record) {
    $records[] = $record->tid;
  }
  $tids = entity_load('user_discount_list', $records);

  foreach ($tids as $tid) {
    if ($tid->uid == $user->uid) {
      $token = $tid->discount_code;
    }
  }

  return $token;
}

/**
 * Load multiple user_discount based on certain conditions.
 */
function user_discount_load_multiple($user_discount = array(), $reset = FALSE) {
  return entity_load('user_discount_list', $user_discount, $reset);
}
