<?php

/**
 * @file
 *
 * This file provides with extract functions.
 */

/**
 * Extracts the entity type from field_ui_field_edit_form.
 *
 * @param array $form
 *   The form.
 *
 * @return string
 */
function field_ui_form_extract_entity_type($form) {
  return $form['instance']['entity_type']['#value'];
}

/**
 * Extracts the entity toolbox field settings group.
 *
 * @param $form
 *   The form.
 *
 * @return mixed
 */
function &field_ui_form_extract_entity_toolbox(&$form) {
  return $form['instance']['settings']['entity_toolbox'];
}