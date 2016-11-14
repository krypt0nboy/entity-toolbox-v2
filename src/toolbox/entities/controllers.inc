<?php

/**
 * @file
 * controllers.inc
 * 
 * Provides with entity controllers callback functions..
 * 
 * @author kryptonboy <me@harold-cohen.com>
 */

/**
 * Returns the toolbox entity controller for an entity type.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $bundle
 *   The entity bundle, or NULL to use the entity type default controller.
 *
 * @return \EntityToolboxController
 */
function entity_toolbox_controller($entity_type, $bundle = NULL) {
  $controllers = &drupal_static(__FUNCTION__, array());
  if (!isset($controllers[$entity_type])) {
    $type_info = entity_toolbox_get_info($entity_type);
    $class     = $type_info['classes']['controller']['class'];
    /** @var \EntityToolboxController */
    $controllers[$entity_type] = new $class($entity_type);
  }

  return $controllers[$entity_type];
}

/**
 * Returns a list of properties to be inherited by children entities.
 *
 * @param $entity_type
 *   The entity type.
 *
 * @return \string[]
 */
function entity_get_inheritable_properties($entity_type) {
  return entity_toolbox_controller($entity_type)->inheritableProperties();
}

/**
 * Returns a list of properties inherited from parent entities.
 *
 * @param $entity_type
 *   The entity type.
 *
 * @return \array[]
 */
function entity_get_inherited_properties($entity_type) {
  return entity_toolbox_controller($entity_type)->getInheritedProperties();
}

/**
 * Returns a list of fields inheritable from parent entities.
 *
 * @param $entity_type
 *   The entity type.
 * @param $bundle
 *   The entity bundle.
 *
 * @return array
 */
function entity_get_inheritable_fields($entity_type, $bundle) {
  /** @var \EntityToolboxControllerFieldable $controller */
  $controller = entity_toolbox_controller($entity_type);

  return $controller->inheritableFields($bundle);
}

/**
 * Returns a list of fields inherited from parent entities.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $bundle
 *   The entity bundle.
 *
 * @return array
 */
function entity_get_inherited_fields($entity_type, $bundle) {
  /** @var \EntityToolboxControllerFieldable $controller */
  $controller = entity_toolbox_controller($entity_type);

  return $controller->inheritedFields($bundle);
}