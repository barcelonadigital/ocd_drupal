<?php

include 'ohp_case_form.utils.inc';

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

    if($form_xml->data->name=='Variables'){

      $form['cancel'] = array(
        '#type' => 'link',
        '#title' => "<span>" . t("Tornar") . "</span>",
        '#href' => 'ohp/ohp_case_taskunit',
        '#attributes' => array(
          'class' => array('h2','back','clearfix'),
        ),
        '#options' => array(
          'html' => TRUE,
          'query' => array('id_task' => $id_task,
              'id_admission' => $id_admission, 'id_case' => $id_case),
        ),
      );


//       $form['cancel'] = array(
//         '#markup' => l("<span>" . t("Tornar") . "</span>",
//             'ohp/ohp_case_taskunit',
//             array('attributes' => array('class' => array('h2','back','clearfix')),
//                 'query' => array('id_task' => $id_task,
//                     'id_admission' => $id_admission, 'id_case' => $id_case))));

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
      $form['columns_container']['column_right'] = array(
        '#type' => 'container',
        '#attributes' => array(
          'class' => array('column','por3'),
        ),
      );
      $form['columns_container']['column_right']['equip'] = array(
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
      $form['columns_container']['column_right']['planificacio'] = array(
        '#type' => 'fieldset',
        '#title' => t('Pla terapèutic'),
        '#attributes' => array (
          'class' => array(
            'collapsible','ohp-form-summary'
          )
        ),
      );
      $form['columns_container']['column_right2'] = array(
        '#type' => 'container',
        '#attributes' => array(
          'class' => array('column','por3'),
        ),
      );
      $form['columns_container']['column_right2']['proves'] = array(
        '#type' => 'fieldset',
        '#title' => t('Proves complementàries'),
        '#attributes' => array (
          'class' => array(
            'collapsible','ohp-form-summary'
          )
        ),
      );

      $id_title = NULL;
      $ids_array = array("1","2","3","4","5","6","7","8","9","10","11","12","13");
      add_group_form('caracteristiques',$form['columns_container']['column_left']['caracteristiques'],
          $questions_map,$id_title,$ids_array,$id_form,$id_task,$id_admission,$id_case);

      $id_title = NULL;
      $ids_array = array("14","15","16","17","18");
      add_group_form('diagnostic',$form['columns_container']['column_left']['diagnostic'],
          $questions_map,$id_title,$ids_array,$id_form,$id_task,$id_admission,$id_case);

	  //espiro
      $id_title = 'Espirometria';
      $ids_array = array("19","20","21","22","23","24","25");
      add_group_form('espiro',$form['columns_container']['column_right2']['proves'],
          $questions_map,$id_title,$ids_array,$id_form,$id_task,$id_admission,$id_case);

	  //gaso
      $id_title = 'Gasometria';
      $ids_array = array("26","27","28","29","30","31","32","33","34","35");
      add_group_form('gaso',$form['columns_container']['column_right2']['proves'],
          $questions_map,$id_title,$ids_array,$id_form,$id_task,$id_admission,$id_case);

	  //pulsio
      $id_title = 'Pulsioximetria';
      $ids_array = array("36","37","38");
      add_group_form('pulsio',$form['columns_container']['column_right2']['proves'],
          $questions_map,$id_title,$ids_array,$id_form,$id_task,$id_admission,$id_case);

      $id_title = NULL;
      $ids_array = array("39","40","41","42",
          "43","44","45","46","47","48","49",
          "50","51","52","53","54");
      add_group_form('equip',$form['columns_container']['column_right']['equip'],
          $questions_map,$id_title,$ids_array,$id_form,$id_task,$id_admission,$id_case);

      $id_title = NULL;
      $ids_array = array("55","56","57","58","59","60");
      add_group_form('planificacio',$form['columns_container']['column_right']['planificacio'],
          $questions_map,$id_title,$ids_array,$id_form,$id_task,$id_admission,$id_case);
      //var_dump($questions_map);

    }else if($form_xml->data->name=='CVSO'){

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

function add_group_form($group_name,&$form_array,$questions_map,$text_title,$ids_array,$id_form,$id_task,$id_admission,$id_case){
  $form_array[] = array(
    '#markup' => '<hr>'.l(t('Editar'),
        'ohp/ohp_case_formunit',
        array('attributes' => array('class' => array('btn-primary', 'btn', 'btn-editform')),
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
    //var_dump($question_obj);
    if($question_obj->type=='STATIC_TEXT' ||
        $question_obj->value!=NULL && $question_obj->value!=""){
      $form_array[] = array(
        '#markup' => '<span class="question">'.$question_obj->description.'</span> <span class="answer">'.get_value_description($question_id, $questions_map).'</span><br/>',
      );
    }
  }
}

function get_value_description($question_id, $questions_map) {
  //var_dump(2);
  if(isset($questions_map[$question_id])){
    $question_obj = $questions_map[$question_id];
    //var_dump($question_obj);
    if($question_obj->type=='VERTICAL_RADIO' || $question_obj->type=='HORIZONTAL_RADIO'){
      foreach ($question_obj->options->option as $option) {
        if(isset($option->id_option) && isset($question_obj->value) && trim($option->id_option)==trim($question_obj->value)){
          return (string)$option->description;
        }
      }
    }else if($question_obj->type=='DATE'){
      //var_dump($question_obj);
      $data_convert = date_create_from_format("Y-m-d",(string)$question_obj->value);
      return date_format($data_convert, 'd/m/Y');
    }else{
      return (string)$question_obj->value;
    }
  }
  return "";
}


/**
 * @} End of "defgroup case_task".
 */
