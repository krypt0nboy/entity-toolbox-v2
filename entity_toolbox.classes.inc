<?php

/**
 * Returns an entity type class, processed by entity toolbox.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return string
 */
function toolbox_entity_get_class($entity_type) {
  $classes = &drupal_static(__FUNCTION__, array());
  if (!isset($classes[$entity_type])) {
    $toolbox_info          = entity_toolbox_get_info($entity_type);
    $classes[$entity_type] = $toolbox_info['classes']['entity'];
  }

  return $classes[$entity_type];
}

/**
 * Returns an entity type controller class, processed by entity toolbox.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return string
 */
function toolbox_entity_get_controller_class($entity_type) {
  $classes = &drupal_static(__FUNCTION__, array());
  if (!isset($classes[$entity_type])) {
    $toolbox_info          = entity_toolbox_get_info($entity_type);
    $classes[$entity_type] = $toolbox_info['classes']['controller'];
  }

  return $classes[$entity_type];
}

/**
 * Returns an entity type ui controller class, processed by entity toolbox.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return string
 */
function toolbox_entity_get_ui_controller_class($entity_type) {
  $classes = &drupal_static(__FUNCTION__, array());
  if (!isset($classes[$entity_type])) {
    $toolbox_info          = entity_toolbox_get_info($entity_type);
    $classes[$entity_type] = $toolbox_info['classes']['ui controller'];
  }

  return $classes[$entity_type];
}

/**
 * Returns an entity type inline entity form controller class, processed by entity toolbox.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return string
 */
function toolbox_entity_get_inline_class($entity_type) {
  $classes = &drupal_static(__FUNCTION__, array());
  if (!isset($classes[$entity_type])) {
    $toolbox_info          = entity_toolbox_get_info($entity_type);
    $classes[$entity_type] = $toolbox_info['classes']['inline form controller'];
  }

  return $classes[$entity_type];
}