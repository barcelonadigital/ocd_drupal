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

  try {
    $id_type="ADMI";
    $client = new SoapClient(null, array('location' => $GLOBALS["WS-ENDPOINT"], 'uri' => ""));
    $result = $client->form_get_summary($token,$id_form);
    if ( $result["ErrorMsg"] ) {
      drupal_set_message($result["ErrorMsg"]);
    } else {
      $form_xml = simplexml_load_string($result["result"]);
      $xml2 = '';
      if($form_xml->data->name=='Variables'){
        $filename = drupal_get_path('module', 'ohp_case').'/xml/form_variables.xml';
        $handle = fopen($filename, "r");
        $xml2 = fread($handle, filesize($filename));
        fclose($handle);
      }else if($form_xml->data->name=='CVSO'){
        $filename = drupal_get_path('module', 'ohp_case').'/xml/form_cvso.xml';
        $handle = fopen($filename, "r");
        $xml2 = fread($handle, filesize($filename));
        fclose($handle);
      }else{
        return array();
      }
      $values_map = array();
      foreach ($form_xml->data->questions->question as $question) {
        $question->question_id = str_replace("/", "_", $question->question_id);
        $values_map[(string)($question->question_id)] = $question->value;
      }
      $form_id1=$id_form+1;
      $form_id2=$id_form+2;
      $form_id3=$id_form+3;
      $form_id4=$id_form+4;
      $form_id5=$id_form+5;
      $form_id6=$id_form+6;
      $form_xml['form_id1']=$form_id1;
      $form_xml['form_id2']=$form_id2;
      $form_xml['form_id3']=$form_id3;
      $form_xml['form_id4']=$form_id4;
      $form_xml['form_id5']=$form_id5;
      $form_xml['form_id6']=$form_id6;
      $ids_array = array($form_id1,$form_id2,$form_id3,$form_id4,$form_id5,$form_id6);
      $form2_xml = simplexml_load_string($xml2);
      //$questions_map = array();
      foreach ($form2_xml->data->questions->question as $question2) {
        $question2->question_id = replace_ids($question2->question_id,$ids_array);
        $question2->condition   = replace_ids($question2->condition,$ids_array);
        $question2->formula     = replace_ids($question2->formula,$ids_array);
        if(isset($values_map[(string)$question2->question_id])){
          $question2->value       = $values_map[(string)$question2->question_id];
        }
        if(isset($question2->options->option)){
          foreach ($question2->options->option as $option) {
            if(isset($option->description) && isset($question2->value) && trim($option->description)==trim($question2->value)){
              $question2->value = $option->option_id;
            }
          }
        }
        $questions_map[(string)($question2->question_id)] = $question2;
      }
      //$form_xml->data->questions->question = $form2_xml->data->questions->question;
      //$form_xml->data->questions->more_question = $form2_xml->data->questions->question;
      //$form_xml->data->questions->addChild($form2_xml->data->questionss);
      //var_dump($form_xml['form_id1']);
      //var_dump($form2_xml->data->questions);

    }
  } catch (SoapFault $fault) {
    drupal_set_message("SOAP Fault: (faultcode: {$fault->faultcode}, faultstring: {$fault->faultstring})");
  }
}

/**
 * @} End of "defgroup case_task".
 */
