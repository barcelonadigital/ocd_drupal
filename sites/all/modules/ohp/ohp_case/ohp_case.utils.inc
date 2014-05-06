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
