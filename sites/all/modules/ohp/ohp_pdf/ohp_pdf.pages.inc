<?php

/**
 * @file
 * Contains page callbacks and related functions of TCPDF module.
 */

/**
 * Page callback for downloading example pdf files.
 */
function ohp_pdf_download($example_name,$id_form) {
  switch ($example_name) {
    case 'prescription':
      $pdf = ohp_pdf_prescription_pdf($id_form);
      break;
    default:
      return t('No such example.');
  }

  if (!$pdf) {
    return t('An error occured.');
  }

  // Tell the browser that this is not an HTML file to show, but a pdf file to
  // download.
  header('Content-Type: application/pdf');
  header('Content-Length: ' . strlen($pdf));
  //header('Content-Disposition: attachment; filename="mydocument.pdf"');
  print $pdf;
  return NULL;
}

function get_sex_for_report($sex) {
  $result = "";
  if($sex=="M"){
  	$result = "Masc.";
  }else if($sex=="F"){
  	$result = "Fem.";
  }
  return $result;
}

function get_cognom_nom($given_name, $middle_name, $family_name, $family_name2) {
  $result = "";
  $result  = $family_name;
  $result .= " ".$family_name2;
  $result .= ", ".$given_name;
  $result .= " ".$middle_name;
  return strtoupper($result);
}

function get_birthday($birthday) {
  $result = str_replace("/", ".", $birthday);
  return $result;
}

function build_address($address) {
  $result ="";
  //Concat the street
  $result .= strtoupper($address->street);
  //Concat the number
  $result .= ", ".strtoupper($address->number);
  //Concat the floor
  $result .= " ".strtoupper($address->floor);
  //Concat the suite
  $result .= "-".strtoupper($address->suite);
  return $result;
}

function add_group_docform(&$count_questions,$questions_map,$ids_array,$hiddens_array=array()){
  $result  = '';
  //$container_result = '';
  //$count_questions=0;
  foreach ($ids_array as $row_question) {
    $i=0;
    $row_result ="";
    foreach ($row_question as $question_id) {
      if(isset($questions_map[$question_id])){
        $question_obj = $questions_map[$question_id];
        //var_dump($question_obj);
//drupal_set_message($question_id.', '.$question_obj->type.', '.$question_obj->value);
        if(!in_array($question_id, $hiddens_array) &&
            ($question_obj->type=='STATIC_TEXT' ||
            $question_obj->value!=NULL && $question_obj->value!="")){
          $row_result .= '<td>'.$question_obj->description.': '.get_value_description($question_id, $questions_map).'</td>';
          $i++;
//drupal_set_message('2');
        }
        $count_questions++;
      }
    }
    if($i>0){
      if($i==1){
        $row_result .= '<td>&nbsp;</td>';
      }
      $result .= '<tr>'.$row_result.'</tr>';
    }
  }
//   if($j>0){
//     $container_result .= '<p><strong>'.$title.'</strong></p>';
//     $container_result .= '<table>';
//     if($result==''){
//       $container_result .= t('No hi ha elements per mostrar.');
//     }else{
//       $container_result .= $result;
//     }
//     $container_result .= '</table>';
//   }
  return $result;
}

// GLOBALS
$fontname;
$fontname_2;

/**
 * Generates a pdf file using TCPDF module.
 *
 * @return string Binary string of the generated pdf.
 */
