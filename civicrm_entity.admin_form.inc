<?php

/**
 * @file
 * CiviCRM Entity admin settings form callbacks
 */

/**
 * Settings form callback function
 *
 * @param $form
 * @param $form_state
 * @return mixed
 */
function civicrm_entity_admin_settings_form($form, &$form_state) {
  $available_entities = _civicrm_entity_available_entities();

  $available_entities_option_set = _civicrm_entity_available_entities_get_option_set($available_entities);

  $options = array();
  foreach ($available_entities as $entity_type => $api_entity) {
    $options[$entity_type] = ucwords(str_replace('_', ' ', $api_entity));
  }

  $default_value = variable_get('civicrm_entity_admin_enabled_entities', $available_entities_option_set);

  $form['civicrm_entity_admin_enabled_entities']  = array(
    '#type' => 'checkboxes',
    '#title' => 'Enabled Entities',
    '#description' => 'Check all CiviCRM API entities that you would like to expose as Drupal entity types.',
    '#default_value' => $default_value,
    '#options' => $options,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save settings'),
  );

  return $form;
}

/**
 * Form submit callback for the CiviCRM Entity admin config page
 *
 * @param $form
 * @param $form_state
 */
function civicrm_entity_admin_settings_form_submit($form, $form_state) {
  variable_set('civicrm_entity_admin_enabled_entities', $form_state['values']['civicrm_entity_admin_enabled_entities']);
  entity_info_cache_clear();
  menu_rebuild();
}
