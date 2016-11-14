<?php

/**
 * @file
 * versioning.inc
 *
 * This file contains entity versioning related functions.
 */

/**
 * Defines the status code for an entity type version that was not found by etbx.
 */
define('ENTITY_STATUS_VERSION_ERROR', 0x0010);
/**
 * Defines the status code for an entity type version that was found and installed.
 */
define('ENTITY_STATUS_VERSION_INSTALLED', 0x0011);
/**
 * Defines the status code for an entity type version that was found but not installed yet.
 */
define('ENTITY_STATUS_VERSION_REGISTERED', 0x0012);
/**
 * Defines a regex to catch a module/entity version.
 */
define('RGX__DRUPAL_VERSION', '/7\d{3}/');
/**
 * Defines the init version.
 */
define('INIT_VERSION', 7000);

/**
 * Returns the module versions dir path.
 *
 * @param string $module
 *   The module.
 *
 * @return string
 */
function module_versions_dir_path($module) {
  $module_path    = module_get_path($module);
  $persistent_dir = paths_join($module_path, array('src', 'versions'));

  return $persistent_dir;
}

/**
 * Returns the version directories within a module.
 *
 * @param string $module
 *   The module's name.
 *
 * @return array|false
 *   Returns an array of directories, or FALSE on error.
 */
function module_get_versions_dirs($module) {
  $version_dirs = module_versions_dir_path($module);
  if (file_exists($version_dirs)) {
    $dirs = scandir($version_dirs);
    $dirs = array_filter_by_regexp($dirs, RGX__DRUPAL_VERSION);
    sort($dirs);

    return $dirs;
  }

  return FALSE;
}

/**
 * Creates a new version directory within a module.
 *
 * @param string $module
 *   The module's name.
 * @param int    $version
 *   The version for which to create the dir.
 *
 * @return bool
 *   Return TRUE if success or if dir already exists, FALSE on error.
 */
function etbx_version_mkdir($module, $version) {
  if (!etbx_module_check_rights($module)) {
    goto no_access;
  }
  $tail = module_versions_dir_path($module);
  $path = paths_join($tail, array($version));
  if (!file_exists($path)) {
    $success = mkdir($path);

    return $success;
  }
  else {
    return TRUE;
  }
  no_access:

  return FALSE;
}

/**
 * Retrieves the filename for a specific persistent file type.
 *
 * @param string $entity_type
 *   The entity type.
 * @param int    $version
 *   The version to retrieve.
 * @param string $hook
 *   The hook name.
 * @param string $module
 *   The module to retrieve.
 *
 * @return string
 */
function entity_toolbox_version_filename($entity_type, $version, $hook, $module = NULL) {
  $filename = concat($entity_type, $hook, '.');
  $head     = module_versions_dir_path(isset($module) ? $module : entity_get_module_info($entity_type));
  $dir      = paths_join($head, array($version));

  return file_path($filename, $dir, array(), 'json');
}

/**
 * Returns the entity current version.
 *
 * This function can only be called once the registry has been built.
 *
 * @param string $entity_type
 *   The entity type to query.
 *
 * @return int
 */
function etbx_entity_current_version($entity_type) {
  $registry = etbx_registry(ETBX_REGISTRY_GET, $entity_type);
  if (!empty($registry['version'])) {
    return $registry['version'];
  }
  else {
    return 0;
  }
}

/**
 * Returns the entity versions registered by entity toolbox, both installed and uninstalled, or unregistered.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $module
 *   The module managing the entity.
 *
 * @return array
 *   An array of the registered versions, or an empty array if no version was found.
 *
 */
function entity_type_get_versions($entity_type, $module) {
  $registered   = entity_registered_versions($entity_type, $module);
  $unregistered = entity_unregistered_versions($entity_type, $module);

  return $registered + $unregistered;
}

/**
 * Returns the versions of an entity by scanning its versioning dir.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $module
 *   The module managing the entity.
 *
 * @return array
 */
function entity_type_scan_versions($entity_type, $module) {
  $version_dirs      = module_get_versions_dirs($module);
  $raw_info_filename = concat($entity_type, array(
    'raw_entity_toolbox',
    'json'
  ), '.');
  // Checks if entity_type is actually present in each dir.
  foreach ($version_dirs as $key => $version_dir) {
    // Scans for persistent files.
    $v_dir = paths_join(module_versions_dir_path($module), array($version_dir));
    $scan  = scandir($v_dir);
    if ($scan) {
      $scan_flip = array_flip($scan);
      // Removes the version dirs that do not apply to the current entity type.
      if (empty($scan_flip[$raw_info_filename])) {
        unset($version_dirs[$key]);
      }
    }
    else {
      unset($version_dirs[$key]);
    }
  }
//  $regexp           = '/(?P<version>7\d{3})$/';
//  $scanned_versions = array();
//  foreach ($version_dirs as $version_dir) {
//    preg_match($regexp, $version_dir, $matches);
//    if (!empty($matches['version'])) {
//      $scanned_versions[] = $matches['version'];
//    }
//  }

  return $version_dirs;
}

/**
 * Retrieves and returns the unregistered versions for an entity type.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $module
 *   The module managing the entity type.
 *
 * @return array
 */
function entity_unregistered_versions($entity_type, $module = NULL) {
  // Scans the module for persistent versions.
  $scanned_versions = entity_type_scan_versions($entity_type, $module);
  // Loads the registered versions, if any.
  $registry_versions     = etbx_registry_version_load($entity_type);
  $unregistered_versions = array_diff_key($scanned_versions, $registry_versions);

  return $unregistered_versions;
}

/**
 * Retrieves and returns the registered versions for an entity type.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $module
 *   The module managing the entity type.
 *
 * @return array
 */
function entity_registered_versions($entity_type, $module = NULL) {
  // Loads the registered versions, if any.
  $registry_versions = etbx_registry_version_load($entity_type);

  return $registry_versions;
}

/**
 * Determines if the initial persistent version dir and raw info file are present.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $module
 *   The module's name.
 *
 * @return bool
 */
function entity_detect_init_version($entity_type, $module) {
  // Scans the module for persistent versions.
  $scanned_versions = entity_type_scan_versions($entity_type, $module);

  return in_array(INIT_VERSION, $scanned_versions);
}

/**
 * Detects and return a new version for a given entity type.
 *
 * @param string $entity_type
 *   The entity type.
 * @param int    $current_version
 *   The current version of the entity type.
 * @param string $module
 *   The module managing the entity type.
 *
 * @return false|int
 */
function entity_detect_new_version($entity_type, $current_version, $module) {
  $scanned_versions = entity_type_scan_versions($entity_type, $module);
  $latest           = end($scanned_versions);

  return $latest > $current_version ? $latest : FALSE;
}

/**
 * Returns a SHA-256 hash generated from a raw info persistent file.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $version
 *   The version of the entity type.
 * @param string $module
 *   The module managing the entity type.
 *
 * @return string
 */
function raw_entity_toolbox_persistent_get_hash($entity_type, $version, $module) {
  $filename = entity_toolbox_version_filename($entity_type, $version, 'raw_entity_toolbox', $module);

  return hash_file('sha256', $filename);
}

/**
 * Indicates if an entity type is up to date.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return bool
 */
function entity_is_up2date($entity_type) {
  $registry   = etbx_registry(ETBX_REGISTRY_GET, $entity_type);
  $registered = entity_registered_versions($entity_type);

  return $registry['version'] == end($registered);
}