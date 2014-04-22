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

    $path = url('ohp/ohp_pdf/download/prescription');
    $page_array['ohp_case_formcatsalut_arguments'] = array(
      //Title serves as page subtitle
      '#title' => t('Sol·licitud d\'OCD a CatSalut'),
      '#markup' => '<iframe src="'.$path.'" style="width:750px; height:375px;"></iframe>',
    );
    return $page_array;
}


/**
 * @} End of "defgroup case_task".
 */
