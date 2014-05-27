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

function load_report_table(&$items, &$subheader_result, &$header_result) {

  $page_array = array();

  $result_questions = get_questions();
  $result_forms     = get_forms();
  $result_answers   = get_answers();

  $header_result = array(array('data' => 'Pacient', 'colspan' => 3));
  $subheader_patientinfo = array('CIP' , 'Nom complert' , 'Gènere');
  $subheader_ids = array();
  $hidden_ids = array();
  $struct_form = get_form_struct();
  $body  = '';
  foreach ($struct_form as $struct_item) {
    if(!isset($struct_item['groups'])){
      $questions_all = call_user_func_array('array_merge', $struct_item['items']);
      $questions_merged = array_diff($questions_all,$struct_item['hidden']);
      $hidden_ids = array_merge($hidden_ids,$struct_item['hidden']);
      $header_result[] = array('data' => $struct_item['title'], 'colspan' => count($questions_merged));
      $subheader_ids = array_merge($subheader_ids,$questions_merged);
    }else{
      foreach ($struct_item['groups'] as $struct_group) {
        $questions_all = call_user_func_array('array_merge', $struct_group['items']);
        $questions_merged = array_diff($questions_all,$struct_group['hidden']);
        $hidden_ids = array_merge($hidden_ids,$struct_group['hidden']);
        $header_result[] = array('data' => $struct_group['title'], 'colspan' => count($questions_merged));
        $subheader_ids = array_merge($subheader_ids,$questions_merged);
      }
    }
  }

  foreach ($result_questions as $question) {
    if(!in_array($question->id_question, $hidden_ids)){
      $question_array[$question->id_question] = $question->description;
    }
  }

  $a = array_fill_keys($subheader_ids, '0');
  $subheader_descriptions = array_replace($a, $question_array);
  $subheader_result['data'] = array_merge($subheader_patientinfo,$subheader_descriptions);
  $subheader_result['class'] = array('first-row');

  foreach ($result_answers as $answer) {
    if(!in_array($answer->id_question_1, $hidden_ids)){
      $answers[$answer->id_form_1][$answer->id_question_1]=$answer->type_text;
    }
  }

  foreach ($result_forms as $row) {
    $fullname = get_fullname ($row->given_name,$row->middle_name,$row->family_name,$row->family_name2);
    $desc_sex = get_gender( $row->gender );
    $items[$row->id_form] = array(
      'data' => array(
        'cip' => $row->cip,
        'fullname' => $fullname,
        'desc_sex' => $desc_sex,
      ),
    );
    $row_answers = array_replace($a, $answers[$row->id_form]);
    $items[$row->id_form]['data'] = array_merge($items[$row->id_form]['data'],$row_answers);
  }
}
function ohp_case_report_page() {

  $items = array();
  $subheader_result = array();
  $header_result = array();
  load_report_table($items, $subheader_result, $header_result);

  if(count($items)>0){
    $per_page = 6;
    // Initialize the pager
    $current_page = pager_default_initialize(count($items), $per_page);
    // Split your list into page sized chunks
    $chunks = array_chunk($items, $per_page, TRUE);

    $table_rows = $chunks[$current_page];
    array_unshift($table_rows, $subheader_result);

    // Create a render array ($page_array) which will be themed as a table with a
    // pager.
    $page_array['doc_links'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array('doc-links'),
      ),
    );
    $page_array['doc_links']['xls'] = array(
      '#type' => 'link',
      '#title' => "XLS",
      '#href' => 'ohp/ohp_case_report_xls',
      '#attributes' => array(
        'class' => array('xls'),
      ),
    );
    $page_array['scroll_table'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array('tbl-scroll'),
      ),
    );
    $page_array['scroll_table']['pager_table'] = array(
      '#theme' => 'table',
      '#attributes' => array('class' => array('table_result','table_report'),),
      '#sticky' => FALSE,
      '#rows' => $table_rows,
      '#header' => $header_result,
      '#empty' => t('No hi ha elements per mostrar.'),
    );

    // Attach the pager theme.
    $page_array[] = array('#theme' => 'pager');
  }else{
    // There were no tasks. Tell the user.
    $content[] = array(
      '#type' => 'item',
      '#markup' => t('No hi ha elements per mostrar.'),
    );
    $page_array['table'] = $content;
  }
  $subtitle_section =  t('Tots els qüestionaris');
  $page_container['main'] = array(
    '#theme' => 'ohp_case_report',
    '#page_content' => $page_array,
    '#subtitle_section' => $subtitle_section,
  );
  $page_container['main']['table_result']=$page_array;
  return $page_container;
}

/**
 * Constructs a descriptive page.
 *
 * Our menu maps this function to the path 'ohp/ohp_case_report_xls'.
 */
