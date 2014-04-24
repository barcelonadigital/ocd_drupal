<?php

/**
 * @file
 * Module file for case_task_module.
 */

/**
 * @defgroup case_task Example: Page
 * @ingroup examples
 * @{
 * This example demonstrates how a module can display a page at a given URL.
 *
 * It's important to understand how the menu system works in order to
 * implement your own pages. See the Menu Example module for some insight.
 *
 * @see menu_example
 */

/**
 * Constructs a descriptive page.
 *
 * Our menu maps this function to the path 'ohp/tasks_assigned'.
 */
function ohp_case_formdocument_page() {

  ohp_case_load_common($form);
  $page_array['page_header'] = array(
    '#theme' => 'ohp_case_header',
  );
  $page_array['main'] = array(
    '#theme' => 'ohp_case_body',
  );
  $page_array['main']['menu_container'] = array(
    '#theme' => 'ohp_case_menu',
    'is_active_menu_formularis' => TRUE,
  );
  $page_array['main']['pager_container'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('content'),
    ),
  );
  $path = url('ohp/ohp_pdf/download/prescription');
  $page_array['main']['pager_container']['pager_table'] = array(
    //Title serves as page subtitle
    '#title' => t('Enviament de document a la història clínica'),
    '#markup' => '<iframe src="'.$path.'" style="width:750px; height:375px;"></iframe>',
    '#prefix' => '<h2 class="newsession">'.t('Enviament de document a la història clínica').'</h2>',
  );
  return $page_array;
}


/**
 * @} End of "defgroup case_task".
 */
