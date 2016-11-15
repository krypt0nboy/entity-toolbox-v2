<?php

/**
 * @file
 * core.inc
 *
 * This file contains core functions.
 */

/**
 * Defines the current etbx api version.
 */
define('ETBX_API_VERSION', 1);
/**
 * Defines the status code for an entity type that was not found by etbx, or that is not managed by etbx.
 */
define('ENTITY_STATUS_ERROR', 0x000);
/**
 * Defines the status code for an entity type that is already installed.
 */
define('ENTITY_STATUS_INSTALLED', 0x001);
/**
 * Defines the status code for an entity type that is registered by etbx but not installed yet.
 */
define('ENTITY_STATUS_REGISTERED', 0x002);

/**
 * Returns a list of modules implementing entity_toolbox.
 *
 * @param bool $reset
 *   Whether to reset static cache.
 *
 * @return array
 */
function entity_toolbox_implement_get_info($reset = FALSE) {
  // Cached since used often.
  $implement = &drupal_static(__FUNCTION__, array());
  if (empty($implement) || $reset) {
    // List modules (both enabled/disabled).
    $modules = modules_get_list();
    foreach ($modules as $module => $data) {
      $info_              = module_parsed_info_file($module);
      $implement[$module] = !empty($info_['entity_toolbox']['toolbox_api']);
    }
    $implement = array_keys(array_filter($implement));
  }

  return $implement;
}

/**
 * Returns a list of modules implementing hook_entity_toolbox_info().
 *
 * @param bool $reset
 *   Whether to reset static cache.
 *
 * @return string[]
 *
 * @see hook_entity_toolbox_info().
 */
function modules_implement_etbx_entities_get_info($reset = FALSE) {
  // Cached since used often.
  $implement = &drupal_static(__FUNCTION__, array());
  if (empty($implement) || $reset) {
    // List modules (both enabled/disabled).
    $modules = modules_get_list();
    foreach ($modules as $module => $data) {
      // Detect if hook_entity_toolbox_info() is implemented.
      if (etbx_info_inc_load($module)) {
        $function = $module . '_entity_toolbox_info';
        if (function_exists($function)) {
          $implement[] = $module;
        }
      }
    }
  }

  return $implement;
}

/**
 * Sorts entities by dependencies to avoid errors during a build.
 *
 * @param array $data
 *   The implementations of hook_entity_toolbox_info.
 *
 * @return array
 */
function etbx_info_sort_by_dependencies(array $data) {
  // Sorting dependencies to avoid errors during build.
  $dependencies = array();
  $filtered     = array_filter_by_value($data, TRUE, 'fieldable');
  foreach ($filtered as $type => $info) {
    if (!empty($info['dependencies'])) {
      foreach ($info['dependencies'] as $dependency) {
        $dependencies[$dependency][] = $type;
      }
    }
  }
  foreach ($dependencies as $dependency => $dependents) {
    $weight                          = count($dependencies[$dependency]) * -1;
    $filtered[$dependency]['weight'] = $weight;
  }
  uasort($filtered, 'drupal_sort_weight');
  $data_ = array();
  foreach ($filtered as $f => $i) {
    $data_[$f]           = $i;
    $data_[$f . '_type'] = $data[$f . '_type'];
  }

  return $data_;
}

/**
 * Returns entities info declared through entity_toolbox.
 *
 * @param null|string $entity_type
 *   The machine_name of the entity for which to get the info or NULL to return an array for all the entities.
 * @param null|int    $update_N
 *   The update number for an entity type, or NULL to returns info with no updates.
 *
 * @see hook_entity_toolbox_entity_info().
 * @see hook_entity_toolbox_entity_info_alter().
 * @see hook_entity_toolbox_ENTITY_TYPE_properties_update_N().
 *
 * @todo handle hook_toolbox_info diffs
 * @todo handle versions
 * @todo handle diffs persistent
 * @todo handle persistent read
 *
 * @return array
 */
