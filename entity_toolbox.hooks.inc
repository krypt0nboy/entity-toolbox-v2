<?php

/**
 * @file
 * entity_toolbox.hooks.inc
 * 
 * This file provides with hook invoke functions..
 * 
 * @author kryptonboy <me@harold-cohen.com>
 */

/**
 * Implements hook_permission_tpl_info().
 */
function entity_toolbox_permission_tpl_info() {
  $info                              = array();
  $info['administer_group_entities'] = array(
    'tpl'   => 'administer.%group%.entities',
    'group' => 'entities'
  );

  return $info;
}

/**
 * Implements hook_modules_installed().
 */
function entity_toolbox_modules_installed($modules) {
  //Clear the cache that needs to be cleared when this hook is invoked.
}

/**
 * Implements hook_field_create_instance().
 */
function entity_toolbox_field_create_instance($instance) {
  //Clear the cache that needs to be cleared when this hook is invoked.
}

/**
 * Implements hook_hook_register_info().
 */
function entity_toolbox_hook_register_info() {
  $info                          = array();
  $info['entity_toolbox_info']   = array(
    'build callback' => 'entity_toolbox_info_build',
    'factory class'  => 'EntityDependentHookBuilderFactory',
    'base class'     => 'EntityToolboxInfoBuilder',
    'model class'    => 'EntityToolboxInfoBuilder%fieldable%',
  );
  $info['entity_info']           = array(
    'build callback' => 'entity_info_build',
    'factory class'  => 'EntityToolboxDependentHookBuilderFactory',
    'base class'     => 'EntityInfoBuilder',
    'model class'    => 'EntityInfoBuilder%fieldable%',
  );
  $info['entity_property_info']  = array(
    'build callback' => 'entity_property_info_build',
    'factory class'  => 'EntityToolboxDependentHookBuilderFactory',
    'base class'     => 'EntityPropertyInfoBuilder',
    'model class'    => 'EntityPropertyInfoBuilder',
  );
  $info['entity_operation_info'] = array(
    'build callback' => 'entity_operation_info_build',
    'factory class'  => 'EntityToolboxDependentHookBuilderFactory',
    'base class'     => 'EntityOperationInfoBuilder',
    'model class'    => 'EntityOperationInfoBuilder%fieldable%',
  );
  $info['schema']                = array(
    'build callback' => 'schema_build',
    'factory class'  => 'EntityToolboxDependentHookBuilderFactory',
    'base class'     => 'SchemaBuilder',
    'model class'    => 'SchemaBuilder%fieldable%',
  );
  $info['menu']                  = array(
    'build callback' => 'menu_build',
    'factory class'  => 'HookBuilderFactory',
    'base class'     => 'MenuBuilder',
  );
  $info['permission']            = array(
    'build callback' => 'permission_build',
    'factory class'  => 'HookBuilderFactory',
    'base class'     => 'PermissionBuilder',
  );
  $info['theme']                 = array(
    'build callback' => 'theme_build',
    'factory class'  => 'HookBuilderFactory',
    'base class'     => 'ThemeBuilder',
  );
  $info['hook_info']             = array(
    'build callback' => 'hook_info_build',
    'factory class'  => 'HookBuilderFactory',
    'base class'     => 'HookInfoBuilder',
  );

  return $info;
}

/**
 * Implements hook_class_type_info().
 */
function entity_toolbox_class_type_info() {
  $info                  = array();
  $info['entity']        = array(
    'base class' => 'EntityToolbox%fieldable%',
    'default'    => array(
      'class' => '%class_base_class%',
      'path'  => '%toolbox_info_module_path%/src/classes/entities',
      'file'  => '%class_base_class%.inc',
    ),
  );
  $info['controller']    = array(
    'base class' => 'EntityToolboxController%fieldable%',
    'default'    => array(
      'class' => '%class_base_class%Controller',
      'path'  => '%toolbox_info_module_path%/src/classes/controllers',
      'file'  => '%class_base_class%Controller.inc',
    ),
  );
  $info['ui controller'] = array(
    'base class' => 'EntityToolboxUiController%fieldable%',
    'default'    => array(
      'class' => '%class_base_class%UiController',
      'path'  => '%toolbox_info_module_path%/src/classes/controllers',
      'file'  => '%class_base_class%UiController.inc',
    ),
  );

  return $info;
}

/**
 * Implements hook_toolbox_property_type_info().
 *
 * Returns info on property types required by entity toolbox.
 */
