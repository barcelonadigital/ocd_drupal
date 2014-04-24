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
function ohp_case_formcatsalut_page() {

  $form = array();
  ohp_case_load_common($form);
  $page_array['page_header'] = array(
    '#theme' => 'ohp_case_header',
  );

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

        if($form_xml->data->name=='Variables'){

          $form['columns_container'] = array(
            '#type' => 'container',
            '#attributes' => array(
              'class' => array('columnboxes','clearfix'),
            ),
          );
          $form['columns_container']['column_left'] = array(
            '#type' => 'container',
            '#attributes' => array(
              'class' => array('column','por2'),
            ),
          );
          $form['columns_container']['column_left']['content'] = array(
            '#type' => 'fieldset',
            '#title' => t('Prescripció de tractament'),
            '#collapsible' => FALSE,
            '#collapsed' => FALSE,
          );
          $form['columns_container']['column_right'] = array(
            '#type' => 'container',
            '#attributes' => array(
              'class' => array('column','por2'),
            ),
          );
          $form['columns_container']['column_right']['content'] = array(
            '#type' => 'fieldset',
            '#title' => t('Variables del tractament'),
            '#collapsible' => FALSE,
            '#collapsed' => FALSE,
          );

          $nhc = "";
          $telefon1 = "";
          $telefon2 = "";
          $telefon3 = "";
          if(isset($_SESSION['case_bean'])){
            if(isset($_SESSION['case_bean']->nhc)){
              $nhc = $_SESSION['case_bean']->nhc;
            }
            if(isset($_SESSION['case_bean']->contact) &&
                isset($_SESSION['case_bean']->contact->phones) &&
                !empty($_SESSION['case_bean']->contact->phones)){
              foreach ($_SESSION['case_bean']->contact->phones as $phone) {
                if(isset($phone->number) && $phone->number!=""){
                  if($phone->type=="home"){
                    $telefon1 = $phone->number;
                  }else if($phone->type=="work"){
                    $telefon2 = $phone->number;
                  }else if($phone->type=="ext"){
                    $telefon3 = $phone->number;
                  }
                }
              }
            }
          }
          $descDiagnostic       = get_value_description($form_id2."_8",$questions_map);
          $descDiagnosticAltres = get_value_description($form_id2."_9",$questions_map);
          if(isset($descDiagnosticAltres) && $descDiagnosticAltres!=""){
          	$descDiagnostic .= " - ".$descDiagnosticAltres;
          }

          $dataSolicitud = get_value_description($form_id1."_5",$questions_map);
          $strDataSolicitud = "";
          if(isset($dataSolicitud) && $dataSolicitud!=""){
            $data_convert = date_create_from_format("Y-m-d",$dataSolicitud);
            $strDataSolicitud = date_format($data_convert, 'd/m/Y');
          }

          $duracio = get_value_description($form_id4."_39",$questions_map);

          $descSolicitant       = get_value_description($form_id6."_44",$questions_map);
          $descSolicitantAltres = get_value_description($form_id6."_45",$questions_map);
          if(isset($descSolicitantAltres) && $descSolicitantAltres!=""){
          	$descSolicitant .= " - ".$descSolicitantAltres;
          }

          //Variables del tractament
          $valueSistAdm = get_value_description($form_id4."_30",$questions_map);
          $descCanulaNasals = "";
          if($valueSistAdm=='1'){
          	$descCanulaNasals = t('Si');
          }else if(isset($valueSistAdm) && $valueSistAdm!=''){
          	$descCanulaNasals = t('No');
          }
          $fluxRepos = get_value_description($form_id4."_34",$questions_map);
          $horesDia = get_value_description($form_id4."_33",$questions_map);
          $observacions = get_value_description($form_id5."_43",$questions_map);

          $form['columns_container']['column_left']['content'][] = array(
            '#markup' => '<span class="question">'.t('Prescripció de tractament').'</span> <span class="answer">'.$strDataSolicitud.'</span><br/>',
          );
          $form['columns_container']['column_left']['content'][] = array(
            '#markup' => '<span class="question">'.t('Número d\'Història Clínica').'</span> <span class="answer">'.$nhc.'</span><br/>',
          );
          $form['columns_container']['column_left']['content'][] = array(
            '#markup' => '<span class="question">'.t('Telèfon de pacient 1').'</span> <span class="answer">'.$telefon1.'</span><br/>',
          );
          $form['columns_container']['column_left']['content'][] = array(
            '#markup' => '<span class="question">'.t('Telèfon de pacient 2').'</span> <span class="answer">'.$telefon2.'</span><br/>',
          );
          $form['columns_container']['column_left']['content'][] = array(
            '#markup' => '<span class="question">'.t('Telèfon de pacient 3').'</span> <span class="answer">'.$telefon3.'</span><br/>',
          );
          $form['columns_container']['column_left']['content'][] = array(
            '#markup' => '<span class="question">'.t('Diagnòstic').'</span> <span class="answer">'.$descDiagnostic.'</span><br/>',
          );
          $form['columns_container']['column_left']['content'][] = array(
            '#markup' => '<span class="question">'.t('Periode de validesa del tractament').'</span> <span class="answer">'.$duracio.'</span><br/>',
          );
          $form['columns_container']['column_left']['content'][] = array(
            '#markup' => '<span class="question">'.t('Metge prescriptor').'</span> <span class="answer">'.$descSolicitant.'</span><br/>',
          );

          $form['columns_container']['column_right']['content'][] = array(
            '#markup' => '<span class="question">'.t('Ulleres nasals').'</span> <span class="answer">'.$descCanulaNasals.'</span><br/>',
          );
          $form['columns_container']['column_right']['content'][] = array(
            '#markup' => '<span class="question">'.t('Flux repos I/MIN').'</span> <span class="answer">'.$fluxRepos.'</span><br/>',
          );
          $form['columns_container']['column_right']['content'][] = array(
            '#markup' => '<span class="question">'.t('Hores/Dia&gt;15/').'</span> <span class="answer">'.$horesDia.'</span><br/>',
          );
          $form['columns_container']['column_right']['content'][] = array(
            '#markup' => '<span class="question">'.t('Observacions').'</span> <span class="answer">'.$observacions.'</span><br/>',
          );
        }else if($form_xml->data->name=='CVSO'){

        }
      }
    } catch (SoapFault $fault) {
      drupal_set_message("SOAP Fault: (faultcode: {$fault->faultcode}, faultstring: {$fault->faultstring})");
    }
  }
  $form['ohp_case_formcatsalut_arguments'] = array(
    //Title serves as page subtitle
    '#title' => t('Sol·licitud d\'OCD a CatSalut'),
    '#markup' => '<iframe src="https://salut.gencat.net/pls/gsa/gsapk030.portal" style="width:690px; height:375px;"></iframe>',
  );

  $page_array['main'] = array(
    '#theme' => 'ohp_case_body',
  );
  $page_array['main']['menu_container'] = array(
    '#theme' => 'ohp_case_menu',
    'is_active_menu_formularis' => TRUE,
  );
  $page_array['main']['pager_container'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('content'),
    ),
  );
  $form['#prefix'] = '<h2 class="newsession">'.t('Sol·licitud d\'OCD a CatSalut').'</h2>';
  $page_array['main']['pager_container']['pager_table'] = $form;
//   array(
//     '#theme' => 'table',
//     '#header' => array(t('Data'), t('Tasca')),
//     '#rows' => $chunks[$current_page],
//     '#empty' => t('No hi ha elements per mostrar.'),
//     '#prefix' => '<h2 class="asses">Tasques</h2>',
//   );

  drupal_add_css(drupal_get_path('module', 'ohp_case') . '/css/ohp_case_form.css');
  return $page_array;
}

function get_value_description($question_id, $questions_map) {
  if(isset($questions_map[$question_id])){
    $question_obj = $questions_map[$question_id];
    if($question_obj->type=='VERTICAL_RADIO' || $question_obj->type=='HORIZONTAL_RADIO'){
//var_dump($question_obj);
      foreach ($question_obj->options->option as $option) {
        if(isset($option->value) && isset($question_obj->value) && trim($option->value)==trim($question_obj->value)){
          return (string)$option->description;
        }
      }
    }else{
      return (string)$question_obj->value;
    }
  }
  return "";
}


/**
 * @} End of "defgroup case_task".
 */
