<?php

/**
 * @file
 * RMS Allergy function file
 */

function rmsallergy_view_incoming_p3 ( $form, &$form_state )
{

// get practice_key from current user
  global $user;
  $account = user_load ( $user->uid );
  $practice_key = field_get_items ( 'user', $account, 'field_practice_key' );
  $practice_key = $practice_key[0]['value'];


// get referral key from previous form page

  $referral_key = $form_state['page_values'][1]['table'];

  if ( empty ( $referral_key ) ) {
    form_set_error ( 'View Allergy Test', t('Page 2 - Key not found') );
  }


// query the database to get patient record

  db_set_active ( 'rmsallergy' );
  $query = db_select ( 'referral', 'r' );
  $query->join ( 'profile', 'p', 'r.profile_key = p.profile_key' );
  $query->join ( 'patient', 'pa', 'p.patient_key = pa.patient_key' );
  $query
    ->fields ( 'p', array ( 'profile_key',
                            'test_date_month',
                            'test_date_day',
                            'test_date_year',
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
                            'trichphyton_mix',
                            'lambs_quarter',
                            'palintain',
                            'ragweed_mix_gs',
                            'marchelder',
                            'dog_fennel',
                            'elm_american',
                            'oak_mix',
                            'pecan_tree',
                            'sweet_gum',
                            'walnut_black',
                            'alternariatenuis',
                            'aspergillus_fumigatus',
                            'botrytis_cinerea',
                            'candida',
                            'cephalosporium',
                            'pine_mix',
                            'sycamore_american',
                            'careless_pigweed',
                            'cocklebur',
                            'dock_sorrel',
                            'bluegrass_kentucky',
                            'corn_cultivated',
                            'oats_common',
                            'orchard_grass',
                            'redtop',
                            'positive_histamine',
                            'negative_glycerine',
                            'phenol',
                            'bahia_grass',
                            'johnson_grass',
                            'sweet_vernalgrass',
                            'boxelder_maple',
                            'cedar_mountian',
                            'common_privet',
                            'cottonwood',
                            'bermuda_grass',
                            'meadow_fescue',
                            'rye_grass',
                            'timothy',
                            'brome_smooth',
                            'casein',
                            'milk_cow',
                            'egg_chicken_white',
                            'peanut',
                            'soybean',
                            'pecan',
                            'shellfish_mix',
                            'shrimp',
      ) )
    ->fields ( 'pa', array ( 'patient_first_name',
                             'patient_middle_name',
                             'patient_last_name',
                             'patient_ssn1',
                             'patient_ssn2',
                             'patient_ssn3',
                             'patient_dob_month',
                             'patient_dob_day',
                             'patient_dob_year',
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
      ) )
    ->condition ( 'r.referral_key', $referral_key );

  $result = $query->execute();

  db_set_active ();

// check for length of array in record
  if ( count($result) != 1 ) {
    form_set_error ( 'View Allergy Test', t('Error searching on patient.') );
  }

  $record = $result->fetchAssoc();

//drupal_set_message ( print_r ( $result, TRUE ) );
//drupal_set_message ( print_r ( $record, TRUE ) );


// set patient record

  $name = $record['patient_last_name'] . ', ' .  $record['patient_first_name'];
  if ( ! empty ( $record['patient_middle_name'] ) ) {
    $name = $name . ' ' . substr ( $record['patient_middle_name'], 0, 1);
  }

  $gender = $record['patient_gender'];

  $ssn = $record['patient_ssn1'].'-'.$record['patient_ssn2'].'-'.$record['patient_ssn3'];

  $dob = $record['patient_dob_month'] . '/' .
         $record['patient_dob_day']   . '/' .
         $record['patient_dob_year'];

  $address1 = $record['patient_address1'];
  $address2 = $record['patient_address2'];
  $address3 = $record['patient_city'] . ', ' . 
              $record['patient_state'] . ' ' .
              $record['patient_zip'];

  $home_phone = $record['patient_home_phone'];
  $work_phone = $record['patient_work_phone'];
  $mobile_phone = $record['patient_mobile_phone'];

  $email = $record['patient_email'];
  $fax = $record['patient_fax'];



  $minor_flag = $record['minor_flag'];

  $g_name = $record['guardian_name'];

  $g_address1 = $record['guardian_address1'];
  $g_address2 = $record['guardian_address2'];
  $g_address3 = $record['guardian_city'] . ', ' . 
              $record['guardian_state'] . ' ' .
              $record['guardian_zip'];

  $g_home_phone = $record['guardian_home_phone'];
  $g_work_phone = $record['guardian_work_phone'];
  $g_mobile_phone = $record['guardian_mobile_phone'];

  $g_email = $record['guardian_email'];
  $g_fax = $record['guardian_fax'];


// set profile record

  $test_date = $record['test_date_month'] . '/' .
               $record['test_date_day']   . '/' .
               $record['test_date_year'];

  $cat_pelt = $record['cat_pelt'];
  $cat_hair = $record['cat_hair'];
  $dog_hair = $record['dog_hair'];
  $cockroach = $record['cockroach'];
  $mite_farinae = $record['mite_farinae'];
  $curvularia = $record['curvularia'];
  $epidermophyton = $record['epidermophyton'];
  $fusarium = $record['fusarium'];
  $helminthosporium = $record['helminthosporium'];
  $hormodendrum = $record['hormodendrum'];
  $mite_petronyssi = $record['mite_petronyssi'];
  $feathers_mix = $record['feathers_mix'];
  $ap_house_dust = $record['ap_house_dust'];
  $pcn_mix = $record['pcn_mix'];
  $horse_hair = $record['horse_hair'];
  $mucor = $record['mucor'];
  $pullularia = $record['pullularia'];
  $rhizopus = $record['rhizopus'];
  $stemphylium_botrysum = $record['stemphylium_botrysum'];
  $trichphyton_mix = $record['trichphyton_mix'];
  $lambs_quarter = $record['lambs_quarter'];
  $palintain = $record['palintain'];
  $ragweed_mix_gs = $record['ragweed_mix_gs'];
  $marchelder = $record['marchelder'];
  $dog_fennel = $record['dog_fennel'];
  $elm_american = $record['elm_american'];
  $oak_mix = $record['oak_mix'];
  $pecan_tree = $record['pecan_tree'];
  $sweet_gum = $record['sweet_gum'];
  $walnut_black = $record['walnut_black'];
  $alternariatenuis = $record['alternariatenuis'];
  $aspergillus_fumigatus = $record['aspergillus_fumigatus'];
  $botrytis_cinerea = $record['botrytis_cinerea'];
  $candida = $record['candida'];
  $cephalosporium = $record['cephalosporium'];
  $pine_mix = $record['pine_mix'];
  $sycamore_american = $record['sycamore_american'];
  $careless_pigweed = $record['careless_pigweed'];
  $cocklebur = $record['cocklebur'];
  $dock_sorrel = $record['dock_sorrel'];
  $bluegrass_kentucky = $record['bluegrass_kentucky'];
  $corn_cultivated = $record['corn_cultivated'];
  $oats_common = $record['oats_common'];
  $orchard_grass = $record['orchard_grass'];
  $redtop = $record['redtop'];
  $positive_histamine = $record['positive_histamine'];
  $negative_glycerine = $record['negative_glycerine'];
  $phenol = $record['phenol'];
  $bahia_grass = $record['bahia_grass'];
  $johnson_grass = $record['johnson_grass'];
  $sweet_vernalgrass = $record['sweet_vernalgrass'];
  $boxelder_maple = $record['boxelder_maple'];
  $cedar_mountian = $record['cedar_mountian'];
  $common_privet = $record['common_privet'];
  $cottonwood = $record['cottonwood'];
  $bermuda_grass = $record['bermuda_grass'];
  $meadow_fescue = $record['meadow_fescue'];
  $rye_grass = $record['rye_grass'];
  $timothy = $record['timothy'];
  $brome_smooth = $record['brome_smooth'];
  $casein = $record['casein'];
  $milk_cow = $record['milk_cow'];
  $egg_chicken_white = $record['egg_chicken_white'];
  $peanut = $record['peanut'];
  $soybean = $record['soybean'];
  $pecan = $record['pecan'];
  $shellfish_mix = $record['shellfish_mix'];
  $shrimp = $record['shrimp'];



// display results

  $form['1'] = array (
    '#type' => 'item',
    '#title' => t('Patient Information'),
    '#prefix' => '',
    '#suffix' => '<table>',
  );

  $form['1a'] = array (
    '#type' => 'item',
    '#title' => t('Name:'),
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['1b'] = array (
    '#type' => 'item',
    '#title' => t($name),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );


  $form['1c'] = array (
    '#type' => 'item',
    '#title' => t('Gender: '),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['1d'] = array (
    '#type' => 'item',
    '#title' => t($gender),
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );



  $form['2a'] = array (
    '#type' => 'item',
    '#title' => t('SSN:'),
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['2b'] = array (
    '#type' => 'item',
    '#title' => t($ssn),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['2c'] = array (
    '#type' => 'item',
    '#title' => t('DOB:'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['2d'] = array (
    '#type' => 'item',
    '#title' => t($dob),
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );



  $form['3a'] = array (
    '#type' => 'item',
    '#title' => t('Address:'),
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['3b'] = array (
    '#type' => 'item',
    '#title' => t($address1),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['3c'] = array (
    '#type' => 'item',
    '#title' => t('Home Phone:'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['3d'] = array (
    '#type' => 'item',
    '#title' => t($home_phone),
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );



  $form['4a'] = array (
    '#type' => 'item',
    '#title' => t(''),
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['4b'] = array (
    '#type' => 'item',
    '#title' => t($address2),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['4c'] = array (
    '#type' => 'item',
    '#title' => t('Work Phone:'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['4d'] = array (
    '#type' => 'item',
    '#title' => t($work_phone),
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );



  $form['5a'] = array (
    '#type' => 'item',
    '#title' => t(''),
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['5b'] = array (
    '#type' => 'item',
    '#title' => t($address3),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['5c'] = array (
    '#type' => 'item',
    '#title' => t('Mobile Phone:'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['5d'] = array (
    '#type' => 'item',
    '#title' => t($mobile_phone),
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );



  $form['6a'] = array (
    '#type' => 'item',
    '#title' => t('Email:'),
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['6b'] = array (
    '#type' => 'item',
    '#title' => t($email),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['6c'] = array (
    '#type' => 'item',
    '#title' => t('Fax:'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['6d'] = array (
    '#type' => 'item',
    '#title' => t($fax),
    '#prefix' => '<td>',
    '#suffix' => '</td></tr></table>',
  );





  $form['7'] = array (
    '#type' => 'item',
    '#title' => t('Guardian Information (Optional)'),
    '#prefix' => '',
    '#suffix' => '<table>',
  );

  if ( $minor_flag )
  {
    $form['7a'] = array (
      '#type' => 'item',
      '#title' => t('Name:'),
      '#prefix' => '<tr><td>',
      '#suffix' => '</td>',
    );

    $form['7b'] = array (
      '#type' => 'item',
      '#title' => t($g_name),
      '#prefix' => '<td>',
      '#suffix' => '</td>',
    );

    $form['7c'] = array (
      '#type' => 'item',
      '#title' => t(''),
      '#prefix' => '<td>',
      '#suffix' => '</td>',
    );

    $form['7d'] = array (
      '#type' => 'item',
      '#title' => t(''),
      '#prefix' => '<td>',
      '#suffix' => '</td></tr>',
    );



    $form['9a'] = array (
      '#type' => 'item',
      '#title' => t('Address:'),
      '#prefix' => '<tr><td>',
      '#suffix' => '</td>',
    );

    $form['9b'] = array (
      '#type' => 'item',
      '#title' => t($g_address1),
      '#prefix' => '<td>',
      '#suffix' => '</td>',
    );

    $form['9c'] = array (
      '#type' => 'item',
      '#title' => t('Home Phone:'),
      '#prefix' => '<td>',
      '#suffix' => '</td>',
    );

    $form['9d'] = array (
      '#type' => 'item',
      '#title' => t($g_home_phone),
      '#prefix' => '<td>',
      '#suffix' => '</td></tr>',
    );



    $form['10a'] = array (
      '#type' => 'item',
      '#title' => t(''),
      '#prefix' => '<tr><td>',
      '#suffix' => '</td>',
    );

    $form['10b'] = array (
      '#type' => 'item',
      '#title' => t($g_address2),
      '#prefix' => '<td>',
      '#suffix' => '</td>',
    );

    $form['10c'] = array (
      '#type' => 'item',
      '#title' => t('Work Phone:'),
      '#prefix' => '<td>',
      '#suffix' => '</td>',
    );

    $form['10d'] = array (
      '#type' => 'item',
      '#title' => t($g_work_phone),
      '#prefix' => '<td>',
      '#suffix' => '</td></tr>',
    );



    $form['11a'] = array (
      '#type' => 'item',
      '#title' => t(''),
      '#prefix' => '<tr><td>',
      '#suffix' => '</td>',
    );

    $form['11b'] = array (
      '#type' => 'item',
      '#title' => t($g_address3),
      '#prefix' => '<td>',
      '#suffix' => '</td>',
    );

    $form['11c'] = array (
      '#type' => 'item',
      '#title' => t('Mobile Phone:'),
      '#prefix' => '<td>',
      '#suffix' => '</td>',
    );

    $form['11d'] = array (
      '#type' => 'item',
      '#title' => t($g_mobile_phone),
      '#prefix' => '<td>',
      '#suffix' => '</td></tr>',
    );



    $form['12a'] = array (
      '#type' => 'item',
      '#title' => t('Email:'),
      '#prefix' => '<tr><td>',
      '#suffix' => '</td>',
    );

    $form['12b'] = array (
      '#type' => 'item',
      '#title' => t($g_email),
      '#prefix' => '<td>',
      '#suffix' => '</td>',
    );

    $form['12c'] = array (
      '#type' => 'item',
      '#title' => t('Fax:'),
      '#prefix' => '<td>',
      '#suffix' => '</td>',
    );

    $form['12d'] = array (
      '#type' => 'item',
      '#title' => t($g_fax),
      '#prefix' => '<td>',
      '#suffix' => '</td></tr></table>',
    );

  } else {

    $form['7a'] = array (
      '#type' => 'item',
      '#title' => t('Not applicable'),
      '#prefix' => '<tr><td>',
      '#suffix' => '<td><tr></table>',
    );
  }


  $form['13a'] = array (
    '#type' => 'item',
    '#title' => t('Allergy Test Results'),
    '#prefix' => '',
    '#suffix' => '<table>',
  );

  $form['13b'] = array (
    '#type' => 'item',
    '#title' => t('Test Date:'),
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['13c'] = array (
    '#type' => 'item',
    '#title' => t($test_date),
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );




  $form['antigen_p3'] = array (
    '#type' => 'item',
    '#title' => t('Antigen Panel #3'),
    '#prefix' => '<tr><td>',
    '#suffix' => '</td></tr>',
  );

  $form['cat_pelt'] = array (
    '#type' => 'item',
    '#title' => t('Cat Pelt'),
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['p3_cat_pelt'] = array (
    '#type' => 'item',
    '#title' => t($cat_pelt),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['cat_hair'] = array (
    '#type' => 'item',
    '#title' => t('Cat Hair'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_cat_hair'] = array (
    '#type' => 'item',
    '#title' => t($cat_hair),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['dog_hair'] = array (
    '#type' => 'item',
    '#title' => t('Dog Hair'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_dog_hair'] = array (
    '#type' => 'item',
    '#title' => t($dog_hair),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['cockroach'] = array (
    '#type' => 'item',
    '#title' => t('Cockroach'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_cockroach'] = array (
    '#type' => 'item',
    '#title' => t($cockroach),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['mite_farinae'] = array (
    '#type' => 'item',
    '#title' => t('Mite D. Farinae'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_mite_farinae'] = array (
    '#type' => 'item',
    '#title' => t($mite_farinae),
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );

  $form['curvularia'] = array (
    '#type' => 'item',
    '#title' => t('Curvularia'),
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['p3_curvularia'] = array (
    '#type' => 'item',
    '#title' => t($curvularia),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['epidermophyton'] = array (
    '#type' => 'item',
    '#title' => t('Epidermophyton'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_epidermophyton'] = array (
    '#type' => 'item',
    '#title' => t($epidermophyton),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['fusarium'] = array (
    '#type' => 'item',
    '#title' => t('fusarium'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_fusarium'] = array (
    '#type' => 'item',
    '#title' => t($fusarium),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['helminthosporium'] = array (
    '#type' => 'item',
    '#title' => t('Helminthosporium'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_helminthosporium'] = array (
    '#type' => 'item',
    '#title' => t($helminthosporium),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['hormodendrum'] = array (
    '#type' => 'item',
    '#title' => t('Hormodendrum'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_hormodendrum'] = array (
    '#type' => 'item',
    '#title' => t($hormodendrum),
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );







  $form['antigen_p4'] = array (
    '#type' => 'item',
    '#title' => t('Antigen Panel #4'),
    '#prefix' => '<tr><td>',
    '#suffix' => '</td></tr>',
  );

  $form['mite_petronyssi'] = array (
    '#type' => 'item',
    '#title' => t('Mite D. petronyssi'),
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['p3_mite_petronyssi'] = array (
    '#type' => 'item',
    '#title' => t($mite_petronyssi),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['feathers_mix'] = array (
    '#type' => 'item',
    '#title' => t('Feathers Mix'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_feathers_mix'] = array (
    '#type' => 'item',
    '#title' => t($feathers_mix),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['ap_house_dust'] = array (
    '#type' => 'item',
    '#title' => t('AP House Dust'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_ap_house_dust'] = array (
    '#type' => 'item',
    '#title' => t($ap_house_dust),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['pcn_mix'] = array (
    '#type' => 'item',
    '#title' => t('PCN Mix'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_pcn_mix'] = array (
    '#type' => 'item',
    '#title' => t($pcn_mix),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['horse_hair'] = array (
    '#type' => 'item',
    '#title' => t('Horse Hair'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_horse_hair'] = array (
    '#type' => 'item',
    '#title' => t($horse_hair),
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );

  $form['mucor'] = array (
    '#type' => 'item',
    '#title' => t('Mucor'),
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['p3_mucor'] = array (
    '#type' => 'item',
    '#title' => t($mucor),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['pullularia'] = array (
    '#type' => 'item',
    '#title' => t('Pullularia'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_pullularia'] = array (
    '#type' => 'item',
    '#title' => t($pullularia),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['rhizopus'] = array (
    '#type' => 'item',
    '#title' => t('Rhizopus'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_rhizopus'] = array (
    '#type' => 'item',
    '#title' => t($rhizopus),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['stemphylium_botrysum'] = array (
    '#type' => 'item',
    '#title' => t('Stemphylium Botrysum'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_stemphylium_botrysum'] = array (
    '#type' => 'item',
    '#title' => t($stemphylium_botrysum),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['trichphyton_mix'] = array (
    '#type' => 'item',
    '#title' => t('Trichphyton'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_trichphyton_mix'] = array (
    '#type' => 'item',
    '#title' => t($trichphyton_mix),
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );





  $form['antigen_p2'] = array (
    '#type' => 'item',
    '#title' => t('Antigen Panel #2'),
    '#prefix' => '<tr><td>',
    '#suffix' => '</td></tr>',
  );

  $form['lambs_quarter'] = array (
    '#type' => 'item',
    '#title' => t('Lambs Quarter'),
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['p3_lambs_quarter'] = array (
    '#type' => 'item',
    '#title' => t($lambs_quarter),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['palintain'] = array (
    '#type' => 'item',
    '#title' => t('Palintain'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_palintain'] = array (
    '#type' => 'item',
    '#title' => t($palintain),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['ragweed_mix_gs'] = array (
    '#type' => 'item',
    '#title' => t('Ragweed Mix GS'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_ragweed_mix_gs'] = array (
    '#type' => 'item',
    '#title' => t($ragweed_mix_gs),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['marchelder'] = array (
    '#type' => 'item',
    '#title' => t('Marchelder/Poverty Mix'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_marchelder'] = array (
    '#type' => 'item',
    '#title' => t($marchelder),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['dog_fennel'] = array (
    '#type' => 'item',
    '#title' => t('Dog Fennel'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_dog_fennel'] = array (
    '#type' => 'item',
    '#title' => t($dog_fennel),
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );

  $form['elm_american'] = array (
    '#type' => 'item',
    '#title' => t('Elm American'),
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['p3_elm_american'] = array (
    '#type' => 'item',
    '#title' => t($elm_american),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['oak_mix'] = array (
    '#type' => 'item',
    '#title' => t('Oak Mix'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_oak_mix'] = array (
    '#type' => 'item',
    '#title' => t($oak_mix),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['pecan_tree'] = array (
    '#type' => 'item',
    '#title' => t('Pecan Tree'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_pecan_tree'] = array (
    '#type' => 'item',
    '#title' => t($pecan_tree),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['sweet_gum'] = array (
    '#type' => 'item',
    '#title' => t('Sweet Gum'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_sweet_gum'] = array (
    '#type' => 'item',
    '#title' => t($sweet_gum),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['walnut_black'] = array (
    '#type' => 'item',
    '#title' => t('Walnut Black'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_walnut_black'] = array (
    '#type' => 'item',
    '#title' => t($walnut_black),
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );




  $form['antigen_p5'] = array (
    '#type' => 'item',
    '#title' => t('Antigen Panel #5'),
    '#prefix' => '<tr><td>',
    '#suffix' => '</td></tr>',
  );

  $form['alternariatenuis'] = array (
    '#type' => 'item',
    '#title' => t('Alternariatenuis'),
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['p3_alternariatenuis'] = array (
    '#type' => 'item',
    '#title' => t($alternariatenuis),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['aspergillus_fumigatus'] = array (
    '#type' => 'item',
    '#title' => t('Aspergillus fumigatus'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_aspergillus_fumigatus'] = array (
    '#type' => 'item',
    '#title' => t($aspergillus_fumigatus),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['botrytis_cinerea'] = array (
    '#type' => 'item',
    '#title' => t('Botrytis Cinerea'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_botrytis_cinerea'] = array (
    '#type' => 'item',
    '#title' => t($botrytis_cinerea),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['candida'] = array (
    '#type' => 'item',
    '#title' => t('Candida'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_candida'] = array (
    '#type' => 'item',
    '#title' => t($candida),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['cephalosporium'] = array (
    '#type' => 'item',
    '#title' => t('Cephalosporium'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_cephalosporium'] = array (
    '#type' => 'item',
    '#title' => t($cephalosporium),
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );

  $form['pine_mix'] = array (
    '#type' => 'item',
    '#title' => t('Pine Mix'),
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['p3_pine_mix'] = array (
    '#type' => 'item',
    '#title' => t($pine_mix),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['sycamore_american'] = array (
    '#type' => 'item',
    '#title' => t('Sycamore American'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_sycamore_american'] = array (
    '#type' => 'item',
    '#title' => t($sycamore_american),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['careless_pigweed'] = array (
    '#type' => 'item',
    '#title' => t('Careless/Pigweed'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_careless_pigweed'] = array (
    '#type' => 'item',
    '#title' => t($careless_pigweed),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['cocklebur'] = array (
    '#type' => 'item',
    '#title' => t('Cocklbur'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_cocklebur'] = array (
    '#type' => 'item',
    '#title' => t($cocklebur),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['dock_sorrel'] = array (
    '#type' => 'item',
    '#title' => t('Dock/Sorrel'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_dock_sorrel'] = array (
    '#type' => 'item',
    '#title' => t($dock_sorrel),
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );




  $form['antigen_p1'] = array (
    '#type' => 'item',
    '#title' => t('Antigen Panel #1'),
    '#prefix' => '<tr><td>',
    '#suffix' => '</td></tr>',
  );


  $form['bluegrass_kentucky'] = array (
    '#type' => 'item',
    '#title' => t('Bluegrass Kentucky'),
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['p3_bluegrass_kentucky'] = array (
    '#type' => 'item',
    '#title' => t($bluegrass_kentucky),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['corn_cultivated'] = array (
    '#type' => 'item',
    '#title' => t('Corn Cultivated'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_corn_cultivated'] = array (
    '#type' => 'item',
    '#title' => t($corn_cultivated),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['oats_common'] = array (
    '#type' => 'item',
    '#title' => t('Oats common'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_oats_common'] = array (
    '#type' => 'item',
    '#title' => t($oats_common),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['orchard_grass'] = array (
    '#type' => 'item',
    '#title' => t('Orchard Grass'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_orchard_grass'] = array (
    '#type' => 'item',
    '#title' => t($orchard_grass),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['redtop'] = array (
    '#type' => 'item',
    '#title' => t('Redtop'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_redtop'] = array (
    '#type' => 'item',
    '#title' => t($redtop),
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );

  $form['positive_histamine'] = array (
    '#type' => 'item',
    '#title' => t('Positive/Histamine'),
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['p3_positive_histamine'] = array (
    '#type' => 'item',
    '#title' => t($positive_histamine),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['negative_glycerine'] = array (
    '#type' => 'item',
    '#title' => t('Negative/Glycerine'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_negative_glycerine'] = array (
    '#type' => 'item',
    '#title' => t($negative_glycerine),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['phenol'] = array (
    '#type' => 'item',
    '#title' => t('Phenol'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_phenol'] = array (
    '#type' => 'item',
    '#title' => t($phenol),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['bahia_grass'] = array (
    '#type' => 'item',
    '#title' => t('Bahia Grass'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_bahia_grass'] = array (
    '#type' => 'item',
    '#title' => t($bahia_grass),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['johnson_grass'] = array (
    '#type' => 'item',
    '#title' => t('Johnson Grass'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_johnson_grass'] = array (
    '#type' => 'item',
    '#title' => t($johnson_grass),
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );




  $form['antigen_p6'] = array (
    '#type' => 'item',
    '#title' => t('Antigen Panel #6'),
    '#prefix' => '<tr><td>',
    '#suffix' => '</td></tr>',
  );

  $form['sweet_vernalgrass'] = array (
    '#type' => 'item',
    '#title' => t('Sweet Vernalgrass'),
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['p3_sweet_vernalgrass'] = array (
    '#type' => 'item',
    '#title' => t($sweet_vernalgrass),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['boxelder_maple'] = array (
    '#type' => 'item',
    '#title' => t('Boxelder Maple'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_boxelder_maple'] = array (
    '#type' => 'item',
    '#title' => t($boxelder_maple),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['cedar_mountian'] = array (
    '#type' => 'item',
    '#title' => t('Cedar Mountian'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_cedar_mountian'] = array (
    '#type' => 'item',
    '#title' => t($cedar_mountian),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['common_privet'] = array (
    '#type' => 'item',
    '#title' => t('Common Privet'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_common_privet'] = array (
    '#type' => 'item',
    '#title' => t($common_privet),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['cottonwood'] = array (
    '#type' => 'item',
    '#title' => t('Cottonwood'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_cottonwood'] = array (
    '#type' => 'item',
    '#title' => t($cottonwood),
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );

  $form['bermuda_grass'] = array (
    '#type' => 'item',
    '#title' => t('Bermuda Grass'),
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['p3_bermuda_grass'] = array (
    '#type' => 'item',
    '#title' => t($bermuda_grass),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['meadow_fescue'] = array (
    '#type' => 'item',
    '#title' => t('Meadow Fescue'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_meadow_fescue'] = array (
    '#type' => 'item',
    '#title' => t($meadow_fescue),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['rye_grass'] = array (
    '#type' => 'item',
    '#title' => t('Rye Grass'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_rye_grass'] = array (
    '#type' => 'item',
    '#title' => t($rye_grass),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['timothy'] = array (
    '#type' => 'item',
    '#title' => t('Timothy'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_timothy'] = array (
    '#type' => 'item',
    '#title' => t($timothy),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['brome_smooth'] = array (
    '#type' => 'item',
    '#title' => t('Brome Smooth'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_brome_smooth'] = array (
    '#type' => 'item',
    '#title' => t($brome_smooth),
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );



  $form['food_allergy'] = array (
    '#type' => 'item',
    '#title' => t('Food Allergy Profile'),
    '#prefix' => '<tr><td>',
    '#suffix' => '</td></tr>',
  );

  $form['casein'] = array (
    '#type' => 'item',
    '#title' => t('Casein'),
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['p3_casein'] = array (
    '#type' => 'item',
    '#title' => t($casein),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['milk_cow'] = array (
    '#type' => 'item',
    '#title' => t('Milk, Cow'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_milk_cow'] = array (
    '#type' => 'item',
    '#title' => t($milk_cow),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['egg_chicken_white'] = array (
    '#type' => 'item',
    '#title' => t('Egg, Checken, White'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_egg_chicken_white'] = array (
    '#type' => 'item',
    '#title' => t($egg_chicken_white),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['peanut'] = array (
    '#type' => 'item',
    '#title' => t('Peanut'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_peanut'] = array (
    '#type' => 'item',
    '#title' => t($peanut),
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );

  $form['soybean'] = array (
    '#type' => 'item',
    '#title' => t('Soybean'),
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['p3_soybean'] = array (
    '#type' => 'item',
    '#title' => t($soybean),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['pecan'] = array (
    '#type' => 'item',
    '#title' => t('Pecan'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_pecan'] = array (
    '#type' => 'item',
    '#title' => t($pecan),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['shellfish_mix'] = array (
    '#type' => 'item',
    '#title' => t('Shellfish, Mix'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_shellfish_mix'] = array (
    '#type' => 'item',
    '#title' => t($shellfish_mix),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['shrimp'] = array (
    '#type' => 'item',
    '#title' => t('Shrimp'),
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['p3_shrimp'] = array (
    '#type' => 'item',
    '#title' => t($timothy),
    '#prefix' => '<td>',
    '#suffix' => '</td></tr></table>',
  );




  $form['submit'] = array (
    '#type' => 'submit',
    '#value' => t('<< Back'),
    '#validate' => array('rmsallergy_view_incoming_p3_back_validate' ),
    '#submit' => array('rmsallergy_view_incoming_p3_back_submit' ),
  );

  return $form;
}

function rmsallergy_view_incoming_p3_back_validate ( $form, &$form_state )
{
  return $form;
}

function rmsallergy_view_incoming_p3_back_submit ( $form, &$form_state )
{
// values are save for each page in order to carry to subsequent pages
// and to tell FAPI how to rebuild the form

  $form_state['page_values'][3] = $form_state['values'];

  if ( !empty($form_state['page_values'][2] )) {
    $form_state['values'] = $form_state['page_values'][1];
  }

  $form_state['page_num'] = 2;
  $form_state['rebuild'] = TRUE;

  return $form;
}

