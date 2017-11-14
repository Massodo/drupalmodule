<?php

namespace Drupal\internet_reception\Form;

use Drupal\Core\Form\FormBase;
use Drupal\Core\Form\FormStateInterface;
use Drupal\smtp\Plugin\Mail\SMTPMailSystem;

class InternetReceptionForm extends FormBase {

  /**
   * {@inheritdoc}
   */
  public function getFormId() {
    return 'internet_reception_exform_form';
  }

  /**
   * {@inheritdoc}
   */
  public function buildForm(array $form, FormStateInterface $form_state) {
    $form['name'] = [
      '#type' => 'textfield',
      '#title' => $this->t('Your name'),
      '#required' => TRUE
    ];

    $form['email'] = [
      '#type' => 'email',
      '#title' => $this->t('Your email'),
      '#required' => TRUE
    ];

    $form['age'] = [
      '#type' => 'number',
      '#title' => $this->t('Your age'),
      '#required' => TRUE
    ];

    $form['subject'] = [
      '#type' => 'textfield',
      '#title' => $this->t('Your subject'),
      '#required' => TRUE
    ];

    $form['message'] = [
      '#type' => 'textfield',
      '#title' => $this->t('Your message'),
      '#required' => TRUE
    ];

    $form['actions']['submit'] = [
      '#type' => 'submit',
      '#value' => $this->t('Submit'),
    ];

    return $form;
  }

  /**
   * {@inheritdoc}
   */
  public function validateForm(array &$form, FormStateInterface $form_state) {
    $is_number = preg_match("/[\d]+/", $form_state->getValue('name'), $match);

    if ($is_number > 0) {
      $form_state->setErrorByName('title', $this->t('Name files invalid value.'));
    }

    if (($form_state->getValue('age')) < 0) {
      $form_state->setErrorByName('age', $this->t('Invalid age'));
    }
  }

  /**
   * {@inheritdoc}
   */
  public function submitForm(array &$form, FormStateInterface $form_state) {
    $account = \Drupal::currentUser();
    $system_site_config = \Drupal::config('system.site');


    $params['subject'] = $form_state->getValue('subject');
    $params['body'] = array(
      t('Name: ') . t($form_state->getValue('name')),
      t('Age: ') . t($form_state->getValue('age')),
      t('Email: ') . t($form_state->getValue('email')),
      $form_state -> getValue('message')
    );

    \Drupal::service('plugin.manager.mail')->mail('smtp', 'smtp-test',
    $system_site_config->get('mail'), $account->getPreferredLangcode() , $params);
  }
}
