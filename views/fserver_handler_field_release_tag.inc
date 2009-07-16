<?php
// $Id$

/**
 * Field handler to present release tag.
 */
class fserver_handler_field_release_tag extends views_handler_field {
  function query() {
    // Do not add this field to query, only add the additional fields.
    $this->add_additional_fields();
  }

  function construct() {
    parent::construct();
    $fields = array(
      0 => array('alias'=> 'core', 'field_name' => 'field_fserver_api'),
      1 => array('alias'=> 'major', 'field_name' => 'field_fserver_versionmajor'),
      2 => array('alias'=> 'patch', 'field_name' => 'field_fserver_versionpatch'),
      3 => array('alias'=> 'extra', 'field_name' => 'field_fserver_versionextra'),
    );

    foreach ($fields as $field) {
      $alias = $field['alias'];
      $table = content_views_tablename($field);
      $column = $field['field_name'] .'_value';

      $this->additional_fields[$alias] = array('table' => $table, 'field' => $column);
    }
  }

  function render($values) {
    $core  = check_plain($values->{$this->aliases['core']});
    $major = check_plain($values->{$this->aliases['major']});
    $patch = check_plain($values->{$this->aliases['patch']});
    $extra = check_plain($values->{$this->aliases['extra']});

    $release = "$core-$major.$patch" . (!empty($extra) ? "-$extra" : '');
    return $release;
  }
}
