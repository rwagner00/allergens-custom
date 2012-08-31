<?php

function rmsallergy_add_profile_p2 ( $form, &$form_state )
{

// set default values for the remainder of the form

  $minor_flag = !empty ( $form_state['values']['minor_flag'] ) ?
                         $form_state['values']['minor_flag'] : '';
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

  unset($form_state['input']['minor_flag']);
  unset($form_state['input']['name']);
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


  $form['minor_flag'] = array (
    '#type' => 'checkbox',
    '#title' => t('Check if patient is a minor.'),
    '#default_value' => $minor_flag,
  );

  $form['name'] = array (
    '#type' => 'textfield',
    '#title' => t('Guardian Name'),
    '#size' => 64,
    '#default_value' => $name,
  );

  $form['address1'] = array (
    '#type' => 'textfield',
    '#title' => t('Guardian Address'),
    '#size' => 64,
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
    '#default_value' => $city,
  );

  $form['state'] = array (
    '#type' => 'textfield',
    '#title' => t('State'),
    '#size' => 32,
    '#default_value' => $state,
  );

  $form['zip'] = array (
    '#type' => 'textfield',
    '#title' => t('Zip'),
    '#size' => 16,
    '#default_value' => $zip,
  );

  $form['home_phone'] = array (
    '#type' => 'textfield',
    '#title' => t('Home Phone'),
    '#size' => 16,
    '#default_value' => $home_phone,
  );

  $form['work_phone'] = array (
    '#type' => 'textfield',
    '#title' => t('Work Phone'),
    '#size' => 16,
    '#default_value' => $work_phone,
  );

  $form['mobile_phone'] = array (
    '#type' => 'textfield',
    '#title' => t('Mobile Phone'),
    '#size' => 16,
    '#default_value' => $mobile_phone,
  );

  $form['email'] = array (
    '#type' => 'textfield',
    '#title' => t('Email'),
    '#size' => 16,
    '#default_value' => $email,
  );

  $form['fax'] = array (
    '#type' => 'textfield',
    '#title' => t('Fax'),
    '#size' => 16,
    '#default_value' => $fax,
  );

  $form['back'] = array (
    '#type' => 'submit',
    '#value' => t('<< Back'),
    '#submit' => array('rmsallergy_add_profile_p2_back_submit' ),
    '#validate' => array('rmsallergy_add_profile_p2_back_validate' ),
  );

  $form['submit'] = array (
    '#type' => 'submit',
    '#value' => t('Next >>'),
    '#submit' => array('rmsallergy_add_profile_p2_next_submit' ),
    '#validate' => array('rmsallergy_add_profile_p2_next_validate' ),
  );


  return $form;
}


function rmsallergy_add_profile_p2_back_validate ( $form, &$form_state )
{
// nothing to validate at this point
  return $form;
}

function rmsallergy_add_profile_p2_back_submit ( $form, &$form_state )
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

function rmsallergy_add_profile_p2_next_validate ( $form, &$form_state )
{
// nothing to validate at this point
  return $form;
}

function rmsallergy_add_profile_p2_next_submit ( $form, &$form_state )
{
// values are save for each page in order to carry to subsequent pages
// and to tell FAPI how to rebuild the form

  $form_state['page_values'][2] = $form_state['values'];

  if ( !empty($form_state['page_values'][3] )) {
    $form_state['values'] = $form_state['page_values'][3];
  }

  $form_state['page_num'] = 3;
  $form_state['rebuild'] = TRUE;

  return $form;
}

?>
