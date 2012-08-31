<?php

/**
 * @file
 * RMS Allergy function file
 */

function rmsallergy_add_practice ( $form, &$form_state )
{

// build the table of practices

  $form['subtitle'] = array (
    '#type' => 'item',
    '#title' => t('Enter Information for New Practice:'),
  );


// build the edit fields of the form

  $form['practice_name'] = array (
    '#type' => 'textfield',
    '#title' => t('Practice Name'),
    '#size' => 64,
  );

  $form['specialty'] = array (
    '#type' => 'radios',
    '#title' => t('Specialty'),
    '#options' => array ( '0' => t('Primary Care'),
                          '1' => t('Allergist'),
                          '2' => t('ENT')),
  );

  $form['admin_poc_name'] = array (
    '#type' => 'textfield',
    '#title' => t('Administrative Point of Contact'),
    '#size' => 64,
//    '#required' => TRUE,
    '#prefix' => '<table><tr><td>',
    '#suffix' => '</td>',
  );

  $form['admin_poc_email'] = array (
    '#type' => 'textfield',
    '#title' => t('Administrative POC Email Address'),
    '#size' => 64,
//    '#required' => TRUE,
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );

  $form['clinical_poc_name'] = array (
    '#type' => 'textfield',
    '#title' => t('Clinical Point of Contact'),
    '#size' => 64,
//    '#required' => TRUE,
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['clinical_poc_email'] = array (
    '#type' => 'textfield',
    '#title' => t('Clinical POC Email Address'),
    '#size' => 64,
//    '#required' => TRUE,
    '#prefix' => '<td>',
    '#suffix' => '</td></tr></table>',
  );

  $form['address1'] = array (
    '#type' => 'textfield',
    '#title' => t('Address'),
    '#size' => 64,
//    '#required' => TRUE,
    '#prefix' => '<table><tr><td>',
    '#suffix' => '</td></tr>',
  );

  $form['address2'] = array (
    '#type' => 'textfield',
    '#title' => t(''),
    '#size' => 64,
    '#prefix' => '<tr><td>',
    '#suffix' => '</td></tr>',
  );

  $form['city'] = array (
    '#type' => 'textfield',
    '#title' => t('City'),
    '#size' => 64,
//    '#required' => TRUE,
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['state'] = array (
    '#type' => 'textfield',
    '#title' => t('State'),
    '#size' => 32,
//    '#required' => TRUE,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['zip'] = array (
    '#type' => 'textfield',
    '#title' => t('Zip'),
    '#size' => 16,
//    '#required' => TRUE,
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );

  $form['phone'] = array (
    '#type' => 'textfield',
    '#title' => t('Main Phone'),
    '#size' => 32,
//    '#required' => TRUE,
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['email'] = array (
    '#type' => 'textfield',
    '#title' => t('Email'),
    '#size' => 64,
//    '#required' => TRUE,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['fax'] = array (
    '#type' => 'textfield',
    '#title' => t('Fax'),
    '#size' => 16,
//    '#required' => TRUE,
    '#prefix' => '<td>',
    '#suffix' => '</td></tr></table>',
  );



  $form['submit'] = array (
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  return $form;
}






function rmsallergy_add_practice_validate ( $form, &$form_state )
{
// nothing to validate at this point
  return $form;
}





function rmsallergy_add_practice_submit ( $form, &$form_state )
{

// get the data out of the form

  $practice_name = $form_state['values']['practice_name'];
  $practice_specialty = $form_state['values']['specialty'];
  $practice_admin_poc_name = $form_state['values']['admin_poc_name'];
  $practice_admin_poc_email = $form_state['values']['admin_poc_email'];
  $practice_clinical_poc_name = $form_state['values']['clinical_poc_name'];
  $practice_clinical_poc_email = $form_state['values']['clinical_poc_email'];
  $practice_address1 = $form_state['values']['address1'];
  $practice_address2 = $form_state['values']['address2'];
  $practice_city = $form_state['values']['city'];
  $practice_state = $form_state['values']['state'];
  $practice_zip = $form_state['values']['zip'];
  $practice_work_phone = $form_state['values']['phone'];
  $practice_email = $form_state['values']['email'];
  $practice_fax = $form_state['values']['fax'];

// set active database and insert new record

  db_set_active ( 'rmsallergy' );

  // update practice database
  $practice_key = db_insert ( 'practice' )
    ->fields ( array (
      'practice_name' => $practice_name,
      'practice_specialty' => $practice_specialty,
      'practice_admin_poc_name' => $practice_admin_poc_name,
      'practice_admin_poc_email' => $practice_admin_poc_email,
      'practice_clinical_poc_name' => $practice_clinical_poc_name,
      'practice_clinical_poc_email' => $practice_clinical_poc_email,
      'practice_address1' => $practice_address1,
      'practice_address2' => $practice_address2,
      'practice_city' => $practice_city,
      'practice_state' => $practice_state,
      'practice_zip' => $practice_zip,
      'practice_work_phone' => $practice_work_phone,
      'practice_email' => $practice_email,
      'practice_fax' => $practice_fax,
    ))
    ->execute();

  db_set_active ();

  drupal_set_message ( t('The practice has been added.') );
}

