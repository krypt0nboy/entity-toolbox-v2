<?php

/**
 * Class EntityInfoModelNotFieldable
 */
class EntityInfoModelNotFieldable extends EntityInfoModel {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'structure' => array(
          'fieldable' => array(
            'default' => FALSE,
          ),
          'bundle of' => array(
            'type'    => 'string',
            'default' => '%toolbox_info_bundle_of%'
          )
        )
      ),
      $args
    );
    parent::__construct($args);
  }
}