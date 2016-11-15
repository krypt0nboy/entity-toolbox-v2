<?php

/**
 * @file
 * etbx_registry_admin.inc
 *
 * This file provides with form build functions for etbx_registry_admin_form.
 *
 * @author kryptonboy <me@harold-cohen.com>
 */

/**
 * Builds form etbx_registry_admin.
 *
 * @param array $form
 *   The form built by drupal_get_form().
 * @param array $form_state
 *   The form state, passed by reference.
 *
 * @return array
 */
function etbx_registry_admin_form($form, &$form_state) {
  // Loads the registry.
  $registry             = etbx_registry_get_info();
  $form['entity_types'] = array('#tree' => TRUE);
  foreach ($registry as $entity_type => $type_registry) {

  }
  $form['actions']['submit'] = array(
    '#type'  => 'submit',
    '#value' => t('Save settings'),
  );
  $form['#submit'][]         = 'etbx_registry_admin_form_submit';

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
function etbx_registry_admin_form_validate($form, &$form_state) {

}

/**
 * Submit handler for entity_type_settings_form.
 *
 * @param array $form
 *   The form built by drupal_get_form.
 * @param array $form_state
 *   The form state, passed by reference.
 */
function etbx_registry_admin_form_submit($form, &$form_state) {

}