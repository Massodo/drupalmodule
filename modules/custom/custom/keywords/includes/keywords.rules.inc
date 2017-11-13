<?php

/**
 * @file
 * Create new rules for keywords.
 */

/**
 * Implements hook_rules_event_info().
 */
function keywords_rules_event_info() {
  return array(
    'keywords_node_update' => array(
      'label' => t('Node update'),
      'module' => 'keywords',
      'group' => t('Custom'),
    ),
  );
}

/**
 * Implements hook_default_rules_configuration().
 */
function keywords_default_rules_configuration() {
  $rule = rules_reaction_rule();
  $rule->label = 'Node Update';
  $rule->active = TRUE;
  $rule->event('keywords_node_update');

  $configs['keywords_default'] = $rule;
  return $configs;
}

/**
 * Implements hook_node_update().
 */
function keywords_node_update($node) {
  $message = '';
  $keyword = array();
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'keywords');
  $result = $query->execute();

  $records = array();

  foreach ($result['keywords'] as $record) {
    $records[] = $record->kid;
  }
  $kids = entity_load('keywords', $records);

  $wrapper = entity_metadata_wrapper('node', $node);
  $node_keyword = preg_split('/[\s,]+/', $wrapper->body->value->value());

  foreach ($kids as $kid) {
    $keyword[] = $kid->keyword;
  }

  $compare_keywords = array_intersect($keyword, $node_keyword);

  foreach ($compare_keywords as $compare_keyword) {
    $message .= $compare_keyword . ' / ';
  }

  if ($compare_keywords) {
    watchdog('keywords', 'Node: !link. Keywords: %message', array(
      '!link' => l($node->title, 'node/' . $node->nid),
      '%message' => $message,
    ));
  }
}
