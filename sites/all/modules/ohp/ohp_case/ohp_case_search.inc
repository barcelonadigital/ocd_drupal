<?php

include_once 'ohp_case.utils.inc';

/**
 * @file
 * Module file for case_search_module.
 */

/**
 * @defgroup case_search Example: Page
 * @ingroup examples
 * @{
 * This example demonstrates how a module can display a page at a given URL.
 *
 * It's important to understand how the menu system works in order to
 * implement your own pages. See the Menu Example module for some insight.
 *
 * @see menu_example
 */

/**
 * A simple form that displays a textfield and submit button.
 *
 * This form will be rendered by theme('form') (theme_form() by default)
 * because we do not provide a theme function for it here.
 */
function ohp_case_search_form($form, &$form_state) {
  $form['text'] = array(
    '#type' => 'textfield',
    '#title' => t('Text lliure'),
    '#required' => TRUE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Cercar'),
    '#attributes' => array(
      'class' => array('btn','custom-btn','btn-large','btn-info'),
    ),
  );
  return $form;
}

/**
 * Constructs a descriptive page.
 *
 * Our menu maps this function to the path 'ohp/ohp_case'.
 */
function ohp_case_search_page() {
  $page_array = array();
  $page_array['page'] = array(
    '#theme' => 'ohp_case_search',
  );
  $page_array['page']['pager_container'] = drupal_get_form('ohp_case_search_form');
  return $page_array;
}

/**
 * Process variables for ohp-case-search-form.tpl.php
 *
 * @see ohp-case-search-form.tpl.php
 */
function template_preprocess_ohp_case_search(&$variables) {
//   $search_form = drupal_get_form('ohp_case_search_form');
//   $search_form_box = drupal_render($search_form);
//   $variables['search_box'] = $search_form_box;
  $variables['search_box'] = drupal_render($variables['elements']['pager_container']);
}

/**
 * Submit handler for the text form.
 *
 * @param array $form
 *   Form API form array.
 * @param array $form_state
 *   Form API form state array.
 */
function ohp_case_search_form_submit($form, &$form_state) {
  $search_str = $form_state['values']['text'];

  $result = search_case($search_str);

  if($result->rowCount()==1){
    $row = $result->fetchAssoc();
    drupal_goto('ohp/ohp_case_main', array('query' => array('id_case' => $row["user_uid"])));
  }else{
    drupal_goto('ohp/ohp_case_result', array('query' => array('search_str' => $search_str)));
  }
}

/**
 * @} End of "defgroup case_search".
 */
