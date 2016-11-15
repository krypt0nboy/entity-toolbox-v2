<?php

/**
 * @file
 * components.inc
 *
 * This file contains entity_toolbox basic hook functions.
 */

/**
 * Returns the available hooks builders info.
 *
 * @param null $hook
 *   The hook name, or NULL to return all hooks.
 *
 * @return array
 *
 * @see hook_hook_register_info().
 */
function entity_toolbox_hook_get_info($hook = NULL) {
  /** @var string $HOOK */
  $HOOK = 'hook_register_info';
  /** @var string $CACHEKEY */
  $CACHEKEY = ENTITY_TOOLBOX__HOOK_REGISTER_INFO;

  // Cached since used very often.
  static $drupal_static_fast;
  if (!isset($drupal_static_fast)) {
    $drupal_static_fast['hook_register_info'] = &drupal_static(__FUNCTION__);
  }

  $hook_register_info = &$drupal_static_fast['hook_register_info'];
  if (empty($hook_register_info)) {
    if ($cache = entity_toolbox_cache_get($CACHEKEY)) {
      $hook_register_info = $cache->data;
    }
    else {
      $data = module_invoke_all($HOOK);
      drupal_alter($HOOK, $data);
      $hook_register_info = $data;
      entity_toolbox_cache_set($CACHEKEY, $hook_register_info);
    }
  }

  return isset($hook) ? $hook_register_info[$hook] : $hook_register_info;
}

/**
 * Returns the classes types declared in entity_toolbox.
 *
 * @param string $class
 *   The class type, or NULL to return info on evert class type.
 *
 * @return array|null
 */
function entity_toolbox_class_type_get_info($class = NULL) {
  /** @var string $HOOK */
  $HOOK = 'class_type_info';
  /** @var string $CACHEKEY */
  $CACHEKEY = ENTITY_TOOLBOX__CLASS_TYPE_INFO;

  // Cached since used very often.
  static $drupal_static_fast;
  if (!isset($drupal_static_fast)) {
    $drupal_static_fast['class_type_info'] = &drupal_static(__FUNCTION__);
  }

  $class_type_info = &$drupal_static_fast['class_type_info'];
  if (empty($class_type_info)) {
    if ($cache = entity_toolbox_cache_get($CACHEKEY)) {
      $class_type_info = $cache->data;
    }
    else {
      $data = module_invoke_all($HOOK);
      drupal_alter($HOOK, $data);
      $class_type_info = $data;
      entity_toolbox_cache_set($CACHEKEY, $class_type_info);
    }
  }

  return isset($class) ? $class_type_info[$class] : $class_type_info;
}

/**
 * Returns info on an entity_toolbox property type.
 *
 * @param null $property_type
 *   The property type, or NULL to return all property types.
 *
 * @return array
 *
 * @see hook_toolbox_property_type_info().
 */
function entity_toolbox_property_type_get_info($property_type = NULL) {
  /** @var string $HOOK */
  $HOOK = 'toolbox_property_type_info';
  /** @var string $CACHEKEY */
  $CACHEKEY = ENTITY_TOOLBOX__PROPERTY_TYPE_INFO;

  // Cached since used very often.
  static $drupal_static_fast;
  if (!isset($drupal_static_fast)) {
    $drupal_static_fast['property_type_info'] = &drupal_static(__FUNCTION__);
  }

  $property_type_info = &$drupal_static_fast['property_type_info'];
  if (empty($property_type_info)) {
    if ($cache = entity_toolbox_cache_get($CACHEKEY)) {
      $property_type_info = $cache->data;
    }
    else {
      $data = module_invoke_all($HOOK);
      drupal_alter($HOOK, $data);
      $types = array();
      foreach ($data as $type => $info) {
        $types[$type] = $info;
      }

      $property_type_info = $types;
      entity_toolbox_cache_set($CACHEKEY, $property_type_info);
    }
  }

  return isset($property_type) ? $property_type_info[$property_type] : $property_type_info;
}

/**
 * Returns info on schema types (or table types), such as base table, revision table, etc...
 *
 * @param null|string $schema_type
 *   The schema type, or NULL to return info on all schema types.
 *
 * @return array
 *
 * @see hook_schema_type_info().
 */
