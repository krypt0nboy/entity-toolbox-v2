<?php

/**
 * @file
 * entity_type_settings.inc
 *
 * This file provides with form build functions for entity_type_settings_form.
 *
 * @author kryptonboy <me@harold-cohen.com>
 */

/**
 * Builds form entity_type_settings.
 *
 * @param array  $form
 *   The form built by drupal_get_form().
 * @param array  $form_state
 *   The form state, passed by reference.
 * @param string $entity_type
 *   The entity type for which to build the settings form.
 *
 * @return array
 */
function entity_type_settings_form($form, &$form_state, $entity_type) {
  $settings_info = entity_settings_get_info($entity_type);
  unset($settings_info['regexp']);
  $grouped        = array_values_group_by($settings_info, 'group');
  $groups         = array_keys($grouped);
  $form['groups'] = array(
    '#type' => 'vertical_tabs',
  );
  foreach ($groups as $group) {
    $form[$group] = array(
      '#type'        => 'fieldset',
      '#title'       => machine_name2sentence($group),
      '#collapsible' => TRUE,
      '#group'       => 'groups'
    );
    foreach ($grouped[$group] as $setting => $info) {
      entity_type_setting_attach_form($entity_type, $setting, $form, $form_state);
    }
  }
  $form['actions']['submit'] = array(
    '#type'  => 'submit',
    '#value' => t('Save settings'),
  );
  $form['#submit'][]         = 'entity_type_settings_form_submit';

  return $form;
}

/**
 * Validation callback for entity_type_settings_form.
 *
 * @param array $form
 *   The form built by drupal_get_form.
 * @param array $form_state
 *   The form state, passed by reference.
 */
function entity_type_settings_form_validate($form, &$form_state) {

}

/**
 * Submit handler for entity_type_settings_form.
 *
 * @param array $form
 *   The form built by drupal_get_form.
 * @param array $form_state
 *   The form state, passed by reference.
 */
function entity_type_settings_form_submit($form, &$form_state) {
  $entity_type = $form_state['build_info']['args'][0];
  $extract     = settings_values_extract($entity_type, $form_state['values']);
  foreach ($extract as $setting => $value) {
    setting_variable_set($entity_type, $setting, $value);
  }
}