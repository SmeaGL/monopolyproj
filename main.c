/*
    Description: Simplified verison of the board game, Monopoly.
    Programmed by: Codie
    Version: 1.0.0
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

// Function Prototypes
void displayMenu();
void gameLoop(int mode);
int debugStepInput();
void changePlayerTurn(char *currentPlayer, char *otherPlayer, int *currentPlayerPosition, int *otherPlayerPosition,
                        int **currentPlayerBalance, int **otherPlayerBalance);
void updateBoardValues(char *boardPlayerPositions, char currentPlayer, char otherPlayer, int *currentPlayerPosition, int *otherPlayerPosition, int steps);
int updatePlayerPosition(int playerPosition, int steps);
int checkTilePurpose(char currentPlayer, int *currentPlayerPosition, int *currentPlayerBalance, int *otherPlayerBalance, char *propertyPositions, int *cost, int *rent);
int buyOrRentProperty(char currentPlayer, int *currentPlayerPosition, int *currentPlayerBalance, int *otherPlayerBalance, char *propertyPositions, int cost, int rent);
void printBoard(char board[], char property[]);
void printPlayerBalances(int player1Balance, int player2Balance);
void printRollSummary(char currentPlayer, int *currentPlayerPosition, int steps, char *boardNames[]);
void printActionSummary(int *currentPlayerPosition, int otherPlayer, char *boardNames[], int tileChoice, int rent);



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

    // Player 1 Variables
    int player1Balance = 10000000;
    int player1JailTurns = 0;
    int player1Position = 0;

    // Player 2 Variables
    int player2Balance = 10000000;
    int player2JailTurns = 0;
    int player2Position = 0;

    // Current Player Variables
    char currentPlayer = '1';
    int *currentPlayerPosition = &player1Position;
    int *currentPlayerBalance = &player1Balance;

    // Other Player Variables
    char otherPlayer = '2';
    int *otherPlayerPosition = &player2Position;
    int *otherPlayerBalance = &player2Balance;

    // Board Variales
    char boardPlayerPositions[21] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    char propertyPositions[21] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    char *boardNames[21] = {"Go", "Property A", "Property B", "Property C", "Property D", "Just Visiting", "Property E", "Property F",
                                    "Property G", "Property H", "Free Parking", "Property I", "Property J", "Property K", "Property L",
                                    "Go To Jail", "Property M", "Property N", "Luxury Tax", "Property O"};


    while(inGame)
    {
        int steps;

        // Clears the console and prints the current state of board and player balances.
        system("clear||cls");
        printBoard(boardPlayerPositions, propertyPositions);
        printPlayerBalances(player1Balance, player2Balance);
        printf("\n");

        
        // Checks the current mode and changes user input between random and specified.
        if(mode == 0)
        {
            printf("yes\n");
        }
        else
        {
            steps = debugStepInput();
        }
        
        // Check if will pass go and add balance if yes
        if(*currentPlayerPosition + steps >= 20)
        {   
            *currentPlayerBalance += 1000000;
        }

        // Moves the current player
        boardPlayerPositions[*currentPlayerPosition] = ' ';
        *currentPlayerPosition = updatePlayerPosition(*currentPlayerPosition, steps);


        // Update the board values
        updateBoardValues(boardPlayerPositions, currentPlayer, otherPlayer, currentPlayerPosition, otherPlayerPosition, steps);

        // Re-print the current board after player move.
        system("clear||cls");
        printBoard(boardPlayerPositions, propertyPositions);
        printPlayerBalances(player1Balance, player2Balance);
        printf("\n");
        printRollSummary(currentPlayer, currentPlayerPosition, steps, boardNames);

        int cost;
        int rent;
        int tileChoice;
        int tilePurpose = checkTilePurpose(currentPlayer, currentPlayerPosition, currentPlayerBalance, otherPlayerBalance, propertyPositions, &cost, &rent);
        switch(tilePurpose)
        {
            case 0:
                tileChoice = -1;
                break;
            case 1:
                tileChoice = buyOrRentProperty(currentPlayer, currentPlayerPosition, currentPlayerBalance, otherPlayerBalance, propertyPositions, cost, rent);
                break;
        }
        

        system("clear||cls");
        printBoard(boardPlayerPositions, propertyPositions);
        printPlayerBalances(player1Balance, player2Balance);
        printf("\n");
        printRollSummary(currentPlayer, currentPlayerPosition, steps, boardNames);
        printActionSummary(currentPlayerPosition, otherPlayer, boardNames, tileChoice, rent);

        // Change the player variables.
        changePlayerTurn(&currentPlayer, &otherPlayer, currentPlayerPosition, otherPlayerPosition, &currentPlayerBalance, &otherPlayerBalance);

        // Wait for the player to end turn.
        printf("\n");
        printf("Press ENTER key to end turn.\n");
        fflush(stdin);
        getchar();
    }

    inGame = false;
}


/*
    Gets user input for number of steps (for debug mode only).
    @return returns the number of steps from input.
*/
int debugStepInput()
{
    int steps;

    do
    {
        printf("Enter a number between 1-20:\n");
        int success = scanf("%i", &steps);

        // Check if input is integer
        switch(success)
        {
            case 1:
                break;
            case 0:
                fflush(stdin);
                steps = 0;
                break;
        }
    }
    while(steps < 1 || steps > 20);

    return steps;
}

