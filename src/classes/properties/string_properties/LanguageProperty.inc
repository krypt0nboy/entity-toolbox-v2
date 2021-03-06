<?php

/**
 * Class LanguageProperty
 */
class LanguageProperty extends VarcharProperty {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = array_replace_recursive(
      array(
        'default_type'  => 'varchar',
        'default_value' => array(
          'max_length' => 3,
        ),
      ),
      $args
    );
    parent::__construct($args);
  }
}