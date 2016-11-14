<?php

/**
 * @file
 * controllers.inc
 * 
 * Provides with entity group callback functions..
 * 
 * @author kryptonboy <me@harold-cohen.com>
 */

/**
 * Returns the entity group controller for an entity group.
 *
 * @param string $group
 *   The entity group name.
 *
 * @return \EntityGroupController
 */
function entity_group_get_controller($group) {
  $controllers = &drupal_static(__FUNCTION__, array());
  if (!isset($controllers[$group])) {
    $type_info = entity_toolbox_entity_group_get_info($group);
    $class     = $type_info['classes']['controller'];
    /** @var \EntityGroupController */
    $controllers[$group] = new $class($group);
  }

  return $controllers[$group];
}

/**
 * Returns a group instance.
 *
 * @param string $group_name
 *   The group name.
 *
 * @return \EntityGroup
 */
function entity_group_get_instance($group_name) {
  $group = entity_group_get_controller($group_name)->getInstance();

  return $group;
}