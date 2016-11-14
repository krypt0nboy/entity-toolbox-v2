<?php

/**
 * @file
 * update.inc
 *
 * This file provides with update functions..
 *
 * @author kryptonboy <me@harold-cohen.com>
 */

/**
 * Detects and return updates for a given entity type.
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
function etbx_detect_update($entity_type, $current_version, $module = NULL) {
  $module             = isset($module) ? $module : entity_get_module_info_safe($entity_type);
  $current_persistent = raw_entity_toolbox_persistent_read($entity_type, $current_version, $module);
  $raw_info           = entity_toolbox_get_raw_info($entity_type, $module);
  $diff               = etbx_info_diff($entity_type, $raw_info, $current_persistent);
  if (!empty($diff)) {
    return $current_version + 1;
  }
  else {
    return FALSE;
  }
}

/**
 * Updates an entity_type.
 * Registers, processes and installs an update.
 * The entity type has to be both registered and installed.
 * Updating an entity will build and store the matching persistent data.
 * It will also create the required schema update files.
 *
 * @param string   $entity_type
 *   The entity type. Must be registered and enabled.
 * @param null|int $version
 *   The update version.
 *
 * @return bool
 *   Returns TRUE if entity type was updated, FALSE otherwise.
 */
function etbx_update($entity_type, $version = NULL) {
}

/**
 * Returns a module update filename.
 *
 * @param string $module
 *   The module's name.
 * @param int    $version
 *   The update number.
 *
 * @return string
 */
function etbx_module_update_filename($module, $version) {
  return concat($module, array($version, 'inc'), '.');
}

/**
 * Returns a module update function name.
 *
 * @param string $module
 *   The module's name.
 * @param int    $version
 *   The update number.
 *
 * @return string
 */
function etbx_module_update_func_name($module, $version) {
  return concat($module, array('update', $version));
}

/**
 * Loads the updates for a given module.
 *
 * @param string $module
 *   The module's name.
 */
function etbx_load_updates($module) {
}