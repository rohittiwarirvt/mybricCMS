<?php
/**
 * @file
 * Alpha's theme implementation to display a single Drupal page.
 */
?>
<div<?php print $attributes; ?>>
  <?php if (isset($page['header'])) : ?>
    <?php print render($page['header']); ?>
  <?php endif; ?>

  <?php if (isset($page['content'])) : ?>
    <?php print render($page['content']); ?>
  <?php endif; ?>
  <div class="page-navigation">
  <div class="page-navlink">
    <?php if(isset($previous)): ?>
      <?php print $previous; ?>
    <?php endif; ?>
    <?php if(isset($next)): ?>
      <?php print $next; ?>
    <?php endif; ?>
  </div>
  </div>

  <?php if (isset($page['footer'])) : ?>
    <?php print render($page['footer']); ?>
  <?php endif; ?>
</div>
