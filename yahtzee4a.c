//include the C libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//macros / global constants
#define ONE 1
#define TWO 2
#define THREE 3
#define FOUR 4
#define FIVE 5
#define NAME 20
#define ZERO 0
#define SIX 6
#define ROLLS 3
#define DICE 5
#define FALSE 0
#define TRUE 1
#define CATEGORY 13
#define COLS 2

//Structure before prototypes
struct Player {
    int playerNum;
    char playerName[NAME];
    int scoreCard[CATEGORY][COLS];
};

//Enumeration of scores
enum scores{one, two, three, four, five, six, 
    threekind, fourkind, fullhouse, smstr,
    lgstr, yahtzee, chance};

void initScorecard(int scoreCard[CATEGORY][COLS]);
int selectCategory(int scoreCard[CATEGORY][COLS]);
void updateScores(int scoreCard[CATEGORY][COLS], int category, int score);
void displayScoreCard(int scoreCard[CATEGORY][COLS]);

//function prototypes
void welcomeScreen();
void playGame();
void displayEmptyCard();
void displayDice();

//functions for displayRandomDice and rollDie
//commented out void displayRandomDice();
int rollDie();

void initDice(int dice[DICE]);
void rollDice(int dice[DICE], int keep[DICE]);
int selectDice(int dice[DICE], int keep[DICE]);
void displayRoll(int dice[DICE]);
void trimTrailing(char * str);
int isValid(char data[NAME]);


int main() 
{
    welcomeScreen();
    //random function
    srand((unsigned int) time(NULL));
    playGame();
    return 0;
}


//Yahtzee welcome screen and rules
void welcomeScreen() 
{
    printf ("\n\tY     Y  A     H   H  TTTTT  ZZZZZ  EEEEE  EEEEE\n");
    printf ("\t  Y Y   A A    H   H    T       Z   E      E \n");
    printf ("\t   Y   A   A   HHHHH    T      Z    EEE    EEE \n");
    printf ("\t   Y  A  A  A  H   H    T     Z     E      E \n");
    printf ("\t   Y  A     A  H   H    T    ZZZZZ  EEEEE  EEEEE\n");
    printf("\n");

    
    printf ("YAHTZEE GAME RULES\n\n");
    printf("\t 1. Five six-sided dice.\n");
    printf("\t 2. Players roll all five dice.\n");
    printf("\t 3. Players can roll selected dice three times per turn.\n");
    printf("\t 4. Player must score one of the 13 categories per turn.\n");
    printf("\t 5. Players alternate turns.\n");
    printf("\t 6. Game ends when all players score 13 categories.\n");
    printf("\t 7. Player with the highest score wins!\n\n");
}


void playGame() 
{
    //Change data type to struct
    struct Player playerOne;
    struct Player playerTwo;
    
    int currentPlayer;
    int category;
  //  int c;  //for flushing ---------------------------
   
    //loop initialized to 0
    int loop = ZERO;
    int dice[DICE];
    int keep[DICE];
    
    //Player One enter name
    printf("\nPlayer One, enter your name\n");
    scanf("%s", playerOne.playerName);
   
    //set struct value to each player
    playerOne.playerNum = ONE;
    initScorecard(playerOne.scoreCard);
    
    //Player 2 enter name
    printf("\nPlayer Two, enter your name\n");
    scanf("%s", playerTwo.playerName);
    
    //set struct value to each player
    playerTwo.playerNum = TWO;
    initScorecard(playerTwo.scoreCard);
    
    currentPlayer = playerOne.playerNum;
    
    printf("\n%s and %s, let's play Yahtzee! \n\n", playerOne.playerName, playerTwo.playerName);
    
    //while loop iterates twice
    while (loop < TWO) 
    {
        if(currentPlayer == playerOne.playerNum)
        {
             printf("%s it is your turn\n", playerOne.playerName);
             
             displayScoreCard(playerOne.scoreCard);
             
             //commented out displayRandomDice();
             
             //call function initDice for arrays dice and keep
             initDice(dice);
             initDice(keep);
             
             // flush the standard in
             fflush(stdin);
             
             //Call function rollDice
             rollDice(dice, keep);
             
             // Select category and update scores
             category = selectCategory(playerOne.scoreCard);
             updateScores(dice, playerOne.scoreCard, category);
             displayScoreCard(playerOne.scoreCard);
             
             currentPlayer = playerTwo.playerNum;
             
         
        }
        else if(currentPlayer == playerTwo.playerNum)
        {
            printf("\n%s it is your turn\n", playerTwo.playerName);
            
            displayScoreCard(playerTwo.scoreCard);
            
            //commented out displayRandomDice();
            
            //call function initDice for arrays dice and keep
            initDice(dice);
            initDice(keep);
            
            //flush the standard in
            fflush(stdin);
            
            //call function rollDice
            rollDice(dice, keep);
            
            //Select category and update scores
            category = selectCategory(playerTwo.scoreCard);
            updateScores(dice, playerTwo.scoreCard, category);
            displayScoreCard(playerTwo.scoreCard);
            
            currentPlayer = playerOne.playerNum;
        }
        
        //increment loop control variable to satisfy while loop
        loop++;
    }
}


