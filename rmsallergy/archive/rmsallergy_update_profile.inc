<?php

/**
 * @file
 * RMS Allergy function file
 */

function rmsallergy_update_profile ( $form, &$form_state )
{
// get practice_key from current user
  global $user;
  $account = user_load ( $user->uid );
  $practice_key = field_get_items ( 'user', $account, 'field_practice_key' );
  $practice_key = $practice_key[0]['value'];


// query the database for patient records

  db_set_active ( 'rmsallergy' );
  $query = db_select ( 'profile', 'p' );
  $query->join ( 'patient', 'pa', 'p.patient_key = pa.patient_key' );
  $query
    ->fields ( 'p', array ( 'profile_key',
                            'test_date', ) )
    ->fields ( 'pa', array ( 'patient_first_name',
                            'patient_middle_name',
                            'patient_last_name',
                          ))
    ->orderBy ( 'patient_last_name', 'ASC' )
    ->orderBy ( 'test_date', 'DESC' )
    ->condition ( 'p.practice_key', $practice_key );

  $result = $query->execute();

  db_set_active ();

// build arrays to show patient table

  $options = array ();
  foreach ( $result as $record ) {

    $options [ $record->profile_key ] = array (
      'patient_last_name' => $record->patient_last_name,
      'patient_first_name' => $record->patient_first_name,
      'patient_middle_name' => $record->patient_middle_name,
      'test_date' => $record->test_date,
    );
  }

  $header = array (
    'patient_last_name' => t('Last Name'),
    'patient_first_name' => t('First Name'),
    'patient_middle_name' => t('Middle Initial'),
    'test_date' => t('Test Date'),
  );


// build form

  $form['subtitle'] = array (
    '#type' => 'item',
    '#title' => t('Select a Test Profile:'),
  );

  $form['table'] = array (
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#empty' => t('No Profiles in Database'),
    '#multiple' => FALSE,
  );


  // code for refresh button - when user selects refresh, the rest
  // of the form will be populated with patient information

  $form['refresh'] = array (
    '#type' => 'submit',
    '#value' => t('Refresh'),
    '#validate' => array ( 'rmsallergy_update_profile_refresh_validate' ),
    '#submit' => array ( 'rmsallergy_update_profile_refresh_submit' ),
  );

  $form['submit'] = array (
    '#type' => 'submit',
    '#value' => t('Update'),
    '#validate' => array ( 'rmsallergy_update_profile_validate' ),
    '#submit' => array ( 'rmsallergy_update_profile_submit' ),
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



function rmsallergy_update_profile_refresh_validate ( $form, &$form_state )
{
  $profile_key = $form_state['values']['table'];
  if ( empty ( $profile_key ) ) { 
    form_set_error ( 'Update Profile', t("Please select a test profile.") );
  }
  return $form;
}



function rmsallergy_update_profile_refresh_submit ( $form, &$form_state )
{
// the refresh routine will populate the values array with the data
// of the selected pratice

  // get the practice key from the table element

  $profile_key = $form_state['values']['table'];

  // query the practice table to retrieve the information

  db_set_active ( 'rmsallergy' );

  $query = db_select ( 'profile', 'p' );
  $query
    ->fields ( 'p', array (
      'test_date',
      'cat_pelt',
      'cat_hair',
      'dog_hair',
      'cockroach',
      'mite_farinae',
      'curvularia',
      'epidermophyton',
      'fusarium',
      'helminthosporium',
      'hormodendrum',
      'mite_petronyssi',
      'feathers_mix',
      'ap_house_dust',
      'pcn_mix',
      'horse_hair',
      'mucor',
      'pullularia',
      'rhizopus',
      'stemphylium_botrysum',
      'trichphyton_mix', ) )
    ->condition ( 'profile_key', $profile_key );

  $result = $query->execute();

  db_set_active ();

  $record = $result->fetchAssoc();

  form_set_value ( $form['test_date'], $record['test_date'], $form_state );
  form_set_value ( $form['cat_pelt'], $record['cat_pelt'], $form_state );
  form_set_value ( $form['cat_hair'], $record['cat_hair'], $form_state );
  form_set_value ( $form['dog_hair'], $record['dog_hair'], $form_state );
  form_set_value ( $form['cockroach'], $record['cockroach'], $form_state );
  form_set_value ( $form['mite_farinae'], $record['mite_farinae'], $form_state );
  form_set_value ( $form['curvularia'], $record['curvularia'], $form_state );
  form_set_value ( $form['epidermophyton'], $record['epidermophyton'], $form_state );
  form_set_value ( $form['fusarium'], $record['fusarium'], $form_state );
  form_set_value ( $form['helminthosporium'], $record['helminthosporium'], $form_state );
  form_set_value ( $form['hormodendrum'], $record['hormodendrum'], $form_state );
  form_set_value ( $form['mite_petronyssi'], $record['mite_petronyssi'], $form_state );
  form_set_value ( $form['feathers_mix'], $record['feathers_mix'], $form_state );
  form_set_value ( $form['ap_house_dust'], $record['ap_house_dust'], $form_state );
  form_set_value ( $form['pcn_mix'], $record['pcn_mix'], $form_state );
  form_set_value ( $form['horse_hair'], $record['horse_hair'], $form_state );

  form_set_value ( $form['mucor'], $record['mucor'], $form_state );
  form_set_value ( $form['pullularia'], $record['pullularia'], $form_state );
  form_set_value ( $form['rhizopus'], $record['rhizopus'], $form_state );
  form_set_value ( $form['stemphylium_botrysum'], $record['stemphylium_botrysum'], $form_state );
  form_set_value ( $form['trichphyton_mix'], $record['trichphyton_mix'], $form_state );

  $form_state['rebuild'] = TRUE;
}



function rmsallergy_update_profile_validate ( $form, &$form_state )
{
  $patient_key = $form_state['values']['table'];

  if ( empty ( $patient_key ) ) { 
    form_set_error ( 'Update Patient', t("Please select a patient.") );
  }

  return $form;
}

function rmsallergy_update_profile_submit ( $form, &$form_state )
{

// get the patient key from the table

  $profile_key = $form_state['values']['table'];


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

  $profile_key = db_update ( 'profile' )
    ->fields ( array (
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
    ->condition ( 'profile_key', $profile_key )
    ->execute();

  db_set_active ();

  drupal_set_message ( t('The profile has been updated.') );

  $form_state['rebuild'] = TRUE;
}

