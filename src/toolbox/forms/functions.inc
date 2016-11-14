<?php

/**
 * @file
 * functions.inc
 *
 * This file provides with form related functions.
 */

/**
 * Attaches an entity type settings to a form.
 *
 * @param string      $entity_type
 *   The entity type.
 * @param array       $form
 *   The form, passed by reference.
 * @param array       $form_state
 *   The form_state, passed by reference.
 * @param null|string $langcode
 *   The language code.
 * @param array       $options
 *   An array of options.
 */
function entity_type_settings_attach_form($entity_type, &$form, &$form_state, $langcode = NULL, $options = array()) {
  foreach (entity_settings_get_info($entity_type) as $setting => $info) {
    entity_type_setting_attach_form($entity_type, $setting, $form, $form_state, $langcode, $options);
  }
}

/**
 * Attaches an entity type setting to a form.
 *
 * @param string      $entity_type
 *   The entity type.
 * @param string      $setting
 *   The setting id.
 * @param array       $form
 *   The form, passed by reference.
 * @param array       $form_state
 *   The form_state, passed by reference.
 * @param null|string $langcode
 *   The language code.
 * @param array       $options
 *   An array of options.
 */
function entity_type_setting_attach_form($entity_type, $setting, &$form, &$form_state, $langcode = NULL, $options = array()) {
  $setting_info     = entity_settings_get_info($entity_type, $setting);
  $parent           = &$form[$setting_info['group']];
  $parent[$setting] = array(
    '#type'          => $setting_info['field']['#type'],
    '#title'         => $setting_info['label'],
    '#description'   => $setting_info['description'],
    '#default_value' => setting_variable_get($entity_type, $setting)
  );
}

/**
 * Attach an entity settings to a form.
 *
 * @param string         $entity_type
 *   The entity type.
 * @param \EntityToolbox $entity
 *   The entity.
 * @param array          $form
 *   The form, passed by reference.
 * @param array          $form_state
 *   The form_state, passed by reference.
 * @param string         $langcode
 *   The language code.
 * @param string[]       $options
 *   The property fields options.
 */
function entity_settings_attach_form($entity_type, $entity, &$form, &$form_state, $langcode = NULL, $options = array()) {
  foreach (entity_settings_get_info($entity_type) as $setting => $info) {
    entity_setting_attach_form($entity_type, $entity, $setting, $form, $form_state, $langcode, $options);
  }
}

/**
 * Attach an entity setting to a form.
 *
 * @param string         $entity_type
 *   The entity type.
 * @param \EntityToolbox $entity
 *   The entity.
 * @param string         $setting
 *   The setting to attach.
 * @param array          $form
 *   The form, passed by reference.
 * @param array          $form_state
 *   The form_state, passed by reference.
 * @param string         $langcode
 *   The language code.
 * @param string[]       $options
 *   The property fields options.
 */
function entity_setting_attach_form($entity_type, $entity, $setting, &$form, &$form_state, $langcode = NULL, $options = array()) {
  $setting_info = entity_setting_extract_info($entity_type, $setting);
  //identify group
  //identify tab
  $var_name = concat($setting, $entity_type);
  $var      = variable_get($var_name, !empty($setting_info['default']) ? $setting_info['default'] : NULL);
}

/**
 * Builds and attach the entity field settings.
 *
 * @param array $form
 *   The form to attach the setting to.
 * @param array $form_state
 *   The form state.
 */
function field_settings_attach_form(&$form, &$form_state) {
  //@todo handle group settings
  //@todo handle entity settings
  $form['instance']['settings']['entity_toolbox'] = array(
    '#type'   => 'vertical_tabs',
    '#prefix' => '<br><div><b>Entity toolbox field settings</b></div>',
    '#weight' => 999
  );
  require_once 'entity_toolbox.forms.field_settings.inc';
  _field_settings_attach_form($form, $form_state);
}

/**
 * Attach an entity properties to a form.
 *
 * @param string         $entity_type
 *   The entity type.
 * @param \EntityToolbox $entity
 *   The entity.
 * @param array          $form
 *   The form, passed by reference.
 * @param array          $form_state
 *   The form_state, passed by reference.
 * @param string         $langcode
 *   The language code.
 * @param string[]       $options
 *   The property fields options.
 */
