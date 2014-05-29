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
 * Our menu maps this function to the path 'ohp/ohp_case_form'.
 */
function ohp_case_form_page() {

  $form = array();
  ohp_case_load_common($form);
  $page_array['page_header'] = array(
    '#theme' => 'ohp_case_header_form',
  );

  if(isset($_SESSION['admission_bean']) && isset($_SESSION['admission_bean']->id_admission) &&
      isset($_SESSION['case_bean']) && isset($_SESSION['case_bean']->id_case) &&
      isset($_GET['id_task']) && isset($_GET['id_form'])){
    $id_admission = $_SESSION['admission_bean']->id_admission;
    $id_case      = $_SESSION['case_bean']->id_case;
    $id_task      = $_GET['id_task'];
    $id_form      = $_GET['id_form'];
    $questions_map = array();
    $form_xml = NULL;
    load_form(NULL ,$id_form, $form_xml, $questions_map);

    $task_bean = get_task($id_task);
    $form['controls'] = array(
      '#theme' => 'ohp_case_formctrl',
      '#selected_option' => t('Qüestionari'),
      '#task_status' => $task_bean->status,
    );

    $form['columns_container'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array('columnboxes','clearfix'),
      ),
    );
    $form['columns_container']['column_left'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array('column','por3'),
      ),
    );

    if($form_xml->data->name=='Variables'){

      $form['columns_container']['column_middle'] = array(
        '#type' => 'container',
        '#attributes' => array(
          'class' => array('column','por3'),
        ),
      );
      $form['columns_container']['column_right'] = array(
        '#type' => 'container',
        '#attributes' => array(
          'class' => array('column','por3'),
        ),
      );

      drupal_add_library('system', 'drupal.collapse');
      $form['columns_container']['column_left']['diagnostic'] = array(
        '#type' => 'fieldset',
        '#title' => t('Diagnòstic'),
        '#attributes' => array (
          'class' => array(
            'collapsible','ohp-form-summary'
          )
        ),
      );
      $form['columns_container']['column_left']['caracteristiques'] = array(
        '#type' => 'fieldset',
        '#title' => t('Característiques de la sol·licitud'),
        '#attributes' => array (
          'class' => array(
            'collapsible','ohp-form-summary'
          )
        ),
      );
      $form['columns_container']['column_middle']['equip'] = array(
        '#type' => 'fieldset',
        '#title' => t('Equips de teràpia respiratòria'),
        '#collapsible' => TRUE,
        '#collapsed' => FALSE,
        '#attributes' => array (
          'class' => array(
            'collapsible','ohp-form-summary'
          )
        ),
      );
      $form['columns_container']['column_middle']['planificacio'] = array(
        '#type' => 'fieldset',
        '#title' => t('Pla terapèutic'),
        '#attributes' => array (
          'class' => array(
            'collapsible','ohp-form-summary'
          )
        ),
      );
      $form['columns_container']['column_middle']['comentaris'] = array(
        '#type' => 'fieldset',
        '#title' => t('Comentaris'),
        '#collapsible' => TRUE,
        '#collapsed' => FALSE,
        '#attributes' => array (
          'class' => array(
            'collapsible','ohp-form-summary'
          )
        ),
      );
      $form['columns_container']['column_right']['proves'] = array(
        '#type' => 'fieldset',
        '#title' => t('Proves funcionals respiratòries'),
        '#attributes' => array (
          'class' => array(
            'collapsible','ohp-form-summary'
          )
        ),
      );

      $id_title = NULL;
      $ids_array = get_form_items('diagnostic');
      add_group_form('diagnostic',$form['columns_container']['column_left']['diagnostic'],
          $questions_map,$id_title,$ids_array,$id_form,$id_task,$id_admission,$id_case,$task_bean->status);

      $id_title = NULL;
      $ids_array = get_form_items('caracteristiques');
      add_group_form('caracteristiques',$form['columns_container']['column_left']['caracteristiques'],
          $questions_map,$id_title,$ids_array,$id_form,$id_task,$id_admission,$id_case,$task_bean->status);

	  //espiro
      $id_title = 'Espirometria';
      $ids_array = get_form_items('espiro');
      add_group_form('espiro',$form['columns_container']['column_right']['proves'],
          $questions_map,$id_title,$ids_array,$id_form,$id_task,$id_admission,$id_case,$task_bean->status);

	  //gaso
      $id_title = 'Gasometria';
      $ids_array = get_form_items('gaso');
      add_group_form('gaso',$form['columns_container']['column_right']['proves'],
          $questions_map,$id_title,$ids_array,$id_form,$id_task,$id_admission,$id_case,$task_bean->status);

	  //pulsio
      $id_title = 'Pulsioximetria';
      $ids_array = get_form_items('pulsio');
      add_group_form('pulsio',$form['columns_container']['column_right']['proves'],
          $questions_map,$id_title,$ids_array,$id_form,$id_task,$id_admission,$id_case,$task_bean->status);

      $id_title = NULL;
      $ids_array = get_form_items('equip');
      add_group_form('equip',$form['columns_container']['column_middle']['equip'],
          $questions_map,$id_title,$ids_array,$id_form,$id_task,$id_admission,$id_case,$task_bean->status);

      $id_title = NULL;
      $ids_array = get_form_items('comentaris');
      add_group_form('comentaris',$form['columns_container']['column_middle']['comentaris'],
          $questions_map,$id_title,$ids_array,$id_form,$id_task,$id_admission,$id_case,$task_bean->status);

      $id_title = NULL;
      $ids_array = get_form_items('planificacio');
      add_group_form('planificacio',$form['columns_container']['column_middle']['planificacio'],
          $questions_map,$id_title,$ids_array,$id_form,$id_task,$id_admission,$id_case,$task_bean->status);

    }else if($form_xml->data->name=='CVSO'){

      $form['columns_container']['column_left']['info'] = array(
        '#type' => 'container',
        '#attributes' => array(
          'class' => array('notitlebox'),
        ),
      );
      $form['columns_container']['right_container'] = array(
        '#type' => 'container',
        '#attributes' => array(
          'class' => array('column','por6'),
        ),
      );
      $form['columns_container']['right_container']['column_top'] = array(
        '#type' => 'container',
        '#attributes' => array(
          'class' => array('column','por6'),
        ),
      );
      $form['columns_container']['right_container']['column_left'] = array(
        '#type' => 'container',
        '#attributes' => array(
          'class' => array('column','por3'),
        ),
      );
      $form['columns_container']['right_container']['column_right'] = array(
        '#type' => 'container',
        '#attributes' => array(
          'class' => array('column','por3'),
        ),
      );

      drupal_add_library('system', 'drupal.collapse');
      $form['columns_container']['column_left']['diagnostic'] = array(
        '#type' => 'fieldset',
        '#title' => t('Diagnòstic'),
        '#attributes' => array (
          'class' => array(
            'collapsible','ohp-form-summary'
          )
        ),
      );
      $form['columns_container']['column_left']['caracteristiques'] = array(
        '#type' => 'fieldset',
        '#title' => t('Característiques de la sol·licitud'),
        '#attributes' => array (
          'class' => array(
            'collapsible','ohp-form-summary'
          )
        ),
      );
      $form['columns_container']['column_left']['factors'] = array(
        '#type' => 'fieldset',
        '#title' => t('Factors de risc  i hàbits de vida'),
        '#attributes' => array (
          'class' => array(
            'collapsible','collapsed','ohp-form-summary'
          )
        ),
      );
      $form['columns_container']['column_left']['adherencia'] = array(
        '#type' => 'fieldset',
        '#title' => t('Adequació i adherència '),
        '#attributes' => array (
          'class' => array(
            'collapsible','collapsed','ohp-form-summary'
          )
        ),
      );
      $form['columns_container']['column_left']['percepcio'] = array(
        '#type' => 'fieldset',
        '#title' => t('Percepció del pacient'),
        '#attributes' => array (
          'class' => array(
            'collapsible','collapsed','ohp-form-summary'
          )
        ),
      );
      $form['columns_container']['right_container']['column_top']['planificacio'] = array(
        '#type' => 'fieldset',
        '#title' => t('Pla terapèutic'),
        '#attributes' => array (
          'class' => array(
            'collapsible','collapsed','ohp-form-summary'
          )
        ),
      );
      $form['columns_container']['right_container']['column_left']['equip'] = array(
        '#type' => 'fieldset',
        '#title' => t('Equips de teràpia respiratòria'),
        '#collapsible' => TRUE,
        '#collapsed' => FALSE,
        '#attributes' => array (
          'class' => array(
            'collapsible','ohp-form-summary'
          )
        ),
      );
      $form['columns_container']['right_container']['column_left']['comentaris'] = array(
        '#type' => 'fieldset',
        '#title' => t('Comentaris'),
        '#collapsible' => TRUE,
        '#collapsed' => FALSE,
        '#attributes' => array (
          'class' => array(
            'collapsible','ohp-form-summary'
          )
        ),
      );
      $form['columns_container']['right_container']['column_right']['proves'] = array(
        '#type' => 'fieldset',
        '#title' => t('Proves funcionals respiratòries'),
        '#attributes' => array (
          'class' => array(
            'collapsible','ohp-form-summary'
          )
        ),
      );

      $id_title = NULL;
      $ids_array = get_form_items('info');
      add_group_form('info',$form['columns_container']['column_left']['info'],
          $questions_map,$id_title,$ids_array,$id_form,$id_task,$id_admission,$id_case,$task_bean->status);
      $form['columns_container']['column_left']['info'][] = array('#markup' => '<hr>');

      $id_title = NULL;
      $ids_array = get_form_items('diagnostic');
      add_group_form('diagnostic',$form['columns_container']['column_left']['diagnostic'],
          $questions_map,$id_title,$ids_array,$id_form,$id_task,$id_admission,$id_case,$task_bean->status);

      $id_title = NULL;
      $ids_array = get_form_items('caracteristiques');
      add_group_form('caracteristiques',$form['columns_container']['column_left']['caracteristiques'],
          $questions_map,$id_title,$ids_array,$id_form,$id_task,$id_admission,$id_case,$task_bean->status);

      $id_title = NULL;
      $ids_array = get_form_items('factors');
      add_group_form('factors',$form['columns_container']['column_left']['factors'],
          $questions_map,$id_title,$ids_array,$id_form,$id_task,$id_admission,$id_case,$task_bean->status);

      $id_title = NULL;
      $ids_array = get_form_items('adherencia');
      add_group_form('adherencia',$form['columns_container']['column_left']['adherencia'],
          $questions_map,$id_title,$ids_array,$id_form,$id_task,$id_admission,$id_case,$task_bean->status);

      $id_title = NULL;
      $ids_array = get_form_items('percepcio');
      add_group_form('percepcio',$form['columns_container']['column_left']['percepcio'],
          $questions_map,$id_title,$ids_array,$id_form,$id_task,$id_admission,$id_case,$task_bean->status);

	  //test marxa
      $id_title = 'Test de la marxa (6 minuts)';
      $ids_array = get_form_items('test');
      add_group_form('test',$form['columns_container']['right_container']['column_right']['proves'],
          $questions_map,$id_title,$ids_array,$id_form,$id_task,$id_admission,$id_case,$task_bean->status);

	  //pulsio noct
      $id_title = 'Pulsioximetria nocturna';
      $ids_array = get_form_items('noct');
      add_group_form('noct',$form['columns_container']['right_container']['column_right']['proves'],
          $questions_map,$id_title,$ids_array,$id_form,$id_task,$id_admission,$id_case,$task_bean->status);

	  //espiro
      $id_title = 'Espirometria';
      $ids_array = get_form_items('espiro');
      add_group_form('espiro',$form['columns_container']['right_container']['column_right']['proves'],
          $questions_map,$id_title,$ids_array,$id_form,$id_task,$id_admission,$id_case,$task_bean->status);

	  //gaso
      $id_title = 'Gasometria';
      $ids_array = get_form_items('gaso');
      add_group_form('gaso',$form['columns_container']['right_container']['column_right']['proves'],
          $questions_map,$id_title,$ids_array,$id_form,$id_task,$id_admission,$id_case,$task_bean->status);

	  //pulsio
      $id_title = 'Pulsioximetria';
      $ids_array = get_form_items('pulsio');
      add_group_form('pulsio',$form['columns_container']['right_container']['column_right']['proves'],
          $questions_map,$id_title,$ids_array,$id_form,$id_task,$id_admission,$id_case,$task_bean->status);

      $id_title = NULL;
      $ids_array = get_form_items('equip');
      add_group_form('equip',$form['columns_container']['right_container']['column_left']['equip'],
          $questions_map,$id_title,$ids_array,$id_form,$id_task,$id_admission,$id_case,$task_bean->status);

      $id_title = NULL;
      $ids_array = get_form_items('comentaris');
      add_group_form('comentaris',$form['columns_container']['right_container']['column_left']['comentaris'],
          $questions_map,$id_title,$ids_array,$id_form,$id_task,$id_admission,$id_case,$task_bean->status);

      $id_title = NULL;
      $ids_array = get_form_items('planificacio');
      add_group_form('planificacio',$form['columns_container']['right_container']['column_top']['planificacio'],
          $questions_map,$id_title,$ids_array,$id_form,$id_task,$id_admission,$id_case,$task_bean->status);
    }
  }

  $page_array['main'] = array(
    '#theme' => 'ohp_case_body',
  );
  $page_array['main']['pager_container'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('content','full'),
    ),
  );
  $page_array['main']['pager_container']['pager_table'] = $form;

  drupal_add_css(drupal_get_path('module', 'ohp_case') . '/css/ohp_case_form.css');
  return $page_array;
}

