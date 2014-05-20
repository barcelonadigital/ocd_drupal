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
  $page_array['formhints_modal'] = array(
    '#theme' => 'ohp_case_formhints',
  );

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

    $form_object = get_form_object($group_form);
    $form['form_container']['#title'] = $form_object['title'];
    add_group_question($form['form_container'],$questions_map,$form_object['items'],$copy_of_questions_map,$form_object['hidden']);
    foreach ($questions_map as $key => $value) {
      add_question($form['form_container'],$questions_map,(string)$key,$copy_of_questions_map, true);
    }

    $form['submit_area2'] = $form['submit_area'];
  }
  return $form;
}

function add_group_question(&$form_array,&$questions_map,$ids_array,$copy_of_questions_map,$hiddens_array=array()){
  $i=0;
  foreach ($ids_array as $row_question) {
    $form_array['row_'.$i] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array('inline-row'),
      ),
    );
    foreach ($row_question as $id_question) {
//     foreach ($ids_array as $id_question) {
      $hidden = FALSE;
      if(in_array($id_question, $hiddens_array)){
        $hidden = TRUE;
      }
      //add_question($form_array,$questions_map,$id_question,$copy_of_questions_map,$hidden);
      add_question($form_array['row_'.$i],$questions_map,$id_question,$copy_of_questions_map,$hidden);
    }
    $i++;
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

    $questions_map = array();
    $form_xml = NULL;
    load_form(NULL ,$id_form, $form_xml, $questions_map);

    // Exclude unnecessary elements.
    unset($form_state['values']['submit'], $form_state['values']['form_id'], $form_state['values']['op'], $form_state['values']['form_token'], $form_state['values']['form_build_id']);

    $doc = new DomDocument("1.0", 'utf-8');
    $doc->standalone = true;
    $root = $doc->createElement("questions");
    $root = $doc->appendChild($root);

    foreach ($form_state['values'] as $key => $value) {
      if(strrpos($key, "question_type")===FALSE &&
          strrpos($key, "question_condition")===FALSE &&
          strrpos($key, "answer_id")===FALSE){
        $question_id    = (string)$key;
        $question_type  = $form_state['values']['question_type_'.$question_id];
        $answer_id      = $form_state['values']['answer_id_'.$question_id];
        if(isset($form_state['values']['question_condition_'.$question_id])){
          $question_condition  = $form_state['values']['question_condition_'.$question_id];
          $elems = explode(",", (string)$question_condition);
          $id_question_that_enables = substr($elems[0], 1);
          $value_that_enables  = $elems[1];
          if(isset($form_state['values'][$id_question_that_enables])){
            $question_that_enables  = $form_state['values'][$id_question_that_enables];
            if($question_that_enables!=$value_that_enables){
              $value = "";
            }else if(isset($form_state['values']['question_condition_'.$id_question_that_enables])){
              $question_condition_2 = $form_state['values']['question_condition_'.$id_question_that_enables];
              $elems_2 = explode(",", (string)$question_condition_2);
              $id_question_that_enables_2 = substr($elems_2[0], 1);
              $value_that_enables_2  = $elems_2[1];
              if(isset($form_state['values'][$id_question_that_enables_2])){
                $question_that_enables_2  = $form_state['values'][$id_question_that_enables_2];
                if($question_that_enables_2!=$value_that_enables_2){
                  $value = "";
                }
              }
            }
          }
        }
        $question_value = NULL;
        if($question_type=='DATE' && isset($value) && $value!=""){
          $parsed = date_parse_from_format("d/m/Y",(string)$value);
          $question_value = mktime(0,0,0,$parsed['month'],$parsed['day'],$parsed['year']);
        }else{
          $question_value = (string)$value;
        }
        $option_id = NULL;
        $value     = NULL;
        if($question_type=='VERTICAL_RADIO' || $question_type=='HORIZONTAL_RADIO'){
          foreach ($questions_map[$question_id]->options->option as $option) {
            if($option->value==$question_value){
              $option_id = $option->id_option;
            }
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
  $string_init_datapicker .= "months: ['Gener','Febrer','Març','Abril','Maig','Juny','Juliol','Agost','Setembre','Octubre','Novembre','Desembre'],";
  $string_init_datapicker .= "monthsShort: ['Gen','Feb','Mar','Apr','May','Jun','Jul','Aug','Sep','Oct','Nov','Des'],";
  $string_init_datapicker .= "today: 'Avui',";
  $string_init_datapicker .= "clear: 'Esborrar'";
  $string_init_datapicker .= "};}( jQuery10 ));";
  drupal_add_js($string_init_datapicker,array('type' => 'inline', 'scope' => 'footer', 'weight' => 5));
  return $form;
}

function add_question(&$form_array, &$questions_map, $question_id,$copy_of_questions_map, $hidden = FALSE){
  if(isset($questions_map[$question_id])){
    $question_obj = $questions_map[$question_id];
    $form_array['question_type_'.$question_id] = array(
      '#value' => $question_obj->type,
      '#type' => 'hidden',
    );
    $form_array['answer_id_'.$question_id] = array(
      '#value' => $question_obj->id_answer,
      '#type' => 'hidden',
    );
    $description = $question_obj->description;
    if($question_id=='26'){
      $description .= '<a href="#helpGasometriaModal" role="button" data-toggle="modal" class="info_popup">Info</a>';
    }else if($question_id=='19'){
      $description .= '<a href="#helpEspiroModal" role="button" data-toggle="modal" class="info_popup">Info</a>';
    }else if($question_id=='36'){
      $description .= '<a href="#helpPulsioModal" role="button" data-toggle="modal" class="info_popup">Info</a>';
    }else if($question_id=='64'){
      $description .= '<a href="#helpTabaqModal" role="button" data-toggle="modal" class="info_popup">Info</a>';
    }else if($question_id=='67'){
      $description .= '<a href="#helpImcModal" role="button" data-toggle="modal" class="info_popup">Info</a>';
    }else if($question_id=='77'){
      $description .= '<a href="#helpPulsioNoctModal" role="button" data-toggle="modal" class="info_popup">Info</a>';
    }else if($question_id=='90'){
      $description .= '<a href="#helpAdequacioModal" role="button" data-toggle="modal" class="info_popup">Info</a>';
    }
    $form_array[$question_id] = array(
      '#title' => $description,
    );
    if(in_array($question_id, get_numeric_array())){
      $form_array[$question_id]['#type'] = 'numericfield';
    }else if(($question_obj->type=='VERTICAL_RADIO' || $question_obj->type=='HORIZONTAL_RADIO') &&
        isset($question_obj->options->option)){
      $form_array[$question_id]['#type'] = 'select';
      $form_array[$question_id]['#empty_value'] = '';
      $form_array[$question_id]['#empty_option'] = t('-');
      //$form_array[$question_id]['#empty_option'] = TRUE;
      foreach ($question_obj->options->option as $option) {
        $form_array[$question_id]['#options'][(string)$option->value]=drupal_html_to_text($option->description);
      }
    }else if($question_obj->type=='TEXT' || $question_obj->type=='NUMERICAL'){
      $form_array[$question_id]['#type'] = 'textfield';
    }else if($question_obj->type=='FORMULA'){
      $form_array[$question_id]['#type'] = 'textfield';
    }else if($question_obj->type=='TEXT_AREA'){
      $form_array[$question_id]['#type'] = 'textarea';
    }else if($question_obj->type=='DATE'){
      $form_array[$question_id]['#type'] = 'textfield';
    }else if($question_obj->type=='STATIC_TEXT'){
      $form_array[$question_id]['#type'] = 'item';
    }else{
      $form_array[$question_id]['#type'] = 'item';
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
    $form_array[$question_id]['#attributes'] = $attributes_array;
    $rules_array = array();
//     if(isset($question_obj->num_decimals)){
//       $rules_array[]='limit_decimals['.$question_obj->num_decimals.']';
//     }
//     if(isset($question_obj->min_value)){
//       $min_value = $question_obj->min_value;
//     }else{
//       $min_value = '*';
//     }
//     if(isset($question_obj->max_value)){
//       $max_value = $question_obj->max_value;
//     }else{
//       $max_value = '*';
//     }
//     if(isset($question_obj->min_value) || isset($question_obj->max_value)){
//       $rules_array[]='range['.$min_value.', '.$max_value.']';
//     }
    if(isset($question_obj->min_value) || isset($question_obj->max_value) || isset($question_obj->num_decimals)){
      $form_array[$question_id]['#type'] = 'numericfield';
      if(isset($question_obj->num_decimals)){
        $form_array[$question_id]['#decimals'] = $question_obj->num_decimals;
      }
      if(isset($question_obj->min_value)){
        $form_array[$question_id]['#minimum'] = $question_obj->min_value;
      }
      if(isset($question_obj->max_value)){
        $form_array[$question_id]['#maximum'] = $question_obj->max_value;
      }
    }
    if(isset($question_obj->min_length)){
      $min_length = $question_obj->min_length;
    }else{
      $min_length = '*';
    }
    if(isset($question_obj->max_length)){
      $max_length = $question_obj->max_length;
    }else{
      $max_length = '*';
    }
    if(isset($question_obj->min_length) || isset($question_obj->max_length)){
      $rules_array[]='length['.$min_length.', '.$max_length.']';
    }
    //var_dump($rules_array);
    if($hidden){
      $form_array[$question_id]['#prefix'] = '<div style="display:none;">';
      $form_array[$question_id]['#suffix'] = '</div>';
    }else{
      $form_array[$question_id]['#rules'] = $rules_array;
    }
    if(isset($question_obj->value)&&!empty($question_obj->value)){
      if($question_obj->type=='DATE'){
        $form_array[$question_id]['#default_value'] = date('d/m/Y',$question_obj->value);
      }else if($question_obj->type=='VERTICAL_RADIO' || $question_obj->type=='HORIZONTAL_RADIO'){
        foreach ($question_obj->options->option as $option) {
          if($option->id_option==(string)$question_obj->value){
            $form_array[$question_id]['#default_value'] = $option->value;
          }
        }
      }else{
        $form_array[$question_id]['#default_value'] = (string)$question_obj->value;
      }
    }
    if(isset($question_obj->requirement)&&!empty($question_obj->requirement)){
      $elems = explode(",", (string)$question_obj->requirement);
      $id_question = substr($elems[0], 1);
      //$oper = $elems[1];
      //if($oper=='EQUAL'){
      $questionThatEnables = $copy_of_questions_map[$id_question];
      $valueThatEnables = $elems[1];
      //if($idOptionThatEnables!=NULL){
        $conditions_array = array();
        $conditions_array['enabled'] = array(
      	        ':input[name="'.$id_question.'"]' => array(
      	            array('value' => $valueThatEnables),
                ));
        if(isset($questionThatEnables->requirement)&&!empty($questionThatEnables->requirement)){
          $elems_2 = explode(",", (string)$questionThatEnables->requirement);
          $id_question_2 = substr($elems_2[0], 1);
          $questionThatEnables_2 = $copy_of_questions_map[$id_question_2];
          $valueThatEnables_2 = $elems_2[1];
          $conditions_array['enabled'][':input[name="'.$id_question_2.'"]'] = array(
      	            array('value' => $valueThatEnables_2),
                );
        }
        $form_array[$question_id]['#states'] = $conditions_array;
//       	$form_array[$question_id]['#states'] = array(
//       	    'enabled' => array(
//       	        ':input[name="'.$id_question.'"]' => array(
//       	            array('value' => $valueThatEnables),
//                 ),
//       	        ':input[name="14"]' => array(
//       	            array('value' => 1),
//                 ),
//             ),
//         );
        $form_array['question_condition_'.$question_id] = array(
          '#value' => (string)$question_obj->requirement,
          '#type' => 'hidden',
        );
      //}
    }
    unset($questions_map[$question_id]);
  }
}

/**
 * @} End of "defgroup case_task".
 */
