<?php

/**
 * @file
 *
 * This files contains all the functions used when calling an entity_toolbox hook.
 */

/**
 * Invoke hook_etbx_module_prepare().
 *
 * @param string $module
 *   The module.
 *
 * @return array
 */
function _etbx_module_prepare($module) {
  $calls = &drupal_static(__FUNCTION__, array());
  if (empty($calls)) {
    $invoke = module_implements('etbx_module_prepare');
    foreach ($invoke as $m) {
      $calls[$m] = concat($m, 'etbx_module_prepare');
    }
  }
  $called = array();
  foreach ($calls as $m => $call) {
    $called[$m] = $call($module);
  }

  return $called;
}

/**
 * Invoke hook_COMPONENT_etbx_diff_process().
 * Allows to process etbx info by component.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $module
 *   The entity's module.
 * @param array  $new
 *   The latest info to process.
 * @param array  $old
 *   The oldest info registered to compare with.
 * @param array  $diff
 *   The raw diff.
 * @param array  $formatted
 *   The formatted diff.
 */
function _etbx_diff_process_invoke($entity_type, $module, $new, $old, $diff, &$formatted) {
  $calls = &drupal_static(__FUNCTION__, array());
  if (empty($calls)) {
    $regexp    = '/^(?P<component>.+)_etbx_diff_process$/';
    $functions = get_defined_functions();
    foreach (preg_grep('/_etbx_diff_process$/', $functions['user']) as $function) {
      if (preg_match($regexp, $function, $matches)) {
        $calls[$matches['component']] = $matches['component'] . '_field_settings_attach_form';
      }
    }
  }
  foreach ($calls as $component => $call) {
    $call($entity_type, $module, $new, $old, $diff, $formatted);
  }
}

/**
 * Invokes hook_field_settings_attach_form().
 *
 * @param array $form
 * @param array $form_state
 */
function _field_settings_attach_form(&$form, &$form_state) {
  $calls = &drupal_static(__FUNCTION__, array());
  if (empty($calls)) {
    $regexp    = '/^(?P<setting_group>.+)_field_settings_attach_form$/';
    $functions = get_defined_functions();
    $calls     = array();
    foreach (preg_grep('/_field_settings_attach_form$/', $functions['user']) as $function) {
      if (preg_match($regexp, $function, $matches)) {
        $calls[$matches['setting_group']] = $matches['setting_group'] . '_field_settings_attach_form';
      }
    }
  }
  foreach ($calls as $setting_group => $call) {
    $call($form, $form_state, $setting_group);
  }
}

/**
 * Toolbox process and build hooks.
 */

/**
 * Alters a form element before it's attached to the entity form.
 *
 * @param array          $element
 *   The element to alter, passed by reference.
 * @param string         $entity_type
 *   The entity type.
 * @param \EntityToolbox $entity
 *   The entity.
 * @param string         $name
 *   The property name.
 * @param string         $form_id
 *   The entity form ID.
 * @param null|string    $widget
 *   The field widget type.
 * @param array          $options
 *   An array of options.
 *
 * @see hook_property_element_alter().
 */
function _property_element_alter(&$element, $entity_type, $entity, $name, $form_id, $widget = NULL, $options = array()) {
  //Passing the element to alter to every module implementing the hook.
  foreach (module_implements('property_element_alter') as $module) {
    $function = $module . '_property_element_alter';
    $function($element, $entity_type, $entity, $name, $form_id, $widget, $options);
  }
}

/**
 * Alters the validation of an entity property.
 *
 * @param string         $entity_type
 *   The entity type.
 * @param \EntityToolbox $entity
 *   The entity.
 * @param string         $name
 *   The property name.
 * @param array          $form
 *   The entity form, passed by reference
 * @param array          $form_state
 *   The form state, passed by reference.
 */
function _property_attach_form_validate($entity_type, $entity, $name, &$form, &$form_state) {
  foreach (module_implements('property_validate') as $module) {
    $function = $module . '_property_validate';
    $function($entity_type, $entity, $name, $form, $form_state);
  }
}

/**
 * Call the alter hooks before returning an entity edit form.
 *
 * @param array          $form
 *   The form to alter, passed by reference.
 * @param array          $form_state
 *   The form_state of the form to alter, passed by reference.
 * @param string         $entity_type
 *   The entity type.
 * @param \EntityToolbox $entity
 *   The entity.
 *
 * @see hook_type_ENTITY_TYPE_edit_form__alter().
 */
