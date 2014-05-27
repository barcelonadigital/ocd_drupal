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
 * Our menu maps this function to the path 'ohp/ohp_case_formdocument'.
 */
function ohp_case_formdocument_page() {

  ohp_case_load_common($form);
  $page_array['page_header'] = array(
    '#theme' => 'ohp_case_header_form',
  );
  $page_array['main'] = array(
    '#theme' => 'ohp_case_body',
  );
  $page_array['main']['pager_container'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('content','full'),
    ),
  );
  $param_form = '';
  if(isset($_GET['id_form'])){
    $param_form .= '/'.$_GET['id_form'];
  }
  $path = url('ohp/ohp_pdf/download/prescription'.$param_form);

  $task_status='';
  if(isset($_GET['id_task']) && $_GET['id_task']!=''){
    $id_task = $_GET['id_task'];
    $task_bean = get_task($id_task);
    $task_status = $task_bean->status;
  }
  $page_array['main']['pager_container']['controls'] = array(
    '#theme' => 'ohp_case_formctrl',
    '#selected_option' => t('Enviament de document a la història clínica'),
    '#task_status' => $task_status,
  );
  $page_array['main']['pager_container']['pager_table'] = array(
    '#title' => t('Enviament de document a la història clínica'),
    '#markup' => '<br><iframe src="'.$path.'" style="width:1000px; height:500px;"></iframe>',
  );
  return $page_array;
}

