<?php
/**
 * @file
 * Example template file for TCPDF Example module.
 */
?>
<html>
  <body>
    <table border="0">
	  <tr>
        <td> </td>
		<td ALIGN="center"><b> CONSULTA DE VALIDACIÓ </b></td>
        <td> </td>
      </tr>
	  <tr>
        <td> </td>
		<td ALIGN="center"><b> I SEGUIMENT D'OXIGENOTERÀPIA </b></td>
        <td> </td>
      </tr>
      <tr>
        <td><b>PACIENT: <?php  print $cognom_nom; ?></b></td>
		<td> </td>
        <td><b>NHC: <?php  print $nhc; ?></b></td>
      </tr>
	</table>
	<p></p>
	<hr>
	<table border="0">
      <tr>
        <td>Sexo/Sexe: <?php  print $sex; ?></td>
        <td>Fecha nac./Data naix.: <?php  print $birthday; ?></td>
        <td>Edad/Edat: <?php  print $age; ?></td>
      </tr>
      <tr>
        <td>Dirección/Adreça: <?php  print $address; ?></td>
		<td> </td>
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
	 <p></p>
	 <hr>
	<table border="0">
    <tr>
       <td><b>Realización/Realització</b></td>
       <td>Fecha/Data: <?php print date("j.m.Y"); ?></td>
       <td>Hora: <?php print date("H:i:s"); ?></td>
     </tr>
     <tr>
       <td>Nº:</td>
	   <td> </td>
       <td> </td>
     </tr>
	<hr>
	<p ALIGN="center"><b>INFORME SOL-LICITUT / CANVIS / RETIRADA / RENOVACIÓ</b></p>
	<?php  print $body; ?>
  </body>
</html>
