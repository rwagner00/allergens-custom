<?php

/**
 * @file
 * RMS Allergy function file
 */

function rmsallergy_update_testctr ( $form, &$form_state )
{

// build the table of testctrs

  $form['subtitle'] = array (
    '#type' => 'item',
    '#title' => t('Select a Testing Center to Update (Select Only One):'),
  );


  db_set_active ( 'rmsallergy' );

  $query = db_select ( 'testctr', 'p' );
  $query
    ->fields ( 'p', array ( 'testctr_key',
                            'testctr_name',
                          ))
    ->orderBy ( 'testctr_name', 'ASC' );

  $result = $query->execute();

  db_set_active ();

  $options = array ();
  foreach ( $result as $record ) {
    $options [ $record->testctr_key ] = array (
      'testctr_name' => $record->testctr_name,
    );
  }

  $header = array (
    'testctr_name' => t('Testing Center Name'),
  );

  $form['table'] = array (
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#empty' => t('No Testing Centers in Database'),
  );


  // code for refresh button - when user selects refresh, the rest
  // of the form will be populated with testctr information

  $form['refresh'] = array (
    '#type' => 'submit',
    '#value' => t('Refresh'),
    '#validate' => array ( 'rmsallergy_update_testctr_validate' ),
    '#submit' => array ( 'rmsallergy_update_testctr_refresh_submit' ),
  );



// set default values for the remainder of the form

  $testctr_name = !empty ( $form_state['values']['testctr_name'] ) ?
                           $form_state['values']['testctr_name'] : '';
  $poc_name = !empty ( $form_state['values']['poc_name'] ) ?
                       $form_state['values']['poc_name'] : '';
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

  unset($form_state['input']['testctr_name']);
  unset($form_state['input']['poc_name']);
  unset($form_state['input']['address1']);
  unset($form_state['input']['address2']);
  unset($form_state['input']['city']);
  unset($form_state['input']['state']);
  unset($form_state['input']['zip']);
  unset($form_state['input']['phone']);
  unset($form_state['input']['email']);
  unset($form_state['input']['fax']);


  $form['testctr_name'] = array (
    '#type' => 'textfield',
    '#title' => t('Testing Center Name'),
    '#size' => 32,
    '#default_value' => $testctr_name,
  );

  $form['poc_name'] = array (
    '#type' => 'textfield',
    '#title' => t('Point of Contact'),
    '#size' => 64,
//    '#required' => TRUE,
    '#default_value' => $poc_name,
  );


  $form['address1'] = array (
    '#type' => 'textfield',
    '#title' => t('Address'),
    '#size' => 64,
//    '#required' => TRUE,
    '#default_value' => $address1,
  );

  $form['address2'] = array (
    '#type' => 'textfield',
    '#title' => t(''),
    '#size' => 64,
    '#default_value' => $address2,
  );

  $form['city'] = array (
    '#type' => 'textfield',
    '#title' => t('City'),
    '#size' => 32,
//    '#required' => TRUE,
    '#default_value' => $city,
  );

  $form['state'] = array (
    '#type' => 'textfield',
    '#title' => t('State'),
    '#size' => 32,
//    '#required' => TRUE,
    '#default_value' => $state,
  );

  $form['zip'] = array (
    '#type' => 'textfield',
    '#title' => t('Zip'),
    '#size' => 16,
//    '#required' => TRUE,
    '#default_value' => $zip,
  );

  $form['phone'] = array (
    '#type' => 'textfield',
    '#title' => t('Main Phone'),
    '#size' => 16,
//    '#required' => TRUE,
    '#default_value' => $phone,
  );

  $form['email'] = array (
    '#type' => 'textfield',
    '#title' => t('Email'),
    '#size' => 16,
//    '#required' => TRUE,
    '#default_value' => $email,
  );

  $form['fax'] = array (
    '#type' => 'textfield',
    '#title' => t('Fax'),
    '#size' => 16,
//    '#required' => TRUE,
    '#default_value' => $fax,
  );


  $form['submit'] = array (
    '#type' => 'submit',
    '#value' => t('Update'),
  );

  return $form;
}




