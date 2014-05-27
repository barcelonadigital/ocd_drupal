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
 * Our menu maps this function to the path 'ohp/ohp_case_taskunit'.
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

  }else{

    // Create a render array ($page_array) which will be themed as a table with a
    // pager.
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