function entity_toolbox_schema_type_get_info($schema_type = NULL) {
  /** @var string $HOOK */
  $HOOK = 'schema_type_info';
  /** @var string $CACHEKEY */
  $CACHEKEY = ENTITY_TOOLBOX__SCHEMA_TYPE_INFO;

  // Cached since used very often.
  static $drupal_static_fast;
  if (!isset($drupal_static_fast)) {
    $drupal_static_fast['schema_type_info'] = &drupal_static(__FUNCTION__);
  }

  $schema_type_info = &$drupal_static_fast['schema_type_info'];
  if (empty($schema_type_info)) {
    if ($cache = entity_toolbox_cache_get($CACHEKEY)) {
      $schema_type_info = $cache->data;
    }
    else {
      $data = module_invoke_all($HOOK);
      drupal_alter($HOOK, $data);
      $types = array();
      foreach ($data as $type => $info) {
        $types[$type] = $info;
      }
      $schema_type_info = $types;
      entity_toolbox_cache_set($CACHEKEY, $schema_type_info);
    }
  }

  return isset($schema_type) ? $schema_type_info[$schema_type] : $schema_type_info;
}

/**
 * Returns an entity callback type info.
 * Callbacks declared in the hook_toolbox_callback_type_info() are default and often required callbacks for an entity.
 *
 * @param null $type
 *   The callback type.
 *
 * @return array
 *
 * @see hook_toolbox_callback_type_info()
 */
function entity_toolbox_entity_callback_type_get_info($type = NULL) {
  /** @var string $HOOK */
  $HOOK = 'toolbox_callback_type_info';
  /** @var string $CACHEKEY */
  $CACHEKEY = ENTITY_TOOLBOX__CALLBACK_TYPE_INFO;

  // Cached since used very often.
  static $drupal_static_fast;
  if (!isset($drupal_static_fast)) {
    $drupal_static_fast['callback_type_info'] = &drupal_static(__FUNCTION__);
  }

  $callback_type_info = &$drupal_static_fast['callback_type_info'];
  if (empty($callback_type_info)) {
    if ($cache = entity_toolbox_cache_get($CACHEKEY)) {
      $callback_type_info = $cache->data;
    }
    else {
      $types = array();
      $data  = module_invoke_all($HOOK);
      drupal_alter($HOOK, $data);
      foreach ($data as $callback => $info) {
        $types[$callback] = $info;
      }
      $callback_type_info = $types;
      entity_toolbox_cache_set($CACHEKEY, $callback_type_info);
    }
  }

  return isset($type) ? $callback_type_info[$type] : $callback_type_info;
}

/**
 * Returns a module entity_toolbox settings, declared in the module's info file.
 *
 * @param string $module
 *   The module's name.
 *
 * @return mixed
 */
function entity_toolbox_module_info_get_info($module) {
  $modules = &drupal_static(__FUNCTION__, array());
  if (!in_array($module, $modules)) {
    $info_file = drupal_parse_info_file(drupal_get_path('module', $module) . '/' . $module . '.info');
    if (!empty($info_file['entity_toolbox'])) {
      $info          = $info_file['entity_toolbox'];
      $function      = $module . '_entity_toolbox_info';
      $info2obj      = new stdClass();
      $info2obj->api = $info['toolbox_api'][0];
      if (function_exists($function)) {
        $module_invoke      = $function();
        $module_entities    = array_keys($module_invoke);
        $info2obj->entities = $module_entities;
      }
      $function = $module . '_entity_group_info';
      if (function_exists($function)) {
        $module_invoke           = $function();
        $entity_groups           = array_keys($module_invoke);
        $info2obj->entity_groups = $entity_groups;
      }
      $modules[$module] = $info2obj;
    }
  }

  return $modules[$module];
}

/**
 * Returns a module entity_toolbox api, declared in the module's info file.
 *
 * @param string $module
 *   The module's name.
 *
 * @return mixed
 */
function entity_toolbox_module_api_get_info($module) {
  $modules = &drupal_static(__FUNCTION__, array());
  if (!in_array($module, $modules)) {
    $info             = entity_toolbox_module_info_get_info($module);
    $modules[$module] = $info->api;
  }

  return $modules[$module];
}

