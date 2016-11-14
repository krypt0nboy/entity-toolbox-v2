<?php

/**
 * @file
 * entity_settings.inc
 *
 * This file provides with entity_settings related functions.
 */

/**
 * Returns an entity type setting variable.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $setting
 *   The setting ID.
 *
 * @return mixed
 */
function setting_variable_get($entity_type, $setting) {
  $setting_info = entity_settings_get_info($entity_type, $setting);
  $var_name     = concat($setting, $entity_type);
  $default      = !empty($setting_info['default']) ? $setting_info['default'] : NULL;
  $var          = variable_get($var_name, $default);

  return $var;
}

/**
 * Returns an entity type setting variable.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $setting
 *   The setting ID.
 * @param mixed  $value
 *   The value to set.
 */
function setting_variable_set($entity_type, $setting, $value) {
  $var_name = concat($setting, $entity_type);
  variable_set($var_name, $value);
}

/**
 * Extracts the settings values from an array of a form values.
 *
 * @param string $entity_type
 *   The entity type.
 * @param array  $values
 *   The form values.
 *
 * @return array
 */
function settings_values_extract($entity_type, $values) {
  $settings_info = entity_settings_get_info($entity_type);
  unset($settings_info['regexp']);
  $settings = array_keys($settings_info);
  $extract  = array_intersect_key($values, array_flip($settings));

  return $extract;
}