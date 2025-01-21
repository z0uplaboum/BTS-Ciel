#include <iostream>
#include <thread>

const int HAUTEUR = 30;
const int LARGEUR = 30;
int TAUX_APPARITION = 40;
const int TAUX_FEU = 15;

int foret[HAUTEUR][LARGEUR], copieforet[HAUTEUR][LARGEUR];

using namespace std;

int main() {
	srand(time(NULL));
	system("clear");
	for (int i = 0; i < HAUTEUR; ++i)
	{
		for (int j = 0; j < LARGEUR; j++)
		{
			if(rand()%5 == 0){
				foret[i][j] = (rand()%2)+1;
			}
		}
	}
	while(1){
		if (rand()%TAUX_FEU == 0){ foret[rand()%HAUTEUR][rand()%LARGEUR] = -1;}

		for (int i = 0; i < HAUTEUR; ++i){

			for (int j = 0; j < LARGEUR; j++){

				copieforet[i][j] = foret[i][j];
			}
		}

		for(int i=0; i <HAUTEUR; i++) {
			for(int j=0; j<LARGEUR; j++){
				if (copieforet[i][j] == -3){
					foret[i][j] = 0;
				} 
				else if ( copieforet[i][j] != 0 && copieforet[i][j]<=2 && copieforet[i][j]>=-2){
					foret[i][j]+= 1;
				} else {
					bool check = false;
					for(int n=0; n<3;n++){
						for(int l=0; l<3;l++){
							int x = (i-1)+n;
							int y = (j-1)+l;

							if (x<0 || x >= HAUTEUR ||y<0 || y >= LARGEUR){
								continue;
							}
							if(copieforet[x][y]==3){
								if (x!=i && y!=j){
									check = true;
								}
							}
						}
					}

					if(check){
						if (rand()%TAUX_APPARITION == 0){
							foret[i][j] = 1;
						}
					}
				}
			}
		}

		for (int i = 0; i < HAUTEUR; ++i){

			for (int j = 0; j < LARGEUR; j++){

				if (copieforet[i][j] < 0){
					if (i<=0 || i >= HAUTEUR ||j<0 || j >= LARGEUR){
						continue;
					}
					if (copieforet[i-1][j] > 0){
						foret[i-1][j] = -1;
					}
					if (copieforet[i+1][j] > 0) {
						foret[i+1][j] = -1;
					}
					if (copieforet[i][j-1] > 0) {
						foret[i][j-1] = -1;
					}
					if (copieforet[i][j+1] > 0) {
						foret[i][j+1] = -1;
					}
				}
			}
		}

		cout << "\033[H";
		int count = 0;
		for(int i=0; i <HAUTEUR; i++){
			for(int j=0; j<LARGEUR; j++) {
				switch(foret[i][j]){
				case 0:
					cout<<" ";
					break;

				case 1:
					cout<<".";
					break;

				case 2:
					cout<<"|";
					break;

				case 3:
					cout<<"T";
					count++;
					break;

				case -1:
					cout<<"#";
					break;

				default:
					cout<<"~";
					break;
				}
				cout<<" ";
			}
			cout <<endl;
		}
		cout << "Nombres d'arbres : "<<count<<endl;
		this_thread::sleep_for(chrono::milliseconds(100));

	}
}