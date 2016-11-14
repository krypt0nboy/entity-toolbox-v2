<?php

/**
 * Returns an instance of a property type.
 *
 * @param array $type
 *   The property type.
 * @param array $args
 *   The args to get the instance.
 *
 * @return EntityToolboxPropertyBase
 */
function property_type_get_instance($type, array $args = array()) {
  $args += array('property_type' => $type);
  $factory = new EntityToolboxPropertyFactory($args);

  return $factory->getInstance();
}

/**
 * Prepares the construct arguments for an instance EntityToolboxInfoBuilder.
 *
 * @param string $entity_type
 *   The entity type.
 * @param array  $raw_info
 *   The raw info.
 *
 * @return array
 */
function entity_toolbox_info_builder_args_prepare($entity_type, array $raw_info) {
  $module        = $raw_info['raw_data']['module'];
  $fieldable     = $raw_info['raw_data']['fieldable'];
  $instance_args = array(
    'entity_type' => $entity_type,
    'raw_data'    => $raw_info['raw_data'],
    'fieldable'   => $fieldable,
    'module'      => $module,
  );
  $factory_args  = array(
    'entity_type'   => $raw_info,
    'fieldable'     => $fieldable,
    'instance_args' => $instance_args
  );

  return $factory_args;
}