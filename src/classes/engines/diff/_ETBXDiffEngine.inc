<?php

/**
 * Class _ETBXDiffEngine
 */
class _ETBXDiffEngine {
  use EntityToolboxCommonTraits;

  /**
   * @access protected
   * @var array $source
   */
  protected $source    = array();
  /**
   * @access protected
   * @var array $update
   */
  protected $update    = array();
  protected $modelSysId;
  protected $model;
  protected $formatted = array();

  /**
   * _ETBXDiffEngine constructor.
   *
   * @param array $source
   *   The source content.
   * @param array $update
   *   The content to compare.
   */
  public function _ETBXDiffEngine(array $source, array $update) {
    $this->source = $source;
    $this->update = $update;
  }
}