function entity_toolbox_get_info($entity_type = NULL, $update_N = NULL, $reset = FALSE) {
  /** @var string $HOOK */
  $HOOK = 'entity_toolbox_info';
  /** @var string $CACHEKEY */
  $CACHEKEY = ENTITY_TOOLBOX__ENTITY_INFO;

  /**
   * Cached since used very often.
   */
  static $drupal_static_fast;
  if (!isset($drupal_static_fast)) {
    $drupal_static_fast['entity_toolbox_info'] = &drupal_static(__FUNCTION__);
  }

  if ($reset) {
    entity_toolbox_cache_clear($CACHEKEY);
    $entity_toolbox_info = NULL;
  }
  else {
    $entity_toolbox_info = &$drupal_static_fast['entity_toolbox_info'];
  }

  if (empty($entity_toolbox_info)) {
    if (($cache = entity_toolbox_cache_get($CACHEKEY)) && (!$reset)) {
      $entity_toolbox_info = $cache->data;
    }
    else {
      $data    = array();
      $modules = module_implements($HOOK);
      foreach ($modules as $module) {
        $function = $module . '_' . $HOOK;
        $call     = $function();
        /**
         * @var string $t
         * @var array  $v
         */
        foreach ($call as $t => $v) {
          $v['module'] = !empty($v['module']) ? $v['module'] : $module;
          $data[$t]    = $v;
        }
      }
      // Sorting dependencies to avoid errors during build.
      $data_     = etbx_info_sort_by_dependencies($data);
      $processed = array();
      /**
       * @var string $type
       *   Matches an entity type.
       * @var array  $info
       *   The matching entity type raw info, as retrieved in module_invoke().
       */
      foreach ($data_ as $type => $info) {
        // Retrieves the info for every registered version.
        $versions = entity_toolbox_info_retrieve($type);
        // Caches each version build.
        foreach ($versions as $v_ => $v_build_) {
          entity_toolbox_info_cache_set($v_build_, $type, $v_);
        }
      }
      $entity_toolbox_info = $processed;
      entity_toolbox_cache_set($CACHEKEY, $entity_toolbox_info);
    }
  }

  if (isset($entity_type)) {
    if ($reset) {
      return !empty($entity_toolbox_info[$entity_type]) ? $entity_toolbox_info[$entity_type] : NULL;
    }
    else {
      return !empty($entity_toolbox_info[$entity_type]) ? $entity_toolbox_info[$entity_type] : entity_toolbox_get_info($entity_type, $update_N, TRUE);
    }
  }
  else {
    return $entity_toolbox_info;
  }
}

/**
 * Returns the raw entity_toolbox info for a given entity type.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $module
 *   The module managing the entity type.
 *
 * @return array
 */
function entity_toolbox_get_raw_info($entity_type, $module) {
  if (!module_is_enabled($module)) {
    if (!etbx_info_inc_load($module)) {
      goto no_raw;
    }
  }
  $function = concat($module, 'entity_toolbox_info');
  if (function_exists($function)) {
    $call = $function();
    if (!empty($call[$entity_type])) {
      return $call[$entity_type];
    }
    else {
      return array();
    }
  }
  no_raw:

  return array();
}

/**
 * Returns the equivalent of entity_get_info(),except that it does not take
 * into account entities declared through hook_entity_toolbox_info().
 * This function avoids infinite loops when reference properties are built.
 *
 * @param null|string $entity_type
 *   The entity type.
 *
 * @return array
 */