function ohp_case_report_xls_page() {

  $items = array();
  $subheader_result = array();
  $header_result = array();
  load_report_table($items, $subheader_result, $header_result);

  $output = '<?xml version="1.0"?>' . "\n";
  $output .= '<?mso-application progid="Excel.Sheet"?>' . "\n";
  $output .= '<Workbook xmlns="urn:schemas-microsoft-com:office:spreadsheet"' . "\n";
  $output .= '  xmlns:o="urn:schemas-microsoft-com:office:office"' . "\n";
  $output .= '  xmlns:x="urn:schemas-microsoft-com:office:excel"' . "\n";
  $output .= '  xmlns:ss="urn:schemas-microsoft-com:office:spreadsheet"' . "\n";
  $output .= '  xmlns:html="http://www.w3.org/TR/REC-html40">' . "\n";
  $output .= '<Styles>' . "\n";
  $output .= '  <Style ss:ID="Default" ss:Name="Normal">' . "\n";
  $output .= '    <Alignment ss:Vertical="Bottom"/>' . "\n";
  $output .= '    <Borders/>' . "\n";
  $output .= '    <Font/>' . "\n";
  $output .= '    <Interior/>' . "\n";
  $output .= '    <NumberFormat/>' . "\n";
  $output .= '    <Protection/>' . "\n";
  $output .= '  </Style>' . "\n";
  $output .= '  <ss:Style ss:ID="1">' . "\n";
  $output .= '    <ss:Font ss:Bold="1"/>' . "\n";
  $output .= '    <Borders>' . "\n";
  $output .= '      <Border ss:Position="Bottom" ss:LineStyle="Continuous" ss:Weight="1"/>' . "\n";
  $output .= '      <Border ss:Position="Left" ss:LineStyle="Continuous" ss:Weight="1"/>' . "\n";
  $output .= '      <Border ss:Position="Right" ss:LineStyle="Continuous" ss:Weight="1"/>' . "\n";
  $output .= '      <Border ss:Position="Top" ss:LineStyle="Continuous" ss:Weight="1"/>' . "\n";
  $output .= '    </Borders>' . "\n";
  $output .= '  </ss:Style>' . "\n";
  $output .= '  <ss:Style ss:ID="2" ss:Parent="1">' . "\n";
  $output .= '    <Alignment ss:WrapText="1"/>' . "\n";
  $output .= '  </ss:Style>' . "\n";
  $output .= '</Styles>' . "\n";
  $output .= '<Worksheet ss:Name="Variables">' . "\n";
  $output .= '  <Table>' . "\n";
  $header_output = '    <Row ss:AutoFitHeight="1" ss:AutoFitLength="1">' . "\n";
  foreach ($header_result as $header_cell) {
    $header_output .= '      <Cell ss:MergeAcross="'.($header_cell['colspan']-1).'" ss:StyleID="1"><Data ss:Type="String">'.$header_cell['data'].'</Data></Cell>' . "\n";
  }
  $header_output .= '    </Row>' . "\n";
  $header_output .= '    <Row ss:AutoFitHeight="1" ss:AutoFitLength="1">' . "\n";
  foreach ($subheader_result['data'] as $subheader_cell) {
    $header_output .= '      <Cell ss:StyleID="2"><Data ss:Type="String">'.str_replace("<sub>", "", str_replace("</sub>", "", $subheader_cell)).'</Data></Cell>' . "\n";
  }
  $header_output .= '    </Row>' . "\n";
  $i = 0;
  foreach ($items as $item_row) {
    if($i==0){
      foreach ($item_row['data'] as $item_field) {
        $output .= '      <ss:Column ss:Width="100"/>' . "\n";
      }
      $output .= $header_output;
    }
    $output .= '    <Row ss:AutoFitHeight="1" ss:AutoFitLength="1">' . "\n";
    foreach ($item_row['data'] as $item_field) {
      $output .= '      <Cell><Data ss:Type="String">'.$item_field.'</Data></Cell>' . "\n";
    }
    $output .= '    </Row>' . "\n";
    $i++;
  }
  $output .= '  </Table>' . "\n";
  $output .= '  <WorksheetOptions xmlns="urn:schemas-microsoft-com:office:excel">' . "\n";
  $output .= '    <Selected/>' . "\n";
  $output .= '    <ProtectObjects>False</ProtectObjects>' . "\n";
  $output .= '    <ProtectScenarios>False</ProtectScenarios>' . "\n";
  $output .= '  </WorksheetOptions>' . "\n";
  $output .= '</Worksheet>' . "\n";
  $output .= '</Workbook>';

  // Tell the browser that this is not an HTML file to show, but a excel file to
  // download.
  header('Content-Type: application/msexcel');
  header('Content-Length: ' . strlen($output));
  header('Content-Disposition: attachment; filename="mydocument.xls"');
  print $output;
  return NULL;
}

/**
 * Process variables for ohp-case-report-layout.tpl.php
 *
 * @see ohp-case-report-layout.tpl.php
 */
function template_preprocess_ohp_case_report(&$variables) {
  $search_form = $variables['page_content'];
  $search_form_box = drupal_render($search_form);
  $variables['table_results'] = $search_form_box;
}