//Empty Card
void displayEmptyCard() 
{
    printf("+----------------------------------+\n");
    printf("| UPPER SECTION  | LOWER SECTION   |\n");
    printf("|----------------------------------|\n");
    printf("|----------------------------------|\n");
    printf("| Aces   |       | 3 Kind |        |\n");
    printf("|----------------------------------|\n");
    printf("| Twos   |       | 4 Kind |        |\n");
    printf("|----------------------------------|\n");
    printf("| Threes |       | Full Hs|        |\n");
    printf("|----------------------------------|\n");
    printf("| Fours  |       | Sm Str |        |\n");
    printf("|----------------------------------|\n");
    printf("| Fives  |       | Lg Str |        |\n");
    printf("|----------------------------------|\n");
    printf("| Sixes  |       | Yahtzee|        |\n");
    printf("|----------------------------------|\n");
    printf("| Total  |       | Chance |        |\n");
    printf("|----------------------------------|\n");
    printf("| Bonus  |       | Total  |        |\n");
    printf("|----------------------------------|\n");
    printf("|----------------------------------|\n");
    printf("|       Game Total        |        |\n");
    printf("+----------------------------------+\n");
}


//Dice
void displayDice()
{
    printf("\n+---+ +---+ +---+ +---+ +---+\n");
    printf("| 6 | | 3 | | 5 | | 2 | | 4 |\n");
    printf("+---+ +---+ +---+ +---+ +---+\n");
}

void displayRandomDice() 
{
    int roll;
    int die1, die2, die3, die4, die5;
    
    //for loop iterates three times aka for ROLLS
    for(roll = ZERO; roll < ROLLS; roll++) 
    {
        die1 = rollDie();
        die2 = rollDie();
        die3 = rollDie();
        die4 = rollDie();
        die5 = rollDie();
        
        //tracks each roll then increments by 1 until for loop is satisfied
        printf("\nRoll %d\n", (roll + 1));
        
        //displays random values of each die
        //%d is used as a placeholder to maintain formatting and box shape
        //then die1 - die5 values are called to replace the %d's in order
        printf("\n+---+ +---+ +---+ +---+ +---+\n");
        printf("| %d | | %d | | %d | | %d | | %d |\n", die1, die2, die3, die4, die5);
        printf("+---+ +---+ +---+ +---+ +---+\n"); 
        
    }
}


//rollDie function generates and returns a random number from 1-6 
//simulates rolling one die
int rollDie() 
{
    int dieValue = rand() % SIX + ONE;
    return dieValue;
    
}

