<?php

namespace Drupal\message\Form;

use Drupal\Core\Form\ConfigFormBase;
use Drupal\Core\Form\FormStateInterface;

class SettingsForm extends ConfigFormBase{

  /**
   * Gets the configuration names that will be editable.
   *
   * @return array
   *   An array of configuration object names that are editable if called in
   *   conjunction with the trait's config() method.
   */
  protected function getEditableConfigNames()
  {
    return ['message.settings',];
  }

  /**
   * Returns a unique string identifying the form.
   *
   * @return string
   *   The unique string identifying the form.
   */
  public function getFormId()
  {
    return 'message_settings_form';
  }

  public function buildForm(array $form, FormStateInterface $form_state)
  {
    $config = $this->config('message.settings');

    $form['example_thing'] = array(
    '#type' => 'textfield',
    '#title' => $this->t('Things'),
    '#default_value' => $config->get('things'),
    );

    $form['other_things'] = array(
    '#type' => 'textfield',
    '#title' => $this->t('Other things'),
    '#default_value' => $config->get('other_things'),
    );
    return parent ::buildForm($form, $form_state);
  }

  public function submitForm(array &$form, FormStateInterface $form_state)
  {
    // Retrieve the configuration
    \Drupal::configFactory()->getEditable('example.settings')
    // Set the submitted configuration setting
    ->set('things', $form_state->getValue('example_thing'))
    // You can set multiple configurations at once by making
    // multiple calls to set()
    ->set('other_things', $form_state->getValue('other_things'))
    ->save();
    parent ::submitForm($form, $form_state);
  }
}