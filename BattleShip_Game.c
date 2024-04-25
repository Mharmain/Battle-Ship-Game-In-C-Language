#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 10
#define SHIP_SIZE 30

char userBoard[BOARD_SIZE][BOARD_SIZE];
char computerBoard[BOARD_SIZE][BOARD_SIZE];
int i, j;

void initializeBoards() {
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            userBoard[i][j] = ' ';
            computerBoard[i][j] = ' ';
        }
    }
}

void printBoards() {
    printf("Your Board:\n");
    for (i = 0; i < BOARD_SIZE; i++) {
        if (i == 0) {
            printf("   ");
        } else {
            printf(" ");
        }
        printf("%d", i);
    }
    printf("\n");
    for (i = 0; i < BOARD_SIZE; i++) {
        printf("%d  ", i);
        for (j = 0; j < BOARD_SIZE; j++) {
            printf("%c ", userBoard[i][j]);
        }
        printf("\n");
    }

    printf("\nComputer's Board:\n");
    for (i = 0; i < BOARD_SIZE; i++) {
        if (i == 0) {
            printf("   ");
        } else {
            printf(" ");
        }
        printf("%d", i);
    }
    printf("\n");
    for (i = 0; i < BOARD_SIZE; i++) {
        printf("%d  ", i);
        for (j = 0; j < BOARD_SIZE; j++) {
            printf("%c ", computerBoard[i][j]);
        }
        printf("\n");
    }
}

void placeShips_randomly(char board[BOARD_SIZE][BOARD_SIZE]) {
    int shipSize = SHIP_SIZE;
    while (shipSize > 0) {
        int x = rand() % BOARD_SIZE;
        int y = rand() % BOARD_SIZE;
        if (board[x][y] == ' ') {
            board[x][y] = 'S';
            shipSize--;
        }
    }
}

int isValidTarget(int x, int y) {
    return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
}

void placeShips_manually(char board[BOARD_SIZE][BOARD_SIZE]) {
    int x, y, shipSize = SHIP_SIZE;
    for (i = 0; i < shipSize; i++) {
        printf("Enter the location (x y) of ship %d: ", i + 1);
        scanf("%d %d", &x, &y);

        if (isValidTarget(x, y) && board[x][y] == ' ') {
            board[x][y] = 'S';
        } else {
            printf("Incorrect input! Try again.\n");
            i--;
        }
    }
}

int main() {
	
    srand(time(NULL));

    initializeBoards();
    placeShips_randomly(computerBoard);

    char ch_1, ch_2, ch_3, ch_4;
    int userShips = SHIP_SIZE;
    int computerShips = SHIP_SIZE;

    printf("\t\t\t\t\tWelcome to Battleship Game!\n");
    printf("\t\t\t\t     Try to sink the computer's ships.\n\n");

    do {
	    int hit_user = 0, hit_computer = 0, miss_user = 0, miss_computer = 0;
        printf("Menu:\n");
        printf("1. Play Game\n");
        printf("2. See Instructions\n");
        printf("3. Quit\n");
        printf("Enter your choice (1, 2, or 3): ");
        scanf(" %c", &ch_1);

        switch (ch_1) {
            case '1':
                back:
                printf("\n1. Place ships yourself\n");
                printf("2. Place ships randomly\n");
                printf("Enter your choice (1 or 2): ");
                scanf(" %c", &ch_2);

                switch (ch_2) {
                    case '1':
                        placeShips_manually(userBoard);
                    break;

                    case '2':
                        placeShips_randomly(userBoard);
                    break;

                    default:
                        printf("Invalid input. Please enter 1 or 2.\n");
                    goto back;
                }

                while (userShips > 0 && computerShips > 0) {
                    int userX, userY, computerX, computerY;

                    printf("\n");
                    printBoards();

                    printf("\nYour turn. Enter target coordinates (x y): ");
                    scanf("%d %d", &userX, &userY);

                    if (isValidTarget(userX, userY) && computerBoard[userX][userY] == 'S') {
                        hit_user++;
                        printf("\nYou hit a ship!\n");
                        computerBoard[userX][userY] = 'X';
                        computerShips--;
                    } 
					else if (isValidTarget(userX, userY) && computerBoard[userX][userY] != 'X') {
                        miss_user++;
                        printf("\nYou missed.\n");
                        computerBoard[userX][userY] = 'O';
                    } 
					else if (isValidTarget(userX, userY) && computerBoard[userX][userY] == 'X') {
                        miss_user++;
                        printf("\nYou missed.\n");
                    }
					else if (userX>BOARD_SIZE||userX<0||userY>BOARD_SIZE||userY<0) {
                        miss_user++;
                        printf("\nYou missed.\n");
                    }

                    do {
                        computerX = rand() % BOARD_SIZE;
                        computerY = rand() % BOARD_SIZE;
                    } while (userBoard[computerX][computerY] == 'X' || userBoard[computerX][computerY] == 'O');

                    if (userBoard[computerX][computerY] == 'S') {
                        hit_computer++;
                        printf("The computer hit your ship at (%d, %d)!\n\n", computerX, computerY);
                        userBoard[computerX][computerY] = 'X';
                        userShips--;
                    } else {
                        miss_computer++;
                        printf("The computer missed at (%d, %d)!\n\n", computerX, computerY);
                        userBoard[computerX][computerY] = 'O';
                    }

                    printf("TOTAL USER HITS: %d\n", hit_user);
                    printf("TOTAL USER MISS: %d\n", miss_user);
                    printf("TOTAL COMPUTER HITS: %d\n", hit_computer);
                    printf("TOTAL COMPUTER MISS: %d\n", miss_computer);
                }

                printf("\nTHE GAME IS OVER\n");

                if (computerShips == 0) {
                    printf("CONGRATULATIONS! YOU SUNK ALL OF THE COMPUTER'S SHIPS.\nYOU WIN\n");
                } else if (userShips == 0) {
                  printf("OOPS! THE COMPUTER SUNK ALL OF YOUR SHIPS.\nYOU LOSE\n");
                }

                printf("1. Play again\n");
                printf("2. Exit\n");
                printf("Enter your choice (1 or 2): ");
                scanf(" %c", &ch_4);

                switch (ch_4) {
                    case '1':
                        initializeBoards();
                        placeShips_randomly(computerBoard);
                        userShips = SHIP_SIZE;
                        computerShips = SHIP_SIZE;
                    break;

                    default:
                        printf("The game is exiting. Thank you for playing!\n");
                    return 0;
                }

                break;

            case '2':
 				printf("\nINSTRUCTIONS:\n");
				printf("Step 1: Place yor ships on a 10x10 map.\n");
   				printf("Step 2: Start entering the row and colomn coordinates for hitting a specific position on computers map\n");
				printf("Note: The player who has most hits under his belt is the winner\n\n");                
				printf("1. Play (Press 1)\n");
                printf("2. Quit (Press any key)\n");
                printf("\nEnter your choice: ");
                scanf(" %c", &ch_3);

                switch (ch_3) {
                    case '1':
                        goto back;
                    break;

                    default:
                        printf("The game is exiting. Thank you for playing!\n");
                    return 0;
                }

                break;

            case '3':
                printf("\nThe game is exiting. Thank you for playing!\n");
                return 0;

            default:
                printf("\nInvalid input. Please enter 1, 2, or 3.\n");
        }

    } while (1);
    
    return 0;
}
