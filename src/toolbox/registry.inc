<?php

/**
 * @file
 * registry.inc
 *
 * This file provides with entity registry related functions.
 *
 * @see etbx_registry_table().
 */

/**
 * ETBX Registry.
 */
define('ETBX_REGISTRY', 'etbx_registry');
/**
 * Notification that registry is available.
 */
define('ETBX_REGISTRY_AVAILABLE', 1);
/**
 * Notification for registry to be reset.
 */
define('ETBX_REGISTRY_NEEDS_RESET', 2);
/**
 * Notification for registry to be rebuilt.
 */
define('ETBX_REGISTRY_NEEDS_REBUILD', 3);
/**
 * Gets registry without building or rebuilding.
 */
define('ETBX_REGISTRY_GET', 1);
/**
 * Gets registry after resetting static var.
 */
define('ETBX_REGISTRY_RESET', 2);
/**
 * Gets registry after rebuild.
 */
define('ETBX_REGISTRY_REBUILD', 3);

/**
 * Loads the entire etbx_registry table.
 * Note that the registry should be retrieved from etbx_registry_get_info() only,
 * since it may requires an update.
 *
 * @return array
 */
function etbx_registry_load() {
  $query   = db_select(ENTITY_TOOLBOX_DB__REGISTRY, 'r')
    ->fields('r', array())
    ->execute();
  $results = array();
  while (($result = $query->fetchAssoc())) {
    $results[$result['entity_type']] = $result;
  }

  return $results;
}

/**
 * Loads the entire etbx_registry_versions table.
 * Note that the registry should be retrieved from etbx_registry_get_info() only,
 * since it may requires an update.
 *
 * @return array
 *   Returns an associative array where the keys are the entity types, followed by the registered version registry info :
 *     - entity_type : The entity type.
 *      - version : The version.
 *       - filename : The raw info filename.
 *       - hash : The hash matching the raw info file during its first parsing.
 *       - status : The status of the version.
 *
 * @see etbx_registry_versions_table()
 */
function etbx_registry_versions_load() {
  $query = db_select(ENTITY_TOOLBOX_DB__VERSIONS, 'r')
    ->fields('r', array())
    //@todo use groupBy rather than the regrouping below.
    ->execute();

  $results = array();
  while (($result = $query->fetchAssoc())) {
    $results[$result['entity_type']][$result['version']] = $result;
  }

  return $results;
}

/**
 * Loads the entire etbx_registry_versions table.
 * Note that the registry should be retrieved from etbx_versions_registry() only,
 * since it may require an update.
 *
 * @return array
 * @deprecated duplicate function to remove
 */
function etbx_versions_registry_load() {
  $query   = db_select(ENTITY_TOOLBOX_DB__VERSIONS, 'r')
    ->fields('r', array())
    ->execute();
  $results = array();
  while (($result = $query->fetchAssoc())) {
    $results[$result['entity_type']][$result['version']] = $result;
  }

  return $results;
}

/**
 * Returns the ETBX registry.
 * Before loading the registry, checks if it needs to be either reset/rebuilt/updated,
 * by checking the variable "registry_status".
 * Should not be called outside function etbx_registry_get_info.
 *
 * @return array
 *
 * @see etbx_registry_get_info()
 */
function etbx_registry() {
  // Cached since used very often.
  static $drupal_static_fast;
  $drupal_static_fast['registry'] = &drupal_static(__FUNCTION__, array());
  $registry                       = &$drupal_static_fast['registry'];
  // Gets the registry status.
  $status = variable_get('registry_status');
  switch ($status) {
    // If available, checks if cached.
    // If not, loads the registry.
    case ETBX_REGISTRY_AVAILABLE:
      $registry = empty($registry) ? etbx_registry_load() : $registry;
      break;
    // If needs to be reset, reloads the registry.
    case ETBX_REGISTRY_NEEDS_RESET:
      $registry = etbx_registry_load();
      variable_set('registry_status', ETBX_REGISTRY_AVAILABLE);
      break;
    // If needs to be rebuilt, updates the registry.
    case ETBX_REGISTRY_NEEDS_REBUILD:
      etbx_registry_update();
      $registry = etbx_registry_load();
      break;
  }

  return $registry;
}

/**
 * Returns the ETBX registry.
 *
 * @param null|string $entity_type
 *   The entity type.
 *
 * @return array|null
 */
function etbx_registry_get_info($entity_type = NULL) {
  // Gets the registry.
  $registry = etbx_registry();

  if (isset($entity_type)) {
    return !empty($registry[$entity_type]) ? $registry[$entity_type] : NULL;
  }
  else {
    return $registry;
  }
}

/**
 * Indicates if an entity type is registered by checking the register.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return bool
 */
function entity_is_registered($entity_type) {
  $registry = etbx_registry_get_info($entity_type);

  return (bool) $registry;
}

