<?php

/**
 * Helper to implementation of hook_node_info().
 */
function _fserver_node_info() {
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
