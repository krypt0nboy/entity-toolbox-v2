<?php

/**
 * @file
 * install.inc
 *
 * Provides with functions to install/uninstall entities..
 *
 * @author kryptonboy <me@harold-cohen.com>
 */

/**
 * Registers, enable and installs an entity type.
 *
 * @param string $entity_type
 *   The entity type to install.
 */
function etbx_entity_install($entity_type) {
  //build etbx_info
}

/**
 * Indicates if an entity type is installed.
 * This function cannot be called from within the etbx_registry_update cycle,
 * and has to be called for a registered entity type.
 *
 * @param string $entity_type
 *   A registered entity type.
 *
 * @return bool
 *
 * @see etbx_registry_update()
 * @see _etbx_registry_update()
 */
function entity_is_installed($entity_type) {
  $registry = etbx_registry(ETBX_REGISTRY_GET, $entity_type);

  return !empty($registry['status']) ? $registry['status'] : 0;
}