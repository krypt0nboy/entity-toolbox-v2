<?php

require_once 'EntityToolboxOperationsView.inc';

/**
 * Class EntityToolboxOperationsView
 */
class EntityToolboxOperationsViewFieldable extends EntityToolboxOperationsView {
  /** {{@inheritdoc}} */
  public function userAccess($entity_type, $entity, $params = array(), $account = NULL) {
    //@todo actually handle access
    return TRUE;
  }
}