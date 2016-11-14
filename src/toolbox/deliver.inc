<?php

/**
 * @file
 * deliver.inc
 *
 * Provides with function to ensure builds are delivered as expected.
 *
 * @author kryptonboy <me@harold-cohen.com>
 */

/**
 * Delivers the entity type schema.
 * Unlike any other build, any version diff will generate an update rather than aggregating the versions.
 * Since hook_schema is called before the module is actually installed, we need to make sure that the entity type is registered.
 *
 * @param string $entity_type
 *   The entity type for which to get the schema.
 *
 * @return array
 *   An array where the keys are the entity type table names and the values are the matching schemas.
 *
 * @see hook_schema()
 */
function schema_deliver($entity_type) {
  $is_registered = entity_is_registered($entity_type);
  // If the entity type isn't registered, update the registry.
  // By updating the registry, new entity types will be registered and prepared.
  if (!$is_registered) {
    etbx_registry_update();
  }
  $schemas = _schema_deliver($entity_type);

  return $schemas;
}

/**
 * Executes schema_deliver().
 *
 * @param string $entity_type
 *   The entity type for which to get the schema.
 *
 * @return array
 *   An array where the keys are the entity type table names and the values are the matching schemas.
 */
function _schema_deliver($entity_type) {
  return schema_version_retrieve($entity_type, INIT_VERSION);
}

/**
 * Delivers the entity type schema update.
 *
 * @param string $entity_type
 *   The entity type.
 * @param int    $update
 *   The update for which to retrieve the update.
 *
 * @return array
 */
function schema_update_deliver($entity_type, $update) {
}

/**
 * Delivers the entity type info.
 * Unlike any other build, it has been prebuilt when building entity_toolbox_info.
 *
 * @param string $entity_type
 *   The entity type for which to get the schema.
 *
 * @return array
 *   An array where the keys are the entity type table names and the values are the matching schemas.
 *
 * @see hook_entity_info()
 */
function entity_info_deliver($entity_type) {
  $info = _entity_info_deliver($entity_type);

  return array($entity_type => $info);
}

/**
 * Executes entity_info_deliver().
 *
 * @param string $entity_type
 *   The entity type for which to get the info.
 *
 * @return array
 */
function _entity_info_deliver($entity_type) {
}