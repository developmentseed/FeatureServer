<?php
// $Id$

/**
 * Sort handler for release tag.
 */
class fserver_handler_sort_release_tag extends views_handler_sort {
  /**
   * Called to add the sort to a query.
   */
  function query() {
    $table = 'node_data_field_fserver_project';
    $table_alias = $this->query->ensure_table($table, $this->relationship);

    // Order by:
    // 1. API version (e.g. 6.x before 5.x).
    // 2. no_extra pseudo-field (e.g. 2.0 before 2.0-beta1).
    // 3. versionmajor (2.x before 1.x).
    // 4. versionpatch (2.1 before 2.0).
    // 5. versionextra (2.1-beta1 before 2.1-alpha1).

    // 1. API.
    $this->query->add_orderby($table_alias, 'field_fserver_api_value', $this->options['order']);

    // 2.
    $this->query->add_field(NULL, "IF ({$table}.field_fserver_versionextra_value IS NULL, 1, 0)", "{$table}_no_extra");
    $this->query->add_orderby(NULL, NULL, $this->options['order'], "{$table}_no_extra");

    // 3-5.
    $fields = array(
      array('field_name' => 'field_fserver_versionmajor'),
      array('field_name' => 'field_fserver_versionpatch'),
      array('field_name' => 'field_fserver_versionextra'),
    );
    foreach ($fields as $field) {
      $column = $field['field_name'] .'_value';
      $this->query->add_orderby($table_alias, $column, $this->options['order']);
    }
  }
}
