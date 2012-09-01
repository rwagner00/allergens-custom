<?php

/**
 * @file
 * RMS Allergy function file
 */


function rmsallergy_administration_form () {
  $form = array ();

  $form['subtitle'] = array (
    '#type' => 'item',
    '#title' => t('Select from the Following Options:'),
  );

  $form['link1'] = array (
    '#type' => 'item',
    '#title' => t('<a href="?q=rmsadmin/add_practice">Add New Practice</a>'),
  );

  $form['link2'] = array (
    '#type' => 'item',
    '#title' => t('<a href="?q=rmsadmin/add_physician">Add New Physician</a>'),
  );

  $form['link3'] = array (
    '#type' => 'item',
    '#title' => t('<a href="?q=rmsadmin/view_practice">View Practice</a>'),
  );

  $form['link4'] = array (
    '#type' => 'item',
    '#title' => t('<a href="?q=rmsadmin/view_physician">View Physician</a>'),
  );

  return $form;
}


function rmsallergy_provider_form () {
  $form = array ();

  $form['subtitle'] = array (
    '#type' => 'item',
    '#title' => t('Select from the Following Options:'),
  );

  $form['link1'] = array (
    '#type' => 'item',
    '#title' => t('<a href="?q=provider/view_patient">View Patient Information</a>'),
  );

  return $form;
}



/////////////////////////////////////////////////////////////////
// Add Practice
/////////////////////////////////////////////////////////////////

