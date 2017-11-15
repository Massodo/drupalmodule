<?php

namespace Drupal\user_discount_code\Entity;

use Drupal\Core\Entity\ContentEntityBase;
use Drupal\Core\Entity\EntityTypeInterface;
use Drupal\Core\Field\BaseFieldDefinition;

/**
 * Defines the discount_code entity.
 *
 *
 * @ContentEntityType(
 *   id = "discount_code",
 *   label = @Translation("Discount code"),
 *   base_table = "discount_code",
 *   entity_keys = {
 *     "id" = "id",
 *     "uuid" = "uuid",
 *     "code" = "code"
 *   },
 * )
 */

class DiscountEntity extends ContentEntityBase{

  public static function baseFieldDefinitions(EntityTypeInterface $entity_type) {
    $fields['id'] = BaseFieldDefinition::create('integer')
    ->setLabel(t('Discount ID'))
    ->setDescription(t('ID'));
    $fields['uuid'] = BaseFieldDefinition::create('uuid')
    ->setLabel(t('UUID'))
    ->setDescription(t('Discount UUID'));
    $fields['code'] = BaseFieldDefinition::create('string')
    ->setLabel(t('Code'))
    ->setDescription(t('User discount code'))
    ->setSettings(array('max_length' => 10,));
    return $fields;
  }
}
