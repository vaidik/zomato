<?php

class zomato_list_handler_field_restaurant_link extends views_handler_field {
  function render($values) {
    return check_plain($values[$this->field_alias]);
  }

  function element_type() {
    if (isset($this->definition['element type'])) {
      return $this->definition['element type'];
    }

    return 'div';
  }

  /**
   * Called to add the field to a query.
   */
  function query() {
    // Add the field.
    $this->field_alias = $this->query->add_field('', 'link');
  }

  /**
   * Provide extra data to the administration form
   */
  function admin_summary() {
    return $this->label();
  }
}

