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
  etbx_info_diff_ignore($entity_type, $new, $old, $diff);

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
  );
  $diff  = array_intersect_key(array_flip($ignore), $diff);
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
}