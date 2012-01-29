<?php

class zomato_list_plugin_query_xml extends views_plugin_query {

  /**
   * Constructor; Create the basic query object and fill with default values.
   */
  function init($base_table = '', $base_field, $options = array()) {
    parent::init($base_table, $base_field, $options);

    $this->listIdentifier = $this->options['listIdentifier'];
  }

  function use_pager() {
    return FALSE;
  }

  /**
   * Generate a query and a countquery from all of the information supplied to
   * the object.
   *
   * @param $get_count
   *   Provide a countquery if this is true, otherwise provide a normal query.
   */
  function query($get_count = FALSE) {
    return array(
      'listIdentifier' => $this->options['listIdentifier'],
    );
  }

  function add_param($param, $value = '') {
    $this->params[$param] = $value;
  }

  /**
   * Builds the necessary info to execute the query.
   */
  function build(&$view) {
    $view->build_info['query'] = $this->query();
    $view->build_info['count_query'] = '';
    $view->build_info['query_args'] = array();
  }

  function execute(&$view) {
    $start = microtime();
    $query = $view->build_info['query'];
    $result = array();

    if ($query['listIdentifier'] == '') {
      return $result;
    }

    $obj = new ZomatoList();
    $r = $obj->getList($query['listIdentifier']);

    if (isset($r->parsed)) {
      foreach ($r->parsed['list'] as $entry) {
        $item = array();

        foreach ($this->fields as $field) {
          switch($field['field']) {
            case 'name':
              $item[$field['field']] = $entry['title'];
              break;
            default:
              $item[$field['field']] = $entry[$field['field']];
          }
        }

        $result[] = $item;
      }

      $view->result = $result;
      $view->total_rows = count($result);
    } else {
      $view->result = '';
    }

    $view->execute_time = microtime() - $start;
  }

  function add_signature(&$view) {}

  function option_definition() {
    $options = parent::option_definition();
    $options['listIdentifier'] = array('default' => '');

    return $options;
  }

  function options_form(&$form, &$form_state) {
    $form['listIdentifier'] = array(
      '#type' => 'textfield',
      '#title' => t('List Identifier'),
      '#default_value' => $this->options['listIdentifier'],
      '#description' => t('List Identifier (slug) of a public list.'),
    );
  }

  function add_field($table, $field, $alias = '', $params = array()) {
    $alias = $field;

    // Create a field info array.
    $field_info = array(
      'field' => $field,
      'table' => $table,
      'alias' => $field,
    ) + $params;

    if (empty($this->fields[$field])) {
      $this->fields[$field] = $field_info;
    }

    return $field;
  }
}

