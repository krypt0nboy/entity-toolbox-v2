<?php

require_once 'EntityToolboxHelperBase.inc';

/**
 * Class EntityToolboxHelper
 */
class EntityToolboxHelper extends EntityToolboxHelperBase {
  /** {{@inheritdoc}} */
  const ALIAS = 'toolboxInfo';

  /*** EXTRACT ***/

  /**
   * @param array $args
   */
  public function dataToArgs(array &$args = array()) {
    $info = $this->alias();
    unset($info['entity_info']);
    foreach ($info as $key => $arg) {
      $key        = preg_replace('/\s/', '_', $key);
      $args[$key] = $arg;
    }
  }

  /*** EXTRACT END ***/

  /*** ISSERS ***/

  /**
   * @return mixed
   */
  public function isFieldable() {
    $info = $this->alias();

    return $info['fieldable'];
  }

  /**
   * @return mixed
   */
  public function isExportable() {
    $info = $this->alias();

    return $info['exportable'];
  }

  /*** ISSERS END ***/

  /*** GETTERS END ***/

  /**
   * Returns the labels.
   *
   * @return string[]
   */
  public function labels() {
    $data = $this->alias();

    return $data['labels'];
  }

  /**
   * Returns a label for a given label type.
   *
   * @param string $type
   *   The label type.
   *
   * @return string
   */
  public function label($type) {
    $labels = $this->labels();
    if (!empty($labels[$type])) {
      return $labels[$type];
    }
  }

  /**
   * Returns the entity type single label.
   *
   * @return string
   */
  public function labelSingle() {
    return $this->label('single');
  }

  /**
   * Returns the entity type plural label.
   *
   * @return string
   */
  public function labelPlural() {
    return $this->label('plural');
  }

  /**
   * Returns the entity type single label.
   *
   * @return string
   */
  public function labelSingleLowerCase() {
    return $this->label('single lowercase');
  }

  /**
   * Returns the entity type plural label.
   *
   * @return string
   */
  public function labelPluralLowerCase() {
    return $this->label('plural lowercase');
  }

  /**
   * Returns the entity type plural machine_name.
   *
   * @return string
   */
  public function machineNamePlural() {
    return $this->label('machine_name_plural');
  }

  /**
   * Returns the classes.
   *
   * @return array
   */
  public function classes() {
    $data = $this->alias();

    return $data['classes'];
  }

  /**
   * Returns a class.
   *
   * @param string $name
   *   The class to get.
   *
   * @return array
   */
  public function classGet($name) {
    $classes = $this->classes();

    if (!empty($classes[$name])) {
      return $classes[$name];
    }
  }

  /**
   * @return mixed
   */
  public function bundleOf() {
    $info = $this->alias();

    return $info['bundle_of'];
  }

  /**
   * @return mixed
   */
  public function bundleEntity() {
    $info = $this->alias();

    return $info['bundle_entity'];
  }

  /**
   * Returns the entity type root path.
   *
   * @return mixed
   */
  public function rootPath() {
    return $this->alias()['root path'];
  }

  /**
   * Returns the entity type callbacks.
   *
   * @return mixed
   */
  public function callbacksGet() {
    $info = $this->alias();

    return $info['callbacks'];
  }

  /**
   * Returns a specific callback.
   *
   * @param $callback
   */
  public function callbackGet($callback) {
    $cbacks = $this->callbacksGet();

    if (isset($cbacks[$callback])) {
      return $cbacks[$callback];
    }
  }

  /**
   * Returns the toolbox info operations.
   *
   * @param bool $real
   *   Whether to return the operations declared outside entity toolbox as well.
   *
   * @return mixed
   */
  public function operationsGet($real = FALSE) {
    $info = $this->alias();
    if (!$real) {
      return $info['operations'];
    }
    else {
      return entity_operations_get_operation_info($this->entityType);
    }
  }

  /**
   * Indicates if the entity type implements a given operation.
   *
   * @param string $operation
   *   The operation name.
   * @param bool   $real
   *   Whether to return the operations declared outside entity toolbox as well.
   *
   * @return bool
   */
  public function implementsOperation($operation, $real = FALSE) {
    $operations = $this->operationsGet($real);

    return array_key_exists($operation, $operations);
  }

  /**
   * @return string|null
   */
  public function groupName() {
    $data = $this->alias();
    if (isset($data['group'])) {
      return $data['group'];
    }
    else {
      return FALSE;
    }
  }

  public function baseSchema() {
    $data = $this->alias();

    return $data['tables']['base'];
  }

  public function revisionSchema() {
    $data = $this->alias();

    return $data['tables']['revision'];
  }

  public function relationSchemas() {
    $data = $this->alias();

    return $data['tables']['relation'];
  }

  public function relationRevisionSchemas() {
    $data = $this->alias();

    return $data['tables']['relation_revision'];
  }

  /**
   * Returns the entity type tables (schemas).
   *
   * @return array
   */
  public function schemas() {
    $data = $this->alias();

    return $data['tables'];
  }

  /*** GETTERS END ***/

  /*** HASSERS ***/

  /**
   * Indicates if the entiy type has revisions.
   *
   * @return bool
   */
  public function hasRevisions() {
    $info = $this->alias();

    return (bool) $info['has_revisions'];
  }

  /**
   * Indicates if the entity type has translations.
   *
   * @return bool
   */
  public function hasTranslations() {
    $info = $this->alias();

    return (bool) $info['has_translations'];
  }

  /*** HASSERS END ***/
}