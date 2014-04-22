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
function ohp_case_form_page($form, &$form_state) {

  ohp_case_load_common($form);

  $task_bean = new stdClass();
  $items = array();
  if(isset($_SESSION['admission_bean']) && isset($_SESSION['admission_bean']->id_admission) &&
      isset($_SESSION['case_bean']) && isset($_SESSION['case_bean']->id_case) &&
      isset($_GET['id_task']) && isset($_GET['id_form'])){
    $id_admission = $_SESSION['admission_bean']->id_admission;
    $id_case      = $_SESSION['case_bean']->id_case;
    $id_task      = $_GET['id_task'];
    $id_form      = $_GET['id_form'];
    try {
      if(!isset($_SESSION['ohp_token'])){
        drupal_set_message("ERROR: no token found");
        return array();
      }
      $token    = $_SESSION['ohp_token'];
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
        $ids_array = array($form_id1,$form_id2,$form_id3,$form_id4,$form_id5,$form_id6);
        $form2_xml = simplexml_load_string($xml2);
        $questions_map = array();
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
        //var_dump($form2_xml->data->questions);

        if($form_xml->data->name=='Variables'){
          $form['#questions'] = $form2_xml->data->questions;
          $form['#after_build'][] = 'ohp_case_after_build'; //Calls function - See more at: http://www.appnovation.com/blog/drupal-tip-using-formafter-build#sthash.a6t5iANp.dpuf
          $form['submit_area'] = array(
            '#type' => 'container',
          );
          $form['submit_area']['submit'] = array(
            '#type' => 'submit',
            '#value' => t('Submit'),
          );
          $form['column_left'] = array(
            '#type' => 'container',
            '#attributes' => array(
              'class' => array('column-left'),
            ),
          );
          $form['column_left']['diagnostic'] = array(
            '#type' => 'fieldset',
            '#title' => t('Diagnòstic'),
            '#collapsible' => TRUE,
            '#collapsed' => FALSE,
          );
          add_question($form['column_left']['diagnostic'],$questions_map,$form_id2."_8");
          add_question($form['column_left']['diagnostic'],$questions_map,$form_id2."_9");
          add_question($form['column_left']['diagnostic'],$questions_map,$form_id1."_5");
          add_question($form['column_left']['diagnostic'],$questions_map,$form_id1."_6");
          add_question($form['column_left']['diagnostic'],$questions_map,$form_id1."_7");
          add_question($form['column_left']['diagnostic'],$questions_map,$form_id4."_24");
          add_question($form['column_left']['diagnostic'],$questions_map,$form_id6."_44");
          add_question($form['column_left']['diagnostic'],$questions_map,$form_id6."_45");
          $form['column_left']['equip'] = array(
            '#type' => 'fieldset',
            '#title' => t('Equip teràpia respiratòria'),
            '#collapsible' => TRUE,
            '#collapsed' => FALSE,
          );
          add_question($form['column_left']['equip'],$questions_map,$form_id4."_25");
          add_question($form['column_left']['equip'],$questions_map,$form_id4."_26");
          add_question($form['column_left']['equip'],$questions_map,$form_id4."_27");
          add_question($form['column_left']['equip'],$questions_map,$form_id4."_28");
          add_question($form['column_left']['equip'],$questions_map,$form_id4."_29");
          add_question($form['column_left']['equip'],$questions_map,$form_id4."_30");
          add_question($form['column_left']['equip'],$questions_map,$form_id4."_31");
          add_question($form['column_left']['equip'],$questions_map,$form_id4."_32");
          add_question($form['column_left']['equip'],$questions_map,$form_id4."_34");
          add_question($form['column_left']['equip'],$questions_map,$form_id4."_35");
          add_question($form['column_left']['equip'],$questions_map,$form_id4."_36");
          add_question($form['column_left']['equip'],$questions_map,$form_id4."_33");
          add_question($form['column_left']['equip'],$questions_map,$form_id4."_37");
          add_question($form['column_left']['equip'],$questions_map,$form_id4."_38");
          add_question($form['column_left']['equip'],$questions_map,$form_id4."_41");
          add_question($form['column_left']['equip'],$questions_map,$form_id4."_42");
          add_question($form['column_left']['equip'],$questions_map,$form_id4."_43");
          $form['column_right'] = array(
            '#type' => 'container',
            '#attributes' => array(
              'class' => array('column-right'),
            ),
          );
          $form['column_right']['proves'] = array(
            '#type' => 'fieldset',
            '#title' => t('Proves complementàries'),
            '#collapsible' => TRUE,
            '#collapsed' => FALSE,
          );
  		  //espiro
          add_question($form['column_right']['proves'],$questions_map,$form_id3."_10");
          add_question($form['column_right']['proves'],$questions_map,$form_id3."_11");
          add_question($form['column_right']['proves'],$questions_map,$form_id3."_12");
          add_question($form['column_right']['proves'],$questions_map,$form_id3."_13");
          add_question($form['column_right']['proves'],$questions_map,$form_id3."_14");
  		  //gaso
  		  add_question($form['column_right']['proves'],$questions_map,$form_id3."_104");
          add_question($form['column_right']['proves'],$questions_map,$form_id3."_15");
          add_question($form['column_right']['proves'],$questions_map,$form_id3."_16");
          add_question($form['column_right']['proves'],$questions_map,$form_id3."_17", true);
          add_question($form['column_right']['proves'],$questions_map,$form_id3."_18");
          add_question($form['column_right']['proves'],$questions_map,$form_id3."_19");
          add_question($form['column_right']['proves'],$questions_map,$form_id3."_20");
          add_question($form['column_right']['proves'],$questions_map,$form_id3."_21");
          add_question($form['column_right']['proves'],$questions_map,$form_id3."_22");
  		  //pulsio
  		  add_question($form['column_right']['proves'],$questions_map,$form_id3."_107");
          add_question($form['column_right']['proves'],$questions_map,$form_id3."_23");
        }else if($form_xml->data->name=='CVSO'){

        }
      }
    } catch (SoapFault $fault) {
      drupal_set_message("SOAP Fault: (faultcode: {$fault->faultcode}, faultstring: {$fault->faultstring})");
    }
  }
  return $form;
}

