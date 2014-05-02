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
        <nav class="menuizq">
          <ul>
            <!--
             -->
            <li><a href="<?php echo url('ohp/ohp_case_main'); ?>?id_case=<?php if (isset($_SESSION['case_bean']->id_case)): print $_SESSION['case_bean']->id_case; endif; ?>&id_admission=<?php if (isset($_SESSION['admission_bean']->id_admission)): print $_SESSION['admission_bean']->id_admission; endif; ?>" class="<?php if (isset($is_active_menu_formularis)): print 'active'; endif; ?>"><?php print t('Tasques'); ?></a></li>
            <li><a href="<?php echo url('ohp/ohp_case_main'); ?>?id_case=<?php if (isset($_SESSION['case_bean']->id_case)): print $_SESSION['case_bean']->id_case; endif; ?>&id_admission=<?php if (isset($_SESSION['admission_bean']->id_admission)): print $_SESSION['admission_bean']->id_admission; endif; ?>" class="<?php if (isset($is_active_menu_info_pacient)): print 'active'; endif; ?>"><?php print t('Informació pacient'); ?></a></li>
            <!--
            <li><html:link action="/caseHistoricAction?idCase=${caseBean.idCase}" styleClass="${historicClass}">Protocols anteriors</html:link></li>
             -->
          </ul>
        </nav>
<!-- /theming-example-text-form template -->
