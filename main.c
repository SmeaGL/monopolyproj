/*
    Description: Simplified verison of the board game, Monopoly.
    Programmed by: Codie
    Version: 1.0.0
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

// Function Prototypes
void displayMenu();
void gameLoop(int mode);
int changePlayerTurn(int currentPlayer);
int movePlayer(int playerPosition, int steps);
void printBoard();
void printPlayerBalances(int player1Balance, int player2Balance);

int main()
{
    bool running = true;

    while(running)
    {
        int mode;

        system("clear||cls");
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
    Pre-condition: mode is a valid integer and Player 1 is always first.
    @param mode - current mode of game (play or debug).
*/
void gameLoop(int mode)
{
    bool inGame = true;

    int currentPlayer = 1;
    char board[21] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    char property[21] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

    // Player 1 Variables
    int player1Balance = 10000000;
    int player1Props[15];
    int player1JailTurns = 0;
    int player1Position = 0;

    // Player 2 Variables
    int player2Balance = 10000000;
    int player2Props[15];
    int player2JailTurns = 0;
    int player2Position = 0;

    while(inGame)
    {
        int steps;

        system("clear||cls");
        printBoard(board, property);
        printPlayerBalances(player1Balance, player2Balance);

        if(mode == 0)
        {
            printf("yes\n");
        }
        else if(mode == 1)
        {
            do
            {
                printf("Enter a number between 1-20:\n");
                scanf("%i", &steps);
            }
            while(steps < 1 || steps > 20);
        }

        printf("Steps: %i\n", steps);

        if(currentPlayer == 1)
        {
            board[player1Position] = ' ';
            player1Position = movePlayer(player1Position, steps);
            board[player1Position] = '1';
        }
        else
        {
            board[player2Position] = ' ';
            player2Position = movePlayer(player2Position, steps);
            board[player2Position] = '2';
        }

        currentPlayer = changePlayerTurn(currentPlayer);

    }
    inGame = false;
}

/*
    Changes current player.
    @param currentPlayer - the current player.
*/
int changePlayerTurn(int currentPlayer)
{
    int newPlayer;
    if (currentPlayer == 1)
    {
        newPlayer = 2;
    }
    else
    {
        newPlayer = 1;
    }

    return newPlayer;
}

/*
    Moves the current player.
    @param playerPosition - the current position of the player.
    @param steps - steps to take.
*/
int movePlayer(int playerPosition, int steps)
{
    int newPlayerPosition;

    if(playerPosition + steps > 19)
    {
        newPlayerPosition = abs((20 - playerPosition) - steps);
    }
    else
    {
        newPlayerPosition = playerPosition + steps;
    }

    return newPlayerPosition;
}

/*
    Prints the current state of board.
    @param board - the current state of board.
*/
void printBoard(char board[], char property[])
{
    printf("        e   f   g   h\n");
    printf("  +---+---+---+---+---+---+\n");
    printf("  |%c V|%c %c|%c %c|%c %c|%c %c|%c P|\n", board[5], board[6], property[6], board[7], property[7], board[8], property[8], board[9], property[9], board[10]);
    printf("  +---+---+---+---+---+---+\n");
    printf("d |%c %c|               |%c %c| i\n", board[4], property[4], board[11], property[11]);
    printf("  +---+               +---+\n");
    printf("c |%c %c|               |%c %c| j\n", board[3], property[3], board[12], property[12]);
    printf("  +---+               +---+\n");
    printf("b |%c %c|               |%c %c| k\n", board[2], property[2], board[13], property[13]);
    printf("  +---+               +---+\n");
    printf("a |%c %c|               |%c %c| l\n", board[1], property[1], board[14], property[14]);
    printf("  +---+---+---+---+---+---+\n");
    printf("  |%c G|%c %c|%c T|%c %c|%c %c|%c J|\n", board[0], board[19], property[19], board[18], board[17], property[17], board[16], property[16], board[15]);
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