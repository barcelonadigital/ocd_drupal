<?php

/**
 * @file
 * A file with form utils.
 */

/**
 * Custom content function.
 *
 * Retrieve cases from database.
 *
 * @return
 *   A result set of the targeted cases.
 */
function search_case($search_str) {

  $query = db_select('ohp_identification', 'n');
  $query->leftJoin('ohp_phone', 'p', 'n.user_uid = p.user_uid');
  $query->addField('n', 'user_uid');
  $query->addField('n', 'cip');
  $query->addField('n', 'nif');
  $query->addField('n', 'given_name');
  $query->addField('n', 'middle_name');
  $query->addField('n', 'family_name');
  $query->addField('n', 'family_name2');
  $or = db_or();
  $or->condition('n.cip','%'.db_like($search_str).'%','LIKE');
  $or->condition('n.nhc','%'.db_like($search_str).'%','LIKE');
  $or->condition('n.nif','%'.db_like($search_str).'%','LIKE');
  $or->condition('n.nie','%'.db_like($search_str).'%','LIKE');
  $or->condition('n.pas','%'.db_like($search_str).'%','LIKE');
  $or->condition('n.given_name','%'.db_like($search_str).'%','LIKE');
  $or->condition('n.middle_name','%'.db_like($search_str).'%','LIKE');
  $or->condition('n.family_name','%'.db_like($search_str).'%','LIKE');
  $or->condition('n.family_name2','%'.db_like($search_str).'%','LIKE');
  $or->condition('p.number','%'.db_like($search_str).'%','LIKE');
  $query->condition($or);
  $query->distinct();
  $query->orderBy('n.user_uid', 'DESC');

  $result = $query->execute();

  return $result;
}

/**
 * Custom content function.
 *
 * Retrieve one single case from database.
 *
 * @return
 *   An object of the targeted case.
 */
function get_case_identification($case_id) {

  $query = db_select('ohp_identification', 'n');
  $query->addField('n', 'user_uid');
  $query->addField('n', 'cip');
  $query->addField('n', 'nif');
  $query->addField('n', 'nie');
  $query->addField('n', 'pas');
  $query->addField('n', 'nhc');
  $query->addField('n', 'given_name');
  $query->addField('n', 'middle_name');
  $query->addField('n', 'family_name');
  $query->addField('n', 'family_name2');
  $query->addField('n', 'gender');
  $query->addField('n', 'birthdate');
  $query->condition('n.user_uid',$case_id,'=');

  $result = $query->execute()->fetchAssoc();

  return $result;
}

/**
 * Custom content function.
 *
 * Retrieve one single task from database.
 *
 * @return
 *   An object of the targeted task.
 */
function get_task($id_task) {

  $query = db_select('ohp_task', 'n');
  $query->join('ohp_activity', 'p', 'n.id_activity = p.id_activity');
  $query->addField('n', 'status');
  $query->addField('n', 'date');
  $query->addField('n', 'type');
  $query->addField('n', 'id_task');
  $query->addField('n', 'id_activity');
  $query->addField('n', 'id_admission');
  $query->addField('p', 'description');
  $query->condition('n.id_task',$id_task,'=');

  $result = $query->execute()->fetchObject();

  return $result;
}

/**
 * Custom content function.
 *
 * Retrieve one single form from database.
 *
 * @return
 *   An object of the targeted form.
 */
function get_form($id_form) {

  $query = db_select('ohp_form', 'n');
  $query->join('ohp_template', 'p', 'n.id_template = p.id_template');
  $query->addField('n', 'status');
  $query->addField('n', 'id_form');
  $query->addField('n', 'id_template');
  $query->addField('n', 'id_task');
  $query->addField('p', 'description');
  $query->condition('n.id_form',$id_form,'=');

  $result = $query->execute()->fetchObject();

  $result->data = new stdClass();
  $result->data->name = $result->description;

  return $result;
}

/**
 * Custom content function.
 *
 * Retrieve one case phones from database.
 *
 * @return
 *   A set of phones from the case.
 */
function get_case_phone($case_id) {

  $query = db_select('ohp_phone', 'n');
  $query->addField('n', 'type');
  $query->addField('n', 'number');
  $query->condition('n.user_uid',$case_id,'=');

  $result = $query->execute();

  return $result;
}

/**
 * Custom content function.
 *
 * Retrieve one case addresses from database.
 *
 * @return
 *   A set of addresses from the case.
 */
function get_case_address($case_id) {

  $query = db_select('ohp_address', 'n');
  $query->addField('n', 'street');
  $query->addField('n', 'number');
  $query->addField('n', 'floor');
  $query->addField('n', 'suite');
  $query->addField('n', 'city');
  $query->addField('n', 'postcode');
  $query->addField('n', 'country');
  $query->condition('n.user_uid',$case_id,'=');

  $result = $query->execute();

  return $result;
}

/**
 * Custom content function.
 *
 * Retrieve case admissions from database.
 *
 * @return
 *   A set of admissions from the case.
 */
