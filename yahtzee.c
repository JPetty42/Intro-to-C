/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
//include the C libraries
#include <stdio.h>

//macros / global constants
#define ONE 1
#define TWO 2
#define NAME 20

//function prototypes
void welcomeScreen();
void playGame();
void displayEmptyCard();
void displayDice();

int main() {
    welcomeScreen();
    playGame();
    return 0;
}

void welcomeScreen() {
    printf ("\tY Y A H H TTTTT ZZZZZ EEEEE EEEEE\n");
    printf ("\t Y Y A A H H T Z E E \n");
    printf ("\t Y A A HHHHH T Z EEE EEE \n");
    printf ("\t Y A A A H H T Z E E \n");
    printf ("\t Y A A H H T ZZZZZ EEEEE EEEEE\n");
    printf("\n");
    
    printf ("YAHTZEE GAME RULES\n\n");
    printf("\t 1. Five six-sided dice.\n");
    printf("\t 2. Players roll all five dice.\n");
    printf("\t 3. Players can roll selected dice three times per turn.\n");
    printf("\t 4. Player must score one of the 13 categories per turn.\n");
    printf("\t 5. Players alternate turns.\n");
    printf("\t 6. Game ends when all players score 13 categories.\n");
    printf("\t 7. Player with the highest score wins!\n");
}

void playGame() {
    char playerOne[NAME];
    char playerTwo[NAME];
    int currentPlayer = ONE;
    
    //Player One enter name
    printf("\nPlayer One, enter your name\n");
    scanf("%s", playerOne);
    
    //Player 2 enter name
    printf("Player Two, enter your name\n");
    scanf("%s", playerTwo);
    
    printf("\n%s and %s, let's play Yahtzee! \n\n", playerOne, playerTwo);
    
    printf("%s it is your turn\n", playerOne);
    
    displayEmptyCard();
    
    displayDice();
    
    currentPlayer = TWO;
    
    printf("\n%s it is your turn\n", playerTwo);
    
    displayEmptyCard();
}

//Empty Card
void displayEmptyCard() {
    printf("|----------------------------------|\n");
    printf("| UPPER SECTION | LOWER SECTION |\n");
    printf("|----------------------------------|\n");
    printf("|----------------------------------|\n");
    printf("| Aces | | 3 Kind | |\n");
    printf("|----------------------------------|\n");
    printf("| Twos | | 4 Kind | |\n");
    printf("|----------------------------------|\n");
    printf("| Threes | | Full Hs | |\n");
    printf("|----------------------------------|\n");
    printf("| Fours | | Sm Str | |\n");
    printf("|----------------------------------|\n");
    printf("| Fives | | Lg Str | |\n");
    printf("|----------------------------------|\n");
    printf("| Sixes | | Yahtzee | |\n");
    printf("|----------------------------------|\n");
    printf("| Total | | Chance | |\n");
    printf("|----------------------------------|\n");
    printf("| Bonus | | Total | |\n");
    printf("|----------------------------------|\n");
    printf("|----------------------------------|\n");
    printf("| Game Total | |\n");
    printf("|----------------------------------|\n");
}

//Dice
void displayDice() {
    printf("\n+---+ +---+ +---+ +---+ +---+\n");
    printf("| 6 | | 3 | | 5 | | 2 | | 4 |\n");
    printf("+---+ +---+ +---+ +---+ +---+\n");
}