<?php

namespace Drupal\message\Form;

use Drupal\Core\Form\FormBase;
use Drupal\Core\Form\FormStateInterface;

class ModalForm extends FormBase {

  /**
   * Returns a unique string identifying the form.
   *
   * @return string
   *   The unique string identifying the form.
   */
  public function getFormId()
  {
    return 'message_modal_form';
  }

  /**
   * Form constructor.
   *
   * @param array $form
   *   An associative array containing the structure of the form.
   * @param \Drupal\Core\Form\FormStateInterface $form_state
   *   The current state of the form.
   *
   * @return array
   *   The form structure.
   */
  public function buildForm(array $form, FormStateInterface $form_state)
  {
    $config = \Drupal::config('message.settings');

    $form = [
      '#theme' => 'hello_page',
      '#styles' =>t(
      'height:' . $config->get('height') . 'px;' .
        'width:' . $config->get('width') . 'px;' .
        'background:' . $config->get('background') .';' .
        'border:' . $config->get('border') . 'px solid;' .
        'border-color:' . $config->get('borderColor') . ';' .
        'font-size:' . $config->get('fontSize') . 'px;' .
        'color:' . $config->get('fontColor') . ';'
      ),
      '#title' => $config->get('title'),
      '#message' => $config->get('message'),
    ];

    $form['#attached']['library'][] = 'message/message';
    return $form;

  }





  /**
   * Form submission handler.
   *
   * @param array $form
   *   An associative array containing the structure of the form.
   * @param \Drupal\Core\Form\FormStateInterface $form_state
   *   The current state of the form.
   */
  public function submitForm(array &$form, FormStateInterface $form_state)
  {
    // TODO: Implement submitForm() method.
  }
}

/*
$config = \Drupal::config('message.settings');
'#title' => $config->get('title'),
'#message' => $config->get('message'),
*/