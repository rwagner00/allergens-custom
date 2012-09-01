<?php

/**
 * @file
 * RMS Allergy function file
 */

function rmsallergy_add_profile ( $form, &$form_state )
{

// check for prior call to add patient and go to appropriate page

  if ( !empty($form_state['page_num'] )) {
    if ( $form_state['page_num'] == 1 ) {
      return rmsallergy_add_profile_p1 ( $form, $form_state );
    } elseif ( $form_state['page_num'] == 2 ) {
      return rmsallergy_add_profile_p2 ( $form, $form_state );
    } elseif ( $form_state['page_num'] == 3 ) {
      return rmsallergy_add_profile_p3 ( $form, $form_state );
    } elseif ( $form_state['page_num'] == 4 ) {
      return rmsallergy_add_profile_p4 ( $form, $form_state );
    } elseif ( $form_state['page_num'] == 5 ) {
      return rmsallergy_add_profile_p5 ( $form, $form_state );
    } elseif ( $form_state['page_num'] == 6 ) {
      return rmsallergy_add_profile_p6 ( $form, $form_state );
    }
  } else {
    return rmsallergy_add_profile_p1 ( $form, $form_state );
  }
}

include ( "rmsallergy_add_profile_p1.inc" );
include ( "rmsallergy_add_profile_p2.inc" );
include ( "rmsallergy_add_profile_p3.inc" );
include ( "rmsallergy_add_profile_p4.inc" );
include ( "rmsallergy_add_profile_p5.inc" );
include ( "rmsallergy_add_profile_p6.inc" );


function rmsallergy_add_profile_validate ( $form, &$form_state )
{
  // this is a more complicated validate since we are coming from
  // two different sources and since the database insert is fairly
  // complicated.

  // start first by validating the immediate past page (will be the
  // same even though two different pages come into this point)

  $practice_key = $form_state['values']['table'];

  if ( ! $practice_key ) {
    form_set_error ( 'Add Profile', t('Please select practice') );
  }

// when you come into this valiate, $form_state['page_num'] is
// the page of the source

  $src_page = $form_state['page_num'];

  if ( ! $src_page ) {
    form_set_error ( 'Add Profile', t('Source page is empty') );
  }

// if user is submitting a referral and a chart is uploaded, the chart
// needs to be uploaded before moving to the submit.  if the source page
// is greater than 3, then the referral is desired

  if ( $src_page > 3 ) {

    $faxchart = $form_state['values']['faxchart'];

//  drupal_set_message ( t('faxchart: @a', array('@a' => $faxchart) ) );

    if ( $faxchart == 0 ) {

      $args = array (
        'file_validate_extensions' => array ( 'pdf' ),
      );

      $dest = 'private://';

      $file = file_save_upload ( 'file', $args, $dest );

      if ( $file ) {
//        drupal_set_message ( print_r ( $file, TRUE ) );
      } else {
        form_set_error ( 'file', t('No file was uploaded'));
//        drupal_set_message ( t('Information: No file was uploaded') );
      }

      $file->status = FILE_STATUS_PERMANENT;
      file_save ( $file );

      drupal_set_message ( t('filename @filename', array('@filename' => $file->filename)));
    }
  }


// data in the submit function will be pulled out from
// $form_state['page_values'][n] array for each page.  If coming from page 3
// it is possible this value might be NULL.  If coming from page 3,
// recopy the data over just to make sure it is not NULL.

  if ( $src_page == 3 ) { 
    $form_state['page_values'][3] = $form_state['values'];
  }

  return $form;
}


function rmsallergy_add_profile_submit ( $form, &$form_state )
{
  $patient_key = __rmsallergy_add_profile_insert_patient ( $form,
                                                           $form_state );

  $profile_key = __rmsallergy_add_profile_insert_profile ( $patient_key,
                                                           $form,
                                                           $form_state );

// if page 4 of the profile exists, then the referral was created
  if ( ! empty ( $form_state['page_values'][4] ) ) {

    $referral_key = __rmsallergy_add_profile_insert_referral ( $patient_key,
                                                               $profile_key,
                                                               $form,
                                                               $form_state );
  }
}

