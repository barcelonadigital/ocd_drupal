<?php
/**
 * @file
 * Contains page callbacks and related functions of TCPDF module.
 */

/**
 * Page callback for downloading example pdf files.
 */
function ohp_pdf_download($example_name) {
  switch ($example_name) {
    case 'prescription':
      $pdf = ohp_pdf_prescription_pdf();
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
  return $result;
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

/**
 * Generates a pdf file using TCPDF module.
 *
 * @return string Binary string of the generated pdf.
 */
function ohp_pdf_prescription_pdf() {
  // Get the content we want to convert into pdf.
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
    );
    $html = theme('ohp_pdf_basic_html',$variables);
  }


  // Never make an instance of TCPDF or TCPDFDrupal classes manually.
  // Use tcpdf_get_instance() instead.
  $tcpdf = tcpdf_get_instance();
  /* DrupalInitialize() is an extra method added to TCPDFDrupal that initializes
  *  some TCPDF variables (like font types), and makes possible to change the
  *  default header or footer without creating a new class.
  */
  $tcpdf->DrupalInitialize(array(
    'footer' => array(
      'html' => '<table border="0">
				  <tr>
					<td>El Hospital Clínic ha incorporado sus datos al Fichero de</td>
					<td ALIGN="center">HOSPITAL CLÍNIC DE BARCELONA</td>
					<td>L\' Hospital Clínic ha incorporat les seves dades al</td>
				  </tr>
				  <tr>
					<td>Pacientes, para tratarlos con fines sanitarios.</td>
					<td ALIGN="center">Villarroel,170 08036-Barcelona (España)</td>
					<td>Fitxer de Pacients, per a tractar-los amb finalitats</td>
				  </tr>
				  <tr>
					<td>Puede ejercer sus derechos de acceso, rectificación,</td>
					<td ALIGN="center">Sabino de Arana ,1 08028-Barcelona (España)</td>
					<td>sanitàries. Pot exercir els seus drets d\'accés,</td>
				  </tr>
				  <tr>
					<td>cancelación y oposición, así como obtener mas información</td>
					<td ALIGN="center">Tel. 93 227 54 00 Fax 93 227 54 54</td>
					<td>rectificació, cancel-lació i oposició, i obtenir més</td>
				  </tr>
				  <tr>
					<td>en la Unidad de \Atención al Cliente.</td>
					<td ALIGN="center">http://www.hospitalclinic.org/</td>
					<td>informació a la Unitat d\'Atenció al Client.</td>
				  </tr>
				</table>',

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
  // Insert the content. Note that DrupalInitialize automaticly adds the first
  // page to the pdf document.
  $tcpdf->writeHTML($html);

  return $tcpdf->Output('', 'S');
}


// Page footer
 function footer() {
	// Position at 15 mm from bottom
	$this->SetY(-15);
	// Set font
	$this->SetFont('Trebuchet', '', 8);
	// Page number

	$pageNumbers = 'Page '.$this->getAliasNumPage().' of '.$this->getAliasNbPages();

	$this->Cell(0, 10, $pageNumbers, 0, false, 'C', 0, '', 0, false, 'T', 'M');

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
  $theme_settings = variable_get('theme_' . variable_get('theme_default', '') . '_settings', '');
  if (isset($theme_settings['logo_path']) && (file_exists($theme_settings['logo_path']))) {
    $tcpdf->Image(drupal_realpath($theme_settings['logo_path']), 10, 10, 30, 0, '', variable_get('site_url', ''), '', TRUE, 150, '', FALSE, FALSE, 0, FALSE, FALSE, FALSE);
  }

  $fontname = $tcpdf->addTTFfont(drupal_realpath(drupal_get_path('module', 'ohp') . '/ohp_pdf/fonts/trebuc.ttf'), '', '', 32);
  // use the font
  $tcpdf->SetFont($fontname, '', 14, '', false);

  $tcpdf->Write(0, $context['welcome_message'], '', 0, 'J', true, 0, false, true, 0);
}
