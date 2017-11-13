<?php

/**
 * @file
 * Build form for internet_reception.
 */

/**
 * Build internet_reception form.
 */
function itnernet_reception_page_form($form, $form_state) {
  $form = array();
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#size' => 20,
  );
  $form['email'] = array(
    '#type' => 'textfield',
    '#title' => t('E-Mail'),
    '#size' => 20,
  );
  $form['age'] = array(
    '#type' => 'textfield',
    '#title' => t('Age'),
    '#size' => 20,
    '#element_validate' => array('element_validate_integer_positive'),
  );
  $form['subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Subject'),
    '#size' => 20,
  );
  $form['message'] = array(
    '#type' => 'textarea',
    '#title' => t('Message'),
  );
  $form['captcha'] = array(
    '#type' => 'captcha',
    '#captcha_type' => 'image_captcha/Image',
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  return $form;
}
