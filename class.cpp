#include "class.h"


//player

player::player() {
    this->coutWin =0;
    cout<<endl<<"Choisir la maniere qui veut voulez ( X ou O ) :"<<endl;
    cin>>this->team;
    this->Maj();
    while (this->team != 'X' && this->team != 'x' && this->team != 'o' && this->team != 'O'){
        cout<<endl<<"Entrez incomprehensible"<<endl<<"S'il veut plait entrer (X ou O) :"<<endl;
        cin>>this->team;
        this->Maj();
    }
}

void player::Maj() {
    if (this ->team == 'o'){
        this->team ='O';
    }
    if (this->team =='x'){
        this->team ='X';
    }
}

player::player(char a) {
    assert (a == 'x' || a == 'X' || a == 'o' || a == 'O');
    this->coutWin=0;
    this->team= a;
    this->Maj();
}

player::player(const player &a) {
    this->coutWin=0;
    if(a.team == 'X'){
        this->team='O';
    } else this->team ='X';
}

player::~player() {

}


char player::GetTeam() {
    return this->team;
}







//GAME :

game::game(const player& a,const  player& b) {
    this->players=new player(a) ;
    (this->players)[0]=a;
    (this->players)[1]=b;     // KHAYF LA MAYB9ACH 3ANDI L'ACCES L HAD DONNES WALAKI FIN TANDIR this->player = new player [2] tay3ayat 3la constrecteur sans parametre wa tayzid dak procdeur ta3 this->team ma3ando ta ma3na
    //WinPossibiliter :
    for(int i=0;i<NbrPossibitite;i++){
        (this->WinPossibiliter)[i]= new int [2];
        ((this->WinPossibiliter)[i])[0]=1;
        ((this->WinPossibiliter)[i])[1]=3;
    }
    //resultat initialision
    this->resulat = 'e';
}

game::~game() {

}

void game::showBoard() {
    cout<<"----------------"<<endl;
    for(int i=0;i<3;i++){
        for(int j=0;j<2;j++){
            cout<<"  "<<(this->board)[i][j]<<"  "<<"|";
        }
        cout<<"  "<<(this->board)[i][2]<<endl;
        cout<<"----------------"<<endl;
    }
}

void game::play(int a) {
    assert(a==1 || a==0);
    int choix;
    int q,r;         //division eucludien
    do{
        cout<<"choisir une casse vide :"<<endl;
        cin>>choix;
        while( choix >9 || choix < 0 ){
            cout<<"please choose an integer between 1 AND 9  :"<<endl;
            cin>>choix;
        }
        q=choix/3;
        r= choix - 3*q;
        if(r==0){
            q-=1;
            r+=2;
        } else{
            r-=1;
        }
    } while (board[q][r] == 'X' || board[q][r] == 'O');
    board[q][r]= (players[a]).GetTeam();
    //ligne et colonne
    (this->WinPossibiliter[q])[1]-=1;
    (this->WinPossibiliter[r+3])[1]-=1;
    //daigonal et anti-daigonal
    if(r==1 && q%2!=0) { this->WinPossibiliter[6][1]-=1;this->WinPossibiliter[7][1]-=1;}
    if((q==0 && r==0) || (q==2 && r==2)) this->WinPossibiliter[6][1]-=1;
    if((q==0 && r==2) || (q==2 && r==0)) this->WinPossibiliter[7][1]-=1;

}

void game::CheckWin(){
    char test;
    int CouOfImpossibleCase = 0;
    for(int i=0;i<NbrPossibitite;i++){
        if((this->WinPossibiliter)[i][1]==0){
            //ligne
            if(i<3){
              test = (this->board)[i][0];
              int j=1;
              while((this->board)[i][j]==test && j<3){
                  j+=1;
              }
                if(j==3) {this->resulat= test;
                    break;}
                else{
                    (this->WinPossibiliter)[i][0]=0;
                    CouOfImpossibleCase+=1;
                }
                continue;           //bach bla maytester dakchi lakhar
            }
            //Colonne
            if(i<6 && i>2){
                test = (this->board)[0][i-3];
                int j=1;
                while((this->board)[j][i-3]==test && j<3){
                    j+=1;
                }
                if(j==3) {this->resulat= test;
                    break;}
                else{
                    (this->WinPossibiliter)[i][0]=0;
                    CouOfImpossibleCase+=1;
                }
                continue;
            }
            if(i== 6){
                test = (this->board)[0][0];
                int j=1;
                while((this->board)[j][j]==test && j<3){
                    j+=1;
                }
                if(j==3) {this->resulat= test;
                    break;}
                else{
                    (this->WinPossibiliter)[i][0]=0;
                    CouOfImpossibleCase+=1;
                }
                continue;
            }
            if(i== 7){
                test = (this->board)[0][2];
                int j=1,k=1;
                while((this->board)[k][j]==test && j<3){
                    j-=1;
                    k+=1;
                }
                if(j==-1) {this->resulat= test;
                    break;}
                else{
                    (this->WinPossibiliter)[i][0]=0;
                    CouOfImpossibleCase+=1;
                }
                continue;
            }

        }
    }
}



void game::fullpart() {
    int i=0;
    while (this->resulat != 'X' && this->resulat != 'O' && i<9){
        this->showBoard();
        this->play(i%2);
        this->CheckWin();
        i+=1;
    }
    if(this->resulat != 'X' && this->resulat != 'O'){
        this->resulat = 'D';
    }
    this->ShowScore();
    this->showBoard();
}


void game::winpossibilityShow() {
    cout<<"{";
    for(int i=0;i<NbrPossibitite;i++){
        cout<<"("<<(this->WinPossibiliter)[i][0]<<","<<(this->WinPossibiliter)[i][1]<<") ,";
    }
    cout<<"}"<<endl;
}


char game::GetResulatat() {
    return this->resulat;
}

void game::ShowScore() {
    if((players[0]).GetTeam() == this->resulat){
        cout<<"The Winner is : Player 1 "<<endl<<"  Who play with :"<<this->resulat<<endl<<"this is the bord in last move :"<<endl;
    } else  {
        if(this->resulat =='D') cout<<"this part ended with a Draw"<<endl<<"this is the bord in last move :"<<endl;
        else cout<<"The Winner is : Player 2 "<<endl<<"  Who play with :"<<this->resulat<<endl<<"this is the bord in last move :"<<endl;
    }
}


void OnevsOne(){
    cout<<endl<<"Player 1 :"<<endl;
    player p1;
    player p2(p1);
    cout<<"So the player 2 will play with :"<<p2.GetTeam()<<endl;
    game g(p1,p2);
    cout<<"Let's start !!!! "<<endl;
    g.fullpart();
};