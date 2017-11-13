<?php

/**
 * @file
 * Build page for user_discount.
 */

/**
 * User Discount page content.
 */
function user_discount_successful_content() {
  global $user;
  $message = '';
  if ($user->uid != 0) {
    $message = variable_get('user_discount_message', 'Hello!');
    $message = token_replace($message);
  }
  return $message;
}
