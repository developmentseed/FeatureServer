<?php
// $Id$

/**
@TODO:
(10:38:30 AM) Adrian Rossouw: if you need drush to be able to modify the files dir
(10:38:47 AM) Adrian Rossouw: you need to add : umask(0002) to your settings.php
(10:38:53 AM) Adrian Rossouw: drupal 6.x has a crazy bug in it
(10:39:10 AM) Adrian Rossouw: that all uploaded files are 600 , owned by the web server user
(10:39:15 AM) Adrian Rossouw: so your drush script can't modify it
(10:39:20 AM) Adrian Rossouw: or change the perms, or anythin
*/

/**
 * Implementation of hook_drush_command().
 *
 * @See drush_parse_command() for a list of recognized keys.
 *
 * @return
 *   An associative array describing your command(s).
 */
function fserver_drush_command() {
  $items = array();
  $items['fserver-status'] = array(
    'callback' => 'fserver_drush_status',
    'description' => 'Determine the packaging status of a project.',
  );
  $items['fserver-package'] = array(
    'callback' => 'fserver_drush_package',
    'description' => 'Update packaging for a project.',
  );
  $items['fserver-distro'] = array(
    'callback' => 'fserver_drush_distro',
    'description' => 'Update packaging for a distribution.',
  );
  return $items;
}

/**
 * Implementation of hook_drush_help().
 */
function fserver_drush_help($section) {
  switch ($section) {
    case 'drush:fserver-status':
      return dt("Determine the packaging status of a project.");
    case 'drush:fserver-package':
      return dt("Update packaging for a project.");
    case 'drush:fserver-distro':
      return dt("Package a new Drupal distribution from a distribution node.");
  }
}

/**
 * Package new releases for a specified project or all.
 */
function fserver_drush_package() {
  if (!drush_get_option('uri') && !drush_get_option('l')) {
    drush_die('You must use the --uri option to specify the location of this site.');
  }

  $projects = _fserver_drush_get_projects();

  // Filter the project list by the argument.
  $args = func_get_args();
  $arg = array_shift($args);
  if (!empty($arg)) {
    if (isset($projects[$arg])) {
      $projects = array($arg => $projects[$arg]);
    }
    else {
      drush_die('The project '. $arg .' could not be found.');
    }
  }

  $rows = array();
  foreach ($projects as $project) {
    $new_tags = $project->get_new_tags();
    if (!empty($new_tags)) {
      foreach ($new_tags as $tag_id => $tag) {
        $release = $project->create_release($tag_id);
        $rows[] = array($project->node->title, $tag_id, $release->field_fserver_file[0]['filename']);
      }
    }
  }
  if (!empty($rows)) {
    array_unshift($rows, array(dt('Project'), dt('Release'), dt('Filename')));
    drush_print_table($rows, TRUE);
  }
  else {
    drush_print(dt('All projects are up to date. No packages were created.'));
  }
}

/**
 * Display project packaging status.
 */
function fserver_drush_status() {
  $projects = _fserver_drush_get_projects();

  // Filter the project list by the argument.
  $args = func_get_args();
  $arg = array_shift($args);
  if (!empty($arg)) {
    if (isset($projects[$arg])) {
      $projects = array($arg => $projects[$arg]);
    }
    else {
      drush_die('The project '. $arg .' could not be found.');
    }
  }

  $rows = array(array(dt('Method'), dt('Project'), dt('New tags')));
  foreach ($projects as $project) {
    $new_tags = $project->get_new_tags();
    $rows[] = array(
      $project->method,
      $project->node->title,
      !empty($new_tags) ? implode(', ',array_keys($new_tags)) : dt("Up to date"),
    );
  }
  drush_print_table($rows, TRUE);
}

/**
 * Retrieve all fserver projects from the DB.
 */
function _fserver_drush_get_projects() {
  static $projects;
  if (!isset($projects)) {
    $projects = array();
    $result = db_query("SELECT nid, title FROM {node} WHERE type = 'fserver_project' AND status = 1");
    while ($row = db_fetch_object($result)) {
      $node = node_load($row->nid);
      $project = new FserverProject($node, $node->field_fserver_name[0]['value'], $node->field_fserver_method[0]['value'], $node->field_fserver_repository[0]['value']);
      $projects[$project->name] = $project;
    }
  }
  return $projects;
}

