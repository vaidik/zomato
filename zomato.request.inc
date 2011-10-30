<?php

class ZomatoApi {
	private $key;
	private $base_url;

	function __construct() {
		$this->key = variable_get('zomato_api_key', '');
		$this->base_url = variable_get('zomato_base_url', '');
	}

	function request($call, $options = array()) {
		$params = array();
		if (isset($options['params'])) {
			foreach ($options['params'] as $param => $value) {
				$params[$param] = $value;
			}
		}
		$query = http_build_query($params);

		$options['http_request_options']['headers']['X-Zomato-API-Key'] = $this->key;

		$response = drupal_http_request($this->base_url . $call . '?' . query, $options['http_request_options']);

		return $response;
	}
}
