#!/bin/bash

##################################
#	 Petit script d'install		 #
#	  d'un serveur web sur 		 #
#	    Ubuntu avec LAMP 		 #
##################################


#Variables
NOM_DU_SITE="votre_domaine"
sql_user="user"
sql_pass="user"

#System update
sudo apt update

#Installation des logiciels nécessaires
echo "Installation de PHP, MySQL et Apache..."
sudo apt install mysql-server php libapache2-mod-php php-mysql curl -y


#Configuration MySQL
sudo mysql_secure_installation      #NYYYY

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

#Modification du fichier DirectoryIndex
sudo cat<<EOF | sudo tee /etc/apache2/mods-enabled/dir.conf
<IfModule mod_dir.c>
        DirectoryIndex index.php index.html index.cgi index.pl index.xhtml index.htm
</IfModule>
EOF

sudo systemctl reload apache2

#Creation de la base donnee sql
cat<<EOF | sudo tee /tmp/script.sql
CREATE DATABASE FilmDB;

USE FilmDB;

CREATE TABLE films (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nom_film VARCHAR(255) NOT NULL,
    acteurs VARCHAR(255)
);

EOF


sudo mysql -u root -p < /tmp/script.sql
sudo mysql -e " CREATE USER '$sql_user'@'localhost' IDENTIFIED BY '$sql_pass';"
#sudo mysql -e "GRANT ALL ON *.* TO '$sql_user'@'localhost' WITH GRANT OPTION;"
sudo rm /tmp/script.sql


#Scrapping web
TITRES=$(curl -s https://www.allocine.fr/film/aucinema/ | grep '<a class="meta-title-link' | awk -F'>' '{print $2}' | awk -F'<' '{print $1}')

while IFS= read -r film; do
    # Échapper les apostrophes pour éviter les erreurs SQL
    film_escaped=$(echo "$film" | sed "s/'/\\\'/g")

    # Insérer dans la base
    sudo mysql --user=$sql_user --password=$sql_pass "FilmDB" <<EOF
        INSERT INTO $TABLE (id, nom_film) VALUES (NULL, "$film_escaped");
EOF

    sudo mysql -u "$sql_user" --password="$sql_pass" "FilmDB" -e "INSERT INTO films (nom_film) VALUES ('$film_escaped');"
done <<< "$TITRES"

echo "Insertion terminée !"

#Fichier test php
cat<<EOF | tee /var/www/$NOM_DU_SITE/index.php
<?php
error_reporting(E_ALL);
ini_set('display_errors', 1);

\$servername = "localhost";
\$username = "user";
\$password = "user";
\$database = "FilmDB";

// Connexion à la base de données
\$conn = new mysqli(\$servername, \$username, \$password, \$database);

// Vérification de la connexion
if (\$conn->connect_error) {
    die("Échec de la connexion : " . \$conn->connect_error);
} else {
    echo "Connexion réussie !<br>";
}

// Requête SQL pour récupérer les films
\$sql = "SELECT nom_film FROM films"; // Assure-toi que la colonne "nom" existe
\$result = \$conn->query(\$sql);

if (!\$result) {
    die("Erreur SQL : " . \$conn->error);
}

?>
<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Liste des Films</title>
    <style>
        table {
            width: 50%;
            margin: 20px auto;
            border-collapse: collapse;
            text-align: left;
        }
        th, td {
            padding: 10px;
            border: 1px solid #ddd;
        }
        th {
            background-color: #4CAF50;
            color: white;
        }
        tr:nth-child(even) {
            background-color: #f2f2f2;
        }
    </style>
</head>
<body>
    <h2 style="text-align:center;">Liste des Films</h2>
    <table>
        <tr>
            <th>Nom du Film</th>
        </tr>
        <?php
        if (\$result->num_rows > 0) {
            while (\$row = \$result->fetch_assoc()) {
                echo "<tr><td>" . htmlspecialchars(\$row["nom_film"]) . "</td></tr>";
            }
        } else {
            echo "<tr><td colspan='1' style='text-align:center;'>Aucun film trouvé</td></tr>";
        }
        ?>
    </table>
</body>
</html>
<?php
// Fermeture de la connexion
\$conn->close();
?>



EOF

