<?php

require_once ENTITY_TOOLBOX_PATH . '/src/classes/models/ModelBase.inc';

/**
 * Class ViewModel
 */
class ViewModel extends ModelBase {
  /**
   * ViewModel constructor.
   *
   * @param array $args
   */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'structure' => array(
        'name'        => array(
          'type'    => 'string',
          'default' => '%toolbox_info_entity_type%',
          'method'  => 'buildName',
        ),
        'description' => array(
          'type'    => 'string',
          'default' => '%view_description%',
          'method'  => 'buildDescription',
        ),
        'tag'         => array(
          'type'    => 'string',
          'default' => '%toolbox_info_labels_plural%',
        ),
        'base_table'  => array(
          'type'    => 'string',
          'default' => '%toolbox_info_tables_base%',
        ),
        'human_name'  => array(
          'type'   => 'string',
          'method' => 'buildHumanName',
        ),
        'core'        => array(
          'type'   => 'int',
          'method' => 'buildCore',
        ),
        'api_version' => array(
          'type'   => 'string',
          'method' => 'buildApiVersion',
        ),
        'disabled'    => array(
          'type'    => 'bool',
          'default' => FALSE,
          'method'  => 'buildDisabled',
        ),
        'displays'    => array(
          'type'    => 'array',
          'default' => array(),
          'method'  => 'buildDisplays',
        ),
      ),
    ), $args);
    parent::__construct($args);
  }
}