function pre_build_entity_get_info($entity_type = NULL) {
  static $drupal_static_fast;
  if (!isset($drupal_static_fast)) {
    $drupal_static_fast['entity_info'] = &drupal_static(__FUNCTION__);
  }
  $entity_info = &$drupal_static_fast['entity_info'];
  if (empty($entity_info)) {
    // Modules implementing hook_entity_info.
    $entity_info_implement = module_implements('entity_info');
    // Modules implementing hook_entity_toolbox_info.
    $toolbox_info_implement = module_implements('entity_toolbox_info');
    // Excludes the toolbox modules from being invoked below.
    $excludes    = array_intersect($entity_info_implement, $toolbox_info_implement);
    $includes    = array_diff($entity_info_implement, $excludes);
    $entity_info = array();
    foreach ($includes as $include) {
      $function = $include . '_entity_info';
      $entity_info += $function();
    }
    // Taken from entity_get_info().
    foreach ($entity_info as $name => $data) {
      $entity_info[$name] += array(
        'fieldable'        => FALSE,
        'controller class' => 'DrupalDefaultEntityController',
        'static cache'     => TRUE,
        'field cache'      => TRUE,
        'load hook'        => $name . '_load',
        'bundles'          => array(),
        'view modes'       => array(),
        'entity keys'      => array(),
        'translation'      => array(),
      );
      $entity_info[$name]['entity keys'] += array(
        'revision' => '',
        'bundle'   => '',
      );
      foreach ($entity_info[$name]['view modes'] as $view_mode => $view_mode_info) {
        $entity_info[$name]['view modes'][$view_mode] += array(
          'custom settings' => FALSE,
        );
      }
      // If no bundle key is provided, assume a single bundle, named after
      // the entity type.
      if (empty($entity_info[$name]['entity keys']['bundle']) && empty($entity_info[$name]['bundles'])) {
        $entity_info[$name]['bundles'] = array($name => array('label' => $entity_info[$name]['label']));
      }
      // Prepare entity schema fields SQL info for
      // DrupalEntityControllerInterface::buildQuery().
      if (isset($entity_info[$name]['base table'])) {
        $entity_info[$name]['base table field types']          = drupal_schema_field_types($entity_info[$name]['base table']);
        $entity_info[$name]['schema_fields_sql']['base table'] = drupal_schema_fields_sql($entity_info[$name]['base table']);
        if (isset($entity_info[$name]['revision table'])) {
          $entity_info[$name]['schema_fields_sql']['revision table'] = drupal_schema_fields_sql($entity_info[$name]['revision table']);
        }
      }
    }
  }
  if (empty($entity_type)) {
    return $entity_info;
  }
  elseif (isset($entity_info[$entity_type])) {
    return $entity_info[$entity_type];
  }
}

/**
 * Returns the entity type install status.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return int
 */
function entity_status_get_info($entity_type) {
  $etbx_entities = &drupal_static(__FUNCTION__, array());
  if (empty($etbx_entities[$entity_type])) {

  }

  return $etbx_entities[$entity_type];
}

/**
 * Returns the entity groups declared.
 *
 * @param null|string $group
 *   The entity group name or NULL to return all groups.
 *
 * @return array
 *
 * @see hook_entity_toolbox_entity_group_info().
 */
function entity_toolbox_entity_group_get_info($group = NULL) {
  $HOOK     = 'entity_group_info';
  $CACHEKEY = ENTITY_TOOLBOX__ENTITY_GROUP_INFO;

  /**
   * Cached since its used very often.
   */
  static $drupal_static_fast;
  if (!isset($drupal_static_fast)) {
    $drupal_static_fast['entity_groups'] = &drupal_static(__FUNCTION__);
  }

  $entity_groups = &$drupal_static_fast['entity_groups'];
  if (empty($entity_groups)) {
    if ($cache = entity_toolbox_cache_get($CACHEKEY)) {
      $entity_groups = $cache->data;
    }
    else {
      $groups = array();
      $data   = module_invoke_all($HOOK);
      drupal_alter($HOOK, $data);
      $groups_entities = array();
      $toolbox_invoke  = module_invoke_all('entity_toolbox_info');
      drupal_alter('entity_toolbox_info', $toolbox_invoke);
      foreach ($toolbox_invoke as $entity_type => $info) {
        if (!empty($info['group'])) {
          $groups_entities[$info['group']][] = $entity_type;
        }
      }
      foreach ($data as $name => $group_info) {
        $group_info['entity_types'] = !empty($groups_entities[$name]) ? $groups_entities[$name] : array();
        foreach (entity_toolbox_field_category_group_get_info() as $field_category_group => $field_category_group_info) {
          if ($field_category_group_info['group'] == $name) {
            $group_info['field_category_groups'][$field_category_group] = $field_category_group_info;
          }
        }
        $groups[$name] = $group_info;
      }
      $entity_groups = $groups;
      entity_toolbox_cache_set($CACHEKEY, $entity_groups);
    }
  }

  return isset($group) ? $entity_groups[$group] : $entity_groups;

}

