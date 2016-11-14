<?php

/**
 * Class LabelsValueBuilder
 */
class EntityToolboxInfoLabelsBuilder extends EntityToolboxInfoKeyBuilder {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'model_class' => 'EntityToolboxInfoLabelsRecursiveModel',
        'self_key'    => 'labels',
      ),
      $args
    );
    parent::__construct($args);
  }

  /**
   * Builds the value "single".
   *
   * @return string
   */
  protected function buildSingle() {
    return machine_name2sentence($this->entityType);
  }

  /**
   * Builds the value "plural".
   *
   * @return string
   */
  protected function buildPlural() {
    $single = machine_name2sentence($this->entityType);

    return single2plural($single);
  }

  /**
   * @return string
   */
  protected function buildMachineNamePlural() {
    return single2plural($this->entityType);
  }

  /**
   * @return string
   */
  protected function buildSingleLowerCase() {
    return lcfirst($this->getBuild('single'));
  }

  /**
   * @return string
   */
  protected function buildPluralLowerCase() {
    return lcfirst($this->getBuild('plural'));
  }

  /** {{@inheritdoc}} */
  protected function updateParentBuilderTemplateVars(array $args = array()) {
    $vars = array(
      'toolbox_info_labels_single'              => $this->getBuild('single'),
      'toolbox_info_labels_plural'              => $this->getBuild('plural'),
      'toolbox_info_labels_single_lowercase'    => $this->getBuild('single lowercase'),
      'toolbox_info_labels_plural_lowercase'    => $this->getBuild('plural lowercase'),
      'toolbox_info_labels_machine_name_plural' => $this->getBuild('machine_name plural'),
    );
    parent::updateParentBuilderTemplateVars($vars);
  }
}