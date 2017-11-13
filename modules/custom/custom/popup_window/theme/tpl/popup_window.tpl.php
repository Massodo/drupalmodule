<?php

/**
 * @file
 * Default template for popup_window.
 */
?>
<div id="popup-overlay"></div>
<div id="popup">
  <div class="popup-bar">Status Messages<span class="btn-close">[X]</span></div>
  <div class="popup-content">
    <?php
    $output = '';

    foreach ($status_messages as $type => $messages) {
      $output .= "<div class=\"messages $type\">\n";
      if (!empty($status_heading[$type])) {
        $output .= '<h2 class="element-invisible">' . $status_heading[$type] . "</h2>\n";
      }
      if (count($messages) > 1) {
        $output .= " <ul>\n";
        foreach ($messages as $message) {
          $output .= '  <li>' . $message . "</li>\n";
        }
        $output .= " </ul>\n";
      }
      else {
        $output .= reset($messages);
      }
      $output .= "</div>\n";
    }

    echo $output;
    ?>
  </div>
</div>
