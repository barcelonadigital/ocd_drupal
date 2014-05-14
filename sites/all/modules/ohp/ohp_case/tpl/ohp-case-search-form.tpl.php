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
<!-- theming-example-text-form template -->
    <div class="gris1">
      <div class="container">
        <!-- Encabezado-->
        <div class="encabezado bordebajo">
          <!--
          <div class="h1actions">
            <a href="#confirmNewModal" role="button" data-toggle="modal" class="btn btn-large btn-warning"><?php print t('Nou pacient'); ?></a>
          </div>
          -->
          <header>
            <h1><?php print t('Usuaris'); ?> <strong>— <?php print t('Pacients'); ?></strong></h1>
          </header>
        </div>
        <!-- Encabezado fin-->
      </div>
      <div class="menuizqlayout">
        <div class="container">
          <div class="content">
            <h2 class="clinician"><?php print t('Cercar pacient'); ?></h2>
            <a href="#info1" role="button" data-toggle="modal" class="info_popup"><bean:message key="label.info"/></a>
            <?php print $search_box; ?>
          </div>
        </div>
      </div>
      <!-- Contenido fin-->
    </div>
    <!-- Lightboxes-->
    <div id="info1" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true" class="modal detail hide fade">
      <div class="modal-header">
        <button type="button" data-dismiss="modal" aria-hidden="true" class="close"><?php print t('Tancar'); ?></button>
        <h3><?php print t('Cercar pacient'); ?></h3>
      </div>
      <div class="modal-body">
        <h4><?php print t('Sobre quins camps es realitza la cerca?'); ?></h4>
        <p><?php print t('Pels identificadors <strong>CIP</strong> i <strong>NHC</strong> dels pacients emmagatzemats al <strong>HIS</strong>.'); ?></p>
      </div>
    </div>
    <div id="confirmNewModal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true" class="modal confirmation hide fade">
      <div class="modal-header">
        <button type="button" data-dismiss="modal" aria-hidden="true" class="close"><bean:message key="label.window.close"/></button>
        <h3><bean:message key="alert.notUpdateHis.title"/></h3>
      </div>
      <div class="modal-body">
        <p>
          <bean:message key="alert.notUpdateHis.body1"/><br/><bean:message key="alert.notUpdateHis.body2"/>
        </p>
      </div>
      <div class="modal-footer">
        <button data-dismiss="modal" aria-hidden="true" class="btn btn-success custom-btn btn-large"><bean:message key="label.review"/></button>
        <button onclick="window.location='<html:rewrite action="/caseNewPg.do"/>'" class="btn btn-primary custom-btn btn-large"><bean:message key="label.okcontinue"/></button>
      </div>
    </div>