function ohp_pdf_prescription_pdf($id_form) {

  // Never make an instance of TCPDF or TCPDFDrupal classes manually.
  // Use tcpdf_get_instance() instead.
  $tcpdf = tcpdf_get_instance();
  /* DrupalInitialize() is an extra method added to TCPDFDrupal that initializes
  *  some TCPDF variables (like font types), and makes possible to change the
  *  default header or footer without creating a new class.
  */
  $tcpdf->DrupalInitialize(array(
    'footer' => array(
      'callback' => array(
        'function' => 'ohp_pdf_default_footer',
        // You can pass extra data to your callback.
        'context' => array(
          'welcome_message' => 'hea dsajh kjas hdjak der',
        ),
      ),
    ),
    'header' => array(
      'callback' => array(
        'function' => 'ohp_pdf_default_header',
        // You can pass extra data to your callback.
        'context' => array(
          'welcome_message' => 'hea dsajh kjas hdjak der',
        ),
      ),
    ),
  ));

  $tcpdf->SetFooterMargin(28);
  $tcpdf->SetMargins(20, 50, 20);
  $tcpdf->SetAutoPageBreak(TRUE, 28);

  $GLOBALS['fontname'] = $tcpdf->addTTFfont(drupal_realpath(drupal_get_path('module', 'ohp') . '/ohp_pdf/fonts/trebuc.ttf'), 'Trebuchet', '', 32);
  $GLOBALS['fontname_2'] = $tcpdf->addTTFfont(drupal_realpath(drupal_get_path('module', 'ohp') . '/ohp_pdf/fonts/trebucbd.ttf'), 'TrebuchetBOLD', '', 32);
  // use the font
  $tcpdf->SetFont($GLOBALS['fontname'], '', 10, '', false);

  // Get the content we want to convert into pdf.
  $html = '';
  $variables = array();
  if(isset($_SESSION['case_bean'])){
    $case_bean_stored  = $_SESSION['case_bean'];

    $sex_for_report = get_sex_for_report($case_bean_stored->sex);
    $cognom_nom = get_cognom_nom($case_bean_stored->given_name,
                                  $case_bean_stored->middle_name,
                                  $case_bean_stored->family_name,
                                  $case_bean_stored->family_name2);
	$birthday = get_birthday($case_bean_stored->birthday);
	$address_str = '';
	$postcode    = '';
	$city        = '';
	if(isset($case_bean_stored->contact->addresses[0])){
      $address_obj = $case_bean_stored->contact->addresses[0];
      $address_str = build_address($address_obj);
      $postcode    = $address_obj->postcode;
      $city        = strtoupper($address_obj->city);
	}
	$telf = '';
	foreach ($case_bean_stored->contact->phones as $phone) {
	  if($phone->type=='home'){
	    $telf = $phone->number;
	  }
	}

    $questions_map = array();
    $form_xml = NULL;
    load_form(NULL ,$id_form, $form_xml, $questions_map);

    $struct_form = get_form_struct();
    $body  = '';
    foreach ($struct_form as $struct_item) {
      if(!isset($struct_item['groups'])){
        $count_questions=0;
        $result = add_group_docform($count_questions,$questions_map,$struct_item['items'],$struct_item['hidden']);
        if($count_questions>0){
          if(isset($struct_item['hide_title']) && $struct_item['hide_title']==TRUE){
            $body .= '<table>'.$result.'</table><br><br>';
          }else{
            $body .= '<table>';
            $body .= '<tr><td><span style="font-family:'.$GLOBALS['fontname_2'].';font-size:10pt;">'.$struct_item['title'].'</span></td><td>&nbsp;</td></tr>';
            if($result==''){
              $body .= '<tr><td>'.t('No hi ha elements per mostrar.').'</td><td>&nbsp;</td></tr>';
            }else{
              $body .= $result;
            }
            $body .= '</table><br><br>';
          }
        }
      }else{
        $groups_result = '';
        $k = 0;
        foreach ($struct_item['groups'] as $struct_group) {
          $count_questions=0;
          $result = add_group_docform($count_questions,$questions_map,$struct_group['items'],$struct_group['hidden']);
          if($count_questions>0){
            if($k>0){
              $groups_result .= '<tr><td>&nbsp;</td><td>&nbsp;</td></tr>';
            }
            $groups_result .= '<tr><td>'.$struct_group['title'].'</td><td>&nbsp;</td></tr>';
            if($result==''){
              $groups_result .= '<tr><td>'.t('No hi ha elements per mostrar.').'</td><td>&nbsp;</td></tr>';
            }else{
              $groups_result .= $result;
            }
            $k++;
          }
        }
        if($groups_result!=''){
          $body .= '<table>';
          $body .= '<tr><td><span style="font-family:'.$GLOBALS['fontname_2'].';font-size:10pt;">'.$struct_item['title'].'</span></td><td>&nbsp;</td></tr>';
          $body .= ''.$groups_result.'</table><br><br>';
        }
      }
    }

    $variables = array(
      'sex'        => $sex_for_report,
      'cognom_nom' => $cognom_nom,
      'telf'       => $telf,
      'birthday'   => $birthday,
      'age'   => $case_bean_stored->age.' anys',
      'nhc'   => $case_bean_stored->nhc,
      'cip'   => $case_bean_stored->cip,
      'address' => $address_str,
      'postcode' => $postcode,
      'city' => $city,
      'body' => $body,
    );
  }
  $html = theme('ohp_pdf_basic_html',$variables);
  //drupal_set_message($html);

  // Insert the content. Note that DrupalInitialize automaticly adds the first
  // page to the pdf document.
  $tcpdf->writeHTML($html);

  return $tcpdf->Output('', 'S');
}

