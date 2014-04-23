<?php

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
 * Constructs a descriptive page.
 *
 * Our menu maps this function to the path 'ohp/tasks_assigned'.
 */
function ohp_case_result_page() {
  $search_str = $_GET['search_str'];
  $items = array();
  try {
    if(!isset($_SESSION['ohp_token'])){
      drupal_set_message("ERROR: no token found");
      return array();
    }
    $token  = $_SESSION['ohp_token'];
    $client = new SoapClient(null, array('location' => $GLOBALS["WS-ENDPOINT"], 'uri' => ""));
    $result = $client->contact_search($token,"CASE",$search_str,"100", "TEAM");
    if ( $result["ErrorMsg"] ) {
      drupal_set_message($result["ErrorMsg"]);
    } else {
      $contacts_xml = simplexml_load_string($result["result"]);
      if(sizeof($contacts_xml->case)==1){
        $case1 = $contacts_xml->case[0];
        drupal_goto('ohp/ohp_case_main', array('query' => array('id_case' => $case1->id)));
      }else if(sizeof($contacts_xml->case)>1){
        foreach ($contacts_xml->case as $case) {
          // Create tabular rows for our entities.
          $items[] = array(
            'data' => array(
              'id' => $case->id,
              'item_description' => l($case->name_complete, 'ohp/ohp_case_main', array('query' => array('id_case' => $case->id))),
            ),
          );
        }
      }
    }
  } catch (SoapFault $fault) {
    drupal_set_message("SOAP Fault: (faultcode: {$fault->faultcode}, faultstring: {$fault->faultstring})");
  }

  if (!empty($items)) { //No content in the last week.
    $per_page = 10;
    // Initialize the pager
    $current_page = pager_default_initialize(count($items), $per_page);
    // Split your list into page sized chunks
    $chunks = array_chunk($items, $per_page, TRUE);

    // Create a render array ($page_array) which will be themed as a table with a
    // pager.
    $page_array['pager_table'] = array(
      '#theme' => 'table',
      '#header' => array(t('ID'), t('Nom complert')),
      '#rows' => $chunks[$current_page],
      '#empty' => t('No hi ha elements per mostrar.'),
    );

    // Attach the pager theme.
    $page_array['pager_pager'] = array('#theme' => 'pager');
  }else {
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
 * Process variables for ohp-case-search-form.tpl.php
 *
 * @see ohp-case-search-form.tpl.php
 */
function template_preprocess_ohp_case_result(&$variables) {
  $search_form = $variables['elements']['#page_content'];
  $search_form_box = drupal_render($search_form);
  $variables['table_results'] = $search_form_box;
}

/**
 * @} End of "defgroup case_search".
 */