/**
 * Project class. Contains helpful methods for detecting tags, packaging, etc.
 */
class FserverProject {
  var $node, $name, $method, $repository;

  /**
   * We will store the backend object here.
   */
  var $backend;

  /**
   * Constructor.
   */
  function __construct($node, $name, $method, $repository) {
    $this->node = $node;
    $this->name = $name;
    $this->method = $method;
    $this->repository = $repository;

    // We try to create a backend for us to user later:
    $method_class = 'FserverProject_' . $this->method;
    if (class_exists($method_class)) {
      $this->backend = new $method_class($this);
    }
  }

  /**
   * Initialize a working copy for this project.
   */
  function init_wc() {
    if (isset($this->backend)) {
      $this->backend->init_wc();
    }
  }

  /**
   * Get new tags that have no corresponding release nodes.
   */
  function get_new_tags() {
    $new_tags = array();
    $releases = $this->get_releases();
    foreach ($this->get_tags() as $tag_id => $tag) {
      if (!isset($releases[$tag_id])) {
        $new_tags[$tag_id] = $tag;
      }
    }
    return $new_tags;
  }

  /**
  * Get release nodes for this project.
  */
  function get_releases() {
    if (!isset($this->releases)) {
      $this->releases = array();
      $result = db_query("SELECT nid FROM {node} WHERE type = 'fserver_release' AND status = 1");
      while ($row = db_fetch_object($result)) {
        $node = node_load($row->nid);
        if ($node && isset($node->field_fserver_project[0]['nid']) && $node->field_fserver_project[0]['nid'] == $this->node->nid) {
          $this->releases[fserver_generate_version($node, TRUE)] = $node;
        }
      }
    }
    return $this->releases;
  }

  function get_tag($tag_id) {
    if (isset($this->backend)) {
      return $this->backend->get_tag($tag_id);
    }
  }

  /**
  * Get tags for this project.
  */
  function get_tags() {
    if (isset($this->backend)) {
      return $this->backend->get_tags();
    }
    return array();
  }

  /**
   * Create a release node for the given tag.
   */
  function create_release($tag_id) {
    $tag = $this->get_tag($tag_id);
    if ($tag && $file = $this->create_package($tag_id)) {
      $node = new stdClass();
      $node->type = 'fserver_release';
      $node->status = 1;
      $node->created = !empty($tag['timestamp']) ? $tag['timestamp'] : time();
      $node->uid = $this->node->uid;
      $node->title = "{$this->name} {$tag_id}";
      $node->body = !empty($tag['message']) ? $tag['message'] : '';

      $node->field_fserver_file = array(0 => (array) $file);
      $node->field_fserver_project = array(0 => array('nid' => $this->node->nid));
      $node->field_fserver_api = array(0 => array('value' => $tag['core']));
      $node->field_fserver_versionmajor = array(0 => array('value' => $tag['major']));
      $node->field_fserver_versionpatch = array(0 => array('value' => $tag['patch']));
      $node->field_fserver_versionextra = array(0 => array('value' => $tag['extra']));

      // @TODO
      $node->field_fserver_recommended = array(0 => array('value' => 1));
      $node->field_fserver_security = array(0 => array('value' => 0));
      node_save($node);
    }
    return $node;
  }

  /**
   * Create an archive package for the given tag.
   */
  function create_package($tag_id) {
    if (isset($this->backend)) {
      return $this->backend->create_package($tag_id);
    }
    return FALSE;
  }

  /**
   * Write packaging information for a release.
   */
  function write_package_info($tag, $exclude_mask = array('.', '..', 'CVS')) {
    if (isset($this->backend)) {
      $fserver_url = url("fserver", array('purl' => array('disabled' => TRUE), 'absolute' => TRUE));

      $packaging = array();
      $packaging[] = "; Information added by fserver";
      $packaging[] = "core = \"{$tag['core']}\"";
      $packaging[] = "datestamp = \"{$tag['timestamp']}\"";
      $packaging[] = "project = \"{$this->name}\"";
      $packaging[] = "project status url = \"{$fserver_url}\"";
      $packaging[] = "version = \"{$tag['version']}\"";
      $packaging = "\n" . implode("\n", $packaging);

      $files = file_scan_directory($this->backend->path, '.info', $exclude_mask);
      foreach ($files as $path => $file) {
        // @TODO: Parse the info file or not?
        $info_file = file_get_contents($file->filename);
        $info_file .= $packaging;
        file_put_contents($file->filename, $info_file);
      }
    }
  }
}

