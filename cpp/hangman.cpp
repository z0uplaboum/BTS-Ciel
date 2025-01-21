#include <iostream>

void jeux();

int main() {
    jeux();

    return 0;
}

void jeux() {
    std::string solution, reponse;
    char rune;
    int count{0};

    std::cout<<"Entrer le mot a deviner : ";
    std::cin>>solution;

    reponse = solution;

    for(int i=1; i<reponse.length(); i++) {
        reponse[i] = '*';
    }

    while (1){
        bool found = 0;
        if(count==10) {
            std::cout<<"Dommage c'est perdu !"<<std::endl;
            break;
        }
        if(solution == reponse && count < 10) {
            std::cout<<"Bravo vous avez trouve "<<reponse<<" en "<<count<<" essais !"<<std::endl;
            break;
        }
        system("cls");
        std::cout<<"Mot a deviner : "<<reponse<<std::endl;
        std::cout<<"Entrer une lettre : ";
        std::cin>>rune;

        for (int i=0; i< reponse.length(); i++) {
            if(rune==solution[i]) {
                reponse[i] = rune;
                found = 1;
            }
        }
        if(!found) {
            count++;
        }
    }
    

}