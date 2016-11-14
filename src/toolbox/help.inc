<?php

/**
 * @file
 * help.inc
 * 
 * Provides with helper functions for entity_toolbox_info..
 * 
 * @author kryptonboy <me@harold-cohen.com>
 */

/**
 * Indicates if an entity type can have revisions.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return bool
 */
function entity_type_has_revisions($entity_type) {
  $controller = entity_toolbox_controller($entity_type);
  $helper     = $controller->getToolboxHelper();

  return $helper->hasRevisions();
}

/**
 * Indicates if an entity type can have translations.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return bool
 */
function entity_type_has_translations($entity_type) {
  $controller = entity_toolbox_controller($entity_type);
  $helper     = $controller->getToolboxHelper();

  return $helper->hasTranslations();
}

/**
 * Returns the toolbox info labels.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $label
 *   The label to return.
 *
 * @return string|array
 */
function entity_type_labels($entity_type, $label = NULL) {
  $controller = entity_toolbox_controller($entity_type);
  $helper     = $controller->getToolboxHelper();

  return isset($label) ? $helper->label($label) : $helper->labels();
}

/**
 * Returns the toolbox info single label.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return string
 */
function entity_type_label_single($entity_type) {
  $controller = entity_toolbox_controller($entity_type);
  $helper     = $controller->getToolboxHelper();

  return $helper->labelSingle();
}

/**
 * Returns the toolbox info plural label.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return string
 */
function entity_type_label_plural($entity_type) {
  $controller = entity_toolbox_controller($entity_type);
  $helper     = $controller->getToolboxHelper();

  return $helper->labelPlural();
}

/**
 * Returns the toolbox info single lowercase label.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return string
 */
function entity_type_label_single_lc($entity_type) {
  $controller = entity_toolbox_controller($entity_type);
  $helper     = $controller->getToolboxHelper();

  return $helper->labelSingleLowerCase();
}

/**
 * Returns the toolbox info plural lowercase label.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return string
 */
function entity_type_label_plural_lc($entity_type) {
  $controller = entity_toolbox_controller($entity_type);
  $helper     = $controller->getToolboxHelper();

  return $helper->labelPluralLowerCase();
}

/**
 * Returns the toolbox info machine name plural label.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return string
 */
function entity_type_machine_name_plural($entity_type) {
  $controller = entity_toolbox_controller($entity_type);
  $helper     = $controller->getToolboxHelper();

  return $helper->machineNamePlural();
}

/**
 * Returns the entity classes.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $class
 *   The class to return.
 *
 * @return string|array
 */
function entity_type_classes($entity_type, $class = NULL) {
  $controller = entity_toolbox_controller($entity_type);
  $helper     = $controller->getToolboxHelper();

  return isset($class) ? $helper->classGet($class) : $helper->classes();
}

/**
 * Returns the entity callbacks.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $callback
 *   The callback to return.
 *
 * @return string|array
 */
function entity_type_callbacks($entity_type, $callback = NULL) {
  $controller = entity_toolbox_controller($entity_type);
  $helper     = $controller->getToolboxHelper();

  return isset($callback) ? $helper->callbackGet($callback) : $helper->callbacksGet();
}

/**
 * Returns the entity root path.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return string|array
 */
function entity_type_root_path($entity_type) {
  $controller = entity_toolbox_controller($entity_type);
  $helper     = $controller->getToolboxHelper();

  return $helper->rootPath();
}

/**
 * Returns the toolbox info properties.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $name
 *   The property to return.
 *
 * @return string|array
 */
function entity_type_properties($entity_type, $name = NULL) {
  $controller = entity_toolbox_controller($entity_type);
  $helper     = $controller->getPropsHelper();

  return isset($name) ? $helper->propGet($name) : $helper->alias();
}

/**
 * Returns the entity required properties.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return string[]
 */
function entity_type_required_properties($entity_type) {
  $controller = entity_toolbox_controller($entity_type);
  $helper     = $controller->getPropsHelper();

  return $helper->requiredPropertiesGet();
}

/**
 * Returns the entity type fields that are inherited from parents.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return string[]
 */
