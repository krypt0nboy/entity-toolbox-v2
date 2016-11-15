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
 * Regexp to match an etbx update file.
 */
define('RGX__ETBX_UPDATE_FILE', '/\w+\.7\d{3}.inc$/');

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
  // Gets the entity module, if not provided.
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
 * Pre updates an entity type.
 * Will generate the persistent builds.
 *
 * @param string      $entity_type
 *   The entity type.
 * @param int         $version
 *   The version (update) to prepare.
 * @param null|string $module
 *   The module managing the entity type.
 *
 * @return bool
 */
function etbx_entity_pre_update($entity_type, $version, $module = NULL) {

}

/**
 * Updates a module entities.
 * Will generate an update for every registered update.
 *
 * @param string $module
 *   The module's name.
 *
 * @return bool
 *   Returns TRUE on success, FALSE on error.
 */
function etbx_module_update($module) {
  //builds
  //group by

  // Loads the current registry.
  $registry = etbx_registry_load();
  // Groups the registry entries by module.
  $registry_by_modules = array_values_group_by($registry, 'module');
  // Gets the module registry.
  // If the module has no entry, exits and returns error.
  if (empty($registry_by_modules[$module])) {
    goto no_update;
  }
  $registry_m  = $registry_by_modules[$module];
  $pre_updated = array();
  /**
   * @var string $type
   *   An entity type.
   * @var array  $type_registry
   *   An entity type registry.
   */
  foreach ($registry_m as $type => $type_registry) {
    $type_current_version   = $type_registry['version'];
    $type_versions_registry = etbx_registry_versions_get_info($type);
    foreach ($type_versions_registry as $type_version => $tvr_entry) {
      $pre_updated[$type][$type_version] = etbx_entity_pre_update($type, $type_version, $module);
    }
  }
  // If one the entities pre update returned FALSE, exits.
  if (!pass_eval($pre_updated)) {
    goto no_update;
  }

  no_update:

  return FALSE;
}

/**
 * Generates a module update, containing one or more entity type updates.
 * An update file will be written in the module updates dir.
 *
 * module dir
 *  |- src
 *  |-- updates
 *  |--- "module"."update".inc
 *
 * foo
 *  |- src
 *  |-- updates
 *  |--- foo.7001.inc
 *
 * @param string   $module
 *   The module's name. The module must be installed, enabled and registered.
 * @param null|int $version
 *   The update version.
 *
 * @return bool
 *   Returns TRUE on success, FALSE on error.
 */
function etbx_module_update_generate($module, $version = NULL) {

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
 * Scans a module for update files.
 *
 * @param string $module
 *   The module's name.
 *
 * @return array
 */
function etbx_scan_update_files($module) {
  $updates_path = module_updates_dir_path($module);

  return file_scan_directory($updates_path, RGX__ETBX_UPDATE_FILE);
}