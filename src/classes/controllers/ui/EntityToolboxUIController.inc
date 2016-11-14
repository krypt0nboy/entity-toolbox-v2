<?php

/**
 * @file
 *
 * This file contains default entity toolbox entity UI controller classes.
 */

/**
 * Class EntityToolboxUIController
 *
 * This class is based on \EntityDefaultUIController.
 * Either \EntityToolboxFieldableUIController or \EntityToolboxNotFieldableUIController should be implemented in code.
 */
class EntityToolboxUIController extends EntityOperationsDefaultAdminUIController {
  use
    EntityToolboxCommonTraits,
    ModuleDependentTraits,
    EntityToolboxDependentTraits,
    EntityGroupDependentTraits,
    EntityToolboxPropertiesDependentTraits;

  /**
   * @var string $wildcard
   */
  protected $wildcard;
  /**
   * @var array $formsIds
   */
  protected $formsIds = array();
  /**
   * @var array $formsSettings
   */
  protected $formsSettings = array();
  /**
   * @var string $statusKey
   */
  protected $statusKey;

  /**
   * EntityToolboxUIController constructor.
   *
   * @param string $entity_type
   *   The entity type. * Entity Toolbox provides
   * @param array  $entity_info
   *   The entity info passed by entity_get_info().
   *
   * @see entity_get_info().
   */
  public function __construct($entity_type, $entity_info) {
    parent::__construct($entity_type, $entity_info);
    $this->toolboxInfo = entity_toolbox_get_info($this->entityType);
    $this->path        = $this->toolboxInfo['root path'];
    $this->id_count    = count(explode('/', $this->path));
    $this->wildcard    = isset($this->entityInfo['admin ui']['menu wildcard']) ? $this->entityInfo['admin ui']['menu wildcard'] : "%$this->entityType";
    $this->setToolboxHelper(new EntityToolboxHelper(array('data_holder' => $this)));
  }

  public function hook_menu() {
    $items = EntityDefaultUIController::hook_menu();

    // Sigh... have to get this all over again.
    $wildcard = isset($this->entityInfo['admin ui']['menu wildcard']) ? $this->entityInfo['admin ui']['menu wildcard'] : '%entity_object';

    $operations = entity_operations_get_operation_info($this->entityType);

    // TODO: check for handlers rather than paths, since these can be custom.
    // However, the handler classes could be subclasses! And also we have two
    // classes of our own to check for 'add' and 'edit'.
    if (isset($operations['add'])) {
      // Change the admin UI 'add' menu item to go to the operation handler, so
      // it becomes effectively just a clone of the menu item for 'ENTITY/add'.

      // We have to repeat a fair bit of work from
      // EntityOperationsDefaultUIController to get the menu item for the
      // 'add' operation.
      $add_operation_handler = entity_operations_get_entity_operation_handler($this->entityType, 'add');
      // Though we give a different loader position to the operation to use for
      // its menu item.
      $operation_loader_position = count(explode('/', $this->path));
      $add_menu_item             = $add_operation_handler->menu_item('add', $operations['add'], $operation_loader_position);

      // Change the page and access callbacks to those from the operation menu
      // item, while leaving it at the current path. Thus we get a clone of the
      // 'add' menu item which works correctly as a local task.
      foreach (array(
                 'page callback',
                 'page arguments',
                 'access callback',
                 'access arguments',
               ) as $menu_item_key) {
        $items[$this->path . '/add'][$menu_item_key] = $add_menu_item[$menu_item_key];
      }
    }

    // Delete uses a generic path which is also used by 'revert', so leave that.

    return $items;
  }

  /**
   * Returns the content for the entity add page.
   *
   * @return mixed
   */
  public function addPage() {
    $item    = menu_get_item();
    $content = system_admin_menu_block($item);
    if (count($content) == 1) {
      $item = array_shift($content);
      drupal_goto($item['href']);
    }

    return theme('entity_add_list', array(
      'type'    => $this->entityType,
      'content' => $content,
    ));
  }

}