function get_case_admission($case_id) {

  $query = db_select('ohp_admission', 'n');
  $query->addField('n', 'id_admission');
  $query->addField('n', 'enrol_date');
  $query->addField('n', 'admission_date');
  $query->addField('n', 'discharge_date');
  $query->addField('n', 'status');
  $query->condition('n.user_uid',$case_id,'=');

  $result = $query->execute();

  return $result;
}

/**
 * Custom content function.
 *
 * Retrieve case admissions from database.
 *
 * @return
 *   A set of admissions from the case.
 */
function get_admission($admission_id) {

  $query = db_select('ohp_admission', 'n');
  $query->addField('n', 'id_admission');
  $query->addField('n', 'enrol_date');
  $query->addField('n', 'admission_date');
  $query->addField('n', 'discharge_date');
  $query->addField('n', 'status');
  $query->condition('n.id_admission',$admission_id,'=');

  $result = $query->execute()->fetchObject();

  return $result;
}

/**
 * Custom content function.
 *
 * Retrieve admission tasks from database.
 *
 * @return
 *   A set of tasks from the admission.
 */
function get_admission_tasks($admission_id) {

  $query = db_select('ohp_task', 'n');
  $query->join('ohp_activity', 'p', 'n.id_activity = p.id_activity');
  $query->addField('n', 'status');
  $query->addField('n', 'date');
  $query->addField('n', 'type');
  $query->addField('n', 'id_task');
  $query->addField('n', 'id_activity');
  $query->addField('n', 'id_admission');
  $query->addField('p', 'description');
  $query->condition('n.id_admission',$admission_id,'=');
  $query->orderBy('n.id_task', 'ASC');

  $result = $query->execute();

  return $result;
}

/**
 * Custom content function.
 *
 * Retrieve task forms from database.
 *
 * @return
 *   A set of forms from the task.
 */
function get_task_forms($id_task) {

  $query = db_select('ohp_form', 'n');
  $query->join('ohp_template', 'p', 'n.id_template = p.id_template');
  $query->addField('n', 'status');
  $query->addField('n', 'id_task');
  $query->addField('n', 'id_template');
  $query->addField('n', 'id_form');
  $query->addField('p', 'description', 'short_name');
  $query->condition('n.id_task',$id_task,'=');

  $result = $query->execute();

  return $result;
}

/**
 * Custom content function.
 *
 * Retrieve form answers from database.
 *
 * @return
 *   A set of answers from the form.
 */
function get_form_answers($id_form) {

  $query = db_select('ohp_answer', 'n');
  $query->join('ohp_question', 'p', 'n.id_question = p.id_question');
  $query->addField('n', 'value');
  $query->addField('n', 'id_option');
  $query->addField('n', 'id_answer');
  $query->addField('n', 'id_form');
  $query->addField('n', 'id_question');
  $query->addField('p', 'description');
  $query->addField('p', 'formula');
  $query->addField('p', 'requirement');
  $query->addField('p', 'min_value');
  $query->addField('p', 'max_value');
  $query->addField('p', 'mandatory');
  $query->addField('p', 'type');
  $query->addField('p', 'min_length');
  $query->addField('p', 'max_length');
  $query->addField('p', 'num_decimals');
  $query->condition('n.id_form',$id_form,'=');

  $result = $query->execute();

  return $result;
}

/**
 * Custom content function.
 *
 * Retrieve form answers options from database.
 *
 * @return
 *   A set of options from the form answers.
 */
function get_formanswers_options($id_form) {

  $query = db_select('ohp_answer', 'n');
  $query->join('ohp_option', 'p', 'n.id_question = p.id_question');
  $query->addField('p', 'value');
  $query->addField('p', 'description');
  $query->addField('p', 'id_question');
  $query->addField('p', 'id_option');
  $query->condition('n.id_form',$id_form,'=');

  $result = $query->execute();

  return $result;
}

/**
 * Custom update function.
 *
 * Update answer in database.
 */
function update_answer($answer_id,$option_id,$value) {

  $entry = array(
    'id_option' => $option_id,
    'value' => $value,
  );
  $count = db_update('ohp_answer')
    ->fields($entry)
    ->condition('id_answer', $answer_id)
    ->execute();

  return $count;
}

/**
 * Custom update function.
 *
 * Insert admission in database.
 */
function insert_admission($id_case) {

  $query = db_select('ohp_admission');
  $query->addExpression('MAX(id_admission)');
  $max= $query->execute()->fetchField();
  $id_admission = $max+1;

  $value = getdate();
  $today = mktime(0, 0, 0, $value['mon'], $value['mday'], $value['year']);

  $entry = array(
    'id_admission' => $id_admission,
    'user_uid' => $id_case,
    'enrol_date' => $today,
    'status' => 'ENROLLED',
  );
  $result = db_insert('ohp_admission')
    ->fields($entry)
    ->execute();

  return $id_admission;
}

/**
 * Custom update function.
 *
 * Update admission in database.
 */
function update_admission($id_admission,$admission_date,$status) {

  $entry = array(
    'admission_date' => $admission_date,
    'status' => $status,
  );
  $count = db_update('ohp_admission')
    ->fields($entry)
    ->condition('id_admission', $id_admission)
    ->execute();

  return $count;
}

