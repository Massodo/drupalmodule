<?php

/**
 * @file
 * Functions for working with the database in a module node_views.
 */

/**
 * Function for selection views on all nodes in a node_views_config_page_view().
 */
function node_views_db_page_view() {
  $header = array(
    array('data' => t('title'), 'field' => 'nid'),
    array('data' => t('created'), 'field' => 'created'),
  );
  $nodes = db_select('node_views', 'n');
  $nodes->fields('n', array('nid'));
  $count = $nodes->addExpression('count(nid)', 'count');
  $nodes->groupBy('n.nid');
  $nodes->extend('TableSort')->orderByHeader($header);
  return $result = $nodes->execute();
}

/**
 * Function for selection views on all nodes in a node_views_config_page_view().
 */
function node_views_db_page_node_view($nid) {
  $header = array(
    array('data' => t('username'), 'field' => 'uid'),
  );
  $nodes = db_select('node_views', 'n');
  $nodes->fields('n', array('nid', 'uid', 'created'));
  $nodes->condition('nid', $nid);
  $nodes->extend('TableSort')->orderByHeader($header);
  return $result = $nodes->execute();
}
