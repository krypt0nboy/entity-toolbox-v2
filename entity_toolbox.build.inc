<?php

/**
 * @file
 *
 * This file contains functions required to build info for drupal.
 * (Eg : hook_entity_info().)
 */

///**
// * Return build info for entity_toolbox_info().
// *
// * @param string $type
// *   The entity type.
// * @param array  $info
// *   The retrieved raw entity_toolbox_info.
// *
// * @return array
// */
//function entity_toolbox_info_build($type, $info) {
//  $module           = $info['raw_data']['module'];
//  $version_dirnames = module_persistent_prepare($module);
//
//  $instanceArgs        = array(
//    'entity_type' => $type,
//    'raw_data'    => $info['raw_data'],
//    'fieldable'   => $info['raw_data']['fieldable'],
//    'module'      => $module,
//  );
//  $factoryArgs         = array(
//    'entity_type'   => $type,
//    'fieldable'     => $info['raw_data']['fieldable'],
//    'instance_args' => $instanceArgs
//  );
//
//  if ($version_dirnames) {
//    $version_dirs = module_versions_dirs($type);
//    $flip         = array_flip($version_dirs);
//    if (($version_dirs === FALSE) || empty($flip[INIT_VERSION])) {
//      $init_dir = paths_join($version_dirnames, array(INIT_VERSION));
//      if (!file_exists($init_dir)) {
//        mkdir($init_dir);
//      }
//    }
//  }
//
//  $init_raw_persistent = raw_entity_toolbox_persistent_read($type, INIT_VERSION);
//  if (!$init_raw_persistent) {
//    raw_entity_toolbox_persistent_write($type, INIT_VERSION, $info['raw_data']);
//  }
//  $init_persistent = entity_toolbox_persistent_read($type, INIT_VERSION);
//  if (!$init_persistent) {
//    $factory = hook_get_builder_factory('entity_toolbox_info', $factoryArgs);
//    /** @var EntityToolboxInfoBuilder $builder */
//    $builder         = $factory->getInstance();
//    $build           = $builder->build();
//    $init_persistent = entity_toolbox_persistent_write($type, INIT_VERSION, $build);
//
//    return $init_persistent;
//  }
//  else {
//    return $init_persistent;
//  }

//  $module               = $info['raw_data']['module'];
//  $version_dirnames     = module_persistent_prepare($module);
//  $persistent_available = $version_dirnames !== FALSE;
//  $versions             = entity_type_versions($type);
//
//  if ($persistent_available) {
//    $version_dirs         = module_versions_dirs($type);
//    $init_dir             = entity_persistent_prepare($type);
//    $persistent_available = $init_dir !== FALSE;
//    $init_raw_persistent  = raw_entity_toolbox_persistent_read($type, INIT_VERSION);
//    if (!$init_raw_persistent) {
//      raw_entity_toolbox_persistent_write($type, INIT_VERSION, $info['raw_data']);
//    }
//    else {
//    }
//    $init_persistent = entity_toolbox_persistent_read($type, INIT_VERSION);
//  }
//  $init_persistent = isset($init_persistent) ? $init_persistent : FALSE;
//  if (!$init_persistent || !$persistent_available) {
//    $instanceArgs = array(
//      'entity_type' => $type,
//      'raw_data'    => $info['raw_data'],
//      'fieldable'   => $info['raw_data']['fieldable'],
//      'module'      => $module,
//    );
//    $factoryArgs  = array(
//      'entity_type'   => $type,
//      'fieldable'     => $info['raw_data']['fieldable'],
//      'instance_args' => $instanceArgs
//    );
//    $factory      = hook_get_builder_factory('entity_toolbox_info', $factoryArgs);
//    /** @var EntityToolboxInfoBuilder $builder */
//    $builder = $factory->getInstance();
//    $build   = $builder->build();
//    if ($persistent_available) {
//      $init_persistent = entity_toolbox_persistent_write($type, INIT_VERSION, $build);
//
//      return $init_persistent;
//    }
//
//    return $build;
//  }
//  else {
//    return $init_persistent;
//  }
//}
//
///**
// * @param $entity_type
// * @return array
// */
//function entity_info_retrieve($entity_type) {
//  $toolbox_info = entity_toolbox_get_info($entity_type);
//
//  return array($entity_type => $toolbox_info['entity_info']);
//}