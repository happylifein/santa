<?php

/**
 * @file
 * Page callback file for the careers module.
 */

 /**
 * Form creation
 */
function careers_form($form, &$form_state) {
  $form['name'] = array(
    '#type' => 'textfield', //you can find a list of available types in the form api
    '#title' => 'Name',
    '#size' => 40,
    '#maxlength' => 40,
    '#required' => TRUE, //make this field required
  );

  $form['email'] = array(
    '#type' => 'textfield', //you can find a list of available types in the form api
    '#title' => 'Email-ID',
    '#size' => 40,
    '#maxlength' => 40,
    '#required' => TRUE, //make this field required
  );

  $form['resume'] = array(
    '#type' => 'file', //managed_file
    '#title' => 'Resume Path',
    '#size' => 40,
    '#maxlength' => 40,
  );

  $form['submit_button'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  return $form;
}



/**
 * Implements form validation
 */
function careers_form_validate($form, &$form_state) {
   $valid_email = $form_state['values']['email'];
   if (!valid_email_address($valid_email)) {
     form_set_error('email', 'Please enter valid email id');
   }
}

/**
 * Implements form submit process
 */
function careers_form_submit($form, &$form_state) {
   $resumedirectory = variable_get('file_public_path', conf_path() . '/files/careers/');
  //If new directory path does not exist, create it.
  file_prepare_directory($resumedirectory, $mode = FILE_CREATE_DIRECTORY);

  $file = file_save_upload('resume', array('file_validate_extensions' => array('docx', 'doc'), FILE_EXISTS_REPLACE));
  $resumepath = basename($file->destination);

  // If the file passed validation:
  if ($file) {
    // Move the file, into the Drupal file system
    if ($file = file_move($file, 'public://careers/')) {
      // Save the file for use in the submit handler.
      $form_state['storage']['resume'] = $file;
    }
    else {
      form_set_error('resume', t('Failed to write the uploaded file the site\'s file folder.'));
    }
  }
  else {
    form_set_error('resume', t('No file was uploaded.'));
  }
  $name = $form_state['values']['name'];
  $email = $form_state['values']['email'];
  $submited_date = date('Y-m-d H:i:s', strtotime('now'));

  $id = db_insert('careers')
  ->fields(array('name', 'path', 'email', 'created'))
  ->values(array('name' => $name, 'path' => $resumepath, 'email' => $email, 'created' => $submited_date))
  ->execute();

   //send mail
  $to ='bharanikumariyer@gmail.com';       //gets the current user's mail address
  $from = variable_get('site_mail', '');    //admin's mail address
  $subject = $name . ' submited profile on ' . $submited_date;
  $body =  '<html>
               <body leftmargin="0" marginwidth="0" topmargin="0" marginheight="0" offset="0" bgcolor="#ffffff" >
               <p>Name: ' . $name . '</p>
               <p>Email: ' . $email . '</p>
               <p>Please find the attached resume '  . $resumepath . ' </p>
               </body></html>';;
  $attachment = array( 'filepath' => $file->uri, 'filename' => $file->filename, 'filemime' => $file->filemime );
  $params = array( 'subject' => $subject, 'body' => $body, 'attachment' => $attachment );
  $module = 'careers';
  $key = 'santa16';
  $message = drupal_mail($module, $key, $to, language_default(), $params, $from);
  //My success processing
  drupal_set_message(t('Hello @name, We have recieved your resume.', array('@name' => $name)), 'butterflies');
}

/**

 * Implementation of hook_mail().
 */
function careers_mail($key, &$message, $params) {
  switch ($key) {
    case "santa16":
      // Set the mail content type to html to send an html e-mail (optional).
      $message['headers']['Content-Type'] = 'text/html; charset=UTF-8; format=flowed';
      // Grab the subject and body from params and add it to the message.
      $message['subject'] = $params['subject'];
      $message['body'][] = $params['body'];
      if (isset($params['attachment'])) {
        $message['params']['attachments'][] = $params['attachment'];
      }
      break;
  }
}

/**
  * Add elements in tpl
  */
function careers_theme() {
  return array( 'careers_form' => array(
    'render element' => 'form',
    'path' => drupal_get_path('module', 'careers') . '/templates',
    'template' => 'careers-form',
    ),
  );
}

/**
  * display records from database
  */
function show_careers_list() {
   // we are going to output the results in a table with a nice header
  $header = array(
    array('data' => t('ID')),
    array('data' => t('Name')),
    array('data' => t('Email')),
    array('data' => t('Resume'))
  );

  // we are extending the PagerDefault class here
  // it has a default of 10 rows per page
  // the extend('PagerDefault') part here does all the magic.
  $query = db_select('careers', 'd')->extend('PagerDefault')->extend('TableSort');
  $query->fields('d', array('name', 'email', 'path', 'id', 'created'));
  $query->orderBy("id", "DESC");


  $result = $query
    ->limit(10)         // this is where you change the number of rows
    ->orderBy('d.id')
    ->execute();
   $resumeroot = variable_get('file_public_path', conf_path() . '/files/careers/');

  $rows = array();
  foreach ($result as $row) {
    // normally we would add some nice formatting to our rows
    // but for our purpose we are simply going to add our row
    // to the array.
   // $rows[] = array('data' => (array) $row);
    $options = array('absolute' => FALSE, 'attributes' => array('title' => $row->name));
    $resumepath = $resumeroot . $row->path;
    $download_url = l(t('Download'), $resumepath, $options);
    $rows[] = array($row->id, $row->name, $row->email, $download_url);
    $resumepath = "";
  }

  // Create a render array ($build) which will be themed as a table with a
  // pager.

  $build['pager_table'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    '#empty' => t('There are no date formats found in the db'),
  );

  // attach the pager theme
  $build['pager_pager'] = array('#theme' => 'pager');

  return $build;
}



