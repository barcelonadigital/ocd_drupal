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
function ohp_case_formunit_page() {

  $page_array = array();
  ohp_case_load_common($page_array);

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
  $page_array['main']['pager_container']['pager_table'] = drupal_get_form('ohp_case_formunit');

  return $page_array;
}

/**
 * Constructs a descriptive page.
 *
 * Our menu maps this function to the path 'ohp/tasks_assigned'.
 */
function ohp_case_formunit($form, &$form_state) {

  if(isset($_SESSION['admission_bean']) && isset($_SESSION['admission_bean']->id_admission) &&
      isset($_SESSION['case_bean']) && isset($_SESSION['case_bean']->id_case) &&
      isset($_GET['id_task']) && isset($_GET['id_form']) && isset($_GET['group_form'])){
    $id_admission = $_SESSION['admission_bean']->id_admission;
    $id_case      = $_SESSION['case_bean']->id_case;
    $id_task      = $_GET['id_task'];
    $id_form      = $_GET['id_form'];
    $group_form   = $_GET['group_form'];
    $questions_map = array();
    $form_xml = NULL;
    load_form(NULL ,$id_form, $form_xml, $questions_map);
    $copy_of_questions_map = array();
    foreach ($questions_map as $k => $v) {
      $copy_of_questions_map[$k] = clone $v;
    }

    if($form_xml->data->name=='Variables'){
      $form['#questions'] = $questions_map;
      $form['#after_build'][] = 'ohp_case_after_build'; //Calls function - See more at: http://www.appnovation.com/blog/drupal-tip-using-formafter-build#sthash.a6t5iANp.dpuf
      $form['submit_area'] = array(
        '#type' => 'container',
      );
      $form['submit_area']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Desar'),
        '#attributes' => array(
          'class' => array('btn','custom-btn','btn-large','btn-info'),
        ),
      );
      $form['submit_area']['cancel'] = array(
        '#type' => 'link',
        '#title' => t('Cancel.'),
        '#href' => 'ohp/ohp_case_form',
        '#options' => array('query' => array('id_form' => $id_form, 'id_task' => $id_task,
                'id_admission' => $id_admission, 'id_case' => $id_case)),
        '#attributes' => array(
          'class' => array('btn','btn-warning','link'),
        ),
      );
//       $form['column_left'] = array(
//         '#type' => 'container',
//         '#attributes' => array(
//           'class' => array('column-left'),
//         ),
//       );
      $form['form_container'] = array(
        '#type' => 'fieldset',
        '#collapsible' => FALSE,
        '#collapsed' => FALSE,
      );

      if($group_form=='caracteristiques'){
        $ids_array = array("1","2","3","4","5","6","7","8","9","10","11","12","13");
        add_group_question($form['form_container'],$questions_map,$ids_array,$copy_of_questions_map);
      }else if($group_form=='diagnostic'){
        $ids_array = array("14","15","16","17","18");
        add_group_question($form['form_container'],$questions_map,$ids_array,$copy_of_questions_map);
      }else if($group_form=='espiro'){
        $ids_array = array("19","20","21","22","23","24","25");
        add_group_question($form['form_container'],$questions_map,$ids_array,$copy_of_questions_map);
      }else if($group_form=='gaso'){
        $ids_array = array("26","27","28","29","30","31","32","33","34","35");
        add_group_question($form['form_container'],$questions_map,$ids_array,$copy_of_questions_map);
      }else if($group_form=='pulsio'){
        $ids_array = array("36","37","38");
        add_group_question($form['form_container'],$questions_map,$ids_array,$copy_of_questions_map);
      }else if($group_form=='equip'){
        $ids_array = array("39","40","41","42",
          "43","44","45","46","47","48","49",
          "50","51","52","53","54");
        add_group_question($form['form_container'],$questions_map,$ids_array,$copy_of_questions_map);
      }else if($group_form=='planificacio'){
        $ids_array = array("55","56","57","58","59","60");
        add_group_question($form['form_container'],$questions_map,$ids_array,$copy_of_questions_map);
      }
      foreach ($questions_map as $key => $value) {
        add_question($form['form_container'],$questions_map,(string)$key,$copy_of_questions_map, true);
      }
      $form['submit_area2'] = $form['submit_area'];

    }else if($form_xml->data->name=='CVSO'){

    }
  }
  return $form;
}

