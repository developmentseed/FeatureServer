// $Id$

/**
 * JS behaviors for fserver.
 */
Drupal.behaviors.fserver = function() {
  $('#edit-field-fserver-method-value:not(.processed)').each(function() {
    $(this).addClass('processed');
    $(this).change(function() {
      switch ($(this).val()) {
        case '0':
          $('#edit-field-fserver-repository-0-value-wrapper').hide();
          break;
        default:
          $('#edit-field-fserver-repository-0-value-wrapper').show();
          break;
      }
    });
    $(this).change();
  });
};
