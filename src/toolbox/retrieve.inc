<?php

/**
 * @file
 * retrieve.inc
 *
 * This file provides with functions to retrieve built and processed data.
 */

require_once 'retrieve/entity_toolbox_info.inc';

/**
 * Retrieves the built data for a given hook and entity_type.
 *
 * @param string $hook
 *   The hook.
 * @param string $entity_type
 *   The entity type.
 *
 * @return array|false
 */
function build_retrieve($hook, $entity_type) {
  $current_version = etbx_entity_current_version($entity_type);
}

/**
 * Retrieves built and processed schema data for a given entity type.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return array
 */
function schema_retrieve($entity_type) {
  $schemas = schema_persistent_read($entity_type, INIT_VERSION);
  if ($schemas === FALSE) {
    $schemas = schema_build($entity_type);
    schema_persistent_write($entity_type, INIT_VERSION, $schemas);
  }

  return $schemas;
}

/**
 * Retrieves built and processed schema update data for a given entity type.
 *
 * @param string $entity_type
 *   The entity type.
 * @param int    $version
 *   The version.
 *
 * @return array
 */
function schema_version_retrieve($entity_type, $version) {
  $schemas = schema_persistent_read($entity_type, $version);
  // If the requested schema version is not available, build it.
  if ($schemas === FALSE) {

  }

  return $schemas;
}

/**
 * Retrieves built and processed schema update for a given entity type.
 *
 * @param string $entity_type
 *   The entity type.
 * @param int    $update
 *   The update for which to retrieve the update.
 */
function schema_update_retrieve($entity_type, $update) {

}

/**
 * Retrieves built and processed entity_info data for a given entity type.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return array
 */
function entity_info_retrieve($entity_type) {

}

/**
 * Retrieves build and processed entity_property_info data for a given entity_type.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return array
 */
function entity_property_info_retrieve($entity_type) {

}