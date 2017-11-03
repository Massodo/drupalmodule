<?php

namespace Drupal\ajax_login_form\Form;

use Drupal\Core\Form\FormStateInterface;
use Drupal\Core\Link;
use Drupal\Core\Utility\LinkGenerator;
use Drupal\user\Form\UserLoginForm;
use Drupal\Core\Ajax\AjaxResponse;
use Drupal\Core\Ajax\CssCommand;
use Drupal\Core\Ajax\HtmlCommand;
use Drupal\Core\Url;

/**
 * {@inheritdoc}
 */
class AJAXLoginForm extends UserLoginForm {

  /**
   * {@inheritdoc}
   */
  public function getFormId() {
    return 'ajax_login_form';
  }

  /**
   * {@inheritdoc}
   */
  public function buildForm(array $form, FormStateInterface $form_state) {
    if (\Drupal::currentUser()->isAnonymous()){
      $form['system_messages'] = [
        '#markup' => '<div id="form-system-messages"></div>',
        '#weight' => '-100',
      ];

      $form += parent ::buildForm($form, $form_state);

      $form['name'] += [
        '#prefix' => '<div id="ajax-login-form-email">',
        '#suffix' => '</div>'
      ];

      $form['actions']['submit'] += [
        '#ajax' => [
          'callback' => '::ajaxHideForm',
          'callback' => '::ajaxSubmitCallback',
          'event' => 'click',
          'progress' => [
            'type' => 'throbber',
          ]
        ],
        '#prefix' => '<div id="ajax-login-form-submit">',
        '#suffix' => '</div>'
      ];

      $form['pass'] += [
        '#prefix' => '<div id="ajax-login-form-pass">',
        '#suffix' => '</div>'
      ];
    }
    else {
      drupal_set_message(t('You are already logged in.'));
    }
    return $form;
  }

  /**
   * {@inheritdoc}
   */
  public function ajaxSubmitCallback(array &$form, FormStateInterface $form_state) {
    $ajax_response = new AjaxResponse();
    $message = [
      '#theme' => 'status_messages',
      '#message_list' => drupal_get_messages(),
      '#status_headings' => [
        'status' => t('Status message'),
        'error' => t('Error message'),
        'warning' => t('Warning message'),
      ],
    ];
    $messages = \Drupal::service('renderer')->render($message);
    $ajax_response->addCommand(new HtmlCommand('#form-system-messages', $messages));
    if ($form_state->getErrors() == NULL){
      $ajax_response->addCommand(new CssCommand('#ajax-login-form-email', ['display' => 'none']));
      $ajax_response->addCommand(new CssCommand('#ajax-login-form-pass', ['display' => 'none']));
      $ajax_response->addCommand(new CssCommand('#ajax-login-form-submit', ['display' => 'none']));
    }
    return $ajax_response;
  }

  /**
   * {@inheritdoc}
   */
  public function submitForm(array &$form, FormStateInterface $form_state) {
    parent ::submitForm($form, $form_state);
    $link = Link::fromTextAndUrl(t('link'), Url::fromRoute('<current>'))->toString();
    drupal_set_message(t('Hello, username! To see the website as a registered user go to this ' . $link), 'status');
  }
}