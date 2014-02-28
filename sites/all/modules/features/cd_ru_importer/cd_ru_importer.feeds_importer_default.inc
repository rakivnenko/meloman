<?php
/**
 * @file
 * cd_ru_importer.feeds_importer_default.inc
 */

/**
 * Implements hook_feeds_importer_default().
 */
function cd_ru_importer_feeds_importer_default() {
  $export = array();

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'cd_ru';
  $feeds_importer->config = array(
    'name' => 'CD RU',
    'description' => '',
    'fetcher' => array(
      'plugin_key' => 'FeedsFileFetcher',
      'config' => array(
        'allowed_extensions' => 'txt csv tsv xml opml',
        'direct' => FALSE,
        'directory' => 'public://feeds',
        'allowed_schemes' => array(
          0 => 'public',
        ),
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsCSVParser',
      'config' => array(
        'delimiter' => ',',
        'encoding' => 'UTF-8',
        'no_headers' => 0,
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsCommerceProductProcessor',
      'config' => array(
        'product_type' => 'product',
        'author' => '1',
        'tax_rate' => TRUE,
        'mappings' => array(
          0 => array(
            'source' => 'Comments',
            'target' => 'field_comments',
            'unique' => FALSE,
          ),
          1 => array(
            'source' => 'SKU',
            'target' => 'sku',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'Artist',
            'target' => 'field_artist',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'Album Title',
            'target' => 'field_album_title',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'Year',
            'target' => 'field_year',
            'unique' => FALSE,
          ),
          5 => array(
            'source' => 'Price',
            'target' => 'commerce_price:amount',
            'unique' => FALSE,
          ),
          6 => array(
            'source' => 'Genre',
            'target' => 'field_genre',
            'unique' => FALSE,
          ),
          7 => array(
            'source' => 'Title',
            'target' => 'title',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => '0',
        'input_format' => 'plain_text',
        'skip_hash_check' => 1,
        'bundle' => 'product',
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => 1800,
    'expire_period' => 3600,
    'import_on_create' => TRUE,
    'process_in_background' => FALSE,
  );
  $export['cd_ru'] = $feeds_importer;

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'cd_ru_display';
  $feeds_importer->config = array(
    'name' => 'CD RU display',
    'description' => '',
    'fetcher' => array(
      'plugin_key' => 'FeedsFileFetcher',
      'config' => array(
        'allowed_extensions' => 'txt csv tsv xml opml',
        'direct' => FALSE,
        'directory' => 'public://feeds',
        'allowed_schemes' => array(
          0 => 'public',
        ),
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsCSVParser',
      'config' => array(
        'delimiter' => ',',
        'no_headers' => 0,
        'encoding' => 'UTF-8',
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsNodeProcessor',
      'config' => array(
        'expire' => '-1',
        'author' => '1',
        'authorize' => 0,
        'mappings' => array(
          0 => array(
            'source' => 'SKU',
            'target' => 'field_product:sku',
            'unique' => FALSE,
          ),
          1 => array(
            'source' => 'Artist',
            'target' => 'title_field',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'Album Title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'Product Category',
            'target' => 'field_product_category',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => '0',
        'input_format' => 'plain_text',
        'skip_hash_check' => 0,
        'bundle' => 'product_display',
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '-1',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['cd_ru_display'] = $feeds_importer;

  return $export;
}
