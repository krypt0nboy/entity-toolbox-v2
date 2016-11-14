<?php

/**
 * Class OperationsValueBuilderNotFieldable
 */
class EntityToolboxInfoOperationsBuilderFieldable extends EntityToolboxInfoOperationsBuilder {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'required_operations' => array(
        'add'  => array('handler' => 'EntityToolboxOperationsAddFieldable'),
        'edit' => array(
          'handler'   => 'EntityToolboxOperationsEditFieldable',
          'provision' => array(
            'menu'        => TRUE,
            'views field' => TRUE,
          ),
        ),
        'view' => array('handler' => 'EntityToolboxOperationsViewFieldable'),
      )
    ),
      $args
    );
    parent::__construct($args);
  }
}