function rmsallergy_add_practice ( $form, &$form_state ) {
  $form = array ();

  $form['PracticeName'] = array (
    '#type' => 'textfield',
    '#title' => t('Practice Name'),
    '#size' => 50,
    '#required' => TRUE,
  );

  $form['Specialty'] = array (
    '#type' => 'radios',
    '#title' => t('Specify Practice Specialty'),
    '#options' => array (
      '0' => t('Primary Care'),
      '1' => t('Allergist'),
      '2' => t('ENT'),
  ));

  $form['ReferringFlag'] = array (
    '#type' => 'checkbox',
    '#title' => t('Check If This Pratice Refers Patients')
  );

  $form['ReferredFlag'] = array (
    '#type' => 'checkbox',
    '#title' => t('Check If This Pratice Receives Patients')
  );

  $form['contact'] = array (
    '#type' => 'fieldset',
    '#title' => t('Primary Location Information'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE
  );

  $form['contact']['Name'] = array (
    '#type' => 'textfield',
    '#title' => t('Location Description'),
    '#size' => 50,
    '#required' => TRUE,
  );

  $form['contact']['Address1'] = array (
    '#type' => 'textfield',
    '#title' => t('Address'),
    '#size' => 50,
    '#required' => TRUE,
  );

  $form['contact']['Address2'] = array (
    '#type' => 'textfield',
    '#title' => t(''),
    '#size' => 50,
  );

  $form['contact']['City'] = array (
    '#type' => 'textfield',
    '#title' => t('City'),
    '#size' => 50,
    '#required' => TRUE,
  );

  $form['contact']['State'] = array (
    '#type' => 'textfield',
    '#title' => t('State'),
    '#size' => 50,
    '#required' => TRUE,
  );

  $form['contact']['Zip'] = array (
    '#type' => 'textfield',
    '#title' => t('Zip'),
    '#size' => 50,
    '#required' => TRUE,
  );

  $form['contact']['Phone'] = array (
    '#type' => 'textfield',
    '#title' => t('Main Phone'),
    '#size' => 50,
    '#required' => TRUE,
  );

  $form['contact']['Email'] = array (
    '#type' => 'textfield',
    '#title' => t('Email'),
    '#size' => 50,
    '#required' => TRUE,
  );

  $form['contact']['Fax'] = array (
    '#type' => 'textfield',
    '#title' => t('Fax'),
    '#size' => 50,
    '#required' => TRUE,
  );

  $form['submit'] = array (
    '#type' => 'submit',
    '#value' => t('Submit')
  );

/*  $form['cancel'] = array (
    '#type' => 'button',
    '#value' => t('Cancel'),
    '#limit_validation_errors' => array()
  );
*/

  return $form;
}

//////////////////////////////////////////////////
// * to do the cancellation properly, need to put in hook_form_alter
//function rmsallergy_cancel_button_submit ( $form, &$form_state ) {
//  return drupal_set_message ( t('Enter cancel button submit' ) );
//}
//////////////////////////////////////////////////

function rmsallergy_add_practice_validate ( $form, &$form_state ) {
  $practice_name = $form_state['values']['PracticeName'];
  $fax = $form_state['values']['Fax'];
//////////////////////////////////////////////////
// MUST INCLUDE VALIDATE CODE
//////////////////////////////////////////////////
//  form_set_error ( 'PracticeName', t("Bad value for practice name: $practice_name") );
}

function rmsallergy_add_practice_submit ( $form, &$form_state ) {

// first, get the data out of the form state array

  $practice_name = $form_state['values']['PracticeName'];
  $specialty = $form_state['values']['Specialty'];
  $referring_flag = $form_state['values']['ReferringFlag'];
  $referred_flag = $form_state['values']['ReferredFlag'];
  $contact_name = $form_state['values']['Name'];
  $contact_address1 = $form_state['values']['Address1'];
  $contact_address2 = $form_state['values']['Address2'];
  $contact_city = $form_state['values']['City'];
  $contact_state = $form_state['values']['State'];
  $contact_zip = $form_state['values']['Zip'];
  $contact_phone = $form_state['values']['Phone'];
  $contact_email = $form_state['values']['Email'];
  $contact_fax = $form_state['values']['Fax'];

  if ( $specialty == '0' ) { $specialty = 'Primary'; }
  if ( $specialty == '1' ) { $specialty = 'Allergist'; }
  if ( $specialty == '2' ) { $specialty = 'ENT'; }

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

  $practice_key = db_insert ( 'practice' )
    ->fields ( array (
      'practice_name' => $practice_name,
      'practice_specialty' => $specialty,
      'practice_referring_flag' => $referring_flag,
      'practice_referred_flag' => $referred_flag,
      'practice_primary_contact_key' => $contact_key,
    ))
    ->execute();

  $practice2contact_key = db_insert ( 'practice2contact' )
    ->fields ( array (
      'practice_key' => $practice_key,
      'contact_key' => $contact_key,
    ))
    ->execute();

  db_set_active ();

  drupal_set_message ( t('The practice has been created.') );
}


/////////////////////////////////////////////////////////////////
// Add Physician
/////////////////////////////////////////////////////////////////

function rmsallergy_add_physician ( $form, &$form_state ) {

// Display add_physician page 2 if $form_state['page_num'] == 2

if ( !empty($form_state['page_num']) && $form_state['page_num'] == 2 ) {
  return rmsallergy_add_physician_page_2 ( $form, $form_state );
}

// load default values from form_state['values'], if exists

  $physician_name = !empty ( $form_state['values']['physician_name'] ) ?
                             $form_state['values']['physician_name'] : '';

  $table = !empty ( $form_state['values']['table'] ) ?
                    $form_state['values']['table'] : array();


// otherwise build the first page

  $form = array ();

  $form['physician_name'] = array (
    '#type' => 'textfield',
    '#title' => t('Physician Name'),
    '#size' => 50,
//    '#required' => TRUE,
    '#default_value' => $physician_name,
  );

  $form['subtitle'] = array (
    '#type' => 'item',
    '#title' => t('Select a Practice For This Physician (Select Only One):'),
  );

  db_set_active ( 'rmsallergy' );

  $query = db_select ( 'practice', 'p' );
  $query
    ->fields ( 'p', array ( 'practice_key',
                            'practice_name',
                            'practice_specialty' ))
    ->orderBy ( 'practice_name', 'ASC' );

  $result = $query->execute();

  db_set_active ();

  $options = array ();
  foreach ( $result as $record ) {
    $options [ $record->practice_key ] = array (
      'practice_name' => $record->practice_name,
      'practice_specialty' => $record->practice_specialty,
    );
  }

  $header = array (
    'practice_name' => t('Practice Name'),
    'practice_specialty' => t('Specialty'),
  );

  $form['table'] = array (
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#empty' => t('No Practicies in Database'),
    '#description' => t('Select which practice'),
    '#default_value' => $table,
  );

  // code for next button

  $form['next'] = array (
    '#type' => 'submit',
    '#value' => t('Next >>'),
    '#submit' => array('rmsallergy_add_physician_next_submit'),
    '#validate' => array('rmsallergy_add_physician_next_validate'),
  );

  return $form;
}


function rmsallergy_add_physician_next_validate ( $form, &$form_state ) {

  $result = $form_state['values']['table'];

  $num_record=0;
  foreach ( $result as $record ) {
    if ( $record > 0 ) {
      $num_record = $num_record + 1;
    }
  }

  if ( $num_record < 1 )
  { 
    form_set_error ( 'Add Physician', t("Please select a practice.") );
  } elseif ( $num_record > 1 ) { 
    form_set_error ( 'Add Physician', t("Please select only one practice.") );
  }
}

function rmsallergy_add_physician_next_submit ( $form, &$form_state ) {
  // Valures are saved for each page to carry to subsequent
  // pages in the form and to tell FAPI to rebuild the form
  $form_state['page_values'][1] = $form_state['values'];

  if ( !empty($form_state['page_values'][2] )) {
    $form_state['values'] = $form_state['page_values'][2];
  }

  $form_state['page_num'] = 2;
  $form_state['rebuild'] = TRUE;

//  drupal_set_message ( print_r($form_state['values'],TRUE) );
}




/////////////////////////////////////////////////////////
// the below will be the form data for the second screen
/////////////////////////////////////////////////////////

function rmsallergy_add_physician_page_2 ( $form, &$form_state ) {

// load default values from form_state['values'], if exists

  $name = !empty ( $form_state['values']['name'] ) ?
                   $form_state['values']['name'] : '';

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


// look up primary location of practice and load into array

  // get practice_key from table
  $result = $form_state['page_values'][1]['table'];

  $practice_key=NULL;
  $num_record=0;
  foreach ( $result as $record ) {
    if ( $record > 0 ) {
      $practice_key = $record;
    }
  }

//  drupal_set_message(print_r($practice_key,TRUE));

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


