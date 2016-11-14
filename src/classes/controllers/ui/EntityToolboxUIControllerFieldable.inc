<?php

/**
 * Class EntityToolboxUIControllerFieldable
 *
 * The default UI Controller for fieldable entities.
 */
class EntityToolboxUIControllerFieldable extends EntityToolboxUIController {
  /** {{@inheritdoc}} */
  public function hook_menu() {
    $items                                                  = parent::hook_menu();
    $items[concat($this->entityType, $this->wildcard, '/')] = array(
      'title callback'   => $this->entityType . '_page_title',
      'title arguments'  => array(1),
      'page callback'    => $this->entityType . '_page_view',
      'page arguments'   => array(1),
      'access callback'  => entity_type_callbacks($this->entityType, 'access'),
      'access arguments' => array('view', 1),
      'type'             => MENU_CALLBACK,
    );
    $operations                                             = entity_operations_get_operation_info($this->entityType);

    if (isset($operations['edit'])) {
      $path     = paths_join($this->path, array('manage', 'edit'));
      $regexp   = str2rgxp($path);
      $filtered = array_filter_key_by_regexp($items, $regexp);
      foreach (array_keys($filtered) as $f) {
        unset($items[$f]);
      }
    }

    return $items;
  }

  /** {{@inheritdoc}} */
  protected function overviewTableRow($conditions, $id, $entity, $additional_cols = array()) {
    $row        = parent::overviewTableRow($conditions, $id, $entity, $additional_cols);
    $operations = entity_operations_get_operation_info($this->entityType);

    if (isset($operations['edit'])) {
      $link     = l(t('edit'), $this->path . '/manage/' . $id);
      $toFilter = array();
      $exclude  = array();
      foreach ($row as $key => $cell) {
        if (!is_array($cell)) {
          $toFilter[$key] = $cell;
        }
        else {
          $exclude[$key] = $cell;
        }
      }
      $catch = array_filter_by_value($toFilter, $link, NULL, TRUE);
      $catch += $exclude;
      arsort($catch);

      return $catch;
    }

    return $row;
  }
}