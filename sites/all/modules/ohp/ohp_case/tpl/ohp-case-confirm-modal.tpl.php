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
    <!-- Lightbox-->

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
	          <?php print t('S\'eliminarà l\'avaluació i el seu qüestionari.'); ?>
	        </p>
	      </div>
	      <div class="modal-footer">
	        <button data-dismiss="modal" aria-hidden="true" class="btn btn-success custom-btn btn-large"><?php print t('Revisar'); ?></button>
	        <button onclick="doFinish()" class="btn btn-primary custom-btn btn-large"><?php print t('D\'acord, continuar'); ?></button>
	      </div>
	    </div>