/**
 * Submit handler for ohp_case_form_page().
 */
function ohp_case_form_page_submit($form, &$form_state) {

  if(isset($_SESSION['admission_bean']) && isset($_SESSION['admission_bean']->id_admission) &&
      isset($_SESSION['case_bean']) && isset($_SESSION['case_bean']->id_case) &&
      isset($_GET['id_task']) && isset($_GET['id_form'])){

    $id_form      = $_GET['id_form'];

    // Exclude unnecessary elements.
    unset($form_state['values']['submit'], $form_state['values']['form_id'], $form_state['values']['op'], $form_state['values']['form_token'], $form_state['values']['form_build_id']);

    $doc = new DomDocument("1.0", 'utf-8');
    $doc->standalone = true;
    $root = $doc->createElement("questions");
    $root = $doc->appendChild($root);

    foreach ($form_state['values'] as $key => $value) {
      if(strrpos($key, "question_type")===FALSE){
        $question = colgar_hijo( $doc, $root, "question");
        $question_id    = str_replace("_", "/", (string)$key);
        $question_type  = $form_state['values']['question_type_'.(string)$key];
        $question_value = NULL;
        if($question_type=='DATE'){
          $question_value = date("Y-m-d", mktime(0, 0, 0, $value['month'], $value['day'], $value['year']));
        }else{
          $question_value = (string)$value;
        }
        colgar_hijo( $doc, $question, "question_id", $question_id);
        if($question_type=='VERTICAL_RADIO' || $question_type=='HORIZONTAL_RADIO'){
          colgar_hijo( $doc, $question, "option_id", $question_value);
        }else{
          colgar_hijo( $doc, $question, "value", $question_value);
        }
      }
    }

    $XML = $doc->saveXML();

    try {
      if(!isset($_SESSION['ohp_token'])){
        drupal_set_message("ERROR: no token found");
        return array();
      }
      $token    = $_SESSION['ohp_token'];
      $id_type="ADMI";
      $client = new SoapClient(null, array('location' => $GLOBALS["WS-ENDPOINT"], 'uri' => ""));
      $result = $client->form_set_all_answers($token,$id_form,$XML);
      if ( $result["ErrorMsg"] ) {
        drupal_set_message($result["ErrorMsg"]);
      }else{
        drupal_set_message(t('El formulari s\'ha desat corectament.'));
      }
    } catch (SoapFault $fault) {
      drupal_set_message("SOAP Fault: (faultcode: {$fault->faultcode}, faultstring: {$fault->faultstring})");
    }
  }
}