function rmsallergy_update_testctr_validate ( $form, &$form_state )
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
    form_set_error ( 'Update Testing Center', t("Please select a testctr.") );
  } elseif ( $num_record > 1 ) { 
    form_set_error ( 'Update Testing Center', t("Please select only one testctr.") );
  }

  return $form;
}





function rmsallergy_update_testctr_refresh_submit ( $form, &$form_state )
{
// the refresh routine will populate the values array with the data
// of the selected testing center

  // get the testing center key from the table element

  $result = $form_state['values']['table'];

  $testctr_key = NULL;
  foreach ( $result as $record ) {
    if ( $record > 0 ) {
      $testctr_key = $record;
    }
  }

  // query the testing center table to retrieve the information

  db_set_active ( 'rmsallergy' );

  $query = db_select ( 'testctr', 'p' );
  $query
    ->fields ( 'p', array ( 'testctr_key',
                            'testctr_name',
                            'testctr_poc_name',
                            'testctr_address1',
                            'testctr_address2',
                            'testctr_city',
                            'testctr_state',
                            'testctr_zip',
                            'testctr_home_phone',
                            'testctr_work_phone',
                            'testctr_mobile_phone',
                            'testctr_email',
                            'testctr_fax'))
    ->condition ( 'testctr_key', $testctr_key );

  $result = $query->execute();

  $record = $result->fetchAssoc();

  db_set_active ();


  form_set_value ( $form['testctr_name'], $record['testctr_name'], $form_state );
  form_set_value ( $form['poc_name'], $record['testctr_poc_name'], $form_state );
  form_set_value ( $form['address1'], $record['testctr_address1'], $form_state );
  form_set_value ( $form['address2'], $record['testctr_address2'], $form_state );
  form_set_value ( $form['city'], $record['testctr_city'], $form_state );
  form_set_value ( $form['state'], $record['testctr_state'], $form_state );
  form_set_value ( $form['zip'], $record['testctr_zip'], $form_state );
  form_set_value ( $form['phone'], $record['testctr_work_phone'], $form_state );
  form_set_value ( $form['email'], $record['testctr_email'], $form_state );
  form_set_value ( $form['fax'], $record['testctr_fax'], $form_state );


  $form_state['rebuild'] = TRUE;
}



function rmsallergy_update_testctr_submit ( $form, &$form_state )
{

// first, get the data out of the form

  $testctr_name = $form_state['values']['testctr_name'];
  $testctr_poc_name = $form_state['values']['poc_name'];
  $testctr_address1 = $form_state['values']['address1'];
  $testctr_address2 = $form_state['values']['address2'];
  $testctr_city = $form_state['values']['city'];
  $testctr_state = $form_state['values']['state'];
  $testctr_zip = $form_state['values']['zip'];
  $testctr_work_phone = $form_state['values']['phone'];
  $testctr_email = $form_state['values']['email'];
  $testctr_fax = $form_state['values']['fax'];

  // second, get the testctr key from the table element

  $result = $form_state['values']['table'];

  $testctr_key = NULL;
  foreach ( $result as $record ) {
    if ( $record > 0 ) {
      $testctr_key = $record;
    }
  }

  // third, set active database and update testctr and contact databases

  db_set_active ( 'rmsallergy' );

  // update testctr database
  $num_updated = db_update ( 'testctr' )
    ->fields ( array (
      'testctr_name' => $testctr_name,
      'testctr_poc_name' => $testctr_poc_name,
      'testctr_address1' => $testctr_address1,
      'testctr_address2' => $testctr_address2,
      'testctr_city' => $testctr_city,
      'testctr_state' => $testctr_state,
      'testctr_zip' => $testctr_zip,
      'testctr_work_phone' => $testctr_work_phone,
      'testctr_email' => $testctr_email,
      'testctr_fax' => $testctr_fax,
    ))
    ->condition('testctr_key', $testctr_key )
    ->execute();

  db_set_active ();

  drupal_set_message ( t('The testing center has been updated.') );

  $form_state['rebuild'] = TRUE;
}

