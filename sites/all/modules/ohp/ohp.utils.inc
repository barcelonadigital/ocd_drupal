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

function load_form($token ,$id_form, &$form_xml, &$questions_map) {

  $form_xml = get_form($id_form);

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
  return array('21','22','23','24','25','28','29','32','33','35','38','46','47','48','49','66','67','72','73','74','76','80','82','83','84','85','86','103');
}

function get_form_object($form_id){
  $struct_form=get_form_struct();
  if(isset($struct_form[$form_id])){
    return $struct_form[$form_id];
  }else{
    if(isset($struct_form['proves']['groups'][$form_id])){
      return $struct_form['proves']['groups'][$form_id];
    }
  }
  return NULL;
}

function get_form_struct(){
  return array(
        'info'=>array(
            'title'=>t('Informació de la visita'),
            'items'=>array(array("61","62"),array("63")),
            'hidden'=>array(),
            'hide_title'=>TRUE,
        ),
        'caracteristiques'=>array(
            'title'=>t('Característiques de la sol·licitud'),
            'items'=>array(array("1","2"),array("3","4"),
                array("5","6"),array("7"),array("8","9"),
                array("10","11"),array("12","13")),
            'hidden'=>array(),
        ),
        'diagnostic'=>array(
            'title'=>t('Diagnòstic'),
            'items'=>array(array("14","15"),array("16","17"),array("18")),
            'hidden'=>array(),
        ),
        'factors'=>array(
            'title'=>t('Factors de risc i hàbits de vida'),
            'items'=>array(array("64"),array("65","66"),array("67"),array("68"),array("69")),
            'hidden'=>array(),
        ),
        'proves'=>array(
            'title'=>t('Proves funcionals respiratòries'),
            'groups'=>array(
                'test'=>array(
                    'title'=>t('Test de la marxa (6 minuts)'),
                    'items'=>array(array("70","71"),array("72","73"),array("74"),array("75","76")),
                    'hidden'=>array()),
                'noct'=>array(
                    'title'=>t('Pulsioximetria nocturna'),
                    'items'=>array(array("77","78"),array("79","80"),array("81","82"),array("83","84"),array("85","86")),
                    'hidden'=>array()),
                'espiro'=>array(
                    'title'=>t('Espirometria'),
                    'items'=>array(array("19","20"),array("21","22"),array("23","24"),array("25")),
                    'hidden'=>array()),
                'gaso'=>array(
                    'title'=>t('Gasometria'),
                    'items'=>array(array("26","27"),array("28"),array("29","30","31"),array("32","33"),array("34","35")),
                    'hidden'=>array("30")),
                'pulsio'=>array(
                    'title'=>t('Pulsioximetria'),
                    'items'=>array(array("36","37"),array("38")),
                    'hidden'=>array()),
                )
        ),
        'equip'=>array(
            'title'=>t('Equips de teràpia respiratòria'),
            'items'=>array(array("87"),array("88"),array("89"),array("39","40"),array("41","42"),
                array("43"),array("44","45","46"),array("47","48"),array("49",
                "50"),array("51"),array("52","53"),array("54")),
            'hidden'=>array("45"),
        ),
        'adherencia'=>array(
            'title'=>t('Adequació i adherència'),
            'items'=>array(array("90","91"),array("92"),array("93","94"),
                array("95"),array("96"),array("97"),array("98"),array("99"),array("100")),
            'hidden'=>array("91","98"),
        ),
        'percepcio'=>array(
            'title'=>t('Percepció del pacient'),
            'items'=>array(array("101","102"),array("103")),
            'hidden'=>array(),
        ),
        'planificacio'=>array(
            'title'=>t('Pla terapèutic'),
            'items'=>array(array("55","56"),array("57","58"),array("59"),
                array("104","105"),array("106","107"),array("108","109"),
                array("110"),array("111"),array("112"),array("113","114"),array("115","116"),array("117","118"),array("119",
                "120"),array("121","122"),array("123","124"),array("125","126"),array("127")),
            'hidden'=>array(),
        ),
        'comentaris'=>array(
            'title'=>t('Comentaris'),
            'items'=>array(array("60")),
            'hidden'=>array(),
        ));
}

function get_value_description($question_id, $questions_map) {
  if(isset($questions_map[$question_id])){
    $question_obj = $questions_map[$question_id];
    if(isset($question_obj->value)&&!empty($question_obj->value)){
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
        return date('d/m/Y',(string)$question_obj->value);
      }else{
        return (string)$question_obj->value;
      }
    }
  }
  return "";
}