class FserverProject_git {

  /**
   * We store the parent FserverProject object here.
   */
  var $FserverProject;

  /**
   * Constructor.
   */
  function __construct(&$FserverProject) {
    $this->FserverProject = $FserverProject;
  }

  /**
   * Destructor.
   */
  function __destruct() {
    if (isset($this->path)) {
      drush_op('drush_shell_exec', "rm -rf {$this->path}");
    }
  }

  /**
   * Initialize a working copy for this project.
   */
  function init_wc() {
    if (!isset($this->path)) {
      $this->path = file_directory_temp() . '/fserver_git_'. $this->FserverProject->name .'_'. time();
      drush_op('drush_shell_exec', "git clone {$this->FserverProject->repository} {$this->path}");
    }
  }

  /**
  * Get tags for this project.
  */
  function get_tags() {
    if (!isset($this->tags)) {
      $this->tags = array();
      _drush_shell_exec_output_set(' '); // Clear output cache.
      drush_op('drush_shell_exec', "git ls-remote --tags {$this->FserverProject->repository} | awk '{print $2;}'");
      $lines = drush_shell_exec_output();
      while ($line = array_shift($lines)) {
        $vc = array_pop(explode('/', $line));
        $parsed = fserver_parse_tag_name($vc);
        if (!empty($parsed)) {
          $this->tags[$parsed['version']] = $vc;
        }
      }
    }
    return $this->tags;
  }

  function get_tag($tag_id) {
    $tags = $this->get_tags();
    if (isset($tags[$tag_id])) {
      $vc = $tags[$tag_id];
      $tag = fserver_parse_tag_name($vc);
      $this->init_wc();

      // Retrieve tag info
      _drush_shell_exec_output_set(' '); // Clear output cache.
      drush_op('drush_shell_exec', "git --git-dir={$this->path}/.git show {$vc}");
      $info = drush_shell_exec_output();
      if ($info[0] == "tag {$vc}") {
        $info = implode("\n", $info);
        $info = explode("\n\n", $info);
        list($basic, $commit, $message) = $info;

        $basic = explode("\n", $basic);
        array_shift($basic); // Removes tag line
        array_shift($basic); // Removes author line

        // Set timestamp on the tag
        $date = array_shift($basic);
        $date = strtotime(trim(substr($date, strpos($date, ':') + 1)));
        $tag['timestamp'] = is_numeric($date) ? $date : time();
      }
      return $tag;
    }
  }

  /**
   * Create an archive package for the given tag.
   */
  function create_package($tag_id) {
    $this->init_wc();
    $tag = $this->get_tag($tag_id);
    if ($tag) {
        $base = "{$this->FserverProject->name}-{$tag_id}";
        $file_path = file_directory_path() .'/fserver';
        // Create the directory if it doesn't exist.
        if (file_check_directory($file_path, TRUE)) {
          $vc = $tag['original'];
          drush_op('drush_shell_exec', "git --git-dir={$this->path}/.git checkout {$vc}");
          $this->FserverProject->write_package_info($tag, array('.git'));
          drush_op('drush_shell_exec', "tar -Pcf - --exclude='.git' --transform='s,{$this->path},{$this->FserverProject->name},' {$this->path} | gzip > {$file_path}/{$base}.tgz");

          // @TODO
          // We need to properly chown and permission these directories.
          // Is it possible for drush to know the web server user?
          drush_op('chmod', $file_path, 0775);
          drush_op('chgrp', $file_path, fserver_posix_groupname());
          drush_op('chmod', "{$file_path}/{$base}.tgz", 0775);
          drush_op('chgrp', "{$file_path}/{$base}.tgz", fserver_posix_groupname());

          $file = new stdClass();
          $file->uid = $this->node->uid;
          $file->filename = "{$base}.tgz";
          $file->filepath = "{$file_path}/{$base}.tgz";
          $file->filemime = file_get_mimetype($file->filename);
          $file->filesize = filesize($file->filepath);
          $file->status = FILE_STATUS_PERMANENT;
          $file->timestamp = time();
          drupal_write_record('files', $file);

          return $file;
        }
    }
    return FALSE;
  }

}

