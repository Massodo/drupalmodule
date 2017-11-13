<?php

/**
 * @file
 * Build custom form for node_views.
 */

/**
 * Function for show views on all nodes.
 */
function node_views_config_page_view() {
  $header = array(
    array('data' => t('title'), 'field' => 'nid'),
    array('data' => t('created'), 'field' => 'created'),
  );
  $result = node_views_db_page_view();
  $rows = array();

  foreach ($result as $node) {
    $nodetitle = node_load($node->nid);
    $rows[] = array(
      l($nodetitle->title, 'node/' . $node->nid),
      l($node->count, '/admin/config/custom/node_views/' . $node->nid),
    );
  }

  return theme('table', array('header' => $header, 'rows' => $rows));
}

/**
 * Function for show views on current nodes.
 */
function node_views_config_page_node_view($nid) {
  $header = array(
    array('data' => t('username'), 'field' => 'uid'),
    array('data' => t('created'), 'field' => 'created'),
  );
  $result = node_views_db_page_node_view($nid);
  $rows = array();

  foreach ($result as $node) {
    $username = user_load($node->uid);
    if ($username->uid) {
      $user = l($username->name, 'user/' . $username->uid);
    }
    else {
      $user = 'anonymous';
    }
    $rows[] = array(
      $user,
      $node->created,
    );
  }

  return theme('table', array('header' => $header, 'rows' => $rows));
}