function add_group_form($group_name,&$form_array,$questions_map,$text_title,$ids_array,$id_form,$id_task,$id_admission,$id_case,$task_status){

  $link_attributes = array('class' => array('btn-primary', 'btn', 'btn-editform'));
  if($task_status=='DONE'){
    $link_attributes['style'] = 'display:none';
  }
  $form_array[] = array(
    '#markup' => '<hr>'.l(t('Editar'),
        'ohp/ohp_case_formunit',
        array('attributes' => $link_attributes,
              'query' => array('id_form' => $id_form, 'id_task' => $id_task,
                'id_admission' => $id_admission, 'id_case' => $id_case, 'group_form' => $group_name))));
  if(isset($text_title) && $text_title!=NULL){
    $form_array[] = array(
      '#markup' => '<span class="question">'.$text_title.'</span> <span class="answer"></span><br/>',
    );
  }
  $size_before = count($form_array);
  foreach ($ids_array as $id_question) {
    add_resume_question($form_array,$questions_map,$id_question);
  }
  $size_after = count($form_array);
  if($size_before==$size_after){
    $form_array[] = array(
      '#markup' => t('No hi ha elements per mostrar.'),
    );
  }
}

function add_resume_question(&$form_array, $questions_map, $question_id, $hidden = false){
  if(isset($questions_map[$question_id])){
    $question_obj = $questions_map[$question_id];
    if($question_obj->type=='STATIC_TEXT' ||
        $question_obj->value!=NULL && $question_obj->value!=""){
      $form_array[] = array(
        '#markup' => '<span class="question">'.$question_obj->description.'</span> <span class="answer">'.get_value_description($question_id, $questions_map).'</span><br/>',
      );
    }
  }
}
