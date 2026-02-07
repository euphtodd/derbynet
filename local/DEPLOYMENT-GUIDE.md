# Pintwood Derby 2026 - Deployment Guide

## Overview
This guide walks you through deploying your customized DerbyNet system to DigitalOcean for the February 21, 2026 race at Liter House, Indianapolis.

**Estimated Time**: 1-2 hours for initial setup
**Cost**: $0 (using DigitalOcean free credit) or ~$6 total
**Domain**: derby.indypintwoodderby.com

---

## Table of Contents
1. [Prerequisites](#prerequisites)
2. [Step 1: SSH Key Setup](#step-1-ssh-key-setup)
3. [Step 2: DigitalOcean Account Setup](#step-2-digitalocean-account-setup)
4. [Step 3: Create Droplet](#step-3-create-droplet)
5. [Step 4: Server Configuration](#step-4-server-configuration)
6. [Step 5: Deploy DerbyNet](#step-5-deploy-derbynet)
7. [Step 6: Domain & SSL Setup](#step-6-domain--ssl-setup)
8. [Step 7: Testing](#step-7-testing)
9. [Step 8: Race Day Procedures](#step-8-race-day-procedures)
10. [Step 9: Post-Race Cleanup](#step-9-post-race-cleanup)
11. [Troubleshooting](#troubleshooting)

---

## Prerequisites

Before starting, make sure you have:
- [ ] Your Mac with the customized DerbyNet files
- [ ] Access to manage DNS for indypintwoodderby.com
- [ ] A credit card for DigitalOcean signup (won't be charged with promo code)
- [ ] About 1-2 hours of uninterrupted time

---

## Step 1: SSH Key Setup

SSH keys allow you to securely connect to your server without passwords.

### 1.1 Check if you already have SSH keys

```bash
ls -la ~/.ssh/
```

If you see files named `id_rsa` and `id_rsa.pub` (or `id_ed25519` and `id_ed25519.pub`), you already have keys! Skip to step 1.3.

### 1.2 Generate new SSH keys (if needed)

```bash
ssh-keygen -t ed25519 -C "todd@pintwood-derby"
```

When prompted:
- Press Enter to accept default location (`~/.ssh/id_ed25519`)
- Press Enter twice for no passphrase (or add one for extra security)

### 1.3 Copy your public key

```bash
cat ~/.ssh/id_ed25519.pub
```

Copy the entire output (starts with `ssh-ed25519`). You'll need this for DigitalOcean.

**Alternative**: If you used the older RSA format:
```bash
cat ~/.ssh/id_rsa.pub
```

---

## Step 2: DigitalOcean Account Setup

### 2.1 Sign Up

1. Go to https://www.digitalocean.com
2. Click "Sign Up"
3. Use your email and create a password
4. Verify your email address

### 2.2 Get Free Credit

1. Look for promotional offers (new accounts often get $200/60 days free)
2. Alternative: Search for "DigitalOcean promo code 2026" for current offers
3. Add your credit card (required but won't be charged if using credits)

### 2.3 Add SSH Key to Account

1. Click your profile icon → Settings
2. Click "Security" in left sidebar
3. Click "Add SSH Key"
4. Paste your public key from Step 1.3
5. Name it: "Mac - Pintwood Derby"
6. Click "Add SSH Key"

---

## Step 3: Create Droplet

A "droplet" is DigitalOcean's term for a virtual server.

### 3.1 Create the Droplet

1. Click "Create" → "Droplets"
2. **Choose an image**: Ubuntu 24.04 LTS x64
3. **Choose a plan**:
   - Select "Basic"
   - CPU: Regular
   - Choose $6/month option (1GB RAM / 1 CPU / 25GB SSD)
4. **Choose a datacenter**:
   - Select a region close to Indianapolis (e.g., "New York 3" or "Chicago")
5. **Authentication**:
   - Select "SSH keys"
   - Check your "Mac - Pintwood Derby" key
6. **Hostname**: `pintwood-derby-2026`
7. **Tags**: Add tag "pinewood-derby" for organization
8. Click "Create Droplet"

Wait 30-60 seconds for it to spin up.

### 3.2 Note Your Droplet IP

Once created, you'll see your droplet's IP address (e.g., `159.65.123.45`).

**Save this IP address** - you'll need it multiple times!

---

## Step 4: Server Configuration

Now we'll connect to your server and install Docker.

### 4.1 Connect to Your Server

```bash
ssh root@YOUR_DROPLET_IP
```

Replace `YOUR_DROPLET_IP` with your actual IP address.

If prompted "Are you sure you want to continue connecting?", type `yes` and press Enter.

You should now see a prompt like: `root@pintwood-derby-2026:~#`

### 4.2 Update System Packages

```bash
apt update && apt upgrade -y
```

This takes 2-3 minutes.

### 4.3 Install Docker

```bash
# Install Docker
curl -fsSL https://get.docker.com -o get-docker.sh
sh get-docker.sh

# Start Docker
systemctl start docker
systemctl enable docker

# Verify installation
docker --version
```

You should see something like: `Docker version 24.0.x`

### 4.4 Install Docker Compose

```bash
apt install docker-compose -y

# Verify
docker-compose --version
```

### 4.5 Configure Firewall

```bash
# Allow SSH, HTTP, and HTTPS
ufw allow 22/tcp
ufw allow 80/tcp
ufw allow 443/tcp

# Enable firewall
ufw --force enable

# Check status
ufw status
```

### 4.6 Create Directory Structure

```bash
# Create directories
mkdir -p /opt/derbynet/website
mkdir -p /opt/derbynet/data/lib

# Create sponsors directories
mkdir -p /opt/derbynet/data/lib/sponsors/{keg,growler,liter,pint}
```

You can now disconnect from the server (type `exit` or just continue).

---

## Step 5: Deploy DerbyNet

Now we'll copy your customized files to the server.

### 5.1 Create Deployment Archive Locally

On your Mac, run:

```bash
cd /Users/todd/derbynet

# Create archive of website files
tar czf derbynet-website.tar.gz website/

# Create archive of data files
cd /Users/todd/derbynet-data
tar czf derbynet-data.tar.gz lib/
```

### 5.2 Copy Files to Server

```bash
# Copy website files
scp /Users/todd/derbynet/derbynet-website.tar.gz root@YOUR_DROPLET_IP:/opt/derbynet/

# Copy data files
scp /Users/todd/derbynet-data/derbynet-data.tar.gz root@YOUR_DROPLET_IP:/opt/derbynet/
```

Replace `YOUR_DROPLET_IP` with your actual IP address.

### 5.3 Extract Files on Server

SSH back into your server:

```bash
ssh root@YOUR_DROPLET_IP
```

Then extract the files:

```bash
cd /opt/derbynet

# Extract website
tar xzf derbynet-website.tar.gz
rm derbynet-website.tar.gz

# Extract data
tar xzf derbynet-data.tar.gz
rm derbynet-data.tar.gz

# Verify structure
ls -la website/
ls -la data/lib/
```

### 5.4 Create Docker Compose File

```bash
cat > /opt/derbynet/docker-compose.yml << 'EOF'
version: '3.8'

services:
  derbynet:
    image: jeffpiazza/derbynet_server:latest
    container_name: derbynet
    ports:
      - "80:80"
      - "443:443"
    volumes:
      - ./website:/var/www/html
      - ./data/lib:/var/lib/derbynet
    environment:
      - TZ=America/Indiana/Indianapolis
    restart: unless-stopped
EOF
```

### 5.5 Start DerbyNet

```bash
cd /opt/derbynet
docker-compose up -d

# Check if it's running
docker ps

# Check logs if needed
docker logs derbynet
```

### 5.6 Test Basic Access

From your Mac, open a browser and go to:
```
http://YOUR_DROPLET_IP
```

You should see the DerbyNet interface with Pintwood Derby theme!

---

## Step 6: Domain & SSL Setup

Now let's set up your custom domain with HTTPS.

### 6.1 Configure DNS

1. Go to your domain registrar or Google Firebase Console
2. Navigate to DNS settings for `indypintwoodderby.com`
3. Add a new **A record**:
   - **Name/Host**: `derby`
   - **Type**: `A`
   - **Value**: `YOUR_DROPLET_IP`
   - **TTL**: `300` (5 minutes)
4. Save the record

DNS propagation can take 5-60 minutes. Test with:

```bash
# On your Mac
nslookup derby.indypintwoodderby.com
```

You should see your droplet IP in the response.

### 6.2 Install Certbot for SSL

SSH back into your server and run:

```bash
# Stop DerbyNet temporarily
cd /opt/derbynet
docker-compose down

# Install Certbot
apt install certbot -y

# Get SSL certificate
certbot certonly --standalone -d derby.indypintwoodderby.com --email YOUR_EMAIL --agree-tos --non-interactive
```

Replace `YOUR_EMAIL` with your actual email address.

### 6.3 Configure Nginx Reverse Proxy

```bash
# Install Nginx
apt install nginx -y

# Create Nginx config
cat > /etc/nginx/sites-available/derbynet << 'EOF'
server {
    listen 80;
    server_name derby.indypintwoodderby.com;
    return 301 https://$server_name$request_uri;
}

server {
    listen 443 ssl http2;
    server_name derby.indypintwoodderby.com;

    ssl_certificate /etc/letsencrypt/live/derby.indypintwoodderby.com/fullchain.pem;
    ssl_certificate_key /etc/letsencrypt/live/derby.indypintwoodderby.com/privkey.pem;

    ssl_protocols TLSv1.2 TLSv1.3;
    ssl_ciphers HIGH:!aNULL:!MD5;

    client_max_body_size 50M;

    location / {
        proxy_pass http://localhost:8080;
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        proxy_set_header X-Forwarded-Proto $scheme;
    }
}
EOF

# Enable the site
ln -sf /etc/nginx/sites-available/derbynet /etc/nginx/sites-enabled/

# Remove default site
rm -f /etc/nginx/sites-enabled/default

# Test config
nginx -t

# Restart Nginx
systemctl restart nginx
```

### 6.4 Update Docker Compose for Port 8080

```bash
cd /opt/derbynet

# Edit docker-compose.yml
cat > docker-compose.yml << 'EOF'
version: '3.8'

services:
  derbynet:
    image: jeffpiazza/derbynet_server:latest
    container_name: derbynet
    ports:
      - "8080:80"
    volumes:
      - ./website:/var/www/html
      - ./data/lib:/var/lib/derbynet
    environment:
      - TZ=America/Indiana/Indianapolis
    restart: unless-stopped
EOF

# Restart DerbyNet
docker-compose up -d
```

### 6.5 Test HTTPS Access

Open your browser and go to:
```
https://derby.indypintwoodderby.com
```

You should see:
- ✅ Secure padlock icon
- ✅ Pintwood Derby theme
- ✅ Sponsor logos displaying

---

## Step 7: Testing

### 7.1 Test Checklist

On your Mac, test these URLs:

- [ ] `https://derby.indypintwoodderby.com` - Main page
- [ ] `https://derby.indypintwoodderby.com/login.php` - Login page
- [ ] `https://derby.indypintwoodderby.com/racer-results.php` - Results page
- [ ] `https://derby.indypintwoodderby.com/slideshow.php` - Slideshow
- [ ] `https://derby.indypintwoodderby.com/sponsors.kiosk.php` - Sponsor kiosk

### 7.2 Admin Access Test

1. Go to `https://derby.indypintwoodderby.com`
2. Log in with coordinator credentials
3. Navigate to admin pages
4. Verify you can:
   - Add racers
   - Create rounds
   - Enter results
   - View reports

### 7.3 Mobile Test

Test on your phone:
- [ ] Visit the URL via browser
- [ ] Check responsive layout
- [ ] Verify sponsor logos display
- [ ] Test QR code scanning (generate one pointing to the site)

### 7.4 Load Test (Optional)

Open the site on multiple devices simultaneously to ensure it can handle the load.

---

## Step 8: Race Day Procedures

### 8.1 Pre-Race Checklist (Week Before)

- [ ] Verify deployment is working
- [ ] Test with sample race data
- [ ] Generate QR codes for venue display
- [ ] Print QR codes and post at venue
- [ ] Test timer hardware connection (if applicable)
- [ ] Backup current database (if you have test data to preserve)

### 8.2 Race Day Morning

1. **Verify Site is Up**
   ```bash
   curl -I https://derby.indypintwoodderby.com
   ```

2. **Check Server Status**
   ```bash
   ssh root@YOUR_DROPLET_IP
   docker ps
   docker logs derbynet --tail 50
   ```

3. **Fresh Database** (if starting clean)
   ```bash
   # On server
   cd /opt/derbynet/data/lib/2025/Development/
   rm derbynet.sqlite3
   # DerbyNet will create a new one on first access
   ```

### 8.3 During Race

**Monitor via:**
- Browser: `https://derby.indypintwoodderby.com`
- Server logs: `ssh root@YOUR_DROPLET_IP && docker logs -f derbynet`

**Backup Plan (if internet fails at venue):**
1. Enable mobile hotspot on your phone
2. Connect your laptop to hotspot
3. Continue accessing `https://derby.indypintwoodderby.com`
4. Notify attendees of connectivity issue

### 8.4 Backup Strategy (Local Fallback)

If cloud completely fails:

1. On your Mac, run:
   ```bash
   cd /Users/todd/derbynet
   docker-compose up -d
   ```

2. Find your Mac's local IP:
   ```bash
   ipconfig getifaddr en0
   ```

3. Have attendees connect to: `http://YOUR_MAC_IP`

---

## Step 9: Post-Race Cleanup

### 9.1 Download Race Data

```bash
# From your Mac
scp -r root@YOUR_DROPLET_IP:/opt/derbynet/data/lib/ ~/Desktop/pintwood-derby-2026-data/
```

This saves:
- Database with all results
- Racer photos (if any)
- Configuration files

### 9.2 Generate Final Reports

1. Log into `https://derby.indypintwoodderby.com`
2. Go to admin section
3. Export/print:
   - Final standings
   - Award recipients
   - Race statistics
   - Any other reports needed

### 9.3 Destroy Droplet (Stop Paying)

Once data is safely backed up:

1. Log into DigitalOcean
2. Go to your droplet
3. Click "More" → "Destroy"
4. Confirm destruction
5. Type the droplet name to confirm
6. Click "Destroy"

**Important**: Only do this AFTER you've downloaded all data!

### 9.4 Remove DNS Record (Optional)

If you want to clean up:
1. Go to DNS settings
2. Delete the `derby` A record
3. Or leave it - won't cost anything

---

## Troubleshooting

### Issue: Can't SSH into server

**Symptom**: `Connection refused` or `Permission denied`

**Solutions**:
```bash
# Check if you're using the right IP
ping YOUR_DROPLET_IP

# Check if SSH key is loaded
ssh-add -l

# Try with verbose output to see what's wrong
ssh -v root@YOUR_DROPLET_IP

# If all else fails, use DigitalOcean web console
# (Available in droplet dashboard)
```

### Issue: Docker container won't start

**Check logs**:
```bash
docker logs derbynet
docker-compose logs
```

**Restart container**:
```bash
cd /opt/derbynet
docker-compose restart
```

**Full reset**:
```bash
docker-compose down
docker-compose up -d
```

### Issue: Site loads but no theme/sponsors

**Check file permissions**:
```bash
ls -la /opt/derbynet/website/
ls -la /opt/derbynet/data/lib/sponsors/
```

**Check sponsor image URL**:
```bash
curl -I https://derby.indypintwoodderby.com/sponsor-image.php?path=keg/half-liter.png
```

Should return `200 OK`

### Issue: SSL certificate fails

**Troubleshooting**:
```bash
# Check DNS is resolving
nslookup derby.indypintwoodderby.com

# Try manual renewal
certbot renew --dry-run

# Check Nginx config
nginx -t

# View detailed error
tail -f /var/log/nginx/error.log
```

### Issue: Can't log into admin

**Reset password**:
```bash
# On server
docker exec -it derbynet bash
cd /var/www/html
# Follow DerbyNet password reset procedure
```

Or check `/Users/todd/derbynet/testing/default.passwords` for default credentials.

### Issue: Sponsor logos not displaying

**Check image paths**:
```bash
# On server
ls -la /opt/derbynet/data/lib/sponsors/keg/
cat /opt/derbynet/data/lib/sponsors.json
```

**Test image serving**:
```bash
curl -I https://derby.indypintwoodderby.com/sponsor-image.php?path=keg/half-liter.png
```

### Issue: Out of disk space

**Check disk usage**:
```bash
df -h
docker system df
```

**Clean up if needed**:
```bash
docker system prune -a
apt autoremove
```

### Getting Help

- DerbyNet documentation: https://derbynet.org
- DigitalOcean docs: https://docs.digitalocean.com
- This GitHub: https://github.com/jeffpiazza/derbynet

---

## Quick Reference Commands

### SSH into server
```bash
ssh root@YOUR_DROPLET_IP
```

### Check DerbyNet status
```bash
docker ps
docker logs derbynet
```

### Restart DerbyNet
```bash
cd /opt/derbynet
docker-compose restart
```

### Update DerbyNet files
```bash
# On Mac
scp /path/to/changed/file root@YOUR_DROPLET_IP:/opt/derbynet/website/path/

# On server
docker-compose restart
```

### Backup database
```bash
scp root@YOUR_DROPLET_IP:/opt/derbynet/data/lib/2025/Development/derbynet.sqlite3 ~/Desktop/
```

### View live logs
```bash
ssh root@YOUR_DROPLET_IP
docker logs -f derbynet
```

---

## Race Day QR Codes

Generate QR codes for these URLs:

1. **Main Site**: `https://derby.indypintwoodderby.com`
   - For spectators to view results

2. **Kiosk View**: `https://derby.indypintwoodderby.com/kiosk.php`
   - For display screens

3. **Sponsor Rotation**: `https://derby.indypintwoodderby.com/sponsors.kiosk.php`
   - For sponsor showcase screens

Generate at: https://qr-code-generator.com or use any QR code tool.

---

## Contact & Support

For issues during deployment or on race day, refer to:
- This guide
- DerbyNet official documentation
- DigitalOcean support (if server issues)

Good luck with the Pintwood Derby 2026! 🏁
