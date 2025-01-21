#include <iostream>

const int TAILLE_VERTICALE = 30;
const int TAILLE_HORIZONTALE = 100;

using namespace std;

int main() {
	srand(time(NULL));
	char grille[TAILLE_VERTICALE][TAILLE_HORIZONTALE];

	for (int i = 0; i < TAILLE_VERTICALE; ++i)
	{
		for (int j = 0; j < TAILLE_HORIZONTALE; ++j)
		{
			grille[i][j] = ' ';
		}
	}
	while(1){
		for (int i = TAILLE_VERTICALE - 1; i >= 0; i--)
		{
			for (int j = 0; j < TAILLE_HORIZONTALE; ++j)
			{
				if (grille[i][j] != ' '){
					grille[i+1][j] = grille[i][j];
				}
			}
		}
		for (int j = 0; j < TAILLE_HORIZONTALE; ++j)
		{
			if(grille[1][j] != ' '){
				grille[0][j] = rand() % (95-33) +33;
			} else {
				if(rand()%20 == 0) {
					grille[0][j] = rand() % (95-33) +33;
				}
			}
		}
		for (int i = 0; i < TAILLE_HORIZONTALE	; ++i)
		{
			if(grille[TAILLE_VERTICALE-1][i] != ' '){
				for (int j = 0; j < TAILLE_VERTICALE; j++)
				{
					grille[j][i] = ' ';
				}
			}
		}
		cout<<"\033[H\033[2J";
		for (int i = 0; i < TAILLE_VERTICALE; ++i)
		{
			for (int j = 0; j < TAILLE_HORIZONTALE; j++)
			{
				cout<<grille[i][j];
			}
			cout<<endl;
		}

		for (int i = 0; i < 50000000; ++i)
		{

		}
	}

	return 0;
}