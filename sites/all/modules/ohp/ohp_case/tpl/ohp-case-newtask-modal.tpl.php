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
    <script>
    function assignarProtocolParam(paramActivitat) {
      var admissionId = '<?php if (isset($_SESSION['admission_bean']->id_admission)): print $_SESSION['admission_bean']->id_admission; endif; ?>';
      var caseId = '<?php if (isset($_SESSION['case_bean']->id_case)): print $_SESSION['case_bean']->id_case; endif; ?>';
      var params = { id_admission:admissionId, id_case:caseId, id_activity:paramActivitat };
  	  var str = jQuery.param( params );
  	  window.location='<?php echo url('ohp/ohp_task_insert'); ?>?'+str;
    }
    </script>
    <div id="alertModal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true" class="modal alert hide fade">
      <div class="modal-header">
        <button type="button" data-dismiss="modal" aria-hidden="true" class="close">Tancar</button>
        <h3>Avís</h3>
      </div>
      <div class="modal-body">
        <p>Si us plau, seleccioni la avaluació que vol realitzar:</p>
      </div>
      <div class="modal-footer">
        <div class="btn-block">
                <button onclick="assignarProtocolParam('#TASK:N253')" class="btn btn-warning custom-btn btn-large">Prescripció d'OCD</button>
                <button onclick="assignarProtocolParam('#TASK:N261')" class="btn btn-warning custom-btn btn-large">Visita de seguiment</button>
        </div>
      </div>
    </div>
