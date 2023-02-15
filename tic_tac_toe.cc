#include "tic_tac_toe.h"

#include <iostream>

int main() {
    Board board = Board();
    int option = 0;

    do {
        board.Reset();
        std::cout << "Tic Tac Toe" << std::endl;
        board.SetPlayers();
        for (int i = 0; i < 9; ++i) {
            system("cls");
            board.Print();
            board.Play();
            if (board.isWin()) {
                board.AnnounceWin();
                break;
            }
            board.SwitchPlayer();
        }

        board.PrintScore();
        std::cout << "Press \"0\" to restart:\n> ";
        std::cin >> option;
    } while (!option);

    return 0;
}