#!/bin/bash

##################################
#	 Petit script d'install		 #
#	  d'un serveur web sur 		 #
#	    Ubuntu avec LAMP 		 #
##################################


#Variables
NOM_DU_SITE="votre_domaine"
db_root_password="motdepasse"

#System update
sudo apt update

#Installation des logiciels nécessaires
echo "Installation de PHP, MySQL et Apache..."
sudo apt install mysql-server php libapache2-mod-php php-mysql -y


#Configuration MySQL
sudo mysql_secure_installation

#Création du répertoire du site web
sudo mkdir -p /var/www/$NOM_DU_SITE 
sudo chown -R  $USER:$USER /var/www/$NOM_DU_SITE


#Création du fichier de configuration
sudo cat<<EOF | sudo tee /etc/apache2/sites-available/$NOM_DU_SITE.conf
<VirtualHost *:80>
    ServerName $NOM_DU_SITE
    ServerAlias www.$NOM_DU_SITE
    ServerAdmin webmaster@localhost
    DocumentRoot /var/www/$NOM_DU_SITE

    ErrorLog ${APACHE_LOG_DIR}/error.log
    CustomLog ${APACHE_LOG_DIR}/access.log combined
</VirtualHost>
EOF

#Désactive le site par défaut et le remplace par le nouveau site
sudo a2dissite 000-default && sudo a2ensite $NOM_DU_SITE
sudo systemctl reload apache2

#Création du fichier test index.html
sudo cat<<EOF | sudo tee /var/www/$NOM_DU_SITE/index.html
<h1>Ca marche !!</h1>

<p>Ceci est un test depuis <strong>$NOM_DU_SITE</strong></p>
EOF

#Modification du fichier DirectoryIndex
sudo cat<<EOF | sudo tee /etc/apache2/mods-enabled/dir.conf
<IfModule mod_dir.c>
        DirectoryIndex index.php index.html index.cgi index.pl index.xhtml index.htm
</IfModule>
EOF

sudo systemctl reload apache2

#Fichier test php
cat<<EOF | tee /var/www/$NOM_DU_SITE/test.php
<?php
echo "Ceci est un test de php depuis $NOM_DU_SITE";
?>
EOF

