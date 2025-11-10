<?php
// theme-selector.inc - Determines which pages get the Pintwood dark theme
// This file should be included at the top of every PHP page

function should_use_pintwood_theme() {
    // Get current page name
    $current_page = basename($_SERVER['PHP_SELF']);
    
    // List of public-facing pages that should use the dark theme
    $public_pages = array(
        'index.php',
        'login.php',
        'racer-results.php',
        'slideshow.php',
        'kiosk.php',
        'sponsors.kiosk.php',  // Our custom sponsor kiosk
        'ondeck.php',
        'now-racing.php',
        'awards.php'
    );
    
    // Check if current page is in the public pages list
    if (in_array($current_page, $public_pages)) {
        return true;
    }
    
    // Check if it's a kiosk page (they often have parameters)
    if (strpos($current_page, 'kiosk') !== false) {
        return true;
    }
    
    return false;
}

function apply_pintwood_theme() {
    if (should_use_pintwood_theme()) {
        // Add dark theme class to body
        echo '<script>document.addEventListener("DOMContentLoaded", function() { document.body.classList.add("pintwood-dark"); });</script>';
        
        // Include the custom CSS
        echo '<link rel="stylesheet" href="css/pintwood-theme.css">';
        
        // Check if user is logged in (you may need to adjust this based on DerbyNet's session handling)
        session_start();
        if (!isset($_SESSION['role']) || empty($_SESSION['role'])) {
            echo '<script>document.addEventListener("DOMContentLoaded", function() { document.body.classList.add("not-logged-in"); });</script>';
        }
    }
}

// Function to be called in the <head> section
function pintwood_head_includes() {
    apply_pintwood_theme();
}
?>
