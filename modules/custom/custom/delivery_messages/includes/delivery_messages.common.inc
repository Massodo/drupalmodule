<?php

/**
 * @file
 * Create custom function for delivery_messages.
 */

/**
 * Functions for load user data.
 */
function delivery_messages_load_user_data() {
  $data = array();
  $users = entity_load('user');
  foreach ($users as $user) {
    if ($user->mail) {
      $data[] = $user->uid;
    }
  }
  return $data;
}
