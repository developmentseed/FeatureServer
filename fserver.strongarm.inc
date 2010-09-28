<?php

/**
 * Implementation of hook_strongarm().
 */
function fserver_strongarm() {
  $export = array();
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_extra_weights_fserver_project';
  $strongarm->value = array(
    'title' => '-5',
    'body_field' => '8',
    'revision_information' => '10',
    'menu' => '0',
    'book' => '9',
    'attachments' => '13',
  );

  $export['content_extra_weights_fserver_project'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_extra_weights_fserver_release';
  $strongarm->value = array(
    'title' => '-5',
    'body_field' => '0',
    'revision_information' => '20',
    'menu' => '-2',
    'book' => '10',
    'attachments' => '30',
  );

  $export['content_extra_weights_fserver_release'] = $strongarm;
  return $export;
}
