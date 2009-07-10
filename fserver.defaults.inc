<?php

/**
 * Helper to implemetation of hook_content_default_fields().
 */
function _fserver_content_default_fields() {
  $fields = array();

  // Exported field: field_fserver_name
  $fields[] = array(
    'field_name' => 'field_fserver_name',
    'type_name' => 'fserver_project',
    'display_settings' => array(
      'weight' => '-4',
      'parent' => '',
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '1',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => 5,
      'size' => '30',
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_fserver_name][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Machine name',
      'weight' => '-4',
      'description' => 'The machine-readable name for your project. This name must contain only lowercase letters, numbers, and underscores. <strong>Example:</strong> cooking_recipes.',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_fserver_api
  $fields[] = array(
    'field_name' => 'field_fserver_api',
    'type_name' => 'fserver_release',
    'display_settings' => array(
      'weight' => '-13',
      'parent' => '',
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '1',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => 'return fserver_cck_options(\'core\');',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Core compatibility',
      'weight' => '-13',
      'description' => '',
      'type' => 'optionwidgets_select',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_fserver_file
  $fields[] = array(
    'field_name' => 'field_fserver_file',
    'type_name' => 'fserver_release',
    'display_settings' => array(
      'weight' => '-8',
      'parent' => '',
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'filefield',
    'required' => '1',
    'multiple' => '0',
    'module' => 'filefield',
    'active' => '1',
    'list_field' => '0',
    'list_default' => 1,
    'description_field' => '0',
    'widget' => array(
      'file_extensions' => 'tgz tar gz',
      'file_path' => 'fserver',
      'progress_indicator' => 'bar',
      'max_filesize_per_file' => '',
      'max_filesize_per_node' => '',
      'label' => 'Package',
      'weight' => '-8',
      'description' => '',
      'type' => 'filefield_widget',
      'module' => 'filefield',
    ),
  );

  // Exported field: field_fserver_project
  $fields[] = array(
    'field_name' => 'field_fserver_project',
    'type_name' => 'fserver_release',
    'display_settings' => array(
      'weight' => '-14',
      'parent' => '',
      'label' => array(
        'format' => 'inline',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'nodereference',
    'required' => '1',
    'multiple' => '0',
    'module' => 'nodereference',
    'active' => '1',
    'referenceable_types' => array(
      'fserver_project' => 'fserver_project',
      'image' => 0,
      'fserver_release' => 0,
    ),
    'advanced_view' => '--',
    'advanced_view_args' => '',
    'widget' => array(
      'autocomplete_match' => 'contains',
      'size' => 60,
      'default_value' => array(
        '0' => array(
          'nid' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Project',
      'weight' => '-14',
      'description' => '',
      'type' => 'nodereference_select',
      'module' => 'nodereference',
    ),
  );

  // Exported field: field_fserver_recommended
  $fields[] = array(
    'field_name' => 'field_fserver_recommended',
    'type_name' => 'fserver_release',
    'display_settings' => array(
      'weight' => '-9',
      'parent' => '',
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '1',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => 'return fserver_cck_options(\'recommended\');',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Recommended',
      'weight' => '-9',
      'description' => '',
      'type' => 'optionwidgets_select',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_fserver_versionextra
  $fields[] = array(
    'field_name' => 'field_fserver_versionextra',
    'type_name' => 'fserver_release',
    'display_settings' => array(
      'weight' => '-10',
      'parent' => '',
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => 5,
      'size' => '20',
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_fserver_versionextra][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Extra version',
      'weight' => '-10',
      'description' => '',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_fserver_versionmajor
  $fields[] = array(
    'field_name' => 'field_fserver_versionmajor',
    'type_name' => 'fserver_release',
    'display_settings' => array(
      'weight' => '-12',
      'parent' => '',
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '1',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => 'return fserver_cck_options(\'major\');',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Major version',
      'weight' => '-12',
      'description' => '',
      'type' => 'optionwidgets_select',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_fserver_versionpatch
  $fields[] = array(
    'field_name' => 'field_fserver_versionpatch',
    'type_name' => 'fserver_release',
    'display_settings' => array(
      'weight' => '-11',
      'parent' => '',
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '1',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => 'return fserver_cck_options(\'patch\');',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Patch version',
      'weight' => '-11',
      'description' => '',
      'type' => 'optionwidgets_select',
      'module' => 'optionwidgets',
    ),
  );

  // Translatables
  array(
    t('Core compatibility'),
    t('Extra version'),
    t('Machine name'),
    t('Major version'),
    t('Package'),
    t('Patch version'),
    t('Project'),
    t('Recommended'),
  );

  return $fields;
}

/**
 * Helper to implemetation of hook_context_default_contexts().
 */
function _fserver_context_default_contexts() {
  $items = array();

  $items[] = array(
    'namespace' => 'fserver',
    'attribute' => 'section',
    'value' => 'project',
    'description' => '',
    'node' => array(
      '0' => 'fserver_project',
    ),
    'block' => array(
      'views_fserver_releases-block_1' => array(
        'module' => 'views',
        'delta' => 'fserver_releases-block_1',
        'weight' => 20,
        'region' => 'content',
        'status' => '0',
        'label' => 'fserver_releases: Block',
        'type' => 'context_ui',
      ),
    ),
  );
  return $items;
}

/**
 * Helper to implemetation of hook_menu_default_items().
 */
function _fserver_menu_default_items() {
  $items = array();

  $items[] = array(
    'title' => 'Projects',
    'path' => 'fserver',
    'weight' => '0',
  );
  // Translatables
  array(
    t('Projects'),
  );


  return $items;
}

/**
 * Helper to implemetation of hook_node_info().
 */
function _fserver_node_info() {
  $items = array(
    'fserver_project' => array(
      'name' => t('Project'),
      'module' => 'node',
      'description' => t('A feature project page. Provides a summary of project information and releases for download.'),
      'has_title' => '1',
      'title_label' => t('Project'),
      'has_body' => '1',
      'body_label' => t('Description'),
    ),
    'fserver_release' => array(
      'name' => t('Release'),
      'module' => 'node',
      'description' => t('A single release package for a feature.'),
      'has_title' => '1',
      'title_label' => t('Release'),
      'has_body' => '1',
      'body_label' => t('Notes'),
    ),
  );
  return $items;
}

/**
 * Helper to implemetation of hook_views_default_views().
 */
function _fserver_views_default_views() {
  $views = array();

  // Exported view: fserver_projects
  $view = new view;
  $view->name = 'fserver_projects';
  $view->description = 'Feature Server > Projects';
  $view->tag = 'fserver';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('fields', array(
    'title' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'link_to_node' => 1,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
    ),
    'teaser' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 1,
        'max_length' => '100',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 1,
        'html' => 0,
      ),
      'exclude' => 0,
      'id' => 'teaser',
      'table' => 'node_revisions',
      'field' => 'teaser',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('sorts', array(
    'title' => array(
      'order' => 'ASC',
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('filters', array(
    'status' => array(
      'operator' => '=',
      'value' => '1',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'relationship' => 'none',
    ),
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'fserver_project' => 'fserver_project',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'none',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('title', 'Projects');
  $handler->override_option('empty', 'There are currently no projects available.');
  $handler->override_option('items_per_page', 20);
  $handler->override_option('use_pager', '1');
  $handler->override_option('style_plugin', 'grid');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'columns' => '2',
    'alignment' => 'vertical',
  ));
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->override_option('path', 'fserver');
  $handler->override_option('menu', array(
    'type' => 'normal',
    'title' => 'Projects',
    'description' => '',
    'weight' => '0',
    'name' => 'features',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
  ));

  $views[$view->name] = $view;

  // Exported view: fserver_releases
  $view = new view;
  $view->name = 'fserver_releases';
  $view->description = 'Feature Server > Releases';
  $view->tag = 'fserver';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('relationships', array(
    'field_fserver_file_fid' => array(
      'label' => 'Package',
      'required' => 1,
      'delta' => -1,
      'id' => 'field_fserver_file_fid',
      'table' => 'node_data_field_fserver_file',
      'field' => 'field_fserver_file_fid',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('fields', array(
    'field_fserver_api_value' => array(
      'label' => 'Core compatibility',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'link_to_node' => 0,
      'label_type' => 'widget',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 1,
      'id' => 'field_fserver_api_value',
      'table' => 'node_data_field_fserver_api',
      'field' => 'field_fserver_api_value',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'field_fserver_versionmajor_value' => array(
      'label' => 'Major version',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'link_to_node' => 0,
      'label_type' => 'widget',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 1,
      'id' => 'field_fserver_versionmajor_value',
      'table' => 'node_data_field_fserver_versionmajor',
      'field' => 'field_fserver_versionmajor_value',
      'relationship' => 'none',
    ),
    'field_fserver_versionpatch_value' => array(
      'label' => 'Patch version',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'link_to_node' => 0,
      'label_type' => 'widget',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 1,
      'id' => 'field_fserver_versionpatch_value',
      'table' => 'node_data_field_fserver_versionpatch',
      'field' => 'field_fserver_versionpatch_value',
      'relationship' => 'none',
    ),
    'field_fserver_versionextra_value' => array(
      'label' => 'Extra version',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'link_to_node' => 0,
      'label_type' => 'widget',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 1,
      'id' => 'field_fserver_versionextra_value',
      'table' => 'node_data_field_fserver_versionextra',
      'field' => 'field_fserver_versionextra_value',
      'relationship' => 'none',
    ),
    'view_node' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'text' => 'Notes',
      'exclude' => 1,
      'id' => 'view_node',
      'table' => 'node',
      'field' => 'view_node',
      'relationship' => 'none',
    ),
    'nothing' => array(
      'label' => 'Release',
      'alter' => array(
        'text' => '[field_fserver_api_value]-[field_fserver_versionmajor_value]-[field_fserver_versionpatch_value] [field_fserver_versionextra_value] ([view_node])',
        'make_link' => 1,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'exclude' => 0,
      'id' => 'nothing',
      'table' => 'views',
      'field' => 'nothing',
      'relationship' => 'none',
    ),
    'filesize' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'file_size_display' => 'formatted',
      'exclude' => 1,
      'id' => 'filesize',
      'table' => 'files',
      'field' => 'filesize',
      'relationship' => 'field_fserver_file_fid',
    ),
    'field_fserver_file_fid' => array(
      'label' => 'Package',
      'alter' => array(
        'alter_text' => 1,
        'text' => '<a href=\'[field_fserver_file_fid]\'>Download</a> ([filesize])',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'link_to_node' => 0,
      'label_type' => 'widget',
      'format' => 'url_plain',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_fserver_file_fid',
      'table' => 'node_data_field_fserver_file',
      'field' => 'field_fserver_file_fid',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'changed' => array(
      'label' => 'Date',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'date_format' => 'custom',
      'custom_date_format' => 'M j Y',
      'exclude' => 0,
      'id' => 'changed',
      'table' => 'node',
      'field' => 'changed',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('sorts', array(
    'field_fserver_api_value' => array(
      'order' => 'DESC',
      'delta' => -1,
      'id' => 'field_fserver_api_value',
      'table' => 'node_data_field_fserver_api',
      'field' => 'field_fserver_api_value',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'field_fserver_versionmajor_value' => array(
      'order' => 'DESC',
      'delta' => -1,
      'id' => 'field_fserver_versionmajor_value',
      'table' => 'node_data_field_fserver_versionmajor',
      'field' => 'field_fserver_versionmajor_value',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'field_fserver_versionpatch_value' => array(
      'order' => 'DESC',
      'delta' => -1,
      'id' => 'field_fserver_versionpatch_value',
      'table' => 'node_data_field_fserver_versionpatch',
      'field' => 'field_fserver_versionpatch_value',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'field_fserver_versionextra_value' => array(
      'order' => 'DESC',
      'delta' => -1,
      'id' => 'field_fserver_versionextra_value',
      'table' => 'node_data_field_fserver_versionextra',
      'field' => 'field_fserver_versionextra_value',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('arguments', array(
    'field_fserver_project_nid' => array(
      'default_action' => 'default',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => '',
      'breadcrumb' => '',
      'default_argument_type' => 'node',
      'default_argument' => '',
      'validate_type' => 'none',
      'validate_fail' => 'not found',
      'break_phrase' => 0,
      'not' => 0,
      'id' => 'field_fserver_project_nid',
      'table' => 'node_data_field_fserver_project',
      'field' => 'field_fserver_project_nid',
      'validate_user_argument_type' => 'uid',
      'validate_user_roles' => array(
        '2' => 0,
      ),
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_argument_user' => 0,
      'default_argument_fixed' => '',
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'fserver_project' => 0,
        'fserver_release' => 0,
        'image' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_argument_vocabulary' => array(),
      'validate_argument_type' => 'tid',
      'validate_argument_transform' => 0,
      'validate_user_restrict_roles' => 0,
      'validate_argument_php' => '',
      'override' => array(
        'button' => 'Override',
      ),
    ),
  ));
  $handler->override_option('filters', array(
    'status' => array(
      'operator' => '=',
      'value' => '1',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'relationship' => 'none',
    ),
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'fserver_release' => 'fserver_release',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'none',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('empty', 'There are no releases available for this project.');
  $handler->override_option('empty_format', '1');
  $handler->override_option('items_per_page', 25);
  $handler->override_option('use_pager', '1');
  $handler->override_option('style_plugin', 'table');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'asc',
    'columns' => array(
      'filesize' => 'field_fserver_file_fid',
      'title' => 'title',
      'nid' => 'nid',
      'field_fserver_file_fid' => 'field_fserver_file_fid',
      'changed' => 'changed',
    ),
    'info' => array(
      'filesize' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'title' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'nid' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'field_fserver_file_fid' => array(
        'separator' => '',
      ),
      'changed' => array(
        'sortable' => 0,
        'separator' => '',
      ),
    ),
    'default' => '-1',
  ));
  $handler = $view->new_display('block', 'Recommended releases', 'block_1');
  $handler->override_option('filters', array(
    'status' => array(
      'operator' => '=',
      'value' => '1',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'relationship' => 'none',
    ),
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'fserver_release' => 'fserver_release',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'relationship' => 'none',
    ),
    'field_fserver_recommended_value_many_to_one' => array(
      'operator' => 'or',
      'value' => array(
        '1' => '1',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'field_fserver_recommended_value_many_to_one',
      'table' => 'node_data_field_fserver_recommended',
      'field' => 'field_fserver_recommended_value_many_to_one',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
      'reduce_duplicates' => 0,
    ),
  ));
  $handler->override_option('title', 'Recommended releases');
  $handler->override_option('block_description', '');
  $handler->override_option('block_caching', -1);
  $handler = $view->new_display('page', 'All releases', 'page_1');
  $handler->override_option('arguments', array(
    'field_fserver_project_nid' => array(
      'default_action' => 'default',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => '%1',
      'breadcrumb' => '',
      'default_argument_type' => 'node',
      'default_argument' => '',
      'validate_type' => 'node',
      'validate_fail' => 'not found',
      'break_phrase' => 0,
      'not' => 0,
      'id' => 'field_fserver_project_nid',
      'table' => 'node_data_field_fserver_project',
      'field' => 'field_fserver_project_nid',
      'validate_user_argument_type' => 'uid',
      'validate_user_roles' => array(
        '2' => 0,
      ),
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_argument_user' => 0,
      'default_argument_fixed' => '',
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'fserver_project' => 'fserver_project',
        'fserver_release' => 0,
        'image' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_argument_vocabulary' => array(),
      'validate_argument_type' => 'tid',
      'validate_argument_transform' => 0,
      'validate_user_restrict_roles' => 0,
      'validate_argument_php' => '',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
  ));
  $handler->override_option('path', 'node/%/releases');
  $handler->override_option('menu', array(
    'type' => 'tab',
    'title' => 'All releases',
    'description' => '',
    'weight' => '0',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
  ));

  $views[$view->name] = $view;

  // Exported view: fserver_updates
  $view = new view;
  $view->name = 'fserver_updates';
  $view->description = 'Feature Server > Update feed';
  $view->tag = 'fserver';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('relationships', array(
    'field_fserver_project_nid' => array(
      'label' => 'Project',
      'required' => 1,
      'delta' => -1,
      'id' => 'field_fserver_project_nid',
      'table' => 'node_data_field_fserver_project',
      'field' => 'field_fserver_project_nid',
      'relationship' => 'none',
    ),
    'field_fserver_file_fid' => array(
      'label' => 'Package',
      'required' => 1,
      'delta' => -1,
      'id' => 'field_fserver_file_fid',
      'table' => 'node_data_field_fserver_file',
      'field' => 'field_fserver_file_fid',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('fields', array(
    'field_fserver_api_value' => array(
      'label' => 'API version',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'link_to_node' => 0,
      'label_type' => 'custom',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_fserver_api_value',
      'table' => 'node_data_field_fserver_api',
      'field' => 'field_fserver_api_value',
      'relationship' => 'none',
    ),
    'field_fserver_versionextra_value' => array(
      'label' => 'Extra version',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'link_to_node' => 0,
      'label_type' => 'widget',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_fserver_versionextra_value',
      'table' => 'node_data_field_fserver_versionextra',
      'field' => 'field_fserver_versionextra_value',
      'relationship' => 'none',
    ),
    'field_fserver_versionmajor_value' => array(
      'label' => 'Major version',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'link_to_node' => 0,
      'label_type' => 'widget',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_fserver_versionmajor_value',
      'table' => 'node_data_field_fserver_versionmajor',
      'field' => 'field_fserver_versionmajor_value',
      'relationship' => 'none',
    ),
    'field_fserver_versionpatch_value' => array(
      'label' => 'Patch version',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'link_to_node' => 0,
      'label_type' => 'widget',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_fserver_versionpatch_value',
      'table' => 'node_data_field_fserver_versionpatch',
      'field' => 'field_fserver_versionpatch_value',
      'relationship' => 'none',
    ),
    'changed' => array(
      'label' => 'Updated date',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'date_format' => 'custom',
      'custom_date_format' => 'U',
      'exclude' => 0,
      'id' => 'changed',
      'table' => 'node',
      'field' => 'changed',
      'relationship' => 'none',
    ),
    'title' => array(
      'label' => 'Project title',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'link_to_node' => 0,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'field_fserver_project_nid',
    ),
    'field_fserver_name_value' => array(
      'label' => 'Project name',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'link_to_node' => 0,
      'label_type' => 'widget',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_fserver_name_value',
      'table' => 'node_data_field_fserver_name',
      'field' => 'field_fserver_name_value',
      'relationship' => 'field_fserver_project_nid',
    ),
    'nid' => array(
      'label' => 'Project URL',
      'alter' => array(
        'alter_text' => 1,
        'text' => 'node/[nid]',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'link_to_node' => 0,
      'exclude' => 0,
      'id' => 'nid',
      'table' => 'node',
      'field' => 'nid',
      'relationship' => 'field_fserver_project_nid',
    ),
    'filepath' => array(
      'label' => 'File path',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'link_to_file' => 0,
      'exclude' => 0,
      'id' => 'filepath',
      'table' => 'files',
      'field' => 'filepath',
      'relationship' => 'field_fserver_file_fid',
    ),
    'filesize' => array(
      'label' => 'Filesize',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'file_size_display' => 'bytes',
      'exclude' => 0,
      'id' => 'filesize',
      'table' => 'files',
      'field' => 'filesize',
      'relationship' => 'field_fserver_file_fid',
    ),
    'nid_1' => array(
      'label' => 'Release URL',
      'alter' => array(
        'alter_text' => 1,
        'text' => 'node/[nid_1]',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'link_to_node' => 0,
      'exclude' => 0,
      'id' => 'nid_1',
      'table' => 'node',
      'field' => 'nid',
      'relationship' => 'none',
    ),
    'mdhash' => array(
      'label' => 'MD5 hash',
      'alter' => array(
        'alter_text' => FALSE,
        'text' => '',
        'make_link' => FALSE,
        'path' => '',
        'alt' => '',
        'link_class' => '',
        'prefix' => '',
        'suffix' => '',
        'trim' => FALSE,
        'max_length' => '',
        'word_boundary' => TRUE,
        'ellipsis' => TRUE,
        'strip_tags' => FALSE,
        'html' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'mdhash',
      'table' => 'files',
      'field' => 'mdhash',
      'relationship' => 'field_fserver_file_fid',
    ),
  ));
  $handler->override_option('arguments', array(
    'field_fserver_name_value' => array(
      'default_action' => 'not found',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => '',
      'breadcrumb' => '',
      'default_argument_type' => 'fixed',
      'default_argument' => '',
      'validate_type' => 'none',
      'validate_fail' => 'not found',
      'glossary' => 0,
      'limit' => '0',
      'case' => 'none',
      'path_case' => 'none',
      'transform_dash' => 0,
      'id' => 'field_fserver_name_value',
      'table' => 'node_data_field_fserver_name',
      'field' => 'field_fserver_name_value',
      'validate_user_argument_type' => 'uid',
      'validate_user_roles' => array(
        '2' => 0,
      ),
      'relationship' => 'field_fserver_project_nid',
      'default_options_div_prefix' => '',
      'default_argument_user' => 0,
      'default_argument_fixed' => '',
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'fserver_project' => 0,
        'fserver_release' => 0,
        'image' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_argument_vocabulary' => array(),
      'validate_argument_type' => 'tid',
      'validate_argument_transform' => 0,
      'validate_user_restrict_roles' => 0,
      'validate_argument_php' => '',
    ),
    'field_fserver_api_value' => array(
      'default_action' => 'not found',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => '',
      'breadcrumb' => '',
      'default_argument_type' => 'fixed',
      'default_argument' => '',
      'validate_type' => 'none',
      'validate_fail' => 'not found',
      'add_table' => 0,
      'require_value' => 0,
      'reduce_duplicates' => 0,
      'id' => 'field_fserver_api_value',
      'table' => 'node_data_field_fserver_api',
      'field' => 'field_fserver_api_value',
      'validate_user_argument_type' => 'uid',
      'validate_user_roles' => array(
        '2' => 0,
      ),
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_argument_user' => 0,
      'default_argument_fixed' => '',
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'fserver_project' => 0,
        'fserver_release' => 0,
        'image' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_argument_vocabulary' => array(),
      'validate_argument_type' => 'tid',
      'validate_argument_transform' => 0,
      'validate_user_restrict_roles' => 0,
      'validate_argument_php' => '',
    ),
  ));
  $handler->override_option('filters', array(
    'field_fserver_recommended_value_many_to_one' => array(
      'operator' => 'or',
      'value' => array(
        '1' => '1',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'field_fserver_recommended_value_many_to_one',
      'table' => 'node_data_field_fserver_recommended',
      'field' => 'field_fserver_recommended_value_many_to_one',
      'relationship' => 'none',
      'reduce_duplicates' => 0,
    ),
    'status' => array(
      'operator' => '=',
      'value' => '1',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'relationship' => 'none',
    ),
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'fserver_release' => 'fserver_release',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'none',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('items_per_page', 0);
  $handler->override_option('style_options', array(
    'grouping' => '',
  ));
  $handler = $view->new_display('feed', 'Update XML feed', 'feed_1');
  $handler->override_option('style_plugin', 'updatexml');
  $handler->override_option('style_options', array(
    'mission_description' => FALSE,
    'description' => '',
    'project' => array(
      'title' => 'title',
      'short_name' => 'field_fserver_name_value',
      'api_version' => 'field_fserver_api_value',
      'link' => 'nid',
    ),
    'release' => array(
      'version_major' => 'field_fserver_versionmajor_value',
      'version_patch' => 'field_fserver_versionpatch_value',
      'version_extra' => 'field_fserver_versionextra_value',
      'release_link' => 'nid_1',
      'download_link' => 'filepath',
      'date' => 'changed',
      'mdhash' => 'mdhash',
      'filesize' => 'filesize',
    ),
  ));
  $handler->override_option('row_plugin', '');
  $handler->override_option('path', 'fserver/%/%');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
  ));
  $handler->override_option('displays', array());
  $handler->override_option('sitename_title', FALSE);

  $views[$view->name] = $view;

  return $views;
}
