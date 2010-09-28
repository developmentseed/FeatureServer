<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function fserver_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: features:fserver
  $menu_links['features:fserver'] = array(
    'menu_name' => 'features',
    'link_path' => 'fserver',
    'router_path' => 'fserver',
    'link_title' => 'Projects',
    'options' => array(),
    'module' => 'system',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '0',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Projects');


  return $menu_links;
}
