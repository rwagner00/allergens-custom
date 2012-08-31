<?php

/**
 * @file
 * RMS Allergy function file
 */


function rmsallergy_view_outgoing ( $form, &$form_state )
{
  if ( !empty ( $form_state['page_num'] )) {
    if ( $form_state['page_num'] == 1 ) {
      return rmsallergy_view_outgoing_p1 ( $form, $form_state );
    } elseif ( $form_state['page_num'] == 2 ) {
      return rmsallergy_view_outgoing_p2 ( $form, $form_state );
    }
  } else {
    return rmsallergy_view_outgoing_p1 ( $form, $form_state );
  }
}

include ( "rmsallergy_view_outgoing_p1.inc" );
include ( "rmsallergy_view_outgoing_p2.inc" );


function rmsallergy_view_outgoing_validate ( $form, &$form_state )
{
  return $form;
}

function rmsallergy_view_outgoing_submit ( $form, &$form_state )
{
  return $form;
}