/**
 * Returns a group attached entity types.
 *
 * @param null|string $group
 *   The group name.
 *
 * @return array
 *
 * @see hook_group_attach_info().
 * @deprecated
 */
function entity_toolbox_entity_group_attach_get_info($group = NULL) {
  $CACHEKEY = ENTITY_TOOLBOX__ENTITY_GROUP_ATTACH_INFO;

  /**
   * Cached since its used very often.
   */
  static $drupal_static_fast;
  if (!isset($drupal_static_fast)) {
    $drupal_static_fast['group_attach_info'] = &drupal_static(__FUNCTION__);
  }

  $group_attach_info = &$drupal_static_fast['group_attach_info'];
  if (empty($group_attach_info)) {
    if ($cache = entity_toolbox_cache_get($CACHEKEY)) {
      $group_attach_info = $cache->data;
    }
    else {
      $groups = array();
      $data   = module_invoke_all('entity_group_attach_info');
      drupal_alter('entity_group_attach_info', $data);
      foreach ($data as $entity_type => $group_name) {
        $groups[$group_name] = $entity_type;
      }
      $group_attach_info = $groups;
      entity_toolbox_cache_set($CACHEKEY, $group_attach_info);
    }
  }

  return isset($group) ? $group_attach_info[$group] : $group_attach_info;
}

/**
 * Returns info on a field category group.
 *
 * @param null|string $group
 *   The field category group name.
 *
 * @return array
 *
 * @see hook_entity_toolbox_field_category_group_info().
 */
function entity_toolbox_field_category_group_get_info($group = NULL) {
  $HOOK     = 'field_category_group_info';
  $CACHEKEY = ENTITY_TOOLBOX__FIELD_CATEGORY_GROUP_INFO;

  /**
   * Cached since used very often.
   */
  static $drupal_static_fast;
  if (!isset($drupal_static_fast)) {
    $drupal_static_fast['field_category_group_info'] = &drupal_static(__FUNCTION__);
  }

  $field_category_group_info = &$drupal_static_fast['field_category_group_info'];
  if (empty($field_category_group_info)) {
    if ($cache = entity_toolbox_cache_get($CACHEKEY)) {
      $field_category_group_info = $cache->data;
    }
    else {
      $groups = array();
      $data   = module_invoke_all($HOOK);
      drupal_alter($HOOK, $data);
      foreach ($data as $name => $info) {
        $groups[$name] = $info;
        foreach (entity_toolbox_field_category_get_info() as $field_category => $field_category_info) {
          if ($field_category_info['group'] == $name) {
            $groups[$name]['field_categories'][] = $field_category;
          }
        }
      }
      $field_category_group_info = $groups;
      entity_toolbox_cache_set($CACHEKEY, $field_category_group_info);
    }
  }

  return isset($group) ? $field_category_group_info[$group] : $field_category_group_info;
}

/**
 * Returns info on a field category.
 *
 * @param null|string $category
 *   The field category name.
 *
 * @return array
 *
 * @see hook_entity_toolbox_field_category_info().
 */
function entity_toolbox_field_category_get_info($category = NULL) {
  $HOOK     = 'field_category_info';
  $CACHEKEY = ENTITY_TOOLBOX__FIELD_CATEGORY_INFO;

  /**
   * Cached since used very often.
   */
  static $drupal_static_fast;
  if (!isset($drupal_static_fast)) {
    $drupal_static_fast['field_category_info'] = &drupal_static(__FUNCTION__);
  }

  $field_category_info = &$drupal_static_fast['field_category_info'];
  if (empty($field_category_info)) {
    if ($cache = entity_toolbox_cache_get($CACHEKEY)) {
      $field_category_info = $cache->data;
    }
    else {
      $groups = array();
      $data   = module_invoke_all($HOOK);
      drupal_alter($HOOK, $data);
      foreach ($data as $name => $info) {
        $groups[$name] = $info;
      }
      $field_category_info = $groups;
      entity_toolbox_cache_set($CACHEKEY, $field_category_info);
    }
  }

  return isset($category) ? $field_category_info[$category] : $field_category_info;
}

/**
 * Returns an entity type parent properties.
 *
 * @param null $entity_type
 *   The entity type, or NULL to return parent properties for all entity types.
 *
 * @return array
 */
