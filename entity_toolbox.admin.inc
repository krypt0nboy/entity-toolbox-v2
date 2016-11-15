<?php

/**
 * @file
 * entity_toolbox.admin.inc
 *
 * This file provides with ETBX admin forms and functions.
 */

/**
 * ETBX settings form.
 *
 * @param array $form
 *   The form built by drupal_get_form().
 * @param array $form_state
 *   The form state, passed by reference.
 *
 * @return array
 */
function entity_toolbox_admin_settings($form, &$form_state) {
  $form['tabs'] = array(
    '#type' => 'vertical_tabs',
  );
  // Adds a tab for global settings.
  $form['global'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Global settings'),
    '#group' => 'tabs'
  );
  // Cache enabled by default.
  $form['global']['cache_enabled'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Cache enabled'),
    '#default_value' => variable_get('cache_enabled', FALSE),
    '#prefix'        => '<p><b>Warning ! Disabling cache will have serious impacts on the website performances.</b></p>'
  );
  // Ajax entity updates enabled by default.
  $form['global']['ajax_enabled'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Ajax enabled'),
    '#default_value' => variable_get('ajax_enabled', TRUE)
  );
  // Notifications enabled by default.
  $form['global']['notifications_enabled'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Notifications enabled'),
    '#default_value' => variable_get('notifications_enabled', TRUE)
  );
  // Adds a tab for registry related settings.
  $form['registry']            = array(
    '#type'  => 'fieldset',
    '#title' => t('Registry'),
    '#group' => 'tabs'
  );
  $form['registry']['rebuild'] = array(
    '#type'   => 'submit',
    '#value'  => t('Rebuild registry'),
    '#prefix'        => '<p><b>Rebuilds the registry.</b></p><p>Rebuilding the registry will update both the registry and check for entity updates.</p>',
    '#submit' => array('etbx_registry_rebuild_submit'),
  );
  // Adds a tab for build related settings.
  $form['build']                                 = array(
    '#type'  => 'fieldset',
    '#title' => t('Build settings'),
    '#group' => 'tabs'
  );
  $form['build']['persistent']                   = array(
    '#type'        => 'fieldset',
    '#title'       => t('Persistent builds'),
    '#collapsible' => TRUE,
    '#collapsed'   => FALSE,
  );
  $form['build']['persistent']['use_persistent'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Use persistent'),
    '#default_value' => variable_get('use_persistent', TRUE),
    '#prefix'        => '<p><b>Warning ! Disabling persistent data will have serious impacts on the website performances.</b></p>'
  );

  return system_settings_form($form);
}

/**
 * Submit callback.
 *
 * @param array $form
 * @param array $form_state
 */
function etbx_registry_rebuild_submit($form, &$form_state) {
  etbx_registry_rebuild();
  drupal_set_message(t('Entity toolbox registry rebuilt.'));
}