<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

function santaws_read_node() {
    //return db_select('node', 'n')->fields('n', array('nid', 'title'))->execute()->fetchAll(PDO::FETCH_ASSOC); //db_query("SELECT * FROM {node}")->fetchField();
    $query = db_select('node', 'n');
    $query->addField('n', 'nid', 'Name');
    $query->addField('n', 'title', 'Country');
    $json['records'] = $query->execute()->fetchAll(PDO::FETCH_ASSOC);
    return $json;
}
