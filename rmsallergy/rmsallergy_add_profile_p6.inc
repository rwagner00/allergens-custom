<?php

function rmsallergy_add_profile_p6 ( $form, &$form_state )
{
// extract ent practices from database

  db_set_active ( 'rmsallergy' );

  $query = db_select ( 'practice', 'p' );
  $query
    ->fields ( 'p', array ( 'practice_key',
                            'practice_name',
                            'practice_specialty',
                            'practice_fax',
                          ))
    ->condition ( 'practice_specialty', '1' )
    ->orderBy ( 'practice_name', 'ASC' );

  $result = $query->execute();

  db_set_active ();

// build tableselect object

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
      'practice_fax' => $record->practice_fax,
    );
  }

  $header = array (
    'practice_name' => t('Practice Name'),
    'practice_specialty' => t('Practice Specialty'),
    'practice_fax' => t('Practice Fax Number'),
  );

  $form['prompt'] = array (
    '#type' => 'item',
    '#title' => t('Select practice for referal'),
  );

  $form['table'] = array (
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#empty' => t('No Practices in Database'),
    '#multiple' => FALSE,
  );


  $form['back'] = array (
    '#type' => 'submit',
    '#value' => t('<< Back'),
    '#submit' => array('rmsallergy_add_profile_p6_back_submit' ),
    '#validate' => array('rmsallergy_add_profile_p6_back_validate' ),
  );

  $form['submit'] = array (
    '#type' => 'submit',
    '#value' => t('Submit'),
    '#submit' => array('rmsallergy_add_profile_submit' ),
    '#validate' => array('rmsallergy_add_profile_validate' ),
  );

  return $form;
}
function rmsallergy_add_profile_p6_back_validate ( $form, &$form_state )
{
// nothing to validate at this point
  return $form;
}

function rmsallergy_add_profile_p6_back_submit ( $form, &$form_state )
{
// values are save for each page in order to carry to subsequent pages
// and to tell FAPI how to rebuild the form

  $form_state['page_values'][6] = $form_state['values'];

  if ( !empty($form_state['page_values'][5]) ) {
    $form_state['page_values'][5] = NULL;
  }

  if ( !empty($form_state['page_values'][4]) ) {
    $form_state['values'] = $form_state['page_values'][4];
  }

  $form_state['page_num'] = 4;
  $form_state['rebuild'] = TRUE;

  return $form;
}

















?>
