<?php

/**
 * @file
 * A file with utils and constants.
 */

$GLOBALS["WS-ENDPOINT"]="http://dev3.linkcare.es/ws/ServerWSDL.php";


function colgar_hijo( $doc, $padre, $etiqueta, $valor = "", $numeric = false )
{
    $aux1 = $doc->createElement($etiqueta);
    $aux1 = $padre->appendChild($aux1);
    if ($valor != "") {
        $aux2 = $doc->createTextNode($valor);
        $value = $aux1->appendChild($aux2);
    } else if ($numeric) {
        $aux2 = $doc->createTextNode("0");
        $value = $aux1->appendChild($aux2);
    }
    return $aux1;
}


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

function get_numeric_array(){
  return array('21','22','23','24','25','28','29','32','33','35','38','46','47','48','49','66','67','72','73','74','82','83','84','85','86','103');
}

function get_value_description($question_id, $questions_map) {
  //var_dump(2);
  if(isset($questions_map[$question_id])){
    $question_obj = $questions_map[$question_id];
    //var_dump($question_obj);
    if(in_array($question_id, get_numeric_array())){
      $num_decimals = 0;
      if(isset($question_obj->num_decimals)){
        $num_decimals = $question_obj->num_decimals;
      }
      return number_format((float)$question_obj->value,$num_decimals,",",".");
    }else
    if($question_obj->type=='VERTICAL_RADIO' || $question_obj->type=='HORIZONTAL_RADIO'){
      foreach ($question_obj->options->option as $option) {
        if(isset($option->id_option) && isset($question_obj->value) && trim($option->id_option)==trim($question_obj->value)){
          return (string)$option->description;
        }
      }
    }else if($question_obj->type=='DATE'){
      //var_dump($question_obj);
      return date('d/m/Y',(string)$question_obj->value);
    }else{
      return (string)$question_obj->value;
    }
  }
  return "";
}