/*
    Changes current player.
    @param currentPlayer - the current player.
    @return returns the new player.
*/
void changePlayerTurn(char *currentPlayer, char *otherPlayer, int *currentPlayerPosition, int *otherPlayerPosition,
                        int **currentPlayerBalance, int **otherPlayerBalance)
{
    char newPlayer;
    int newPlayerPosition;
    int *newPlayerBalance;

    // Store other variable to new
    newPlayer = *otherPlayer;
    newPlayerPosition = *otherPlayerPosition;
    newPlayerBalance = *otherPlayerBalance;

    // Change other
    *otherPlayer = *currentPlayer;
    *otherPlayerPosition = *currentPlayerPosition;
    *otherPlayerBalance = *currentPlayerBalance;

    // Change current
    *currentPlayer = newPlayer;
    *currentPlayerPosition = newPlayerPosition;
    *currentPlayerBalance = newPlayerBalance;
}

/*
    Updates the board values according to player positions.
    @param currentPlayer - the current player.
    @param otherPlayer - the other player.
    @param player1Position - the position of player 1.
    @param player2Position - the position of player 2.
    @param beforeMove - checks if called before or after player move.
    @return returns the new value for the board according to the current player's position. 
*/
void updateBoardValues(char *boardPlayerPositions, char currentPlayer, char otherPlayer, int *currentPlayerPosition, int *otherPlayerPosition, int steps)
{   
    if(*currentPlayerPosition == *otherPlayerPosition)
    {
        boardPlayerPositions[*currentPlayerPosition] = '3';
    }
    else
    {
        boardPlayerPositions[*currentPlayerPosition] = currentPlayer;
        boardPlayerPositions[*otherPlayerPosition] = otherPlayer;
    }
}

/*
    Moves the current player.
    @param playerPosition - the current position of the player.
    @param steps - steps to take.
    @return returns new player position after taking steps.
*/
int updatePlayerPosition(int playerPosition, int steps)
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

int checkTilePurpose(char currentPlayer, int *currentPlayerPosition, int *currentPlayerBalance, int *otherPlayerBalance, char *propertyPositions, int *cost, int *rent)
{
    int returnValue;

    switch(*currentPlayerPosition)
    {   
        case 1:
        case 2:
        case 3:
        case 4:
            *cost = 2000000;
            *rent = 300000;
            returnValue = 1;
            break;

        case 6:
        case 7:
        case 8:
        case 9:
            *cost = 4000000;
            *rent = 500000;
            returnValue = 1;
            break;
        
        case 11:
        case 12:
        case 13:
        case 14:
            *cost = 6000000;
            *rent = 1000000;
            returnValue = 1;
            break;

        case 16:
        case 17:
        case 19:
            *cost = 8000000;
            *rent = 2000000;
            returnValue = 1;
            break;

        // Go To Jail
        case 15:
            break;

        // Luxury Tax
        case 18:
            *currentPlayerBalance -= 1000000;
            returnValue = 3;
            break;
        default:
            returnValue = 0;
            break;
    }

    return returnValue;
}

int buyOrRentProperty(char currentPlayer, int *currentPlayerPosition, int *currentPlayerBalance, int *otherPlayerBalance, char *propertyPositions, int cost, int rent)
{
    int returnValue;
    
    // Ask to buy property
    if(propertyPositions[*currentPlayerPosition] == ' ')
    {
        char answer;
        fflush(stdin);
        printf("\n");
        printf("Would you like to buy this property? y/n: \n");

        int success = scanf("%c", &answer);
        switch(success)
        {
            case 1:
                break;
            case 0:
                fflush(stdin);
                answer = ' ';
                break;
        }
        
        answer = tolower(answer);

        if (answer == 'y')
        {
            if (*currentPlayerBalance >= cost)
            {
                if(currentPlayer == '1')
                {
                    propertyPositions[*currentPlayerPosition] = 'X';
                }
                else
                {
                    propertyPositions[*currentPlayerPosition] = 'Y';
                }

                returnValue = 0;
            }
            else
            {
                returnValue = 1;
            }
        }
    }

    // Pay rent
    else
    {
        *currentPlayerBalance -= rent;
        *otherPlayerBalance += rent;

        returnValue = 2;
    }

    return returnValue;
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

/*
    Prints the current turn's summary.
    @param currentPlayer - the current player.
    @param steps - the rolled steps to take.
    @param player1Position - the position of player 1.
    @param player2Position - the position of player 2.
    @param boardNames - the array of the names of each position on the board.
*/
void printRollSummary(char currentPlayer, int *currentPlayerPosition, int steps, char *boardNames[])
{
    printf("Player %c turn:\n", currentPlayer);
    printf("- rolled a %i\n", steps);
    printf("- landed on %s\n", boardNames[*currentPlayerPosition]);
}

void printActionSummary(int *currentPlayerPosition, int otherPlayer, char *boardNames[], int tileChoice, int rent)
{
    switch(tileChoice)
    {
        case 0:
            printf("- bought %s\n", boardNames[*currentPlayerPosition]);
            break;
        case 1:
            printf("\n");
            printf("Not enough money.\n");
            break;
        case 2:
            printf("- paid %i.00 to Player %c\n", rent, otherPlayer);
            break;
        case 3:
            printf("- paid Luxury Tax");
        default:
            break;
    }
}