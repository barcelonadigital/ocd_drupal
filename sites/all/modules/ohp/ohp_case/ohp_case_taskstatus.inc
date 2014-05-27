<?php

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
 * Our menu maps this function to the path 'ohp/ohp_case_taskdelete'.
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
/**
 * Constructs a descriptive page.
 *
 * Our menu maps this function to the path 'ohp/ohp_case_taskopen'.
 */
function ohp_case_task_reopen() {
  return ohp_case_task_update('OPEN', 'ACTIVE');
}
/**
 * Constructs a descriptive page.
 *
 * Our menu maps this function to the path 'ohp/ohp_case_finish'.
 */
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
