<?php

namespace Drupal\nodeviewcount;

use Drupal\Core\Config\ConfigFactoryInterface;
use Drupal\Core\Database\Connection;
use Drupal\Core\Datetime\DrupalDateTime;
use Drupal\Core\Session\AccountInterface;
use Drupal\node\NodeInterface;
use Drupal\user\UserInterface;

define('DEFAULT_TIME_FORMAT', 'Y-m-d H:i:sP');

/**
 * Provides an class for interfering with nodeviewcount records.
 */
class NodeViewCountRecordsManager implements NodeViewCountRecordsManagerInterface {

  /**
   * The database connection object.
   *
   * @var \Drupal\Core\Database\Connection
   */
  protected $connection;

  /**
   * Nodeviewcount configuration object.
   *
   * @var \Drupal\Core\Config\Config $config
   */
  protected $config;

  /**
   * Constructs a NodeViewCountRecordsManager object.
   *
   * @param \Drupal\Core\Database\Connection $connection
   *   The database connection object.
   * @param \Drupal\Core\Config\ConfigFactoryInterface $config_factory
   *   Configuration object factory.
   */
  public function __construct(Connection $connection, ConfigFactoryInterface $config_factory) {
    $this->connection = $connection;
    $this->config = $config_factory->get('nodeviewcount.settings');
  }

  /**
   * {@inheritdoc}
   */
  public function insertRecord($uid, $nid) {
    $config = \Drupal::config('nodeviewcount.settings');

    if($config->get('duplicate_views') == 0){
      $this->insertData($uid, $nid);
    } else {
      $query = \Drupal::database()->select('nodeviewcount', 'nvc');
      $query->addField('nvc','id');
      $query->condition('uid', $uid, '=');
      $query->condition('nid', $nid, '=');
      $result = $query->execute()->fetchField();

      if($result == NULL){
        $this->insertData($uid, $nid);
      } else {
        $dateTime = new DrupalDateTime('NOW', date_default_timezone_get());
        $query = \Drupal::database()->update('nodeviewcount');
        $query->fields([
          'datetime' => $dateTime->format(DEFAULT_TIME_FORMAT)
        ]);
        $query->condition('id', $result, '=');
        $query->execute();
      }
    }
  }

  private function insertData($uid, $nid){
    $timeZone = date_default_timezone_get();
    $dateTime = new DrupalDateTime('NOW', $timeZone);
    $fields = array(
      'nid' => $nid,
      'uid' => $uid,
      'datetime' => $dateTime->format(DEFAULT_TIME_FORMAT),
    );
    $this->connection->insert('nodeviewcount')
    ->fields($fields)
    ->execute();
  }

  /**
   * {@inheritdoc}
   */
  public function getNodeViewsCount(NodeInterface $node, UserInterface $user = NULL, $distinct_users = FALSE) {
    drupal_set_message('get node view count');
    if (!$this->isRecordableForNodeType($node)) {
      return FALSE;
    }
    if (!is_null($user) && !$this->isRecordableForUserRole($user)) {
      return FALSE;
    }
    $query = $this->connection->select('nodeviewcount', 'nvc');
    $query->condition('nid', $node->id(), '=');
    if ($user) {
      $query->condition('uid', $user->id(), '=');
    }
    if ($distinct_users) {
      $query->addExpression('COUNT(DISTINCT uid)');
    }
    else {
      $query->addExpression('COUNT(*)');
    }
    return $query->execute()->fetchAll();
  }

  /**
   * {@inheritdoc}
   */
  public function deleteOldRecords($time) {
    $this->connection->delete('nodeviewcount')
      ->condition('datetime', REQUEST_TIME - $time, '<')
      ->execute();
  }

  /**
   * {@inheritdoc}
   */
  public function isRecordableForViewMode($view_mode) {
    $tracked_view_modes = $this->config->get('view_modes');
    return in_array($view_mode, $tracked_view_modes, TRUE);
  }

  /**
   * {@inheritdoc}
   */
  public function isRecordableForUserRole(AccountInterface $account) {
    $tracked_user_roles = $this->config->get('user_roles');
    $excluded_user_roles = $this->config->get('excluded_user_roles');
    $is_checked_user_role = array_intersect($tracked_user_roles, $account->getRoles()) !== [];
    $is_in_excluded_user_roles = array_intersect($excluded_user_roles, $account->getRoles()) !== [];
    return $is_checked_user_role && !$is_in_excluded_user_roles;
  }

  /**
   * {@inheritdoc}
   */
  public function isRecordableForNodeType(NodeInterface $node) {
    $tracked_unode_types = $this->config->get('node_types');
    return in_array($node->bundle(), $tracked_unode_types, TRUE);
  }

  /**
   * {@inheritdoc}
   */
  public function getLogsLifeTime() {
    return $this->config->get('logs_life_time');
  }

}