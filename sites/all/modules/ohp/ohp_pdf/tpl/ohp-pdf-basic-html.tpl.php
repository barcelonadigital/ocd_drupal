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
 * Template file for theming the creation of PDF.
 */
?>
<html>
  <body>
    <p></p>
    <table border="0">
	  <tr>
		<td ALIGN="center"><span style="font-family:<?php print $GLOBALS['fontname_2'] ?>;font-size:12pt;">CONSULTA DE VALIDACIÓ<br>I SEGUIMENT D'OXIGENOTERÀPIA</span></td>
      </tr>
	</table>
    <table border="0">
      <tr>
        <td><span style="font-family:<?php print $GLOBALS['fontname_2'] ?>;font-size:12pt;"><?php  print $cognom_nom; ?></span></td>
		<td> </td>
        <td><span style="font-family:<?php print $GLOBALS['fontname_2'] ?>;font-size:12pt;">NHC: <?php  print $nhc; ?></span></td>
      </tr>
	</table>
	<br>
	<hr>
	<table border="0">
      <tr>
        <td>Sexo/Sexe: <?php  print $sex; ?></td>
        <td>Fecha nac./Data naix.: <?php  print $birthday; ?></td>
        <td>Edad/Edat: <?php  print $age; ?></td>
      </tr>
      <tr>
        <td colspan="2">Dirección/Adreça: <?php  print $address; ?></td>
        <td>CP: <?php  print $postcode; ?></td>
      </tr>
      <tr>
		<td>Municip. (Prov.): <?php  print $city; ?></td>
        <td>ABS: </td>
        <td>Tel.: <?php  print $telf; ?></td>
      </tr>
	  <tr>
		<td>As.: </td>
        <td>CIP: <?php  print $cip; ?></td>
        <td>NASS: </td>
      </tr>
	  <tr>
		<td>Nº epis.: </td>
        <td>Tipo/Tipus: </td>
        <td>Ingres.: </td>
      </tr>
	  <tr>
		<td>Serv: </td>
        <td>UO Enf.: </td>
        <td>Hora: </td>
      </tr>
	  <tr>
		<td>Facult. de ref.: </td>
		<td> </td>
        <td> </td>
      </tr>
     </table>
	 <br>
	 <hr>
	<table border="0">
    <tr>
       <td><span style="font-family:<?php print $GLOBALS['fontname_2'] ?>;font-size:12pt;">Realización/Realització</span></td>
       <td>Fecha/Data: <?php print date("j.m.Y"); ?></td>
       <td>Hora: <?php print date("H:i:s"); ?></td>
     </tr>
     <tr>
       <td>Nº:</td>
	   <td> </td>
       <td> </td>
     </tr>
	<hr>
	<p ALIGN="center"><span style="font-family:<?php print $GLOBALS['fontname_2'] ?>;font-size:12pt;">INFORME SOL-LICITUT / CANVIS / RETIRADA / RENOVACIÓ</span></p>
	<?php  print $body; ?>
</html>