<?php

/**
 * Implementation of hook_content_default_fields().
 */
function fserver_content_default_fields() {
  module_load_include('inc', 'fserver', 'fserver.defaults');
  return _fserver_content_default_fields();
}

/**
 * Implementation of hook_context_default_contexts().
 */
function fserver_context_default_contexts() {
  module_load_include('inc', 'fserver', 'fserver.defaults');
  return _fserver_context_default_contexts();
}

/**
 * Implementation of hook_menu_default_items().
 */
function fserver_menu_default_items() {
  module_load_include('inc', 'fserver', 'fserver.defaults');
  return _fserver_menu_default_items();
}

/**
 * Implementation of hook_node_info().
 */
function fserver_node_info() {
  module_load_include('inc', 'fserver', 'fserver.defaults');
  return _fserver_node_info();
}

/**
 * Implementation of hook_views_default_views().
 */
function fserver_views_default_views() {
  module_load_include('inc', 'fserver', 'fserver.defaults');
  return _fserver_views_default_views();
}
