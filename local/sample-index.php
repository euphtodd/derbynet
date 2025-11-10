<?php
// SAMPLE: Modified index.php for Pintwood Derby
// This shows how to integrate all customizations into DerbyNet's index.php

session_start();
require_once('inc/theme-selector.inc');

// Original DerbyNet includes would go here
// require_once('inc/data.inc');
// require_once('inc/authorize.inc');
// etc...

?><!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8"/>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Pintwood Derby - Race Management</title>
    
    <!-- Original DerbyNet CSS files would be here -->
    <link rel="stylesheet" type="text/css" href="css/jquery.mobile-1.4.5.css"/>
    <link rel="stylesheet" type="text/css" href="css/main-elements.css"/>
    
    <!-- Pintwood Theme Integration -->
    <?php pintwood_head_includes(); ?>
    
    <!-- Original DerbyNet JavaScript files would be here -->
    <script type="text/javascript" src="js/jquery.js"></script>
    <script type="text/javascript" src="js/jquery.mobile-1.4.5.min.js"></script>
</head>
<body>
    <?php
    // Include our custom header and footer handlers
    require_once('inc/header.inc');
    require_once('inc/footer.inc');
    
    // Display custom header (replaces DerbyNet banner)
    replace_default_banner('Welcome', false);
    
    // Check if user is logged in (adjust based on DerbyNet's actual session handling)
    $logged_in = isset($_SESSION['role']) && !empty($_SESSION['role']);
    ?>
    
    <div class="main-content">
        <!-- Public buttons - always visible -->
        <div class="button-group public-buttons">
            <a href="racer-results.php" class="button">View Results</a>
            <a href="sponsors.kiosk.php" class="button">Sponsor Display</a>
            <a href="login.php" class="button">Login</a>
        </div>
        
        <?php if ($logged_in): ?>
        <!-- Admin buttons - only visible when logged in -->
        <div class="button-group admin-buttons">
            <h3>Race Management</h3>
            <a href="coordinator.php" class="button coordinator-only">Coordinator Dashboard</a>
            <a href="checkin.php" class="button">Check-In</a>
            <a href="photo-capture.php" class="button">Photo Capture</a>
            <a href="judging.php" class="button">Judging</a>
            <a href="racer-card-editor.php" class="button">Racer Cards</a>
        </div>
        
        <div class="button-group kiosk-buttons">
            <h3>Kiosk Displays</h3>
            <a href="kiosk.php?page=now-racing" class="button">Now Racing</a>
            <a href="kiosk.php?page=ondeck" class="button">On Deck</a>
            <a href="slideshow.php" class="button">Results Slideshow</a>
            <a href="awards.php" class="button">Awards</a>
        </div>
        <?php else: ?>
        <!-- Message for non-logged-in users -->
        <div class="welcome-message">
            <h2>Monon District Pintwood Derby</h2>
            <p>February 21, 2026 at Liter House</p>
            <p>Please login to access race management features.</p>
        </div>
        <?php endif; ?>
        
        <!-- Event information -->
        <div class="event-info">
            <h3>Event Information</h3>
            <p>A 21+ pinewood derby fundraiser for Scouting</p>
            <p>Learn more at <a href="https://indypintwoodderby.com" target="_blank">indypintwoodderby.com</a></p>
        </div>
    </div>
    
    <?php
    // Add sponsor footer on public pages
    if (should_use_pintwood_theme()) {
        add_pintwood_footer();
    }
    ?>
    
    <script>
    // Additional JavaScript to hide buttons for non-logged-in users
    document.addEventListener('DOMContentLoaded', function() {
        <?php if (!$logged_in): ?>
        // Hide any DerbyNet default admin buttons that might still be visible
        var selectorsToHide = [
            '.control_group',
            '[onclick*="coordinator"]',
            '[onclick*="settings"]',
            '.timer-button',
            '.export-button'
        ];
        
        selectorsToHide.forEach(function(selector) {
            var elements = document.querySelectorAll(selector);
            elements.forEach(function(el) {
                el.style.display = 'none';
            });
        });
        <?php endif; ?>
    });
    </script>
</body>
</html>
