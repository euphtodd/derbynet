<?php
// footer.inc - Pintwood Derby Footer with Sponsors
// This file adds a footer with sponsor logos to designated pages

require_once('sponsors.inc');

function render_pintwood_footer() {
    // Add the has-sponsor-footer class to body for proper spacing
    echo '<script>document.body.classList.add("has-sponsor-footer");</script>';
    
    // Render the sponsor footer
    echo render_footer_sponsors();
}

// Function to include footer on appropriate pages
function add_pintwood_footer() {
    render_pintwood_footer();
}
?>
