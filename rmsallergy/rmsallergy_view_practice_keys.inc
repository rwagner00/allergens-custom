<?php

/**
 * @file
 * RMS Allergy function file
 */

function rmsallergy_view_practice_keys ( $form, &$form_state )
{

// build the table of practices

  $form['subtitle'] = array (
    '#type' => 'item',
    '#title' => t('Practice Keys'),
  );

// code snippet to get practice key from user account
//  global $user;
//  $account = user_load ( $user->uid );
//  $practice_key = field_get_items ( 'user', $account, 'field_practice_key' );
//  $practice_key = $practice_key[0]['value'];


// query database for list of practices

  db_set_active ( 'rmsallergy' );
  $query = db_select ( 'practice', 'p' );
  $query->fields ( 'p', array ( 'practice_key',
                            'practice_name',))
        ->orderBy ( 'practice_name', 'ASC' );
  $result = $query->execute();
  db_set_active ();

// copy practices into array for the table

  $options = array ();
  foreach ( $result as $record ) {
    $options [ $record->practice_key ] = array (
      'practice_name' => $record->practice_name,
      'practice_key' => $record->practice_key,
    );
  }

  $header = array (
    'practice_name' => t('Practice Name'),
    'practice_key' => t('Practice Key'),
  );

  $form['table'] = array (
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#empty' => t('No practices in database'),
    '#multiple' => FALSE,
  );

  return $form;
}

