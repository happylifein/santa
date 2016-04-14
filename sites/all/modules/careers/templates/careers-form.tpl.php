<?php // Change the labels of the "name" and "mail" textfields.
$form['name']['#title'] = t('Name');
$form['email']['#title'] = t('E-mail');
$form['resume']['#title'] = t('Resume');
?>
<?php // Render the "name" and "mail" elements individually and add markup. ?>
<div class="name-and-email">
  <p><?php print t("Please upload your profile here"); ?></p>

  <table>
    <tr>
      <td><?php print render($form['name']); ?></td>
       <td><?php print render($form['email']); ?></td>
    </tr>
    <tr>
      <td><?php print render($form['resume']); ?></td>
      <td><?php print render($form['submit_button']); ?></td>
    </tr>

  </table>
</div>
<?php print drupal_render_children($form); ?>
