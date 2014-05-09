<?php
/**
 * @file
 * Example template file for TCPDF Example module.
 */
 
//VARIABLES 
$today = date("j.n.Y");
$today_hour = date("H:i:s");  
 
//FUNCTIONS
 
 
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
        <td><b>PACIENT: </b></td>
		<td> </td>
        <td><b> NHC: </b></td>
      </tr>
	</table>
	<p></p>
	<hr>
	<table border="0">
      <tr>
        <td>Sexo/Sexe: </td>
        <td>Fecha nac./Data naix.: </td>
        <td>Edad/Edat: </td>
      </tr>
      <tr>
        <td>Dirección/Adreça: </td>
		<td> </td>
        <td>CP: </td>
      </tr>
      <tr>
		<td>Municip. (Prov.): </td>
        <td>ABS: </td>
        <td>Tel.: </td>
      </tr>
	  <tr>
		<td>As.: </td>
        <td>CIP: </td>
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
       <td>Fecha/Data: <?php echo $today?></td>
       <td>Hora: <?php echo $today_hour?></td>
     </tr>
     <tr>
       <td>Nº:</td>
	   <td> </td>
       <td> </td>
     </tr>
	<hr>
	<p ALIGN="center"><b>INFORME SOL-LICITUT / CANVIS / RETIRADA / RENOVACIÓ</b></p>
  </body>
</html>