function entity_toolbox_entity_parent_properties_get_info($entity_type = NULL) {
  $CACHEKEY = ENTITY_TOOLBOX__PARENT_PROPERTY_INFO;
  /**
   * Cached since used very often.
   */
  static $drupal_static_fast;
  if (!isset($drupal_static_fast)) {
    $drupal_static_fast['parent_property_info'] = &drupal_static(__FUNCTION__);
  }

  $parent_property_info = &$drupal_static_fast['parent_property_info'];
  if (empty($parent_property_info)) {
    if ($cache = entity_toolbox_cache_get($CACHEKEY)) {
      $parent_property_info = $cache->data;
    }
    else {
      $parents = array();
      foreach (entity_toolbox_get_info() as $type => $info) {
        foreach ($info['properties'] as $prop_name => $prop_info) {
          if (is_property_parent($type, $prop_name)) {
            $parents[$type][$prop_name] = $prop_info['reference'];
          }
        }
      }
      $parent_property_info = $parents;
      entity_toolbox_cache_set($CACHEKEY, $parent_property_info);
    }
  }

  return isset($entity_type) ? !empty($parent_property_info[$entity_type]) ? $parent_property_info[$entity_type] : array() : $parent_property_info;
}

/**
 * Returns the inheritable property of an entity type.
 *
 * @param null|string $entity_type
 *   The entity type, or NULL to return info on all entity types.
 *
 * @return array
 */
function entity_toolbox_inheritable_property_get_info($entity_type = NULL) {
  $CACHEKEY = ENTITY_TOOLBOX__INHERITABLE_PROPERTY_INFO;

  /**
   * Cached since used very often.
   */
  static $drupal_static_fast;
  if (!isset($drupal_static_fast)) {
    $drupal_static_fast['inheritable_property_info'] = &drupal_static(__FUNCTION__);
  }

  $inheritable_property_info = &$drupal_static_fast['inheritable_property_info'];
  if (empty($inheritable_property_info)) {
    if ($cache = entity_toolbox_cache_get($CACHEKEY)) {
      $inheritable_property_info = $cache->data;
    }
    else {
      $inheritable = array();
      foreach (entity_toolbox_get_info() as $type => $info) {
        $inheritable[$type] = $info['children_inherit'];
      }
      $inheritable_property_info = $inheritable;
      entity_toolbox_cache_set($CACHEKEY, $inheritable_property_info);
    }
  }

  return isset($entity_type) ? $inheritable_property_info[$entity_type] : $inheritable_property_info;
}

/**
 * Returns the inherited properties of an entity type.
 *
 * @param null $entity_type
 *   The entity type, or NULL to return properties for every entity type.
 *
 * @return array
 */
function entity_toolbox_inherited_property_get_info($entity_type = NULL) {
  $CACHEKEY = ENTITY_TOOLBOX__INHERITED_PROPERTY_INFO;

  /**
   * Cached since used very often.
   */
  static $drupal_static_fast;
  if (!isset($drupal_static_fast)) {
    $drupal_static_fast['inherited_property_info'] = &drupal_static(__FUNCTION__);
  }

  $inherited_property_info = &$drupal_static_fast['inherited_property_info'];
  if (empty($inherited_property_info)) {
    if ($cache = entity_toolbox_cache_get($CACHEKEY)) {
      $inherited_property_info = $cache->data;
    }
    else {
      $inherited = array();
      foreach (entity_toolbox_get_info() as $type => $info) {
        $buffer       = array();
        $parent_types = entity_toolbox_entity_parent_properties_get_info($type);
        if (!empty($parent_types[$type])) {
          unset($parent_types[$type]);
        }
        foreach ($parent_types as $parent_type) {
          $inheritable          = entity_toolbox_inheritable_property_get_info($parent_type);
          $inherit_             = array_diff(array_keys($info['properties']), $inheritable);
          $inherit__            = array_diff(array_keys($info['properties']), $inherit_);
          $buffer[$parent_type] = $inherit__;
        }
        $inherited[$type] = $buffer;
      }
      $inherited_property_info = $inherited;
      entity_toolbox_cache_set($CACHEKEY, $inherited_property_info);
    }
  }

  return isset($entity_type) ? $inherited_property_info[$entity_type] : $inherited_property_info;
}

