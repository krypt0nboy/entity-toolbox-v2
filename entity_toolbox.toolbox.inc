<?php

/**
 * @file
 * entity_toolbox.toolbox.inc
 *
 * This file provides with resources loading functions.
 */

/**
 * Loads and includes every toolbox component file.
 */
function toolbox_load() {
  module_load_include('inc', 'entity_toolbox', 'src/toolbox/build');
  module_load_include('inc', 'entity_toolbox', 'src/toolbox/components');
  module_load_include('inc', 'entity_toolbox', 'src/toolbox/core');
  module_load_include('inc', 'entity_toolbox', 'src/toolbox/db');
  module_load_include('inc', 'entity_toolbox', 'src/toolbox/deliver');
  module_load_include('inc', 'entity_toolbox', 'src/toolbox/diff');
  module_load_include('inc', 'entity_toolbox', 'src/toolbox/entity_settings');
  module_load_include('inc', 'entity_toolbox', 'src/toolbox/errors');
  module_load_include('inc', 'entity_toolbox', 'src/toolbox/help');
  module_load_include('inc', 'entity_toolbox', 'src/toolbox/hierarchy');
  module_load_include('inc', 'entity_toolbox', 'src/toolbox/install');
  module_load_include('inc', 'entity_toolbox', 'src/toolbox/lock');
  module_load_include('inc', 'entity_toolbox', 'src/toolbox/nuke');
  module_load_include('inc', 'entity_toolbox', 'src/toolbox/persistent');
  module_load_include('inc', 'entity_toolbox', 'src/toolbox/registry');
  module_load_include('inc', 'entity_toolbox', 'src/toolbox/retrieve');
  module_load_include('inc', 'entity_toolbox', 'src/toolbox/test');
  module_load_include('inc', 'entity_toolbox', 'src/toolbox/update');
  module_load_include('inc', 'entity_toolbox', 'src/toolbox/versioning');
  form_tools_load();
  entities_tools_load();
  entity_groups_tools_load();
}

/**
 * Loads the form functions files.
 */
function form_tools_load() {
  module_load_include('inc', 'entity_toolbox', 'toolbox/forms/functions');
  module_load_include('inc', 'entity_toolbox', 'toolbox/forms/extract');
  module_load_include('inc', 'entity_toolbox', 'toolbox/forms/field_settings');
}

/**
 * Loads the entities functions files.
 */
function entities_tools_load() {
  module_load_include('inc', 'entity_toolbox', 'toolbox/entities/required');
  module_load_include('inc', 'entity_toolbox', 'toolbox/entities/controllers');
  module_load_include('inc', 'entity_toolbox', 'toolbox/entities/ui');
  module_load_include('inc', 'entity_toolbox', 'toolbox/entities/entities');
}

/**
 * Loads the entity group controllers.
 */
function entity_groups_tools_load() {
  module_load_include('inc', 'entity_toolbox', 'toolbox/entity_groups/controllers');
}

/**
 * Loads and includes an etbx form.
 *
 * @param string $form_id
 *   The form ID. The form ID should be available in "src/forms" as "[form_id].inc".
 *
 * @return bool
 *   Returns TRUE if success, FALSE otherwise.
 */
function etbx_form_load($form_id) {
  $filename = file_path($form_id, ENTITY_TOOLBOX_PATH, array('src/forms'), 'inc');
  if (file_exists($filename)) {
    require_once $filename;

    return TRUE;
  }
  else {
    return FALSE;
  }
}

/**
 * Loads and includes an etbx info inc file.
 *
 * @param string $module
 *   The module containing the info.inc file.
 *
 * @return bool
 *   Returns TRUE if success, FALSE otherwise.
 */
function etbx_info_inc_load($module) {
  $path     = module_get_path($module);
  $filename = concat($module, 'info.inc', '.');
  $filepath = file_path($filename, $path);
  if (file_exists($filepath)) {
    require_once $filepath;

    return TRUE;
  }
  else {
    return FALSE;
  }
}