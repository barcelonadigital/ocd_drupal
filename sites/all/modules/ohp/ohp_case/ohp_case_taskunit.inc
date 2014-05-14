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
function ohp_case_taskunit_page() {

  $page_array = array();
  ohp_case_load_common($page_array);
  $page_array['page_header'] = array(
    '#theme' => 'ohp_case_header',
  );

  $task_bean = new stdClass();
  $items = array();
  if(isset($_SESSION['admission_bean']) && isset($_SESSION['admission_bean']->id_admission) &&
      isset($_SESSION['case_bean']) && isset($_SESSION['case_bean']->id_case) &&
      isset($_GET['id_task'])){
    $id_admission = $_SESSION['admission_bean']->id_admission;
    $id_case      = $_SESSION['case_bean']->id_case;
    $id_task      = $_GET['id_task'];

    $task_bean = get_task($id_task);
    if("VARIABLES"==strtoupper($task_bean->description)){
      $task_bean->description = 'Prescripció d\'OCD';
    }else if("CVSO"==strtoupper($task_bean->description)){
      $task_bean->description = 'Visita de seguiment';
    }

    $ref_last_item = NULL;
    $result = get_task_forms($id_task);
    $form = $result->fetchObject();
    drupal_goto('ohp/ohp_case_form', array('query' => array('id_form' => $form->id_form, 'id_task' => $id_task,
                'id_admission' => $id_admission, 'id_case' => $id_case)));

//     foreach ($result as $form) {
//       $ref_last_item = $form->id_form;
//       $items[] = array(
//         'data' => array(
//           'id' => l(t('QÜESTIONARI'), 'ohp/ohp_case_form', array('query' => array('id_form' => $form->id_form, 'id_task' => $id_task, 'id_admission' => $id_admission, 'id_case' => $id_case))),
//           'item_description' => l($form->short_name, 'ohp/ohp_case_form', array('query' => array('id_form' => $form->id_form, 'id_task' => $id_task, 'id_admission' => $id_admission, 'id_case' => $id_case))),
//         ),
//       );
//     }
//     $items[] = array(
//       'data' => array(
//         'id' => l(t('REPORT'), 'ohp/ohp_case_formdocument', array('query' => array('id_form' => $ref_last_item, 'id_task' => $id_task, 'id_admission' => $id_admission, 'id_case' => $id_case))),
//         'item_description' => l(t('Enviament de document a la història clínica'), 'ohp/ohp_case_formdocument', array('query' => array('id_form' => $ref_last_item, 'id_task' => $id_task, 'id_admission' => $id_admission, 'id_case' => $id_case))),
//       ),
//     );
//     $items[] = array(
//       'data' => array(
//         'id' => l(t('REPORT'), 'ohp/ohp_case_formcatsalut', array('query' => array('id_form' => $ref_last_item, 'id_task' => $id_task, 'id_admission' => $id_admission, 'id_case' => $id_case))),
//         'item_description' => l(t('Sol·licitud d\'OCD a CatSalut'), 'ohp/ohp_case_formcatsalut', array('query' => array('id_form' => $ref_last_item, 'id_task' => $id_task, 'id_admission' => $id_admission, 'id_case' => $id_case))),
//       ),
//     );
  }else{
//   if (!empty($items)) { //No content in the last week.
//     $per_page = 10;
//     // Initialize the pager
//     $current_page = pager_default_initialize(count($items), $per_page);
//     // Split your list into page sized chunks
//     $chunks = array_chunk($items, $per_page, TRUE);

//     $content[] = array(
//       '#theme' => 'table',
//       '#attributes' => array('id' => array('table_taskunit'),),
//       '#rows' => $chunks[$current_page],
//       '#empty' => t('No hi ha elements per mostrar.'),
//       '#task_bean' => $task_bean,
//       '#prefix' => '<h2 class="asses">Tasques</h2><h3>'.$task_bean->description.'<span>'.date('d/m/Y', $task_bean->date).'<strong></strong></span></h3>',
//     );

//   }else {
//     // There were no tasks. Tell the user.
//     $content[] = array(
//       '#type' => 'item',
//       '#markup' => t('No hi ha elements per mostrar.'),
//     );
//     $page_array['table'] = $content;
//   }

  // Create a render array ($page_array) which will be themed as a table with a
  // pager.
  $page_array['main'] = array(
    '#theme' => 'ohp_case_body',
  );
//   $page_array['main']['menu_container'] = array(
//     '#theme' => 'ohp_case_menu',
//     'is_active_menu_formularis' => TRUE,
//   );
  $page_array['main']['pager_container'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('content'),
    ),
  );
//   $page_array['main']['pager_container']['pager_table'] = $content;

  return $page_array;
  }
}

/**
 * Process variables for theming-example-text-form.tpl.php
 *
 * @see theming-example-text-form.tpl.php
 */
function template_preprocess_ohp_case_taskunit(&$variables) {


}


/**
 * @} End of "defgroup case_task".
 */
