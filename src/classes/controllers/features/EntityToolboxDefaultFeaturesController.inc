<?php

/**
 * Class EntityToolboxDefaultFeaturesController
 */
class EntityToolboxDefaultFeaturesController {
  use
    EntityToolboxCommonTraits,
    EntityDependentTraits,
    EntityToolboxDependentTraits;

  /**
   * @access protected
   * @var string $entityInfo
   *   The entity info.
   */
  protected $entityInfo;
  /**
   * @access protected
   * @var string $component
   *   The features component name.
   */
  protected $component;
  /**
   * @const string COMPONENT
   */
  const COMPONENT = '';
  /**
   * @access protected
   * @var string $prefix
   *   The component prefix.
   */
  protected $prefix;
  /**
   * @access protected
   * @var string $defaultHook
   *   The default hook.
   */
  protected $defaultHook;
  /**
   * @const string DEFAULT_HOOK
   */
  const DEFAULT_HOOK = '';

  /**
   * EntityToolboxDefaultFeaturesController constructor.
   * @param       $entityType
   * @param array $args
   */
  public function __construct($entityType = NULL, array $args = array()) {
    if (isset($entityType)) {
      $this->entityType = $entityType;
    }
  }

  /**
   * Setup method.
   *
   * @param array $args
   *   The args to set up.
   */
  public function setUp(array $args = array()) {
    $this->bulkSet($args);
  }

  /**
   * Returns the component info for hook_features_api().
   *
   * @return array
   *
   * @see hook_features_api()
   */
  static function api() {
    return array();
  }

  /**
   * Returns the export options.
   *
   * @return array
   */
  public function exportOptions() {
    return array();
  }

  /**
   * Exports the feature.
   *
   * @param        $data
   * @param        $export
   * @param string $module_name
   */
  public function export($data, &$export, $module_name = '') {
  }

  /**
   * Renders the export code.
   *
   * @param      $module
   * @param      $data
   * @param null $export
   *
   * @return array
   */
  public function exportRender($module, $data, $export = NULL) {
    return array();
  }
}