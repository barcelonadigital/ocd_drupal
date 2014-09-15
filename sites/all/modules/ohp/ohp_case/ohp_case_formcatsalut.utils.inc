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

/**
 * @file
 * A file with CatSalut form utils.
 */

function get_data_prescripcio ($questions_map) {
  return get_value_description("2",$questions_map);
}

function get_unitat_proveidora ($questions_map) {
  return "00718|HOSPITAL CLÍNIC I PROVINCIAL BARCELONA";
}

function get_tipus_tractament ($questions_map) {
  return "CONCENTRADOR ESTÀTIC";
}

function get_tipus_prestacio ($questions_map) {
  return "OXIGENOTERÀPIA";
}

function get_nhc ($questions_map) {
  $nhc = "";
  if(isset($_SESSION['case_bean'])){
    if(isset($_SESSION['case_bean']->nhc)){
      $nhc = $_SESSION['case_bean']->nhc;
    }
  }
  return $nhc;
}

function get_telefon ($questions_map) {
  $telefon1 = "";
  $telefon2 = "";
  $telefon3 = "";
  if(isset($_SESSION['case_bean'])){
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
  if($telefon1!=""){
    return $telefon1;
  }else if($telefon2!=""){
    return $telefon2;
  }else if($telefon3!=""){
    return $telefon3;
  }else{
    return "";
  }
}

function get_diagnostic ($questions_map) {
  $diagnostic_1 = get_radio_value("14", $questions_map);
  $diagnostic_2 = get_radio_value("15", $questions_map);
  $diagnostic_3 = get_radio_value("16", $questions_map);
  $diagnostic_4 = get_radio_value("17", $questions_map);
  $diagnostic_5 = get_radio_value("18", $questions_map);
  if($diagnostic_1=="1"){
    if($diagnostic_3=="1"){
      return "MPOC";//496.0
    }else if($diagnostic_3=="2"){
      return "FIBROSI QUÍSTICA";//515
    }else if($diagnostic_3=="3"){
      return "BRONQUIÈCTASI";//494
    }else if($diagnostic_3=="4"){
      return "ASMA";//493.2
    }
  }else if($diagnostic_1=="2"){
    if($diagnostic_5=="1"){
      return "INSUFICIENCIA CARDIACA";//428.0
    }
  }else if($diagnostic_1=="3"){
    return "MALALTIES NEUROMUSCULARS";//349.90
  }
  return "";
}

function get_duracio ($questions_map) {
  $duracio = get_radio_value("57", $questions_map);
  if($duracio=="1"){
    return "12";
  }else if($duracio=="2"){
    return "3";
  }else if($duracio=="3"){
    return "6";
  }else if($duracio=="4"){
    return "3";
  }else{
    return "";
  }
}

function get_metge ($questions_map) {
  return "MARRADES SICART RAMON";
}

function get_ulleres_nasals ($questions_map) {
  $valueSistAdm = get_radio_value("44",$questions_map);
  $descCanulaNasals = "";
  if($valueSistAdm=='1'){
  	$descCanulaNasals = t('Si');
  }else if(isset($valueSistAdm) && $valueSistAdm!=''){
  	$descCanulaNasals = t('No');
  }
  return $descCanulaNasals;
}

function get_flux_repos ($questions_map) {
  return get_value_description("47",$questions_map);
}

function get_flux_exercici ($questions_map) {
  return get_value_description("48",$questions_map);
}

function get_hores_dia ($questions_map) {
  $value = get_radio_value("50", $questions_map);
  if($value=="1"){
    return "15";
  }else if($value=="2"){
    return "15";
  }else if($value=="3"){
    return "18";
  }else if($value=="4"){
    return "24";
  }else{
    return "";
  }
}

function get_observacions ($questions_map) {
  return get_value_description("60",$questions_map);
}

function get_data_baixa ($questions_map) {
  return get_value_description("1",$questions_map);
}

function get_motiu_baixa ($questions_map) {
  $value = get_radio_value("6", $questions_map);
  if($value=="1"){
    return "Baixa clínica";
  }else if($value=="2"){
    return "Exitus del pacient";
  }else if($value=="3"){
    return "Baixa voluntària del pacient";
  }else{
    return "";
  }
}
