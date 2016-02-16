<?php
//require_once './includes/bootstrap.inc';
//drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);

define('DRUPAL_ROOT', getcwd());
require_once DRUPAL_ROOT . '/includes/bootstrap.inc';
$_SERVER['REMOTE_ADDR'] = '127.0.0.1';

class TddTests extends PHPUnit_Framework_TestCase
{
  public function test_tdd_help()
  {
    $this->assertEquals(tdd_help('admin/content/tdd'), "<p>Help for TDD module.</p>");
  }
}
?>
