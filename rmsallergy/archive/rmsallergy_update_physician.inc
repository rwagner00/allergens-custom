<?php

/**
 * @file
 * RMS Allergy function file
 */

function rmsallergy_update_physician ( $form, &$form_state )
{

// build the table of physicians

  $form['subtitle'] = array (
    '#type' => 'item',
    '#title' => t('Select a Physician to Update (Select Only One):'),
  );


  db_set_active ( 'rmsallergy' );

  $query = db_select ( 'physician', 'p' );
  $query
    ->fields ( 'p', array ( 'physician_key',
                            'physician_name',
                          ))
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
    '#empty' => t('No Physician in Database'),
    '#multiple' => FALSE,
  );


  // code for refresh button - when user selects refresh, the rest
  // of the form will be populated with physician information

  $form['refresh'] = array (
    '#type' => 'submit',
    '#value' => t('Refresh'),
    '#validate' => array ( 'rmsallergy_update_physician_validate' ),
    '#submit' => array ( 'rmsallergy_update_physician_refresh_submit' ),
  );



// set default values for the remainder of the form

  $physician_name = !empty ( $form_state['values']['physician_name'] ) ?
                           $form_state['values']['physician_name'] : '';
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
  unset($form_state['input']['address1']);
  unset($form_state['input']['address2']);
  unset($form_state['input']['city']);
  unset($form_state['input']['state']);
  unset($form_state['input']['zip']);
  unset($form_state['input']['phone']);
  unset($form_state['input']['email']);
  unset($form_state['input']['fax']);


  $form['physician_name'] = array (
    '#type' => 'textfield',
    '#title' => t('Physician Name'),
    '#size' => 32,
    '#default_value' => $physician_name,
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




function rmsallergy_update_physician_validate ( $form, &$form_state )
{
  $result = $form_state['values']['table'];

  if ( empty ( $result ) ) {
    form_set_error ( 'Update Physician', t("Please select a physician.") );
  }

  return $form;
}




function rmsallergy_update_physician_refresh_submit ( $form, &$form_state )
{
// the refresh routine will populate the values array with the data
// of the selected testing center

  // get the testing center key from the table element

  $physician_key = $form_state['values']['table'];


  // query the testing center table to retrieve the information

  db_set_active ( 'rmsallergy' );

  $query = db_select ( 'physician', 'p' );
  $query
    ->fields ( 'p', array ( 'physician_key',
                            'physician_name',
                            'physician_address1',
                            'physician_address2',
                            'physician_city',
                            'physician_state',
                            'physician_zip',
                            'physician_home_phone',
                            'physician_work_phone',
                            'physician_mobile_phone',
                            'physician_email',
                            'physician_fax'))
    ->condition ( 'physician_key', $physician_key );

  $result = $query->execute();

  $record = $result->fetchAssoc();

  db_set_active ();


  form_set_value ( $form['physician_name'], $record['physician_name'], $form_state );
  form_set_value ( $form['address1'], $record['physician_address1'], $form_state );
  form_set_value ( $form['address2'], $record['physician_address2'], $form_state );
  form_set_value ( $form['city'], $record['physician_city'], $form_state );
  form_set_value ( $form['state'], $record['physician_state'], $form_state );
  form_set_value ( $form['zip'], $record['physician_zip'], $form_state );
  form_set_value ( $form['phone'], $record['physician_work_phone'], $form_state );
  form_set_value ( $form['email'], $record['physician_email'], $form_state );
  form_set_value ( $form['fax'], $record['physician_fax'], $form_state );


  $form_state['rebuild'] = TRUE;
}



function rmsallergy_update_physician_submit ( $form, &$form_state )
{

// first, get the data out of the form

  $physician_name = $form_state['values']['physician_name'];
  $physician_address1 = $form_state['values']['address1'];
  $physician_address2 = $form_state['values']['address2'];
  $physician_city = $form_state['values']['city'];
  $physician_state = $form_state['values']['state'];
  $physician_zip = $form_state['values']['zip'];
  $physician_work_phone = $form_state['values']['phone'];
  $physician_email = $form_state['values']['email'];
  $physician_fax = $form_state['values']['fax'];

  // second, get the physician key from the table element

  $physician_key = $form_state['values']['table'];

  // third, set active database and update physician and contact databases

  db_set_active ( 'rmsallergy' );

  // update physician database
  $num_updated = db_update ( 'physician' )
    ->fields ( array (
      'physician_name' => $physician_name,
      'physician_address1' => $physician_address1,
      'physician_address2' => $physician_address2,
      'physician_city' => $physician_city,
      'physician_state' => $physician_state,
      'physician_zip' => $physician_zip,
      'physician_work_phone' => $physician_work_phone,
      'physician_email' => $physician_email,
      'physician_fax' => $physician_fax,
    ))
    ->condition('physician_key', $physician_key )
    ->execute();

  db_set_active ();

  drupal_set_message ( t('The testing center has been updated.') );

  $form_state['rebuild'] = TRUE;
}

