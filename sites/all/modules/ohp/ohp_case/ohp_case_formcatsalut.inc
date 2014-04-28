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
function ohp_case_formcatsalut_page() {

  $form = array();
  ohp_case_load_common($form);
  $page_array['page_header'] = array(
    '#theme' => 'ohp_case_header',
  );

  if(isset($_SESSION['admission_bean']) && isset($_SESSION['admission_bean']->id_admission) &&
      isset($_SESSION['case_bean']) && isset($_SESSION['case_bean']->id_case) &&
      isset($_GET['id_task']) && isset($_GET['id_form'])){
    $id_admission = $_SESSION['admission_bean']->id_admission;
    $id_case      = $_SESSION['case_bean']->id_case;
    $id_task      = $_GET['id_task'];
    $id_form      = $_GET['id_form'];
    if(!isset($_SESSION['ohp_token'])){
      drupal_set_message("ERROR: no token found");
      return array();
    }
    $token    = $_SESSION['ohp_token'];
    $questions_map = array();
    $form_xml = NULL;
    load_form($token ,$id_form, $form_xml, $questions_map);

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
      $descDiagnostic       = get_value_description($form_xml['form_id2']."_8",$questions_map);
      $descDiagnosticAltres = get_value_description($form_xml['form_id2']."_9",$questions_map);
      if(isset($descDiagnosticAltres) && $descDiagnosticAltres!=""){
      	$descDiagnostic .= " - ".$descDiagnosticAltres;
      }

      $dataSolicitud = get_value_description($form_xml['form_id1']."_5",$questions_map);
      $strDataSolicitud = "";
      if(isset($dataSolicitud) && $dataSolicitud!=""){
        $data_convert = date_create_from_format("Y-m-d",$dataSolicitud);
        $strDataSolicitud = date_format($data_convert, 'd/m/Y');
      }

      $duracio = get_value_description($form_xml['form_id4']."_39",$questions_map);

      $descSolicitant       = get_value_description($form_xml['form_id6']."_44",$questions_map);
      $descSolicitantAltres = get_value_description($form_xml['form_id6']."_45",$questions_map);
      if(isset($descSolicitantAltres) && $descSolicitantAltres!=""){
      	$descSolicitant .= " - ".$descSolicitantAltres;
      }

      //Variables del tractament
      $valueSistAdm = get_value_description($form_xml['form_id4']."_30",$questions_map);
      $descCanulaNasals = "";
      if($valueSistAdm=='1'){
      	$descCanulaNasals = t('Si');
      }else if(isset($valueSistAdm) && $valueSistAdm!=''){
      	$descCanulaNasals = t('No');
      }
      $fluxRepos = get_value_description($form_xml['form_id4']."_34",$questions_map);
      $horesDia = get_value_description($form_xml['form_id4']."_33",$questions_map);
      $observacions = get_value_description($form_xml['form_id5']."_43",$questions_map);

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
