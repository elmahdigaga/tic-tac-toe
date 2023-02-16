#include "tic_tac_toe.h"

#include <iostream>

int main() {
    srand(time(0));
    Board board = Board();
    __int8 option = 0;

    do {
        board.Reset();       // Reset the board and it's settings
        board.SetPlayers();  // Set the players symbols and order of play

        for (__int8 i = 0; i < BOARD_SIZE; ++i) {
            system(CLEAR_SCREEN);  // Clear the screen
            board.Print();         // Show the board
            board.Play();          // Take input


            if (board.isWin()) {  // Check for a win
                break;
            }

            board.SwitchPlayer();  // Swap players turn
        }

        system(CLEAR_SCREEN);    // Clear the screen
        board.Print();           // Show the board
        board.AnnounceResult();  // Announce the winner or a draw
        board.PrintScore();      // Show the current score

        std::cout << "Press \"0\" to restart:\n> ";  // 0 to start another round
        scanf("%hhd", &option);
    } while (!option);

    return 0;
}