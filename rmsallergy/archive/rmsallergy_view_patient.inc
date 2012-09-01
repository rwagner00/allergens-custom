<?php

/**
 * @file
 * RMS Allergy function file
 */

function rmsallergy_view_patient ( $form, &$form_state )
{

// build the table of patients

  $form['subtitle'] = array (
    '#type' => 'item',
    '#title' => t('Select a Patient (Select Only One):'),
  );


  db_set_active ( 'rmsallergy' );

  $query = db_select ( 'patient', 'p' );
  $query
    ->fields ( 'p', array ( 'patient_key',
                            'patient_name' ))
    ->orderBy ( 'patient_name', 'ASC' );

  $result = $query->execute();

  db_set_active ();

  $options = array ();
  foreach ( $result as $record ) {
    $options [ $record->patient_key ] = array (
      'patient_name' => $record->patient_name,
    );
  }

  $header = array (
    'patient_name' => t('Patient Name'),
  );

  $form['table'] = array (
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#empty' => t('No Patients in Database'),
  );


  // code for refresh button - when user selects refresh, the rest
  // of the form will be populated with patient information

  $form['refresh'] = array (
    '#type' => 'submit',
    '#value' => t('Refresh'),
    '#validate' => array ( 'rmsallergy_view_patient_validate' ),
    '#submit' => array ( 'rmsallergy_view_patient_refresh_submit' ),
  );



//
// set default values for the remainder of the form
//


  $patient_name = !empty ( $form_state['values']['patient_name'] ) ?
                           $form_state['values']['patient_name'] : '';
  $ssn = !empty ( $form_state['values']['ssn'] ) ?
                  $form_state['values']['ssn'] : '';
  $dob = !empty ( $form_state['values']['dob'] ) ?
                  $form_state['values']['dob'] : '';
  $dob = '';
  $gender = !empty ( $form_state['values']['gender'] ) ?
                     $form_state['values']['gender'] : '';
  $primary_flag = !empty ( $form_state['values']['primary_flag'] ) ?
                           $form_state['values']['primary_flag'] : '';
  $secondary_flag = !empty ( $form_state['values']['secondary_flag'] ) ?
                             $form_state['values']['secondary_flag'] : '';
  $minor_flag = !empty ( $form_state['values']['minor_flag'] ) ?
                         $form_state['values']['minor_flag'] : '';

  $contact_name = !empty ( $form_state['values']['contact_name'] ) ?
                           $form_state['values']['contact_name'] : '';
  $address1 = !empty ( $form_state['values']['address1'] ) ?
                       $form_state['values']['address1'] : '';
  $address2 = !empty ( $form_state['values']['address2'] ) ?
                       $form_state['values']['address2'] : '';
  $city = !empty ( $form_state['values']['city'] ) ?
                   $form_state['values']['city'] : '';
  $state = !empty ( $form_state['values']['state'] ) ?
                    $form_state['values']['state'] : '';
  $zip = !empty ( $form_state['values']['zip'] ) ?
                  $form_state['values']['zip'] : '';
  $phone = !empty ( $form_state['values']['phone'] ) ?
                    $form_state['values']['phone'] : '';
  $email = !empty ( $form_state['values']['email'] ) ?
                    $form_state['values']['email'] : '';
  $fax = !empty ( $form_state['values']['fax'] ) ?
                  $form_state['values']['fax'] : '';


//
// build the edit fields of the form
//

  unset($form_state['input']['patient_name']);
  unset($form_state['input']['ssn']);
  unset($form_state['input']['dob']);
  unset($form_state['input']['gender']);
  unset($form_state['input']['primary_flag']);
  unset($form_state['input']['secondary_flag']);
  unset($form_state['input']['minor_flag']);

  $form['patient'] = array (
    '#type' => 'fieldset',
    '#title' => t('Patient Information'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['patient']['patient_name'] = array (
    '#type' => 'textfield',
    '#title' => t('Patient Name'),
    '#size' => 64,
    '#default_value' => $patient_name,
  );

  $form['patient']['ssn'] = array (
    '#type' => 'textfield',
    '#title' => t('SSN'),
    '#size' => 16,
    '#default_value' => $ssn,
  );

  $form['patient']['dob'] = array (
    '#type' => 'textfield',
    '#title' => t('Date of Birth (mm/dd/yyyy)'),
    '#size' => 10,
    '#default_value' => $dob,
  );

  $form['patient']['gender'] = array (
    '#type' => 'textfield',
    '#title' => t('Gender'),
    '#size' => 1,
    '#default_value' => $gender,
  );

  $form['patient']['minor_flag'] = array (
    '#type' => 'checkbox',
    '#title' => 'Check If Patient is a Minor',
    '#default_value' => $minor_flag,
  );

  $form['patient']['primary_flag'] = array (
    '#type' => 'checkbox',
    '#title' => 'Check If Patient Has Primary Coverage',
    '#default_value' => $primary_flag,
  );

  $form['patient']['secondary_flag'] = array (
    '#type' => 'checkbox',
    '#title' => 'Check If Patient Has Secondary Coverage',
    '#default_value' => $secondary_flag,
  );
  

  $form['contact'] = array (
    '#type' => 'fieldset',
    '#title' => t('Primary Contact Information'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  unset($form_state['input']['contact_name']);
  unset($form_state['input']['address1']);
  unset($form_state['input']['address2']);
  unset($form_state['input']['city']);
  unset($form_state['input']['state']);
  unset($form_state['input']['zip']);
  unset($form_state['input']['phone']);
  unset($form_state['input']['email']);
  unset($form_state['input']['fax']);

  $form['contact']['contact_name'] = array (
    '#type' => 'textfield',
    '#title' => t('Location Description'),
    '#size' => 50,
//    '#required' => TRUE,
    '#default_value' => $contact_name,
  );


  $form['contact']['address1'] = array (
    '#type' => 'textfield',
    '#title' => t('Address'),
    '#size' => 50,
//    '#required' => TRUE,
    '#default_value' => $address1,
  );

  $form['contact']['address2'] = array (
    '#type' => 'textfield',
    '#title' => t(''),
    '#size' => 50,
    '#default_value' => $address2,
  );

  $form['contact']['city'] = array (
    '#type' => 'textfield',
    '#title' => t('City'),
    '#size' => 50,
//    '#required' => TRUE,
    '#default_value' => $city,
  );

  $form['contact']['state'] = array (
    '#type' => 'textfield',
    '#title' => t('State'),
    '#size' => 50,
//    '#required' => TRUE,
    '#default_value' => $state,
  );

  $form['contact']['zip'] = array (
    '#type' => 'textfield',
    '#title' => t('Zip'),
    '#size' => 50,
//    '#required' => TRUE,
    '#default_value' => $zip,
  );

  $form['contact']['phone'] = array (
    '#type' => 'textfield',
    '#title' => t('Main Phone'),
    '#size' => 50,
//    '#required' => TRUE,
    '#default_value' => $phone,
  );

  $form['contact']['email'] = array (
    '#type' => 'textfield',
    '#title' => t('Email'),
    '#size' => 50,
//    '#required' => TRUE,
    '#default_value' => $email,
  );

  $form['contact']['fax'] = array (
    '#type' => 'textfield',
    '#title' => t('Fax'),
    '#size' => 50,
//    '#required' => TRUE,
    '#default_value' => $fax,
  );

  $form['submit_new'] = array (
    '#type' => 'submit',
    '#value' => t('Submit As New'),
    '#validate' => array ( 'rmsallergy_view_patient_new_validate' ),
    '#submit' => array ( 'rmsallergy_view_patient_new_submit' ),
  );

  $form['submit_update'] = array (
    '#type' => 'submit',
    '#value' => t('Update'),
    '#validate' => array ( 'rmsallergy_view_patient_validate' ),
    '#submit' => array ( 'rmsallergy_view_patient_update_submit' ),
  );

  return $form;
}






function rmsallergy_view_patient_validate ( $form, &$form_state )
{
  $result = $form_state['values']['table'];

  $num_record=0;
  foreach ( $result as $record ) {
    if ( $record > 0 ) {
      $num_record = $num_record + 1;
    }
  }

  if ( $num_record < 1 )
  { 
    form_set_error ( 'View Patient', t("Please select a patient.") );
  } elseif ( $num_record > 1 ) { 
    form_set_error ( 'View Patient', t("Please select only one patient.") );
  }

  return $form;
}

function rmsallergy_view_patient_new_validate ( $form, &$form_state )
{
  return $form;
}




function rmsallergy_view_patient_refresh_submit ( $form, &$form_state )
{
// the refresh routine will populate the values array with the data
// of the selected patient

  // get the patient key from the table element

  $result = $form_state['values']['table'];

  $patient_key = NULL;
  foreach ( $result as $record ) {
    if ( $record > 0 ) {
      $patient_key = $record;
    }
  }

  // query the patient table to retrieve the information

  db_set_active ( 'rmsallergy' );

  $query = db_select ( 'patient', 'p' );
  $query
    ->fields ( 'p', array ( 'patient_key',
                            'patient_name',
                            'patient_ssn',
                            'patient_dob',
                            'patient_gender',
                            'patient_minor_flag',
                            'patient_primary_flag',
                            'patient_secondary_flag',
                            'patient_contact_key' ))
    ->condition ( 'patient_key', $patient_key );

  $result = $query->execute();

  $record = $result->fetchAssoc();

  db_set_active ();


  form_set_value ( $form['patient']['patient_name'],
                   $record['patient_name'],
                   $form_state );
  form_set_value ( $form['patient']['ssn'],
                   $record['patient_ssn'],
                   $form_state );
  form_set_value ( $form['patient']['dob'],
                   $record['patient_dob'],
                   $form_state );
  form_set_value ( $form['patient']['gender'],
                   $record['patient_gender'],
                   $form_state );
  form_set_value ( $form['patient']['minor_flag'],
                   $record['patient_minor_flag'],
                   $form_state );
  form_set_value ( $form['patient']['primary_flag'],
                   $record['patient_primary_flag'],
                   $form_state );
  form_set_value ( $form['patient']['secondary_flag'],
                   $record['patient_secondary_flag'],
                   $form_state );


  $contact_key = $record['patient_contact_key'];

  db_set_active ( 'rmsallergy' );

  $query = db_select ( 'contact', 'p' );
  $query
    ->fields ( 'p', array ( 'contact_name',
                            'contact_address1',
                            'contact_address2',
                            'contact_city',
                            'contact_state',
                            'contact_zip',
                            'contact_home_phone',
                            'contact_work_phone',
                            'contact_mobile_phone',
                            'contact_email',
                            'contact_fax'))
    ->condition ( 'contact_key', $contact_key );

  $result = $query->execute();

  $record = $result->fetchAssoc();

  db_set_active ();

  form_set_value ( $form['contact']['contact_name'],
                   $record['contact_name'],
                   $form_state );
  form_set_value ( $form['contact']['address1'],
                   $record['contact_address1'],
                   $form_state );
  form_set_value ( $form['contact']['address2'],
                   $record['contact_address2'],
                   $form_state );
  form_set_value ( $form['contact']['city'],
                   $record['contact_city'],
                   $form_state );
  form_set_value ( $form['contact']['state'],
                   $record['contact_state'],
                   $form_state );
  form_set_value ( $form['contact']['zip'],
                   $record['contact_zip'],
                   $form_state );
  form_set_value ( $form['contact']['phone'],
                   $record['contact_work_phone'],
                   $form_state );
  form_set_value ( $form['contact']['email'],
                   $record['contact_email'],
                   $form_state );
  form_set_value ( $form['contact']['fax'],
                   $record['contact_fax'],
                   $form_state );


  $form_state['rebuild'] = TRUE;
}






function rmsallergy_view_patient_new_submit ( $form, &$form_state )
{

  // get the data out of the form
  $patient_name = $form_state['values']['patient_name'];
  $ssn = $form_state['values']['ssn'];
  $dob = $form_state['values']['dob'];
  $dob = 1;
  $gender = $form_state['values']['gender'];
  $minor_flag = $form_state['values']['minor_flag'];
  $primary_flag = $form_state['values']['primary_flag'];
  $secondary_flag = $form_state['values']['secondary_flag'];

  $contact_name = $form_state['values']['contact_name'];
  $contact_address1 = $form_state['values']['address1'];
  $contact_address2 = $form_state['values']['address2'];
  $contact_city = $form_state['values']['city'];
  $contact_state = $form_state['values']['state'];
  $contact_zip = $form_state['values']['zip'];
  $contact_phone = $form_state['values']['phone'];
  $contact_email = $form_state['values']['email'];
  $contact_fax = $form_state['values']['fax'];


  // set active database and insert patient and contact databases

  db_set_active ( 'rmsallergy' );

  $contact_key =  db_insert ( 'contact' )
    ->fields ( array (
      'contact_name' => $contact_name,
      'contact_address1' => $contact_address1,
      'contact_address2' => $contact_address2,
      'contact_city' => $contact_city,
      'contact_state' => $contact_state,
      'contact_zip' => $contact_zip,
      'contact_home_phone' => NULL,
      'contact_work_phone' => $contact_phone,
      'contact_mobile_phone' => NULL,
      'contact_email' => $contact_email,
      'contact_fax' => $contact_fax,
    ))
    ->execute();

  // update patient database
  $patient_key = db_insert ( 'patient' )
    ->fields ( array (
      'patient_name' => $patient_name,
      'patient_contact_key' => $contact_key,
      'patient_ssn' => $ssn,
      'patient_dob' => $dob,
      'patient_gender' => $gender,
      'patient_minor_flag' => $minor_flag,
      'patient_primary_flag' => $primary_flag,
      'patient_secondary_flag' => $secondary_flag,
    ))
    ->execute();

  db_set_active ();

  drupal_set_message ( t('The patient has been created.') );

  $form_state['rebuild'] = TRUE;
}


function rmsallergy_view_patient_update_submit ( $form, &$form_state )
{
  // first, get the data out of the form
  $patient_name = $form_state['values']['patient_name'];
  $ssn = $form_state['values']['ssn'];
  $dob = $form_state['values']['dob'];
  $dob = 1;
  $gender = $form_state['values']['gender'];
  $minor_flag = $form_state['values']['minor_flag'];
  $primary_flag = $form_state['values']['primary_flag'];
  $secondary_flag = $form_state['values']['secondary_flag'];

  $contact_name = $form_state['values']['contact_name'];
  $contact_address1 = $form_state['values']['address1'];
  $contact_address2 = $form_state['values']['address2'];
  $contact_city = $form_state['values']['city'];
  $contact_state = $form_state['values']['state'];
  $contact_zip = $form_state['values']['zip'];
  $contact_phone = $form_state['values']['phone'];
  $contact_email = $form_state['values']['email'];
  $contact_fax = $form_state['values']['fax'];

  // get the patient key from the table element

  $result = $form_state['values']['table'];

  $patient_key = NULL;
  foreach ( $result as $record ) {
    if ( $record > 0 ) {
      $patient_key = $record;
    }
  }

  // set active database and update patient and contact databases

  db_set_active ( 'rmsallergy' );

  $query = db_select ( 'patient', 'p' );

  $query 
    ->fields ( 'p', array ( 'patient_contact_key' ) )
    ->condition ( 'patient_key', $patient_key );

  $result = $query->execute();

  $record = $result->fetchAssoc();

  $contact_key = $record['patient_contact_key'];


  // update patient database
  $num_updated = db_update ( 'patient' )
    ->fields ( array (
      'patient_name' => $patient_name,
      'patient_contact_key' => $contact_key,
      'patient_ssn' => $ssn,
      'patient_dob' => 1,
      'patient_dob' => $dob,
      'patient_gender' => $gender,
      'patient_minor_flag' => $minor_flag,
      'patient_primary_flag' => $primary_flag,
      'patient_secondary_flag' => $secondary_flag,
    ))
    ->condition('patient_key', $patient_key )
    ->execute();


  $num_updated =  db_update ( 'contact' )
    ->fields ( array (
      'contact_name' => $contact_name,
      'contact_address1' => $contact_address1,
      'contact_address2' => $contact_address2,
      'contact_city' => $contact_city,
      'contact_state' => $contact_state,
      'contact_zip' => $contact_zip,
      'contact_work_phone' => $contact_phone,
      'contact_email' => $contact_email,
      'contact_fax' => $contact_fax,
    ))
    ->condition('contact_key', $contact_key)
    ->execute();

  db_set_active ();

  drupal_set_message ( t('The patient has been updated.') );

  $form_state['rebuild'] = TRUE;
}

