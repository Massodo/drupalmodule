<?php

namespace Drupal\note\Form;

use Drupal\Core\Form\ConfigFormBase;
use Drupal\Core\Form\FormStateInterface;

class NoteSettings extends ConfigFormBase {

  /**
   * {@inheritdoc}
   */
  protected function getEditableConfigNames() {
    return ['node.settings'];
  }

  /**
   * {@inheritdoc}
   */
  public function getFormId() {
    return 'node_settings_form';
  }

  /**
   * {@inheritdoc}
   */
  public function buildForm(array $form, FormStateInterface $form_state) {

    $form['date'] = [
      '#type' => 'date',
      '#title' => 'Date',
      '#default_value' => $this->config('node.settings')->get('date'),
    ];
    $form['reset'] = [
      '#type' => 'submit',
      '#value' => t('Reset status'),
    ];
    $form['update'] = [
    '#type' => 'submit',
    '#value' => t('Update status'),
    ];


    return parent::buildForm($form,$form_state);
  }

  /**
   * {@inheritdoc}
   */
  public function validateForm(array &$form, FormStateInterface $form_state) {
    parent::validateForm($form, $form_state);
  }

  /**
   * {@inheritdoc}
   */
  public function submitForm (array &$form, FormStateInterface $form_state) {
    \Drupal::configFactory()->getEditable('node.settings')
    ->set('date', $form_state->getValue('date'))
    ->save();
    parent::submitForm($form, $form_state);
  }
}