class FserverProject_svn {
  /**
   * We store the parent FserverProject object here.
   */
  var $FserverProject;

  /**
   * Constructor.
   */
  function __construct(&$FserverProject) {
    $this->FserverProject = $FserverProject;
  }

  /**
   * Destructor.
   */
  function __destruct() {
    if (isset($this->path)) {
      drush_op('drush_shell_exec', "rm -rf {$this->path}");
    }
  }

  /**
   * Initialize a working copy for this project.
   */
  function init_wc() {
    if (!isset($this->path)) {
      $this->path = file_directory_temp() . '/fserver_svn_'. $this->FserverProject->name .'_'. time();
      //drush_op('drush_shell_exec', "git clone {$this->FserverProject->repository} {$this->path}");
    }
  }

  /**
  * Get tags for this project.
  */
  function get_tags() {
    if (!isset($this->tags)) {
      $this->tags = array();
      _drush_shell_exec_output_set(' '); // Clear output cache.
      drush_op('drush_shell_exec', "svn ls {$this->FserverProject->repository}/tags | awk '{print $1;}'");
      $lines = drush_shell_exec_output();
      while ($line = array_shift($lines)) {
        $vc = array_shift(explode('/', $line));
        $parsed = fserver_parse_tag_name($vc);
        if (!empty($parsed)) {
          $this->tags[$parsed['version']] = $vc;
        }
      }
    }
    return $this->tags;
  }

  function get_tag($tag_id) {
    $tags = $this->get_tags();
    if (isset($tags[$tag_id])) {
      $vc = $tags[$tag_id];
      $tag = fserver_parse_tag_name($vc);
      $this->init_wc();

      // Retrieve tag info
      _drush_shell_exec_output_set(' '); // Clear output cache.
      drush_op('drush_shell_exec', "svn info --non-interactive --xml {$this->FserverProject->repository}/tags/{$vc}");
      $info = drush_shell_exec_output();
      if (!empty($info)) {
        $info = implode("\n", $info);
        // $info is now an xml string:
        $info_xml = simplexml_load_string($info);
        foreach ($info_xml->xpath('//commit/date') as $date_element) {
          $date = strtotime((string)$date_element);
        }
      }


      $tag['timestamp'] = is_numeric($date) ? $date : time();
      return $tag;
    }
  }

  /**
   * Create an archive package for the given tag.
   */
  function create_package($tag_id) {
    $this->init_wc();
    $tag = $this->get_tag($tag_id);
    if ($tag) {
        $base = "{$this->FserverProject->name}-{$tag_id}";
        $file_path = file_directory_path() .'/fserver';
        // Create the directory if it doesn't exist.
        if (file_check_directory($file_path, TRUE)) {
          $vc = $tag['original'];
          if (is_dir($this->path)) {
            // I'd quite like to do a switch here, but couldn't get it to work reliably.
            drush_op('drush_shell_exec', "rm -rf {$this->path}");
          }
          drush_op('drush_shell_exec', "svn checkout --non-interactive  {$this->FserverProject->repository}/tags/{$vc} {$this->path}");
          $this->FserverProject->write_package_info($tag, array('.svn'));
          drush_op('drush_shell_exec', "tar -Pcf - --exclude='.svn' --transform='s,{$this->path},{$this->FserverProject->name},' {$this->path} | gzip > {$file_path}/{$base}.tgz");

          // @TODO
          // We need to properly chown and permission these directories.
          // Is it possible for drush to know the web server user?
          drush_op('chmod', $file_path, 0775);
          drush_op('chgrp', $file_path, fserver_posix_groupname());
          drush_op('chmod', "{$file_path}/{$base}.tgz", 0775);
          drush_op('chgrp', "{$file_path}/{$base}.tgz", fserver_posix_groupname());

          $file = new stdClass();
          $file->uid = $this->node->uid;
          $file->filename = "{$base}.tgz";
          $file->filepath = "{$file_path}/{$base}.tgz";
          $file->filemime = file_get_mimetype($file->filename);
          $file->filesize = filesize($file->filepath);
          $file->status = FILE_STATUS_PERMANENT;
          $file->timestamp = time();
          drupal_write_record('files', $file);

          return $file;
        }
    }
    return FALSE;
  }
}