function add_group_question(&$form_array,&$questions_map,$ids_array,$copy_of_questions_map,$hiddens_array=array()){
  foreach ($ids_array as $id_question) {
    $hidden = FALSE;
    if(in_array($id_question, $hiddens_array)){
      $hidden = TRUE;
    }
    add_question($form_array,$questions_map,$id_question,$copy_of_questions_map,$hidden);
  }
}
/**
 * Submit handler for ohp_case_form().
 */
function ohp_case_formunit_submit($form, &$form_state) {

  if(isset($_SESSION['admission_bean']) && isset($_SESSION['admission_bean']->id_admission) &&
      isset($_SESSION['case_bean']) && isset($_SESSION['case_bean']->id_case) &&
      isset($_GET['id_task']) && isset($_GET['id_form'])){

    $id_admission = $_SESSION['admission_bean']->id_admission;
    $id_case      = $_SESSION['case_bean']->id_case;
    $id_task      = $_GET['id_task'];
    $id_form      = $_GET['id_form'];

    // Exclude unnecessary elements.
    unset($form_state['values']['submit'], $form_state['values']['form_id'], $form_state['values']['op'], $form_state['values']['form_token'], $form_state['values']['form_build_id']);

    $doc = new DomDocument("1.0", 'utf-8');
    $doc->standalone = true;
    $root = $doc->createElement("questions");
    $root = $doc->appendChild($root);

    foreach ($form_state['values'] as $key => $value) {
      if(strrpos($key, "question_type")===FALSE && strrpos($key, "question_condition")===FALSE){
        $question = colgar_hijo( $doc, $root, "question");
        $answer_id    = (string)$key;
        $question_type  = $form_state['values']['question_type_'.$answer_id];
        if(isset($form_state['values']['question_condition_'.$answer_id])){
          $question_condition  = $form_state['values']['question_condition_'.$answer_id];
          $elems = explode(",", (string)$question_condition);
          $id_answer = substr($elems[0], 1);
          $value_that_enables  = $elems[1];
          $question_that_enables  = $form_state['values'][$id_answer];
          if($question_that_enables!=$value_that_enables){
            $value = "";
          }
        }
        $question_value = NULL;
        if($question_type=='DATE' && isset($value['month']) && isset($value['day']) && isset($value['year'])){
          $question_value = date("Y-m-d", mktime(0, 0, 0, $value['month'], $value['day'], $value['year']));
        }else{
          $question_value = (string)$value;
        }
        $option_id = NULL;
        $value     = NULL;
        if($question_type=='VERTICAL_RADIO' || $question_type=='HORIZONTAL_RADIO'){
          if(isset($question_value) && $question_value!=''){
            $option_id = $question_value;
          }else{
            $option_id = NULL;
          }
        }else{
          $value = $question_value;
        }

        //drupal_set_message($answer_id.', '.$option_id.', '.$value);
        try {
          update_answer($answer_id,$option_id,$value);
        }
        catch (Exception $e) {
          drupal_set_message(t('db_update failed. Message = %message, query= %query',
            array('%message' => $e->getMessage(), '%query' => $e->query_string)), 'error');
          return;
        }

      }
    }
    drupal_set_message(t('El formulari s\'ha desat correctament.'));
    drupal_goto('ohp/ohp_case_form', array('query' => array('id_form' => $id_form, 'id_task' => $id_task,
                'id_admission' => $id_admission, 'id_case' => $id_case)));
  }
}

function ohp_case_after_build($form, &$form_state) {
  $field_formulas = array();
  foreach ($form['#questions'] as $key => $question) {
    if(isset($question->formula)&&!empty($question->formula)){
      $field_formulas[(string)$question->id_question]=(string)$question->formula;
    }
  }
  drupal_add_js(array('field_formulas' => $field_formulas), array('type' => 'setting'));
  drupal_add_js(drupal_get_path('module', 'ohp_case') .'/js/ohp_case_form.js');
  drupal_add_css(drupal_get_path('module', 'ohp_case') . '/css/ohp_case_form.css');

  $string_init_datapicker  = "(function ( $ ) {  $.fn.datepicker.dates['linkcare'] = {";
  $string_init_datapicker .= "days: ['Diumenge', 'Dilluns', 'Dimarts', 'Dimecres', 'Dijous', 'Divendres', 'Dissabte', 'Diumenge'],";
  $string_init_datapicker .= "daysShort: ['Diu', 'Dil', 'Dim', 'Dim', 'Dij', 'Div', 'Dis', 'Diu'],";
  $string_init_datapicker .= "daysMin: ['Dg', 'Dl', 'Dm', 'Dc', 'Dj', 'Dv', 'Ds', 'Dg'],";
  $string_init_datapicker .= "months: ['Gener','Febrer','Març','Abril','Maig','Juny','Juliol','Agost','Setembre','Octubre','Novembre','Decembre'],";
  $string_init_datapicker .= "monthsShort: ['Gen','Feb','Mar','Apr','May','Jun','Jul','Aug','Sep','Oct','Nov','Dec'],";
  $string_init_datapicker .= "today: 'Avui',";
  $string_init_datapicker .= "clear: 'Esborrar'";
  $string_init_datapicker .= "};}( jQuery10 ));";
  drupal_add_js($string_init_datapicker,array('type' => 'inline', 'scope' => 'footer', 'weight' => 5));
  return $form;
}

