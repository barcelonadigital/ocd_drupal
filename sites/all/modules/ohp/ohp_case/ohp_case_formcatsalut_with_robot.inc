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

include_once 'ohp_case_formcatsalut.utils.inc';
require_once "phpwebdriver/WebDriver.php";

/**
 * Constructs a descriptive page.
 *
 * Our menu maps this function to the path 'ohp/ohp_case_formcatsalut_robot'.
 */
function ohp_case_formcatsalut_robot() {

  if(isset($_SESSION['admission_bean']) && isset($_SESSION['admission_bean']->id_admission) &&
      isset($_SESSION['case_bean']) && isset($_SESSION['case_bean']->id_case) &&
      isset($_GET['id_task']) && isset($_GET['id_form']) &&
      isset($_GET['is_discharge']) && ($_GET['is_discharge']=="true" || $_GET['is_discharge']=="false")){

    $id_admission = $_SESSION['admission_bean']->id_admission;
    $id_case      = $_SESSION['case_bean']->id_case;
    $id_task      = $_GET['id_task'];
    $id_form      = $_GET['id_form'];
    $is_discharge = $_GET['is_discharge'];
    $questions_map = array();
    load_form(NULL ,$id_form, $form_xml, $questions_map);

    //********************************************************************
    //IT REQUIRES TO RUN: java -jar selenium-server-standalone-2.42.2.jar
    //********************************************************************
    $webdriver = new WebDriver("localhost", "4444");
    $webdriver->connect("firefox");

    //$webdriver->get("https://salut.gencat.net/pls/gsa/gsapk030.inici_portal");
    $webdriver->get("http://localhost/buildkit/oxigen/000AccesUsuari.htm");
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
        $buttonSubmit->click();
    }
    //sleep( 3 );
    $linkSubmit = $webdriver->findElementBy(LocatorStrategy::xpath, "/html/body/table[3]/tbody/tr[1]/td[3]/table[2]/tbody/tr[4]/td[1]/table/tbody/tr[1]/td[3]/a");
    if ($linkSubmit) {
        $linkSubmit->click();
    }
    //sleep( 3 );
    $fieldCip = $webdriver->findElementBy(LocatorStrategy::xpath, "//*[@id=\"form:variable_37143_1_2227_37143_0\"]");
    if ($fieldCip) {
        $fieldCip->sendKeys(array("ROVI0101000000000" ) );
    }
    $linkSubmit = $webdriver->findElementBy(LocatorStrategy::xpath, "//*[@id=\"form:executeFilterButton\"]");
    if ($linkSubmit) {
        $linkSubmit->click();
    }
    //sleep( 3 );
    $linkSubmit = $webdriver->findElementBy(LocatorStrategy::xpath, "//*[@id=\"form:newCaseButtton\"]");
    if ($linkSubmit) {
        $linkSubmit->click();
    }
    //sleep( 3 );
    $fieldCip = $webdriver->findElementBy(LocatorStrategy::xpath, "//*[@id=\"form:INPUT_2227_37143_0\"]");
    if ($fieldCip) {
        $fieldCip->sendKeys(array("ROVI0101000000000" ) );
    }
    $fieldName = $webdriver->findElementBy(LocatorStrategy::xpath, "//*[@id=\"form:INPUT_2227_37143_585\"]");
    if ($fieldName) {
        $fieldName->sendKeys(array("Jordi" ) );
    }
    $fieldSurname = $webdriver->findElementBy(LocatorStrategy::xpath, "//*[@id=\"form:INPUT_2227_37143_603\"]");
    if ($fieldSurname) {
        $fieldSurname->sendKeys(array("Roda" ) );
    }
    $fieldBirthdate = $webdriver->findElementBy(LocatorStrategy::xpath, "//*[@id=\"form:INPUT_2227_37143_607\"]");
    if ($fieldBirthdate) {
        $fieldBirthdate->sendKeys(array("01/01/1981" ) );
    }
    $fieldGender = $webdriver->findElementBy(LocatorStrategy::xpath, "//*[@id=\"form:INPUT_2227_37143_516\"]");
    if ($fieldGender) {
        $fieldGender->sendKeys(array("HOME" ) );
    }
    $fieldAddress = $webdriver->findElementBy(LocatorStrategy::xpath, "//*[@id=\"form:INPUT_2227_37143_587\"]");
    if ($fieldAddress) {
        $fieldAddress->sendKeys(array("C. Roc Boronat, 1" ) );
    }
    $fieldCity = $webdriver->findElementBy(LocatorStrategy::xpath, "//*[@id=\"form:INPUT_2227_37143_517\"]");
    if ($fieldCity) {
        $fieldCity->sendKeys(array("Barcelona" ) );
    }
    $fieldAbs = $webdriver->findElementBy(LocatorStrategy::xpath, "//*[@id=\"form:INPUT_2227_37143_497\"]");
    if ($fieldAbs) {
        $fieldAbs->sendKeys(array("1" ) );
    }
    $linkSubmit = $webdriver->findElementBy(LocatorStrategy::xpath, "//*[@id=\"form:save\"]");
    if ($linkSubmit) {
        $linkSubmit->click();
    }
    //sleep( 3 );

    if($is_discharge=="true"){

      $linkSubmit = $webdriver->findElementBy(LocatorStrategy::xpath, "//*[@id=\"O37144_7691477\"]/div[8]/div[1]/img[7]");
      if ($linkSubmit) {
          $linkSubmit->click();
      }
      //sleep( 3 );

      //$webdriver->get("http://localhost/buildkit/oxigen/230Baixadelaprescripcio.htm");

      $str_data_baixa = get_data_baixa ($questions_map);
      $str_motiu_baixa= get_motiu_baixa ($questions_map);
      $data_baixa  = $webdriver->findElementBy(LocatorStrategy::xpath, "//*[@id=\"form:INPUT_2227_37186_114180\"]");
      if ($data_baixa) {
          $data_baixa->sendKeys(array($str_data_baixa ) );
      }
      $motiu_baixa = $webdriver->findElementBy(LocatorStrategy::xpath, "//*[@id=\"form:INPUT_2227_37186_114162\"]");
      if ($motiu_baixa) {
          $motiu_baixa->sendKeys(array($str_motiu_baixa ) );
      }
//       //sleep( 3 );
      $linkSubmit = $webdriver->findElementBy(LocatorStrategy::xpath, "//*[@id=\"form:save\"]");
      if ($linkSubmit) {
          $linkSubmit->click();
      }

    }else if($is_discharge=="false"){

      $linkSubmit = $webdriver->findElementBy(LocatorStrategy::xpath, "//*[@id=\"O37143_7691476\"]/div[2]/div[1]/img[5]");
      if ($linkSubmit) {
          $linkSubmit->click();
      }
      //sleep( 3 );

      //$webdriver->get("http://localhost/buildkit/oxigen/200Prescripciodetractament.htm");

      $str_data_prescripcio = get_data_prescripcio ($questions_map);
      $str_unitat_proveidora = get_unitat_proveidora ($questions_map);
      $str_tipus_tractament = get_tipus_tractament ($questions_map);
      $str_tipus_prestacio = get_tipus_prestacio ($questions_map);
      $str_nhc = get_nhc ($questions_map);
      $str_telefon = get_telefon ($questions_map);
      $str_diagnostic = get_diagnostic ($questions_map);
      $str_duracio = get_duracio ($questions_map);
      $str_metge = get_metge ($questions_map);

      $fieldDataPres = $webdriver->findElementBy(LocatorStrategy::xpath, "//*[@id=\"form:INPUT_2227_37144_113467\"]");
      if ($fieldDataPres) {
          $fieldDataPres->sendKeys(array($str_data_prescripcio ) );
      }
      $fieldUnitat = $webdriver->findElementBy(LocatorStrategy::xpath, "//*[@id=\"form:INPUT_2227_37144_113468\"]");
      if ($fieldUnitat) {
          $fieldUnitat->sendKeys(array($str_unitat_proveidora ) );
      }
      $fieldTractament = $webdriver->findElementBy(LocatorStrategy::xpath, "//*[@id=\"form:INPUT_2227_37144_113469\"]");
      if ($fieldTractament) {
          $fieldTractament->sendKeys(array($str_tipus_tractament ) );
      }
      $fieldPrestacio = $webdriver->findElementBy(LocatorStrategy::xpath, "//*[@id=\"form:INPUT_2227_37144_113470\"]");
      if ($fieldPrestacio) {
          $fieldPrestacio->sendKeys(array($str_tipus_prestacio ) );
      }
      $fieldNhc = $webdriver->findElementBy(LocatorStrategy::xpath, "//*[@id=\"form:INPUT_2227_37144_113471\"]");
      if ($fieldNhc) {
          $fieldNhc->sendKeys(array($str_nhc ) );
      }
    //   $fieldTelefon = $webdriver->findElementBy(LocatorStrategy::xpath, "//*[@id=\"form:INPUT_2227_37144_113472\"]");
    //   if ($fieldTelefon) {
    //       $fieldTelefon->sendKeys(array($str_telefon ) );
    //   }
      $fieldDiagnostic = $webdriver->findElementBy(LocatorStrategy::xpath, "//*[@id=\"form:INPUT_2227_37144_113473\"]");
      if ($fieldDiagnostic) {
          $fieldDiagnostic->sendKeys(array($str_diagnostic ) );
      }
      $fieldPeriode = $webdriver->findElementBy(LocatorStrategy::xpath, "//*[@id=\"form:INPUT_2227_37144_113477\"]");
      if ($fieldPeriode) {
          $fieldPeriode->sendKeys(array($str_duracio ) );
      }
    //   $fieldEmpresa = $webdriver->findElementBy(LocatorStrategy::xpath, "//*[@id=\"form:INPUT_2227_37144_113478\"]");
    //   if ($fieldEmpresa) {
    //       $fieldEmpresa->sendKeys(array("05158|ESTEVE TEIJIN LOT - 8" ) );
    //   }
      $fieldMetge = $webdriver->findElementBy(LocatorStrategy::xpath, "//*[@id=\"form:INPUT_2227_37144_113479\"]");
      if ($fieldMetge) {
          $fieldMetge->sendKeys(array($str_metge ) );
      }
      //sleep( 3 );
      $linkSubmit = $webdriver->findElementBy(LocatorStrategy::xpath, "//*[@id=\"form:save\"]");
      if ($linkSubmit) {
          $linkSubmit->click();
      }

      //$webdriver->get("http://localhost/buildkit/oxigen/210VariablesdeTractament.htm");

      $str_ulleres_nasals = get_ulleres_nasals ($questions_map);
      $fluxRepos    = get_flux_repos($questions_map);
      $fluxExercici = get_flux_exercici($questions_map);
      $horesDia     = get_hores_dia($questions_map);
      $observacions = get_observacions($questions_map);
      $fieldUlleres = $webdriver->findElementBy(LocatorStrategy::xpath, "//*[@id=\"form:INPUT_2227_37187_114206\"]");
      if ($fieldUlleres) {
          $fieldUlleres->sendKeys(array($str_ulleres_nasals ) );
      }
      $fieldRepos = $webdriver->findElementBy(LocatorStrategy::xpath, "//*[@id=\"form:INPUT_2227_37187_114185\"]");
      if ($fieldRepos) {
          $fieldRepos->sendKeys(array($fluxRepos ) );
      }
      $fieldEsforc = $webdriver->findElementBy(LocatorStrategy::xpath, "//*[@id=\"form:INPUT_2227_37187_114208\"]");
      if ($fieldEsforc) {
          $fieldEsforc->sendKeys(array($fluxExercici ) );
      }
      $fieldHores = $webdriver->findElementBy(LocatorStrategy::xpath, "//*[@id=\"form:INPUT_2227_37187_114209\"]");
      if ($fieldHores) {
          $fieldHores->sendKeys(array($horesDia ) );
      }
      $fieldObservacions = $webdriver->findElementBy(LocatorStrategy::xpath, "//*[@id=\"form:INPUT_2227_37187_114240\"]");
      if ($fieldObservacions) {
          $fieldObservacions->sendKeys(array($observacions ) );
      }
      //sleep( 3 );
      $linkSubmit = $webdriver->findElementBy(LocatorStrategy::xpath, "//*[@id=\"form:save\"]");
      if ($linkSubmit) {
          $linkSubmit->click();
      }
    }
    $webdriver->close();

    drupal_set_message(t('La sol·licitud s\'ha enviat correctament.'));
    drupal_goto('ohp/ohp_case_formcatsalut', array('query' => array('id_form' => $id_form, 'id_task' => $id_task,
                'id_admission' => $id_admission, 'id_case' => $id_case)));
  }
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
  $page_array['main'] = array(
    '#theme' => 'ohp_case_body',
  );
  $page_array['main']['pager_container'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('content','full'),
    ),
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

    //var_dump($questions_map);

    $task_status='';
    if(isset($id_task) && $id_task!=''){
      $id_task = $_GET['id_task'];
      $task_bean = get_task($id_task);
      $task_status = $task_bean->status;
    }

    $form['columns_container'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array('columnboxes','clearfix'),
      ),
    );

    $value = get_radio_value("5", $questions_map);
    //var_dump($value);
    if($value=="S"){

      $form['columns_container']['column_left'] = array(
        '#type' => 'container',
        '#attributes' => array(
          'class' => array('column','por1'),
        ),
      );
      $form['columns_container']['column_left']['content'] = array(
        '#type' => 'fieldset',
        '#title' => t('Baixa de prescripció'),
        '#collapsible' => FALSE,
        '#collapsed' => FALSE,
      );
      $str_data_baixa = get_data_baixa ($questions_map);
      $str_motiu_baixa= get_motiu_baixa ($questions_map);
      $form['columns_container']['column_left']['content'][] = array(
        '#markup' => '<span class="question">'.t('Data de Baixa del Tractament').'</span> <span class="answer">'.$str_data_baixa.'</span><br/>',
      );
      $form['columns_container']['column_left']['content'][] = array(
        '#markup' => '<span class="question">'.t('Motiu de Baixa del Tractament').'</span> <span class="answer">'.$str_motiu_baixa.'</span><br/>',
      );

      $page_array['main']['pager_container']['controls'] = array(
        '#theme' => 'ohp_case_catsalutctrl',
        '#selected_option' => t('Sol·licitud d\'OCD a CatSalut'),
        '#task_status' => $task_status,
        '#is_discharge' => 'true',
      );
    }else{

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




      $str_data_prescripcio = get_data_prescripcio ($questions_map);
      $str_unitat_proveidora = get_unitat_proveidora ($questions_map);
      $str_tipus_tractament = get_tipus_tractament ($questions_map);
      $str_tipus_prestacio = get_tipus_prestacio ($questions_map);
      $str_nhc = get_nhc ($questions_map);
      $str_telefon = get_telefon ($questions_map);
      $str_diagnostic = get_diagnostic ($questions_map);
      $str_duracio = get_duracio ($questions_map);
      $str_metge = get_metge ($questions_map);

      //Treatment variables
      $str_ulleres_nasals = get_ulleres_nasals ($questions_map);
      $fluxRepos    = get_flux_repos($questions_map);
      $fluxExercici = get_flux_exercici($questions_map);
      $horesDia     = get_hores_dia($questions_map);
      $observacions = get_observacions($questions_map);

      $form['columns_container']['column_left']['content'][] = array(
        '#markup' => '<span class="question">'.t('Data de Prescripció').'</span> <span class="answer">'.$str_data_prescripcio.'</span><br/>',
      );
      $form['columns_container']['column_left']['content'][] = array(
        '#markup' => '<span class="question">'.t('Unitat Proveïdora').'</span> <span class="answer">'.$str_unitat_proveidora.'</span><br/>',
      );
      $form['columns_container']['column_left']['content'][] = array(
        '#markup' => '<span class="question">'.t('Codi de Tractament').'</span> <span class="answer">'.$str_tipus_tractament.'</span><br/>',
      );
      $form['columns_container']['column_left']['content'][] = array(
        '#markup' => '<span class="question">'.t('Tipus de prestació').'</span> <span class="answer">'.$str_tipus_prestacio.'</span><br/>',
      );
      $form['columns_container']['column_left']['content'][] = array(
        '#markup' => '<span class="question">'.t('Número d\'Història Clínica').'</span> <span class="answer">'.$str_nhc.'</span><br/>',
      );
  //     $form['columns_container']['column_left']['content'][] = array(
  //       '#markup' => '<span class="question">'.t('Telèfon de pacient').'</span> <span class="answer">'.$str_telefon.'</span><br/>',
  //     );
      $form['columns_container']['column_left']['content'][] = array(
        '#markup' => '<span class="question">'.t('Diagnòstic').'</span> <span class="answer">'.$str_diagnostic.'</span><br/>',
      );
      $form['columns_container']['column_left']['content'][] = array(
        '#markup' => '<span class="question">'.t('Indicador de primera prescripció').'</span> <span class="answer">No</span><br/>',
      );
      $form['columns_container']['column_left']['content'][] = array(
        '#markup' => '<span class="question">'.t('Tipus de malalt (per tractament SAHOS)').'</span> <span class="answer">- '.t('Sense determinar').' -</span><br/>',
      );
      $form['columns_container']['column_left']['content'][] = array(
        '#markup' => '<span class="question">'.t('Tractament Ambulatori/Domiciliari').'</span> <span class="answer">- '.t('Sense determinar').' -</span><br/>',
      );
      $form['columns_container']['column_left']['content'][] = array(
        '#markup' => '<span class="question">'.t('Periode de validesa del tractament (en mesos)').'</span> <span class="answer">'.$str_duracio.'</span><br/>',
      );
  //     $form['columns_container']['column_left']['content'][] = array(
  //       '#markup' => '<span class="question">'.t('Empresa proveïdora').'</span> <span class="answer">- '.t('Sense determinar').' -</span><br/>',
  //     );
      $form['columns_container']['column_left']['content'][] = array(
        '#markup' => '<span class="question">'.t('Metge prescriptor').'</span> <span class="answer">'.$str_metge.'</span><br/>',
      );

      $form['columns_container']['column_right']['content'][] = array(
        '#markup' => '<span class="question">'.t('Ulleres nasals').'</span> <span class="answer">'.$str_ulleres_nasals.'</span><br/>',
      );
      $form['columns_container']['column_right']['content'][] = array(
        '#markup' => '<span class="question">'.t('Flux repos I/MIN').'</span> <span class="answer">'.$fluxRepos.'</span><br/>',
      );
      $form['columns_container']['column_right']['content'][] = array(
        '#markup' => '<span class="question">'.t('Flux esforç I/MIN').'</span> <span class="answer">'.$fluxExercici.'</span><br/>',
      );
      $form['columns_container']['column_right']['content'][] = array(
        '#markup' => '<span class="question">'.t('Hores/Dia&gt;15/').'</span> <span class="answer">'.$horesDia.'</span><br/>',
      );
      $form['columns_container']['column_right']['content'][] = array(
        '#markup' => '<span class="question">'.t('Observacions').'</span> <span class="answer">'.$observacions.'</span><br/>',
      );

      $page_array['main']['pager_container']['controls'] = array(
        '#theme' => 'ohp_case_catsalutctrl',
        '#selected_option' => t('Sol·licitud d\'OCD a CatSalut'),
        '#task_status' => $task_status,
        '#is_discharge' => 'false',
      );
    }
//   $form['ohp_case_formcatsalut_arguments'] = array(
//     //Title serves as page subtitle
//     '#title' => t('Sol·licitud d\'OCD a CatSalut'),
//     '#markup' => '<iframe src="https://salut.gencat.net/pls/gsa/gsapk030.portal" style="width:1000px; height:375px;"></iframe>',
//   );
  }
  $page_array['main']['pager_container']['pager_table'] = $form;

  drupal_add_css(drupal_get_path('module', 'ohp_case') . '/css/ohp_case_form.css');
  return $page_array;
}
