<?php

/**
 * @file
 * Module file for case_search_module.
 */

/**
 * @defgroup case_search Example: Page
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
 * A simple form that displays a textfield and submit button.
 *
 * This form will be rendered by theme('form') (theme_form() by default)
 * because we do not provide a theme function for it here.
 */
function ohp_case_search_form($form, &$form_state) {
  $form['text'] = array(
    '#type' => 'textfield',
    '#title' => t('Text lliure'),
    '#required' => TRUE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Cercar'),
  );
  return $form;
}

/**
 * Submit handler for the text form.
 *
 * @param array $form
 *   Form API form array.
 * @param array $form_state
 *   Form API form state array.
 */
function ohp_case_search_form_submit($form, &$form_state) {
  try {
    $search_str = $form_state['values']['text'];
    $cip = 'CIP/'.$search_str;
    $nhc = 'NHC/'.$search_str;
    if(!isset($_SESSION['ohp_token'])){
      drupal_set_message("ERROR: no token found");
      return;
    }
    $token     = $_SESSION['ohp_token'];

    $doc = new DomDocument("1.0", 'utf-8');
    $doc->standalone = true;
    $root = $doc->createElement("case");
    $root = $doc->appendChild($root);

    $refs = colgar_hijo( $doc, $root, "refs");
    colgar_hijo( $doc, $refs, "ref", "CIP"."/".$search_str);
    colgar_hijo( $doc, $refs, "ref", "NHC"."/".$search_str);

    $XML = $doc->saveXML();

    $client = new SoapClient(null, array('location' => $GLOBALS["WS-ENDPOINT"], 'uri' => ""));
    $result = $client->case_insert($token,$XML);
    if ( $result["ErrorMsg"] == "Fill all reguired fields") {
      $doc = new DomDocument("1.0", 'utf-8');
      $doc->standalone = true;
      $root = $doc->createElement("case");
      $root = $doc->appendChild($root);

      $refs = colgar_hijo( $doc, $root, "refs");
      colgar_hijo( $doc, $refs, "ref", "NIE"."/".$search_str);
      colgar_hijo( $doc, $refs, "ref", "PAS"."/".$search_str);
      colgar_hijo( $doc, $refs, "ref", "NIF"."/".$search_str);

      $XML = $doc->saveXML();
      $result = $client->case_insert($token,$XML);
      if ( $result["ErrorMsg"] == "Fill all reguired fields") {
        drupal_goto('ohp/ohp_case_result', array('query' => array('search_str' => $search_str)));
      }else if ( $result["ErrorMsg"] ){
        drupal_set_message($result["ErrorMsg"]);
        return -1;
      }
    }else if ( $result["ErrorMsg"] ){
      drupal_set_message($result["ErrorMsg"]);
      return -1;
    }
    if($result["type"] != "EXIST") {
      drupal_set_message("Error no esperat del servei remot.".$result["type"]);
    }else{
      drupal_goto('ohp/ohp_case_main', array('query' => array('id_case' => $result["result"])));
  	}
  } catch (SoapFault $fault) {
    drupal_set_message("SOAP Fault: (faultcode: {$fault->faultcode}, faultstring: {$fault->faultstring})");
  }
}

/**
 * @} End of "defgroup case_search".
 */
