<?php

/**
 * Implementation of hook_content_default_fields().
 */
function fserver_content_default_fields() {
  module_load_include('inc', 'fserver', 'fserver.defaults');
  $args = func_get_args();
  return call_user_func_array('_fserver_content_default_fields', $args);
}

/**
 * Implementation of hook_context_default_contexts().
 */
function fserver_context_default_contexts() {
  module_load_include('inc', 'fserver', 'fserver.defaults');
  $args = func_get_args();
  return call_user_func_array('_fserver_context_default_contexts', $args);
}

/**
 * Implementation of hook_menu_default_items().
 */
function fserver_menu_default_items() {
  module_load_include('inc', 'fserver', 'fserver.defaults');
  $args = func_get_args();
  return call_user_func_array('_fserver_menu_default_items', $args);
}

/**
 * Implementation of hook_node_info().
 */
function fserver_node_info() {
  module_load_include('inc', 'fserver', 'fserver.features.node');
  $args = func_get_args();
  return call_user_func_array('_fserver_node_info', $args);
}

/**
 * Implementation of hook_views_default_views().
 */
function fserver_views_default_views() {
  module_load_include('inc', 'fserver', 'fserver.features.views');
  $args = func_get_args();
  return call_user_func_array('_fserver_views_default_views', $args);
}
