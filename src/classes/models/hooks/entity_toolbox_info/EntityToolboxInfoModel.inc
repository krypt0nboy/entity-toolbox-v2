<?php

/**
 * Class EntityToolboxInfoModel
 */
class EntityToolboxInfoModel extends HookModel {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'hook'      => 'entity_toolbox_info',
        'structure' => array(
          'entity_type'      => array(
            'type'        => 'string',
            'default'     => '%toolbox_info_entity_type%',
            'versionable' => FALSE,
          ),
          'fieldable'        => array(
            'type'        => 'boolean',
            'default'     => '%toolbox_info_fieldable%',
            'versionable' => FALSE,
          ),
          'group'            => array(
            'type'        => 'string',
            'default'     => '%toolbox_info_group%',
            'unset if'    => 'is_null:c:',
            'versionable' => FALSE,
          ),
          'has_revisions'    => array(
            'type'        => 'boolean',
            'versionable' => TRUE,
          ),
          'has_translations' => array(
            'type'        => 'boolean',
            'versionable' => TRUE,
          ),
          'exportable'       => array(
            'type'        => 'boolean',
            'versionable' => TRUE,
          ),
          'module'           => array(
            'type'        => 'string',
            'default'     => '%toolbox_info_module%',
            'versionable' => TRUE,
          ),
          'labels'           => array(
            'type'        => 'array',
            'method'      => 'buildLabels',
            'model'       => 'entity_toolbox_labels',
            'versionable' => FALSE,
          ),
          'root path'        => array(
            'type'        => 'string',
            'method'      => 'buildRootPath',
            'versionable' => TRUE,
          ),
          'classes'          => array(
            'type'        => 'array',
            'method'      => 'buildClasses',
            'default'     => '',
            'model'       => 'entity_toolbox_classes',
            'versionable' => TRUE,
          ),
          'properties'       => array(
            'type'        => 'array',
            'method'      => 'buildProperties',
            'default'     => '',
            'model'       => 'entity_toolbox_properties',
            'versionable' => TRUE,
          ),
          'tables'           => array(
            'type'        => 'array',
            'method'      => 'buildTables',
            'default'     => '',
            'model'       => 'entity_toolbox_info_tables',
            'versionable' => FALSE,
          ),
          'callbacks'        => array(
            'type'        => 'array',
            'method'      => 'buildCallbacks',
            'default'     => '',
            'model'       => '',
            'versionable' => TRUE,
          ),
          'operations'       => array(
            'type'        => 'array',
            'method'      => 'buildOperations',
            'model'       => 'entity_toolbox_operations',
            'versionable' => TRUE,
          ),
          'keys'             => array(
            'type'        => 'array',
            'method'      => 'buildKeys',
            'default'     => '',
            'model'       => '',
            'versionable' => TRUE,
          ),
          'children_inherit' => array(
            'type'        => 'array',
            'method'      => 'buildChildrenInherit',
            'versionable' => TRUE,
          ),
        )
      ), $args
    );
    parent::__construct($args);
  }
}