#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

#include <iostream>

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
    Player* p;

   public:
    Board();
    ~Board();

    Board& Reset();
    Board& Print();
    Board& SetPlayers();
};

Board::Board() {
    matrix = new char*[ROWS];
    for (short int i = 0; i < ROWS; ++i) {
        matrix[i] = new char[COLS];
    }
    Reset();
}

Board::~Board() {
    for (short int i = 0; i < ROWS; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

Board& Board::Reset() {
    char c = '0';
    for (short int i = 0; i < ROWS; ++i) {
        for (short int j = 0; j < COLS; ++j) {
            matrix[i][j] = ++c;
        }
    }
    nbr_moves = 0;
    p1.symbol = ' ';
    p2.symbol = ' ';
    p = nullptr;

    return *this;
}

Board& Board::Print() {
    for (short int i = 0; i < ROWS; ++i) {
        std::cout << "     |     |     " << std::endl;
        for (short int j = 0; j < COLS; ++j) {
            std::cout << "  " << matrix[i][j] << "  ";
            if (j < COLS - 1) {
                std::cout << "|";
            }
        }
        if (i < ROWS - 1) {
            std::cout << "\n_____|_____|_____" << std::endl;
        }
    }
    std::cout << "\n     |     |     " << std::endl;

    return *this;
}

Board& Board::SetPlayers() {
    srand(time(0));
    short int who_first = rand() % 2 + 1;
    if (who_first == 1) {
        p1.symbol = 'X';
        p2.symbol = 'O';
        p = &p1;
    } else {
        p1.symbol = 'O';
        p2.symbol = 'X';
        p = &p2;
    }
    std::cout << "Player" << who_first << " (X) plays first" << std::endl;

    return *this;
}

#endif