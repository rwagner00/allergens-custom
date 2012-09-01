<?php

  db_set_active ( 'rmsallergy' );

  $query = db_select ( 'practice', 'p' );
  $query
    ->fields ( 'p', array ( 'practice_key',
                            'practice_name',
                            'practice_specialty',
                            'practice_referring_flag',
                            'practice_referred_flag',
                            'practice_primary_contact_key' ))
    ->orderBy ( 'practice_name', 'ASC' );

  $result = $query->execute();

  db_set_active ();

  $practice_table_options = array ();
  foreach ( $result as $record ) {
    $practice_table_options [ $record->practice_key ] = array (
      'practice_name' => $record->practice_name,
      'practice_specialty' => $record->practice_specialty,
      'practice_referring_flag' => $record->practice_referring_flag,
      'practice_referred_flag' => $record->practice_referred_flag,
    );
  }

  $practice_table_header = array (
    'practice_name' => t('Practice Name'),
    'practice_specialty' => t('Practice Specialty'),
    'practice_referring_flag' => t('Practice Referring'),
    'practice_referred_flag' => t('Practice Referred'),
  );

?>