/**
 * Returns the entities managed by ETBX.
 * Note that it will only return entities that are registered && enabled && installed.
 *
 * @return array
 */
function entity_toolbox_get_entities() {
  // Cached since used very often.
  static $drupal_static_fast;
  if (!isset($drupal_static_fast)) {
    $drupal_static_fast['entity_toolbox_entities'] = &drupal_static(__FUNCTION__);
  }
  $entity_toolbox_entities = &$drupal_static_fast['entity_toolbox_entities'];
  if (empty($entity_toolbox_entities)) {
    $entity_toolbox_entities = array_keys(module_invoke_all('entity_toolbox_info'));
  }

  return $entity_toolbox_entities;
}

/**
 * Returns the module managing an entity type that is not registered yet.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return string
 */
function entity_get_module_info_pre_register($entity_type) {

}

/**
 * Returns the module managing an entity type.
 * Available only for registered entities.
 *
 * @param string $entity_type
 *   The entity type.
 * @param bool   $reset
 *   Whether to reset the cache.
 *
 * @return string|null
 */
function entity_get_module_info($entity_type, $reset = FALSE) {
  // Static cached, since used very often.
  $entities = &drupal_static(__FUNCTION__, array());
  if (empty($entities)) {
    $registry = etbx_registry_get_info();
    foreach ($registry as $type => $type_registry) {
      $entities[$type] = $type_registry['module'];
    }
  }

  return !empty($entities[$entity_type]) ? $entities[$entity_type] : NULL;
}

/**
 * Returns the module managing the entity type, even if not registered.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return string
 */
function entity_get_module_info_safe($entity_type) {
  $try = entity_get_module_info($entity_type);
  if (is_null($try)) {
    return entity_get_module_info_pre_register($entity_type);
  }
  else {
    return $try;
  }
}

/**
 * Indicates if an entity type is managed by entity toolbox.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return bool
 */
function is_entity_toolbox_entity($entity_type) {
  return in_array($entity_type, entity_toolbox_get_entities());
}

/**
 * Returns entities classes declared through entity_toolbox.
 *
 * @param null|string $entity_type
 *   The entity type, or NULL to return info on every entity type.
 * @param null|string $class
 *   The class type, or NULL to return info on every class type.
 *
 * @return array
 *
 * @see hook_entity_class_info().
 * @deprecated
 */
function entity_toolbox_get_entity_class_info($entity_type = NULL, $class = NULL) {

}

/**
 * Returns the entities settings.
 *
 * @param null|string $type
 *   The entity type.
 * @param null|string $setting
 *   The setting ID.
 * @param false|bool  $reset
 *   Whether to reset static cache or not.
 *
 * @return array
 *
 * @see hook_entity_setting_info().
 */
function entity_settings_get_info($type = NULL, $setting = NULL, $reset = FALSE) {
  /** @var string $cid */
  $cid = 'entity_settings_info';
  /** @var string $hook */
  $hook = 'entity_setting_info';

  // Cached since used very often.
  static $drupal_static_fast;
  if (!isset($drupal_static_fast)) {
    $drupal_static_fast[$cid] = &drupal_static(__FUNCTION__);
  }
  $entity_settings_info = &$drupal_static_fast[$cid];
  if ($reset) {
    $entity_settings_info = array();
    entity_toolbox_cache_clear($cid);
  }
  if (empty($entity_settings_info)) {
    if ($cache = entity_toolbox_cache_get($cid)) {
      $entity_settings_info = $cache->data;
    }
    else {
      // Invokes and alters hook_entity_settings_info.
      $invoke = invoke_and_alter($hook);
      $buffer = array();
      foreach ($invoke as $entity_type => $settings) {
        $r_buffer = !empty($settings['regexp']) ? $settings['regexp'] : NULL;
        if (isset($r_buffer)) {
          unset($settings['regexp']);
        }
        foreach ($settings as $sid => $s_info) {
          $s_info += array(
            'model'       => concat($sid, '%entity_type%'),
            'label'       => machine_name2sentence($sid),
            'description' => '',
            'group'       => 'global',
          );
          $buffer[$entity_type][$sid] = $s_info;
        }
        if ($entity_type == '*') {
          $buffer[$entity_type]['regexp'] = TRUE;
        }
        else {
          $buffer[$entity_type]['regexp'] = isset($r_buffer) ? $r_buffer : FALSE;
        }
      }

      $entity_settings_info = $buffer;
      entity_toolbox_cache_set($cid, $entity_settings_info);
    }
  }

  if (isset($type)) {
    $type_settings_info = !empty($entity_settings_info[$type]) ? $entity_settings_info[$type] + $entity_settings_info['*'] : $entity_settings_info['*'];

    return isset($setting) ? $type_settings_info[$setting] : $type_settings_info;
  }
  else {
    return $entity_settings_info;
  }
}

