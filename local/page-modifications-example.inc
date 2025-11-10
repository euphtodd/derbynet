<?php
// page-modifications-example.inc
// This file shows how to modify existing DerbyNet pages to include Pintwood customizations
// Copy these code snippets into the appropriate pages

/* ===========================================================================
   EXAMPLE MODIFICATIONS FOR index.php
   Add these at the appropriate locations in the file
   =========================================================================== */

// At the very top of index.php, after <?php tag:
require_once('inc/theme-selector.inc');
session_start();

// In the <head> section:
?>
<head>
    <!-- Existing head content -->
    <?php pintwood_head_includes(); ?>
</head>
<?php

// After the opening <body> tag:
require_once('inc/header.inc');
require_once('inc/footer.inc');

// Replace the existing header/banner:
replace_default_banner('Welcome to Pintwood Derby', false);

// Before the closing </body> tag:
if (should_use_pintwood_theme()) {
    add_pintwood_footer();
}

/* ===========================================================================
   EXAMPLE MODIFICATIONS FOR login.php
   =========================================================================== */

// At the top:
require_once('inc/theme-selector.inc');

// In <head>:
pintwood_head_includes();

// After <body>:
require_once('inc/header.inc');
replace_default_banner('Login', true, 'index.php');

/* ===========================================================================
   EXAMPLE MODIFICATIONS FOR racer-results.php
   =========================================================================== */

// At the top:
require_once('inc/theme-selector.inc');

// In <head>:
pintwood_head_includes();

// After <body>:
require_once('inc/header.inc');
require_once('inc/footer.inc');
replace_default_banner('Race Results', true, 'index.php');

// Before </body>:
if (should_use_pintwood_theme()) {
    add_pintwood_footer();
}

/* ===========================================================================
   HIDING BUTTONS FOR NON-LOGGED-IN USERS
   Add this JavaScript to index.php
   =========================================================================== */
?>
<script>
document.addEventListener('DOMContentLoaded', function() {
    <?php if (!isset($_SESSION['role']) || empty($_SESSION['role'])): ?>
    // Hide admin buttons for non-logged-in users
    var buttonsToHide = [
        '.control_group',
        '.coordinator-only', 
        '[onclick*="coordinator"]',
        '[onclick*="checkin"]',
        '[onclick*="photo"]',
        '[onclick*="settings"]',
        '[onclick*="kiosk.php"]' // Except the sponsor kiosk
    ];
    
    buttonsToHide.forEach(function(selector) {
        var elements = document.querySelectorAll(selector);
        elements.forEach(function(el) {
            // Don't hide the sponsor kiosk link
            if (!el.href || el.href.indexOf('sponsors.kiosk.php') === -1) {
                el.style.display = 'none';
            }
        });
    });
    
    // Add a link to the sponsor kiosk if not already present
    var kioskLinks = document.querySelector('.kiosk-links');
    if (kioskLinks) {
        var sponsorLink = document.createElement('a');
        sponsorLink.href = 'sponsors.kiosk.php';
        sponsorLink.className = 'kiosk-link';
        sponsorLink.textContent = 'View Sponsors';
        kioskLinks.appendChild(sponsorLink);
    }
    <?php endif; ?>
});
</script>
<?php

/* ===========================================================================
   NOTES FOR IMPLEMENTATION:
   1. These are example snippets - you'll need to adapt them to the actual
      structure of each DerbyNet page
   2. Session handling may vary - check how DerbyNet handles user sessions
   3. Test thoroughly after each modification
   4. Keep backups of original files before modifying
   =========================================================================== */
?>
