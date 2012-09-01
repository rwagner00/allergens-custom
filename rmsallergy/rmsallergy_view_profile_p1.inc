<?php

/**
 * @file
 * RMS Allergy function file
 */

function rmsallergy_view_profile_p1 ( $form, &$form_state )
{

// get practice_key from current user
  global $user;
  $account = user_load ( $user->uid );
  $practice_key = field_get_items ( 'user', $account, 'field_practice_key' );
  $practice_key = $practice_key[0]['value'];


// query the database for patient records

  db_set_active ( 'rmsallergy' );
  $query = db_select ( 'profile', 'p' );
  $query->join ( 'patient', 'pa', 'p.patient_key = pa.patient_key' );
  $query
    ->fields ( 'p', array ( 'profile_key',
                            'test_date_month',
                            'test_date_day',
                            'test_date_year', ) )
    ->fields ( 'pa', array ( 'patient_first_name',
                             'patient_middle_name',
                             'patient_last_name',
                             'patient_dob_month',
                             'patient_dob_day',
                             'patient_dob_year', ) )
    ->orderBy ( 'test_date_year', 'DESC' )
    ->orderBy ( 'test_date_month', 'DESC' )
    ->orderBy ( 'test_date_day', 'DESC' )
    ->orderBy ( 'patient_last_name', 'ASC' )
    ->condition ( 'p.practice_key', $practice_key );

  $result = $query->execute();

  db_set_active ();

  $options = array ();
  foreach ( $result as $record ) {
    $profile_key = $record->profile_key;

    $name = $record->patient_last_name . ', ' .  $record->patient_first_name;
    if ( ! empty ( $record->patient_middle_name ) ) {
      $name = $name . ' ' . substr ( $record->patient_middle_name, 0, 1);
    }

    $dob = $record->patient_dob_month . '/' .
           $record->patient_dob_day   . '/' .
           $record->patient_dob_year;

    $test_date = $record->test_date_month . '/' .
                 $record->test_date_day   . '/' .
                 $record->test_date_year;


    $options [ $profile_key ] = array (
      'patient_name' => $name,
      'dob' => $dob,
      'test_date' => $test_date,
    );
  }

  $header = array (
    'patient_name' => t('Patient Name'),
    'dob' => t('Date of Birth'),
    'test_date' => t('Test Date'),
  );

  $form['table'] = array (
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#multiple' => FALSE,
    '#empty' => t('No Allergy Tests in Database'),
  );

  $form['submit'] = array (
    '#type' => 'submit',
    '#value' => t('Show Allergy Test'),
    '#submit' => array('rmsallergy_view_profile_p1_next_submit' ),
    '#validate' => array('rmsallergy_view_profile_p1_next_validate' ),
  );

  return $form;
}

function rmsallergy_view_profile_p1_next_validate ( $form, &$form_state )
{
  $profile_key = $form_state['values']['table'];

  if ( empty ( $profile_key ) ) {
    form_set_error ( 'View Allergy Test', t('Please select a patient.') );
  }

  return $form;
}

function rmsallergy_view_profile_p1_next_submit ( $form, &$form_state )
{
// values are save for each page in order to carry to subsequent pages
// and to tell FAPI how to rebuild the form

  $form_state['page_values'][1] = $form_state['values'];

  if ( !empty($form_state['page_values'][2] )) {
    $form_state['values'] = $form_state['page_values'][2];
  }

  $form_state['page_num'] = 2;
  $form_state['rebuild'] = TRUE;

  return $form;
}