/**
 * Updates the ETBX registry.
 *
 * @return bool
 *   Returns TRUE if registry was successfully updated, FALSE otherwise.
 */
function etbx_registry_update() {
  if (!lock_acquire(__FUNCTION__)) {
    // Another request got the lock, wait for it to finish.
    $hold = lock_wait(__FUNCTION__);
    // If lock is available, go to _etbx_register_update.
    if (!$hold) {
      goto _etbx_register_update;
    }
    else {
      return FALSE;
    }
  }
  _etbx_register_update:
  // Actually updates the register.
  _etbx_registry_update();
  lock_release(__FUNCTION__);
  // Sets the registry as available.
  variable_set('registry_status', ETBX_REGISTRY_AVAILABLE);
  // Updates the registry for etbx entities versions.
  etbx_version_registry_update();

  return TRUE;
}

/**
 * Does the update for etbx_registry_update().
 *
 * This function should be called within etbx_registry_update() only.
 *
 * @return bool
 *   Returns TRUE if registry was successfully updated, FALSE otherwise.
 *
 * @see etbx_registry_update()
 * @todo handle registry update errors
 */
function _etbx_registry_update() {
  // Gets info on modules implementing ETBX in any way.
  $modules = entity_toolbox_implement_get_info();
  // Loads the current registry.
  $registry = etbx_registry_load();
  // Groups the registry entries by module.
  $registry_by_modules = array_values_group_by($registry, 'module');
  // Prepare the modules implementing etbx
  //@todo handle excludes for modules that returns error on prepare_check
  array_map('etbx_module_prepare', $modules);
  $to_register = array();
  // Foreach module implementing entity toolbox.
  foreach ($modules as $module) {
    $module_enabled = module_is_enabled($module);
    $proceed        = $module_enabled;
    // Gets whether the module registry entry if any.
    $registry_ = !empty($registry_by_modules[$module]) ? $registry_by_modules[$module] : array();
    // If the module is disabled, loads the info.inc file.
    if (!$proceed) {
      $proceed = etbx_info_inc_load($module);
    }
    // If the info.inc is available and loaded, proceeds.
    if ($proceed) {
      // Invoke function foreach module.
      $function = concat($module, 'entity_toolbox_info');
      // If implemented, invokes hook_entity_toolbox_info.
      if (function_exists($function)) {
        $invoke = $function();
        foreach ($invoke as $entity_type => $raw_info) {
          // Gets the entity type registry entry, if any.
          // If not, then $is_registered will be set to FALSE.
          $type_registry = !empty($registry_[$entity_type]) ? $registry_[$entity_type] : array();
          $is_registered = !empty($type_registry);
          // If not registered, registers the new entity type.
          if (!$is_registered) {
            $to_register[$entity_type] = array('module' => $module);
          }
        }
      }
    }
  }
  /**
   * If entity types require to be register, register them.
   *
   * @var string $type
   *   The entity type to register
   * @var array  $r
   *   The info for registration.
   */
  foreach ($to_register as $type => $r) {
    etbx_entity_register($type, $r['module']);
  }
}

/**
 * Rebuilds the ETBX registry.
 *
 * @return bool
 *   Returns TRUE if registry was successfully rebuilt, FALSE otherwise.
 */
function etbx_registry_rebuild() {
  // Updates the system module registry to ensure recently added modules are included in our registry.
  system_rebuild_module_data();
  // Updates the registry.
  etbx_registry_update();
}

/**
 * Processes and registers a new entity type.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $module
 *   The module managing the entity type.
 *
 * @return bool
 *   Returns TRUE if successfully registered or FALSE otherwise.
 */
function etbx_entity_register($entity_type, $module) {
  // Prepares the entity type before it's registered.
  $proceed = etbx_entity_type_prepare($entity_type, $module);
  // If successfully prepared, registers.
  if ($proceed) {
    etbx_registry_table_insert($entity_type, $module);
  }
}

/**
 * Processes and registers an update for a given entity type.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $version
 *   The version of the entity type.
 * @param string $module
 *   The module managing the entity type.
 *
 * @return bool
 *   Returns TRUE if successfully registered or FALSE otherwise.
 */
function etbx_update_register($entity_type, $version, $module) {
  $current_version = $version - 1;
  etbx_version_mkdir($module, $version);
  $raw_info = entity_toolbox_get_raw_info($entity_type, $module);
  raw_entity_toolbox_persistent_write($entity_type, $version, $raw_info, $module);
  $current_persistent = raw_entity_toolbox_persistent_read($entity_type, $current_version, $module);
  $diff               = etbx_info_diff($entity_type, $raw_info, $current_persistent);
  $formatted_diff     = etbx_info_diff_process($entity_type, $module, $raw_info, $current_persistent, $diff);
  etbx_info_diff_persistent_write($entity_type, $formatted_diff, $current_version, $version, $module);
  entity_version_register($entity_type, $version, $module);
}

