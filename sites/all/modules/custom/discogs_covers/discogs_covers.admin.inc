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

function discogs_covers_settings($form, &$form_state) {
  $form['discogs_covers_process_new_entity'] = array(
    '#type' => 'checkbox',
    '#title' => t('Process new entity'),
    '#description' => t('Automatically fetch cover on entity create/update, if no image provided yet.'),
    '#default_value' => variable_get('discogs_covers_process_new_entity', FALSE),
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