<?php

/**
 * @file
 * entity_toolbox.cache.inc
 *
 * This file provides with cache related constants and functions.
 *
 * @author kryptonboy<me@harold-cohen.com>
 */

/**
 * Cache cid for entity_toolbox cache info.
 * @see hook_entity_toolbox_cache_info().
 * @see entity_toolbox_cache_get_info().
 */
define('ENTITY_TOOLBOX__CACHE_INFO', 'entity_toolbox_cache_info');
/**
 * Cache cid for hook register info.
 * @see hook_hook_register_info().
 */
define('ENTITY_TOOLBOX__HOOK_REGISTER_INFO', 'entity_toolbox_hook_register_info');
/**
 * Cache cid for property type info.
 * @see hook_toolbox_property_type_info().
 * @see entity_toolbox_property_type_get_info().
 */
define('ENTITY_TOOLBOX__PROPERTY_TYPE_INFO', 'entity_toolbox_property_type_info');
/**
 * Cache cid for schema type info.
 * @see hook_schema_type_info().
 * @see entity_toolbox_schema_type_get_info().
 */
define('ENTITY_TOOLBOX__SCHEMA_TYPE_INFO', 'schema_type_info');
/**
 * Cache cid for callback type info.
 * @see hook_toolbox_callback_type_info().
 * @see entity_toolbox_entity_callback_type_get_info().
 */
define('ENTITY_TOOLBOX__CALLBACK_TYPE_INFO', 'callback_type_info');
/**
 * Cache cid for action type info.
 * @see hook_toolbox_action_type_info().
 * @see entity_toolbox_entity_action_type_get_info().
 */
define('ENTITY_TOOLBOX__ACTION_TYPE_INFO', 'action_type_info');
/**
 * Cache cid for class type info.
 * @see hook_class_type_info().
 */
define('ENTITY_TOOLBOX__CLASS_TYPE_INFO', 'class_type_info');
/**
 * Cache cid for toolbox entity info.
 * @see hook_entity_toolbox_entity_info().
 * @see entity_toolbox_get_info().
 */
define('ENTITY_TOOLBOX__ENTITY_INFO', 'entity_info');
/**
 * Cache cid for toolbox entity info.
 * @see hook_entity_toolbox_entity_info().
 * @see entity_toolbox_get_info().
 */
define('ENTITY_TOOLBOX__TMP_ENTITY_INFO', 'tmp_entity_info');
/**
 * Cache cid to store generated entities schemas.
 */
define('ENTITY_TOOLBOX__ENTITY_SCHEMA', 'entity_schema');
/**
 * Cache cid for entity resources info.
 * @see hook_entity_resources_info().
 * @see entity_toolbox_entity_resources_get_info().
 */
define('ENTITY_TOOLBOX__ENTITY_RESOURCES_INFO', 'entity_resources_info');
/**
 * Cache cid for entity group info.
 */
define('ENTITY_TOOLBOX__ENTITY_GROUP_INFO', 'entity_group_info');
/**
 * Cache cid for entity group attach info.
 */
define('ENTITY_TOOLBOX__ENTITY_GROUP_ATTACH_INFO', 'entity_group_attach_info');
/**
 * Cache cid for field category group info.
 */
define('ENTITY_TOOLBOX__FIELD_CATEGORY_GROUP_INFO', 'field_category_group_info');
/**
 * Cache cid for field category info.
 */
define('ENTITY_TOOLBOX__FIELD_CATEGORY_INFO', 'field_category_info');
/**
 * Cache cid for parent property info.
 */
define('ENTITY_TOOLBOX__PARENT_PROPERTY_INFO', 'parent_property_info');
/**
 * Cache cid for inheritable info.
 */
define('ENTITY_TOOLBOX__INHERITABLE_PROPERTY_INFO', 'inheritable_property_info');
/**
 * Cache cid for inherited property info.
 */
define('ENTITY_TOOLBOX__INHERITED_PROPERTY_INFO', 'inherited_property_info');
/**
 * Cache cid for inheritable info.
 */
define('ENTITY_TOOLBOX__INHERITABLE_FIELD_INFO', 'inheritable_field_info');
/**
 * Cache cid for inherited field info.
 */
define('ENTITY_TOOLBOX__INHERITED_FIELD_INFO', 'inherited_field_info');
/**
 * Cache cid fomr modules_prepared.
 * Caches whether a module is ready to be processed by ETBX.
 */
define('ETBX_CID__MODULES_PREP', 'modules_prepared');
/**
 * Cache cid for etbx dependencies.
 */
define('ETBX_CID__DEPENDENCIES_SORTED', 'dependencies_sorted');

/**
 * Implements @see hook_flush_caches().
 */
function entity_toolbox_flush_caches() {
  return array(ENTITY_TOOLBOX_DB__CACHE);
}