/**
 * Returns fields to be inherited by children entities.
 *
 * @param null|string $entity_type
 *   The entity type.
 * @param null|string $bundle
 *   The bundle name.
 * @param null|string $field
 *   The field name.
 *
 * @return array
 *   An associative array where the keys are the entity types and the values are :
 *     - The entity type bundles : An array containing the name of inheritable fields.
 */
function entity_toolbox_inheritable_field_get_info($entity_type = NULL, $bundle = NULL, $field = NULL) {
  $CACHEKEY = ENTITY_TOOLBOX__INHERITABLE_FIELD_INFO;

  /**
   * Cached since used very often.
   */
  static $drupal_static_fast;
  if (!isset($drupal_static_fast)) {
    $drupal_static_fast['inheritable_field_info'] = &drupal_static(__FUNCTION__);
  }

  $inheritable_field_info = &$drupal_static_fast['inheritable_field_info'];
  if (empty($inheritable_field_info)) {
    if ($cache = entity_toolbox_cache_get(ENTITY_TOOLBOX__INHERITABLE_FIELD_INFO)) {
      $inheritable_field_info = $cache->data;
    }
    else {
      $inheritable = array();
      foreach (entity_toolbox_get_info() as $type => $info) {
        foreach (entity_get_types($type) as $bnd) {
          foreach (field_info_instances($type, $bnd) as $field_info_instance) {
            if (isset($field_info_instance['settings']['toolbox']['inherit'])) {
              $inheritable[$type][$bnd][] = $field_info_instance['name'];
            }
          }
        }
      }
      $inheritable_field_info = $inheritable;
      entity_toolbox_cache_set($CACHEKEY, $inheritable_field_info);
    }
  }

  if (isset($entity_type)) {
    if (isset($bundle)) {
      return isset($field) ? $inheritable_field_info[$entity_type][$bundle][$field] : $inheritable_field_info[$entity_type][$bundle];
    }
    else {
      return $inheritable_field_info[$entity_type];
    }
  }
  else {
    return $inheritable_field_info;
  }
}

/**
 * Returns fields that should inherit parent values.
 *
 * @param null|string $entity_type
 *   The entity type.
 * @param null|string $bundle
 *   The entity bundle.
 * @param null|string $field
 *   The field name.
 *
 * @return array
 */
function entity_toolbox_inherited_field_get_info($entity_type = NULL, $bundle = NULL, $field = NULL) {
  $CACHEKEY = ENTITY_TOOLBOX__INHERITED_FIELD_INFO;

  /**
   * Cached since used very often.
   */
  static $drupal_static_fast;
  if (!isset($drupal_static_fast)) {
    $drupal_static_fast['inherited_field_info'] = &drupal_static(__FUNCTION__);
  }

  $inherited_field_info = &$drupal_static_fast['inherited_field_info'];
  if (empty($inherited_field_info)) {
    if ($cache = entity_toolbox_cache_get(ENTITY_TOOLBOX__INHERITABLE_FIELD_INFO)) {
      $inherited_field_info = $cache->data;
    }
    else {
      $inherited   = array();
      $inheritable = entity_toolbox_inheritable_field_get_info();
      foreach (entity_toolbox_get_info() as $type => $info) {
        /**
         * @var string $b
         *   A bundle of $type.
         */
        foreach (entity_get_bundles($type) as $b) {
          $fields = field_info_instances($entity_type, $b);
          /**
           * @var string $f
           * @var array  $i
           */
          foreach ($fields as $f => $i) {

          }
        }
      }
      $inherited_field_info = $inherited;
      entity_toolbox_cache_set($CACHEKEY, $inherited_field_info);
    }
  }

  if (isset($entity_type)) {
    if (isset($bundle)) {
      return isset($field) ? $inherited_field_info[$entity_type][$bundle][$field] : $inherited_field_info[$entity_type][$bundle];
    }
    else {
      return $inherited_field_info[$entity_type];
    }
  }
  else {
    return $inherited_field_info;
  }

}