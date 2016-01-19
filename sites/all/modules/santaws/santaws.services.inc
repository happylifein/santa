<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

function santaws_services_resources() {
    $resources = array(
      'santaws_resources' => array(
        'operations' => array(
          'retrieve' => array(
            'help' => 'Retrieves a note',
            'file' => array(
              'type' => 'inc',
              'module' => 'santaws',
              'name' => 'santaws.resource',
            ),
            'callback' => 'santaws_get_user_count',
            'access callback' => 'user_access',
            'access arguments' => array('access content'),
            'access arguments append' => FALSE,
            'args' => array(
              array(
                'name' => 'id',
                'type' => 'int',
                'description' => 'The id of the note to get',
                'source' => array('path' => '0'),
                'optional' => FALSE,
              ),
            ),
          ),
          'index' => array(
            'help' => 'Retrieves a listing of notes',
            'file' => array(
              'type' => 'inc',
              'module' => 'santaws',
              'name' => 'santaws.resource'
            ),
            'callback' => 'santaws_get_user_count',
            'access callback' => 'user_access',
            'access arguments' => array('access content'),
            'access arguments append' => FALSE,
            'args' => array(array(
                'name' => 'page',
                'type' => 'int',
                'description' => '',
                'source' => array(
                  'param' => 'page',
                ),
                'optional' => TRUE,
                'default value' => 0,
              ),
              array(
                'name' => 'parameters',
                'type' => 'array',
                'description' => '',
                'source' => 'param',
                'optional' => TRUE,
                'default value' => array(),
              ),
            ),
          ),
        ),
      ),
    );
    return $resources;
}