/**
 * @param $type
 * @param $setting
 * @return object
 */
function entity_setting_extract_info($type, $setting) {
  $setting_info = entity_settings_get_info($type, $setting);

  return (object) $setting_info;
}

/**
 * Returns the entities edit form alters.
 *
 * @return array
 */
function entity_toolbox_edit_form_alter_get_info() {
  $calls = &drupal_static(__FUNCTION__, NULL);
  if (empty($calls)) {
    $regexp    = '/^(?P<module>.+)_type_(?P<entity_type>.+)_edit_form__alter$/';
    $functions = get_defined_functions();
    $calls     = array();
    foreach (preg_grep('/__alter$/', $functions['user']) as $function) {
      if (preg_match($regexp, $function, $matches)) {
        $calls[$matches['module']][] = $matches['entity_type'];
      }
    }
  }

  return $calls;
}

/**
 * Returns the entities delete form alters.
 *
 * @return array
 */
function entity_toolbox_delete_form_alter_get_info() {
  $calls = &drupal_static(__FUNCTION__, NULL);
  if (empty($calls)) {
    $regexp    = '/^(?P<module>.+)_type_(?P<entity_type>.+)_delete_form__alter$/';
    $functions = get_defined_functions();
    $calls     = array();
    foreach (preg_grep('/__alter$/', $functions['user']) as $function) {
      if (preg_match($regexp, $function, $matches)) {
        $calls[$matches['module']][] = $matches['entity_type'];
      }
    }
  }

  return $calls;
}

/**
 * Returns the entities inline entity form alters.
 *
 * @return array
 */
function entity_toolbox_inline_form_alter_get_info() {
  $calls = &drupal_static(__FUNCTION__, NULL);
  if (empty($calls)) {
    $regexp    = '/^(?P<module>.+)_type_(?P<entity_type>.+)_inline_entity_form__alter/';
    $functions = get_defined_functions();
    $calls     = array();
    foreach (preg_grep('/__alter$/', $functions['user']) as $function) {
      if (preg_match($regexp, $function, $matches)) {
        $calls[$matches['module']][] = $matches['entity_type'];
      }
    }
  }

  return $calls;
}

/**
 * Returns the module implementing hook_entity_skip_load().
 * Used in entity_skip_load().
 *
 * @return array
 *
 * @see hook_entity_skip_load().
 * @see _entity_skip_load().
 */
function entity_toolbox_entity_skip_load_get_info() {
  $calls = &drupal_static(__FUNCTION__, NULL);
  if (empty($calls)) {
    $regexp    = '/^(?P<module>.+)_entity_skip_load$/';
    $functions = get_defined_functions();
    $calls     = array();
    foreach ($functions['user'] as $function) {
      if (preg_match($regexp, $function, $matches)) {
        $calls[] = $matches['module'];
      }
    }
  }

  return $calls;
}

/**
 * Returns an entity type operations path.
 *
 * @param string      $entity_type
 * @param null|string $op
 *
 * @return array
 */
function entity_operation_get_path($entity_type, $op = NULL) {
  $paths = &drupal_static(__FUNCTION__, array());
  if (empty($paths)) {
    foreach (entity_toolbox_get_info() as $type => $info) {
      $buffer = array();
      foreach ($info['operations'] as $operation => $op_info) {
        $handler = entity_operations_get_entity_operation_handler($type, $operation);
        if (method_exists($handler, 'basePath')) {
          $path                      = $handler->basePath();
          $buffer[$type][$operation] = $path;
        }
      }
      $paths += $buffer;
    }
  }

  return isset($op) ? $paths[$entity_type][$op] : $paths[$entity_type];
}