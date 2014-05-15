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