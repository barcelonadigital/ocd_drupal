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
 * Template file for theming the case form controls.
 */
?>
<div id="task_controls">
	<a href="<?php echo url('ohp/ohp_case_main'); ?>?id_case=<?php if (isset($_SESSION['case_bean']->id_case)): print $_SESSION['case_bean']->id_case; endif; ?>&id_admission=<?php if (isset($_SESSION['admission_bean']->id_admission)): print $_SESSION['admission_bean']->id_admission; endif; ?>"
		class="h2 back clearfix"><span><?php echo t('Tornar'); ?></span></a>
	<div class="dropdown">
		<button data-toggle="dropdown" class="btn dropdown-toggle"><?php  print $selected_option; ?><span class="caret triangulo"></span>
		</button>
		<ul role="menu" class="dropdown-menu">
			<li><a href="<?php echo url('ohp/ohp_case_form'); ?>?id_case=<?php if (isset($_SESSION['case_bean']->id_case)): print $_SESSION['case_bean']->id_case; endif; ?>&id_admission=<?php if (isset($_SESSION['admission_bean']->id_admission)): print $_SESSION['admission_bean']->id_admission; endif; ?>&id_form=<?php if (isset($_GET['id_form'])): print $_GET['id_form']; endif; ?>&id_task=<?php if (isset($_GET['id_task'])): print $_GET['id_task']; endif; ?>"><?php echo t('Qüestionari'); ?></a></li>
			<li><a href="<?php echo url('ohp/ohp_case_formdocument'); ?>?id_case=<?php if (isset($_SESSION['case_bean']->id_case)): print $_SESSION['case_bean']->id_case; endif; ?>&id_admission=<?php if (isset($_SESSION['admission_bean']->id_admission)): print $_SESSION['admission_bean']->id_admission; endif; ?>&id_form=<?php if (isset($_GET['id_form'])): print $_GET['id_form']; endif; ?>&id_task=<?php if (isset($_GET['id_task'])): print $_GET['id_task']; endif; ?>"><?php echo t('Enviament de document a la història clínica'); ?></a></li>
			<li><a href="<?php echo url('ohp/ohp_case_formcatsalut'); ?>?id_case=<?php if (isset($_SESSION['case_bean']->id_case)): print $_SESSION['case_bean']->id_case; endif; ?>&id_admission=<?php if (isset($_SESSION['admission_bean']->id_admission)): print $_SESSION['admission_bean']->id_admission; endif; ?>&id_form=<?php if (isset($_GET['id_form'])): print $_GET['id_form']; endif; ?>&id_task=<?php if (isset($_GET['id_task'])): print $_GET['id_task']; endif; ?>"><?php echo t('Sol·licitud d\'OCD a CatSalut'); ?></a></li>
		</ul>
	</div>
	<?php if ($task_status=='ACTIVE') { ?>
	<a href="<?php echo url('ohp/ohp_case_taskfinish'); ?>?id_case=<?php if (isset($_SESSION['case_bean']->id_case)): print $_SESSION['case_bean']->id_case; endif; ?>&id_admission=<?php if (isset($_SESSION['admission_bean']->id_admission)): print $_SESSION['admission_bean']->id_admission; endif; ?>&id_form=<?php if (isset($_GET['id_form'])): print $_GET['id_form']; endif; ?>&id_task=<?php if (isset($_GET['id_task'])): print $_GET['id_task']; endif; ?>" class="btn btn-large btn-warning btn-finish">Finalitzar</a>
	<?php } ?>
	<?php if ($task_status=='DONE') { ?>
	<a href="<?php echo url('ohp/ohp_case_taskopen'); ?>?id_case=<?php if (isset($_SESSION['case_bean']->id_case)): print $_SESSION['case_bean']->id_case; endif; ?>&id_admission=<?php if (isset($_SESSION['admission_bean']->id_admission)): print $_SESSION['admission_bean']->id_admission; endif; ?>&id_form=<?php if (isset($_GET['id_form'])): print $_GET['id_form']; endif; ?>&id_task=<?php if (isset($_GET['id_task'])): print $_GET['id_task']; endif; ?>" class="btn btn-large btn-warning btn-finish">Reobrir</a>
	<?php } ?>
	<a href="#confirmModal" role="button" data-toggle="modal" class="btn btn-large btn-warning btn-finish"><?php print t('Eliminar'); ?></a>
</div>
<script type="text/javascript">
function doFinish(){
	window.location='<?php echo url('ohp/ohp_case_taskdelete'); ?>?id_case=<?php if (isset($_SESSION['case_bean']->id_case)): print $_SESSION['case_bean']->id_case; endif; ?>&id_admission=<?php if (isset($_SESSION['admission_bean']->id_admission)): print $_SESSION['admission_bean']->id_admission; endif; ?>&id_form=<?php if (isset($_GET['id_form'])): print $_GET['id_form']; endif; ?>&id_task=<?php if (isset($_GET['id_task'])): print $_GET['id_task']; endif; ?>';
}
</script>
<div id="confirmModal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true" class="modal confirmation hide fade">
  <div class="modal-header">
    <button type="button" data-dismiss="modal" aria-hidden="true" class="close"><?php print t('Tancar'); ?></button>
    <h3><?php print t('Eliminar avaluació?'); ?></h3>
  </div>
  <div class="modal-body">
    <p>
      <?php print t('Estàs segur que vols eliminar aquesta avaluació i suprimir-ne el contingut?'); ?>
    </p>
  </div>
  <div class="modal-footer">
    <button data-dismiss="modal" aria-hidden="true" class="btn btn-success custom-btn btn-large"><?php print t('Revisar'); ?></button>
    <button onclick="doFinish()" class="btn btn-primary custom-btn btn-large"><?php print t('D\'acord, continuar'); ?></button>
  </div>
</div>