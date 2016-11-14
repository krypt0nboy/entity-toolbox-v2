<?php

/**
 * Class RevisionDrupalSchemaBuilder
 */
class RevisionDrupalSchemaBuilder extends DrupalSchemaBuilder {
  /** {{@inheritdoc}} */
  protected function buildDescription() {
    return $this->processValueTemplate('The revision table for %toolbox_info_entity_type% entities.');
  }

  /** {{@inheritdoc}} */
  protected function buildUniqueKeys() {
    $uniqueKeys        = array();
    $uniqueKeys['vid'] = array('vid');

    return $uniqueKeys;
  }
}