<?php

/**
 * @file
 * bar.inc
 *
 * This file provides required info for etbx.
 *
 * @author kryptonboy <me@harold-cohen.com>
 */

/**
 * Implements hook_entity_toolbox_info().
 */
function bar_entity_toolbox_info() {
  $info             = array();
  $info['bar']      = array(
    'fieldable'     => TRUE,
    'has_revisions' => FALSE,
    'group'         => 'example',
  );
  $info['bar_type'] = array(
    'fieldable' => FALSE,
    'group'     => 'example',
  );

  return $info;
}