<?php

/**
 * @file
 * RMS Allergy function file
 */

function rmsallergy_add_profile ( $form, &$form_state )
{
// get practice_key from current user
  global $user;
  $account = user_load ( $user->uid );
  $practice_key = field_get_items ( 'user', $account, 'field_practice_key' );
  $practice_key = $practice_key[0]['value'];


// query the database for patient records

  db_set_active ( 'rmsallergy' );
  $query = db_select ( 'patient', 'p' );
  $query
    ->fields ( 'p', array ( 'patient_key',
                            'patient_first_name',
                            'patient_middle_name',
                            'patient_last_name',
                          ))
    ->orderBy ( 'patient_last_name', 'ASC' )
    ->condition ( 'practice_key', $practice_key );

  $result = $query->execute();

  db_set_active ();

// build arrays to show patient table

  $options = array ();
  foreach ( $result as $record ) {

    $options [ $record->patient_key ] = array (
      'patient_last_name' => $record->patient_last_name,
      'patient_first_name' => $record->patient_first_name,
      'patient_middle_name' => $record->patient_middle_name,
    );
  }

  $header = array (
    'patient_last_name' => t('Last Name'),
    'patient_first_name' => t('First Name'),
    'patient_middle_name' => t('Middle Initial'),
  );


// build form

  $form['subtitle'] = array (
    '#type' => 'item',
    '#title' => t('Select a Patient:'),
  );

  $form['table'] = array (
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#empty' => t('No Patients in Database'),
    '#multiple' => FALSE,
  );


  // code for refresh button - when user selects refresh, the rest
  // of the form will be populated with patient information

  $form['submit'] = array (
    '#type' => 'submit',
    '#value' => t('Submit'),
    '#validate' => array ( 'rmsallergy_add_profile_validate' ),
    '#submit' => array ( 'rmsallergy_add_profile_submit' ),
  );



// set default values for the remainder of the form

  $test_date = !empty ( $form_state['values']['test_date'] ) ?
                        $form_state['values']['test_date'] : '';

  $cat_pelt = !empty ( $form_state['values']['cat_pelt'] ) ?
                       $form_state['values']['cat_pelt'] : '';
  $cat_hair = !empty ( $form_state['values']['cat_hair'] ) ?
                       $form_state['values']['cat_hair'] : '';
  $dog_hair = !empty ( $form_state['values']['dog_hair'] ) ?
                       $form_state['values']['dog_hair'] : '';
  $cockroach = !empty ( $form_state['values']['cockroach'] ) ?
                        $form_state['values']['cockroach'] : '';
  $mite_farinae = !empty ( $form_state['values']['mite_farinae'] ) ?
                           $form_state['values']['mite_farinae'] : '';
  $curvularia = !empty ( $form_state['values']['curvularia'] ) ?
                         $form_state['values']['curvularia'] : '';
  $epidermophyton = !empty ( $form_state['values']['epidermophyton'] ) ?
                             $form_state['values']['epidermophyton'] : '';
  $fusarium = !empty ( $form_state['values']['fusarium'] ) ?
                       $form_state['values']['fusarium'] : '';
  $helminthosporium = !empty ( $form_state['values']['helminthosporium'] ) ?
                               $form_state['values']['helminthosporium'] : '';
  $hormodendrum = !empty ( $form_state['values']['hormodendrum'] ) ?
                           $form_state['values']['hormodendrum'] : '';

  $mite_petronyssi = !empty ( $form_state['values']['mite_petronyssi'] ) ?
                              $form_state['values']['mite_petronyssi'] : '';
  $feathers_mix = !empty ( $form_state['values']['feathers_mix'] ) ?
                           $form_state['values']['feathers_mix'] : '';
  $ap_house_dust = !empty ( $form_state['values']['ap_house_dust'] ) ?
                            $form_state['values']['ap_house_dust'] : '';
  $pcn_mix = !empty ( $form_state['values']['pcn_mix'] ) ?
                      $form_state['values']['pcn_mix'] : '';
  $horse_hair = !empty ( $form_state['values']['horse_hair'] ) ?
                         $form_state['values']['horse_hair'] : '';
  $mucor = !empty ( $form_state['values']['mucor'] ) ?
                    $form_state['values']['mucor'] : '';
  $pullularia = !empty ( $form_state['values']['pullularia'] ) ?
                       $form_state['values']['pullularia'] : '';
  $rhizopus = !empty ( $form_state['values']['rhizopus'] ) ?
                       $form_state['values']['rhizopus'] : '';
  $stemphylium_botrysum = !empty ( $form_state['values']['stemphylium_botrysum'] ) ?
                                   $form_state['values']['stemphylium_botrysum'] : '';
  $trichphyton_mix = !empty ( $form_state['values']['trichphyton_mix'] ) ?
                              $form_state['values']['trichphyton_mix'] : '';

  $lambs_quarter = !empty ( $form_state['values']['lambs_quarter'] ) ?
                            $form_state['values']['lambs_quarter'] : '';
  $palintain = !empty ( $form_state['values']['palintain'] ) ?
                        $form_state['values']['palintain'] : '';
  $ragweed_mix_gs = !empty ( $form_state['values']['ragweed_mix_gs'] ) ?
                             $form_state['values']['ragweed_mix_gs'] : '';
  $marchelder = !empty ( $form_state['values']['marchelder'] ) ?
                         $form_state['values']['marchelder'] : '';
  $dog_fennel = !empty ( $form_state['values']['dog_fennel'] ) ?
                           $form_state['values']['dog_fennel'] : '';
  $elm_american = !empty ( $form_state['values']['elm_american'] ) ?
                           $form_state['values']['elm_american'] : '';
  $oak_mix = !empty ( $form_state['values']['oak_mix'] ) ?
                      $form_state['values']['oak_mix'] : '';
  $pecan_tree = !empty ( $form_state['values']['pecan_tree'] ) ?
                         $form_state['values']['pecan_tree'] : '';
  $sweet_gum = !empty ( $form_state['values']['sweet_gum'] ) ?
                        $form_state['values']['sweet_gum'] : '';
  $walnut_black = !empty ( $form_state['values']['walnut_black'] ) ?
                           $form_state['values']['walnut_black'] : '';


// unset prior values so the form rebuild correctly

  unset($form_state['input']['test_date']);

  unset($form_state['input']['cat_pelt']);
  unset($form_state['input']['cat_hair']);
  unset($form_state['input']['dog_hair']);
  unset($form_state['input']['cockroach']);
  unset($form_state['input']['mite_farinae']);
  unset($form_state['input']['curvularia']);
  unset($form_state['input']['epidermophyton']);
  unset($form_state['input']['fusarium']);
  unset($form_state['input']['helminthosporium']);
  unset($form_state['input']['hormodendrum']);

  unset($form_state['input']['mite_petronyssi']);
  unset($form_state['input']['feathers_mix']);
  unset($form_state['input']['ap_house_dust']);
  unset($form_state['input']['pcn_mix']);
  unset($form_state['input']['horse_hair']);
  unset($form_state['input']['mucor']);
  unset($form_state['input']['pullularia']);
  unset($form_state['input']['rhizopus']);
  unset($form_state['input']['stemphylium_botrysum']);
  unset($form_state['input']['trichphyton_mix']);

  unset($form_state['input']['lambs_quarter']);
  unset($form_state['input']['palintain']);
  unset($form_state['input']['ragweed_mix_gs']);
  unset($form_state['input']['marchelder']);
  unset($form_state['input']['dog_fennel']);
  unset($form_state['input']['elm_american']);
  unset($form_state['input']['oak_mix']);
  unset($form_state['input']['pecan_tree']);
  unset($form_state['input']['sweet_gum']);
  unset($form_state['input']['walnut_black']);


// create form

  $form['test_date'] = array (
    '#type' => 'textfield',
    '#title' => t('Test Date'),
    '#size' => 16,
   '#default_value' => $test_date,
  );

//  $form['p3'] = array (
//    '#type' => 'fieldset',
//    '#title' => t('Antigen Panel #3'),
//    '#collapsible' => TRUE,
//    '#collapsed' => TRUE,
//    '#prefix' => '<table>',
//    '#suffix' => '</table>',
//  );


  $form['antigen_p3'] = array (
    '#type' => 'item',
    '#title' => t('Antigen Panel #3'),
    '#suffix' => '<table>',
  );

  $form['cat_pelt'] = array (
    '#type' => 'textfield',
    '#title' => t('Cat Pelt'),
    '#size' => 16,
    '#default_value' => $cat_pelt,
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['cat_hair'] = array (
    '#type' => 'textfield',
    '#title' => t('Cat Hair'),
    '#size' => 16,
    '#default_value' => $cat_hair,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['dog_hair'] = array (
    '#type' => 'textfield',
    '#title' => t('Dog Hair'),
    '#size' => 16,
    '#default_value' => $dog_hair,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['cockroach'] = array (
    '#type' => 'textfield',
    '#title' => t('Cockroach'),
    '#size' => 16,
    '#default_value' => $cockroach,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['mite_farinae'] = array (
    '#type' => 'textfield',
    '#title' => t('Mite D. Farinae'),
    '#size' => 16,
    '#default_value' => $mite_farinae,
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );

  $form['curvularia'] = array (
    '#type' => 'textfield',
    '#title' => t('Curvularia'),
    '#size' => 16,
    '#default_value' => $curvularia,
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['epidermophyton'] = array (
    '#type' => 'textfield',
    '#title' => t('Epidermophyton'),
    '#size' => 16,
    '#default_value' => $epidermophyton,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['fusarium'] = array (
    '#type' => 'textfield',
    '#title' => t('fusarium'),
    '#size' => 16,
    '#default_value' => $fusarium,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['helminthosporium'] = array (
    '#type' => 'textfield',
    '#title' => t('Helminthosporium'),
    '#size' => 16,
    '#default_value' => $helminthosporium,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['hormodendrum'] = array (
    '#type' => 'textfield',
    '#title' => t('Hormodendrum'),
    '#size' => 16,
    '#default_value' => $hormodendrum,
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );

  $form['antigen_p4'] = array (
    '#type' => 'item',
    '#title' => t('Antigen Panel #4'),
    '#prefix' => '</table><hr><table>',
  );

  $form['mite_petronyssi'] = array (
    '#type' => 'textfield',
    '#title' => t('Mite D. petronyssi'),
    '#size' => 16,
    '#default_value' => $mite_petronyssi,
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['feathers_mix'] = array (
    '#type' => 'textfield',
    '#title' => t('Feathers Mix'),
    '#size' => 16,
    '#default_value' => $feathers_mix,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['ap_house_dust'] = array (
    '#type' => 'textfield',
    '#title' => t('AP House Dust'),
    '#size' => 16,
    '#default_value' => $ap_house_dust,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['pcn_mix'] = array (
    '#type' => 'textfield',
    '#title' => t('PCN Mix'),
    '#size' => 16,
    '#default_value' => $pcn_mix,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['horse_hair'] = array (
    '#type' => 'textfield',
    '#title' => t('Horse Hair'),
    '#size' => 16,
    '#default_value' => $horse_hair,
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );

  $form['mucor'] = array (
    '#type' => 'textfield',
    '#title' => t('Mucor'),
    '#size' => 16,
    '#default_value' => $mucor,
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['pullularia'] = array (
    '#type' => 'textfield',
    '#title' => t('Pullularia'),
    '#size' => 16,
    '#default_value' => $pullularia,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['rhizopus'] = array (
    '#type' => 'textfield',
    '#title' => t('Rhizopus'),
    '#size' => 16,
    '#default_value' => $rhizopus,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['stemphylium_botrysum'] = array (
    '#type' => 'textfield',
    '#title' => t('Stemphylium Botrysum'),
    '#size' => 16,
    '#default_value' => $stemphylium_botrysum,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['trichphyton_mix'] = array (
    '#type' => 'textfield',
    '#title' => t('Trichphyton'),
    '#size' => 16,
    '#default_value' => $trichphyton_mix,
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );

  $form['antigen_p2'] = array (
    '#type' => 'item',
    '#title' => t('Antigen Panel #2'),
    '#prefix' => '</table><hr>',
  );

  return $form;
}


function rmsallergy_add_profile_validate ( $form, &$form_state )
{
  $patient_key = $form_state['values']['table'];

  if ( empty ( $patient_key ) ) { 
    form_set_error ( 'Update Patient', t("Please select a patient.") );
  }

  return $form;
}

/*
function rmsallergy_update_patient_refresh_submit ( $form, &$form_state )
{
// the refresh routine will populate the values array with the data
// of the selected pratice

  // get the practice key from the table element

  $patient_key = $form_state['values']['table'];


  // query the practice table to retrieve the information

  db_set_active ( 'rmsallergy' );

  $query = db_select ( 'patient', 'p' );
  $query
    ->fields ( 'p', array (
      'patient_first_name',
      'patient_middle_name',
      'patient_last_name',
      'patient_ssn',
      'patient_dob',
      'patient_gender',
      'patient_address1',
      'patient_address2',
      'patient_city',
      'patient_state',
      'patient_zip',
      'patient_home_phone',
      'patient_work_phone',
      'patient_mobile_phone',
      'patient_email',
      'patient_fax',
      'minor_flag',
      'guardian_name',
      'guardian_address1',
      'guardian_address2',
      'guardian_city',
      'guardian_state',
      'guardian_zip',
      'guardian_home_phone',
      'guardian_work_phone',
      'guardian_mobile_phone',
      'guardian_email',
      'guardian_fax',
      'primary_flag',
      'primary_carrier',
      'primary_group_number',
      'primary_policy_holder_name',
      'primary_policy_holder_ssn',
      'primary_policy_holder_dob',
      'secondary_flag',
      'secondary_carrier',
      'secondary_group_number',
      'secondary_policy_holder_name',
      'secondary_policy_holder_ssn',
      'secondary_policy_holder_dob'))
    ->condition ( 'patient_key', $patient_key );

  $result = $query->execute();

  db_set_active ();

  $record = $result->fetchAssoc();

  form_set_value ( $form['p']['first_name'], $record['patient_first_name'], $form_state );
  form_set_value ( $form['p']['middle_name'], $record['patient_middle_name'], $form_state );
  form_set_value ( $form['p']['last_name'], $record['patient_last_name'], $form_state );
  form_set_value ( $form['p']['ssn'], $record['patient_ssn'], $form_state );
  form_set_value ( $form['p']['dob'], $record['patient_dob'], $form_state );
  form_set_value ( $form['p']['gender'], $record['patient_gender'], $form_state );
  form_set_value ( $form['p']['address1'], $record['patient_address1'], $form_state );
  form_set_value ( $form['p']['address2'], $record['patient_address2'], $form_state );
  form_set_value ( $form['p']['city'], $record['patient_city'], $form_state );
  form_set_value ( $form['p']['state'], $record['patient_state'], $form_state );
  form_set_value ( $form['p']['zip'], $record['patient_zip'], $form_state );
  form_set_value ( $form['p']['home_phone'], $record['patient_home_phone'], $form_state );
  form_set_value ( $form['p']['work_phone'], $record['patient_work_phone'], $form_state );
  form_set_value ( $form['p']['mobile_phone'], $record['patient_mobile_phone'], $form_state );
  form_set_value ( $form['p']['email'], $record['patient_email'], $form_state );
  form_set_value ( $form['p']['fax'], $record['patient_fax'], $form_state );

  form_set_value ( $form['g']['minor_flag'], $record['minor_flag'], $form_state );
  form_set_value ( $form['g']['gname'], $record['guardian_name'], $form_state );
  form_set_value ( $form['g']['gaddress1'], $record['guardian_address1'], $form_state );
  form_set_value ( $form['g']['gaddress2'], $record['guardian_address2'], $form_state );
  form_set_value ( $form['g']['gcity'], $record['guardian_city'], $form_state );
  form_set_value ( $form['g']['gstate'], $record['guardian_state'], $form_state );
  form_set_value ( $form['g']['gzip'], $record['guardian_zip'], $form_state );
  form_set_value ( $form['g']['ghome_phone'], $record['guardian_home_phone'], $form_state );
  form_set_value ( $form['g']['gwork_phone'], $record['guardian_work_phone'], $form_state );
  form_set_value ( $form['g']['gmobile_phone'], $record['guardian_mobile_phone'], $form_state );
  form_set_value ( $form['g']['gemail'], $record['guardian_email'], $form_state );
  form_set_value ( $form['g']['gfax'], $record['guardian_fax'], $form_state );

  form_set_value ( $form['i']['primary_flag'], $record['primary_flag'], $form_state );
  form_set_value ( $form['i']['primary_carrier'], $record['primary_carrier'], $form_state );
  form_set_value ( $form['i']['primary_group_number'], $record['primary_group_number'], $form_state );
  form_set_value ( $form['i']['primary_holder_name'], $record['primary_policy_holder_name'], $form_state );
  form_set_value ( $form['i']['primary_holder_ssn'], $record['primary_policy_holder_ssn'], $form_state );
  form_set_value ( $form['i']['primary_holder_dob'], $record['primary_policy_holder_dob'], $form_state );
  form_set_value ( $form['i']['secondary_flag'], $record['secondary_flag'], $form_state );
  form_set_value ( $form['i']['secondary_carrier'], $record['secondary_carrier'], $form_state );
  form_set_value ( $form['i']['secondary_group_number'], $record['secondary_group_number'], $form_state );
  form_set_value ( $form['i']['secondary_holder_name'], $record['secondary_policy_holder_name'], $form_state );
  form_set_value ( $form['i']['secondary_holder_ssn'], $record['secondary_policy_holder_ssn'], $form_state );
  form_set_value ( $form['i']['secondary_holder_dob'], $record['secondary_policy_holder_dob'], $form_state );

  $form_state['rebuild'] = TRUE;
}
*/



function rmsallergy_add_profile_submit ( $form, &$form_state )
{
// get the practice key from the user

  global $user;
  $account = user_load ( $user->uid );
  $practice_key = field_get_items ( 'user', $account, 'field_practice_key' );
  $practice_key = $practice_key[0]['value'];


// get the patient key from the table

  $patient_key = $form_state['values']['table'];


// get the data out of the form

  $test_date   = $form_state['values']['test_date'];

  $cat_pelt         = $form_state['values']['cat_pelt'];
  $cat_hair         = $form_state['values']['cat_hair'];
  $dog_hair         = $form_state['values']['dog_hair'];
  $cockroach        = $form_state['values']['cockroach'];
  $mite_farinae     = $form_state['values']['mite_farinae'];
  $curvularia       = $form_state['values']['curvularia'];
  $epidermophyton   = $form_state['values']['epidermophyton'];
  $fusarium         = $form_state['values']['fusarium'];
  $helminthosporium = $form_state['values']['helminthosporium'];
  $hormodendrum     = $form_state['values']['hormodendrum'];

  $mite_petronyssi      = $form_state['values']['mite_petronyssi'];
  $feathers_mix         = $form_state['values']['feathers_mix'];
  $ap_house_dust        = $form_state['values']['ap_house_dust'];
  $pcn_mix              = $form_state['values']['pcn_mix'];
  $horse_hair           = $form_state['values']['horse_hair'];
  $mucor                = $form_state['values']['mucor'];
  $pullularia           = $form_state['values']['pullularia'];
  $rhizopus             = $form_state['values']['rhizopus'];
  $stemphylium_botrysum = $form_state['values']['stemphylium_botrysum'];
  $trichphyton_mix      = $form_state['values']['trichphyton_mix'];


  // set active database and update practice and contact databases

  db_set_active ( 'rmsallergy' );

  $profile_key = db_insert ( 'profile' )
    ->fields ( array (
      'practice_key' => $practice_key,
      'patient_key' => $patient_key,
      'test_date' => $test_date,
      'cat_pelt' => $cat_pelt,
      'cat_hair' => $cat_hair,
      'dog_hair' => $dog_hair,
      'cockroach' => $cockroach,
      'mite_farinae' => $mite_farinae,
      'curvularia' => $curvularia,
      'epidermophyton' => $epidermophyton,
      'fusarium' => $fusarium,
      'helminthosporium' => $helminthosporium,
      'hormodendrum' => $hormodendrum,
      'mite_petronyssi' => $mite_petronyssi,
      'feathers_mix' => $feathers_mix,
      'ap_house_dust' => $ap_house_dust,
      'pcn_mix' => $pcn_mix,
      'horse_hair' => $horse_hair,
      'mucor' => $mucor,
      'pullularia' => $pullularia,
      'rhizopus' => $rhizopus,
      'stemphylium_botrysum' => $stemphylium_botrysum,
      'trichphyton_mix' => $trichphyton_mix,
    ))
    ->execute();

  db_set_active ();

  drupal_set_message ( t('The patient has been updated.') );

  $form_state['rebuild'] = TRUE;
}

