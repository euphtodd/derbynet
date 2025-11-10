<?php
// header.inc - Custom Pintwood Derby Header
// This file replaces the standard DerbyNet header with Pintwood Derby branding

require_once('sponsors.inc');

function render_pintwood_header($page_title = '', $show_back_button = false, $back_url = 'index.php') {
    ?>
    <div class="pintwood-header">
        <div class="header-left">
            <?php if ($show_back_button): ?>
                <button class="back-button" onclick="window.location.href='<?php echo htmlspecialchars($back_url); ?>'">
                    ← Back
                </button>
            <?php endif; ?>
            <div class="event-logo">
                <img src="/derbynet-data/pintwood-logo.png" alt="Pintwood Derby Logo" />
                <div class="event-wordmark">Monon District<br>Pintwood Derby</div>
            </div>
        </div>
        
        <?php if (!empty($page_title)): ?>
        <div class="header-center">
            <h1 class="page-title"><?php echo htmlspecialchars($page_title); ?></h1>
        </div>
        <?php endif; ?>
        
        <div class="header-right">
            <?php echo render_title_sponsor(); ?>
        </div>
    </div>
    <?php
}

// Function to replace default DerbyNet banner
function replace_default_banner($page_title = '', $show_back = false) {
    // Hide the default DerbyNet banner if it exists
    echo '<style>#derby_nav_bar, .navbar, .banner { display: none !important; }</style>';
    
    // Render our custom header
    render_pintwood_header($page_title, $show_back);
}
?>