function _entity_edit_form__alter(&$form, &$form_state, $entity_type, $entity) {
  $hook = '_edit_form__alter';
  foreach (entity_toolbox_edit_form_alter_get_info() as $module => $form_alters) {
    if (in_array($entity_type, $form_alters)) {
      $function = $module . '_type_' . $entity_type . $hook;
      $function($form, $form_state, $entity_type, $entity);
    }
  }
}

/**
 * Call the alter hooks before returning an entity delete form.
 *
 * @param array          $form
 *   The form to alter, passed by reference.
 * @param array          $form_state
 *   The form_state of the form to alter, passed by reference.
 * @param string         $entity_type
 *   The entity type.
 * @param \EntityToolbox $entity
 *   The entity.
 *
 * @see hook_type_ENTITY_TYPE_delete_form__alter().
 */
function _entity_delete_form__alter(&$form, &$form_state, $entity_type, $entity) {
  $hook = '_delete_form__alter';
  foreach (entity_toolbox_delete_form_alter_get_info() as $module => $form_alters) {
    if (in_array($entity_type, $form_alters)) {
      $function = $module . '_type_' . $entity_type . $hook;
      $function($form, $form_state, $entity_type, $entity);
    }
  }
}

/**
 * Call the alter hooks before returning an entity delete form.
 *
 * @param array          $form
 *   The form to alter, passed by reference.
 * @param array          $form_state
 *   The form_state of the form to alter, passed by reference.
 * @param string         $entity_type
 *   The entity type.
 * @param \EntityToolbox $entity
 *   The entity.
 *
 * @see hook_type_ENTITY_TYPE_inline_entity_form__alter().
 */
function _entity_inline_entity_form__alter(&$form, &$form_state, $entity_type, $entity) {
  $hook = '_inline_entity_form__alter';
  foreach (entity_toolbox_inline_form_alter_get_info() as $module => $form_alters) {
    if (in_array($entity_type, $form_alters)) {
      $function = $module . '_type_' . $entity_type . $hook;
      $function($form, $form_state, $entity_type, $entity);
    }
  }
}

/**
 * Entities hooks.
 */

/**
 * Returns the modules implemented hook_entity_skip_load().
 *
 * @param string         $entity_type
 *   The entity type.
 * @param \EntityToolbox $entity
 *   The entity.
 *
 * @return array
 *   An array where the values are the module names requesting to skip the load.
 */
function _entity_skip_load($entity_type, $entity) {
  $hook  = '_entity_skip_load';
  $skips = array();

  foreach (entity_toolbox_entity_skip_load_get_info() as $module) {
    $function = $module . $hook;
    $call     = $function($entity_type, $entity);
    if ($call) {
      $skips[] = $call;
    }
  }

  return $skips;
}

/**
 * Alters the validation of an entity property.
 *
 * @param string         $entity_type
 *   The entity type.
 * @param \EntityToolbox $entity
 *   The entity.
 * @param string         $name
 *   The property name.
 * @param mixed          $value
 *   The property value to validate.
 */
function _property_validate($entity_type, $entity, $name, $value) {
  foreach (module_implements('property_validate') as $module) {
    $function = $module . '_property_validate';
    $function($entity_type, $entity, $name, $value);
  }
}

/**
 * Alters the submit of an entity property.
 *
 * @param string         $entity_type
 *   The entity type.
 * @param \EntityToolbox $entity
 *   The entity.
 * @param string         $name
 *   The property name.
 * @param array          $form
 *   The entity form, passed by reference
 * @param array          $form_state
 *   The form state, passed by reference.
 */
function _property_submit($entity_type, $entity, $name, &$form, &$form_state) {
  foreach (module_implements('property_submit') as $module) {
    $function = $module . '_property_submit';
    $function($entity_type, $entity, $name, $form, $form_state);
  }
}

/**
 * Returns the modules implementing hook_update_entity_field_settings().
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $bundle
 *   The entity bundle.
 * @param string $name
 *   The field name.
 *
 * @see hook_update_entity_field_settings().
 */
function _update_entity_field_settings($entity_type, $bundle, $name) {
  foreach (module_implements('update_entity_field_settings') as $module) {
    /** @var callable $function */
    $function = $module . '_update_entity_field_settings';
    $function($entity_type, $bundle, $name);
  }
}