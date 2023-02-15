#include "tic_tac_toe.h"

#include <iostream>

int main() {
    srand(time(0));
    Board board = Board();
    __int8 option = 0;

    do {
        board.Reset();
        board.SetPlayers();

        for (__int8 i = 0; i < BOARD_SIZE; ++i) {
            system(CLEAR_SCREEN);
            board.Print();
            board.Play();

            if (board.isWin()) {
                system(CLEAR_SCREEN);
                board.Print();
                board.AnnounceWin();
                break;
            }

            board.SwitchPlayer();
        }

        board.PrintScore();
        std::cout << "Press \"0\" to restart:\n> ";
        scanf("%hhd", &option);
    } while (!option);

    return 0;
}