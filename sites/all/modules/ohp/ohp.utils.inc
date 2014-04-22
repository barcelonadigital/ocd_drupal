<?php

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

