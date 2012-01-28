<?php

/**
 * @file
 * Provides API for scraping public lists from Zomato.com.
 */

/**
 * Class for scraping list of lists or list of restaurants in a list
 * created by a particular user on Zomato.com.
 */
class ZomatoList {
  private $userIdentifier;
  private $baseURL;

  function __construct($userIdentifier) {
    $this->setUserIdentifier($userIdentifier);
    $this->baseURL = 'http://www.zomato.com/';
  }

  /**
   * Validates and sets user identifier.
   */
  function setUserIdentifier($userIdentifier) {
    if (!empty($userIdentifier)) {
      $this->userIdentifier = $userIdentifier;
    }
  }

  /**
   * Gets list of lists created by the user.
   */
  function getLists() {
    $lists = array();

    $url = $this->baseURL . 'users/' . $this->userIdentifier . '/lists';
    $response = drupal_http_request($url);

    if (!isset($response->redirect_url)) {
      $doc = new DOMDocument();
      @$doc->loadHTML($response->data);

      $elements = $this->getElementByClassName($doc,
                                               'list-excerpt-container',
                                               'div');

      foreach ($elements as $element) {
        $list = array();
       
        $childNodes = $element->childNodes; 
        $list['name'] = $childNodes->item(0)->nodeValue;
        $list['link'] = $childNodes->item(0)->childNodes
                                            ->item(0)->getAttribute('href');
        preg_match('/[0-9]+/', $childNodes->item(1)->nodeValue, $matches);
        $list['count'] = (int) $matches[0];
        $list['description'] = $childNodes->item(2)->nodeValue;

        $lists[] = $list;
      }
      unset($list);
    }

    $response->parsed = $lists;
    return $response;
  }

  /**
   * Gets list of restaurants in a particular list.
   */
  function getList($listIdentifier) {
    $lists = array();

    $url = $this->baseURL . 'lists/' . $this->listIdentifier;
    $response = drupal_http_request($url);

    $response['parsed'] = $lists;
    return $response;
  }

  /**
   * Custom function to get elements by class name.
   */
  private function getElementByClassName($doc, $classes, $tag) {
    $classes = explode(' ', $classes);
    $matched = array();

    $elements = $doc->getElementsByTagName($tag);
    for ($i=0;$i<$elements->length;$i++) {
      $tag_classes = explode(' ', $elements->item($i)->getAttribute('class'));
      if (array_intersect($tag_classes, $classes) == $classes) {
        $matched[] = $elements->item($i);
      }
    }

    return $matched;
  }
}
