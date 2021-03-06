<?php

require_once 'EntityToolbox.inc';

/**
 * Class EntityToolboxFieldable
 */
class EntityToolboxFieldable extends EntityToolbox {
  /**
   * @var int $uid
   */
  public $uid;
  /**
   * @var int $created
   */
  public $created;
  /**
   * @var int $changed
   */
  public $changed;
  /**
   * @var string $name
   *   The name property.
   */
  public $name;
}