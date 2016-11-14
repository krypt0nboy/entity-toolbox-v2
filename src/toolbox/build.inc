<?php

/**
 * @file
 * build.inc
 *
 * This file provides with build callbacks.
 * Each callback is associated to a Builder.
 *
 * @see hook_hook_register_info()
 * @see BuilderBase
 */

/**
 * Returns a built hook data.
 *
 * @param string $hook
 *   The hook name.
 * @param string $entity_type
 *   The entity type.
 *
 * @return array
 */
function hook_build($hook, $entity_type) {
  $hook_info = entity_toolbox_hook_get_info($hook);

  return $hook_info['build callback']($entity_type);
}

/**
 * Returns a hook builder.
 *
 * @param $hook
 * @param $arg
 *
 * @return HookBuilder
 */
function hook_get_builder($hook, $arg) {
  return hook_get_builder_factory($hook, $arg)->getInstance();
}

/**
 * Returns a hook builder factory.
 *
 * @param $hook
 * @param $args
 *
 * @return HookBuilderFactory
 */
function hook_get_builder_factory($hook, array $args = array()) {
  require_once ENTITY_TOOLBOX_PATH . 'src/classes/factories/EntityToolboxDependentHookBuilderFactory.inc';
  $args += array('hook' => $hook);
  $hook_info    = entity_toolbox_hook_get_info($hook);
  $factoryClass = $hook_info['factory class'];
  $factory      = new $factoryClass($args);

  return $factory;
}

/**
 * Build callback for hook_entity_toolbox_info().
 * Rebuilds the data for a given entity_type.
 *
 * @param string $entity_type
 *   The entity type.
 * @param int    $version
 *   The version for which the data is built.
 *
 * @return array
 */
function entity_toolbox_info_build($entity_type, $version) {
  $raw_info     = raw_entity_toolbox_persistent_read($entity_type, $version);
  $factory_args = entity_toolbox_info_builder_args_prepare($entity_type, $raw_info);
}

/**
 * Build callback for hook_schema().
 * Rebuilds the data for a given entity_type.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return array
 */
function schema_build($entity_type) {
  $instanceArgs = array(
    'entity_type' => $entity_type,
  );
  $factoryArgs  = array(
    'entity_type'   => $entity_type,
    'instance_args' => $instanceArgs
  );
  $builder      = hook_get_builder('schema', $factoryArgs);
  $build        = $builder->build();

  return $build;
}

/**
 * Build callback for hook_entity_info().
 * Rebuilds the data for a given entity_type.
 *
 * ! Should not be called outside EntityToolboxInfoBuilder !
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return array
 */
function entity_info_build($entity_type) {
  $instanceArgs = array(
    'entity_type' => $entity_type,
  );
  $factoryArgs  = array(
    'entity_type'   => $entity_type,
    'instance_args' => $instanceArgs
  );
  $builder      = hook_get_builder('entity_info', $factoryArgs);

  return $builder->build();
}

/**
 * Build callback for hook_entity_property_info().
 * Rebuilds the data for a given entity_type.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return array
 */
function entity_property_info_build($entity_type) {
  $instanceArgs = array(
    'entity_type' => $entity_type,
  );
  $factoryArgs  = array(
    'entity_type'   => $entity_type,
    'instance_args' => $instanceArgs
  );
  $builder      = hook_get_builder('entity_property_info', $factoryArgs);

  return $builder->build();
}

/**
 * Build callback for hook_entity_property_info().
 * Rebuilds the data for a given entity_type.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return array
 */
function entity_operation_info_build($entity_type) {
  $instanceArgs = array(
    'entity_type' => $entity_type,
  );
  $factoryArgs  = array(
    'entity_type'   => $entity_type,
    'instance_args' => $instanceArgs
  );
  $builder      = hook_get_builder('entity_operation_info', $factoryArgs);

  return $builder->build();
}

/**
 * Returns build info for hook_permissions().
 *
 * @param string $entity_type
 *   The entity type for which to build the permissions.
 *
 * @return array
 *
 * @see hook_permissions().
 */
function permissions_build($entity_type) {
  $instanceArgs = array(
    'entity_type' => $entity_type,
  );
  $factoryArgs  = array(
    'entity_type'   => $entity_type,
    'instance_args' => $instanceArgs
  );
  $builder      = hook_get_builder('permissions', $factoryArgs);

  return $builder->build();
}