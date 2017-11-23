<?php

namespace Drupal\message\Form;

use Drupal\Core\Form\ConfigFormBase;
use Drupal\Core\Form\FormStateInterface;

class SettingsForm extends ConfigFormBase {

  /**
   * {@inheritdoc}
   */
  protected function getEditableConfigNames() {
    return ['message.settings'];
  }

  /**
   * {@inheritdoc}
   */
  public function getFormId() {
    return 'message_settings_form';
  }

  /**
   * {@inheritdoc}
   */
  public function buildForm(array $form, FormStateInterface $form_state) {
    $config = $this->config('message.settings');
    $form['height'] = [
      '#type' => 'number',
      '#title' => $this->t('Height'),
      '#default_value' => $config->get('height'),
    ];
    $form['width'] = [
      '#type' => 'number',
      '#title' => $this->t('Width'),
      '#default_value' => $config->get('width'),
    ];
    $form['background'] = [
      '#type' => 'color',
      '#title' => $this->t('Background color'),
      '#default_value' => $config->get('background'),
    ];
    $form['border'] = [
      '#type' => 'number',
      '#title' => $this->t('Border'),
      '#default_value' => $config->get('border'),
    ];
    $form['borderColor'] = [
      '#type' => 'color',
      '#title' => $this->t('Border color'),
      '#default_value' => $config->get('borderColor'),
    ];
    $form['fontSize'] = [
      '#type' => 'number',
      '#title' => $this->t('Font size'),
      '#default_value' => $config->get('fontSize'),
    ];
    $form['color'] = [
      '#type' => 'color',
      '#title' => $this->t('Text color'),
      '#default_value' => $config->get('color'),
    ];
    $form['title'] = [
      '#type' => 'textfield',
      '#title' => $this->t('Title'),
      '#default_value' => $config->get('title'),
    ];
    return parent ::buildForm($form, $form_state);
  }

  /**
   * {@inheritdoc}
   */
  public function validateForm(array &$form, FormStateInterface $form_state) {
    if ($form_state->getValue('height') < 0) {
      $form_state->setErrorByName('height', t('Height can\'t be less then 0'));
    }
    if ($form_state->getValue('width') < 0) {
      $form_state->setErrorByName('width', t('Width can\'t be less then 0'));
    }
    if ($form_state->getValue('fontSize') < 0) {
      $form_state->getValue('font color', t('Font size can\'t be less then 0'));
    }
    if ($form_state->getValue('border') < 0) {
      $form_state->setErrorByName('border', t('Border can\'t be less then 0'));
    }
    parent ::validateForm($form, $form_state);
  }

  /**
   * {@inheritdoc}
   */
  public function submitForm(array &$form, FormStateInterface $form_state) {
    \Drupal ::configFactory()->getEditable('message.settings')
    ->set('height', $form_state->getValue('height'))
    ->set('width', $form_state->getValue('width'))
    ->set('background', $form_state->getValue('background'))
    ->set('border', $form_state->getValue('border'))
    ->set('borderColor', $form_state->getValue('borderColor'))
    ->set('fontSize', $form_state->getValue('fontSize'))
    ->set('color', $form_state->getValue('color'))
    ->set('title', $form_state->getValue('title'))
    ->save();
    parent ::submitForm($form, $form_state);
    return $form;
  }
}