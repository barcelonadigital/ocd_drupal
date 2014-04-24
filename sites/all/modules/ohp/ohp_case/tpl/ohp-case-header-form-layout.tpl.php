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
    <div class="cabeceraperfil">
      <div class="container">
        <div id="contentnophotoslim" class="content">
          <small><?php echo t('Pacient'); ?></small>
          <h2><?php  print $fullname; ?></h2>
          <?php if (isset($ident_patient)): ?>
              <?php print $ident_patient; ?>
          <?php endif; ?>
          <div class="contactinfo">
            <div class="dropdown">
              <a href="#" data-toggle="dropdown" class="btn-large dropdown-toggle">
              <?php echo t('Dades de contacte'); ?><span class="caret"></span>
              </a>
              <div class="dropdown-menu">
                <?php print render($dropdown_list); ?>
              </div>
            </div>
          </div>
          <!--
          <div class="contactinfo">
            &nbsp;&nbsp;&nbsp;&nbsp;<a href="#protocolsModal" role="button" data-toggle="modal">Històric protocols</a>
          </div>
          -->
        </div>
      </div>
    </div>
<!--
  < ? php print render($content); ? >
  -->
<!-- /theming-example-text-form template -->
