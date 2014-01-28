<?php

/**
 * Form callback
 */
function discogs_covers_startform($form, &$form_state) {
  $count = discogs_covers_products_without_image_count();

  $form['description'] = array(
    '#type' => 'markup',
    '#markup' => '<p>' . t('We found %num products without images, should I fetch them?', array(
        '%num' => $count,
      )) . '</p>',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Yeah',
  );

  return $form;
}

/**
 * Form submit callback
 * Runs batch
 */
function discogs_covers_startform_submit() {
  discogs_covers_batch();
}

function discogs_covers_clearform($form, &$form_state) {
  $query = db_select('commerce_product', 'cp');
  $query->addJoin('LEFT', 'field_data_field_images', 'image', 'cp.product_id = image.entity_id');
  $query->condition('image.entity_id', null, 'IS NOT');
  $query->fields('cp', array('product_id', 'title'));
  $query->distinct();
  $result = $query->execute();

  $form['products'] = array(
    '#tree' => TRUE,
    '#type' => 'fieldset',
    '#title' => t('Entities that have image'),
    '#theme' => array('table'),
    '#header' => array('Flush images', 'Title'),
    '#rows' => array(),
  );

  while ($product = $result->fetchAssoc()) {
    $delete = array(
      '#id' => 'product-' . $product['product_id'] . '-id',
      '#type' => 'checkbox',
      '#default_value' => FALSE,
    );
    $title = array(
      '#id' => 'product-' . $product['product_id'] . '-id',
      '#item' => 'checkbox',
      '#markup' => $product['title'],
    );

    $form['products'][] = array(
      'delete' => &$delete,
      'title' => &$title,
      'id' => array(
        '#type' => 'hidden',
        '#value' => $product['product_id'],
      ),
    );
    $form['products']['#rows'][] = array(
      array('data' => &$delete),
      array('data' => &$title),
    );

    unset($delete);
    unset($title);
  }

  $form['apply'] = array(
    '#type' => 'submit',
    '#submit' => array('discogs_covers_clearform_submit'),
    '#value' => t('Delete'),
  );

  return $form;
}

function discogs_covers_clearform_submit($form, &$form_state) {
  $update = &drupal_static('discogs_covers_update_entity');
  $update = FALSE;

  foreach($form_state['values']['products'] as $item) {
    if ($item['delete']) {
      $product = commerce_product_load($item['id']);

      $product->field_images = array();

      commerce_product_save($product);
    }
  }
}

function discogs_covers_settings($form, &$form_state) {
  $form['discogs_covers_process_new_entity'] = array(
    '#type' => 'checkbox',
    '#title' => t('Process new entity'),
    '#description' => t('Automatically fetch cover on entity create/update, if no image provided yet.'),
    '#default_value' => variable_get('discogs_covers_process_new_entity', FALSE),
  );

  $form['discogs_covers_files_to_fetch'] = array(
    '#type' => 'textfield',
    '#title' => t('Images to fetch'),
    '#description' => t('Specifies how many images should be fetched per entity.'),
    '#default_value' => variable_get('discogs_covers_files_to_fetch', 3),
    '#element_validate' => array('element_validate_integer_positive'),
  );

  $form['discogs_covers_maximum_fetch_attempts'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum fetch attempts'),
    '#description' => t('Specifies how many releases can be dived into during the search of cover.'),
    '#default_value' => variable_get('discogs_covers_maximum_fetch_attempts', 5),
    '#element_validate' => array('element_validate_integer_positive'),
  );

  return system_settings_form($form);
}