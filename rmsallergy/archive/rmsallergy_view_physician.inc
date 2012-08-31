<?php

/**
 * @file
 * RMS Allergy function file
 */

function rmsallergy_view_physician ( $form, &$form_state )
{

// build the table of practices

  $form['subtitle'] = array (
    '#type' => 'item',
    '#title' => t('Select a Physician (Select Only One):'),
  );


  db_set_active ( 'rmsallergy' );

  $query = db_select ( 'physician', 'p' );
  $query
    ->fields ( 'p', array ( 'physician_key',
                            'physician_name',
                            'physician_practice_key',
                            'physician_primary_contact_key' ))
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
  );


  // code for refresh button - when user selects refresh, the rest
  // of the form will be populated with practice information

  $form['refresh'] = array (
    '#type' => 'submit',
    '#value' => t('Refresh'),
    '#validate' => array ( 'rmsallergy_view_physician_validate' ),
    '#submit' => array ( 'rmsallergy_view_physician_refresh_submit' ),
  );



//
// set default values for the remainder of the form
//

  $physician_name = !empty ( $form_state['values']['physician_name'] ) ?
                             $form_state['values']['physician_name'] : '';

  $practice_table = !empty ( $form_state['values']['practice_table'] ) ?
                             $form_state['values']['practice_table'] : array();

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

  unset($form_state['input']['physician_name']);
  unset($form_state['input']['practice_table']);

  $form['physician_name'] = array (
    '#type' => 'textfield',
    '#title' => t('Physician Name'),
    '#size' => 50,
//    '#required' => TRUE,
    '#default_value' => $physician_name,
  );


  include ( "rmsallergy__create_practice_table.inc" );

  $form['practice'] = array (
    '#type' => 'fieldset',
    '#title' => t('Practice Association'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['practice']['practice_table'] = array (
    '#type' => 'tableselect',
    '#header' => $practice_table_header,
    '#options' => $practice_table_options,
    '#empty' => t('No Practices in Database'),
    '#default_value' => $practice_table,
  );




  $form['contact'] = array (
    '#type' => 'fieldset',
    '#title' => t('Primary Location Information'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
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



  $form['submit'] = array (
    '#type' => 'submit',
    '#value' => t('Update'),
  );

  return $form;
}






function rmsallergy_view_physician_validate ( $form, &$form_state )
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
    form_set_error ( 'View Physician', t("Please select a physician.") );
  } elseif ( $num_record > 1 ) { 
    form_set_error ( 'View Physician', t("Please select only one physician.") );
  }

  return $form;
}





function rmsallergy_view_physician_refresh_submit ( $form, &$form_state )
{
// the refresh routine will populate the values array with the data
// of the selected pratice

  // get the physician key from the table element

  $result = $form_state['values']['table'];

  $physician_key = NULL;
  foreach ( $result as $record ) {
    if ( $record > 0 ) {
      $physician_key = $record;
    }
  }

  // query the physician table to retrieve the information

  db_set_active ( 'rmsallergy' );

  $query = db_select ( 'physician', 'p' );
  $query
    ->fields ( 'p', array ( 'physician_key',
                            'physician_name',
                            'physician_practice_key',
                            'physician_primary_contact_key' ))
    ->condition ( 'physician_key', $physician_key );

  $result = $query->execute();

  $record = $result->fetchAssoc();

  db_set_active ();


  // set form value for physician structure

  form_set_value ( $form['physician_name'],
                   $record['physician_name'],
                   $form_state );

  $practice_key = $record['physician_practice_key'];

  $allkeys = array_keys ( $form_state['values']['practice_table'] );

  foreach ( $allkeys as $key ) {
    $form_state['values']['practice_table']["$key"] = 0;
  }

  $form_state['values']['practice_table']["$practice_key"] = $practice_key;


  // set form value for contact structure

  $contact_key = $record['physician_primary_contact_key'];

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



function rmsallergy_view_physician_submit ( $form, &$form_state )
{

  // first, get the data out of the form

  $physician_name = $form_state['values']['physician_name'];


  // get the physician practice key
  $allkeys = array_keys ( $form_state['values']['practice_table'] );
  $n=0;
  foreach ( $allkeys as $key ) {
    $value = $form_state['values']['practice_table']["$key"];
    if ( $value > 0 ) {
      $physician_practice_key = $value;
      $n = $n + 1;
    }
  }

  if ( $n < 1 )
  {
    form_set_error ( 'View Physician', t("Please select a practice"));
    $form_state['rebuild'] = TRUE;
    return;
  } elseif ( $n > 1 ) {
    form_set_error ( 'View Physician', t("Please select only one practice."));
    $form_state['rebuild'] = TRUE;
    return;
  }

  $contact_name = $form_state['values']['contact_name'];
  $contact_address1 = $form_state['values']['address1'];
  $contact_address2 = $form_state['values']['address2'];
  $contact_city = $form_state['values']['city'];
  $contact_state = $form_state['values']['state'];
  $contact_zip = $form_state['values']['zip'];
  $contact_phone = $form_state['values']['phone'];
  $contact_email = $form_state['values']['email'];
  $contact_fax = $form_state['values']['fax'];

  // second, get the physician key from the table element

  $result = $form_state['values']['table'];

  $physician_key = NULL;
  foreach ( $result as $record ) {
    if ( $record > 0 ) {
      $physician_key = $record;
    }
  }

  // third, set active database and update physician and contact databases

  db_set_active ( 'rmsallergy' );

  // update physician database
  $num_updated = db_update ( 'physician' )
    ->fields ( array (
      'physician_name' => $physician_name,
      'physician_practice_key' => $physician_practice_key,
    ))
    ->condition('physician_key', $physician_key )
    ->execute();

  $query = db_select ( 'physician', 'p' );

  $query 
    ->fields ( 'p', array ( 'physician_primary_contact_key' ) )
    ->condition ( 'physician_key', $physician_key );

  $result = $query->execute();

  $record = $result->fetchAssoc();

  $contact_key = $record['physician_primary_contact_key'];

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

  drupal_set_message ( t('The physician has been updated.') );

  $form_state['rebuild'] = TRUE;
}

