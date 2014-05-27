<?php

include_once 'ohp_case.utils.inc';

/**
 * Author: Jordi Roda, Ernest Pastor, Filip Velickovski, Magí Lluch-Ariet
 * Barcelona Digital Technology Centre, 2014
 *
 * Open Health Practice is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Open Health Practice is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
