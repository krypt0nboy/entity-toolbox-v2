<?php

/**
 * @file
 * test.inc
 *
 * Provides with test related functions.
 *
 * @author kryptonboy <me@harold-cohen.com>
 */

/**
 * Prepares a module before its entities are installed.
 *
 * @param string $module
 *   The module's name.
 *
 * @return bool
 *   Returns TRUE if the module is ready, FALSE if not.
 */
function etbx_module_prepare($module) {
  if (etbx_module_check_rights($module)) {
    $prepared = _etbx_persistent_prepare($module);
    $invoke   = _etbx_module_prepare($module);

    return pass_eval($invoke) && $prepared;
  }
  else {
    return FALSE;
  }
}

/**
 * Verifies that the current script is granted read/write access on the module's file.
 *
 * @param string $module
 *   The module's name.
 * @param null   $user
 *   The owner of the script.
 *
 * @return bool
 */
function etbx_module_check_rights($module, $user = NULL) {
  $user  = !isset($user) ? get_current_user() : $user;
  $check = posix_user_check_rights_recursive(module_get_path($module));
  $check = array_unique(array_values_recursive($check));
  $check = (count($check) == 1) && $check[0];
  if (!$check) {
    etbx_module_access_warning($module, $user);
  }

  return $check;
}

/**
 * Ensures a entity type provides the required data before the initial install.
 * If not, generates raw_info.
 *
 * @param string $entity_type
 *   The entity type to prepare.
 * @param string $module
 *   The module managing the entity type.
 *
 * @return bool
 *   Returns TRUE if the entity type can be installed, FALSE otherwise.
 */
function etbx_entity_type_prepare($entity_type, $module) {
  $prepare = _etbx_entity_type_prepare($entity_type, $module);

  return $prepare;
}

/**
 * Exec function for etbx_entity_type_prepare.
 *
 * @param string $entity_type
 *   The entity type to prepare.
 * @param string $module
 *   The module managing the entity type.
 *
 * @return bool
 *   Returns TRUE if the entity type can be installed, FALSE otherwise.
 *
 * @see etbx_entity_type_prepare().
 */
function _etbx_entity_type_prepare($entity_type, $module) {
  if (!entity_detect_init_version($entity_type, $module)) {
    $raw_info = entity_toolbox_get_raw_info($entity_type, $module);
    raw_entity_toolbox_persistent_write($entity_type, INIT_VERSION, $raw_info, $module);
  }

  return TRUE;
}