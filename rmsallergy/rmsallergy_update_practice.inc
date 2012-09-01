<?php

/*m
 * @file
 * RMS Allergy function file
 */

function rmsallergy_update_practice ( $form, &$form_state )
{

// build the table of practices

  $form['subtitle'] = array (
    '#type' => 'item',
    '#title' => t('Select a Practice to Update:'),
  );


  db_set_active ( 'rmsallergy' );

  $query = db_select ( 'practice', 'p' );
  $query
    ->fields ( 'p', array ( 'practice_key',
                            'practice_name',
                            'practice_specialty',
                          ))
    ->orderBy ( 'practice_name', 'ASC' );

  $result = $query->execute();

  db_set_active ();

  $options = array ();
  foreach ( $result as $record ) {

     $specialty = $record->practice_specialty;
         if ( $specialty == '0' ) { $specialty = 'Primary Care'; }
     elseif ( $specialty == '1' ) { $specialty = 'Allergist'; }
     elseif ( $specialty == '2' ) { $specialty = 'ENT'; }
     else                         { $specialty = 'Unknown'; }

    $options [ $record->practice_key ] = array (
      'practice_name' => $record->practice_name,
      'practice_specialty' => $specialty,
    );
  }

  $header = array (
    'practice_name' => t('Practice Name'),
    'practice_specialty' => t('Practice Specialty'),
  );

  $form['table'] = array (
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#empty' => t('No Practices in Database'),
    '#multiple' => FALSE,
  );


  // code for refresh button - when user selects refresh, the rest
  // of the form will be populated with practice information

  $form['refresh'] = array (
    '#type' => 'submit',
    '#value' => t('Open'),
    '#validate' => array ( 'rmsallergy_update_practice_validate' ),
    '#submit' => array ( 'rmsallergy_update_practice_refresh_submit' ),
  );



// set default values for the remainder of the form

  $practice_name = !empty ( $form_state['values']['practice_name'] ) ?
                            $form_state['values']['practice_name'] : '';
  $specialty = !empty ( $form_state['values']['specialty'] ) ?
                        $form_state['values']['specialty'] : '';
  $admin_poc_name = !empty ( $form_state['values']['admin_poc_name'] ) ?
                             $form_state['values']['admin_poc_name'] : '';
  $admin_poc_email = !empty ( $form_state['values']['admin_poc_email'] ) ?
                              $form_state['values']['admin_poc_email'] : '';
  $clinical_poc_name = !empty ( $form_state['values']['clinical_poc_name'] ) ?
                                $form_state['values']['clinical_poc_name'] : '';
  $clinical_poc_email = !empty ( $form_state['values']['clinical_poc_email'] ) ?
                                 $form_state['values']['clinical_poc_email'] : '';
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

  unset($form_state['input']['practice_name']);
  unset($form_state['input']['specialty']);
  unset($form_state['input']['admin_poc_name']);
  unset($form_state['input']['admin_poc_email']);
  unset($form_state['input']['clinical_poc_name']);
  unset($form_state['input']['clinical_poc_email']);
  unset($form_state['input']['address1']);
  unset($form_state['input']['address2']);
  unset($form_state['input']['city']);
  unset($form_state['input']['state']);
  unset($form_state['input']['zip']);
  unset($form_state['input']['phone']);
  unset($form_state['input']['email']);
  unset($form_state['input']['fax']);


  $form['practice_name'] = array (
    '#type' => 'textfield',
    '#title' => t('Practice Name'),
    '#size' => 64,
    '#default_value' => $practice_name,
  );

  $form['specialty'] = array (
    '#type' => 'radios',
    '#title' => t('Specialty'),
    '#options' => array ( '0' => t('Primary Care'),
                          '1' => t('Allergist'),
                          '2' => t('ENT')),
    '#default_value' => $specialty,
  );

  $form['admin_poc_name'] = array (
    '#type' => 'textfield',
    '#title' => t('Administrative Point of Contact'),
    '#size' => 64,
//    '#required' => TRUE,
    '#default_value' => $admin_poc_name,
    '#prefix' => '<table><tr><td>',
    '#suffix' => '</td>',
  );

  $form['admin_poc_email'] = array (
    '#type' => 'textfield',
    '#title' => t('Email'),
    '#size' => 64,
//    '#required' => TRUE,
    '#default_value' => $admin_poc_email,
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );

  $form['clinical_poc_name'] = array (
    '#type' => 'textfield',
    '#title' => t('Clinical Point of Contact'),
    '#size' => 64,
//    '#required' => TRUE,
    '#default_value' => $clinical_poc_name,
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['clinical_poc_email'] = array (
    '#type' => 'textfield',
    '#title' => t('Email'),
    '#size' => 64,
//    '#required' => TRUE,
    '#default_value' => $clinical_poc_email,
    '#prefix' => '<td>',
    '#suffix' => '</td></tr></table>',
  );


  $form['address1'] = array (
    '#type' => 'textfield',
    '#title' => t('Address'),
    '#size' => 64,
//    '#required' => TRUE,
    '#default_value' => $address1,
    '#prefix' => '<table><tr><td>',
    '#suffix' => '</td></tr>',
  );

  $form['address2'] = array (
    '#type' => 'textfield',
    '#title' => t(''),
    '#size' => 64,
    '#default_value' => $address2,
    '#prefix' => '<tr><td>',
    '#suffix' => '</td></tr>',
  );

  $form['city'] = array (
    '#type' => 'textfield',
    '#title' => t('City'),
    '#size' => 64,
//    '#required' => TRUE,
    '#default_value' => $city,
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['state'] = array (
    '#type' => 'textfield',
    '#title' => t('State'),
    '#size' => 32,
//    '#required' => TRUE,
    '#default_value' => $state,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['zip'] = array (
    '#type' => 'textfield',
    '#title' => t('Zip'),
    '#size' => 16,
//    '#required' => TRUE,
    '#default_value' => $zip,
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );

  $form['phone'] = array (
    '#type' => 'textfield',
    '#title' => t('Main Phone'),
    '#size' => 32,
//    '#required' => TRUE,
    '#default_value' => $phone,
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['email'] = array (
    '#type' => 'textfield',
    '#title' => t('Email'),
    '#size' => 64,
//    '#required' => TRUE,
    '#default_value' => $email,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['fax'] = array (
    '#type' => 'textfield',
    '#title' => t('Fax'),
    '#size' => 16,
//    '#required' => TRUE,
    '#default_value' => $fax,
    '#prefix' => '<td>',
    '#suffix' => '</td></tr></table>',
  );


  $form['submit'] = array (
    '#type' => 'submit',
    '#value' => t('Update'),
  );

  return $form;
}




function rmsallergy_update_practice_validate ( $form, &$form_state )
{
  $practice_key = $form_state['values']['table'];

  if ( empty ( $practice_key ) )
  { 
    form_set_error ( 'Update Practice', t("Please select a practice.") );
  }

  return $form;
}





function rmsallergy_update_practice_refresh_submit ( $form, &$form_state )
{
// the refresh routine will populate the values array with the data
// of the selected pratice

  // get the practice key from the table element

  $practice_key = $form_state['values']['table'];

//  $practice_key = NULL;
//  foreach ( $result as $record ) {
//    if ( $record > 0 ) {
//      $practice_key = $record;
//    }
//  }

  // query the practice table to retrieve the information

  db_set_active ( 'rmsallergy' );

  $query = db_select ( 'practice', 'p' );
  $query
    ->fields ( 'p', array ( 'practice_key',
                            'practice_name',
                            'practice_specialty',
                            'practice_admin_poc_name',
                            'practice_admin_poc_email',
                            'practice_clinical_poc_name',
                            'practice_clinical_poc_email',
                            'practice_address1',
                            'practice_address2',
                            'practice_city',
                            'practice_state',
                            'practice_zip',
                            'practice_home_phone',
                            'practice_work_phone',
                            'practice_mobile_phone',
                            'practice_email',
                            'practice_fax'))
    ->condition ( 'practice_key', $practice_key );

  $result = $query->execute();

  $record = $result->fetchAssoc();

  db_set_active ();


  form_set_value ( $form['practice_name'], $record['practice_name'], $form_state );
  form_set_value ( $form['specialty'], $record['practice_specialty'], $form_state );
  form_set_value ( $form['admin_poc_name'], $record['practice_admin_poc_name'], $form_state );
  form_set_value ( $form['admin_poc_email'], $record['practice_admin_poc_email'], $form_state );
  form_set_value ( $form['clinical_poc_name'], $record['practice_clinical_poc_name'], $form_state );
  form_set_value ( $form['clinical_poc_email'], $record['practice_clinical_poc_email'], $form_state );
  form_set_value ( $form['address1'], $record['practice_address1'], $form_state );
  form_set_value ( $form['address2'], $record['practice_address2'], $form_state );
  form_set_value ( $form['city'], $record['practice_city'], $form_state );
  form_set_value ( $form['state'], $record['practice_state'], $form_state );
  form_set_value ( $form['zip'], $record['practice_zip'], $form_state );
  form_set_value ( $form['phone'], $record['practice_work_phone'], $form_state );
  form_set_value ( $form['email'], $record['practice_email'], $form_state );
  form_set_value ( $form['fax'], $record['practice_fax'], $form_state );


  $form_state['rebuild'] = TRUE;
}



function rmsallergy_update_practice_submit ( $form, &$form_state )
{

// first, get the data out of the form

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

  // second, get the practice key from the table element

  $result = $form_state['values']['table'];

  $practice_key = NULL;
  foreach ( $result as $record ) {
    if ( $record > 0 ) {
      $practice_key = $record;
    }
  }

  // third, set active database and update practice and contact databases

  db_set_active ( 'rmsallergy' );

  // update practice database
  $num_updated = db_update ( 'practice' )
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
    ->condition('practice_key', $practice_key )
    ->execute();

  db_set_active ();

  drupal_set_message ( t('The practice has been updated.') );

  $form_state['rebuild'] = TRUE;
}

