/*
    Description: Simplified verison of the board game, Monopoly.
    Programmed by: Codie
    Version: 1.0.0
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Function Prototypes
void displayMenu();
void gameLoop(int mode);
void printBoard();
void printPlayerBalances(int player1Balance, int player2Balance);

int main()
{
    bool running = true;

    while(running)
    {
        int mode;

        system("clear");
        displayMenu();

        scanf("%i", &mode);

        if(mode == 0)
        {
            gameLoop(mode);
        }
        else if(mode == 1)
        {
            gameLoop(mode);
        }
        else
        {
            running = false;
        }
    }

    return 0;
}

/*
    Displays the main menu screen.
*/
void displayMenu()
{
    printf("%-5s %s\n", "", "-=-=-=-=-=-=-=");
    printf("%-5s %s\n", "", "|| Minipoly ||");
    printf("%-5s %s\n", "", "-=-=-=-=-=-=-=");

    printf("%-6s %s\n", "", "Codie Aragon");
    printf("\n");

    printf("Choose 0 for play mode\n");
    printf("Choose 1 for debug mode\n");
    printf("Choose any other number to quit.\n");
}

/*
    The main loop of the game.
*/
void gameLoop(int mode)
{
    bool inGame = true;

    // Current game static variables
    int currentPlayer;
    char board[21] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    int player1Balance = 10000000;
    int player2Balance = 10000000;
    int player1Props[15];
    int player2Props[15];

    while(inGame)
    {
        int steps;

        system("clear");
        printBoard(board);
        printPlayerBalances(player1Balance, player2Balance);

        if(mode == 0)
        {
            printf("yes\n");
        }
        else if(mode == 1)
        {
            scanf("%i", &steps);
        }

        printf("Steps: %i\n", steps);

        inGame = false;
    }
}


/*
    Prints the current state of board.
    @param board - the current state of board.
*/
void printBoard(char board[])
{
    printf("        e   f   g   h\n");
    printf("  +---+---+---+---+---+---+\n");
    printf("  | %cV| %c | %c | %c | %c | %cP|\n", board[5], board[6], board[7], board[8], board[9], board[10]);
    printf("  +---+---+---+---+---+---+\n");
    printf("d | %c |               | %c | i\n", board[4], board[11]);
    printf("  +---+               +---+\n");
    printf("c | %c |               | %c | j\n", board[3], board[12]);
    printf("  +---+               +---+\n");
    printf("b | %c |               | %c | k\n", board[2], board[13]);
    printf("  +---+               +---+\n");
    printf("a | %c |               | %c | l\n", board[1], board[14]);
    printf("  +---+---+---+---+---+---+\n");
    printf("  | %cG| %c | %c | %c | %c | %cJ|\n", board[0], board[19], board[18], board[17], board[16], board[15]);
    printf("  +---+---+---+---+---+---+\n");
    printf("        o       n   m\n");
}

/*
    Prints the current balance of each player.
    @param player1Balance - the current balance of Player 1.
    @param player2Balance - the current balance of Player 2.
*/
void printPlayerBalances(int player1Balance, int player2Balance)
{
    printf("Account Balance:\n");
    printf("Player 1: %i.00\n", player1Balance);
    printf("Player 2: %i.00\n", player2Balance);
}