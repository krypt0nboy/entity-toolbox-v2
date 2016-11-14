<?php

require_once ENTITY_TOOLBOX_PATH . '/src/classes/helpers/HelperBase.inc';
require_once ENTITY_TOOLBOX_PATH . '/src/traits/EntityDependentTraits.inc';

/**
 * Class EntityToolboxHelperBase
 */
class EntityToolboxHelperBase extends HelperBase {
  use EntityDependentTraits;

}