/**
 * Custom update function.
 *
 * Insert task in database.
 */
function insert_task($id_admission,$id_activity) {

  $query = db_select('ohp_task');
  $query->addExpression('MAX(id_task)');
  $max= $query->execute()->fetchField();

  $value = getdate();
  $today = mktime(0, 0, 0, $value['mon'], $value['mday'], $value['year']);

  if($id_activity=="#TASK:N261"){
    $id_activity = 2;
  }else if($id_activity=="#TASK:N253"){
    $id_activity = 1;
  }
  $id_task = $max+1;
  $entry = array(
    'id_task' => $max+1,
    'id_activity' => $id_activity,
    'id_admission' => $id_admission,
    'status' => 'ACTIVE',
    'date' => $today,
    'type' => 'PRO_TASK',
  );
  $result_task = db_insert('ohp_task')
    ->fields($entry)
    ->execute();

  $query = db_select('ohp_template', 'n');
  $query->addField('n', 'id_template');
  $query->addField('n', 'id_activity');
  $query->addField('n', 'description');
  $query->condition('n.id_activity',$id_activity,'=');

  $result_template = $query->execute();

  foreach ($result_template as $row_template) {


    $query = db_select('ohp_form', 'n');
    $query->join('ohp_task', 'p', 'n.id_task = p.id_task');
    $query->join('ohp_template', 'o', 'o.id_template = n.id_template');
    $query->addExpression('MAX(n.id_form)');
    $query->condition('p.id_admission',$id_admission,'=');
    $query->condition('o.id_activity',array(1,2),'IN');

    $maxform= $query->execute()->fetchField();
// if(!isset($maxform)){
// drupal_set_message('A'.' '.$id_admission);
// var_dump('A'.' '.$id_admission);
// }else if($maxform==null){
// drupal_set_message('B');
// var_dump('B');
// }else{
// drupal_set_message($maxform);
// var_dump($maxform);
// }

    $query = db_select('ohp_form');
    $query->addExpression('MAX(id_form)');
    $max= $query->execute()->fetchField();

    $id_form = $max+1;
    $id_template = $row_template->id_template;
    $entry = array(
      'id_form' => $id_form,
      'id_template' => $id_template,
      'id_task' => $id_task,
      'status' => 'OPEN',
    );
    $result_form = db_insert('ohp_form')
      ->fields($entry)
      ->execute();

    $query = db_select('ohp_template_question', 'n');
    if(isset($maxform)){
      $query->leftJoin('ohp_answer', 'p', 'n.id_question = p.id_question and p.id_form='.$maxform);
    }
    $query->addField('n', 'id_template_question');
    $query->addField('n', 'id_template');
    $query->addField('n', 'id_question');
    if(isset($maxform)){
      $query->addField('p', 'id_option');
      $query->addField('p', 'value');
    }
    $query->condition('n.id_template',$id_template,'=');
//     if(isset($maxform)){
//       $query->condition('p.id_form',$maxform,'=');
// var_dump('$maxform '.$maxform);
// drupal_set_message('$maxform '.$maxform);
//     }

    $result_tq = $query->execute();
var_dump('$$query-> '.$query->__toString());
drupal_set_message('$$query-> '.$query->__toString());

    foreach ($result_tq as $row_tq) {
      $query = db_select('ohp_answer');
      $query->addExpression('MAX(id_answer)');
      $max= $query->execute()->fetchField();

      $id_option = NULL;
      if(isset($row_tq->id_option)){
        $id_option = $row_tq->id_option;
      }
      $value = NULL;
      if(isset($row_tq->value)){
        $value = $row_tq->value;
      }
      $entry = array(
        'id_answer' => $max+1,
        'id_form' => $id_form,
        'id_question' => $row_tq->id_question,
        'id_option' => $id_option,
        'value' => $value,
      );
      $result_task = db_insert('ohp_answer')
        ->fields($entry)
        ->execute();
    }
  }

  $admission_obj = get_admission($id_admission);

  if($admission_obj->status!='ACTIVE'){
    $value = getdate();
    $enrol_date = mktime($value['hours'], $value['minutes'], 0, $value['mon'], $value['mday'], $value['year']);
    update_admission($id_admission,$enrol_date,'ACTIVE');
  }
}

function get_age( $then_ts )
{
  $then_year = date('Y', $then_ts);
  $age = date('Y') - $then_year;
  if (strtotime('+' . $age . ' years', $then_ts) > time())
      $age--;
  return $age;
}

function get_fullname ($given_name, $middle_name, $family_name, $family_name2) {
  $full_name = $given_name;
  if(isset($middle_name) && $middle_name!=""){
    $full_name .= ' '.$middle_name;
  }
  if(isset($family_name) && $family_name!=""){
    $full_name .= ' '.$family_name;
  }
  if(isset($family_name2) && $family_name2!=""){
    $full_name .= ' '.$family_name2;
  }
  return $full_name;
}

/**
 * @} End of "defgroup case_task".
 */