function properties_attach_form($entity_type, $entity, &$form, &$form_state, $langcode = NULL, $options = array()) {
  foreach (entity_type_form_exposed_properties($entity_type, entity_form_extract_type_from_id($form['form_id'])) as $name => $info) {
    if ($info['type'] != 'entity_machine_name') {
      property_attach_form($entity_type, $entity, $name, $form, $form_state, $langcode, $options);
    }
  }
  if (entity_type_has_revisions($entity_type)) {
    $form['revision'] = array(
      '#type'          => 'checkbox',
      '#title'         => 'Create a new revision ?',
      '#default_value' => '',
    );
  }
}

/**
 * Attach a property to an entity form.
 *
 * @param string         $entity_type
 *   The entity type.
 * @param \EntityToolbox $entity
 *   The entity.
 * @param string         $name
 *   The property name.
 * @param array          $form
 *   The form, passed by reference.
 * @param array          $form_state
 *   The form_state, passed by reference.
 * @param string         $langcode
 *   The language code.
 * @param array          $options
 *   The property fields options.
 */
function property_attach_form($entity_type, $entity, $name, &$form, &$form_state, $langcode = NULL, $options = array()) {
  //Check if the property is set to be exposed for this form.
  $function = is_property_multi_value($entity_type, $name) ? 'property_multi_attach_form' : 'property_single_attach_form';
  $function($entity_type, $entity, $name, $form, $form_state, $langcode, $options);
  foreach (module_implements('property_attach_form') as $module) {
    $hook = $module . '_property_attach_form';
    $hook($entity_type, $entity, $name, $form, $form_state, $langcode, $options);
  }
}

/**
 * Attach a property to an entity form.
 *
 * @param string         $entity_type
 *   The entity type.
 * @param \EntityToolbox $entity
 *   The entity.
 * @param string         $name
 *   The property name.
 * @param array          $form
 *   The form, passed by reference.
 * @param array          $form_state
 *   The form_state, passed by reference.
 * @param string         $langcode
 *   The language code.
 * @param array          $options
 *   The property fields options.
 */
function property_single_attach_form($entity_type, $entity, $name, &$form, &$form_state, $langcode = NULL, $options = array()) {
  $info       = entity_get_info($entity_type);
  $key        = $info['entity keys'][$name];
  $form[$key] = property_element_build($entity_type, $entity, $name, $form['form_id'], NULL, $options);
}

/**
 * Attach a property to an entity form.
 *
 * @param string         $entity_type
 *   The entity type.
 * @param \EntityToolbox $entity
 *   The entity.
 * @param string         $name
 *   The property name.
 * @param array          $form
 *   The form, passed by reference.
 * @param array          $form_state
 *   The form_state, passed by reference.
 * @param string         $langcode
 *   The language code.
 * @param array          $options
 *   The property fields options.
 */
function property_multi_attach_form($entity_type, $entity, $name, &$form, &$form_state, $langcode = NULL, $options = array()) {
  $info       = entity_get_info($entity_type);
  $key        = $info['entity keys'][$name];
  $form[$key] = property_element_build($entity_type, $entity, $name, $form['form_id'], NULL, $options);
}

/**
 * Builds a property field to be used in an entity form.
 *
 * @param string         $entity_type
 *   The entity type for which the field is built.
 * @param \EntityToolbox $entity
 *   The entity for which the field is built.
 * @param string         $name
 *   The property name.
 * @param string         $form_id
 *   The form ID.
 * @param null|string    $widget
 *   The widget type, or NULL to use the property type default widget.
 * @param array          $options
 *   The options, such as js_enabled, etc...
 *
 * @return array
 *
 * @see hook_property_element_alter().
 *
 * @todo Add hook_property_element_build().
 * @todo handle multiple properties with add_more_wrapper.
 */
function property_element_build($entity_type, $entity, $name, $form_id, $widget = NULL, $options = array()) {
  $property       = entity_type_properties($entity_type, $name);
  $id             = entity_id($entity_type, $entity);
  $prop_form_info = $property['forms'][entity_form_extract_type_from_id($form_id)];
  $widget         = isset($widget) ? $widget : $prop_form_info['widget'];
  $element        = array(
    '#type'          => $widget,
    '#title'         => $property['label'],
    '#description'   => $property['description'],
    '#default_value' => entity_property_default($entity_type, $entity, $name),
    '#required'      => $prop_form_info['required'],
  );
  switch ($prop_form_info['widget']) {
    case 'select';
      $references = entity_reference_select_options($entity_type, $entity, $name);
      if (is_property_self_parent($entity_type, $name)) {
        unset($references[$id]);
      }
      $element['#empty_value'] = '-- SELECT --';
      $element['#options']     = $references;
      break;
    case 'machine_name':
      $element['#machine_name'] = array(
        'source' => array($prop_form_info['source']),
        'exists' => $prop_form_info['exists']
      );
      break;
    default:
      break;
  }

  //Let other modules alter the element.
  _property_element_alter($element, $entity_type, $entity, $name, $form_id, $widget, $options);

  return $element;
}

