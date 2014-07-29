<?php

/**
 * @file
 * Provides Entity metadata integration.
 */

/**
 * Extend the default OG membership metadata properties.
 */
class CivicrmEntityMetadataController extends EntityDefaultMetadataController {



  /**
   * @return array
   */
  public function entityPropertyInfo() {
    module_load_include('module', 'civicrm_entity', 'civicrm_entity');
    $schemaInfo = parent::entityPropertyInfo();
    foreach ($schemaInfo as $name => $info) {
      $schema = civicrm_entity_get_schema($name);
      foreach ($schema['fields'] as $name => $info) {
        if ($type = _entity_metadata_convert_schema_type($info['type'])) {
          $schemaInfo[$this->type][$name] = array(
            'type' => $type,
            'label' => drupal_ucfirst($name),
            'schema field' => $name,
            'setter callback' => 'entity_property_verbatim_set',
            'description' => isset($info['description']) ? $info['description'] : '',
          );
          if ($info['type'] == 'serial') {
            $properties[$name]['validation callback'] = 'entity_metadata_validate_integer_positive';
          }
        }
      }
    }
    return $schemaInfo;
  }
}
