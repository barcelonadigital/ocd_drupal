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
function ohp_case_task_delete() {

  if(isset($_SESSION['admission_bean']) && isset($_SESSION['admission_bean']->id_admission) &&
      isset($_SESSION['case_bean']) && isset($_SESSION['case_bean']->id_case) &&
      isset($_GET['id_task']) && isset($_GET['id_form'])){
    $id_admission = $_SESSION['admission_bean']->id_admission;
    $id_case      = $_SESSION['case_bean']->id_case;
    $id_task      = $_GET['id_task'];
    $id_form      = $_GET['id_form'];

    delete_task($id_task);

    drupal_set_message(t('Els canvis s\'han desat correctament.'));
    drupal_goto('ohp/ohp_case_main', array('query' => array(
                'id_admission' => $id_admission, 'id_case' => $id_case)));
  }else{
    $page_array = array();
    ohp_case_load_common($page_array);
    $page_array['page_header'] = array(
      '#theme' => 'ohp_case_header',
    );
    $page_array['main'] = array(
      '#theme' => 'ohp_case_body',
    );
    $page_array['main']['pager_container'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array('content'),
      ),
    );
    return $page_array;
  }
}
function ohp_case_task_reopen() {
  return ohp_case_task_update('OPEN', 'ACTIVE');
}
function ohp_case_task_finish() {
  return ohp_case_task_update('CLOSE', 'DONE');
}
function ohp_case_task_update($form_status, $task_status) {

  if(isset($_SESSION['admission_bean']) && isset($_SESSION['admission_bean']->id_admission) &&
      isset($_SESSION['case_bean']) && isset($_SESSION['case_bean']->id_case) &&
      isset($_GET['id_task']) && isset($_GET['id_form'])){
    $id_admission = $_SESSION['admission_bean']->id_admission;
    $id_case      = $_SESSION['case_bean']->id_case;
    $id_task      = $_GET['id_task'];
    $id_form      = $_GET['id_form'];

    update_taskform_status($id_task,$form_status);
    update_task_status($id_task,$task_status);

    drupal_set_message(t('Els canvis s\'han desat correctament.'));
    drupal_goto('ohp/ohp_case_form', array('query' => array('id_form' => $id_form, 'id_task' => $id_task,
                'id_admission' => $id_admission, 'id_case' => $id_case)));
  }else{
    $page_array = array();
    ohp_case_load_common($page_array);
    $page_array['page_header'] = array(
      '#theme' => 'ohp_case_header',
    );
    $page_array['main'] = array(
      '#theme' => 'ohp_case_body',
    );
    $page_array['main']['pager_container'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array('content'),
      ),
    );
    return $page_array;
  }
}

/**
 * @} End of "defgroup case_task".
 */
