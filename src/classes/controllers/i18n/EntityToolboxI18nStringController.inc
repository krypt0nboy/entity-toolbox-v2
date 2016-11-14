<?php

require_once ENTITY_TOOLBOX_PATH . '/src/classes/helpers/entity_toolbox/EntityToolboxHelper.inc';
require_once ENTITY_TOOLBOX_PATH . '/src/classes/helpers/entity_toolbox/ToolboxPropertiesHelper.inc';
require_once ENTITY_TOOLBOX_PATH . '/src/traits/EntityParametersDependentTraits.inc';

/**
 * Class EntityToolboxI18nStringController
 */
class EntityToolboxI18nStringController extends EntityDefaultI18nStringController {
  
  use
    EntityToolboxCommonTraits,
    ModuleDependentTraits,
    EntityToolboxDependentTraits,
    EntityParametersDependentTraits,
    EntityGroupDependentTraits,
    EntityToolboxPropertiesDependentTraits;
}