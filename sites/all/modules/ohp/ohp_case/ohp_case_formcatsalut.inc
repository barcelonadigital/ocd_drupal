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

require_once "phpwebdriver/WebDriver.php";

/**
 * Constructs a descriptive page.
 *
 * Our menu maps this function to the path 'ohp/ohp_case_formcatsalut_robot'.
 */
function ohp_case_formcatsalut_robot() {
  //********************************************************************
  //IT REQUIRES TO RUN: java -jar selenium-server-standalone-2.42.2.jar
  //********************************************************************
  $webdriver = new WebDriver("localhost", "4444");
  $webdriver->connect("firefox");
  $webdriver->get("https://salut.gencat.net/pls/gsa/gsapk030.inici_portal");
  $usernameInput = $webdriver->findElementBy(LocatorStrategy::name, "v_nom_usu");
  if ($usernameInput) {
      $usernameInput->sendKeys(array("user" ) );
  }
  $passwordInput = $webdriver->findElementBy(LocatorStrategy::name, "v_clau");
  if ($passwordInput) {
      $passwordInput->sendKeys(array("user" ) );
  }
  $buttonSubmit = $webdriver->findElementBy(LocatorStrategy::xpath, "/html/body/table[3]/tbody/tr[1]/td[3]/table[2]/tbody/tr[5]/td[1]/a");
  if ($buttonSubmit) {
      //$buttonSubmit->click();
  }
  sleep( 3 );
  $webdriver->close();

  $id_admission = $_SESSION['admission_bean']->id_admission;
  $id_case      = $_SESSION['case_bean']->id_case;
  $id_task      = $_GET['id_task'];
  $id_form      = $_GET['id_form'];

  drupal_set_message(t('La sol·licitud s\'ha enviat correctament.'));
  drupal_goto('ohp/ohp_case_formcatsalut', array('query' => array('id_form' => $id_form, 'id_task' => $id_task,
              'id_admission' => $id_admission, 'id_case' => $id_case)));
}

/**
 * Constructs a descriptive page.
 *
 * Our menu maps this function to the path 'ohp/ohp_case_formcatsalut'.
 */
function ohp_case_formcatsalut_page() {

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
    load_form(NULL ,$id_form, $form_xml, $questions_map);

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
    $descDiagnostic   = get_value_description("14",$questions_map);
    $descDiagnostic_2 = get_value_description("15",$questions_map);
    $descDiagnostic_3 = get_value_description("16",$questions_map);
    $descDiagnostic_4 = get_value_description("17",$questions_map);
    $descDiagnostic_5 = get_value_description("18",$questions_map);
    if(isset($descDiagnostic_2) && $descDiagnostic_2!=""){
    	$descDiagnostic .= " - ".$descDiagnostic_2;
    }
    if(isset($descDiagnostic_3) && $descDiagnostic_3!=""){
    	$descDiagnostic .= " - ".$descDiagnostic_3;
    }
    if(isset($descDiagnostic_4) && $descDiagnostic_4!=""){
    	$descDiagnostic .= " - ".$descDiagnostic_4;
    }
    if(isset($descDiagnostic_5) && $descDiagnostic_5!=""){
    	$descDiagnostic .= " - ".$descDiagnostic_5;
    }

    $strDataSolicitud = get_value_description("2",$questions_map);

    $duracio = get_value_description("57",$questions_map);

    $descSolicitant       = get_value_description("8",$questions_map);
    $descSolicitantAltres = get_value_description("9",$questions_map);
    if(isset($descSolicitantAltres) && $descSolicitantAltres!=""){
    	$descSolicitant .= " - ".$descSolicitantAltres;
    }

    //Treatment variables
    $valueSistAdm = get_value_description("44",$questions_map);
    $descCanulaNasals = "";
    if($valueSistAdm=='1'){
    	$descCanulaNasals = t('Si');
    }else if(isset($valueSistAdm) && $valueSistAdm!=''){
    	$descCanulaNasals = t('No');
    }
    $fluxRepos = get_value_description("47",$questions_map);
    $horesDia = get_value_description("50",$questions_map);
    $observacions = get_value_description("60",$questions_map);

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
  }
//   $form['ohp_case_formcatsalut_arguments'] = array(
//     //Title serves as page subtitle
//     '#title' => t('Sol·licitud d\'OCD a CatSalut'),
//     '#markup' => '<iframe src="https://salut.gencat.net/pls/gsa/gsapk030.portal" style="width:1000px; height:375px;"></iframe>',
//   );

  $page_array['main'] = array(
    '#theme' => 'ohp_case_body',
  );
  $page_array['main']['pager_container'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('content','full'),
    ),
  );

  $task_status='';
  if(isset($id_task) && $id_task!=''){
    $id_task = $_GET['id_task'];
    $task_bean = get_task($id_task);
    $task_status = $task_bean->status;
  }
  $page_array['main']['pager_container']['controls'] = array(
    '#theme' => 'ohp_case_catsalutctrl',
    '#selected_option' => t('Sol·licitud d\'OCD a CatSalut'),
    '#task_status' => $task_status,
  );
  $page_array['main']['pager_container']['pager_table'] = $form;

  drupal_add_css(drupal_get_path('module', 'ohp_case') . '/css/ohp_case_form.css');
  return $page_array;
}
