<?php

/**
 * @file
 * Template for Secure Site pages. Taken from modules/system/html.tpl.php
 *
 * @see template_preprocess_page()
 */
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
  <head >
    <?php print $head; ?>
    <title><?php print $head_title; ?></title>
    <?php print $styles; ?>
    <?php print $scripts; ?>
  </head>
  <body>

    <div id='content' class="<?php print $classes; ?>">
       <?php if (isset($messages)): print $messages; endif; ?>
      <?php print render($title_prefix); ?>
      <?php if ($title): ?><h1 id="page-title"><?php print $title; ?></h1><?php endif; ?>
      <?php print render($title_suffix); ?>
      <?php print $content ?>

  </div>
  <?php if( isset($destination)): ?>
  <input class ="redirecturl-active" type='hidden'  name='redirecturl' value='<?php print $destination;?>'>
<?php endif; ?>
  <div class="loader-wrapper"><?php print $loader ?></div></body>
</html>
