<?php

/**
 * Implementation of hook_views_plugins().
 */
function fserver_views_plugins() {
  return array(
    'module' => 'views',
    'style' => array(
      'updatexml' => array(
        'title' => t('Update XML'),
        'help' => t('Generates a project XML feed compatible with the update module.'),
        'handler' => 'fserver_plugin_style_updatexml',
        'theme' => 'fserver_updatexml',
        'theme path' => drupal_get_path('module', 'fserver') .'/views',
        'path' => drupal_get_path('module', 'fserver') .'/views',
        'uses row plugin' => FALSE,
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'feed',
      ),
    ),
  );
}

/**
 * Implementation of hook_views_plugins().
 */
function fserver_views_data() {
  $data = array();

  // MD5 hash
  $data['files']['mdhash'] = array(
    'real field' => 'filepath',
    'title' => t('MD5 hash'),
    'help' => t('Provides an MD5 hash of the file.'),
    'field' => array(
      'handler' => 'fserver_handler_field_mdhash',
    ),
  );

  return $data;
}

/**
 * Implementation of hook_views_handlers().
 */
function fserver_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'fserver') .'/views',
    ),
    'handlers' => array(
      'fserver_handler_field_mdhash' => array(
        'parent' => 'views_handler_field',
      ),
    ),
  );
}
