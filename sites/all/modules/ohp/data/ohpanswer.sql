select a.*, 
CASE 
    WHEN b.type='DATE' THEN DATE_FORMAT(FROM_UNIXTIME(a.value), '%d-%m-%Y') 
    WHEN b.type='TEXT' THEN a.value
    WHEN b.type='FORMULA' THEN a.value
    WHEN b.type='TEXT_AREA' THEN a.value
    WHEN b.type='VERTICAL_RADIO' THEN g.description
    ELSE 'error'
  end AS type_text,
convert(b.description using utf8) as description, f.cip, f.given_name from ohp_answer a
join ohp_question b on b.id_question = a.id_question
join ohp_form c on c.id_form = a.id_form
join ohp_task d on d.id_task = c.id_task
join ohp_admission e on e.id_admission = d.id_admission
join ohp_identification f on f.user_uid = e.user_uid
left join ohp_option g on g.id_option = a.id_option
ORDER BY id_form,id_question
