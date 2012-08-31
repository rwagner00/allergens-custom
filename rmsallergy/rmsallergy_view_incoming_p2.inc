<?php

/**
 * @file
 * RMS Allergy function file
 */

function rmsallergy_view_incoming_p2 ( $form, &$form_state )
{

// get practice_key from current user
  global $user;
  $account = user_load ( $user->uid );
  $practice_key = field_get_items ( 'user', $account, 'field_practice_key' );
  $practice_key = $practice_key[0]['value'];


// get referral key from previous form page

  $referral_key = $form_state['page_values'][1]['table'];

  if ( empty ( $referral_key ) ) {
    form_set_error ( 'View Incoming', t('Page 2 - Key not found') );
  }


// query the database to get patient record

  db_set_active ( 'rmsallergy' );
  $query = db_select ( 'referral', 'r' );
  $query->join ( 'patient', 'pa', 'r.patient_key = pa.patient_key' );
  $query->join ( 'profile', 'p', 'r.profile_key = p.profile_key' );
  $query->join ( 'practice', 'pr', 'r.practice_key = pr.practice_key' );
  $query
    ->fields ( 'p', array ( 'test_date_month',
                            'test_date_day',
                            'test_date_year', ) )
    ->fields ( 'pa', array ( 'patient_first_name',
                             'patient_middle_name',
                             'patient_last_name',
                             'patient_ssn1',
                             'patient_ssn2',
                             'patient_ssn3',
                             'patient_dob_month',
                             'patient_dob_day',
                             'patient_dob_year',
                             'patient_gender',
                             'patient_address1',
                             'patient_address2',
                             'patient_city',
                             'patient_state',
                             'patient_zip',
                             'patient_home_phone',
                             'patient_work_phone',
                             'patient_mobile_phone',
                             'patient_email',
                             'patient_fax',
                             'minor_flag',
                             'guardian_name',
                             'guardian_address1',
                             'guardian_address2',
                             'guardian_city',
                             'guardian_state',
                             'guardian_zip',
                             'guardian_home_phone',
                             'guardian_work_phone',
                             'guardian_mobile_phone',
                             'guardian_email',
                             'guardian_fax',
      ) )
    ->fields ( 'pr', array ( 'practice_name',
                             'practice_specialty',
                             'practice_admin_poc_name',
                             'practice_admin_poc_email',
                             'practice_clinical_poc_name',
                             'practice_clinical_poc_email',
                             'practice_address1',
                             'practice_address2',
                             'practice_city',
                             'practice_state',
                             'practice_zip',
                             'practice_work_phone',
                             'practice_fax',
      ) )
    ->orderBy ( 'test_date_year', 'DESC' )
    ->orderBy ( 'test_date_month', 'DESC' )
    ->orderBy ( 'test_date_day', 'DESC' )
    ->orderBy ( 'patient_last_name', 'ASC' )
    ->condition ( 'r.referral_key', $referral_key )
    ->condition ( 'r.referred_practice_key', $practice_key );

  $result = $query->execute();

  db_set_active ();

// check for length of array in record
  if ( count($result) != 1 ) {
    form_set_error ( 'View Incoming', t('Error searching on patient.') );
  }

  $record = $result->fetchAssoc();

//drupal_set_message ( print_r ( $result, TRUE ) );
//drupal_set_message ( print_r ( $record, TRUE ) );


// set patient record

  $name = $record['patient_last_name'] . ', ' .  $record['patient_first_name'];
  if ( ! empty ( $record['patient_middle_name'] ) ) {
    $name = $name . ' ' . substr ( $record['patient_middle_name'], 0, 1);
  }

  $gender = $record['patient_gender'];

  $ssn = $record['patient_ssn1'].'-'.$record['patient_ssn2'].'-'.$record['patient_ssn3'];

  $dob = $record['patient_dob_month'] . '/' .
         $record['patient_dob_day']   . '/' .
         $record['patient_dob_year'];

  $address1 = $record['patient_address1'];
  $address2 = $record['patient_address2'];
  $address3 = $record['patient_city'] . ', ' . 
              $record['patient_state'] . ' ' .
              $record['patient_zip'];

  $home_phone = $record['patient_home_phone'];
  $work_phone = $record['patient_work_phone'];
  $mobile_phone = $record['patient_mobile_phone'];

  $email = $record['patient_email'];
  $fax = $record['patient_fax'];



  $minor_flag = $record['minor_flag'];

  $g_name = $record['guardian_name'];

  $g_address1 = $record['guardian_address1'];
  $g_address2 = $record['guardian_address2'];
  $g_address3 = $record['guardian_city'] . ', ' . 
                $record['guardian_state'] . ' ' .
                $record['guardian_zip'];

  $g_home_phone = $record['guardian_home_phone'];
  $g_work_phone = $record['guardian_work_phone'];
  $g_mobile_phone = $record['guardian_mobile_phone'];

  $g_email = $record['guardian_email'];
  $g_fax = $record['guardian_fax'];


  $pr_name = $record['practice_name'];
  $pr_specialty = $record['practice_specialty'];

  $pr_admin_poc_name = $record['practice_admin_poc_name'];
  $pr_admin_poc_email = $record['practice_admin_poc_email'];

  $pr_clinical_poc_name = $record['practice_clinical_poc_name'];
  $pr_clinical_poc_email = $record['practice_clinical_poc_email'];

  $pr_address1 = $record['practice_address1'];
  $pr_address2 = $record['practice_address2'];
  $pr_address3 = $record['practice_city'] . ', ' . 
                 $record['practice_state'] . ' ' .
                 $record['practice_zip'];

  $pr_work_phone = $record['practice_work_phone'];
  $pr_fax = $record['practice_fax'];







  $test_date = $record['test_date_month'] . '/' .
               $record['test_date_day']   . '/' .
               $record['test_date_year'];

  $practice_name = $record['practice_name'];


// display results

  $form['1'] = array (
    '#type' => 'item',
    '#title' => t('Patient Information'),
    '#prefix' => '',
    '#suffix' => '<table>',
  );

  $form['1a'] = array (
    '#type' => 'item',
    '#title' => t('Name:'),
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['1b'] = array (
    '#type' => 'item',
    '#title' => t($name),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );


  $form['1c'] = array (
    '#type' => 'item',
    '#title' => t('Gender: '),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['1d'] = array (
    '#type' => 'item',
    '#title' => t($gender),
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );



  $form['2a'] = array (
    '#type' => 'item',
    '#title' => t('SSN:'),
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['2b'] = array (
    '#type' => 'item',
    '#title' => t($ssn),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['2c'] = array (
    '#type' => 'item',
    '#title' => t('DOB:'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['2d'] = array (
    '#type' => 'item',
    '#title' => t($dob),
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );



  $form['3a'] = array (
    '#type' => 'item',
    '#title' => t('Address:'),
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['3b'] = array (
    '#type' => 'item',
    '#title' => t($address1),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['3c'] = array (
    '#type' => 'item',
    '#title' => t('Home Phone:'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['3d'] = array (
    '#type' => 'item',
    '#title' => t($home_phone),
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );



  $form['4a'] = array (
    '#type' => 'item',
    '#title' => t(''),
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['4b'] = array (
    '#type' => 'item',
    '#title' => t($address2),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['4c'] = array (
    '#type' => 'item',
    '#title' => t('Work Phone:'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['4d'] = array (
    '#type' => 'item',
    '#title' => t($work_phone),
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );



  $form['5a'] = array (
    '#type' => 'item',
    '#title' => t(''),
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['5b'] = array (
    '#type' => 'item',
    '#title' => t($address3),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['5c'] = array (
    '#type' => 'item',
    '#title' => t('Mobile Phone:'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['5d'] = array (
    '#type' => 'item',
    '#title' => t($mobile_phone),
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );



  $form['6a'] = array (
    '#type' => 'item',
    '#title' => t('Email:'),
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['6b'] = array (
    '#type' => 'item',
    '#title' => t($email),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['6c'] = array (
    '#type' => 'item',
    '#title' => t('Fax:'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['6d'] = array (
    '#type' => 'item',
    '#title' => t($fax),
    '#prefix' => '<td>',
    '#suffix' => '</td></tr></table>',
  );





  $form['7'] = array (
    '#type' => 'item',
    '#title' => t('Guardian Information (Optional)'),
    '#prefix' => '',
    '#suffix' => '<table>',
  );

  if ( $minor_flag )
  {
    $form['7a'] = array (
      '#type' => 'item',
      '#title' => t('Name:'),
      '#prefix' => '<tr><td>',
      '#suffix' => '</td>',
    );

    $form['7b'] = array (
      '#type' => 'item',
      '#title' => t($g_name),
      '#prefix' => '<td>',
      '#suffix' => '</td>',
    );

    $form['7c'] = array (
      '#type' => 'item',
      '#title' => t(''),
      '#prefix' => '<td>',
      '#suffix' => '</td>',
    );

    $form['7d'] = array (
      '#type' => 'item',
      '#title' => t(''),
      '#prefix' => '<td>',
      '#suffix' => '</td></tr>',
    );



    $form['9a'] = array (
      '#type' => 'item',
      '#title' => t('Address:'),
      '#prefix' => '<tr><td>',
      '#suffix' => '</td>',
    );

    $form['9b'] = array (
      '#type' => 'item',
      '#title' => t($g_address1),
      '#prefix' => '<td>',
      '#suffix' => '</td>',
    );

    $form['9c'] = array (
      '#type' => 'item',
      '#title' => t('Home Phone:'),
      '#prefix' => '<td>',
      '#suffix' => '</td>',
    );

    $form['9d'] = array (
      '#type' => 'item',
      '#title' => t($g_home_phone),
      '#prefix' => '<td>',
      '#suffix' => '</td></tr>',
    );



    $form['10a'] = array (
      '#type' => 'item',
      '#title' => t(''),
      '#prefix' => '<tr><td>',
      '#suffix' => '</td>',
    );

    $form['10b'] = array (
      '#type' => 'item',
      '#title' => t($g_address2),
      '#prefix' => '<td>',
      '#suffix' => '</td>',
    );

    $form['10c'] = array (
      '#type' => 'item',
      '#title' => t('Work Phone:'),
      '#prefix' => '<td>',
      '#suffix' => '</td>',
    );

    $form['10d'] = array (
      '#type' => 'item',
      '#title' => t($g_work_phone),
      '#prefix' => '<td>',
      '#suffix' => '</td></tr>',
    );



    $form['11a'] = array (
      '#type' => 'item',
      '#title' => t(''),
      '#prefix' => '<tr><td>',
      '#suffix' => '</td>',
    );

    $form['11b'] = array (
      '#type' => 'item',
      '#title' => t($g_address3),
      '#prefix' => '<td>',
      '#suffix' => '</td>',
    );

    $form['11c'] = array (
      '#type' => 'item',
      '#title' => t('Mobile Phone:'),
      '#prefix' => '<td>',
      '#suffix' => '</td>',
    );

    $form['11d'] = array (
      '#type' => 'item',
      '#title' => t($g_mobile_phone),
      '#prefix' => '<td>',
      '#suffix' => '</td></tr>',
    );



    $form['12a'] = array (
      '#type' => 'item',
      '#title' => t('Email:'),
      '#prefix' => '<tr><td>',
      '#suffix' => '</td>',
    );

    $form['12b'] = array (
      '#type' => 'item',
      '#title' => t($g_email),
      '#prefix' => '<td>',
      '#suffix' => '</td>',
    );

    $form['12c'] = array (
      '#type' => 'item',
      '#title' => t('Fax:'),
      '#prefix' => '<td>',
      '#suffix' => '</td>',
    );

    $form['12d'] = array (
      '#type' => 'item',
      '#title' => t($g_fax),
      '#prefix' => '<td>',
      '#suffix' => '</td></tr></table>',
    );

  } else {

    $form['7a'] = array (
      '#type' => 'item',
      '#title' => t('Not applicable'),
      '#prefix' => '<tr><td>',
      '#suffix' => '<td><tr></table>',
    );
  }




  $form['13'] = array (
    '#type' => 'item',
    '#title' => t('Incoming Referral Contact Information'),
    '#prefix' => '',
    '#suffix' => '<table>',
  );


  $form['13a'] = array (
    '#type' => 'item',
    '#title' => t('Practice:'),
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['13b'] = array (
    '#type' => 'item',
    '#title' => t($pr_name),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['13c'] = array (
    '#type' => 'item',
    '#title' => t('Specialty:'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['13d'] = array (
    '#type' => 'item',
    '#title' => t($pr_specialty),
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );



  $form['14a'] = array (
    '#type' => 'item',
    '#title' => t('Admin POC:'),
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['14b'] = array (
    '#type' => 'item',
    '#title' => t($pr_admin_poc_name),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['14c'] = array (
    '#type' => 'item',
    '#title' => t('Email:'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['14d'] = array (
    '#type' => 'item',
    '#title' => t($pr_admin_poc_email),
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );



  $form['15a'] = array (
    '#type' => 'item',
    '#title' => t('Clinical POC:'),
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['15b'] = array (
    '#type' => 'item',
    '#title' => t($pr_clinical_poc_name),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['15c'] = array (
    '#type' => 'item',
    '#title' => t('Email:'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['15d'] = array (
    '#type' => 'item',
    '#title' => t($pr_clinical_poc_email),
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );



  $form['16a'] = array (
    '#type' => 'item',
    '#title' => t('Address:'),
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['16b'] = array (
    '#type' => 'item',
    '#title' => t($pr_address1),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['16c'] = array (
    '#type' => 'item',
    '#title' => t('Phone:'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['16d'] = array (
    '#type' => 'item',
    '#title' => t($pr_work_phone),
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );



  $form['17a'] = array (
    '#type' => 'item',
    '#title' => t(''),
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['17b'] = array (
    '#type' => 'item',
    '#title' => t($pr_address2),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['17c'] = array (
    '#type' => 'item',
    '#title' => t('Fax:'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['17d'] = array (
    '#type' => 'item',
    '#title' => t($pr_fax),
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );



  $form['18a'] = array (
    '#type' => 'item',
    '#title' => t(''),
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['18b'] = array (
    '#type' => 'item',
    '#title' => t($pr_address3),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['18c'] = array (
    '#type' => 'item',
    '#title' => t(''),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['18d'] = array (
    '#type' => 'item',
    '#title' => t(''),
    '#prefix' => '<td>',
    '#suffix' => '</td></tr></table>',
  );


  $form['back'] = array (
    '#type' => 'submit',
    '#value' => t('<< Back'),
    '#validate' => array('rmsallergy_view_incoming_p2_back_validate' ),
    '#submit' => array('rmsallergy_view_incoming_p2_back_submit' ),
  );

  $form['next'] = array (
    '#type' => 'submit',
    '#value' => t('View Allergy Test'),
    '#validate' => array('rmsallergy_view_incoming_p2_next_validate' ),
    '#submit' => array('rmsallergy_view_incoming_p2_next_submit' ),
  );

  return $form;
}

function rmsallergy_view_incoming_p2_back_validate ( $form, &$form_state )
{
  return $form;
}

function rmsallergy_view_incoming_p2_back_submit ( $form, &$form_state )
{
// values are save for each page in order to carry to subsequent pages
// and to tell FAPI how to rebuild the form

  $form_state['page_values'][2] = $form_state['values'];

  if ( !empty($form_state['page_values'][1] )) {
    $form_state['values'] = $form_state['page_values'][1];
  }

  $form_state['page_num'] = 1;
  $form_state['rebuild'] = TRUE;

  return $form;
}


function rmsallergy_view_incoming_p2_next_validate ( $form, &$form_state )
{
  return $form;
}

function rmsallergy_view_incoming_p2_next_submit ( $form, &$form_state )
{
// values are save for each page in order to carry to subsequent pages
// and to tell FAPI how to rebuild the form

  $form_state['page_values'][2] = $form_state['values'];

  if ( !empty($form_state['page_values'][3] )) {
    $form_state['values'] = $form_state['page_values'][3];
  }

  $form_state['page_num'] = 3;
  $form_state['rebuild'] = TRUE;

  return $form;
}

