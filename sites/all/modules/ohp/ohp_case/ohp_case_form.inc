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
 * Constructs a descriptive page.
 *
 * Our menu maps this function to the path 'ohp/ohp_case_form'.
 */
function ohp_case_form_page() {

  $form = array();
  ohp_case_load_common($form);
  $page_array['page_header'] = array(
    '#theme' => 'ohp_case_header_form',
  );

  if(isset($_SESSION['admission_bean']) && isset($_SESSION['admission_bean']->id_admission) &&
      isset($_SESSION['case_bean']) && isset($_SESSION['case_bean']->id_case) &&
      isset($_GET['id_task']) && isset($_GET['id_form'])){
    $id_admission = $_SESSION['admission_bean']->id_admission;
    $id_case      = $_SESSION['case_bean']->id_case;
    $id_task      = $_GET['id_task'];
    $id_form      = $_GET['id_form'];
    $questions_map = array();
    $form_xml = NULL;
    load_form(NULL ,$id_form, $form_xml, $questions_map);

    $task_bean = get_task($id_task);
    $form['controls'] = array(
      '#theme' => 'ohp_case_formctrl',
      '#selected_option' => t('Qüestionari'),
      '#task_status' => $task_bean->status,
    );

    $form['columns_container'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array('columnboxes','clearfix'),
      ),
    );
    $form['columns_container']['column_left'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array('column','por3'),
      ),
    );

    drupal_add_library('system', 'drupal.collapse');

    $form['columns_container']['right_container'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array('column','por6'),
      ),
    );
    $form['columns_container']['right_container']['column_top'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array('column','por6'),
      ),
    );
    $form['columns_container']['right_container']['column_left'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array('column','por3'),
      ),
    );
    $form['columns_container']['right_container']['column_right'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array('column','por3'),
      ),
    );

    add_box('info',$form['columns_container']['column_left'],
        $questions_map,$id_form,$id_task,$id_admission,$id_case,$task_bean->status);
    add_box('diagnostic',$form['columns_container']['column_left'],
        $questions_map,$id_form,$id_task,$id_admission,$id_case,$task_bean->status);
    add_box('caracteristiques',$form['columns_container']['column_left'],
        $questions_map,$id_form,$id_task,$id_admission,$id_case,$task_bean->status);
    add_box('factors',$form['columns_container']['column_left'],
        $questions_map,$id_form,$id_task,$id_admission,$id_case,$task_bean->status,TRUE);
    add_box('adherencia',$form['columns_container']['column_left'],
        $questions_map,$id_form,$id_task,$id_admission,$id_case,$task_bean->status,TRUE);
    add_box('percepcio',$form['columns_container']['column_left'],
        $questions_map,$id_form,$id_task,$id_admission,$id_case,$task_bean->status,TRUE);

    add_box('equip',$form['columns_container']['right_container']['column_left'],
        $questions_map,$id_form,$id_task,$id_admission,$id_case,$task_bean->status);
    if($form_xml->data->name=='Variables'){
      add_box('planificacio',$form['columns_container']['right_container']['column_left'],
          $questions_map,$id_form,$id_task,$id_admission,$id_case,$task_bean->status);
    }else if($form_xml->data->name=='CVSO'){
      add_box('planificacio',$form['columns_container']['right_container']['column_top'],
          $questions_map,$id_form,$id_task,$id_admission,$id_case,$task_bean->status,TRUE);
    }
    add_box('comentaris',$form['columns_container']['right_container']['column_left'],
        $questions_map,$id_form,$id_task,$id_admission,$id_case,$task_bean->status);

    add_box('proves',$form['columns_container']['right_container']['column_right'],
        $questions_map,$id_form,$id_task,$id_admission,$id_case,$task_bean->status);

  }

  $page_array['main'] = array(
    '#theme' => 'ohp_case_body',
  );
  $page_array['main']['pager_container'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('content','full'),
    ),
  );
  $page_array['main']['pager_container']['pager_table'] = $form;

  drupal_add_css(drupal_get_path('module', 'ohp_case') . '/css/ohp_case_form.css');
  return $page_array;
}
function add_content_box($group_name,&$form_array,$questions_map,$text_title,&$num_questions,$id_form,$id_task,$id_admission,$id_case,$task_status,$collapsed = FALSE){
  $ids_array = get_form_items($group_name);
  $form_object=get_form_object($group_name);

  $link_attributes = array('class' => array('btn-primary', 'btn', 'btn-editform'));
  if($task_status=='DONE'){
    $link_attributes['style'] = 'display:none';
  }
  $form_array[$group_name][] = array(
    '#markup' => '<hr>'.l(t('Editar'),
        'ohp/ohp_case_formunit',
        array('attributes' => $link_attributes,
              'query' => array('id_form' => $id_form, 'id_task' => $id_task,
                'id_admission' => $id_admission, 'id_case' => $id_case, 'group_form' => $group_name))));
  if(isset($text_title) && $text_title!=NULL){
    $form_array[$group_name][] = array(
      '#markup' => '<span class="question">'.$text_title.'</span> <span class="answer"></span><br/>',
    );
  }
  $size_before = count($form_array[$group_name]);
  foreach ($ids_array as $id_question) {
    if(isset($questions_map[$id_question])){
      $question_obj = $questions_map[$id_question];
      if($question_obj->type=='STATIC_TEXT' ||
          $question_obj->value!=NULL && $question_obj->value!=""){
        $form_array[$group_name][] = array(
          '#markup' => '<span class="question">'.$question_obj->description.'</span> <span class="answer">'.get_value_description($id_question, $questions_map).'</span><br/>',
        );
      }
      $num_questions++;
    }
  }
  $size_after = count($form_array[$group_name]);
  if($size_before==$size_after){
    $form_array[$group_name][] = array(
      '#markup' => t('No hi ha elements per mostrar.'),
    );
  }

  if(isset($form_object['hide_title']) && $form_object['hide_title']==TRUE){
    $form_array[$group_name][] = array('#markup' => '<hr>');
  }
}
function add_box($group_name,&$form_result,$questions_map,$id_form,$id_task,$id_admission,$id_case,$task_status,$collapsed = FALSE){

  $form_object=get_form_object($group_name);
  if(isset($form_object['groups'])){
    $form_subresult=array();
    foreach ($form_object['groups'] as $key => $struct_group) {
      $count_questions=0;
      $form_subgroup=array();
      add_content_box($key,$form_subgroup,$questions_map,$struct_group['title'],$count_questions,$id_form,$id_task,$id_admission,$id_case,$task_status,$collapsed);
      if($count_questions>0){
        $form_subresult[$key] = $form_subgroup;
      }
    }
    if(count($form_subresult)>0){
      $fieldset_classes = array('collapsible','ohp-form-summary');
      if($collapsed){
        $fieldset_classes[] = 'collapsed';
      }
      $form_subresult['#type']='fieldset';
      $form_subresult['#title']=$form_object['title'];
      $form_subresult['#attributes']=array (
          'class' => $fieldset_classes
        );
      $form_result[] = $form_subresult;
    }
  }else{
    $count_questions=0;
    $form_subgroup=array();
    add_content_box($group_name,$form_subgroup,$questions_map,NULL,$count_questions,$id_form,$id_task,$id_admission,$id_case,$task_status,$collapsed);
    if($count_questions>0){
      if(isset($form_object['hide_title']) && $form_object['hide_title']==TRUE){
        $form_subgroup[$group_name]['#type']='container';
        $form_subgroup[$group_name]['#attributes']=array(
            'class' => array('notitlebox'),
          );
      }else{
        $fieldset_classes = array('collapsible','ohp-form-summary');
        if($collapsed){
          $fieldset_classes[] = 'collapsed';
        }
        $form_subgroup[$group_name]['#type']='fieldset';
        $form_subgroup[$group_name]['#title']=$form_object['title'];
        $form_subgroup[$group_name]['#attributes']=array (
            'class' => $fieldset_classes
          );
      }
      $form_result[] = $form_subgroup;
    }
  }
}