function __rmsallergy_add_profile_insert_referral ( $patient_key, 
                                                    $profile_key,
                                                    $form, 
                                                    &$form_state )
{
// get practice_key from current user
  global $user;
  $account = user_load ( $user->uid );
  $practice_key = field_get_items ( 'user', $account, 'field_practice_key' );
  $practice_key = $practice_key[0]['value'];


// get the referred practice key from form

  $referred_practice_key = $form_state['values']['table'];
drupal_set_message ( print_r ( $referred_practice_key, TRUE ) );


// get the data out of the form
  $cash_pay_flag = $form_state['page_values'][4]['cash_pay_flag'];

  $primary_flag               = $form_state['page_values'][4]['primary_flag'];
  $primary_carrier            = $form_state['page_values'][4]['primary_carrier'];
  $primary_group_number       = $form_state['page_values'][4]['primary_group_number'];
  $primary_policy_holder_name = $form_state['page_values'][4]['primary_holder_name'];
  $primary_policy_holder_ssn1 = $form_state['page_values'][4]['primary_holder_ssn1'];
  $primary_policy_holder_ssn2 = $form_state['page_values'][4]['primary_holder_ssn2'];
  $primary_policy_holder_ssn3 = $form_state['page_values'][4]['primary_holder_ssn3'];
  $primary_policy_holder_dob_month = $form_state['page_values'][4]['primary_holder_dob_month'];
  $primary_policy_holder_dob_day   = $form_state['page_values'][4]['primary_holder_dob_day'];
  $primary_policy_holder_dob_year  = $form_state['page_values'][4]['primary_holder_dob_year'];

  $secondary_flag               = $form_state['page_values'][4]['secondary_flag'];
  $secondary_carrier            = $form_state['page_values'][4]['secondary_carrier'];
  $secondary_group_number       = $form_state['page_values'][4]['secondary_group_number'];
  $secondary_policy_holder_name = $form_state['page_values'][4]['secondary_holder_name'];
  $secondary_policy_holder_ssn1 = $form_state['page_values'][4]['secondary_holder_ssn1'];
  $secondary_policy_holder_ssn2 = $form_state['page_values'][4]['secondary_holder_ssn2'];
  $secondary_policy_holder_ssn3 = $form_state['page_values'][4]['secondary_holder_ssn3'];
  $secondary_policy_holder_dob_month = $form_state['page_values'][4]['secondary_holder_dob_month'];
  $secondary_policy_holder_dob_day   = $form_state['page_values'][4]['secondary_holder_dob_day'];
  $secondary_policy_holder_dob_year  = $form_state['page_values'][4]['secondary_holder_dob_year'];


// set active database and insert new record

  db_set_active ( 'rmsallergy' );

  // update patient database
  $referral_key = db_insert ( 'referral' )
    ->fields ( array (
      'practice_key' => $practice_key,
      'patient_key'  => $patient_key,
      'profile_key'  => $profile_key,
      'referred_practice_key'  => $referred_practice_key,
      'cash_pay_flag' => $cash_pay_flag,
      'primary_flag' => $primary_flag,
      'primary_carrier' => $primary_carrier,
      'primary_group_number' => $primary_group_number,
      'primary_policy_holder_name' => $primary_policy_holder_name,
      'primary_policy_holder_ssn1' => $primary_policy_holder_ssn1,
      'primary_policy_holder_ssn2' => $primary_policy_holder_ssn2,
      'primary_policy_holder_ssn3' => $primary_policy_holder_ssn3,
      'primary_policy_holder_dob_month' => $primary_policy_holder_dob_month,
      'primary_policy_holder_dob_day' => $primary_policy_holder_dob_day,
      'primary_policy_holder_dob_year' => $primary_policy_holder_dob_year,
      'secondary_flag' => $secondary_flag,
      'secondary_carrier' => $secondary_carrier,
      'secondary_group_number' => $secondary_group_number,
      'secondary_policy_holder_name' => $secondary_policy_holder_name,
      'secondary_policy_holder_ssn1' => $secondary_policy_holder_ssn1,
      'secondary_policy_holder_ssn2' => $secondary_policy_holder_ssn2,
      'secondary_policy_holder_ssn3' => $secondary_policy_holder_ssn3,
      'secondary_policy_holder_dob_month' => $secondary_policy_holder_dob_month,
      'secondary_policy_holder_dob_day' => $secondary_policy_holder_dob_day,
      'secondary_policy_holder_dob_year' => $secondary_policy_holder_dob_year,
    ))
    ->execute();

  db_set_active ();

  drupal_set_message ( t('The referral has been added.') );

  return $referral_key;

}

