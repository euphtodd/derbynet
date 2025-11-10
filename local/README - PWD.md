# Pintwood Derby Customizations for DerbyNet

## Overview
This customization package transforms DerbyNet for the Monon District Pintwood Derby event at Liter House on February 21, 2026. It includes sponsor management, custom branding, dark theme styling, and event-specific features.

## File Structure

```
/website/
├── inc/
│   ├── sponsors.json          # Sponsor configuration
│   ├── sponsors.inc           # Sponsor display functions
│   ├── header.inc            # Custom Pintwood header
│   ├── footer.inc            # Footer with sponsor display
│   └── theme-selector.inc    # Theme application logic
├── css/
│   └── pintwood-theme.css    # All custom styling
├── sponsors.kiosk.php        # Rotating sponsor display
└── [modified DerbyNet files]

/var/lib/derbynet/ (or /Users/todd/derbynet-data/lib/)
├── sponsors/
│   ├── keg/                  # Title sponsor logos
│   ├── growler/              # Growler tier logos
│   ├── liter/                # Liter tier logos
│   └── pint/                 # Pint tier logos
├── pintwood-logo.png         # Event logo
├── sponsors.json             # Sponsor configuration (backup)
└── pintwood-config.json      # Event configuration
```

## Installation Instructions

### 1. Copy Files to DerbyNet Installation

```bash
# Copy include files
cp *.inc /website/inc/

# Copy CSS
cp pintwood-theme.css /website/css/

# Copy kiosk page
cp sponsors.kiosk.php /website/

# Copy configuration files to data directory
cp sponsors.json /var/lib/derbynet/
cp pintwood-config.json /var/lib/derbynet/
```

### 2. Create Sponsor Logo Directories

```bash
mkdir -p /var/lib/derbynet/sponsors/keg
mkdir -p /var/lib/derbynet/sponsors/growler
mkdir -p /var/lib/derbynet/sponsors/liter
mkdir -p /var/lib/derbynet/sponsors/pint
```

### 3. Upload Logo Files
- Place the Pintwood Derby logo as `/var/lib/derbynet/pintwood-logo.png`
- Place sponsor logos in their respective tier directories

### 4. Modify Existing DerbyNet Pages

Each public-facing page needs three modifications:

#### At the top of the file (after opening <?php):
```php
require_once('inc/theme-selector.inc');
session_start();
```

#### In the <head> section:
```php
<?php pintwood_head_includes(); ?>
```

#### After <body> tag:
```php
<?php
require_once('inc/header.inc');
require_once('inc/footer.inc');

// Replace 'Page Title' with appropriate title
replace_default_banner('Page Title', true, 'index.php');
?>
```

#### Before closing </body>:
```php
<?php
if (should_use_pintwood_theme()) {
    add_pintwood_footer();
}
?>
```

### 5. Pages to Modify

Required modifications for these files:
- `index.php` - Main landing page
- `login.php` - Login page
- `racer-results.php` - Race results display
- `slideshow.php` - Results slideshow
- Kiosk pages in the kiosk directory

## Configuration

### Adding/Updating Sponsors

Edit `/var/lib/derbynet/sponsors.json`:

```json
{
  "sponsors": {
    "keg": [
      {
        "name": "Company Name",
        "logo": "keg/company-logo.png",
        "url": "https://company.com"
      }
    ],
    "growler": [
      {
        "name": "Another Company",
        "logo": "growler/another-logo.png",
        "url": ""
      }
    ]
    // ... more sponsors
  }
}
```

### Customizing Theme Colors

Edit `/website/css/pintwood-theme.css`:

```css
:root {
    --pintwood-citrine: #D89A12;
    --pintwood-sapphire: #1B76BC;
    --pintwood-garnet: #9a0101;
    --pintwood-dark-bg: #231F20;
    --pintwood-darker-bg: #1e1e1e;
}
```

### Controlling Which Pages Get Dark Theme

Edit `/website/inc/theme-selector.inc`:

```php
$public_pages = array(
    'index.php',
    'login.php',
    // Add more pages here
);
```

## Features

### 1. Sponsor Management
- Four tier system: Keg (Title), Growler, Liter, Pint
- Automatic logo sizing by tier
- Optional URL linking for each sponsor
- JSON-based configuration for easy updates

### 2. Custom Header
- Pintwood Derby branding
- Event logo and wordmark
- Title sponsor display
- Optional back button
- Centered page titles

### 3. Sponsor Footer
- Fixed position at bottom of page
- Single-line display of non-title sponsors
- Mobile responsive stacking
- Hover effects on logos

### 4. Sponsor Kiosk
- Full-screen rotating display
- Shows all sponsors with tier labels
- Configurable rotation interval
- ESC key to exit kiosk mode
- Auto-refresh every 30 minutes

### 5. Dark Theme
- Based on indypintwoodderby.com aesthetic
- Citrine/Sapphire/Garnet color scheme
- Montserrat headers, Roboto body text
- Enhanced readability in low light
- Professional appearance

### 6. Mobile Responsive
- Header adapts to small screens
- Footer stacks sponsors on mobile
- Touch-friendly button sizes
- Optimized font sizes

## Troubleshooting

### Sponsors Not Displaying
1. Check that `sponsors.json` exists in `/var/lib/derbynet/`
2. Verify logo files are in correct directories
3. Check file permissions (web server must be able to read files)

### Theme Not Applied
1. Verify `pintwood-theme.css` is in `/website/css/`
2. Check that `theme-selector.inc` is included at top of page
3. Ensure `pintwood_head_includes()` is called in `<head>`

### Header/Footer Not Showing
1. Confirm include files are in `/website/inc/`
2. Check that `require_once` statements are present
3. Verify PHP error reporting for include errors

### Logo Path Issues
If logos aren't loading, check:
1. Path in `sponsors.json` matches actual file location
2. Web server has read permissions
3. Use absolute paths if relative paths fail

## Testing Checklist

- [ ] All public pages show dark theme
- [ ] Header displays on all designated pages
- [ ] Title sponsor appears in header
- [ ] Footer sponsors display correctly
- [ ] Sponsor kiosk rotates through all sponsors
- [ ] Mobile responsive layout works
- [ ] Non-logged-in users see limited buttons
- [ ] Admin pages retain default theme
- [ ] All links and navigation work

## Support Files

### Example Nginx Configuration
```nginx
location /derbynet-data/ {
    alias /var/lib/derbynet/;
    expires 1h;
}
```

### Example Apache Configuration
```apache
Alias /derbynet-data /var/lib/derbynet
<Directory /var/lib/derbynet>
    Require all granted
</Directory>
```

## Docker Considerations

When running in Docker:
1. Mount sponsor directory as volume
2. Ensure persistent storage for configuration
3. Map paths correctly in docker-compose

Example docker-compose snippet:
```yaml
volumes:
  - ./derbynet-data/lib:/var/lib/derbynet
  - ./website:/var/www/html
```

## Future Enhancements

Potential improvements for future events:
- Admin interface for sponsor management
- Animated sponsor transitions in kiosk
- Sponsor analytics/impression tracking
- Dynamic sponsor package information display
- Integration with registration for sponsor tickets

## Contact

For questions about these customizations:
- Review documentation at derbynet.org
- Check indypintwoodderby.com for event details
- Customization by Todd (euphtodd)

## License

These customizations are provided for use with DerbyNet software.
Original DerbyNet software copyright Jeff Piazza.
Customizations for Pintwood Derby 2026.
