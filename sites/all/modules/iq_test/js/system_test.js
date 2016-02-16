
/**
 * @file
 * Result summary color will change to green
 */

(function($) {
Drupal.behaviors.myBehavior = {
  attach: function (context, settings) {
    if ($(".wizard-trail").length == 0) {
      $('#block-system-main .content').css('color','green');
      $('#block-system-main .content').append('Thank you for submitting the system test form.');
    }
  }
};
})(jQuery);