/**
 * Implements hook_admin_menu_cache_info().
 *
 * @see entity_toolbox_cache_clear_all().
 */
function entity_toolbox_admin_menu_cache_info() {
  $caches['entity_toolbox'] = array(
    'title'    => t('Entity toolbox'),
    'callback' => 'entity_toolbox_cache_clear_all',
  );

  return $caches;
}

/**
 * Cache data fore entity toolbox in cache_entity_toolbox.
 * Sets the cache in entity_toolbox cache table.
 *
 * @param string $cid
 *   The cache ID.
 * @param mixed  $data
 *   The data to cache.
 * @param int    $expire
 *   The expiration in seconds.
 */
function entity_toolbox_cache_set($cid, $data, $expire = CACHE_PERMANENT) {
  generic_cache_set(ENTITY_TOOLBOX_DB__CACHE, $cid, $data, $expire);
}

/**
 * Returns cache from cache_entity_toolbox.
 * Gets the cache from entity_toolbox cache table.
 *
 * @param $cid
 *   The cache ID.
 *
 * @return null|object
 */
function entity_toolbox_cache_get($cid) {
  return generic_cache_get(ENTITY_TOOLBOX_DB__CACHE, $cid);
}

/**
 * Clear entity_toolbox cache.
 * Once cleared, related cache IDs are cleared as well.
 *
 * @param string $cid
 *   The entity toolbox cache ID.
 *
 * @see hook_entity_toolbox_cache_info().
 */
function entity_toolbox_cache_clear($cid) {
  generic_cache_clear(ENTITY_TOOLBOX_DB__CACHE, $cid);
}

/**
 * Clear the cache for every entity_toolbox cache id.
 */
function entity_toolbox_cache_clear_all() {
  cache_clear_all('*', ENTITY_TOOLBOX_DB__CACHE, TRUE);
}

/**
 * Implements hook_entity_toolbox_cache_info().
 */
function entity_toolbox_cache_info() {
  $info                                                                      = array();
  $info[ENTITY_TOOLBOX_DB__CACHE][ENTITY_TOOLBOX__HOOK_REGISTER_INFO]        = array(
    'expires' => CACHE_PERMANENT
  );
  $info[ENTITY_TOOLBOX_DB__CACHE][ENTITY_TOOLBOX__CLASS_TYPE_INFO]           = array(
    'expires' => CACHE_PERMANENT
  );
  $info[ENTITY_TOOLBOX_DB__CACHE][ENTITY_TOOLBOX__PROPERTY_TYPE_INFO]        = array(
    'expires' => CACHE_PERMANENT,
  );
  $info[ENTITY_TOOLBOX_DB__CACHE][ENTITY_TOOLBOX__SCHEMA_TYPE_INFO]          = array(
    'expires' => CACHE_PERMANENT,
  );
  $info[ENTITY_TOOLBOX_DB__CACHE][ENTITY_TOOLBOX__CALLBACK_TYPE_INFO]        = array(
    'expires' => CACHE_PERMANENT,
  );
  $info[ENTITY_TOOLBOX_DB__CACHE][ENTITY_TOOLBOX__ENTITY_INFO]               = array(
    'expires' => CACHE_PERMANENT,
    'clear'   => array(
      ENTITY_TOOLBOX__ENTITY_GROUP_INFO,
      ENTITY_TOOLBOX__ENTITY_GROUP_ATTACH_INFO,
      ENTITY_TOOLBOX__INHERITABLE_PROPERTY_INFO,
      ENTITY_TOOLBOX__INHERITED_PROPERTY_INFO,
      ENTITY_TOOLBOX__INHERITABLE_FIELD_INFO,
      ENTITY_TOOLBOX__FIELD_CATEGORY_GROUP_INFO,
      ENTITY_TOOLBOX__FIELD_CATEGORY_INFO,
    ),
    'hooks'   => array(
      //@todo add hook_module_pre_install
      'module_pre_install',
    )
  );
  $info[ENTITY_TOOLBOX_DB__CACHE][ENTITY_TOOLBOX__TMP_ENTITY_INFO]           = array(
    'expires' => CACHE_PERMANENT,
    'cache'   => TRUE,
  );
  $info[ENTITY_TOOLBOX_DB__CACHE][ENTITY_TOOLBOX__PARENT_PROPERTY_INFO]      = array(
    'expires' => CACHE_PERMANENT,
  );
  $info[ENTITY_TOOLBOX_DB__CACHE][ENTITY_TOOLBOX__ENTITY_SCHEMA]             = array(
    'expires' => CACHE_PERMANENT,
    'clear'   => array(),
    'hooks'   => array(
      'module_install',
    )
  );
  $info[ENTITY_TOOLBOX_DB__CACHE][ENTITY_TOOLBOX__ENTITY_GROUP_INFO]         = array(
    'expires' => CACHE_PERMANENT,
  );
  $info[ENTITY_TOOLBOX_DB__CACHE][ENTITY_TOOLBOX__FIELD_CATEGORY_GROUP_INFO] = array(
    'expires' => CACHE_PERMANENT
  );
  $info[ENTITY_TOOLBOX_DB__CACHE][ENTITY_TOOLBOX__FIELD_CATEGORY_INFO]       = array(
    'expires' => CACHE_PERMANENT
  );
  $info[ENTITY_TOOLBOX_DB__CACHE][ENTITY_TOOLBOX__ENTITY_GROUP_ATTACH_INFO]  = array(
    'expires' => CACHE_PERMANENT,
  );
  $info[ENTITY_TOOLBOX_DB__CACHE][ENTITY_TOOLBOX__INHERITABLE_PROPERTY_INFO] = array(
    'expires' => CACHE_PERMANENT,
  );
  $info[ENTITY_TOOLBOX_DB__CACHE][ENTITY_TOOLBOX__INHERITED_PROPERTY_INFO]   = array(
    'expires' => CACHE_PERMANENT,
    'cache'   => FALSE,
  );
  $info[ENTITY_TOOLBOX_DB__CACHE][ENTITY_TOOLBOX__INHERITABLE_FIELD_INFO]    = array(
    'expires' => CACHE_PERMANENT,
  );
  $info[ENTITY_TOOLBOX_DB__CACHE][ENTITY_TOOLBOX__FIELD_CATEGORY_GROUP_INFO] = array(
    'expires' => CACHE_PERMANENT,
  );
  $info[ENTITY_TOOLBOX_DB__CACHE][ENTITY_TOOLBOX__FIELD_CATEGORY_INFO]       = array(
    'expires' => CACHE_PERMANENT,
  );
  $info[ENTITY_TOOLBOX_DB__CACHE]['entity_settings_info']                    = array(
    'expires' => CACHE_PERMANENT,
  );
  $info[ENTITY_TOOLBOX_DB__CACHE][ETBX_CID__MODULES_PREP]                    = array(
    'expires' => CACHE_PERMANENT,
  );
  $info[ENTITY_TOOLBOX_DB__CACHE][ETBX_CID__DEPENDENCIES_SORTED]             = array(
    'expires' => CACHE_PERMANENT,
  );

  return $info;
}

