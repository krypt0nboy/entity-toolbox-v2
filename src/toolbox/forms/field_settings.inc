<?php

/**
 * @file
 *
 * This file provides with field settings related functions.
 */

/**
 * Implements hook_field_settings_attach_form().
 *
 * Build and attaches a field ui form to add heritage settings.
 */
function heritage_field_settings_attach_form(&$form, &$form_state, $setting_group) {
  $settings                                  = &field_ui_form_extract_entity_toolbox($form);
  $settings['heritage']                      = array(
    '#type'  => 'fieldset',
    '#title' => 'Heritage',
  );
  $settings['heritage']['children_inherit']  = array(
    '#type'        => 'checkbox',
    '#title'       => t('Children inherit'),
    '#description' => t('Children inherit the field value ?'),
  );
  $settings['heritage']['children_override'] = array(
    '#type'        => 'checkbox',
    '#title'       => t('Children override'),
    '#description' => t('Children can override the inherited value ?'),
  );
}

/**
 * Implements hook_field_settings_attach_form().
 */
function field_category_field_settings_attach_form(&$form, &$form_state, $setting_group) {
  $entity_type = field_ui_form_extract_entity_type($form);
  if (($entity_group = entity_type_group_name($entity_type))) {
    $group_info = entity_toolbox_entity_group_get_info($entity_group);
    if (!empty($group_info['field_category_groups'])) {
      $group_keys                             = array_keys($group_info['field_category_groups']);
      $field_category_group_name              = reset($group_keys);
      $field_category_group_info              = entity_toolbox_field_category_group_get_info($field_category_group_name);
      $field_categories                       = $field_category_group_info['field_categories'];
      $settings                               = &field_ui_form_extract_entity_toolbox($form);
      $settings['category']                   = array(
        '#type'  => 'fieldset',
        '#title' => 'Category',
      );
      $settings['category']['field_category'] = array(
        '#type'          => 'select',
        '#title'         => t('Field category'),
        '#options'       => array_fill_keys_mirror($field_categories),
        '#empty_value'   => '',
        '#default_value' => !empty($form['#instance']['settings']['entity_toolbox']['category']['field_category']) ? $form['#instance']['settings']['entity_toolbox']['category']['field_category'] : ''
      );
    }
  }
}