/**
 * Discover the web server group. Taken from provision.
 */
function fserver_posix_groupname() {
  $info = posix_getgrgid(posix_getgid());
  $common_groups = array(
    'httpd',
    'www-data',
    'apache',
    'nogroup',
    'nobody',
    $info['name']);
  foreach ($common_groups as $group) {
    $groupname = '';
    if (is_numeric($group)) {
      $info = posix_getgrgid($group);
      $groupname = $info['name'];
    }
    else {
      $info = posix_getgrnam($group);
      $groupname = $info['name'];
    }
    if ($groupname) {
      return $groupname;
      break;
    }
  }
  return NULL;
}

function fserver_drush_distro() {
  if (!drush_get_option('version')) {
    drush_die('No version supplied, please use --version to specify a version for your release.');
  }
  $distros = _fserver_drush_get_distros();

  // Filter the project list by the argument.
  $args = func_get_args();
  $arg = array_shift($args);
  $version = drush_get_option('version');
  if (!empty($arg)) {
    if (isset($distros[$arg])) {
      $distros = array($arg => $distros[$arg]);
    }
    else {
      drush_die('The distribution '. $arg .' could not be found.');
    }
  }

  $rows = array();
  foreach ($distros as $distro) {
    $release = $distro->create_release($version);
    $rows[] = array($distro->node->title, $release->field_fserver_file[0]['filename']);
  }
  if (!empty($rows)) {
    array_unshift($rows, array(dt('Project'), dt('Filename')));
    drush_print_table($rows, TRUE);
  }
  else {
    drush_print(dt('No distributions to update.'));
  }
}

function _fserver_drush_get_distros() {
  static $distros;
  if (!isset($distros)) {
    $projects = array();
    $result = db_query("SELECT nid, title FROM {node} WHERE type = 'fserver_distro' AND status = 1");
    while ($row = db_fetch_object($result)) {
      $node = node_load($row->nid);
      $distro = new FserverDistro($node, $node->field_fserver_name[0]['value']);
      $distros[$distro->name] = $distro;
    }
  }
  return $distros;
}

/**
 * Project class. Contains helpful methods for detecting tags, packaging, etc.
 */
class FserverDistro {
  var $node, $name;

  /**
   * Constructor.
   */
  function __construct($node, $name, $version = NULL) {
    $this->node = $node;
    $this->name = $name;
    //$this->version = $version;
  }

  /**
   * Destructor.
   */
  function __destruct() {
    if (isset($this->path)) {
      drush_op('drush_shell_exec', "rm -rf {$this->path}");
    }
  }

  /**
   * Initialize a working copy for this project.
   */
  function init_wc() {
    if (!isset($this->raw_version)) {
      drush_die('Version was not parsed properly. Please supply versions in the drupal-6--1-0-alpha1 format.');
    }
    if (!isset($this->path)) {
      $this->path = file_directory_temp() . '/fserver_'. $this->name .'_'. time();
      if (file_check_directory($this->path, TRUE)) {
        if(!file_save_data($this->node->field_fserver_drushmake[0]['value'], $this->path .'/'. $this->name .'-'. $this->raw_version .'.make', FILE_EXISTS_REPLACE)) {
          return FALSE;
        }
        // @TODO
        // We need to properly chown and permission these directories.
        // Is it possible for drush to know the web server user?
        drush_op('chmod', $this->path, 0775);
        drush_op('chgrp', $this->path, fserver_posix_groupname());
        drush_op('chmod', "{$this->path}/{$this->name}-{$this->raw_version}.make", 0775);
        drush_op('chgrp', "{$this->path}/{$this->name}-{$this->raw_version}.make", fserver_posix_groupname());
      }
    }
    return TRUE;
  }

  /**
  * Get release nodes for this project.
  */
  function get_releases() {
    if (!isset($this->releases)) {
      $this->releases = array();
      $result = db_query("SELECT nid FROM {node} WHERE type = 'fserver_release' AND status = 1");
      while ($row = db_fetch_object($result)) {
        $node = node_load($row->nid);
        if ($node && isset($node->field_fserver_project[0]['nid']) && $node->field_fserver_project[0]['nid'] == $this->node->nid) {
          $this->releases[fserver_generate_version($node, TRUE)] = $node;
        }
      }
    }
    return $this->releases;
  }

