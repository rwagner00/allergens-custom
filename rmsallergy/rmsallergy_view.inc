<?php

/**
 * @file
 * RMS Allergy function file
 */

function rmsallergy_view_physician ( $form, &$form_state ) {


// query database to get list of physicians

// select physician to see details (check box with submit)

// display physician information




// Display add_physician page 2 if $form_state['page_num'] == 2

if ( !empty($form_state['page_num']) && $form_state['page_num'] == 2 ) {
  return rmsallergy_view_physician_page_2 ( $form, $form_state );
}



// otherwise build the first page

  $form = array ();

  $form['subtitle'] = array (
    '#type' => 'item',
    '#title' => t('Select a Physician (Select Only One):'),
  );

  db_set_active ( 'rmsallergy' );

  $query = db_select ( 'physician', 'p' );
  $query
    ->fields ( 'p', array ( 'physician_key',
                            'physician_name' ))
    ->orderBy ( 'physician_name', 'ASC' );

  $result = $query->execute();

  db_set_active ();

  $options = array ();
  foreach ( $result as $record ) {
    $options [ $record->physician_key ] = array (
      'physician_name' => $record->physician_name,
    );
  }

  $header = array (
    'physician_name' => t('Physician Name'),
  );

  $form['table'] = array (
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#empty' => t('No Physicians in Database'),
    '#default_value' => $table,
  );

  // code for next button

  $form['submit'] = array (
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  return $form;
}


function rmsallergy_view_physician_validate ( $form, &$form_state ) {
  $result = $form_state['values']['table'];

  $num_record=0;
  foreach ( $result as $record ) {
    if ( $record > 0 ) {
      $num_record = $num_record + 1;
    }
  }

  if ( $num_record < 1 )
  { 
    form_set_error ( 'View Physician', t("Please select a physician.") );
  } elseif ( $num_record > 1 ) { 
    form_set_error ( 'View Physician', t("Please select only one physician.") );
  }
}

function rmsallergy_add_physician_submit ( $form, &$form_state ) {


// look up primary location of practice and load into array

  // get physician_key from table
  $result = $form_state['values']['table'];

  $physician_key=NULL;
  $num_record=0;
  foreach ( $result as $record ) {
    if ( $record > 0 ) {
      $physician_key = $record;
    }
  }

  drupal_set_message(print_r($physician_key,TRUE));

  // get contact_key from database lookup
  db_set_active ( 'rmsallergy' );

  $query = db_select ( 'practice2contact', 'p2c' );
  $query
    ->fields ( 'p2c', array ( 'contact_key' ) )
    ->condition ( 'practice_key', $practice_key );

  $result = $query->execute();

  $nrows = $result->rowCount ();
  if ( $nrows != 1 ) {
    form_set_error ( 'Add Physician', t('Query returned bad contact key') );
  } 

  $contact_key = $result->fetchField ( 0 );

//  drupal_set_message ( print_r($contact_key,TRUE));
    
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

  $nrows = $result->rowCount ();
  if ( $nrows != 1 ) {
    form_set_error ( 'Add Physician', t('Query returned bad contact record') );
  } 

  $record = $result->fetchAssoc ();

  $name = $record['contact_name'];
  $address1 = $record['contact_address1'];
  $address2 = $record['contact_address2'];
  $city = $record['contact_city'];
  $state = $record['contact_state'];
  $zip = $record['contact_zip'];
  $phone = $record['contact_work_phone'];
  $email = $record['contact_email'];
  $fax = $record['contact_fax'];

  db_set_active ();


// build the form

  $form['contact'] = array (
    '#type' => 'fieldset',
    '#title' => t('Primary Location Information'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['contact']['name'] = array (
    '#type' => 'textfield',
    '#title' => t('Location Description'),
    '#size' => 50,
    '#required' => TRUE,
    '#default_value' => $name,
  );

  $form['contact']['address1'] = array (
    '#type' => 'textfield',
    '#title' => t('Address'),
    '#size' => 50,
    '#required' => TRUE,
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
    '#required' => TRUE,
    '#default_value' => $city,
  );

  $form['contact']['state'] = array (
    '#type' => 'textfield',
    '#title' => t('State'),
    '#size' => 50,
    '#required' => TRUE,
    '#default_value' => $state,
  );

  $form['contact']['zip'] = array (
    '#type' => 'textfield',
    '#title' => t('Zip'),
    '#size' => 50,
    '#required' => TRUE,
    '#default_value' => $zip,
  );

  $form['contact']['phone'] = array (
    '#type' => 'textfield',
    '#title' => t('Main Phone'),
    '#size' => 50,
    '#required' => TRUE,
    '#default_value' => $phone,
  );

  $form['contact']['email'] = array (
    '#type' => 'textfield',
    '#title' => t('Email'),
    '#size' => 50,
    '#required' => TRUE,
    '#default_value' => $email,
  );

  $form['contact']['fax'] = array (
    '#type' => 'textfield',
    '#title' => t('Fax'),
    '#size' => 50,
    '#default_value' => $fax,
    '#required' => TRUE,
  );

  $form['submit'] = array (
    '#type' => 'submit',
    '#value' => t('Submit'),
    '#submit' => array ( 'rmsallergy_add_physician_page_2_submit' ),
    '#validate' => array ( 'rmsallergy_add_physician_page_2_validate' ),
  );

  $form['back'] = array (
    '#type' => 'submit',
    '#value' => t('<< Back'),
    '#submit' => array ( 'rmsallergy_add_physician_page_2_back' ),
    '#limit_validiation_errors' => array (),
  );

  return $form;
}

function rmsallergy_add_physician_page_2_back ( $form, &$form_state ) {
  $form_state['page_values'][2] = $form_state['values'];
  $form_state['values'] = $form_state['page_values'][1];
  $form_state['page_num'] = 1;
  $form_state['rebuild'] = TRUE;
//  drupal_set_message ( print_r($form_state['page_values'][2],TRUE) );
}

function rmsallergy_add_physician_page_2_validate ( $form, &$form_state ) {
}

function rmsallergy_add_physician_page_2_submit ( $form, &$form_state ) {

// get the data out of the form state array

  $contact_name = $form_state['values']['name'];
  $contact_address1 = $form_state['values']['address1'];
  $contact_address2 = $form_state['values']['address2'];
  $contact_city = $form_state['values']['city'];
  $contact_state = $form_state['values']['state'];
  $contact_zip = $form_state['values']['zip'];
  $contact_phone = $form_state['values']['phone'];
  $contact_email = $form_state['values']['email'];
  $contact_fax = $form_state['values']['fax'];

  $form_state['values'] = $form_state['page_values'][1];

  $physician_name = $form_state['page_values'][1]['physician_name'];

  // get practice_key from table
  $result = $form_state['page_values'][1]['table'];

  $practice_key=NULL;
  foreach ( $result as $record ) {
    if ( $record > 0 ) {
      $practice_key = $record;
    }
  }

// second, set active database and populate db_insert statement

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

  $physician_key = db_insert ( 'physician' )
    ->fields ( array (
      'physician_name' => $physician_name,
      'physician_practice_key' => $practice_key,
      'physician_primary_contact_key' => $contact_key,
    ))
    ->execute();

  $practice2physician = db_insert ( 'practice2physician' )
    ->fields ( array (
      'practice_key' => $practice_key,
      'physician_key' => $physician_key,
    ))
    ->execute();

  db_set_active ();

  drupal_set_message ( t('The physician has been added.') );
}


