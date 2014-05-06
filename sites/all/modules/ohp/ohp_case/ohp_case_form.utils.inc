<?php

/**
 * @file
 * A file with form utils.
 */


/**
 * Constructs a descriptive page.
 *
 * Our menu maps this function to the path 'ohp/tasks_assigned'.
 */
function load_form($token ,$id_form, &$form_xml, &$questions_map) {

  $form_xml = get_form($id_form);

//   $form_xml['form_id1']=$id_form;
//   $form_xml['form_id2']=$id_form;
//   $form_xml['form_id3']=$id_form;
//   $form_xml['form_id4']=$id_form;
//   $form_xml['form_id5']=$id_form;
//   $form_xml['form_id6']=$id_form;

  $result = get_form_answers($id_form);
  foreach ($result as $row) {
    $questions_map[$row->id_question] = $row;
    if($questions_map[$row->id_question]->type=='VERTICAL_RADIO' ||
        $questions_map[$row->id_question]->type=='HORIZONTAL_RADIO'){
      $questions_map[$row->id_question]->value = $questions_map[$row->id_question]->id_option;
    }
  }
  $result = get_formanswers_options($id_form);
  foreach ($result as $row) {
    $question = $questions_map[$row->id_question];
    if(!isset($question->options->option)){
      $question->options = new stdClass();
      $question->options->option=array();
    }
    if($question->id_question==$row->id_question){
      $question->options->option[]=$row;
    }
  }
}

/**
 * @} End of "defgroup case_task".
 */