function ohp_case_after_build($form, &$form_state) {
  $field_formulas = array();
  foreach ($form['#questions']->question as $question) {
    if(isset($question->formula)&&!empty($question->formula)){
      $field_formulas[(string)$question->question_id]=(string)$question->formula;
    }
  }
  drupal_add_js(array('field_formulas' => $field_formulas), array('type' => 'setting'));
  drupal_add_js(drupal_get_path('module', 'ohp_case') .'/js/ohp_case_form.js');
  drupal_add_css(drupal_get_path('module', 'ohp_case') . '/css/ohp_case_form.css');
  return $form;
}

function add_question(&$form_array, $questions_map, $question_id, $hidden = false){
  if(isset($questions_map[$question_id])){
    $question_obj = $questions_map[$question_id];
    $form_array['question_type_'.$question_id] = array(
      '#value' => $question_obj->type,
      '#type' => 'hidden',
    );
    $form_array[$question_id] = array(
      '#title' => $question_obj->description,
    );
    $attributes_array = array();
    if($question_obj->type=='VERTICAL_RADIO' || $question_obj->type=='HORIZONTAL_RADIO'){
      $form_array[$question_id]['#type'] = 'select';
      $form_array[$question_id]['#empty_value'] = '';
      //$form_array[$question_id]['#empty_option'] = TRUE;
      foreach ($question_obj->options->option as $option) {
        $form_array[$question_id]['#options'][(string)$option->option_id]=(string)$option->description;
      }
    }else if($question_obj->type=='TEXT' || $question_obj->type=='NUMERICAL'){
      $form_array[$question_id]['#type'] = 'textfield';
    }else if($question_obj->type=='FORMULA'){
      $form_array[$question_id]['#type'] = 'textfield';
    }else if($question_obj->type=='TEXT_AREA'){
      $form_array[$question_id]['#type'] = 'textarea';
    }else if($question_obj->type=='DATE'){
      $form_array[$question_id]['#type'] = 'date';
    }else if($question_obj->type=='STATIC_TEXT'){
      $form_array[$question_id]['#type'] = 'item';
    }
    if($question_obj->type=='FORMULA'){
      $form_array[$question_id]['#attributes'] = array('readonly' => 'readonly');
    }else{
      $form_array[$question_id]['#attributes'] = array('onchange' => 'checkFormulas()');
    }
    if($hidden){
      $form_array[$question_id]['#prefix'] = '<div style="display:none;">';
      $form_array[$question_id]['#suffix'] = '</div>';
    }
    if(isset($question_obj->value)&&!empty($question_obj->value)){
      if($question_obj->type=='DATE'){
        $arr = date_parse_from_format("Y-m-d",$question_obj->value);
        $form_array[$question_id]['#default_value'] = array('year' => $arr['year'], 'month' => $arr['month'],
           'day' => $arr['day']);
      }else{
        $form_array[$question_id]['#default_value'] = (string)$question_obj->value;
      }
    }
    if(isset($question_obj->condition)&&!empty($question_obj->condition)){
      $elems = explode(",", (string)$question_obj->condition);
      $id_question = substr($elems[0], 1);
      $oper = $elems[1];
      if($oper=='EQUAL'){
      	$valueThatEnables = $elems[2];
      	$form_array[$question_id]['#states'] = array(
      	    'visible' => array(
      	        ':input[name="'.$id_question.'"]' => array(
      	            array('value' => $valueThatEnables),
                ),
            ),
        );
      }
    }
  }
}

/**
 * @} End of "defgroup case_task".
 */
