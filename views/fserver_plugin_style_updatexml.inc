<?php

class fserver_plugin_style_updatexml extends views_plugin_style {
  /**
   * List of project XML elements.
   */
  private function project_elements() {
    return array('title', 'short_name', 'api_version', 'link', 'type', 'redirect');
  }

  /**
   * List of release XML elements.
   */
  private function release_elements() {
    return array('version_major', 'version_patch', 'version_extra', 'release_link', 'download_link', 'date', 'mdhash', 'filesize', 'security', 'recommended');
  }

  /**
   * Set default options
   */
  function option_definition() {
    $options = parent::option_definition();

    $project_defaults = array();
    foreach ($this->project_elements() as $element) {
      $project_defaults[$element] = '';
    }
    $options['project'] = array('default' => $project_defaults);

    $release_defaults = array();
    foreach ($this->release_elements() as $element) {
      $release_defaults[$element] = '';
    }
    $options['release'] = array('default' => $release_defaults);

    return $options;
  }

  /**
   * Render the given style.
   */
  function options_form(&$form, &$form_state) {
    // Build list of valid fields
    $options = array();
    $handlers = $this->display->handler->get_handlers('field');
    foreach ($handlers as $field => $handler) {
      if (empty($handler->options['exclude'])) {
        $options[$field] = $handler->label();
      }
    }

    $form['project'] = array(
      '#tree' => TRUE,
      '#type' => 'fieldset',
      '#title' => t('Project fields'),
    );
    foreach ($this->project_elements() as $element) {
      $form['project'][$element] = array(
        '#title' => $element,
        '#type' => 'select',
        '#options' => $options,
        '#default_value' => $this->options['project'][$element],
      );
    }

    $form['release'] = array(
      '#tree' => TRUE,
      '#type' => 'fieldset',
      '#title' => t('Release fields'),
    );
    foreach ($this->release_elements() as $element) {
      $form['release'][$element] = array(
        '#title' => $element,
        '#type' => 'select',
        '#options' => $options,
        '#default_value' => $this->options['release'][$element],
      );
    }
  }

  /**
   * Theme preprocessor.
   */
  function preprocess(&$vars) {
    $fields = $vars['view']->field;

    // Build project XML values
    $project = array();
    foreach ($vars['options']['project'] as $element => $field) {
      $alias = $fields[$field]->field_alias;
      foreach ($vars['rows'] as $row) {
        if (isset($row->{$alias})) {
          $project[$element] = $fields[$field]->theme($row);
          continue;
        }
      }
    }

    // If this is a legacy project and has a redirect URL use it immediately.
    if (!empty($project['redirect'])) {
      $redirect = $project['redirect'];
      $redirect .= !empty($vars['view']->args) ? '/'. implode('/', $vars['view']->args) : '';
      drupal_goto($redirect);
    }

    // Additional formatting for some values
    if (isset($project['link'])) {
      $project['link'] =  url($project['link'], array('absolute' => TRUE));
    }

    // Build release XML values
    $releases = array();
    $project['recommended_major'] = '';
    $project['supported_majors'] = array();
    foreach ($vars['rows'] as $num => $row) {
      foreach ($vars['options']['release'] as $element => $field) {
        $alias = $fields[$field]->field_alias;
        if (isset($row->{$alias})) {
          switch ($element) {
            // Don't mess with certain fields, period.
            case 'recommended':
            case 'security':
            case 'version_major':
            case 'version_patch':
            case 'version_extra':
              $releases[$num][$element] = check_plain($row->{$alias});
              break;
            default:
              $releases[$num][$element] = $fields[$field]->theme($row);
              break;
          }
        }
      }

      if ($releases[$num]['recommended']) {
        // Use the first major version for the project major.
        // The list is sorted by "major desc", this way the latest branch will be
        // recommended and all other branches (which have a recommended release)
        // will be tagged as supported.
        if (empty($project['recommended_major'])) {
          $project['recommended_major'] = $releases[$num]['version_major'];
        }
        $project['supported_majors'][$releases[$num]['version_major']] = $releases[$num]['version_major'];
      }

      // Version
      $releases[$num]['version'] = "{$project['api_version']}-{$releases[$num]['version_major']}.{$releases[$num]['version_patch']}";
      if (!empty($releases[$num]['version_extra'])) {
        $releases[$num]['version'] .= "-{$releases[$num]['version_extra']}";
      }

      // Name
      $releases[$num]['name'] = "{$project['short_name']} {$releases[$num]['version']}";

      // Release link
      $releases[$num]['release_link'] = url($releases[$num]['release_link'], array('absolute' => TRUE));

      // Download link
      $releases[$num]['download_link'] = file_create_url($releases[$num]['download_link']);
    }
    sort($project['supported_majors']);
    $project['supported_majors'] = implode(",", $project['supported_majors']);

    // Finalize
    $vars['project'] = $project;
    $vars['releases'] = $releases;
    drupal_set_header('Content-Type: application/xml; charset=utf-8');
  }
}
