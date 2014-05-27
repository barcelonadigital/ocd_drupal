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
 * Our menu maps this function to the path 'ohp/ohp_case_main'.
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
      if("Prescripció d'OCD"==$row->description){
        //$row->description = 'Prescripció d\'OCD';
        $long_desc = 'Característiques de la sol·licitud. Diagnòstic. Proves funcionals respiratòries. Equips de teràpia respiratòria. Pla terapèutic. Comentaris.';
      }else if("Visita de seguiment"==$row->description){
        //$row->description = 'Visita de seguiment';
        $long_desc = 'Característiques de la sol·licitud. Diagnòstic. Factors de risc i hábits de vida. Proves funcionals respiratòries. Equips de teràpia respiratòria. Adequació i adherència. Percepció del pacient envers la seva salut. Pla terapèutic. Comentaris.';
      }else if("DISCHARGE"==$row->type){
        $long_desc = 'QÜESTIONARI REGISTRE D\'ALTA DEL PROGRAMA. REPORT Enviament de document a la història clínica. REPORT Sol·licitud d\'OCD a CatSalut.';
      }
      if($row->status=='ACTIVE'){
        $desc_status=t('Pendent');
      }else if($row->status=='DONE'){
        $desc_status=t('Finalitzat');
      }else if($row->status=='DELETED'){
        $desc_status=t('Eliminat');
      }else{
        $desc_status=$row->status;
      }
      $items[] = array(
        'data' => array(
          'id' => l('<span class="month">'.$month.'</span><span class="day">'.$day.'</span><span class="year">'.$year.'</span>',
          'ohp/ohp_case_taskunit', array('html' => TRUE,'query' => array('id_task' => $row->id_task, 'id_admission' => $id_admission, 'id_case' => $id_case))),
          'item_description' => l('<h4>'.$row->description.'</h4><p>'.$long_desc.'</p>',
          'ohp/ohp_case_taskunit', array('html' => TRUE,'query' => array('id_task' => $row->id_task, 'id_admission' => $id_admission, 'id_case' => $id_case))),
          'status' => l('<span class="status">'.$desc_status.'</span>',
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
      '#attributes' => array('id' => array('table_task'),),
      '#rows' => $chunks[$current_page],
      '#empty' => t('No hi ha elements per mostrar.'),
      '#prefix' => '<h2 class="asses">Històric d\'avaluacions</h2><br><br>',
    );

  }else {
    // There were no tasks. Tell the user.
    $content[] = array(
      '#type' => 'item',
      '#markup' => t('No hi ha elements per mostrar.'),
      '#prefix' => '<h2 class="asses">Històric d\'avaluacions</h2><br><br>',
    );
  }

  // Create a render array ($page_array) which will be themed as a table with a
  // pager.
  $page_array['main'] = array(
    '#theme' => 'ohp_case_body',
  );
  $page_array['main']['pager_container'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('content','full'),
    ),
  );
  $page_array['main']['pager_container']['newtask_link'] = array(
    '#markup' => t('<div class="h2actions"><a href="#alertModal" role="button" data-toggle="modal" class="btn btn-warning btn-large custom-btn">Nova avaluació</a></div>'),
  );
  $page_array['main']['pager_container']['pager_table'] = $content;
  $page_array['main']['pager_container']['newtask_modal'] = array(
    '#theme' => 'ohp_case_newtask',
  );

  return $page_array;
}