/**
 * Cache temporary entity_toolbox_info build for a given entity type.
 *
 * @param string $entity_type
 *   The entity type.
 * @param int    $version
 *   The tmp build version.
 * @param array  $data
 *   The build to cache.
 */
function etbx_info_tmp_cache_set($entity_type = NULL, $version = NULL, array $data) {
  $tmp_cached = entity_toolbox_cache_get(ENTITY_TOOLBOX__TMP_ENTITY_INFO);
  $tmp_cached = !empty($tmp_cached) ? $tmp_cached->data : array();
  $tmp_cache  = is_empty($tmp_cached) ? array($entity_type => $data) : $tmp_cached + array($entity_type => $data);
  entity_toolbox_cache_set(ENTITY_TOOLBOX__TMP_ENTITY_INFO, $tmp_cache);
}

/**
 * Retrieves the temporary cache for a given entity type version.
 *
 * @param null|string $entity_type
 *   The entity type.
 * @param null|string $version
 *   The entity version.
 *
 * @return null|object
 */
function etbx_info_tmp_cache_get($entity_type = NULL, $version = NULL) {
  $cid = tokens2cid(ENTITY_TOOLBOX__TMP_ENTITY_INFO, array(
    $entity_type,
    $version
  ));

  return entity_toolbox_cache_get($cid);
}

/**
 * Caches entity_toolbox_info.
 *
 * @param array       $data
 *   The data to cache.
 * @param null|string $entity_type
 *   The entity type for which to cache the info. NULL to cache all.
 * @param null|int    $version
 *   The version for which to cache the info. NULL to cache all.
 */
function entity_toolbox_info_cache_set(array $data, $entity_type = NULL, $version = NULL) {
  $cid = tokens2cid(ENTITY_TOOLBOX__ENTITY_INFO, array($entity_type, $version));
  entity_toolbox_cache_set($cid, $data);
}

/**
 * Retrieves the cache for a given entity toolbox info.
 *
 * @param null|string $entity_type
 *   The entity type.
 * @param null|string $version
 *   The entity version.
 *
 * @return null|object
 */
function entity_toolbox_info_cache_get($entity_type = NULL, $version = NULL) {
  $cid = tokens2cid(ENTITY_TOOLBOX__ENTITY_INFO, array($entity_type, $version));

  return entity_toolbox_cache_get($cid);
}