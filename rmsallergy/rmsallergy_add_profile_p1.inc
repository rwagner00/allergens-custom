<?php

/**
 * @file
 * RMS Allergy function file
 */

function rmsallergy_add_profile_p1 ( $form, &$form_state )
{

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



// build the new patient form

  $form['subtitle'] = array (
    '#type' => 'item',
    '#title' => t('Enter Information for New Patient:'),
  );

  $form['first_name'] = array (
    '#type' => 'textfield',
    '#title' => t('First Name'),
    '#size' => 64,
   '#default_value' => $first_name,
  );

  $form['middle_name'] = array (
    '#type' => 'textfield',
    '#title' => t('Middle Initial'),
    '#size' => 8,
   '#default_value' => $middle_name,
  );

  $form['last_name'] = array (
    '#type' => 'textfield',
    '#title' => t('Last Name'),
    '#size' => 64,
   '#default_value' => $last_name,
  );

  $form['header_ssn'] = array (
    '#type' => 'item',
    '#title' => t('Social Security Number'),
    '#suffix' => "<table>",
  );

  $form['ssn1'] = array (
    '#type' => 'textfield',
    '#size' => 3,
    '#default_value' => $ssn1,
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['ssn2'] = array (
    '#type' => 'textfield',
    '#size' => 2,
    '#default_value' => $ssn2,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['ssn3'] = array (
    '#type' => 'textfield',
    '#size' => 4,
    '#default_value' => $ssn3,
    '#prefix' => '<td>',
    '#suffix' => '</td></tr></table>',
  );

  $form['header_dob'] = array (
    '#type' => 'item',
    '#title' => t('Date of Birth'),
    '#suffix' => "<table>",
  );

  $form['dob_month'] = array (
    '#type' => 'textfield',
    '#title' => t('Month (mm)'),
    '#size' => 2,
    '#default_value' => $dob_month,
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['dob_day'] = array (
    '#type' => 'textfield',
    '#title' => t('Day (dd)'),
    '#size' => 2,
   '#default_value' => $dob_day,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['dob_year'] = array (
    '#type' => 'textfield',
    '#title' => t('Year (yyyy)'),
    '#size' => 4,
   '#default_value' => $dob_year,
    '#prefix' => '<td>',
    '#suffix' => '</td></tr></table>',
  );

  $form['gender'] = array (
    '#type' => 'textfield',
    '#title' => t('Gender'),
    '#size' => 8,
   '#default_value' => $gender,
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

  $form['home_phone'] = array (
    '#type' => 'textfield',
    '#title' => t('Home Phone'),
    '#size' => 16,
//    '#required' => TRUE,
    '#default_value' => $home_phone,
  );

  $form['work_phone'] = array (
    '#type' => 'textfield',
    '#title' => t('Work Phone'),
    '#size' => 16,
//    '#required' => TRUE,
    '#default_value' => $work_phone,
  );

  $form['mobile_phone'] = array (
    '#type' => 'textfield',
    '#title' => t('Mobile Phone'),
    '#size' => 16,
//    '#required' => TRUE,
    '#default_value' => $mobile_phone,
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
    '#submit' => array('rmsallergy_add_profile_p1_next_submit' ),
    '#validate' => array('rmsallergy_add_profile_p1_next_validate' ),
  );

  return $form;
}


function rmsallergy_add_profile_p1_next_validate ( $form, &$form_state )
{
  if ( empty ( $form_state['values']['dob_month'] )) {
    $form_state['values']['dob_month'] = 0;
  }
  if ( empty ( $form_state['values']['dob_day'] )) {
    $form_state['values']['dob_day'] = 0;
  }
  if ( empty ( $form_state['values']['dob_year'] )) {
    $form_state['values']['dob_year'] = 0;
  }

  return $form;
}


function rmsallergy_add_profile_p1_next_submit ( $form, &$form_state )
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

?>
