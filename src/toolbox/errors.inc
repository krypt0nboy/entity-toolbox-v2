<?php

/**
 * @file
 * errors.inc
 *
 * This file provide with error handling functions..
 *
 * @author kryptonboy <me@harold-cohen.com>
 */

/**
 * Logs an etbx system message.
 *
 * @param $message
 *   The message to store in the log. Keep $message translatable
 *   by not concatenating dynamic values into it! Variables in the
 *   message should be added by using placeholder strings alongside
 *   the variables argument to declare the value of the placeholders.
 *   See t() for documentation on how $message and $variables interact.
 * @param $variables
 *   Array of variables to replace in the message on display or
 *   NULL if message is already translated or not possible to
 *   translate.
 * @param $severity
 *   The severity of the message; one of the following values as defined in
 * @link http://www.faqs.org/rfcs/rfc3164.html RFC 3164: @endlink
 *   - WATCHDOG_EMERGENCY: Emergency, system is unusable.
 *   - WATCHDOG_ALERT: Alert, action must be taken immediately.
 *   - WATCHDOG_CRITICAL: Critical conditions.
 *   - WATCHDOG_ERROR: Error conditions.
 *   - WATCHDOG_WARNING: Warning conditions.
 *   - WATCHDOG_NOTICE: (default) Normal but significant conditions.
 *   - WATCHDOG_INFO: Informational messages.
 *   - WATCHDOG_DEBUG: Debug-level messages.
 * @param $link
 *   A link to associate with the message.
 */
function etbx_watchdog($message, $variables = array(), $severity = WATCHDOG_NOTICE, $link = NULL) {
  $type = 'etbx';
  switch ($severity) {
    case WATCHDOG_EMERGENCY:
      $type .= '_emergency';
      break;
    case WATCHDOG_NOTICE:
      $type .= '_notice';
      break;
    case WATCHDOG_WARNING:
      $type .= '_warning';
      break;
    case WATCHDOG_ALERT:
      $type .= '_alert';
      break;
    case WATCHDOG_DEBUG:
      $type .= '_debug';
      break;
    case WATCHDOG_INFO:
      $type .= '_info';
      break;
    case WATCHDOG_ERROR:
      $type .= '_error';
      break;
    case WATCHDOG_CRITICAL:
      $type .= '_critical';
      break;
    default:
      break;
  }
  watchdog($type, $message, $variables, $severity, $link);
}

/**
 * Warns when a user lacks the required access.
 *
 * @param string $module
 *   The module's name.
 * @param string $user
 *   The user requesting access.
 * @param int    $severity
 *   The log severity.
 */
function etbx_module_access_warning($module, $user, $severity = WATCHDOG_WARNING) {
  $message   = 'User @user lacks the rights to read/write on one or more of the module @module files.';
  $variables = array(
    '@module' => $module,
    '@user'   => $user
  );
  etbx_watchdog($message, $variables, $severity);
}