function entity_toolbox_toolbox_property_type_info() {
  $info                          = array();
  $info['string']                = array(
    'base class' => 'StringProperty',
  );
  $info['varchar']               = array(
    'base class' => 'VarcharProperty',
  );
  $info['machine_name']          = array(
    'base class' => 'MachineNameProperty',
  );
  $info['language']              = array(
    'base class' => 'LanguageProperty',
  );
  $info['bundle']                = array(
    'base class' => 'BundleProperty',
  );
  $info['alphanumeric']          = array(
    'base class' => 'AlphaNumericProperty',
  );
  $info['entity_machine_name']   = array(
    'base class'  => 'EntityMachineNameProperty',
    'model class' => 'EntityMachineNameProperty%fieldable%',
  );
  $info['entity_human_name']     = array(
    'base class'  => 'EntityHumanNameProperty',
    'model class' => 'EntityHumanNameProperty%fieldable%',
  );
  $info['text']                  = array(
    'base class' => 'TextProperty',
  );
  $info['small_text']            = array(
    'base class' => 'SmallTextProperty',
  );
  $info['medium_text']           = array(
    'base class' => 'mediumTextProperty',
  );
  $info['long_text']             = array(
    'base class' => 'LongTextProperty',
  );
  $info['numeric']               = array(
    'base class' => 'NumericProperty',
  );
  $info['int']                   = array(
    'base class' => 'IntegerProperty',
  );
  $info['weight']                = array(
    'base class' => 'WeightProperty',
  );
  $info['float']                 = array(
    'base class' => 'FloatProperty',
  );
  $info['decimal']               = array(
    'base class' => 'DecimalProperty',
  );
  $info['boolean']               = array(
    'base class' => 'BooleanProperty',
  );
  $info['status']                = array(
    'base class' => 'StatusProperty',
  );
  $info['entity_id']             = array(
    'base class'  => 'IdProperty',
    'model class' => 'IdProperty%fieldable%',
  );
  $info['entity_revision_id']    = array(
    'base class' => 'RevisionIdProperty',
  );
  $info['entity_translation_id'] = array(
    'base class' => 'TranslationIdProperty',
  );
  $info['entity_weight']         = array(
    'base class' => 'EntityWeightProperty',
  );
  $info['date']                  = array(
    'base class' => 'DateProperty'
  );
  $info['timestamp']             = array(
    'base class' => 'TimeStampProperty'
  );
  $info['created']               = array(
    'base class' => 'CreationTimeStampProperty'
  );
  $info['updated']               = array(
    'base class' => 'UpdateTimeStampProperty'
  );
  $info['duration']              = array(
    'base class' => 'DurationProperty'
  );
  $info['object']                = array(
    'base class' => 'ObjectProperty'
  );
  $info['reference']             = array(
    'base class' => 'EntityProperty'
  );
  $info['author']                = array(
    'base class' => 'AuthorProperty'
  );
  $info['display']               = array(
    'base class' => 'DisplayProperty'
  );
  $info['parent']                = array(
    'base class' => 'ParentEntityProperty'
  );
  $info['self_parent']           = array(
    'base class' => 'SelfParentEntityProperty'
  );

  return $info;
}

/**
 * Implements hook_schema_type_info().
 */
function entity_toolbox_schema_type_info() {
  $info                      = array();
  $info['base']              = array(
    'base class'  => 'SchemaBaseBuilder',
    'class model' => 'SchemaBaseBuilder%fieldable%'
  );
  $info['revision']          = array(
    'base class'  => 'SchemaRevisionBuilder',
    'class model' => 'SchemaRevisionBuilder%fieldable%'
  );
  $info['relation']          = array(
    'base class'  => 'SchemaRelationBuilder',
    'class model' => 'SchemaRelationBuilder%fieldable%'
  );
  $info['relation_revision'] = array(
    'base class'  => 'SchemaRelationRevisionBuilder',
    'class model' => 'SchemaRelationRevisionBuilder%fieldable%'
  );

  return $info;
}

/**
 * Implements hook_toolbox_callback_type_info().
 */
function entity_toolbox_toolbox_callback_type_info() {
  $info           = array();
  $info['create'] = array(
    'name'    => '%entity_type%_create',
    'default' => 'entity_toolbox_create',
  );
  $info['access'] = array(
    'name'    => '%entity_type%_access',
    'default' => 'entity_toolbox_access',
  );
  $info['uri']    = array(
    'name'    => '%entity_type%_uri',
    'default' => 'entity_toolbox_uri',
  );
  $info['page']   = array(
    'name'    => '%entity_type%_page',
    'default' => 'entity_toolbox_page',
  );
  $info['label']  = array(
    'name'    => '%entity_type%_label',
    'default' => 'entity_toolbox_label',
  );

  return $info;
}

///**
// * Implements hook_entity_info_alter().
// */
//function entity_toolbox_entity_info_alter(&$entity_info) {
//  //@todo replace with builder
//  foreach ($entity_info as $type => $i) {
//    if (is_entity_toolbox_entity($type)) {
//      $info = &$entity_info[$type];
//      if (entity_type_is_fieldable($type)) {
//        $function  = entity_type_callbacks($type, 'get_types');
//        $get_types = $function();
//        /** @var EntityToolboxNotFieldable $bundle */
//        foreach ($get_types as $bundle) {
//          $type_                          = $bundle->entityType();
//          $real_path                      = paths_join(entity_type_root_path($type_), array(
//            'manage',
//            $bundle->type
//          ), FALSE);
//          $info['bundles'][$bundle->type] = array(
//            'label' => $bundle->label,
//            'admin' => array(
//              'path'             => paths_join(entity_type_root_path($type_), array(
//                'manage',
//                "%$type_"
//              ), FALSE),
//              'real path'        => $real_path,
//              'bundle argument'  => path_head_pos($real_path),
//              'access arguments' => array('access administration pages'),
//            ),
//          );
//        }
//      }
//    }
//  }
//}

/**
 * Implements hook_entity_setting_info().
 */
function entity_toolbox_entity_setting_info() {
  $info      = array();
  $info['*'] = array(
    'auto_revision' => array(
      'description' => 'Automatically create a new revision when editing a product ?',
      'type'        => 'boolean',
      'default'     => TRUE,
      'field'       => array(
        '#type' => 'checkbox',
      )
    ),
    'lock_entity'   => array(
      'description' => 'Lock entity after inserting ?',
      'type'        => 'boolean',
      'default'     => FALSE,
      'group'       => 'access',
      'field'       => array(
        '#type' => 'checkbox',
      )
    )
  );

  return $info;
}

/**
 * Implements hook_form_FORMID_alter().
 */
function entity_toolbox_form_field_ui_field_edit_form_alter(&$form, &$form_state) {
  $entity_type      = field_ui_form_extract_entity_type($form);
  $toolbox_entities = entity_toolbox_get_entities();
  if (in_array($entity_type, $toolbox_entities)) {
    field_settings_attach_form($form, $form_state);
  }
}