#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

#define ROWS 3
#define COLS 3

typedef struct {
    char symbol;
} Player;

class Board {
   private:
    char** matrix;
    int nbr_moves;
    Player p1;
    Player p2;

   public:
    Board();
    ~Board();
};

Board::Board() {
    matrix = new char*[ROWS];
    for (short int i = 0; i < ROWS; ++i) {
        matrix[i] = new char[COLS];
    }
    nbr_moves = 0;
    p1.symbol = ' ';
    p2.symbol = ' ';
}

Board::~Board() {
    for (short int i = 0; i < ROWS; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

#endif