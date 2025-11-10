<?php
// sponsors.kiosk.php - Rotating sponsor display kiosk for Pintwood Derby
session_start();
require_once('inc/sponsors.inc');
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="refresh" content="1800"> <!-- Refresh page every 30 minutes -->
    <title>Pintwood Derby Sponsors</title>
    <link rel="stylesheet" href="css/pintwood-theme.css">
    <style>
        body {
            margin: 0;
            padding: 0;
            overflow: hidden;
        }
        .sponsor-kiosk {
            cursor: none; /* Hide cursor for kiosk mode */
        }
    </style>
    <?php echo render_kiosk_sponsor_data(); ?>
</head>
<body class="pintwood-dark">
    <div class="sponsor-kiosk" id="sponsorKiosk">
        <div class="sponsor-display" id="sponsorDisplay">
            <!-- Content will be dynamically inserted here -->
        </div>
    </div>

    <script>
    (function() {
        var currentIndex = 0;
        var displayElement = document.getElementById('sponsorDisplay');
        
        function getTierLabel(tier) {
            var labels = {
                'keg': 'Title Sponsor',
                'growler': 'Growler Sponsor',
                'liter': 'Liter Sponsor',
                'pint': 'Pint Sponsor'
            };
            return labels[tier] || tier;
        }
        
        function showSponsor() {
            if (!sponsorData || sponsorData.length === 0) {
                displayElement.innerHTML = '<div class="sponsor-name">No sponsors configured</div>';
                return;
            }
            
            var sponsor = sponsorData[currentIndex];
            
            // Fade out
            displayElement.style.animation = 'none';
            displayElement.offsetHeight; // Trigger reflow
            displayElement.style.animation = null;
            
            // Update content
            var html = '';
            html += '<img src="' + sponsor.logo + '" alt="' + sponsor.name + '" class="sponsor-logo">';
            html += '<div class="sponsor-name">' + sponsor.name + '</div>';
            html += '<div class="sponsor-tier-label">' + getTierLabel(sponsor.tier) + '</div>';
            
            displayElement.innerHTML = html;
            
            // Move to next sponsor
            currentIndex = (currentIndex + 1) % sponsorData.length;
        }
        
        // Initialize display
        if (typeof sponsorData !== 'undefined' && sponsorData.length > 0) {
            showSponsor();
            
            // Set up rotation
            if (sponsorData.length > 1) {
                setInterval(showSponsor, rotationInterval || 5000);
            }
        } else {
            displayElement.innerHTML = '<div class="sponsor-name">Loading sponsors...</div>';
        }
        
        // Optional: Exit kiosk mode with ESC key
        document.addEventListener('keydown', function(e) {
            if (e.key === 'Escape') {
                window.location.href = 'index.php';
            }
        });
    })();
    </script>
</body>
</html>
