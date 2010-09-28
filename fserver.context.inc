<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function fserver_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'fserver-section-project';
  $context->description = '';
  $context->tag = '';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'fserver_project' => 'fserver_project',
        'fserver_distro' => 'fserver_distro',
      ),
      'options' => array(
        'node_form' => 0,
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-fserver_releases-block_1' => array(
          'module' => 'views',
          'delta' => 'fserver_releases-block_1',
          'region' => 'content',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  $export['fserver-section-project'] = $context;
  return $export;
}