void initDice(int dice[DICE])
{
    //loop through the five dice
    for(int die = 0; die < DICE; die++)
    {
        //set each die to FALSE
        dice[die] = FALSE;
        
    }
}
void rollDice(int dice[DICE], int keep[DICE])
{
    int roll = ZERO;
    //iterate through the three rolls
    while(roll < ROLLS)
    {
        printf("Roll %d\n", (roll + 1));
        //iterate through the five dice
        for(int die = 0; die < DICE; die++)
        {
            //only roll dice that have not been selected to keep
            if(keep[die] == FALSE)
            {
                dice[die] = rollDie();
            }
            
        }
        
        //display the current roll
        displayRoll(dice);
        
        // if the selected dice are not valid, player needs to be prompted again
        // without increasing the roll number
        if(selectDice(dice, keep) == FALSE)
        {
            printf("Selected dice invalid, try again\n");
        }
        
        else
        {
            roll++;
        }
        
    } //end while loop for three rolls
}

// prompts player to select the dice they want to keep from their roll
int selectDice(int dice[DICE], int keep[DICE])
{
    // store the player's input
    char input[NAME];
    char data[NAME];
    
    // variable for each token in string data
    char * value;
    
    // looping control variable to force user to select valid die
    int valid = FALSE;
    
    // prompt the user
    printf("\nSelect dice to keep, enter values 1 through 5 with spaces between numbers\n");
    
    // read the input
    fgets(input, NAME, stdin);
    
    // remove any trailing spaces
    trimTrailing(input);
    
    // check if the input is valid before parsing
    strcpy(data, input);
    
    valid = isValid(data);
    
    // if the input is not valid, return false
    if(!valid)
        return FALSE;
    
    // call initDice() for the keep array for each request
    // since users can change their mind for each roll
    initDice(keep);
    
    // parse the string into each value
    // priming read for first value
    value = strtok(input, " ");
    // loop to end of input
    while(value != NULL )
    
    {
        int number = atoi(value);
        switch(number)
        {
            case ONE:
                keep[ZERO] = TRUE;
                valid = TRUE;
                break;
            case TWO:
                keep[ONE] = TRUE;
                valid = TRUE;
                break;
            case THREE:
                keep[TWO] = TRUE;
                valid = TRUE;
                break;
            case FOUR:
                keep[THREE] = TRUE;
                valid = TRUE;
                break;
            case FIVE:
                keep[FOUR] = TRUE;
                valid = TRUE;
                break;
            default:
                break;
            
        }
        // read the next value
        value = strtok(NULL, " ");
    }
    return valid;
}

void displayRoll(int dice[DICE])
{
    printf("+-------+ +-------+ +-------+ +-------+ +-------+\n");
    printf("|       | |       | |       | |       | |       |\n");
    
    for(int die = 0; die < DICE; die++)
    {
        printf("|   %d   | ", dice[die]);
    }
    
    printf("\n");
    printf("|       | |       | |       | |       | |       |\n");
    printf("+-------+ +-------+ +-------+ +-------+ +-------+\n");
    printf("   (1)       (2)       (3)       (4)       (5)   \n");
    
}

int isValid(char data[NAME])
{
    int valid = FALSE;
    char * value;
    
    // parse the string into each value
    // priming read for first value
    value = strtok(data, " ");
    
    // loop to end of input
    while(value != NULL )
    {
        // convert the string data to integer
        int number = atoi(value);
        
        // if data is valid, set valid to TRUE
        if(number >= ONE && number <= FIVE)
        {
            valid = TRUE;
        }
        // else data is invalid, set valid to FALSE and break out of the loop
        else
        {
            valid = FALSE;
            break;
        }
        
        value = strtok(NULL, " ");
        
    }
    return valid;
}

void trimTrailing(char * str)
{
    // Set default index to invalid number
    int index = -1;
    
    // loop control variable
    int i = 0;
    
    // Find last index of non-white space character
    while(str[i] != '\0')
    {
        if(str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
        {
            index = i;
        }
        
        i++;
        
    }
    // Mark next character to last non-white space character as NULL
    str[index + 1] = '\0';
    
}

void initScorecard(int card[CATEGORY][COLS])
{
    for (int row = 0; row < CATEGORY; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            if (col == ZERO)
            {
                card[row][col] = row;
            }
            else
            {
                card[row][col] = ZERO;
            }
        }
    }
}

