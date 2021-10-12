# radioTelescope
radioTelescopeProject

#Imaging the Milky Way in Neutral Hydrogen with an RTL-SDR
https://www.rtl-sdr.com/imaging-the-milky-way-in-neutral-hydrogen-with-an-rtl-sdr/

# Network

## Interface
### Current Status

### how to up/down interface
ip link set br0 up
ip link set br0 down

### Restart network interface

Debian / Ubuntu Linux restart network interface
To restart network interface, enter:
sudo /etc/init.d/networking restart

To stop and start use the following option (do not run them over remote ssh session as you will get disconnected):
sudo /etc/init.d/networking stop
sudo /etc/init.d/networking start

Debian/Ubuntu Linux with systemd, run:
$ sudo systemctl restart networking

## bridge
brctl show

brctl showmacs br0

## Enabling forwarding
echo "1" > /proc/sys/net/ipv4/ip_forward

## Enabling DynamicAddr
echo "1" > /proc/sys/net/ipv4/ip_dynaddr

## Iptables configuration.
https://iximiuz.com/en/posts/laymans-iptables-101/

### Add a NAT forwarding rule to iptables:

sudo iptables -t nat -A POSTROUTING -o ens160 -j MASQUERADE

:OUTPUT ACCEPT [0:0]
-A FORWARD -i "$EXTIF" -o "$INTIF" -m conntrack --ctstate ESTABLISHED,RELATED -j ACCEPT 
-A FORWARD -i "$INTIF" -o "$EXTIF" -j ACCEPT
-A FORWARD -j LOG

## TCPdump
### get ping
sudo tcpdump -n icmp -i xxx

## DNS
https://opensource.com/article/17/4/build-your-own-name-server

### get DNS list
dig corp.microsoft.com

# MCU 8051

# Docker
## install Docker
https://docs.docker.com/engine/install/ubuntu/
https://docs.docker.com/engine/install/linux-postinstall/
## docker with c++
https://medium.com/@mfcollins3/shipping-c-programs-in-docker-1d79568f6f52
## build
docker build -t testedge .
## run
docker run --name edge testedge
## delete
docker rm --force edge
# K8S
https://microk8s.io/

# Clang
sudo apt-get install clang
sudo update-alternatives --config c++




