<?php

/**
 * @file
 * persistent.inc
 *
 * This file contains persistent data handling functions.
 */

/**
 * Writes persistent data.
 *
 * @param string $entity_type
 *   The entity type.
 * @param int    $version
 *   The version to retrieve.
 * @param string $hook
 *   The hook name.
 * @param mixed  $data
 *   The data to write.
 * @param string $module
 *   The module to retrieve.
 */
function persistent_write($entity_type, $version, $hook, $data, $module = NULL) {
  $filename = entity_toolbox_version_filename($entity_type, $version, $hook, $module);
  $encoded  = drupal_json_encode($data);
  if (!file_exists($filename)) {
    touch($filename);
  }
  if (file_exists($filename)) {
    $file  = fopen($filename, 'w');
    $write = fwrite($file, $encoded);
    if (!$write) {
      //@todo handle errors
    }
    fclose($file);
  }
}

/**
 * Writes persistent data into a file.
 *
 * @param string $target
 *   The target filename.
 * @param mixed  $data
 *   The data to write.
 * @param bool   $encode
 *   Whether to encode the data.
 *
 * @return bool
 *   Returns  TRUE on success, FALSE on error.
 */
function _persistent_write($target, $data, $encode = TRUE) {
  if (is_writable($target)) {
    if (!file_exists($target)) {
      touch($target);
    }
    $data_ = $encode ? drupal_json_decode($data) : $data;
    $file  = fopen($target, 'w');
    $write = fwrite($file, $data_);
    if (!$write) {
      //@todo handle errors
      return FALSE;
    }
    fclose($file);
  }

  return FALSE;
}

/**
 * Reads persistent data.
 *
 * @param string $filename
 *   The persistent filename.
 *
 * @return array|false
 */
function _persistent_read($filename) {
  if (file_exists($filename)) {
    $file       = fopen($filename, 'r');
    $persistent = fread($file, filesize($filename));
    fclose($file);

    return drupal_json_decode($persistent);
  }
  else {
    return FALSE;
  }
}

/**
 * Writes raw persistent data.
 *
 * @param string $entity_type
 *   The entity type.
 * @param int    $version
 *   The version to retrieve.
 * @param string $hook
 *   The hook name.
 * @param mixed  $data
 *   The data to write.
 * @param string $module
 *   The module to retrieve.
 */
function raw_persistent_write($entity_type, $version, $hook, $data, $module = NULL) {
  $raw_hook = concat('raw', $hook);
  persistent_write($entity_type, $version, $raw_hook, $data, $module);
}

/**
 * Reads persistent data.
 *
 * @param string      $entity_type
 *   The entity type.
 * @param int         $version
 *   The entity version.
 * @param string      $hook
 *   The hook name.
 * @param null|string $module
 *   The module name.
 *
 * @return array|false
 */
function persistent_read($entity_type, $version, $hook, $module = NULL) {
  $filename = entity_toolbox_version_filename($entity_type, $version, $hook, $module);
  if (file_exists($filename)) {
    $file       = fopen($filename, 'r');
    $persistent = fread($file, filesize($filename));
    fclose($file);

    return drupal_json_decode($persistent);
  }
  else {
    return FALSE;
  }
}

/**
 * Reads raw persistent data.
 *
 * @param string      $entity_type
 *   The entity type.
 * @param int         $version
 *   The entity version.
 * @param string      $hook
 *   The hook name.
 * @param null|string $module
 *   The module name.
 *
 * @return array|false
 */
function raw_persistent_read($entity_type, $version, $hook, $module = NULL) {
  $raw_hook = concat('raw', $hook);
  persistent_read($entity_type, $version, $raw_hook, $module);
}

/**
 * Returns the module version dirs.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return false|array
 */
function module_versions_dirs($entity_type) {
  $version_dirs = module_versions_dir_path(entity_get_module_info($entity_type));
  if (file_exists($version_dirs)) {
    $dirs = scandir($version_dirs);
    $dirs = array_filter_by_regexp($dirs, RGX__DRUPAL_VERSION);
    sort($dirs);

    return $dirs;
  }

  return FALSE;
}

/**
 * Writes permanent entity_toolbox data to a .json file.
 *
 * @param string     $entity_type
 *   The entity type.
 * @param string|int $version
 *   The data version.
 * @param array      $data
 *   The data to write as permanent.
 *
 * @return bool
 */
