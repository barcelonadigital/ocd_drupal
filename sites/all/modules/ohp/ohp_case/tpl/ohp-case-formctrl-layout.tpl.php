  <?php
  /**
 * @file
 * Template file for the theming example text form.
 *
 * Available custom variables:
 * - $text_form: A string containing the pre-rendered form.
 * - $text_form_content: An array of form elements keyed by the element name.
 *
 * The default example below renders the entire form and its form elements in
 * a default order provided by Drupal.
 *
 * Alternatively, you may print each form element in the order you desire,
 * adding any extra html markup you wish to decorate the form like this:
 *
 * <?php print $text_form_content['element_name']; ?>
 *
 * The following snippet will print the contents of the $text_form_content
 * array, hidden in the source of the page, for you to discover the individual
 * element names.
 *
 * <?php print '<!--' . print_r($text_form_content, TRUE) . '-->'; ?>
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