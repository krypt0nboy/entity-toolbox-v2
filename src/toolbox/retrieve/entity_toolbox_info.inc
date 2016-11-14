<?php

/**
 * @file
 * entity_toolbox_info.inc
 *
 * Provides with functions to retrieve entity_toolbox_info builds..
 *
 * @author kryptonboy <me@harold-cohen.com>
 */

/**
 * Retrieves build and processed entity_toolbox_info data for a given entity type.
 * If not built yet, etbx will build and process it.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return array
 */
function entity_toolbox_info_retrieve($entity_type) {
  $module = entity_get_module_info_safe($entity_type);
  // Retrieves the registered versions.
  $versions      = entity_registered_versions($entity_type);
  $versions_info = array();
  foreach ($versions as $version) {
    $version_retrieved       = entity_toolbox_info_retrieve_version($entity_type, $version);
    $versions_info[$version] = $version_retrieved;
    etbx_info_tmp_cache_set($entity_type, $version_retrieved);
  }

  return entity_toolbox_info_aggregate($entity_type, $versions_info);
}

/**
 * Retrieves built and processed entity_toolbox_info data for a given entity type version.
 *
 * @param string $entity_type
 *   The entity type.
 * @param int    $version
 *   The version to retrieve.
 *
 * @return array
 */
function entity_toolbox_info_retrieve_version($entity_type, $version) {
  $info = entity_toolbox_persistent_read($entity_type, $version);
  if ($info === FALSE) {
    $info = entity_toolbox_info_build($entity_type, $version);
    entity_toolbox_persistent_write($entity_type, $version, $info);

    return entity_toolbox_persistent_read($entity_type, $version);
  }
}

/**
 * Retrieves the aggregated build for entity_toolbox_info.
 *
 * @param string $entity_type
 *   The entity type.
 * @param array  $versions_info
 *   An array of retrieved info builds.
 *
 * @return array
 */
function entity_toolbox_info_aggregate($entity_type, array $versions_info) {

}