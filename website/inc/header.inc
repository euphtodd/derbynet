<?php
// header.inc - Custom Pintwood Derby Header
// This file replaces the standard DerbyNet header with Pintwood Derby branding

require_once('sponsors.inc');

function render_pintwood_header($page_title = '', $show_back_button = false, $back_url = 'index.php') {
    // Determine the correct path for the Pintwood logo
    // Try different possible locations
    $logo_path = 'images/Pintwood_Derby/pintwood-logo.png';  // Default relative path
    
    // Check if file exists in common locations and use appropriate web path
    if (file_exists($_SERVER['DOCUMENT_ROOT'] . '/images/pintwood-logo.png')) {
        $logo_path = '/images/pintwood-logo.png';
    } elseif (file_exists($_SERVER['DOCUMENT_ROOT'] . '/pintwood-logo.png')) {
        $logo_path = '/pintwood-logo.png';
    }
    // For local development, you might need to copy the logo to the website/images directory
    
    ?>
    <div class="pintwood-header">
        <div class="header-left">
            <?php if ($show_back_button): ?>
                <button class="back-button" onclick="window.location.href='<?php echo htmlspecialchars($back_url); ?>'">
                    ← Back
                </button>
            <?php endif; ?>
            <div class="event-logo">
                <img src="<?php echo $logo_path; ?>" alt="Pintwood Derby Logo" 
                     onerror="this.style.display='none'; console.error('Pintwood logo not found at: ' + this.src);" />
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
