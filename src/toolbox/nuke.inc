<?php

/**
 * @file
 * nuke.inc
 *
 * This file provides with clean uninstall functions.
 */

/**
 * Nukes a module tables and variables, as well as its cache.
 *
 * @param string $module
 *   The module to nuke.
 *
 * @return bool
 *   Returns TRUE if uninstall was successful, FALSE if not.
 */
function etbx_module_nuke($module) {
  _etbx_nuke_tables($module);
  _etbx_nuke_variables($module);
}

/**
 * Nukes a module tables.
 *
 * @param string $module
 *   The module's name.
 *
 * @return bool
 *   Returns TRUE if nuke was successful, FALSE if not.
 */
function _etbx_nuke_tables($module) {

}

/**
 * Nukes a module entity variables.
 *
 * @param string $module
 *   The module's name.
 *
 * @return bool
 *   Returns TRUE if nuke was successful, FALSE if not.
 */
function _etbx_nuke_variables($module) {

}

/**
 * Nukes the persistent data of an entity type.
 *
 * @param string $entity_type
 *   The entity type.
 * @param int    $version
 *   The version to nuke.
 * @param array  $hooks
 *   The hooks to nuke.
 */
function nuke_persistent($entity_type, $version = INIT_VERSION, $hooks = array()) {
  $version_dir = paths_join(module_versions_dir_path(entity_get_module_info($entity_type)), array($version));
  $files       = file_scan_directory($version_dir, RGX__FILE_EXT_JSON);
  foreach ($files as $file) {
    unlink($file->uri);
  }
}

/**
 * Nukes all entity type persistent data files.
 */
function nuke_persistent_all() {
  foreach (entity_toolbox_get_entities() as $entity_type) {
    nuke_persistent($entity_type, INIT_VERSION);
  }
}

/**
 * Implements hook_modules_uninstalled().
 */
function entity_toolbox_modules_uninstalled($modules) {
  foreach ($modules as $module) {
    etbx_module_nuke($module);
  }
}