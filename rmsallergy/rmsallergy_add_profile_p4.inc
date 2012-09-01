<?php

// this is the insurance information page
// currently it is not being used (removed per review on 5/30/2012)

function rmsallergy_add_profile_p4 ( $form, &$form_state )
{
  $cash_pay_flag = !empty ( $form_state['values']['cash_pay_flag'] ) ?
                            $form_state['values']['cash_pay_flag'] : '';

  $primary_flag = !empty ( $form_state['values']['primary_flag'] ) ?
                           $form_state['values']['primary_flag'] : '';
  $primary_carrier = !empty ( $form_state['values']['primary_carrier'] ) ?
                              $form_state['values']['primary_carrier'] : '';
  $primary_group_number = !empty ( $form_state['values']['primary_group_number'] ) ?
                                   $form_state['values']['primary_group_number'] : '';
  $primary_holder_name = !empty ( $form_state['values']['primary_holder_name'] ) ?
                                  $form_state['values']['primary_holder_name'] : '';
  $primary_holder_ssn1 = !empty ( $form_state['values']['primary_holder_ssn1'] ) ?
                                 $form_state['values']['primary_holder_ssn1'] : '';
  $primary_holder_ssn2 = !empty ( $form_state['values']['primary_holder_ssn2'] ) ?
                                 $form_state['values']['primary_holder_ssn2'] : '';
  $primary_holder_ssn3 = !empty ( $form_state['values']['primary_holder_ssn3'] ) ?
                                 $form_state['values']['primary_holder_ssn3'] : '';
  $primary_holder_dob_month = !empty ( $form_state['values']['primary_holder_dob_month'] ) ?
                                 $form_state['values']['primary_holder_dob_month'] : '';
  $primary_holder_dob_day = !empty ( $form_state['values']['primary_holder_dob_day'] ) ?
                                 $form_state['values']['primary_holder_dob_day'] : '';
  $primary_holder_dob_year = !empty ( $form_state['values']['primary_holder_dob_year'] ) ?
                                 $form_state['values']['primary_holder_dob_year'] : '';

  $secondary_flag = !empty ( $form_state['values']['secondary_flag'] ) ?
                             $form_state['values']['secondary_flag'] : '';
  $secondary_carrier = !empty ( $form_state['values']['secondary_carrier'] ) ?
                                $form_state['values']['secondary_carrier'] : '';
  $secondary_group_number = !empty ( $form_state['values']['secondary_group_number'] ) ?
                                     $form_state['values']['secondary_group_number'] : '';
  $secondary_holder_name = !empty ( $form_state['values']['secondary_holder_name'] ) ?
                                    $form_state['values']['secondary_holder_name'] : '';
  $secondary_holder_ssn1 = !empty ( $form_state['values']['secondary_holder_ssn1'] ) ?
                                   $form_state['values']['secondary_holder_ssn1'] : '';
  $secondary_holder_ssn2 = !empty ( $form_state['values']['secondary_holder_ssn2'] ) ?
                                   $form_state['values']['secondary_holder_ssn2'] : '';
  $secondary_holder_ssn3 = !empty ( $form_state['values']['secondary_holder_ssn3'] ) ?
                                   $form_state['values']['secondary_holder_ssn3'] : '';
  $secondary_holder_dob_month = !empty ( $form_state['values']['secondary_holder_dob_month'] ) ?
                                 $form_state['values']['secondary_holder_dob_month'] : '';
  $secondary_holder_dob_day = !empty ( $form_state['values']['secondary_holder_dob_day'] ) ?
                                 $form_state['values']['secondary_holder_dob_day'] : '';
  $secondary_holder_dob_year = !empty ( $form_state['values']['secondary_holder_dob_year'] ) ?
                                 $form_state['values']['secondary_holder_dob_year'] : '';

  unset($form_state['input']['cash_pay_flag']);
  unset($form_state['input']['primary_flag']);
  unset($form_state['input']['primary_carrier']);
  unset($form_state['input']['primary_group_number']);
  unset($form_state['input']['primary_holder_name']);
  unset($form_state['input']['primary_holder_ssn1']);
  unset($form_state['input']['primary_holder_ssn2']);
  unset($form_state['input']['primary_holder_ssn3']);
  unset($form_state['input']['primary_holder_dob_month']);
  unset($form_state['input']['primary_holder_dob_day']);
  unset($form_state['input']['primary_holder_dob_year']);
  unset($form_state['input']['secondary_flag']);
  unset($form_state['input']['secondary_carrier']);
  unset($form_state['input']['secondary_group_number']);
  unset($form_state['input']['secondary_holder_name']);
  unset($form_state['input']['secondary_holder_ssn1']);
  unset($form_state['input']['secondary_holder_ssn2']);
  unset($form_state['input']['secondary_holder_ssn3']);
  unset($form_state['input']['secondary_holder_dob_month']);
  unset($form_state['input']['secondary_holder_dob_day']);
  unset($form_state['input']['secondary_holder_dob_year']);

  $form['cash_pay_flag'] = array (
    '#type' => 'checkbox',
    '#title' => t('Check if patient is paying out of pocket.'),
    '#default_value' => $cash_pay_flag,
  );

  $form['primary_flag'] = array (
    '#type' => 'checkbox',
    '#title' => t('Check if patient has primary coverage.'),
    '#default_value' => $primary_flag,
  );

  $form['primary_carrier'] = array (
    '#type' => 'textfield',
    '#title' => t('Primary Carrier'),
    '#size' => 64,
    '#default_value' => $primary_carrier,
  );

  $form['primary_group_number'] = array (
    '#type' => 'textfield',
    '#title' => t('Primary Group Number'),
    '#size' => 32,
    '#default_value' => $primary_group_number,
  );

  $form['primary_holder_name'] = array (
    '#type' => 'textfield',
    '#title' => t('Policy Holder Name'),
    '#size' => 64,
    '#default_value' => $primary_holder_name,
  );

  $form['header_primary_holder_ssn'] = array (
    '#type' => 'item',
    '#title' => t('Policy Holder Social Security Number'),
    '#suffix' => '<table>',
  );

  $form['primary_holder_ssn1'] = array (
    '#type' => 'textfield',
    '#size' => 3,
    '#default_value' => $primary_holder_ssn1,
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['primary_holder_ssn2'] = array (
    '#type' => 'textfield',
    '#size' => 2,
    '#default_value' => $primary_holder_ssn2,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['primary_holder_ssn3'] = array (
    '#type' => 'textfield',
    '#size' => 4,
    '#default_value' => $primary_holder_ssn3,
    '#prefix' => '<td>',
    '#suffix' => '</td></tr></table>',
  );

  $form['header_primary_holder_dob'] = array (
    '#type' => 'item',
    '#title' => t('Date of Birth'),
    '#suffix' => "<table>",
  );

  $form['primary_holder_dob_month'] = array (
    '#type' => 'textfield',
    '#title' => t('Month (mm)'),
    '#size' => 2,
    '#default_value' => $primary_holder_dob_month,
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['primary_holder_dob_day'] = array (
    '#type' => 'textfield',
    '#title' => t('Day (dd)'),
    '#size' => 2,
    '#default_value' => $primary_holder_dob_day,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['primary_holder_dob_year'] = array (
    '#type' => 'textfield',
    '#title' => t('Year (yyyy)'),
    '#size' => 4,
   '#default_value' => $primary_holder_dob_year,
    '#prefix' => '<td>',
    '#suffix' => '</td></tr></table>',
  );


  $form['secondary_flag'] = array (
    '#type' => 'checkbox',
    '#title' => t('Check if patient has secondary coverage.'),
    '#default_value' => $secondary_flag,
  );

  $form['secondary_carrier'] = array (
    '#type' => 'textfield',
    '#title' => t('Secondary Carrier'),
    '#size' => 64,
    '#default_value' => $secondary_carrier,
  );

  $form['secondary_group_number'] = array (
    '#type' => 'textfield',
    '#title' => t('Secondary Group Number'),
    '#size' => 32,
    '#default_value' => $secondary_group_number,
  );

  $form['secondary_holder_name'] = array (
    '#type' => 'textfield',
    '#title' => t('Policy Holder Name'),
    '#size' => 64,
    '#default_value' => $secondary_holder_name,
  );

  $form['header_secondary_holder_ssn'] = array (
    '#type' => 'item',
    '#title' => t('Policy Holder Social Security Number'),
    '#suffix' => '<table>',
  );

  $form['secondary_holder_ssn1'] = array (
    '#type' => 'textfield',
    '#size' => 3,
    '#default_value' => $secondary_holder_ssn1,
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['secondary_holder_ssn2'] = array (
    '#type' => 'textfield',
    '#size' => 2,
    '#default_value' => $secondary_holder_ssn2,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['secondary_holder_ssn3'] = array (
    '#type' => 'textfield',
    '#size' => 4,
    '#default_value' => $secondary_holder_ssn3,
    '#prefix' => '<td>',
    '#suffix' => '</td></tr></table>',
  );

  $form['header_secondary_holder_dob'] = array (
    '#type' => 'item',
    '#title' => t('Date of Birth'),
    '#suffix' => "<table>",
  );

  $form['secondary_holder_dob_month'] = array (
    '#type' => 'textfield',
    '#title' => t('Month (mm)'),
    '#size' => 2,
   '#default_value' => $secondary_holder_dob_month,
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['secondary_holder_dob_day'] = array (
    '#type' => 'textfield',
    '#title' => t('Day (dd)'),
    '#size' => 2,
    '#default_value' => $secondary_holder_dob_day,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['secondary_holder_dob_year'] = array (
    '#type' => 'textfield',
    '#title' => t('Year (yyyy)'),
    '#size' => 4,
    '#default_value' => $secondary_holder_dob_year,
    '#prefix' => '<td>',
    '#suffix' => '</td></tr></table>',
  );

  $form['back'] = array (
    '#type' => 'submit',
    '#value' => t('<< Back'),
    '#submit' => array('rmsallergy_add_profile_p4_back_submit' ),
    '#validate' => array('rmsallergy_add_profile_p4_back_validate' ),
  );

  $form['next_ent'] = array (
    '#type' => 'submit',
    '#value' => t('Refer to ENT'),
    '#submit' => array('rmsallergy_add_profile_p4_next_ent_submit' ),
    '#validate' => array('rmsallergy_add_profile_p4_next_validate' ),
  );

  $form['next_allergist'] = array (
    '#type' => 'submit',
    '#value' => t('Refer to Allergist'),
    '#submit' => array('rmsallergy_add_profile_p4_next_allergist_submit' ),
    '#validate' => array('rmsallergy_add_profile_p4_next_validate' ),
  );

  return $form;
}
function rmsallergy_add_profile_p4_back_validate ( $form, &$form_state )
{
// nothing to validate at this point
  return $form;
}

function rmsallergy_add_profile_p4_back_submit ( $form, &$form_state )
{
// values are save for each page in order to carry to subsequent pages
// and to tell FAPI how to rebuild the form

  $form_state['page_values'][4] = $form_state['values'];

  if ( !empty($form_state['page_values'][3] )) {
    $form_state['values'] = $form_state['page_values'][3];
  }

  $form_state['page_num'] = 3;
  $form_state['rebuild'] = TRUE;

  return $form;
}

function rmsallergy_add_profile_p4_next_validate ( $form, &$form_state )
{
  if ( empty ( $form_state['values']['primary_holder_dob_month'] )) {
    $form_state['values']['primary_holder_dob_month'] = 0;
  }
  if ( empty ( $form_state['values']['primary_holder_dob_day'] )) {
    $form_state['values']['primary_holder_dob_day'] = 0;
  }
  if ( empty ( $form_state['values']['primary_holder_dob_year'] )) {
    $form_state['values']['primary_holder_dob_year'] = 0;
  }

  if ( empty ( $form_state['values']['secondary_holder_dob_month'] )) {
    $form_state['values']['secondary_holder_dob_month'] = 0;
  }
  if ( empty ( $form_state['values']['secondary_holder_dob_day'] )) {
    $form_state['values']['secondary_holder_dob_day'] = 0;
  }
  if ( empty ( $form_state['values']['secondary_holder_dob_year'] )) {
    $form_state['values']['secondary_holder_dob_year'] = 0;
  }

  return $form;
}

function rmsallergy_add_profile_p4_next_ent_submit ( $form, &$form_state )
{
// values are save for each page in order to carry to subsequent pages
// and to tell FAPI how to rebuild the form

  $form_state['page_values'][4] = $form_state['values'];

  if ( !empty($form_state['page_values'][5] )) {
    $form_state['values'] = $form_state['page_values'][5];
  }

  $form_state['page_num'] = 5;
  $form_state['rebuild'] = TRUE;

  return $form;
}

function rmsallergy_add_profile_p4_next_allergist_submit ( $form, &$form_state )
{
// values are save for each page in order to carry to subsequent pages
// and to tell FAPI how to rebuild the form

  $form_state['page_values'][4] = $form_state['values'];

  if ( !empty($form_state['page_values'][6] )) {
    $form_state['values'] = $form_state['page_values'][6];
  }

  $form_state['page_num'] = 6;
  $form_state['rebuild'] = TRUE;

  return $form;
}

















?>
