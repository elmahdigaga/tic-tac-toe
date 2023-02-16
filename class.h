#include <iostream>
#include <assert.h>
#define NbrPossibitite 8



using namespace std;


class player {
    void Maj();
protected:
    int coutWin ;
    char team;        //sera utiliser comme parametre dans les methode de class game
public:
    //constrecteur et destrecteur:
    player(char);
    player();
    player(const player&);
    ~player();
    char GetTeam();
};

class IA : public player{
    int* choice();    //return les coordoner que IA sera chioser
};

class game {
    static int coutpart ;
    char board[3][3]={{'1','2','3'},{'4','5','6'},{'7','8','9'}};
    int* WinPossibiliter[NbrPossibitite] ;  //WinPossibiliter[i]=(1 ou 0 , nbr de case vide ) et [0<= i <=2 : row et 3<= i <= 5 : colone et i==6 daigonal i=7 : daigonale inverse ] ou les donnes de cette variable initilizer dans methode  init_board(); et chnager dans play(char); et utiser dans  char CheckWin();        //je creer cette attribue pour reduire les testes dans checkwin() et aide IA de pendre la bonne décision  EXEMEPLE : WinPossibiliter[0] = (1,2) signfer qui un des deux joueur a la possibiliter de ganger a partir de row 1 et 0 la recéproque ( X O X )
    player* players;
    char resulat;
public:
    void winpossibilityShow();
    //constrecteur et destrecteur:
    game(const player&,const player&);              //darori constrecteur avec parametre 7it sans parametre ma3ando ta ma3na
    ~game();
    //methode :
    void init_board();
    void play(int);                  // hana anstakhalo table dynamique players
    void fullpart();                //the main ft of our programme
    void CheckWin();                // return team('X'ou'O') de joueur qui gagne et 'D' ou cas de resultat nulle
    char GetResulatat();
    void showBoard();
    void ShowScore();
    static int CanteurPart();

};

void OnevsOne();
