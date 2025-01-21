#!/bin/bash

#Installer iptables
sudo apt install iptables iptables-persistent -y

#nano -w /etc/iptables/rules.v4

#Récuperer les interfaces réseau de la VM
$toto = ip -br l | awk '$1 !~ "lo|vir|wl" { print $1}'

sudo cat >/etc/iptables/rules.v4 <<EOL
*nat
-A POSTROUTING -o ${toto[0]} -j MASQUERADE
COMMIT

*filter
-A INPUT -i lo -j ACCEPT
-A INPUT -I ${toto[0]} -p tcp -m tcp --dport 22 -j ACCEPT
-A INPUT -m state --state RELATED,ESTABLISHED -j ACCEPT
-A INPUT -i ${toto[0]} -j DROP
COMMIT
EOL













