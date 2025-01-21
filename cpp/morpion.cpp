#include <iostream>

void jeux();
bool victoire(char verif_tab[3][3]);
void prevision(char tab_prevision[3][3], char joueur);
void tabl_copy(char entre[3][3], char sortie[3][3]);

int main() {
	jeux();

	return 0;
}

void jeux() {
	char grille[3][3];
	int count{0};
	char joueur;

	for(int i=0; i < 3; i++) {
		for (int j=0; j < 3; j++) {
			grille[i][j] = '*';
		}
	}

	while(1) {
		int x,y;
		system("clear");

		for(int i=0; i < 3; i++) {
			for (int j=0; j < 3; j++) {
				std::cout<<grille[i][j];
			}
			std::cout<<std::endl;
		}
		if (count >= 4) {
			prevision(grille, joueur);
		}	
		if (count == 9) {
			break;
		}

		if (victoire(grille)){
			std::cout<<"Victoire des "<<joueur<<std::endl;
			break;
		}
		std::cout<<"Entrez la ligne : ";
		std::cin>>x;

		std::cout<<"Entrez la colonne : ";
		std::cin>>y;

		if (grille[x][y]!= '*') {
			std::cout<<"Case deja prise !"<<std::endl;
			continue;
		} else {
			joueur = (count%2==0) ? 'x' : 'o';
			grille[x][y] = joueur;
			count++;
		}

	}
}

bool victoire(char verif_tab[3][3]) {
	bool check = false;
	for (int i=0; i<3; i++) {
		//comparaison entre toutes les lignes
		if (((verif_tab[i][0]==verif_tab[i][1])&&(verif_tab[i][1]==verif_tab[i][2]))&&(verif_tab[i][0] != '*')) {
			check = true;
		} else 	if (((verif_tab[0][i]==verif_tab[1][i])&&(verif_tab[1][i]==verif_tab[2][0]))&&(verif_tab[0][i] != '*')){
			check = true;
		}	
	}

	if ((((verif_tab[0][0]==verif_tab[1][1])&&(verif_tab[1][1]==verif_tab[2][2]))||((verif_tab[0][2]==verif_tab[1][1])&&(verif_tab[1][1]==verif_tab[2][0]))) &&(verif_tab[1][1] != '*')){
		check = true;
	}

	return check;
}

void prevision(char tab_prevision[3][3],char joueur) {
	char copy[3][3];
	for(int i=0; i < 3; i++) {
		for (int j=0; j < 3; j++) {
			tabl_copy(tab_prevision, copy);
			if (copy[i][j] == '*') {
			joueur = (joueur=='o') ? 'x' : 'o';
				copy[i][j] = joueur;
				if (victoire(copy)) {
					std::cout<<"Victoire potentiel en "<<i<<" "<<j<<std::endl;
					return;
				} else {
					copy[i][j] = '*';
				}
			}
		}
	}

}

void tabl_copy(char entre[3][3], char sortie[3][3]) {

	for(int i=0; i < 3; i++) {
		for (int j=0; j < 3; j++) {
			sortie[i][j] = entre[i][j];
		}
	}

}
