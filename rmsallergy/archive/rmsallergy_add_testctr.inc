<?php

/**
 * @file
 * RMS Allergy function file
 */

function rmsallergy_add_testctr ( $form, &$form_state )
{

// build the table of testctrs

  $form['subtitle'] = array (
    '#type' => 'item',
    '#title' => t('Enter Information for New Testing Center:'),
  );


// build the edit fields of the form

  $form['testctr_name'] = array (
    '#type' => 'textfield',
    '#title' => t('Testing Center Name'),
    '#size' => 32,
  );

  $form['poc_name'] = array (
    '#type' => 'textfield',
    '#title' => t('Point of Contact'),
    '#size' => 64,
//    '#required' => TRUE,
  );


  $form['address1'] = array (
    '#type' => 'textfield',
    '#title' => t('Address'),
    '#size' => 64,
//    '#required' => TRUE,
  );

  $form['address2'] = array (
    '#type' => 'textfield',
    '#title' => t(''),
    '#size' => 64,
  );

  $form['city'] = array (
    '#type' => 'textfield',
    '#title' => t('City'),
    '#size' => 32,
//    '#required' => TRUE,
  );

  $form['state'] = array (
    '#type' => 'textfield',
    '#title' => t('State'),
    '#size' => 32,
//    '#required' => TRUE,
  );

  $form['zip'] = array (
    '#type' => 'textfield',
    '#title' => t('Zip'),
    '#size' => 16,
//    '#required' => TRUE,
  );

  $form['phone'] = array (
    '#type' => 'textfield',
    '#title' => t('Main Phone'),
    '#size' => 16,
//    '#required' => TRUE,
  );

  $form['email'] = array (
    '#type' => 'textfield',
    '#title' => t('Email'),
    '#size' => 16,
//    '#required' => TRUE,
  );

  $form['fax'] = array (
    '#type' => 'textfield',
    '#title' => t('Fax'),
    '#size' => 16,
//    '#required' => TRUE,
  );



  $form['submit'] = array (
    '#type' => 'submit',
    '#value' => t('Update'),
  );

  return $form;
}






function rmsallergy_add_testctr_validate ( $form, &$form_state )
{
// nothing to validate at this point
  return $form;
}





function rmsallergy_add_testctr_submit ( $form, &$form_state )
{

// get the data out of the form

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

// set active database and insert new record

  db_set_active ( 'rmsallergy' );

  // update testctr database
  $testctr_key = db_insert ( 'testctr' )
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
    ->execute();

  db_set_active ();

  drupal_set_message ( t('The testing center has been added.') );
}