int selectCategory()
{
    int select = ZERO;
    int valid = FALSE;

    while (valid == FALSE)
    {
        // Category selection menu
        printf("\nSelect a category for dice:\n");
        printf("1.  Ones\n");
        printf("2.  Twos\n");
        printf("3.  Threes\n");
        printf("4.  Fours\n");
        printf("5.  Fives\n");
        printf("6.  Sixes\n");
        printf("7.  Three of a Kind\n");
        printf("8.  Four of a Kind\n");
        printf("9.  Full House\n");
        printf("10. Small Straight\n");
        printf("11. Large Straight\n");
        printf("12. Yahtzee\n");
        printf("13. Chance\n");
        printf("Enter category number: ");
        
        scanf("%d", &select);
        fflush(stdin); // Use getchar() instead if needed on replit

        if (select >= 1 && select <= 13)
        {
            valid = TRUE;
        }
        else
        {
            printf("Error! Please enter a number between 1 and 13.\n");
            valid = FALSE;
        }
    }
    return select;
}

//Function for updating scores
void updateScores(int dice[DICE], int scoreCard[CATEGORY][COLS], int category)
{
    switch (category)
    {
        case one:
            printf("Selected Category: Ones\n");
            break;
        case two:
            printf("Selected Category: Twos\n");
            break;
        case three:
            printf("Selected Category: Threes\n");
            break;
        case four:
            printf("Selected Category: Fours\n");
            break;
        case five:
            printf("Selected Category: Fives\n");
            break;
        case six:
            printf("Selected Category: Sixes\n");
            break;
        case threekind:
            printf("Selected Category: Three of a Kind\n");
            break;
        case fourkind:
            printf("Selected Category: Four of a Kind\n");
            break;
        case fullhouse:
            printf("Selected Category: Full House\n");
            break;
        case smstr:
            printf("Selected Category: Small Straight\n");
            break;
        case lgstr:
            printf("Selected Category: Large Straight\n");
            break;
        case yahtzee:
            printf("Selected Category: Yahtzee\n");
            break;
        case chance:
            printf("Selected Category: Chance\n");
            break;
        default:
            printf("Invalid Category. Please try again\n");
            break;
    }
}

void displayScoreCard(int scoreCard[CATEGORY][COLS])
{
    printf("+-----------------------------------+\n");
    printf("| UPPER SECTION  |  LOWER SECTION   |\n");
    printf("|-----------------------------------|\n");
    printf("|-----------------------------------|\n");
    printf("| Aces   |   %d   | 3 Kind |   %d   |\n", scoreCard[one][ONE], scoreCard[threekind][ONE]);
    printf("|-----------------------------------|\n");
    printf("| Twos   |   %d   | 4 Kind |   %d   |\n", scoreCard[two][ONE], scoreCard[fourkind][ONE]);
    printf("|-----------------------------------|\n");
    printf("| Threes |   %d   | Full Hs|   %d   |\n", scoreCard[three][ONE], scoreCard[fullhouse][ONE]);
    printf("|-----------------------------------|\n");
    printf("| Fours  |   %d   | Sm Str |   %d   |\n", scoreCard[four][ONE], scoreCard[smstr][ONE]);
    printf("|-----------------------------------|\n");
    printf("| Fives  |   %d   | Lg Str |   %d   |\n", scoreCard[five][ONE], scoreCard[lgstr][ONE]);
    printf("|-----------------------------------|\n");
    printf("| Sixes  |   %d   | Yahtzee|   %d   |\n", scoreCard[six][ONE], scoreCard[yahtzee][ONE]);
    printf("|-----------------------------------|\n");
    printf("| Total  |   %d   | Chance |   %d   |\n", ZERO, scoreCard[chance][ONE]);
    printf("|-----------------------------------|\n");
    printf("| Bonus  |   %d   | Total  |   %d   |\n", ZERO, ZERO);
    printf("|-----------------------------------|\n");
    printf("|-----------------------------------|\n");
    printf("|       Game Total         |   %d   |\n", ZERO);
    printf("+----------------------------------+\n");
}



















