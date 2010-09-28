<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function fserver_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "context" && $api == "context") {
    return array("version" => 3);
  }
  elseif ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_node_info().
 */
function fserver_node_info() {
  $items = array(
    'fserver_distro' => array(
      'name' => t('Distribution'),
      'module' => 'features',
      'description' => t('A feature distribution page. Provides the drush make commands and releases for download.'),
      'has_title' => '1',
      'title_label' => t('Distribution'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
    'fserver_project' => array(
      'name' => t('Project'),
      'module' => 'features',
      'description' => t('A feature project page. Provides a summary of project information and releases for download.'),
      'has_title' => '1',
      'title_label' => t('Project'),
      'has_body' => '1',
      'body_label' => t('Description'),
      'min_word_count' => '0',
      'help' => '',
    ),
    'fserver_release' => array(
      'name' => t('Release'),
      'module' => 'features',
      'description' => t('A single release package for a feature.'),
      'has_title' => '1',
      'title_label' => t('Release'),
      'has_body' => '1',
      'body_label' => t('Notes'),
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}

/**
 * Implementation of hook_views_api().
 */
function fserver_views_api() {
  return array(
    'api' => '2',
  );
}