  function parse_version($version) {
    if (isset($version)) {
      $this->version = array();
      $parsed = fserver_parse_tag_name($version);
      if (!empty($parsed)) {
        $extra = $parsed['extra'] ? $parsed['extra'] : 0;
        $view = views_get_view('fserver_release_lookup');
        $view->set_display('default');
        $args = array();
        $args[] = $this->node->nid;
        $args[] = $parsed['core'];
        $args[] = $extra;
        $view->set_arguments($args);
        $preview = $view->preview($form_state['display_id'], $args);
        $query = db_prefix_tables($view->build_info['query']);
        _db_query_callback($view->build_info['query_args'], TRUE);
        $query = preg_replace_callback(DB_QUERY_REGEXP, '_db_query_callback', $query);
        // Next line required because views passes 0 as "IS NULL" to the query, and we actually want 0, so it's been hacked in manually
        $query .= " AND (node_data_field_fserver_project.field_fserver_versionmajor_value = %d) AND (node_data_field_fserver_api.field_fserver_versionpatch_value = %d)";
        $items = db_query($query, $parsed['major'], $parsed['patch']);
        while ($result = db_fetch_object($items)) {
          $results[] = $result->nid;
        }
        if (!$results[0]) {
          $this->version = $parsed;
          $this->raw_version = $parsed['version'];
        }
        else {
          return FALSE;
        }
      }
      else {
        return FALSE;
      }
    }
    return $this->version;
  }

  /**
   * Create a release node for the given tag.
   */
  function create_release($version = NULL) {
    $version = $this->parse_version($version);
    if ($file = $this->create_package()) {
    //if ($version) {
      $node = new stdClass();
      $node->type = 'fserver_release';
      $node->status = 1;
      $node->created = !empty($tag['timestamp']) ? $tag['timestamp'] : time();
      $node->uid = $this->node->uid;
      $node->title = "{$this->name} {$tag_id}";
      $node->body = !empty($tag['message']) ? $tag['message'] : '';

      $node->field_fserver_file = array(0 => (array) $file);
      $node->field_fserver_project = array(0 => array('nid' => $this->node->nid));
      $node->field_fserver_api = array(0 => array('value' => $version['core']));
      $node->field_fserver_versionmajor = array(0 => array('value' => $version['major']));
      $node->field_fserver_versionpatch = array(0 => array('value' => $version['patch']));
      $node->field_fserver_versionextra = array(0 => array('value' => $version['extra']));

      // @TODO
      $node->field_fserver_recommended = array(0 => array('value' => 1));
      $node->field_fserver_security = array(0 => array('value' => 0));
      node_save($node);
    }
    return $node;
  }

  /**
   * Create an archive package for the given tag.
   */
  function create_package() {
    if (!$this->init_wc()) {
      return FALSE;
    }
    $base = "{$this->name}-{$this->raw_version}";
    $file_path = file_directory_path() .'/fserver';
    // Create the directory if it doesn't exist.
    if (file_check_directory($file_path, TRUE)) {
      drush_backend_invoke('make', array("{$this->path}/{$base}.make", "{$file_path}/{$base}", "--tar"));
      drush_op('drush_shell_exec', "mv {$file_path}/{$base}.tar.gz {$file_path}/{$base}.tgz");

      // @TODO
      // We need to properly chown and permission these directories.
      // Is it possible for drush to know the web server user?
      drush_op('chmod', $file_path, 0775);
      drush_op('chgrp', $file_path, fserver_posix_groupname());
      drush_op('chmod', "{$file_path}/{$base}.tgz", 0775);
      drush_op('chgrp', "{$file_path}/{$base}.tgz", fserver_posix_groupname());

      $file = new stdClass();
      $file->uid = $this->node->uid;
      $file->filename = "{$base}.tgz";
      $file->filepath = "{$file_path}/{$base}.tgz";
      $file->filemime = file_get_mimetype($file->filename);
      $file->filesize = filesize($file->filepath);
      $file->status = FILE_STATUS_PERMANENT;
      $file->timestamp = time();
      drupal_write_record('files', $file);

      return $file;
    }
    return FALSE;
  }
}
