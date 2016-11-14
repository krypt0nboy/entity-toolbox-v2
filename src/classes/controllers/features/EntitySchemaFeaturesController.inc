<?php

require_once 'EntityToolboxDefaultFeaturesController.inc';

/**
 * Class EntitySchemaFeaturesController
 */
class EntitySchemaFeaturesController extends EntityToolboxDefaultFeaturesController {
  /**
   * @access protected
   * @var string $component
   *   The features component name.
   */
  protected $component = 'schemas';
  const COMPONENT = 'schemas';
  protected $defaultHook = 'schema_test';
  const DEFAULT_HOOK = 'schema_test';

  /** {{@inheritdoc}} */
  static function api() {
    return array(
      'name'         => machine_name2sentence(self::COMPONENT),
      'default_hook' => self::DEFAULT_HOOK,
    );
  }

  /** {{@inheritdoc}} */
  public function exportOptions() {
    $options = array();
    foreach (entity_toolbox_get_info() as $type => $info) {
      $schemas = entity_type_schemas($type);
      foreach ($schemas as $schemaType => $schema) {
        if (is_array($schema)) {
          foreach ($schema as $item) {
            $tr           = concat($type, $item, '-');
            $options[$tr] = concat($item, "($schemaType)", ' - ');
          }
        }
        else {
          $tr           = concat($type, $schema, '-');
          $options[$tr] = concat($schema, "($schemaType)", ' - ');
        }
      }
    }
    asort($options);

    return $options;
  }

  /** {{@inheritdoc}} */
  public function export($data, &$export, $module_name = '') {
    $pipe     = array();
    $toExport = array();
    foreach ($data as $item => $i) {
      $split                    = explode('-', $i);
      $entity_type              = $split[0];
      $schema_name              = $split[1];
      $toExport[$entity_type][] = $schema_name;
    }
    foreach ($toExport as $type => $schema_names) {

    }

    return $pipe;
  }

  /** {{@inheritdoc}} */
  public function exportRender($module, $data, $export = NULL) {
    return array();
  }
}