<?php

/**
 * @file
 * RMS Allergy function file
 */


function rmsallergy_administration_form () {
  $form = array ();

  $form['subtitle'] = array (
    '#type' => 'item',
    '#title' => t('Select from the Following Options:'),
  );

/*
  $form['link1'] = array (
    '#type' => 'item',
    '#title' => t('<a href="?q=rmsadmin/add_practice">Add New Practice</a>'),
  );

  $form['link2'] = array (
    '#type' => 'item',
    '#title' => t('<a href="?q=rmsadmin/add_physician">Add New Physician</a>'),
  );

  $form['link3'] = array (
    '#type' => 'item',
    '#title' => t('<a href="?q=rmsadmin/view_practice">View Practice</a>'),
  );

  $form['link4'] = array (
    '#type' => 'item',
    '#title' => t('<a href="?q=rmsadmin/view_physician">View Physician</a>'),
  );
*/

  return $form;
}

