<?php


function rmsallergy_add_profile_p3 ( $form, &$form_state )
{

// set default values for the remainder of the form

  $test_date_month = !empty ( $form_state['values']['test_date_month'] ) ?
                              $form_state['values']['test_date_month'] : '';
  $test_date_day = !empty ( $form_state['values']['test_date_day'] ) ?
                            $form_state['values']['test_date_day'] : '';
  $test_date_year = !empty ( $form_state['values']['test_date_year'] ) ?
                             $form_state['values']['test_date_year'] : '';

  $cat_pelt = !empty ( $form_state['values']['cat_pelt'] ) ?
                       $form_state['values']['cat_pelt'] : '00/00';
  $cat_hair = !empty ( $form_state['values']['cat_hair'] ) ?
                       $form_state['values']['cat_hair'] : '00/00';
  $dog_hair = !empty ( $form_state['values']['dog_hair'] ) ?
                       $form_state['values']['dog_hair'] : '00/00';
  $cockroach = !empty ( $form_state['values']['cockroach'] ) ?
                        $form_state['values']['cockroach'] : '00/00';
  $mite_farinae = !empty ( $form_state['values']['mite_farinae'] ) ?
                           $form_state['values']['mite_farinae'] : '00/00';
  $curvularia = !empty ( $form_state['values']['curvularia'] ) ?
                         $form_state['values']['curvularia'] : '00/00';
  $epidermophyton = !empty ( $form_state['values']['epidermophyton'] ) ?
                             $form_state['values']['epidermophyton'] : '00/00';
  $fusarium = !empty ( $form_state['values']['fusarium'] ) ?
                       $form_state['values']['fusarium'] : '00/00';
  $helminthosporium = !empty ( $form_state['values']['helminthosporium'] ) ?
                               $form_state['values']['helminthosporium'] : '00/00';
  $hormodendrum = !empty ( $form_state['values']['hormodendrum'] ) ?
                           $form_state['values']['hormodendrum'] : '00/00';

  $mite_petronyssi = !empty ( $form_state['values']['mite_petronyssi'] ) ?
                              $form_state['values']['mite_petronyssi'] : '00/00';
  $feathers_mix = !empty ( $form_state['values']['feathers_mix'] ) ?
                           $form_state['values']['feathers_mix'] : '00/00';
  $ap_house_dust = !empty ( $form_state['values']['ap_house_dust'] ) ?
                            $form_state['values']['ap_house_dust'] : '00/00';
  $pcn_mix = !empty ( $form_state['values']['pcn_mix'] ) ?
                      $form_state['values']['pcn_mix'] : '00/00';
  $horse_hair = !empty ( $form_state['values']['horse_hair'] ) ?
                         $form_state['values']['horse_hair'] : '00/00';
  $mucor = !empty ( $form_state['values']['mucor'] ) ?
                    $form_state['values']['mucor'] : '00/00';
  $pullularia = !empty ( $form_state['values']['pullularia'] ) ?
                       $form_state['values']['pullularia'] : '00/00';
  $rhizopus = !empty ( $form_state['values']['rhizopus'] ) ?
                       $form_state['values']['rhizopus'] : '00/00';
  $stemphylium_botrysum = !empty ( $form_state['values']['stemphylium_botrysum'] ) ?
                                   $form_state['values']['stemphylium_botrysum'] : '00/00';
  $trichphyton_mix = !empty ( $form_state['values']['trichphyton_mix'] ) ?
                              $form_state['values']['trichphyton_mix'] : '00/00';

  $lambs_quarter = !empty ( $form_state['values']['lambs_quarter'] ) ?
                            $form_state['values']['lambs_quarter'] : '00/00';
  $palintain = !empty ( $form_state['values']['palintain'] ) ?
                        $form_state['values']['palintain'] : '00/00';
  $ragweed_mix_gs = !empty ( $form_state['values']['ragweed_mix_gs'] ) ?
                             $form_state['values']['ragweed_mix_gs'] : '00/00';
  $marchelder = !empty ( $form_state['values']['marchelder'] ) ?
                         $form_state['values']['marchelder'] : '00/00';
  $dog_fennel = !empty ( $form_state['values']['dog_fennel'] ) ?
                           $form_state['values']['dog_fennel'] : '00/00';
  $elm_american = !empty ( $form_state['values']['elm_american'] ) ?
                           $form_state['values']['elm_american'] : '00/00';
  $oak_mix = !empty ( $form_state['values']['oak_mix'] ) ?
                      $form_state['values']['oak_mix'] : '00/00';
  $pecan_tree = !empty ( $form_state['values']['pecan_tree'] ) ?
                         $form_state['values']['pecan_tree'] : '00/00';
  $sweet_gum = !empty ( $form_state['values']['sweet_gum'] ) ?
                        $form_state['values']['sweet_gum'] : '00/00';
  $walnut_black = !empty ( $form_state['values']['walnut_black'] ) ?
                           $form_state['values']['walnut_black'] : '00/00';


  $alternariatenuis = !empty ( $form_state['values']['alternariatenuis'] ) ?  $form_state['values']['alternariatenuis'] : '00/00';
  $aspergillus_fumigatus = !empty ( $form_state['values']['aspergillus_fumigatus'] ) ?  $form_state['values']['aspergillus_fumigatus'] : '00/00';
  $botrytis_cinerea = !empty ( $form_state['values']['botrytis_cinerea'] ) ?  $form_state['values']['botrytis_cinerea'] : '00/00';
  $candida = !empty ( $form_state['values']['candida'] ) ?  $form_state['values']['candida'] : '00/00';
  $cephalosporium = !empty ( $form_state['values']['cephalosporium'] ) ?  $form_state['values']['cephalosporium'] : '00/00';
  $pine_mix = !empty ( $form_state['values']['pine_mix'] ) ?  $form_state['values']['pine_mix'] : '00/00';
  $sycamore_american = !empty ( $form_state['values']['sycamore_american'] ) ?  $form_state['values']['sycamore_american'] : '00/00';
  $careless_pigweed = !empty ( $form_state['values']['careless_pigweed'] ) ?  $form_state['values']['careless_pigweed'] : '00/00';
  $cocklebur = !empty ( $form_state['values']['cocklebur'] ) ?  $form_state['values']['cocklebur'] : '00/00';
  $dock_sorrel = !empty ( $form_state['values']['dock_sorrel'] ) ?  $form_state['values']['dock_sorrel'] : '00/00';

  $bluegrass_kentucky = !empty ( $form_state['values']['bluegrass_kentucky'] ) ?  $form_state['values']['bluegrass_kentucky'] : '00/00';
  $corn_cultivated = !empty ( $form_state['values']['corn_cultivated'] ) ?  $form_state['values']['corn_cultivated'] : '00/00';
  $oats_common = !empty ( $form_state['values']['oats_common'] ) ?  $form_state['values']['oats_common'] : '00/00';
  $orchard_grass = !empty ( $form_state['values']['orchard_grass'] ) ?  $form_state['values']['orchard_grass'] : '00/00';
  $redtop = !empty ( $form_state['values']['redtop'] ) ?  $form_state['values']['redtop'] : '00/00';
  $positive_histamine = !empty ( $form_state['values']['positive_histamine'] ) ?  $form_state['values']['positive_histamine'] : '00/00';
  $negative_glycerine = !empty ( $form_state['values']['negative_glycerine'] ) ?  $form_state['values']['negative_glycerine'] : '00/00';
  $phenol = !empty ( $form_state['values']['phenol'] ) ?  $form_state['values']['phenol'] : '00/00';
  $bahia_grass = !empty ( $form_state['values']['bahia_grass'] ) ?  $form_state['values']['bahia_grass'] : '00/00';
  $johnson_grass = !empty ( $form_state['values']['johnson_grass'] ) ?  $form_state['values']['johnson_grass'] : '00/00';

  $sweet_vernalgrass = !empty ( $form_state['values']['sweet_vernalgrass'] ) ?  $form_state['values']['sweet_vernalgrass'] : '00/00';
  $boxelder_maple = !empty ( $form_state['values']['boxelder_maple'] ) ?  $form_state['values']['boxelder_maple'] : '00/00';
  $cedar_mountain = !empty ( $form_state['values']['cedar_mountain'] ) ?  $form_state['values']['cedar_mountain'] : '00/00';
  $common_privet = !empty ( $form_state['values']['common_privet'] ) ?  $form_state['values']['common_privet'] : '00/00';
  $cottonwood = !empty ( $form_state['values']['cottonwood'] ) ?  $form_state['values']['cottonwood'] : '00/00';
  $bermuda_grass = !empty ( $form_state['values']['bermuda_grass'] ) ?  $form_state['values']['bermuda_grass'] : '00/00';
  $meadow_fescue = !empty ( $form_state['values']['meadow_fescue'] ) ?  $form_state['values']['meadow_fescue'] : '00/00';
  $rye_grass = !empty ( $form_state['values']['rye_grass'] ) ?  $form_state['values']['rye_grass'] : '00/00';
  $timothy = !empty ( $form_state['values']['timothy'] ) ?  $form_state['values']['timothy'] : '00/00';
  $brome_smooth = !empty ( $form_state['values']['brome_smooth'] ) ?  $form_state['values']['brome_smooth'] : '00/00';

  $casein = !empty ( $form_state['values']['casein'] ) ?  $form_state['values']['casein'] : '00/00';
  $milk_cow = !empty ( $form_state['values']['milk_cow'] ) ?  $form_state['values']['milk_cow'] : '00/00';
  $egg_chicken_white = !empty ( $form_state['values']['egg_chicken_white'] ) ?  $form_state['values']['egg_chicken_white'] : '00/00';
  $peanut = !empty ( $form_state['values']['peanut'] ) ?  $form_state['values']['peanut'] : '00/00';
  $soybean = !empty ( $form_state['values']['soybean'] ) ?  $form_state['values']['soybean'] : '00/00';
  $pecan = !empty ( $form_state['values']['pecan'] ) ?  $form_state['values']['pecan'] : '00/00';
  $shellfish_mix = !empty ( $form_state['values']['shellfish_mix'] ) ?  $form_state['values']['shellfish_mix'] : '00/00';
  $shrimp = !empty ( $form_state['values']['shrimp'] ) ?  $form_state['values']['shrimp'] : '00/00';



// unset prior values so the form rebuild correctly

  unset($form_state['input']['test_date_month']);
  unset($form_state['input']['test_date_day']);
  unset($form_state['input']['test_date_year']);

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

  unset($form_state['input']['alternariatenius']);
  unset($form_state['input']['aspergillus_fumigatus']);
  unset($form_state['input']['botrytis_cinerea']);
  unset($form_state['input']['candida']);
  unset($form_state['input']['cephalosporium']);
  unset($form_state['input']['pine_mix']);
  unset($form_state['input']['sycamore_american']);
  unset($form_state['input']['careless_pigweed']);
  unset($form_state['input']['cocklebur']);
  unset($form_state['input']['dock_sorrel']);

  unset($form_state['input']['bluegrass_kentucky']);
  unset($form_state['input']['corn_cultivated']);
  unset($form_state['input']['oats_common']);
  unset($form_state['input']['orchard_grass']);
  unset($form_state['input']['redtop']);
  unset($form_state['input']['positive_histamine']);
  unset($form_state['input']['negative_glycerine']);
  unset($form_state['input']['phenol']);
  unset($form_state['input']['bahia_grass']);
  unset($form_state['input']['johnson_grass']);

  unset($form_state['input']['sweet_vernalgrass']);
  unset($form_state['input']['boxelder_maple']);
  unset($form_state['input']['cedar_mountain']);
  unset($form_state['input']['common_privet']);
  unset($form_state['input']['cottonwood']);
  unset($form_state['input']['bermuda_grass']);
  unset($form_state['input']['meadow_fescue']);
  unset($form_state['input']['rye_grass']);
  unset($form_state['input']['timothy']);
  unset($form_state['input']['brome_smooth']);

  unset($form_state['input']['casein']);
  unset($form_state['input']['milk_cow']);
  unset($form_state['input']['egg_chicken_white']);
  unset($form_state['input']['peanut']);
  unset($form_state['input']['soybean']);
  unset($form_state['input']['pecan']);
  unset($form_state['input']['shellfish_mix']);
  unset($form_state['input']['shrimp']);

// create form

  $form['test_date_header'] = array (
    '#type' => 'item',
    '#title' => t('Testing Date'),
    '#suffix' => '<table>',
  );

  $form['test_date_month'] = array (
    '#type' => 'textfield',
    '#title' => t('Month (mm)'),
    '#size' => 16,
    '#default_value' => $test_date_month,
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
    '#required' => TRUE,
  );

  $form['test_date_day'] = array (
    '#type' => 'textfield',
    '#title' => t('Date (dd)'),
    '#size' => 16,
    '#default_value' => $test_date_day,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
    '#required' => TRUE,
  );

  $form['test_date_year'] = array (
    '#type' => 'textfield',
    '#title' => t('Year (yyyy)'),
    '#size' => 16,
    '#default_value' => $test_date_year,
    '#prefix' => '<td>',
    '#suffix' => '</td></tr></table>',
    '#required' => TRUE,
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
    '#prefix' => '</table><hr><table>',
  );

  $form['lambs_quarter'] = array (
    '#type' => 'textfield',
    '#title' => t('Lambs Quarter'),
    '#size' => 16,
    '#default_value' => $lambs_quarter,
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['palintain'] = array (
    '#type' => 'textfield',
    '#title' => t('Palintain'),
    '#size' => 16,
    '#default_value' => $palintain,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['ragweed_mix_gs'] = array (
    '#type' => 'textfield',
    '#title' => t('Ragweed Mix GS'),
    '#size' => 16,
    '#default_value' => $ragweed_mix_gs,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['marchelder'] = array (
    '#type' => 'textfield',
    '#title' => t('Marchelder/Poverty Mix'),
    '#size' => 16,
    '#default_value' => $marchelder,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['dog_fennel'] = array (
    '#type' => 'textfield',
    '#title' => t('Dog Fennel'),
    '#size' => 16,
    '#default_value' => $dog_fennel,
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );

  $form['elm_american'] = array (
    '#type' => 'textfield',
    '#title' => t('Elm American'),
    '#size' => 16,
    '#default_value' => $elm_american,
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['oak_mix'] = array (
    '#type' => 'textfield',
    '#title' => t('Oak Mix'),
    '#size' => 16,
    '#default_value' => $oak_mix,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['pecan_tree'] = array (
    '#type' => 'textfield',
    '#title' => t('Pecan Tree'),
    '#size' => 16,
    '#default_value' => $pecan_tree,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['sweet_gum'] = array (
    '#type' => 'textfield',
    '#title' => t('Sweet Gum'),
    '#size' => 16,
    '#default_value' => $sweet_gum,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['walnut_black'] = array (
    '#type' => 'textfield',
    '#title' => t('Walnut Black'),
    '#size' => 16,
    '#default_value' => $walnut_black,
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );






  $form['antigen_p5'] = array (
    '#type' => 'item',
    '#title' => t('Antigen Panel #5'),
    '#prefix' => '</table><hr><table>',
  );

  $form['alternariatenuis'] = array (
    '#type' => 'textfield',
    '#title' => t('Alternariatenuis'),
    '#size' => 16,
    '#default_value' => $alternariatenuis,
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['aspergillus_fumigatus'] = array (
    '#type' => 'textfield',
    '#title' => t('Aspergillus fumigatus'),
    '#size' => 16,
    '#default_value' => $aspergillus_fumigatus,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['botrytis_cinerea'] = array (
    '#type' => 'textfield',
    '#title' => t('Botrytis Cinerea'),
    '#size' => 16,
    '#default_value' => $botrytis_cinerea,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['candida'] = array (
    '#type' => 'textfield',
    '#title' => t('Candida'),
    '#size' => 16,
    '#default_value' => $candida,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['cephalosporium'] = array (
    '#type' => 'textfield',
    '#title' => t('Cephalosporium'),
    '#size' => 16,
    '#default_value' => $cephalosporium,
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );

  $form['pine_mix'] = array (
    '#type' => 'textfield',
    '#title' => t('Pine Mix'),
    '#size' => 16,
    '#default_value' => $pine_mix,
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['sycamore_american'] = array (
    '#type' => 'textfield',
    '#title' => t('Sycamore American'),
    '#size' => 16,
    '#default_value' => $sycamore_american,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );


  $form['careless_pigweed'] = array (
    '#type' => 'textfield',
    '#title' => t('Careless/Pigweed'),
    '#size' => 16,
    '#default_value' => $careless_pigweed,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['cocklebur'] = array (
    '#type' => 'textfield',
    '#title' => t('Cocklbur'),
    '#size' => 16,
    '#default_value' => $cocklebur,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['dock_sorrel'] = array (
    '#type' => 'textfield',
    '#title' => t('Dock/Sorrel'),
    '#size' => 16,
    '#default_value' => $dock_sorrel,
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );






  $form['antigen_p1'] = array (
    '#type' => 'item',
    '#title' => t('Antigen Panel #1'),
    '#prefix' => '</table><hr><table>',
  );

  $form['bluegrass_kentucky'] = array (
    '#type' => 'textfield',
    '#title' => t('Bluegrass Kentucky'),
    '#size' => 16,
    '#default_value' => $bluegrass_kentucky,
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['corn_cultivated'] = array (
    '#type' => 'textfield',
    '#title' => t('Corn Cultivated'),
    '#size' => 16,
    '#default_value' => $corn_cultivated,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['oats_common'] = array (
    '#type' => 'textfield',
    '#title' => t('Oats common'),
    '#size' => 16,
    '#default_value' => $oats_common,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['orchard_grass'] = array (
    '#type' => 'textfield',
    '#title' => t('Orchard Grass'),
    '#size' => 16,
    '#default_value' => $orchard_grass,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['redtop'] = array (
    '#type' => 'textfield',
    '#title' => t('Redtop'),
    '#size' => 16,
    '#default_value' => $redtop,
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );

  $form['positive_histamine'] = array (
    '#type' => 'textfield',
    '#title' => t('Positive/Histamine'),
    '#size' => 16,
    '#default_value' => $positive_histamine,
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['negative_glycerine'] = array (
    '#type' => 'textfield',
    '#title' => t('Negative/Glycerine'),
    '#size' => 16,
    '#default_value' => $negative_glycerine,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['phenol'] = array (
    '#type' => 'textfield',
    '#title' => t('Phenol'),
    '#size' => 16,
    '#default_value' => $phenol,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['bahia_grass'] = array (
    '#type' => 'textfield',
    '#title' => t('Bahia Grass'),
    '#size' => 16,
    '#default_value' => $bahia_grass,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['johnson_grass'] = array (
    '#type' => 'textfield',
    '#title' => t('Johnson Grass'),
    '#size' => 16,
    '#default_value' => $johnson_grass,
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );

  $form['antigen_p6'] = array (
    '#type' => 'item',
    '#title' => t('Antigen Panel #6'),
    '#prefix' => '</table><hr><table>',
  );

  $form['sweet_vernalgrass'] = array (
    '#type' => 'textfield',
    '#title' => t('Sweet Vernalgrass'),
    '#size' => 16,
    '#default_value' => $sweet_vernalgrass,
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['boxelder_maple'] = array (
    '#type' => 'textfield',
    '#title' => t('Boxelder Maple'),
    '#size' => 16,
    '#default_value' => $boxelder_maple,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['cedar_mountain'] = array (
    '#type' => 'textfield',
    '#title' => t('Cedar Mountain'),
    '#size' => 16,
    '#default_value' => $cedar_mountain,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['common_privet'] = array (
    '#type' => 'textfield',
    '#title' => t('Common Privet'),
    '#size' => 16,
    '#default_value' => $common_privet,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['cottonwood'] = array (
    '#type' => 'textfield',
    '#title' => t('Cottonwood'),
    '#size' => 16,
    '#default_value' => $cottonwood,
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );

  $form['bermuda_grass'] = array (
    '#type' => 'textfield',
    '#title' => t('Bermuda Grass'),
    '#size' => 16,
    '#default_value' => $bermuda_grass,
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['meadow_fescue'] = array (
    '#type' => 'textfield',
    '#title' => t('Meadow Fescue'),
    '#size' => 16,
    '#default_value' => $meadow_fescue,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['rye_grass'] = array (
    '#type' => 'textfield',
    '#title' => t('Rye Grass'),
    '#size' => 16,
    '#default_value' => $rye_grass,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['timothy'] = array (
    '#type' => 'textfield',
    '#title' => t('Timothy'),
    '#size' => 16,
    '#default_value' => $timothy,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['brome_smooth'] = array (
    '#type' => 'textfield',
    '#title' => t('Brome Smooth'),
    '#size' => 16,
    '#default_value' => $brome_smooth,
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );

  $form['food_allergy'] = array (
    '#type' => 'item',
    '#title' => t('Food Allergy Profile'),
    '#prefix' => '</table><hr><table>',
  );

  $form['casein'] = array (
    '#type' => 'textfield',
    '#title' => t('Casein'),
    '#size' => 16,
    '#default_value' => $casein,
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['milk_cow'] = array (
    '#type' => 'textfield',
    '#title' => t('Milk, Cow'),
    '#size' => 16,
    '#default_value' => $milk_cow,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['egg_chicken_white'] = array (
    '#type' => 'textfield',
    '#title' => t('Egg, Checken, White'),
    '#size' => 16,
    '#default_value' => $egg_chicken_white,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['peanut'] = array (
    '#type' => 'textfield',
    '#title' => t('Peanut'),
    '#size' => 16,
    '#default_value' => $peanut,
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );

  $form['soybean'] = array (
    '#type' => 'textfield',
    '#title' => t('Soybean'),
    '#size' => 16,
    '#default_value' => $soybean,
    '#prefix' => '<tr><td>',
    '#suffix' => '</td>',
  );

  $form['pecan'] = array (
    '#type' => 'textfield',
    '#title' => t('Pecan'),
    '#size' => 16,
    '#default_value' => $pecan,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['shellfish_mix'] = array (
    '#type' => 'textfield',
    '#title' => t('Shellfish, Mix'),
    '#size' => 16,
    '#default_value' => $shellfish_mix,
    '#prefix' => '<td>',
    '#suffix' => '</td>',
  );

  $form['shrimp'] = array (
    '#type' => 'textfield',
    '#title' => t('Shrimp'),
    '#size' => 16,
    '#default_value' => $shrimp,
    '#prefix' => '<td>',
    '#suffix' => '</td></tr></table>',
  );



  $form['back'] = array (
    '#type' => 'submit',
    '#value' => t('<< Back'),
    '#submit' => array('rmsallergy_add_profile_p3_back_submit' ),
    '#validate' => array('rmsallergy_add_profile_p3_back_validate' ),
    '#limit_validation_errors' => array (),
  );

  $form['next'] = array (
    '#type' => 'submit',
    '#value' => t('Create Referral'),
    '#submit' => array('rmsallergy_add_profile_p3_next_submit' ),
    '#validate' => array('rmsallergy_add_profile_p3_next_validate' ),
  );

  $form['submit'] = array (
    '#type' => 'submit',
    '#value' => t('Submit W/O Referring'),
    '#validate' => array('rmsallergy_add_profile_p3_validate' ),
    '#submit' => array('rmsallergy_add_profile_submit' ),
  );



  return $form;
}

function rmsallergy_add_profile_p3_back_validate ( $form, &$form_state )
{
// nothing to validate at this point
  return $form;
}

function rmsallergy_add_profile_p3_back_submit ( $form, &$form_state )
{
// values are saved for each page in order to carry to subsequent pages
// and to tell FAPI how to rebuild the form

  $form_state['page_values'][3] = $form_state['values'];

  if ( !empty($form_state['page_values'][2] )) {
    $form_state['values'] = $form_state['page_values'][2];
  }

  $form_state['page_num'] = 2;
  $form_state['rebuild'] = TRUE;

  return $form;
}

function rmsallergy_add_profile_p3_next_validate ( $form, &$form_state )
{
// nothing to validate at this point
  return $form;
}


function rmsallergy_add_profile_p3_next_submit ( $form, &$form_state )
{
// values are save for each page in order to carry to subsequent pages
// and to tell FAPI how to rebuild the form

  $form_state['page_values'][3] = $form_state['values'];

  if ( !empty($form_state['page_values'][4] )) {
    $form_state['values'] = $form_state['page_values'][4];
  }

  $form_state['page_num'] = 4;
  $form_state['rebuild'] = TRUE;

//  return $form;
}


function rmsallergy_add_profile_p3_validate ( $form, &$form_state )
{
// data will be pulled out from $form_state['page_values'] array
// verify that this array exists.  if the user never goes back, this array
// may not exist.

// check for $form_state['page_values'][3]  this array may not exist if the
// user submits a profile without a referal. in this case, we are coming from
// page 3 of the form.  we might need to do other validation on dates as well.


  if ( empty ( $form_state['page_values'][3] )) {
    $form_state['page_values'][3] = $form_state['values'];
  }


// also, we need to check that $form_state['page_values'][4] remains
// empty.  the submit routine will check that value to determine if the
// referral should be created

  if ( ! empty ( $form_state['page_values'][4] )) {
    $form_state['page_values'][4] = 0;
  }

  return $form;
}

?>