/**
 * Builds the ajax component of an entity field.
 *
 * @param string         $entity_type
 *   The entity type for which the field is built.
 * @param \EntityToolbox $entity
 *   The entity for which the field is built.
 * @param string         $name
 *   The property name.
 * @param string         $form_id
 *   The form ID.
 * @param null|string    $widget
 *   The widget type, or NULL to use the property type default widget.
 * @param array          $options
 *   The entity form options, such as js_enabled, etc...
 *
 * @return array
 */
function property_element_ajax_build($entity_type, $entity, $name, $form_id, $widget = NULL, $options = array()) {
  $ajax = array(
    'callback' => 'property_ajax_process',
    //@todo evaluate the type of property, widget to define which event to set
    'event'    => '',
    'effect'   => !empty($options['effect']) ? $options['effect'] : 'fade',
    'method'   => 'replace',
    //@todo add property_element_get_ajax_wrapper() function.
    'wrapper'  => '',
    //@todo add ajax progress
  );

  return $ajax;
}

/**
 * Implements hook_property_element_alter().
 */
function entity_toolbox_property_element_alter(&$element, $entity_type, $entity, $name, $form_id, $widget = NULL, $options = array()) {
  /**
   * Check if the property is to be inherited from one or more parents
   */
//  if (in_array($name, array_keys(entity_get_inherited_properties($entity_type)))) {
//    $element['#ajax'] = property_element_ajax_build($entity_type, $entity, $name, $form_id, $widget, $options);
//  }
}

/**
 * Validates a properties attached to a form.
 *
 * @param string $entity_type
 *   The entity type.
 * @param object $entity
 *   The entity to validate.
 * @param array  $form
 *   The entity form.
 * @param array  $form_state
 *   The form state, passed by reference.
 * @param array  $options
 *   The form options.
 */
function properties_attach_form_validate($entity_type, $entity, &$form, &$form_state, $options = array()) {
  foreach (entity_toolbox_get_info($entity_type)['properties'] as $name => $property) {
    property_attach_form_validate($entity_type, $entity, $form, $form_state, $options);
  }
}

/**
 * Validates a property attached to a form.
 *
 * @param string $entity_type
 *   The entity type.
 * @param object $entity
 *   The entity to validate.
 * @param string $property
 *   The property to validate.
 * @param array  $form
 *   The entity form.
 * @param array  $form_state
 *   The form state, passed by reference.
 * @param array  $options
 *   The form options.
 */
function property_attach_form_validate($entity_type, $entity, $property, $form, &$form_state, $options = array()) {
  //@todo add entity_property_validate().
  //@todo add _property_attach_form_validate()
}

/**
 * Submits properties attached to a form.
 *
 * @param string $entity_type
 *   The entity type.
 * @param object $entity
 *   The entity to validate.
 * @param array  $form
 *   The entity form.
 * @param array  $form_state entity_toolbox_ui_controller($entity_type)->entityEditFormSubmit($form, $form_state);
 *   The form state, passed by reference.
 * @param array  $options
 *   The form options.
 */
function properties_attach_form_submit($entity_type, $entity, &$form, &$form_state, $options = array()) {
  foreach (entity_toolbox_get_info($entity_type)['properties'] as $name => $property) {
    property_attach_form_submit($entity_type, $entity, $form, $form_state, $options);
  }
}

/**
 * Submits a property attached to a form.
 *
 * @param string $entity_type
 *   The entity type.
 * @param object $entity
 *   The entity to validate.
 * @param string $property
 *   The property to submit.
 * @param array  $form
 *   The entity form.
 * @param array  $form_state
 *   The form state, passed by reference.
 * @param array  $options
 *   The form options.
 */
function property_attach_form_submit($entity_type, $entity, $property, &$form, &$form_state, $options = array()) {
  //@todo _property_attach_form_submit()
}

/**
 * Process a property field returned in an AJAX query for evaluation.
 *
 * @param array  $form
 *   The entity form.
 * @param array  $form_state
 *   The entity form state.
 * @param string $name
 *   The property name.
 */