/**
 * Returns the ETBX versions registry.
 * Before loading the registry, checks if it needs to be either reset/rebuilt/updated,
 * by checking the variable "registry_versions_status".
 * Should not be called outside function etbx_registry_versions_get_info.
 *
 * @return array
 *
 * @see etbx_registry_versions_get_info()
 */
function etbx_registry_versions() {
  // Cached since used very often.
  static $drupal_static_fast;
  $drupal_static_fast['registry'] = &drupal_static(__FUNCTION__, array());
  $registry                       = &$drupal_static_fast['registry'];
  // Gets the registry status.
  $status = variable_get('registry_versions_status');
  switch ($status) {
    // If available, checks if cached.
    // If not, loads the registry.
    case ETBX_REGISTRY_AVAILABLE:
      $registry = empty($registry) ? etbx_registry_versions_load() : $registry;
      break;
    // If needs to be reset, reloads the registry.
    case ETBX_REGISTRY_NEEDS_RESET:
      $registry = etbx_registry_versions_load();
      break;
    // If needs to be rebuilt, updates the registry.
    case ETBX_REGISTRY_NEEDS_REBUILD:
      etbx_version_registry_update();
      $registry = etbx_registry_versions_load();
      break;
  }

  return $registry;
}

/**
 * Returns the ETBX versions registry.
 *
 * @param null|string $entity_type
 *   The entity type.
 *
 * @return array|null
 */
function etbx_registry_versions_get_info($entity_type = NULL) {
  // Gets the registry.
  $registry = etbx_registry_versions();

  if (isset($entity_type)) {
    return !empty($registry[$entity_type]) ? $registry[$entity_type] : NULL;
  }
  else {
    return $registry;
  }
}

/**
 * Updates the versions registry.
 *
 * @return bool
 */
function etbx_version_registry_update() {
  if (!lock_acquire(__FUNCTION__)) {
    // Another request got the lock, wait for it to finish.
    $hold = lock_wait(__FUNCTION__);
    // If lock is available, go to _etbx_register_update.
    if (!$hold) {
      goto _etbx_version_register_update;
    }
    else {
      return FALSE;
    }
  }
  _etbx_version_register_update:
  // Actually updates the register.
  _etbx_version_registry_update();
  lock_release(__FUNCTION__);

  return TRUE;
}

/**
 * Executes etbx_version_registry_update().
 *
 * @return bool
 *
 * @see etbx_version_registry_update()
 */
function _etbx_version_registry_update() {
  // Loads the current registry.
  $registry = etbx_registry_load();
  // Groups the registry entries by module.
  $registry_by_modules = array_values_group_by($registry, 'module');
  // Loads the versions current registry.
  $v_registry = etbx_registry_versions_load();
  foreach ($registry_by_modules as $module => $registry_) {
    foreach ($registry_ as $entity_type => $type_registry_) {
      $status          = !empty($type_registry_['status']) ? $type_registry_['status'] : 0;
      $current_version = !empty($type_registry_['version']) ? $type_registry_['version'] : INIT_VERSION;
      $has_v_registry  = !empty($v_registry[$entity_type]);
      $is_registered   = $current_version && $has_v_registry;
      // If not registered, registers the versions.
      if (!$is_registered) {
        if (entity_versions_register($entity_type, $module)) {
          goto etbx_register_updates;
        }
      }
      // Detects updates if the entity type has its versions registered.
      else {
        etbx_register_updates:
        if (($update = etbx_detect_update($entity_type, $current_version, $module)) !== FALSE) {
          // If found, registers the new update.
          etbx_update_register($entity_type, $update, $module);
        }
      }
    }
  }
}

/**
 * Registers every version for an entity type.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $module
 *   The module managing the entity type.
 *
 * @return bool
 */
function entity_versions_register($entity_type, $module) {
  $unregistered_versions = entity_unregistered_versions($entity_type, $module);
  foreach ($unregistered_versions as $version) {
    entity_version_register($entity_type, $version, $module);
  }

  return TRUE;
}

/**
 * Processes and registers a new version for a given entity.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $version
 *   The version of the entity type.
 * @param string $module
 *   The module managing the entity type.
 *
 * @return bool
 *   Returns TRUE if successfully registered or FALSE otherwise.
 */
function entity_version_register($entity_type, $version, $module) {
  $hash     = raw_entity_toolbox_persistent_get_hash($entity_type, $version, $module);
  $filename = entity_toolbox_version_filename($entity_type, $version, 'raw_entity_toolbox', $module);
  etbx_registry_versions_table_insert($entity_type, $version, $filename, $hash, 0);

  return TRUE;
}