function __rmsallergy_add_profile_insert_profile ( $patient_key, $form, &$form_state )
{

// get practice_key from current user
  global $user;
  $account = user_load ( $user->uid );
  $practice_key = field_get_items ( 'user', $account, 'field_practice_key' );
  $practice_key = $practice_key[0]['value'];

// get the data out of the form

  $test_date_month = $form_state['page_values'][3]['test_date_month'];
  $test_date_day   = $form_state['page_values'][3]['test_date_day'];
  $test_date_year  = $form_state['page_values'][3]['test_date_year'];


  $cat_pelt = $form_state['page_values'][3]['cat_pelt'];
  $cat_hair = $form_state['page_values'][3]['cat_hair'];
  $dog_hair = $form_state['page_values'][3]['dog_hair'];
  $cockroach = $form_state['page_values'][3]['cockroach'];
  $mite_farinae = $form_state['page_values'][3]['mite_farinae'];
  $curvularia = $form_state['page_values'][3]['curvularia'];
  $epidermophyton = $form_state['page_values'][3]['epidermophyton'];
  $fusarium = $form_state['page_values'][3]['fusarium'];
  $helminthosporium = $form_state['page_values'][3]['helminthosporium'];
  $hormodendrum = $form_state['page_values'][3]['hormodendrum'];
  $mite_petronyssi = $form_state['page_values'][3]['mite_petronyssi'];
  $feathers_mix = $form_state['page_values'][3]['feathers_mix'];
  $ap_house_dust = $form_state['page_values'][3]['ap_house_dust'];
  $pcn_mix = $form_state['page_values'][3]['pcn_mix'];
  $horse_hair = $form_state['page_values'][3]['horse_hair'];
  $mucor = $form_state['page_values'][3]['mucor'];
  $pullularia = $form_state['page_values'][3]['pullularia'];
  $rhizopus = $form_state['page_values'][3]['rhizopus'];
  $stemphylium_botrysum = $form_state['page_values'][3]['stemphylium_botrysum'];
  $trichphyton_mix = $form_state['page_values'][3]['trichphyton_mix'];
  $lambs_quarter = $form_state['page_values'][3]['lambs_quarter'];
  $palintain = $form_state['page_values'][3]['palintain'];
  $ragweed_mix_gs = $form_state['page_values'][3]['ragweed_mix_gs'];
  $marchelder = $form_state['page_values'][3]['marchelder'];
  $dog_fennel = $form_state['page_values'][3]['dog_fennel'];
  $elm_american = $form_state['page_values'][3]['elm_american'];
  $oak_mix = $form_state['page_values'][3]['oak_mix'];
  $pecan_tree = $form_state['page_values'][3]['pecan_tree'];
  $sweet_gum = $form_state['page_values'][3]['sweet_gum'];
  $walnut_black = $form_state['page_values'][3]['walnut_black'];
  $alternariatenuis = $form_state['page_values'][3]['alternariatenuis'];
  $aspergillus_fumigatus = $form_state['page_values'][3]['aspergillus_fumigatus'];
  $botrytis_cinerea = $form_state['page_values'][3]['botrytis_cinerea'];
  $candida = $form_state['page_values'][3]['candida'];
  $cephalosporium = $form_state['page_values'][3]['cephalosporium'];
  $pine_mix = $form_state['page_values'][3]['pine_mix'];
  $sycamore_american = $form_state['page_values'][3]['sycamore_american'];
  $careless_pigweed = $form_state['page_values'][3]['careless_pigweed'];
  $cocklebur = $form_state['page_values'][3]['cocklebur'];
  $dock_sorrel = $form_state['page_values'][3]['dock_sorrel'];
  $bluegrass_kentucky = $form_state['page_values'][3]['bluegrass_kentucky'];
  $corn_cultivated = $form_state['page_values'][3]['corn_cultivated'];
  $oats_common = $form_state['page_values'][3]['oats_common'];
  $orchard_grass = $form_state['page_values'][3]['orchard_grass'];
  $redtop = $form_state['page_values'][3]['redtop'];
  $positive_histamine = $form_state['page_values'][3]['positive_histamine'];
  $negative_glycerine = $form_state['page_values'][3]['negative_glycerine'];
  $phenol = $form_state['page_values'][3]['phenol'];
  $bahia_grass = $form_state['page_values'][3]['bahia_grass'];
  $johnson_grass = $form_state['page_values'][3]['johnson_grass'];
  $sweet_vernalgrass = $form_state['page_values'][3]['sweet_vernalgrass'];
  $boxelder_maple = $form_state['page_values'][3]['boxelder_maple'];
  $cedar_mountian = $form_state['page_values'][3]['cedar_mountian'];
  $common_privet = $form_state['page_values'][3]['common_privet'];
  $cottonwood = $form_state['page_values'][3]['cottonwood'];
  $bermuda_grass = $form_state['page_values'][3]['bermuda_grass'];
  $meadow_fescue = $form_state['page_values'][3]['meadow_fescue'];
  $rye_grass = $form_state['page_values'][3]['rye_grass'];
  $timothy = $form_state['page_values'][3]['timothy'];
  $brome_smooth = $form_state['page_values'][3]['brome_smooth'];
  $casein = $form_state['page_values'][3]['casein'];
  $milk_cow = $form_state['page_values'][3]['milk_cow'];
  $egg_chicken_white = $form_state['page_values'][3]['egg_chicken_white'];
  $peanut = $form_state['page_values'][3]['peanut'];
  $soybean = $form_state['page_values'][3]['soybean'];
  $pecan = $form_state['page_values'][3]['pecan'];
  $shellfish_mix = $form_state['page_values'][3]['shellfish_mix'];
  $shrimp = $form_state['page_values'][3]['shrimp'];


// perform insert into database

  db_set_active ( 'rmsallergy' );

  // update patient database
  $profile_key = db_insert ( 'profile' )
    ->fields ( array (
      'practice_key' => $practice_key,
      'patient_key' => $patient_key,
      'test_date_month' => $test_date_month,
      'test_date_day' => $test_date_day,
      'test_date_year' => $test_date_year,
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
      'lambs_quarter' => $lambs_quarter,
      'palintain' => $palintain,
      'ragweed_mix_gs' => $ragweed_mix_gs,
      'marchelder' => $marchelder,
      'dog_fennel' => $dog_fennel,
      'elm_american' => $elm_american,
      'oak_mix' => $oak_mix,
      'pecan_tree' => $pecan_tree,
      'sweet_gum' => $sweet_gum,
      'walnut_black' => $walnut_black,
      'alternariatenuis' => $alternariatenuis,
      'aspergillus_fumigatus' => $aspergillus_fumigatus,
      'botrytis_cinerea' => $botrytis_cinerea,
      'candida' => $candida,
      'cephalosporium' => $cephalosporium,
      'pine_mix' => $pine_mix,
      'sycamore_american' => $sycamore_american,
      'careless_pigweed' => $careless_pigweed,
      'cocklebur' => $cocklebur,
      'dock_sorrel' => $dock_sorrel,
      'bluegrass_kentucky' => $bluegrass_kentucky,
      'corn_cultivated' => $corn_cultivated,
      'oats_common' => $oats_common,
      'orchard_grass' => $orchard_grass,
      'redtop' => $redtop,
      'positive_histamine' => $positive_histamine,
      'negative_glycerine' => $negative_glycerine,
      'phenol' => $phenol,
      'bahia_grass' => $bahia_grass,
      'johnson_grass' => $johnson_grass,
      'sweet_vernalgrass' => $sweet_vernalgrass,
      'boxelder_maple' => $boxelder_maple,
      'cedar_mountian' => $cedar_mountian,
      'common_privet' => $common_privet,
      'cottonwood' => $cottonwood,
      'bermuda_grass' => $bermuda_grass,
      'meadow_fescue' => $meadow_fescue,
      'rye_grass' => $rye_grass,
      'timothy' => $timothy,
      'brome_smooth' => $brome_smooth,
      'casein' => $casein,
      'milk_cow' => $milk_cow,
      'egg_chicken_white' => $egg_chicken_white,
      'peanut' => $peanut,
      'soybean' => $soybean,
      'pecan' => $pecan,
      'shellfish_mix' => $shellfish_mix,
      'shrimp' => $shrimp,
    ))
    ->execute();

  db_set_active ();

  drupal_set_message ( t('The allergy profile has been added.') );

  return $profile_key;
}

