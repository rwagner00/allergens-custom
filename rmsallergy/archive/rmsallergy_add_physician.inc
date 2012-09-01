<?php

/**
 * @file
 * RMS Allergy function file
 */

function rmsallergy_add_physician ( $form, &$form_state )
{
// check for prior call to add physician and go to page 2 if appropriate

  if ( !empty($form_state['page_num']) && $form_state['page_num'] == 2 ) {
    return rmsallergy_add_physician_page_2 ( $form, $form_state );
  }

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

  unset($form_state['input']['physician_name']);
  unset($form_state['input']['address1']);
  unset($form_state['input']['address2']);
  unset($form_state['input']['city']);
  unset($form_state['input']['state']);
  unset($form_state['input']['zip']);
  unset($form_state['input']['phone']);
  unset($form_state['input']['email']);
  unset($form_state['input']['fax']);




// build the table of physicians

  $form['subtitle'] = array (
    '#type' => 'item',
    '#title' => t('Enter Information for New Physician:'),
  );


// build the edit fields of the form

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
    '#value' => t('Next >>'),
    '#submit' => array('rmsallergy_add_physician_next_submit' ),
    '#validate' => array('rmsallergy_add_physician_next_validate' ),
  );

  return $form;
}




function rmsallergy_add_physician_next_validate ( $form, &$form_state )
{
// nothing to validate at this point
  return $form;
}



function rmsallergy_add_physician_next_submit ( $form, &$form_state )
{
// values are save for each page in order to carry to subsequent pages
// and to tell FAPI how to rebuild the form

  $form_state['page_values'][1] = $form_state['values'];

  if ( !empty($form_state['page_values'][2] )) {
    $form_state['values'] = $form_state['page_values'][2];
  }

  $form_state['page_num'] = 2;
  $form_state['rebuild'] = TRUE;

  return $form;
}





function rmsallergy_add_physician_page_2 ( $form, &$form_state )
{
// set default values

  $table = !empty ( $form_state['values']['table'] ) ?
                    $form_state['values']['table'] : array();

  unset ( $form_state['inputs']['table'] );


//

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


// build the form

  $form['subtitle'] = array (
    '#type' => 'item',
    '#title' => t('Select Practice for This Physician:'),
  );

  $form['table'] = array (
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#empty' => t('No Practices in Database'),
    '#multiple' => FALSE,
    '#default_value' => $table,
  );

  $form['back'] = array (
    '#type' => 'submit',
    '#value' => t('<< Back'),
    '#submit' => array('rmsallergy_add_physician_back_submit' ),
    '#validate' => array('rmsallergy_add_physician_back_validate' ),
  );

  $form['submit'] = array (
    '#type' => 'submit',
    '#value' => t('Submit'),
    '#submit' => array('rmsallergy_add_physician_submit' ),
    '#validate' => array('rmsallergy_add_physician_validate' ),
  );


  return $form;
}


function rmsallergy_add_physician_back_validate ( $form, &$form_state )
{
// nothing to validate at this point
  return $form;
}

function rmsallergy_add_physician_back_submit ( $form, &$form_state )
{
// values are save for each page in order to carry to subsequent pages
// and to tell FAPI how to rebuild the form

  $form_state['page_values'][2] = $form_state['values'];

  if ( !empty($form_state['page_values'][1] )) {
    $form_state['values'] = $form_state['page_values'][1];
  }

  $form_state['page_num'] = 1;
  $form_state['rebuild'] = TRUE;

  return $form;
}



function rmsallergy_add_physician_validate ( $form, &$form_state )
{
  if ( empty($form_state['values']['table'] )) {
    form_set_error ( 'Add Physician', t("Please select a practice." ) );
  }

  return $form;
}


function rmsallergy_add_physician_submit ( $form, &$form_state )
{

// get the data out of the form

  $practice_key = $form_state['values']['table'];

  $physician_name       = $form_state['page_values'][1]['physician_name'];
  $physician_address1   = $form_state['page_values'][1]['address1'];
  $physician_address2   = $form_state['page_values'][1]['address2'];
  $physician_city       = $form_state['page_values'][1]['city'];
  $physician_state      = $form_state['page_values'][1]['state'];
  $physician_zip        = $form_state['page_values'][1]['zip'];
  $physician_work_phone = $form_state['page_values'][1]['phone'];
  $physician_email      = $form_state['page_values'][1]['email'];
  $physician_fax        = $form_state['page_values'][1]['fax'];

// set active database and insert new record

  db_set_active ( 'rmsallergy' );

  // update physician database
  $physician_key = db_insert ( 'physician' )
    ->fields ( array (
      'physician_name' => $physician_name,
      'practice_key' => $practice_key,
      'physician_address1' => $physician_address1,
      'physician_address2' => $physician_address2,
      'physician_city' => $physician_city,
      'physician_state' => $physician_state,
      'physician_zip' => $physician_zip,
      'physician_work_phone' => $physician_work_phone,
      'physician_email' => $physician_email,
      'physician_fax' => $physician_fax,
    ))
    ->execute();

  db_set_active ();

  drupal_set_message ( t('The physician has been added.') );
}