function add_question(&$form_array, &$questions_map, $question_id,$copy_of_questions_map, $hidden = FALSE){
  if(isset($questions_map[$question_id])){
    $question_obj = $questions_map[$question_id];
    $answer_id = $question_obj->id_answer;
    $form_array['question_type_'.$answer_id] = array(
      '#value' => $question_obj->type,
      '#type' => 'hidden',
    );
    $form_array[$answer_id] = array(
      '#title' => $question_obj->description,
    );
    if(($question_obj->type=='VERTICAL_RADIO' || $question_obj->type=='HORIZONTAL_RADIO') &&
        isset($question_obj->options->option)){
      $form_array[$answer_id]['#type'] = 'select';
      $form_array[$answer_id]['#empty_value'] = '';
      //$form_array[$answer_id]['#empty_option'] = TRUE;
      foreach ($question_obj->options->option as $option) {
        $form_array[$answer_id]['#options'][(string)$option->id_option]=(string)$option->description;
      }
    }else if($question_obj->type=='TEXT' || $question_obj->type=='NUMERICAL'){
      $form_array[$answer_id]['#type'] = 'textfield';
    }else if($question_obj->type=='FORMULA'){
      $form_array[$answer_id]['#type'] = 'textfield';
    }else if($question_obj->type=='TEXT_AREA'){
      $form_array[$answer_id]['#type'] = 'textarea';
    }else if($question_obj->type=='DATE'){
      $form_array[$answer_id]['#type'] = 'textfield';
    }else if($question_obj->type=='STATIC_TEXT'){
      $form_array[$answer_id]['#type'] = 'item';
    }else{
      $form_array[$answer_id]['#type'] = 'item';
    }
    $attributes_array = array();
    if($question_obj->type=='FORMULA'){
      $attributes_array['readonly']='readonly';
    }else{
      $attributes_array['onchange']='checkFormulas()';
    }
    if($question_obj->type=='DATE'){
      $attributes_array['class']=array('form-control','date');
    }
    $form_array[$answer_id]['#attributes'] = $attributes_array;
    if($hidden){
      $form_array[$answer_id]['#prefix'] = '<div style="display:none;">';
      $form_array[$answer_id]['#suffix'] = '</div>';
    }
    if(isset($question_obj->value)&&!empty($question_obj->value)){
      if($question_obj->type=='DATE'){
        $arr = date_parse_from_format("Y-m-d",$question_obj->value);
        $form_array[$answer_id]['#default_value'] = array('year' => $arr['year'], 'month' => $arr['month'],
           'day' => $arr['day']);
      }else{
        $form_array[$answer_id]['#default_value'] = (string)$question_obj->value;
      }
    }
    if(isset($question_obj->requirement)&&!empty($question_obj->requirement)){
      $elems = explode(",", (string)$question_obj->requirement);
      $id_question = substr($elems[0], 1);
      //$oper = $elems[1];
      //if($oper=='EQUAL'){
      $questionThatEnables = $copy_of_questions_map[$id_question];
      $idOptionThatEnables = NULL;
      $valueThatEnables = $elems[1];
      if(isset($questionThatEnables->options->option)){
        foreach ($questionThatEnables->options->option as $option) {
          if($option->value==$valueThatEnables){
            $idOptionThatEnables = $option->id_option;
          }
        }
      }
      if($idOptionThatEnables!=NULL){
      	$form_array[$answer_id]['#states'] = array(
      	    'enabled' => array(
      	        ':input[name="'.$questionThatEnables->id_answer.'"]' => array(
      	            array('value' => $idOptionThatEnables),
                ),
            ),
        );
        $form_array['question_condition_'.$answer_id] = array(
          '#value' => '$'.$questionThatEnables->id_answer.','.$idOptionThatEnables,
          '#type' => 'hidden',
        );
      }
    }
    unset($questions_map[$question_id]);
  }
}

/**
 * @} End of "defgroup case_task".
 */
