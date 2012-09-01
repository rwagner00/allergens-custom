<?php

/**
 * @file
 * RMS Allergy function file
 */

function rmsallergy_update_patient ( $form, &$form_state )
{
// get practice_key from current user
  global $user;
  $account = user_load ( $user->uid );
  $practice_key = field_get_items ( 'user', $account, 'field_practice_key' );
  $practice_key = $practice_key[0]['value'];


// query the database for patient records

  db_set_active ( 'rmsallergy' );
  $query = db_select ( 'patient', 'p' );
  $query
    ->fields ( 'p', array ( 'patient_key',
                            'patient_first_name',
                            'patient_middle_name',
                            'patient_last_name',
                          ))
    ->orderBy ( 'patient_last_name', 'ASC' )
    ->condition ( 'practice_key', $practice_key );

  $result = $query->execute();

  db_set_active ();

// build arrays to show patient table

  $options = array ();
  foreach ( $result as $record ) {

    $options [ $record->patient_key ] = array (
      'patient_last_name' => $record->patient_last_name,
      'patient_first_name' => $record->patient_first_name,
      'patient_middle_name' => $record->patient_middle_name,
    );
  }

  $header = array (
    'patient_last_name' => t('Last Name'),
    'patient_first_name' => t('First Name'),
    'patient_middle_name' => t('Middle Initial'),
  );


// build form

  $form['subtitle'] = array (
    '#type' => 'item',
    '#title' => t('Select a Patient to Update:'),
  );

  $form['table'] = array (
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#empty' => t('No Patients in Database'),
    '#multiple' => FALSE,
  );


  // code for refresh button - when user selects refresh, the rest
  // of the form will be populated with patient information

  $form['refresh'] = array (
    '#type' => 'submit',
    '#value' => t('Open'),
    '#validate' => array ( 'rmsallergy_update_patient_validate' ),
    '#submit' => array ( 'rmsallergy_update_patient_refresh_submit' ),
  );



// set default values for the remainder of the form

  $first_name = !empty ( $form_state['values']['first_name'] ) ?
                         $form_state['values']['first_name'] : '';
  $middle_name = !empty ( $form_state['values']['middle_name'] ) ?
                          $form_state['values']['middle_name'] : '';
  $last_name = !empty ( $form_state['values']['last_name'] ) ?
                        $form_state['values']['last_name'] : '';
  $ssn1 = !empty ( $form_state['values']['ssn1'] ) ?
                   $form_state['values']['ssn1'] : '';
  $ssn2 = !empty ( $form_state['values']['ssn2'] ) ?
                   $form_state['values']['ssn2'] : '';
  $ssn3 = !empty ( $form_state['values']['ssn3'] ) ?
                   $form_state['values']['ssn3'] : '';
  $dob_month = !empty ( $form_state['values']['dob_month'] ) ?
                        $form_state['values']['dob_month'] : '';
  $dob_day = !empty ( $form_state['values']['dob_day'] ) ?
                      $form_state['values']['dob_day'] : '';
  $dob_year = !empty ( $form_state['values']['dob_year'] ) ?
                       $form_state['values']['dob_year'] : '';
  $gender = !empty ( $form_state['values']['gender'] ) ?
                     $form_state['values']['gender'] : '';
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
  $home_phone = !empty ( $form_state['values']['home_phone'] ) ?
                         $form_state['values']['home_phone'] : '';
  $work_phone = !empty ( $form_state['values']['work_phone'] ) ?
                         $form_state['values']['work_phone'] : '';
  $mobile_phone = !empty ( $form_state['values']['mobile_phone'] ) ?
                           $form_state['values']['mobile_phone'] : '';
  $email = !empty ( $form_state['values']['email'] ) ?
                    $form_state['values']['email'] : '';
  $fax = !empty ( $form_state['values']['fax'] ) ?
                  $form_state['values']['fax'] : '';

  $minor_flag = !empty ( $form_state['values']['minor_flag'] ) ?
                         $form_state['values']['minor_flag'] : '';
  $gname = !empty ( $form_state['values']['gname'] ) ?
                    $form_state['values']['gname'] : '';
  $gaddress1 = !empty ( $form_state['values']['gaddress1'] ) ?
                        $form_state['values']['gaddress1'] : '';
  $gaddress2 = !empty ( $form_state['values']['gaddress2'] ) ?
                        $form_state['values']['gaddress2'] : '';
  $gcity = !empty ( $form_state['values']['gcity'] ) ?
                    $form_state['values']['gcity'] : '';
  $gstate = !empty ( $form_state['values']['gstate'] ) ?
                     $form_state['values']['gstate'] : '';
  $gzip = !empty ( $form_state['values']['gzip'] ) ?
                   $form_state['values']['gzip'] : '';
  $ghome_phone = !empty ( $form_state['values']['ghome_phone'] ) ?
                          $form_state['values']['ghome_phone'] : '';
  $gwork_phone = !empty ( $form_state['values']['gwork_phone'] ) ?
                          $form_state['values']['gwork_phone'] : '';
  $gmobile_phone = !empty ( $form_state['values']['gmobile_phone'] ) ?
                            $form_state['values']['gmobile_phone'] : '';
  $gemail = !empty ( $form_state['values']['gemail'] ) ?
                     $form_state['values']['gemail'] : '';
  $gfax = !empty ( $form_state['values']['gfax'] ) ?
                   $form_state['values']['gfax'] : '';



// unset prior values so the form rebuild correctly

  unset($form_state['input']['first_name']);
  unset($form_state['input']['middle_name']);
  unset($form_state['input']['last_name']);
  unset($form_state['input']['ssn1']);
  unset($form_state['input']['ssn2']);
  unset($form_state['input']['ssn3']);
  unset($form_state['input']['dob_month']);
  unset($form_state['input']['dob_day']);
  unset($form_state['input']['dob_year']);
  unset($form_state['input']['gender']);
  unset($form_state['input']['address1']);
  unset($form_state['input']['address2']);
  unset($form_state['input']['city']);
  unset($form_state['input']['state']);
  unset($form_state['input']['zip']);
  unset($form_state['input']['home_phone']);
  unset($form_state['input']['work_phone']);
  unset($form_state['input']['mobile_phone']);
  unset($form_state['input']['email']);
  unset($form_state['input']['fax']);

  unset($form_state['input']['minor_flag']);
  unset($form_state['input']['gname']);
  unset($form_state['input']['gaddress1']);
  unset($form_state['input']['gaddress2']);
  unset($form_state['input']['gcity']);
  unset($form_state['input']['gstate']);
  unset($form_state['input']['gzip']);
  unset($form_state['input']['ghome_phone']);
  unset($form_state['input']['gwork_phone']);
  unset($form_state['input']['gmobile_phone']);
  unset($form_state['input']['gemail']);
  unset($form_state['input']['gfax']);


// create form

  $form['p'] = array (
    '#type' => 'fieldset',
    '#title' => t('Patient Information'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['p']['first_name'] = array (
    '#type' => 'textfield',
    '#title' => t('First Name'),
    '#size' => 64,
   '#default_value' => $first_name,
  );

  $form['p']['middle_name'] = array (
    '#type' => 'textfield',
    '#title' => t('Middle Initial'),
    '#size' => 8,
   '#default_value' => $middle_name,
  );

  $form['p']['last_name'] = array (
    '#type' => 'textfield',
    '#title' => t('Last Name'),
    '#size' => 64,
   '#default_value' => $last_name,
  );

  $form['p']['header_ssn'] = array (
    '#type' => 'item',
    '#title' => t('Social Security Number'),
    '#suffix' => "<table>",
  );

  $form['p']['ssn1'] = array (
    '#type' => 'textfield',
    '#size' => 3,
    '#default_value' => $ssn1,
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['p']['ssn2'] = array (
    '#type' => 'textfield',
    '#size' => 2,
    '#default_value' => $ssn2,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p']['ssn3'] = array (
    '#type' => 'textfield',
    '#size' => 4,
    '#default_value' => $ssn3,
    '#prefix' => '<td>',
    '#suffix' => '</td></tr></table>',
  );

  $form['p']['header_dob'] = array (
    '#type' => 'item',
    '#title' => t('Date of Birth'),
    '#suffix' => "<table>",
  );

  $form['p']['dob_month'] = array (
    '#type' => 'textfield',
    '#title' => t('Month (mm)'),
    '#size' => 2,
   '#default_value' => $dob_month,
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['p']['dob_day'] = array (
    '#type' => 'textfield',
    '#title' => t('Day (dd)'),
    '#size' => 2,
   '#default_value' => $dob_day,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p']['dob_year'] = array (
    '#type' => 'textfield',
    '#title' => t('Year (yyyy)'),
    '#size' => 4,
   '#default_value' => $dob_year,
    '#prefix' => '<td>',
    '#suffix' => '</td></tr></table>',
  );

  $form['p']['gender'] = array (
    '#type' => 'textfield',
    '#title' => t('Gender'),
    '#size' => 8,
   '#default_value' => $gender,
  );

  $form['p']['address1'] = array (
    '#type' => 'textfield',
    '#title' => t('Address'),
    '#size' => 64,
//    '#required' => TRUE,
    '#default_value' => $address1,
  );

  $form['p']['address2'] = array (
    '#type' => 'textfield',
    '#title' => t(''),
    '#size' => 64,
    '#default_value' => $address2,
  );

  $form['p']['city'] = array (
    '#type' => 'textfield',
    '#title' => t('City'),
    '#size' => 32,
//    '#required' => TRUE,
    '#default_value' => $city,
  );

  $form['p']['state'] = array (
    '#type' => 'textfield',
    '#title' => t('State'),
    '#size' => 32,
//    '#required' => TRUE,
    '#default_value' => $state,
  );

  $form['p']['zip'] = array (
    '#type' => 'textfield',
    '#title' => t('Zip'),
    '#size' => 16,
//    '#required' => TRUE,
    '#default_value' => $zip,
  );

  $form['p']['home_phone'] = array (
    '#type' => 'textfield',
    '#title' => t('Home Phone'),
    '#size' => 16,
//    '#required' => TRUE,
    '#default_value' => $home_phone,
  );

  $form['p']['work_phone'] = array (
    '#type' => 'textfield',
    '#title' => t('Work Phone'),
    '#size' => 16,
//    '#required' => TRUE,
    '#default_value' => $work_phone,
  );

  $form['p']['mobile_phone'] = array (
    '#type' => 'textfield',
    '#title' => t('Mobile Phone'),
    '#size' => 16,
//    '#required' => TRUE,
    '#default_value' => $mobile_phone,
  );

  $form['p']['email'] = array (
    '#type' => 'textfield',
    '#title' => t('Email'),
    '#size' => 16,
//    '#required' => TRUE,
    '#default_value' => $email,
  );

  $form['p']['fax'] = array (
    '#type' => 'textfield',
    '#title' => t('Fax'),
    '#size' => 16,
//    '#required' => TRUE,
    '#default_value' => $fax,
  );


  $form['g'] = array (
    '#type' => 'fieldset',
    '#title' => t('Guardian Information (if applicable)'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['g']['minor_flag'] = array (
    '#type' => 'checkbox',
    '#title' => t('Check if patient is a minor.'),
    '#default_value' => $minor_flag,
  );

  $form['g']['gname'] = array (
    '#type' => 'textfield',
    '#title' => t('Guardian Name'),
    '#size' => 64,
    '#default_value' => $gname,
  );

  $form['g']['gaddress1'] = array (
    '#type' => 'textfield',
    '#title' => t('Guardian Address'),
    '#size' => 64,
    '#default_value' => $gaddress1,
  );

  $form['g']['gaddress2'] = array (
    '#type' => 'textfield',
    '#title' => t(''),
    '#size' => 64,
    '#default_value' => $gaddress2,
  );

  $form['g']['gcity'] = array (
    '#type' => 'textfield',
    '#title' => t('City'),
    '#size' => 32,
    '#default_value' => $gcity,
  );

  $form['g']['gstate'] = array (
    '#type' => 'textfield',
    '#title' => t('State'),
    '#size' => 32,
    '#default_value' => $gstate,
  );

  $form['g']['gzip'] = array (
    '#type' => 'textfield',
    '#title' => t('Zip'),
    '#size' => 16,
    '#default_value' => $gzip,
  );

  $form['g']['ghome_phone'] = array (
    '#type' => 'textfield',
    '#title' => t('Home Phone'),
    '#size' => 16,
    '#default_value' => $ghome_phone,
  );

  $form['g']['gwork_phone'] = array (
    '#type' => 'textfield',
    '#title' => t('Work Phone'),
    '#size' => 16,
    '#default_value' => $gwork_phone,
  );

  $form['g']['gmobile_phone'] = array (
    '#type' => 'textfield',
    '#title' => t('Mobile Phone'),
    '#size' => 16,
    '#default_value' => $gmobile_phone,
  );

  $form['g']['gemail'] = array (
    '#type' => 'textfield',
    '#title' => t('Email'),
    '#size' => 16,
    '#default_value' => $gemail,
  );

  $form['g']['gfax'] = array (
    '#type' => 'textfield',
    '#title' => t('Fax'),
    '#size' => 16,
    '#default_value' => $gfax,
  );



// build the edit fields of the form


  $form['submit'] = array (
    '#type' => 'submit',
    '#value' => t('Update'),
  );

  return $form;
}


function rmsallergy_update_patient_validate ( $form, &$form_state )
{
  $patient_key = $form_state['values']['table'];

  if ( empty ( $patient_key ) ) { 
    form_set_error ( 'Update Patient', t("Please select a patient.") );
  }

  return $form;
}

function rmsallergy_update_patient_refresh_submit ( $form, &$form_state )
{
// the refresh routine will populate the values array with the data
// of the selected pratice

  // get the practice key from the table element

  $patient_key = $form_state['values']['table'];


  // query the practice table to retrieve the information

  db_set_active ( 'rmsallergy' );

  $query = db_select ( 'patient', 'p' );
  $query
    ->fields ( 'p', array (
      'patient_first_name',
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
      'guardian_fax' ))
    ->condition ( 'patient_key', $patient_key );

  $result = $query->execute();

  db_set_active ();

  $record = $result->fetchAssoc();


  form_set_value ( $form['p']['first_name'], $record['patient_first_name'], $form_state );
  form_set_value ( $form['p']['middle_name'], $record['patient_middle_name'], $form_state );
  form_set_value ( $form['p']['last_name'], $record['patient_last_name'], $form_state );
  form_set_value ( $form['p']['ssn1'], $record['patient_ssn1'], $form_state );
  form_set_value ( $form['p']['ssn2'], $record['patient_ssn2'], $form_state );
  form_set_value ( $form['p']['ssn3'], $record['patient_ssn3'], $form_state );
  form_set_value ( $form['p']['dob_month'], $record['patient_dob_month'], $form_state );
  form_set_value ( $form['p']['dob_day'], $record['patient_dob_day'], $form_state );
  form_set_value ( $form['p']['dob_year'], $record['patient_dob_year'], $form_state );
  form_set_value ( $form['p']['gender'], $record['patient_gender'], $form_state );
  form_set_value ( $form['p']['address1'], $record['patient_address1'], $form_state );
  form_set_value ( $form['p']['address2'], $record['patient_address2'], $form_state );
  form_set_value ( $form['p']['city'], $record['patient_city'], $form_state );
  form_set_value ( $form['p']['state'], $record['patient_state'], $form_state );
  form_set_value ( $form['p']['zip'], $record['patient_zip'], $form_state );
  form_set_value ( $form['p']['home_phone'], $record['patient_home_phone'], $form_state );
  form_set_value ( $form['p']['work_phone'], $record['patient_work_phone'], $form_state );
  form_set_value ( $form['p']['mobile_phone'], $record['patient_mobile_phone'], $form_state );
  form_set_value ( $form['p']['email'], $record['patient_email'], $form_state );
  form_set_value ( $form['p']['fax'], $record['patient_fax'], $form_state );

  form_set_value ( $form['g']['minor_flag'], $record['minor_flag'], $form_state );
  form_set_value ( $form['g']['gname'], $record['guardian_name'], $form_state );
  form_set_value ( $form['g']['gaddress1'], $record['guardian_address1'], $form_state );
  form_set_value ( $form['g']['gaddress2'], $record['guardian_address2'], $form_state );
  form_set_value ( $form['g']['gcity'], $record['guardian_city'], $form_state );
  form_set_value ( $form['g']['gstate'], $record['guardian_state'], $form_state );
  form_set_value ( $form['g']['gzip'], $record['guardian_zip'], $form_state );
  form_set_value ( $form['g']['ghome_phone'], $record['guardian_home_phone'], $form_state );
  form_set_value ( $form['g']['gwork_phone'], $record['guardian_work_phone'], $form_state );
  form_set_value ( $form['g']['gmobile_phone'], $record['guardian_mobile_phone'], $form_state );
  form_set_value ( $form['g']['gemail'], $record['guardian_email'], $form_state );
  form_set_value ( $form['g']['gfax'], $record['guardian_fax'], $form_state );

  $form_state['rebuild'] = TRUE;
}



function rmsallergy_update_patient_submit ( $form, &$form_state )
{

// get the patient key from the table

  $patient_key = $form_state['values']['table'];


// get the data out of the form

  $patient_first_name   = $form_state['values']['first_name'];
  $patient_middle_name  = $form_state['values']['middle_name'];
  $patient_last_name    = $form_state['values']['last_name'];
  $patient_ssn1         = $form_state['values']['ssn1'];
  $patient_ssn2         = $form_state['values']['ssn2'];
  $patient_ssn3         = $form_state['values']['ssn3'];
  $patient_dob_month    = $form_state['values']['dob_month'];
  $patient_dob_day      = $form_state['values']['dob_day'];
  $patient_dob_year     = $form_state['values']['dob_year'];
  $patient_gender       = $form_state['values']['gender'];
  $patient_address1     = $form_state['values']['address1'];
  $patient_address2     = $form_state['values']['address2'];
  $patient_city         = $form_state['values']['city'];
  $patient_state        = $form_state['values']['state'];
  $patient_zip          = $form_state['values']['zip'];
  $patient_home_phone   = $form_state['values']['home_phone'];
  $patient_work_phone   = $form_state['values']['work_phone'];
  $patient_mobile_phone = $form_state['values']['mobile_phone'];
  $patient_email        = $form_state['values']['email'];
  $patient_fax          = $form_state['values']['fax'];

  $minor_flag            = $form_state['values']['minor_flag'];
  $guardian_name         = $form_state['values']['gname'];
  $guardian_address1     = $form_state['values']['gaddress1'];
  $guardian_address2     = $form_state['values']['gaddress2'];
  $guardian_city         = $form_state['values']['gcity'];
  $guardian_state        = $form_state['values']['gstate'];
  $guardian_zip          = $form_state['values']['gzip'];
  $guardian_home_phone   = $form_state['values']['ghome_phone'];
  $guardian_work_phone   = $form_state['values']['gwork_phone'];
  $guardian_mobile_phone = $form_state['values']['gmobile_phone'];
  $guardian_email        = $form_state['values']['gemail'];
  $guardian_fax          = $form_state['values']['gfax'];


  // set active database and update practice and contact databases

  db_set_active ( 'rmsallergy' );

  $num_updated = db_update ( 'patient' )
    ->fields ( array (
      'patient_first_name' => $patient_first_name,
      'patient_middle_name' => $patient_middle_name,
      'patient_last_name' => $patient_last_name,
      'patient_ssn1' => $patient_ssn1,
      'patient_ssn2' => $patient_ssn2,
      'patient_ssn3' => $patient_ssn3,
      'patient_dob_month' => $patient_dob_month,
      'patient_dob_day' => $patient_dob_day,
      'patient_dob_year' => $patient_dob_year,
      'patient_gender' => $patient_gender,
      'patient_address1' => $patient_address1,
      'patient_address2' => $patient_address2,
      'patient_city' => $patient_city,
      'patient_state' => $patient_state,
      'patient_zip' => $patient_zip,
      'patient_home_phone' => $patient_home_phone,
      'patient_work_phone' => $patient_work_phone,
      'patient_mobile_phone' => $patient_mobile_phone,
      'patient_email' => $patient_email,
      'patient_fax' => $patient_fax,
      'minor_flag' => $minor_flag,
      'guardian_name' => $guardian_name,
      'guardian_address1' => $guardian_address1,
      'guardian_address2' => $guardian_address2,
      'guardian_city' => $guardian_city,
      'guardian_state' => $guardian_state,
      'guardian_zip' => $guardian_zip,
      'guardian_home_phone' => $guardian_home_phone,
      'guardian_work_phone' => $guardian_work_phone,
      'guardian_mobile_phone' => $guardian_mobile_phone,
      'guardian_email' => $guardian_email,
      'guardian_fax' => $guardian_fax,
    ))
    ->condition('patient_key', $patient_key )
    ->execute();

  db_set_active ();

  drupal_set_message ( t('The patient has been updated.') );

  $form_state['rebuild'] = TRUE;
}

