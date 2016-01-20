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
            'help' => 'Retrieves a records from node',
            'file' => array(
              'type' => 'inc',
              'module' => 'santaws',
              'name' => 'santaws.resource',
            ),
            'callback' => 'santaws_read_node',
            'access callback' => 'user_access',
            'access arguments' => array('access content'),
            'access arguments append' => FALSE,
            'args' => array(
              array(
                'name' => 'id',
                'type' => 'int',
                'description' => 'Retrieves a records from node',
                'source' => array('path' => '0'),
                'optional' => FALSE,
              ),
            ),
          ),
          'index' => array(
            'help' => 'Retrieves a records from node',
            'file' => array(
              'type' => 'inc',
              'module' => 'santaws',
              'name' => 'santaws.resource'
            ),
            'callback' => 'santaws_read_node',
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
