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
  $page_array['page_header'] = array(
    '#theme' => 'ohp_case_header',
  );

  $items = array();
  if(isset($_SESSION['admission_bean']) && isset($_SESSION['admission_bean']->id_admission) &&
      isset($_SESSION['case_bean']) && isset($_SESSION['case_bean']->id_case)){
    $id_admission = $_SESSION['admission_bean']->id_admission;
    $id_case      = $_SESSION['case_bean']->id_case;

    $result = get_admission_tasks($id_admission);
    foreach ($result as $row) {
      $day = date('d',$row->date);
      $month = date('M',$row->date);
      $year = date('Y',$row->date);
      $long_desc = NULL;
      if("VARIABLES"==strtoupper($row->description)){
        $row->description = 'Prescripció d\'OCD';
        $long_desc = 'QÜESTIONARI VARIABLES. REPORT Enviament de document a la història clínica. REPORT Sol·licitud d\'OCD a CatSalut.';
      }else if("CVSO"==strtoupper($row->description)){
        $row->description = 'Visita de seguiment';
        $long_desc = 'QÜESTIONARI CVSO. REPORT Enviament de document a la història clínica. REPORT Sol·licitud d\'OCD a CatSalut.';
      }else if("DISCHARGE"==$row->type){
        $long_desc = 'QÜESTIONARI REGISTRE D\'ALTA DEL PROGRAMA. REPORT Enviament de document a la història clínica. REPORT Sol·licitud d\'OCD a CatSalut.';
      }
      $items[] = array(
        'data' => array(
          'id' => l('<span class="month">'.$month.'</span><span class="day">'.$day.'</span><span class="year">'.$year.'</span>',
          'ohp/ohp_case_taskunit', array('html' => TRUE,'query' => array('id_task' => $row->id_task, 'id_admission' => $id_admission, 'id_case' => $id_case))),
          'item_description' => l('<h4>'.$row->description.'</h4><p>'.$long_desc.'</p>',
          'ohp/ohp_case_taskunit', array('html' => TRUE,'query' => array('id_task' => $row->id_task, 'id_admission' => $id_admission, 'id_case' => $id_case))),
        ),
      );
    }
  }

  if (!empty($items)) { //No content in the last week.
    $per_page = 10;
    // Initialize the pager
    $current_page = pager_default_initialize(count($items), $per_page);
    // Split your list into page sized chunks
    $chunks = array_chunk($items, $per_page, TRUE);

    $content[] = array(
      '#theme' => 'table',
      //'#header' => array(t('Data'), t('Tasca')),
      '#attributes' => array('id' => array('table_task'),),
      '#rows' => $chunks[$current_page],
      '#empty' => t('No hi ha elements per mostrar.'),
      '#prefix' => '<h2 class="asses">Tasques</h2><br><br>',
    );

  }else {
    // There were no tasks. Tell the user.
    $content[] = array(
      '#type' => 'item',
      '#markup' => t('No hi ha elements per mostrar.'),
      '#prefix' => '<h2 class="asses">Tasques</h2><br><br>',
    );
    //$page_array['table'] = $content;
  }

  // Create a render array ($page_array) which will be themed as a table with a
  // pager.
  $page_array['main'] = array(
    '#theme' => 'ohp_case_body',
  );
  $page_array['main']['menu_container'] = array(
    '#theme' => 'ohp_case_menu',
    'is_active_menu_formularis' => TRUE,
  );
  $page_array['main']['pager_container'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('content'),
    ),
  );
  $page_array['main']['pager_container']['newtask_link'] = array(
    '#markup' => t('<div class="h2actions"><a href="#alertModal" role="button" data-toggle="modal" class="btn btn-warning btn-large custom-btn">Nova tasca</a></div>'),
  );
  $page_array['main']['pager_container']['pager_table'] = $content;
  $page_array['main']['pager_container']['newtask_modal'] = array(
    '#theme' => 'ohp_case_newtask',
  );

  return $page_array;
}

/**
 * @} End of "defgroup case_task".
 */