function property_ajax_process($form, &$form_state, $name) {
  //@todo add hook_property_ajax_process().
}

/**
 * Process an entity field returned in an AJAX query for evaluation.
 *
 * @param array  $form
 *   The entity form.
 * @param array  $form_state
 *   The entity form state.
 * @param string $name
 *   The field name.
 */
function field_ajax_process($form, &$form_state, $name) {
  //@todo add hook_field_ajax_process().
}

/**
 * Extract property values from an entity form.
 *
 * @param string         $entity_type
 *   The entity type.
 * @param \EntityToolbox $entity
 *   The entity.
 * @param string         $name
 *   The property name.
 * @param array          $items
 *   The property values, passed by reference.
 * @param null|string    $langcode
 *   The langcode, defaults to NULL.
 * @param array          $form
 *   The entity form.
 * @param array          $form_state
 *   The form state, passed by reference.
 */
function property_default_extract_form_values($entity_type, $entity, $name, &$items, $langcode = NULL, $form, &$form_state) {

}

/**
 * Returns the possible options for a reference property in a form.
 *
 * @param string        $entity_type
 *   The entity type.
 * @param EntityToolbox $entity
 *   The entity.
 * @param string        $name
 *   The property name.
 *
 * @return array
 */
function entity_reference_select_options($entity_type, $entity, $name) {
  $property  = entity_type_properties($entity_type, $name);
  $reference = $property['reference'];

  $options = entity_load($reference);
  $o       = array();
  foreach ($options as $id => $option) {
    $o[$id] = $option->name;
  }
  $o = array_filter($o, 'strlen');

  return $o;
}

/**
 * @param       $entity_type
 * @param       $entity
 * @param       $form
 * @param       $form_state
 * @param array $options
 */
function field_category_group_attach_form($entity_type, $entity, &$form, &$form_state, $options = array()) {
  if (($group_name = entity_type_group_name($entity_type)) !== NULL) {
    $group_info = entity_toolbox_entity_group_get_info($group_name);
    if (!empty($group_info['field_category_groups'])) {
      $group_keys                       = array_keys($group_info['field_category_groups']);
      $field_category_group_name        = reset($group_keys);
      $form[$field_category_group_name] = array(
        '#type' => 'vertical_tabs',
      );
      field_categories_attach_form($entity_type, $entity, $field_category_group_name, $form, $form_state, $options);
    }
  }
}

/**
 * @param       $entity_type
 * @param       $entity
 * @param       $group
 * @param       $form
 * @param       $form_state
 * @param array $options
 */
function field_categories_attach_form($entity_type, $entity, $group, &$form, &$form_state, $options = array()) {
  $field_category_group_info = entity_toolbox_field_category_group_get_info($group);
  $field_categories          = $field_category_group_info['field_categories'];
  foreach ($field_categories as $field_category) {
    $field_category_info   = entity_toolbox_field_category_get_info($field_category);
    $form[$field_category] = array(
      '#type'        => 'fieldset',
      '#title'       => $field_category_info['label'],
      '#collapsible' => TRUE,
      '#group'       => $group,
    );
  }
  fields_attach_form_by_category($entity_type, $entity, $form, $form_state, $options);
}

function field_category_attach_form($entity_type, $entity, $name, &$form, &$form_state, $options = array()) {

}

/**
 * @param       $entity_type
 * @param       $entity
 * @param       $form
 * @param       $form_state
 * @param array $options
 */
function fields_attach_form_by_category($entity_type, $entity, &$form, &$form_state, $options = array()) {
  if (isset($entity->type)) {
    foreach (field_info_instances($entity_type, $entity->type) as $field => $info) {
      field_attach_form_by_category($entity_type, $entity, $field, $form, $form_state);
    }
  }
}

/**
 * @param       $entity_type
 * @param       $entity
 * @param       $name
 * @param       $form
 * @param       $form_state
 * @param array $options
 */
function field_attach_form_by_category($entity_type, $entity, $name, &$form, &$form_state, $options = array()) {
  $field_info     = field_info_instance($entity_type, $name, $entity->type);
  $field_settings = $field_info['settings'];
  if (!empty($field_settings['field_category'])) {
    $field_category               = $field_settings['field_category'];
    $form[$field_category][$name] = $form[$name];
    unset($form[$name]);
  }
}

function element_empty_value_attach(&$element, $empty_value = '-- SELECT --') {
  $element['#empty_option'] = '-- SELECT --';
}