function __rmsallergy_add_profile_insert_patient ( $form, &$form_state )
{

// get practice_key from current user
  global $user;
  $account = user_load ( $user->uid );
  $practice_key = field_get_items ( 'user', $account, 'field_practice_key' );
  $practice_key = $practice_key[0]['value'];

// get the data out of the form

  $patient_first_name   = $form_state['page_values'][1]['first_name'];
  $patient_middle_name  = $form_state['page_values'][1]['middle_name'];
  $patient_last_name    = $form_state['page_values'][1]['last_name'];
  $patient_ssn1         = $form_state['page_values'][1]['ssn1'];
  $patient_ssn2         = $form_state['page_values'][1]['ssn2'];
  $patient_ssn3         = $form_state['page_values'][1]['ssn3'];
  $patient_dob_month    = $form_state['page_values'][1]['dob_month'];
  $patient_dob_day      = $form_state['page_values'][1]['dob_day'];
  $patient_dob_year     = $form_state['page_values'][1]['dob_year'];
  $patient_gender       = $form_state['page_values'][1]['gender'];
  $patient_address1     = $form_state['page_values'][1]['address1'];
  $patient_address2     = $form_state['page_values'][1]['address2'];
  $patient_city         = $form_state['page_values'][1]['city'];
  $patient_state        = $form_state['page_values'][1]['state'];
  $patient_zip          = $form_state['page_values'][1]['zip'];
  $patient_home_phone   = $form_state['page_values'][1]['home_phone'];
  $patient_work_phone   = $form_state['page_values'][1]['work_phone'];
  $patient_mobile_phone = $form_state['page_values'][1]['mobile_phone'];
  $patient_email        = $form_state['page_values'][1]['email'];
  $patient_fax          = $form_state['page_values'][1]['fax'];

  $minor_flag            = $form_state['page_values'][2]['minor_flag'];
  $guardian_name         = $form_state['page_values'][2]['name'];
  $guardian_address1     = $form_state['page_values'][2]['address1'];
  $guardian_address2     = $form_state['page_values'][2]['address2'];
  $guardian_city         = $form_state['page_values'][2]['city'];
  $guardian_state        = $form_state['page_values'][2]['state'];
  $guardian_zip          = $form_state['page_values'][2]['zip'];
  $guardian_home_phone   = $form_state['page_values'][2]['home_phone'];
  $guardian_work_phone   = $form_state['page_values'][2]['work_phone'];
  $guardian_mobile_phone = $form_state['page_values'][2]['mobile_phone'];
  $guardian_email        = $form_state['page_values'][2]['email'];
  $guardian_fax          = $form_state['page_values'][2]['fax'];

/*
  $primary_flag               = $form_state['values']['primary_flag'];
  $primary_carrier            = $form_state['values']['primary_carrier'];
  $primary_group_number       = $form_state['values']['primary_group_number'];
  $primary_policy_holder_name = $form_state['values']['primary_holder_name'];
  $primary_policy_holder_ssn  = $form_state['values']['primary_holder_ssn'];
  $primary_policy_holder_dob  = $form_state['values']['primary_holder_dob'];

  $secondary_flag               = $form_state['values']['secondary_flag'];
  $secondary_carrier            = $form_state['values']['secondary_carrier'];
  $secondary_group_number       = $form_state['values']['secondary_group_number'];
  $secondary_policy_holder_name = $form_state['values']['secondary_holder_name'];
  $secondary_policy_holder_ssn  = $form_state['values']['secondary_holder_ssn'];
  $secondary_policy_holder_dob  = $form_state['values']['secondary_holder_dob'];
*/


// set active database and insert new record

  db_set_active ( 'rmsallergy' );

  // update patient database
  $patient_key = db_insert ( 'patient' )
    ->fields ( array (
      'practice_key' => $practice_key,
      'patient_first_name' => $patient_first_name,
      'patient_middle_name' => $patient_middle_name,
      'patient_last_name' => $patient_last_name,
      'patient_ssn1' => $patient_ssn1,
      'patient_ssn2' => $patient_ssn2,
      'patient_ssn3' => $patient_ssn3,
      'patient_dob_month' => $patient_dob_month,
      'patient_dob_day' => $patient_dob_day,
      'patient_dob_year' => $patient_dob_year,
      'patient_gender' => $patient_gender,
      'patient_address1' => $patient_address1,
      'patient_address2' => $patient_address2,
      'patient_city' => $patient_city,
      'patient_state' => $patient_state,
      'patient_zip' => $patient_zip,
      'patient_home_phone' => $patient_home_phone,
      'patient_work_phone' => $patient_work_phone,
      'patient_mobile_phone' => $patient_mobile_phone,
      'patient_email' => $patient_email,
      'patient_fax' => $patient_fax,
      'minor_flag' => $minor_flag,
      'guardian_name' => $guardian_name,
      'guardian_address1' => $guardian_address1,
      'guardian_address2' => $guardian_address2,
      'guardian_city' => $guardian_city,
      'guardian_state' => $guardian_state,
      'guardian_zip' => $guardian_zip,
      'guardian_home_phone' => $guardian_home_phone,
      'guardian_work_phone' => $guardian_work_phone,
      'guardian_mobile_phone' => $guardian_mobile_phone,
      'guardian_email' => $guardian_email,
      'guardian_fax' => $guardian_fax,
 /*     'primary_flag' => $primary_flag,
      'primary_carrier' => $primary_carrier,
      'primary_group_number' => $primary_group_number,
      'primary_policy_holder_name' => $primary_policy_holder_name,
      'primary_policy_holder_ssn' => $primary_policy_holder_ssn,
      'primary_policy_holder_dob' => $primary_policy_holder_dob,
      'secondary_flag' => $secondary_flag,
      'secondary_carrier' => $secondary_carrier,
      'secondary_group_number' => $secondary_group_number,
      'secondary_policy_holder_name' => $secondary_policy_holder_name,
      'secondary_policy_holder_ssn' => $secondary_policy_holder_ssn,
      'secondary_policy_holder_dob' => $secondary_policy_holder_dob,
*/
    ))
    ->execute();

  db_set_active ();

  drupal_set_message ( t('The patient has been added.') );

  return $patient_key;
}