function entity_type_inherited_fields($entity_type) {
}

/**
 * Returns the entity type fields that are to be inherited by children entities.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return string[]
 */
function entity_type_inheritable_fields($entity_type) {
}

/**
 * Returns the entity type properties that are inherited from parent entities.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return string[]
 */
function entity_type_inherited_properties($entity_type) {
}

/**
 * Returns the entity type fields that are to be inherited by children entities.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return string[]
 */
function entity_type_inheritable_properties($entity_type) {
}

/**
 * Returns the properties to be exposed in a given entity form.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $type
 *   The form type.
 *
 * @return array
 */
function entity_type_form_exposed_properties($entity_type, $type) {
  $controller = entity_toolbox_controller($entity_type);
  $helper     = $controller->getPropsHelper();

  return $helper->entityFormExposedPropertiesGet($type);
}

/**
 * Returns a boolean indicating if the property is multi value or not.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $name
 *   The property name.
 *
 * @return bool
 */
function is_property_multi_value($entity_type, $name) {
  $controller = entity_toolbox_controller($entity_type);
  $helper     = $controller->getPropsHelper();

  return $helper->propIsMulti($name);
}

/**
 * Returns a boolean indicating if the property is a reference.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $name
 *   The property name.
 *
 * @return bool
 */
function is_property_reference($entity_type, $name) {
  $controller = entity_toolbox_controller($entity_type);
  $helper     = $controller->getPropsHelper();

  return $helper->propIsReference($name);
}

/**
 * Returns a boolean indicating if the property is a parent.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $name
 *   The property name.
 *
 * @return bool
 */
function is_property_parent($entity_type, $name) {
  $controller = entity_toolbox_controller($entity_type);
  $helper     = $controller->getPropsHelper();

  return $helper->propIsParent($name);
}

/**
 * Returns a boolean indicating if the property is a self parent.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $name
 *   The property name.
 *
 * @return bool
 */
function is_property_self_parent($entity_type, $name) {
  $controller = entity_toolbox_controller($entity_type);
  $helper     = $controller->getPropsHelper();

  return $helper->propIsSelfParent($name);
}

/**
 * Returns the operations implemented by an entity type.
 *
 * @param string $entity_type
 *   The entity type.
 * @param bool   $real
 *   Whether to return the operations declared outside entity toolbox as well.
 *
 * @return array
 */
function entity_type_operations($entity_type, $real = FALSE) {
  $controller = entity_toolbox_controller($entity_type);
  $helper     = $controller->getToolboxHelper();

  return $helper->operationsGet($real);
}

/**
 * Indicates if an entity type implement a given operation.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $operation
 *   The operation.
 * @param bool   $real
 *   Whether to return the operations declared outside entity toolbox as well.
 *
 * @return bool
 */
function entity_type_implements_operation($entity_type, $operation, $real = FALSE) {
  $controller = entity_toolbox_controller($entity_type);
  $helper     = $controller->getToolboxHelper();

  return $helper->implementsOperation($operation, $real);
}

/**
 * @param $entity_type
 * @return string|false
 */
function entity_type_group_name($entity_type) {
  $controller = entity_toolbox_controller($entity_type);
  $helper     = $controller->getToolboxHelper();

  return $helper->groupName();
}

/**
 * @param $entity_type
 * @return array
 */
function entity_type_schemas($entity_type) {
  $schemas = &drupal_static(__FUNCTION__, array());
  if (!isset($schemas[$entity_type])) {
    $controller   = entity_toolbox_controller($entity_type);
    $helper       = $controller->getToolboxHelper();
    $type_schemas = $helper->schemas();
    $buffer       = array();
    foreach ($type_schemas as $schema_type => $schema) {
      if (!is_null($schema)) {
        if (!is_array($schema)) {
          $buffer[$schema_type] = $schema;
        }
        else {
          foreach ($schema as $property => $schema_) {
            $buffer[$schema_type][] = $schema_;
          }
        }
      }
    }
    $schemas[$entity_type] = $buffer;
  }

  return $schemas[$entity_type];
}