function entity_toolbox_persistent_write($entity_type, $version, $data, $module = NULL) {
  persistent_write($entity_type, $version, 'entity_toolbox', $data, $module);
}

/**
 * Reads permanent entity_toolbox data from a .json file.
 *
 * @param string     $entity_type
 *   The entity type.
 * @param string|int $version
 *   The data version.
 *
 * @return array|false
 */
function entity_toolbox_persistent_read($entity_type, $version, $module = NULL) {
  return persistent_read($entity_type, $version, 'entity_toolbox', $module);
}

/**
 * Writes permanent raw entity_toolbox data to a .json file.
 *
 * @param string     $entity_type
 *   The entity type.
 * @param string|int $version
 *   The data version.
 * @param array      $data
 *   The data to write as permanent.
 *
 * @return string
 */
function raw_entity_toolbox_persistent_write($entity_type, $version, $data, $module) {
  if (!raw_entity_toolbox_persistent_read($entity_type, $version, $module)) {
    persistent_write($entity_type, $version, 'raw_entity_toolbox', $data, $module);
  }
}

/**
 * Reads permanent raw entity_toolbox data from a .json file.
 *
 * @param string     $entity_type
 *   The entity type.
 * @param string|int $version
 *   The data version.
 * @param string     $module
 *   The module managing the entity type.
 *
 * @return array|false
 */
function raw_entity_toolbox_persistent_read($entity_type, $version, $module = NULL) {
  $module = isset($module) ? $module : entity_get_module_info_safe($entity_type);

  return persistent_read($entity_type, $version, 'raw_entity_toolbox', $module);
}

/**
 * Writes permanent schema data to a .json file.
 *
 * @param string     $entity_type
 *   The entity type.
 * @param string|int $version
 *   The data version.
 * @param array      $data
 *   The data to write.
 *
 * @return bool
 */
function schema_persistent_write($entity_type, $version, $data, $module = NULL) {
  persistent_write($entity_type, $version, 'schema', $data, $module);
}

/**
 * Reads permanent schema data to a .json file.
 *
 * @param string     $entity_type
 *   The entity type.
 * @param string|int $version
 *   The data version.
 *
 * @return array
 */
function schema_persistent_read($entity_type, $version, $module = NULL) {
  return persistent_read($entity_type, $version, 'schema', $module);
}

/**
 * Writes a persistent diff between two versions of the same entity.
 *
 * @param string      $entity_type
 *   The entity type.
 * @param array       $diff
 *   The diff.
 * @param int         $v1
 *   The older version.
 * @param int         $v2
 *   The newest version.
 * @param null|string $module
 *   The module managing the entity type.
 */
function etbx_info_diff_persistent_write($entity_type, $diff, $v1, $v2, $module = NULL) {
  $filename = etbx_info_diff_filename($entity_type, $v1, $v2, $module);
  _persistent_write($filename, $diff);
}

/**
 * Reads a persistent diff between two versions of the same entity.
 *
 * @param string      $entity_type
 *   The entity type.
 * @param int         $v1
 *   The older version.
 * @param int         $v2
 *   The newest version.
 * @param null|string $module
 *   The module managing the entity type.
 *
 * @return array
 */
function etbx_info_diff_persistent_read($entity_type, $v1, $v2, $module = NULL) {
  $filename = etbx_info_diff_filename($entity_type, $v1, $v2, $module);

  return _persistent_read($filename);
}

/**
 * Prepares a module before writing/reading persistent data.
 *
 * @param string $module
 *   The module name.
 *
 * @return bool
 *   TRUE if success, FALSE otherwise.
 */
function _etbx_persistent_prepare($module) {
  // Checks if the version dir exists
  $version_dirnames = module_versions_dir_path($module);
  // If not, creates the version dir
  if (!file_exists($version_dirnames)) {
    mkdir($version_dirnames);
  }
  // Checks if the udpates dir exists
  $updates_dirname = module_updates_dir_path($module);
  if (!file_exists($updates_dirname)) {
    mkdir($updates_dirname);
  }
  // Checks if the init version dir exists
  $version_dirs = module_get_versions_dirs($module);
  if (!in_array(INIT_VERSION, $version_dirs)) {
    return etbx_version_mkdir($module, INIT_VERSION);
  }
  else {
    return TRUE;
  }
}