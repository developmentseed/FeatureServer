<?php

class fserver_handler_field_mdhash extends views_handler_field {
  function allow_advanced_render() { return FALSE; }

  function render($values) {
    $filepath = $values->{$this->field_alias};
    if (file_exists($filepath)) {
      $contents = file_get_contents($filepath);
      return md5($contents);
    }
  }
}
