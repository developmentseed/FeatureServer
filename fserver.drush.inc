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
  $items['fserver status'] = array(
    'callback' => 'fserver_drush_status',
    'description' => 'Determine the packaging status of a project.',
  );
  $items['fserver package'] = array(
    'callback' => 'fserver_drush_package',
    'description' => 'Update packaging for a project.',
  );
  return $items;
}

/**
 * Implementation of hook_drush_help().
 */
function fserver_drush_help($section) {
  switch ($section) {
    case 'drush:fserver status':
      return dt("Determine the packaging status of a project.");
    case 'drush:fserver package':
      return dt("Update packaging for a project.");
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
   * Constructor.
   */
  function __construct($node, $name, $method, $repository) {
    $this->node = $node;
    $this->name = $name;
    $this->method = $method;
    $this->repository = $repository;
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
      $this->path = file_directory_temp() . '/fserver_'. $this->name .'_'. time();
      switch ($this->method) {
        case 'git':
          drush_op('drush_shell_exec', "git clone {$this->repository} {$this->path}");
          break;
      }
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
  * Get tags for this project.
  */
  function get_tags() {
    if (!isset($this->tags)) {
      $this->tags = array();
      switch ($this->method) {
        case 'git':
          _drush_shell_exec_output_set(' '); // Clear output cache.
          drush_op('drush_shell_exec', "git ls-remote --tags {$this->repository} | awk '{print $2;}'");
          $lines = drush_shell_exec_output();
          while ($line = array_shift($lines)) {
            $vc = array_pop(explode('/', $line));
            $parsed = fserver_parse_tag_name($vc);
            if (!empty($parsed)) {
              $this->tags[$parsed['version']] = $vc;
            }
          }
          break;
      }
    }
    return $this->tags;
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
    $this->init_wc();
    $tag = $this->get_tag($tag_id);
    if ($tag) {
      switch ($this->method) {
        case 'git':
          $base = "{$this->name}-{$tag_id}";
          $file_path = file_directory_path() .'/fserver';
          // Create the directory if it doesn't exist.
          if (file_check_directory($file_path, TRUE)) {
            drush_op('drush_shell_exec', "git --git-dir={$this->path}/.git checkout {$vc}");
            $this->write_package_info($tag);
            drush_op('drush_shell_exec', "tar -Pcf - --exclude='.git' --transform='s,{$this->path},{$this->name},' {$this->path} | gzip > {$file_path}/{$base}.tgz");

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
    }
    return FALSE;
  }

  /**
   * Write packaging information for a release.
   */
  function write_package_info($tag) {
    $fserver_url = url("fserver", array('purl' => array('disabled' => TRUE), 'absolute' => TRUE));

    $packaging = array();
    $packaging[] = "; Information added by fserver";
    $packaging[] = "core = \"{$tag['core']}\"";
    $packaging[] = "datestamp = \"{$tag['timestamp']}\"";
    $packaging[] = "project = \"{$this->name}\"";
    $packaging[] = "project status url = \"{$fserver_url}\"";
    $packaging[] = "version = \"{$tag['version']}\"";
    $packaging = "\n" . implode("\n", $packaging);

    $files = file_scan_directory($this->path, '.info', array('.git'));
    foreach ($files as $path => $file) {
      // @TODO: Parse the info file or not?
      $info_file = file_get_contents($file->filename);
      $info_file .= $packaging;
      file_put_contents($file->filename, $info_file);
    }
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
