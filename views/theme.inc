<?php

/**
 * Theme preprocess for theme('fserver_updatexml')
 */
function template_preprocess_fserver_updatexml(&$vars) {
  $vars['view']->style_plugin->preprocess($vars);
}
