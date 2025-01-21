//La gestion des erreurs de cin conduit a une boucle infinie...

#include <iostream>
#include <vector>
//#include <bits/stdc++.h>

const std::vector<std::string>	MotEn5Lettres = {"table", "chaud", "glace", "pomme", "clair", "lourd", "vague", "vertu", "noire", "fleur"};
const std::vector<std::string>	MotEn6Lettres = {"maison"};
const std::vector<std::string>	MotEn7Lettres = {"voiture"};
const std::vector<std::string>	MotEn8Lettres = {"coiffeur"};

std::string motADeviner;

int menu();
std::string getMot(int i);
//bool checkList(std::string MotEntre, std::string NomListe);
void jeux(std::string& motADeviner, int& longeur);

int main() {
	int longeur = menu();
	motADeviner = getMot(longeur);
	jeux(motADeviner, longeur);

	return 0; 
}

int menu() {
	int menuEntree{0};

	start:
	std::cin.clear();
	system("clear");
	std::cout<<"Choisissez le nombres de lettres (5,6,7 ou 8): ";
	std::cin>> menuEntree;

	if (std::cin && menuEntree >=4 && menuEntree <=8) {
		return menuEntree;
	} else {
		goto start;
	}
}

std::string getMot(int i){
	srand(time(NULL));
	std::string mot;
	switch(i){
	case 5:
		mot = MotEn5Lettres[std::rand()%MotEn5Lettres.size()];
		break;
	case 6:
		mot = MotEn6Lettres[std::rand()%MotEn6Lettres.size()];
		break;
	case 7:
		mot = MotEn7Lettres[std::rand()%MotEn7Lettres.size()];
		break;
	case 8:
		mot = MotEn8Lettres[std::rand()%MotEn8Lettres.size()];
		break;
	default:
		break;
	}

	return mot;
}

void jeux(std::string& motADeviner, int& longeur){
	/*char copieMot[motADeviner.length() + 1];
	std::copy(motADeviner.begin(),motADeviner.end(), copieMot);*/
	std::string copieMot = motADeviner;

	std::cout << "Bienvenue dans le jeu Wordle !\n";
    printf("Devinez le mot de %i lettres en 6 tentatives.\n",longeur);

    int tentatives = 0;
    bool gagne = false;
	std::string entree="";

	while(1){
		if (gagne){
			std::cout << "\n\033[1;32mBravo ! Vous avez deviné le mot : " << motADeviner << "\033[0m\n";
			break;
		} else if (tentatives > 6){
			std::cout << "\n\033[1;31mDommage ! Le mot secret était : " << motADeviner << "\033[0m\n";
			break;
		}
		
		printf("Entrez un mot de %i lettres : ",longeur);
		std::cin>>entree;

		if (entree.size() != longeur) {
            printf("Le mot doit comporter exactement %i lettres. Essayez à nouveau.\n", longeur);
            continue;
        }
		std::cin.clear();
	    // Conversion en majuscules
        //std::transform(entree.begin(), entree.end(), entree.begin(), ::tolower);

		for (int i = 0; i < motADeviner.size(); i++){
			if (entree[i] == motADeviner[i]){
				copieMot[i] = '*';
			}
		}
		
	    for (int i = 0; i < motADeviner.size(); i++) {
        	if (entree[i] == motADeviner[i]) {
        	    // Lettre correcte et bien placée
        	    std::cout << "\033[1;32m" << char(toupper(entree[i]))<<" " << "\033[0m"; // Vert
				copieMot[i]='*';
        	} else if (copieMot.find(entree[i]) != std::string::npos) {
        	    // Lettre correcte mais mal placée
        	    std::cout << "\033[1;33m" << char(toupper(entree[i]))<<" " << "\033[0m"; // Jaune
        	} else {
        	    // Lettre incorrecte
        	    std::cout << "\033[1;31m" << char(toupper(entree[i]))<<" " << "\033[0m"; // Rouge
        	}
		}
		std::cout << std::endl;

		if (entree == motADeviner){
			gagne = true;
		} else {
			tentatives++;
		}
	}
	

}