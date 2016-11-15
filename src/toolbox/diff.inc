<?php

/**
 * @file
 * diff.inc
 *
 * This file provides with diff related functions.
 */

/**
 * Returns the diff for an entity toolbox info.
 *
 * @param string $entity_type
 *   The entity type.
 * @param array  $new
 *   The latest info to process.
 * @param array  $old
 *   The oldest info registered to compare with.
 *
 * @return array
 */
function etbx_info_diff($entity_type, $new, $old) {
  $diff = drupal_array_diff_assoc_recursive($new, $old);

//  etbx_info_diff_ignore($entity_type, $new, $old, $diff);

  return $diff;
}

/**
 * Cleans a diff.
 * Some changes should not be taken into account when detecting and processing updates.
 *
 * @param string $entity_type
 *   The entity type.
 * @param array  $new
 *   The latest info to process.
 * @param array  $old
 *   The oldest info registered to compare with.
 * @param        $diff
 *   The diff to clean, passed by reference.
 */
function etbx_info_diff_ignore($entity_type, $new, $old, &$diff) {
  $ignore = array(
    // Ignores "entity_type", since it shouldn't change.
    'entity_type',
    // Ignores "fieldable" for now. Will be taken into account in a later version.
    'fieldable',
    'module',
    'weight',
  );
  $k      = array_keys(array_flip($ignore));
  $diff   = array_intersect_key($k, $diff);
}

/**
 * Returns the diff for an entity toolbox info.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $module
 *   The entity's module.
 * @param array  $new
 *   The latest info to process.
 * @param array  $old
 *   The oldest info registered to compare with.
 * @param array  $diff
 *   The raw diff.
 *
 * @return array
 *   An associative array whose keys are :
 *     - add : An array containing data that was added.
 *     - del : An array containing data that was deleted.
 *     - mod : An array containing data that was modified.
 */
function etbx_info_diff_process($entity_type, $module, $new, $old, $diff) {
  // Sets the structure of the formatted diff :
  $formatted = array(
    // mod : The modified data
    'mod' => array(),
    // add : The added data
    'add' => array(),
    // del : The deleted data
    'del' => array(),
  );
  // Processes the diff.
  _etbx_info_diff_process($entity_type, $module, $new, $old, $diff, $formatted);
  // Invokes hook_COMPONENT_etbx_diff_process()
  _etbx_diff_process_invoke($entity_type, $module, $new, $old, $diff, $formatted);

  return $formatted;
}

/**
 * Executes etbx_info_diff_process.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $module
 *   The entity's module.
 * @param array  $new
 *   The latest info to process.
 * @param array  $old
 *   The oldest info registered to compare with.
 * @param array  $diff
 *   The raw diff.
 * @param array  $formatted
 *   The formatted diff.
 *
 * @see etbx_info_diff_process()
 */
function _etbx_info_diff_process($entity_type, $module, $new, $old, $diff, &$formatted) {
}

/**
 * Returns the diff for entity toolbox properties.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $module
 *   The entity's module.
 * @param array  $new
 *   The latest info to process.
 * @param array  $old
 *   The oldest info registered to compare with.
 * @param array  $diff
 *   The raw diff.
 * @param array  $formatted
 *   The formatted diff.
 */
function properties_etbx_diff_process($entity_type, $module, $new, $old, $diff, &$formatted) {
  // If there is a diff in properties.
  if (!empty($diff['properties'])) {
    // Foreach diff property, we check whether the diff meant to add/del/mod a property.
    foreach ($diff['properties'] as $property => $info) {
      switch (gettype($info)) {
        // If the var type of $info is NULL or boolean, means the property should be deleted.
        case 'NULL':
        case 'boolean':
          $formatted['del']['properties'][] = $property;
          break;
        case 'array':
          // If the property is present in the old info array, should be mod, else add.
          $action                             = !empty($old['properties'][$property]) ? 'mod' : 'add';
          $formatted[$action]['properties'][] = $property;
          break;
      }
    }
  }
}

/**
 * Returns the diff for entity toolbox operations.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $module
 *   The entity's module.
 * @param array  $new
 *   The latest info to process.
 * @param array  $old
 *   The oldest info registered to compare with.
 * @param array  $diff
 *   The raw diff.
 * @param array  $formatted
 *   The formatted diff.
 */
function operations_etbx_diff_process($entity_type, $module, $new, $old, $diff, &$formatted) {
  // If there is a diff in operations.
  if (!empty($diff['operations'])) {
    foreach ($diff['operations'] as $operation => $info) {
      switch (gettype($info)) {
        // If the var type of $info is NULL or boolean, means the operation should be deleted.
        case 'NULL':
        case 'boolean':
          $formatted['del']['operations'][] = $operation;
          break;
        case 'array':
          // If the property is present in the old info array, should be mod, else add.
          $action                             = !empty($old['operations'][$operation]) ? 'mod' : 'add';
          $formatted[$action]['operations'][] = $operation;
          break;
      }
    }
  }
}

/**
 * Writes a persistent diff between two versions of the same entity.
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
 * @return string
 */
function etbx_info_diff_filename($entity_type, $v1, $v2, $module = NULL) {
  $module   = isset($module) ? $module : entity_get_module_info_safe($entity_type);
  // Filename pattern for diff is [entity_type].diff.[v1]_[v2].json
  $filename = concat($entity_type, array(
    'diff',
    concat($v1, $v2),
  ), '.');
  // A diff file should be located in the entity's module diffs directory.
  // module
  //  |- src
  //  |-- diffs
  $dir      = paths_join(module_get_path($module), array('diffs'));

  return file_path($filename, $dir, array(), 'json');
}