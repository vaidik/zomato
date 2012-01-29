<?php

/**
 * Implements hook_views_data
 */
function zomato_list_views_data() {
  $data['zomato']['table']['group'] = t('Zomato List');

  $data['zomato']['table']['base'] = array(
    'title' => t('Zomato List'),
    'help' => t('Scrapes data from public lists on Zomato.com.'),
    'query class' => 'zomato_list',
  );

  $data['zomato']['name'] = array(
    'title' => t('Restaurant Name'),
    'help' => t('Name of a restaurant.'),
    'field' => array(
      'handler' => 'zomato_list_handler_field_restaurant_name',
      'element type' => 'div',
    ),
  );

  $data['zomato']['link'] = array(
    'title' => t('Restaurant Link'),
    'help' => t('Link to restaurant listing on Zomato.'),
    'field' => array(
      'handler' => 'zomato_list_handler_field_restaurant_link',
      'element type' => 'div',
    ),
  );

  $data['zomato']['address'] = array(
    'title' => t('Restaurant Address'),
    'help' => t('Address of the restaurant.'),
    'field' => array(
      'handler' => 'zomato_list_handler_field_restaurant_address',
      'element type' => 'div',
    ),
  );

  $data['zomato']['cuisine'] = array(
    'title' => t('Cuisine'),
    'help' => t('Cuisine offered in the restaurant.'),
    'field' => array(
      'handler' => 'zomato_list_handler_field_restaurant_cuisine',
      'element type' => 'div',
    ),
  );

  return $data;
}

/**
 * Implements hook_views_plugins().
 */
function zomato_list_views_plugins() {
  return array(
    'query' => array(
      'zomato_list' => array(
        'title' => t('Zomato'),
        'help' => t('Gets data from Zomato.com.'),
        'handler' => 'zomato_list_plugin_query_xml',
      ),
    ),
  );
}

/**
 * Implementation of hook_views_handlers().
 */
function zomato_list_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'zomato_list') . '/handlers',
    ),
    'handlers' => array(
      // Fields 
      'zomato_list_handler_field_restaurant_name' => array(
        'parent' => 'views_handler_field',
      ),
      'zomato_list_handler_field_restaurant_link' => array(
        'parent' => 'views_handler_field',
      ),
      'zomato_list_handler_field_restaurant_address' => array(
        'parent' => 'views_handler_field',
      ),
      'zomato_list_handler_field_restaurant_cuisine' => array(
        'parent' => 'views_handler_field',
      ),
    ),
  );
}

