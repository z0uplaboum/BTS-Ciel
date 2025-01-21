#include <iostream>

void PierrePapierCiseau();
void plusOuMoins();
char entreJoueurPPC();
void AfficherScore();


int SCORE_GLOBAL[2]{0,0};

int main() {
	int entree;
	bool quitter = false;
	do {
		system("clear");
		std::cout<<"1)  Affichage des scores\n2)  Plus ou Moins\n3)  Pierre\\papier\\ciseau\n4)Quitter\n\nChoix: ";
		std::cin>>entree;

		switch(entree){
			case 1:
				AfficherScore();
				break;
			case 2:
				break;
			case 3:
				PierrePapierCiseau();
				break;
			case 4:
				quitter = true;
				break;
			default:
				std::cin.clear();
				entree = 0;
		}
	}while(quitter != true);

	return 0;
}	

void PierrePapierCiseau(){
	int score[2]={0,0};
	char continuer ;

	std::cout<<"Voici les règles, chaque joueur va entrer une \nlettre"
			<<"P pour pierre\n"
			<<"F pour feuille\n"
			<<"C pour ciseau\n\n"
			<<"Le premier joueur a 3 points a gagné la partie"<<std::endl;
	
	while(1){
		char joueur1, joueur2;

		//Joueur 1 entree
		system("clear");
		joueur1 = entreJoueurPPC();

		//Joueur 2 entree
		system("clear");
		joueur2 = entreJoueurPPC();

		if (joueur1 == joueur2){
			std::cout<<"Égalité !";
			continue;
		} else {
			//suite du pierre feuille ciseau a implementer
		}

		//check gagnant
		for (int i=0; i < 2; i++){
			if (score[i] > 2){
				SCORE_GLOBAL[i]++;
				printf("Victoire du joueur %i !! Félicitations !\n", i);
				continue;
			}
		}

		std::cout<<"Voulez-vous continuer (O/N) ? : ";
		std::cin>>continuer;

		if (continuer =='n' || continuer == 'N'){
			return;
		}
	}

}


void plusOuMoins(){

}

char entreJoueurPPC(){
	char entree = 'X';
	do {
		std::cout<<"Entrez une lettre (P,F,C) :";
		std::cin>>entree;

		if (!std::cin.fail()){
			entree = (char)toupper(entree);
			if (entree == 'P' || entree == 'F' || entree=='C'){
				continue;
			} else {
				entree = 'X';
			}
		} else {
			std::cin.clear();
		}
	} while (entree == 'X');

	return entree;
}

void AfficherScore() {
	system("clear");

	char toto;

	std::cout<<"*************"<<std::endl;
	std::cout<<"	SCORE    "<<std::endl;
	std::cout<<"*************"<<std::endl;
	std::cout<<"Joueur 1: "<<SCORE_GLOBAL[0]<<std::endl;
	std::cout<<"Joueur 2: "<<SCORE_GLOBAL[1]<<std::endl;
	printf("\n Appuyez sur entrer pour quitter...");
	toto = getchar();
}