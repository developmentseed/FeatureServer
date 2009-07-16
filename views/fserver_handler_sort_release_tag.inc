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
    $fields = array(
      0 => array('field_name' => 'field_fserver_api'),
      1 => array('field_name' => 'field_fserver_versionmajor'),
      2 => array('field_name' => 'field_fserver_versionpatch'),
      //3 => array('field_name' => 'field_fserver_versionextra'),
    );

    foreach ($fields as $field) {
      $table = 'node_data_field_fserver_project';
      $column = $field['field_name'] .'_value';

      $table_alias = $this->query->ensure_table($table, $this->relationship);
      $this->query->add_orderby($table_alias, $column, $this->options['order']);
    }

    // Instead of version-extra the release creation date is used for sort.
    $table_alias = $this->query->ensure_table('node', $this->relationship);
    $this->query->add_orderby($table_alias, 'created', $this->options['order']);
  }
}