function ohp_pdf_default_footer(&$tcpdf, $context) {
  $text_column_1  = "El Hospital Clínic ha incorporado sus datos al Fichero de\n";
  $text_column_1 .= "Pacientes, para tratarlos con fines sanitarios.\n";
  $text_column_1 .= "Puede ejercer sus derechos de acceso, rectificación,\n";
  $text_column_1 .= "cancelación y oposición, así como obtener mas información\n";
  $text_column_1 .= "en la Unidad de Atención al Cliente.";
  $text_column_2  = "HOSPITAL CLÍNIC DE BARCELONA\n";
  $text_column_2 .= "Villarroel,170 08036-Barcelona (España)\n";
  $text_column_2 .= "Sabino de Arana ,1 08028-Barcelona (España)\n";
  $text_column_2 .= "Tel. 93 227 54 00 Fax 93 227 54 54\n";
  $text_column_2 .= "http://www.hospitalclinic.org/";
  $text_column_3  = "L'Hospital Clínic ha incorporat les seves dades al\n";
  $text_column_3 .= "Fitxer de Pacients, per a tractar-los amb finalitats\n";
  $text_column_3 .= "sanitàries. Pot exercir els seus drets d'accés,\n";
  $text_column_3 .= "rectificació, cancel·lació i oposició, i obtenir més\n";
  $text_column_3 .= "informació a la Unitat d\'Atenció al Client.";
  $tcpdf->SetFont($GLOBALS['fontname'], '', 10, '', false);
  $tcpdf->MultiCell(60, 3, '', 0, 'L', 0, false,20);
  $tcpdf->MultiCell(60, 3, "Vers.", 0, 'C', 0, false);
  $tcpdf->MultiCell(60, 3, '', 0, 'L', 0, false);
  $tcpdf->Ln();
  $tcpdf->MultiCell(60, 3, '', 0, 'L', 0, false,20);
  $tcpdf->MultiCell(60, 3, "              Pag. ".$tcpdf->getAliasNumPage()." de ".$tcpdf->getAliasNbPages(), 0, 'C', 0, false);
  $tcpdf->MultiCell(60, 3, '', 0, 'L', 0, false);
  $tcpdf->Ln();
  $tcpdf->SetFont($GLOBALS['fontname'], '', 6, '', false);
  $tcpdf->MultiCell(60, 0, $text_column_1, 0, 'L', 0, false,20);
  $tcpdf->MultiCell(60, 0, $text_column_2, 0, 'C', 0, false);
  $tcpdf->MultiCell(60, 0, $text_column_3, 0, 'L', 0, false);
}
/**
 * Callback for generating the header. This function acts like if it overridded
 *   the Header() function of tcpdf class except the tcpdf instance is not $this
 *   but a parameter.
 *
 * @param type $tcpdf TCPDFDrupal instance. It can be used as $this in the
 *   Header() function of a siebling of TCPDF.
 */
function ohp_pdf_default_header(&$tcpdf, $context) {
  // $args contains passed variable...
  $tcpdf->Image(drupal_realpath(drupal_get_path('module', 'ohp') . '/ohp_pdf/image/HOSPITAL.jpg'), 10, 10, 43, 0, '', '', '', TRUE, 150, '', FALSE, FALSE, 0, FALSE, FALSE, FALSE);
}
