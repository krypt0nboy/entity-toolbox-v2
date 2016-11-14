<?php

/**
 * @file
 * db.inc
 *
 * This file provides with db related functions.
 * ETBX tables unprocessed schema can be returned using the functions below.
 */

/**
 * Table to store entity_toolbox related cache.
 */
define('ENTITY_TOOLBOX_DB__CACHE', 'cache_entity_toolbox');
/**
 * ETBX registry table name.
 *
 * @see etbx_registry_table()
 */
define('ENTITY_TOOLBOX_DB__REGISTRY', 'etbx_registry');
/**
 * ETBX versions registry table name.
 */
define('ENTITY_TOOLBOX_DB__VERSIONS', 'etbx_registry_versions');

/**
 * Returns the unprocessed schema for etbx_registry table.
 * The etbx_registry table registers all the entities managed by ETBX.
 *
 * @return array
 */
function etbx_registry_table() {
  return array(
    'description' => 'Entity toolbox registry table.',
    'fields'      => array(
      'entity_type' => array(
        'type'        => 'varchar',
        'length'      => 255,
        'description' => 'The entity type.',
        'default'     => '',
        'not null'    => TRUE,
      ),
      'module'      => array(
        'type'        => 'varchar',
        'length'      => 255,
        'description' => 'The module managing the entity type.',
        'default'     => '',
        'not null'    => TRUE,
      ),
      'version'     => array(
        'type'        => 'int',
        'description' => 'The current installed version.',
        'default'     => 0,
        'not null'    => TRUE,
      ),
      'status'      => array(
        'type'        => 'int',
        'size'        => 'tiny',
        'description' => 'A boolean indicating if the entity type is installed.',
        'default'     => 0,
        'not null'    => TRUE,
      ),
    ),
    'unique keys' => array('entity_type' => array('entity_type'))
  );
}

/**
 * Returns the entity toolbox etbx_versions table.
 * This table keeps track of each entity version.
 *
 * @return array
 */
function etbx_registry_versions_table() {
  return array(
    'description' => 'Keeps track of each entity version.',
    'fields'      => array(
      'entity_type' => array(
        'type'        => 'varchar',
        'length'      => 255,
        'description' => 'The entity type.',
        'default'     => '',
        'not null'    => TRUE,
      ),
      'version'     => array(
        'type'        => 'int',
        'description' => 'The version number.',
        'default'     => 0,
        'not null'    => TRUE,
      ),
      'filename'    => array(
        'type'        => 'varchar',
        'length'      => 255,
        'description' => 'The raw info persistent filename.',
        'default'     => '',
        'not null'    => TRUE,
      ),
      'hash'        => array(
        'type'        => 'varchar',
        'length'      => 255,
        'description' => 'A hash validating the raw info for this entity version.',
        'default'     => '',
        'not null'    => TRUE,
      ),
      'status'      => array(
        'type'        => 'int',
        'size'        => 'tiny',
        'description' => 'A boolean indicating if this version has been enabled.',
        'default'     => 0,
        'not null'    => TRUE,
      ),
    ),
  );
}

/**
 * Inserts a new entity type in ETBX registry.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $module
 *   The module managing the entity type.
 * @param int    $version
 *   The version to register.
 * @param int    $status
 *   Whether the entity type is installed or not.
 */
function etbx_registry_table_insert($entity_type, $module, $version = 0, $status = 0) {
  $query = db_insert(ENTITY_TOOLBOX_DB__REGISTRY)
    ->fields(array(
      'entity_type' => $entity_type,
      'module'      => $module,
      'version'     => $version,
      'status'      => $status
    ))
    ->execute();
}

/**
 * Updates the ETBX registry.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $module
 *   The module managing the entity type.
 * @param int    $version
 *   The version to register.
 */
function etbx_registry_table_update_version($entity_type, $module, $version) {
  $query = db_update(ENTITY_TOOLBOX_DB__REGISTRY, 'r')
    ->fields(array(
      'version' => $version
    ))
    ->condition('r.entity_type', $entity_type)
    ->condition('r.module', $module)
    ->execute();
}

/**
 * Updates the ETBX registry.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $module
 *   The module managing the entity type.
 * @param int    $status
 *   Whether the entity type is installed or not.
 */
function etbx_registry_table_update_status($entity_type, $module, $status) {
  $query = db_update(ENTITY_TOOLBOX_DB__REGISTRY, 'r')
    ->fields(array(
      'status' => $status
    ))
    ->condition('r.entity_type', $entity_type)
    ->condition('r.module', $module)
    ->execute();
}

/**
 * Inserts a new entity type in ETBX registry.
 *
 * @param string $entity_type
 *   The entity type.
 * @param int    $version
 *   The version to register.
 * @param string $filename
 *   The raw info filename.
 * @param string $hash
 *   The file's hash when parsed.
 * @param int    $status
 *   Whether the entity type is installed or not.
 */
function etbx_registry_versions_table_insert($entity_type, $version, $filename, $hash, $status = 0) {
  $query = db_insert(ENTITY_TOOLBOX_DB__VERSIONS)
    ->fields(array(
      'entity_type' => $entity_type,
      'version'     => $version,
      'filename'    => $filename,
      'hash'        => $hash,
      'status'      => $status
    ))
    ->execute();
}

/**
 * Updates the ETBX registry.
 *
 * @param string $entity_type
 *   The entity type.
 * @param int    $version
 *   The version to register.
 * @param int    $status
 *   Whether the entity type is installed or not.
 */
function etbx_registry_versions_table_update_status($entity_type, $version, $status) {
  $query = db_update(ENTITY_TOOLBOX_DB__REGISTRY, 'r')
    ->fields(array(
      'status' => $status
    ))
    ->condition('r.entity_type', $entity_type)
    ->condition('r.version', $version)
    ->execute();
}

/**
 * Loads every version registered in etbx_registry_versions for a given entity type.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return array
 *   An array where the keys are the entity type versions and the values are the matching fetched lines.
 */
function etbx_registry_version_load($entity_type) {
  $query = db_select(ENTITY_TOOLBOX_DB__VERSIONS, 'r')
    ->fields('r', array('version'))
    ->condition('r.entity_type', $entity_type)
    ->execute();

  $results = array();
  while (($result = $query->fetchAssoc())) {
    $results[] = $result;
  }

  return $results;
}