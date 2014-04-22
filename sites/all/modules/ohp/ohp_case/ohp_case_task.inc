<?php

/**
 * @file
 * Module file for case_task_module.
 */

/**
 * @defgroup case_task Example: Page
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
function ohp_case_task_page() {

  $page_array = array();
  ohp_case_load_common($page_array);

  $items = array();
  if(isset($_SESSION['admission_bean']) && isset($_SESSION['admission_bean']->id_admission) &&
      isset($_SESSION['case_bean']) && isset($_SESSION['case_bean']->id_case)){
    $id_admission = $_SESSION['admission_bean']->id_admission;
    $id_case      = $_SESSION['case_bean']->id_case;
    try {
      if(!isset($_SESSION['ohp_token'])){
        drupal_set_message("ERROR: no token found");
        return array();
      }
      $token    = $_SESSION['ohp_token'];
      $client = new SoapClient(null, array('location' => $GLOBALS["WS-ENDPOINT"], 'uri' => ""));
      $id_type="ADMI";
   	  $today = getdate();
   	  for ($i=$today['year']; $i<=$today['year']+1; $i++) {
   	    $result = $client->task_calendar_year( $token, $i, $id_type, $id_admission);
   	    if ( $result["ErrorMsg"] ) {
   	      drupal_set_message($result["ErrorMsg"]);
        } else {
          if($result["result"]){
   	        $dates_array = explode("#", $result["result"]);
   	        foreach ($dates_array as $date_item) {
   	          $infoDateArray = explode("|", $date_item);
   	          $result = $client->task_list_date( $token, $infoDateArray[0], $id_type, $id_admission);
         	  if ( $result["ErrorMsg"] ) {
         	    drupal_set_message($result["ErrorMsg"]);
              } else {
   	            $task_xml = simplexml_load_string($result["result"]);
     	        foreach ($task_xml->task as $task) {
     	          // Create tabular rows for our entities.
                  $items[] = array(
                    'data' => array(
                      'id' => $task->date,
                      'item_description' => l($task->description, 'ohp/ohp_case_taskunit', array('query' => array('id_task' => $task->id, 'id_admission' => $id_admission, 'id_case' => $id_case))),
                    ),
                  );
     	        }
              }
   	        }
          }
        }
   	  }
    } catch (SoapFault $fault) {
      drupal_set_message("SOAP Fault: (faultcode: {$fault->faultcode}, faultstring: {$fault->faultstring})");
    }
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
      '#header' => array(t('Data'), t('Tasca')),
      '#rows' => $chunks[$current_page],
      '#empty' => t('No hi ha elements per mostrar.'),
    );
    $page_array['pager_table']['#prefix'] = '<h2 class="asses">Tasques</h2>';

  }else {
    // There were no tasks. Tell the user.
    $content[] = array(
      '#type' => 'item',
      '#markup' => t('No hi ha elements per mostrar.'),
    );
    $page_array['table'] = $content;
  }

  return $page_array;
}


/**
 * @} End of "defgroup case_task".
 */
