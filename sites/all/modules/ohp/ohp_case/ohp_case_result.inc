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
 * Constructs a descriptive page.
 *
 * Our menu maps this function to the path 'ohp/ohp_case_result'.
 */
function ohp_case_result_page() {

  $search_str = $_GET['search_str'];

  $result = search_case($search_str);

  if($result->rowCount()>0){


    $items = array();
    $per_page = 6;
    // Initialize the pager
    $current_page = pager_default_initialize($result->rowCount(), $per_page);

    foreach ($result as $row) {
      $fullname = get_fullname ($row->given_name,$row->middle_name,$row->family_name,$row->family_name2);
      $items[] = array(
        'data' => array(
          'cip' => l($row->cip, 'ohp/ohp_case_main', array('query' => array('id_case' => $row->user_uid))),
          'nif' => l($row->nif, 'ohp/ohp_case_main', array('query' => array('id_case' => $row->user_uid))),
          'item_description' => l($fullname, 'ohp/ohp_case_main', array('query' => array('id_case' => $row->user_uid))),
        ),
      );
    }
    // Split your list into page sized chunks
    $chunks = array_chunk($items, $per_page, TRUE);

    // Create a render array ($page_array) which will be themed as a table with a
    // pager.
    $page_array['pager_table'] = array(
      '#theme' => 'table',
      '#header' => array(t('CIP'), t('NIF'), t('Nom complert')),
      '#attributes' => array('class' => array('table_result'),),
      '#rows' => $chunks[$current_page],
      '#empty' => t('No hi ha elements per mostrar.'),
    );

    // Attach the pager theme.
    $page_array['pager_pager'] = array('#theme' => 'pager');
  }else{
    // There were no tasks. Tell the user.
    $content[] = array(
      '#type' => 'item',
      '#markup' => t('No hi ha elements per mostrar.'),
    );
    $page_array['table'] = $content;
  }

  $page_container['main'] = array(
    '#theme' => 'ohp_case_result',
    '#page_content' => $page_array,
  );
  $page_container['main']['table_result']=$page_array;
  return $page_container;
}

/**
 * Process variables for ohp-case-result-form.tpl.php
 *
 * @see ohp-case-result-form.tpl.php
 */
function template_preprocess_ohp_case_result(&$variables) {
  $search_form = $variables['elements']['#page_content'];
  $search_form_box = drupal_render($search_form);
  $variables['table_results'] = $search_form_box;
}
