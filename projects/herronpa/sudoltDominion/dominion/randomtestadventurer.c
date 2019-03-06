/****************************************************************************
* Author: Parick M. Herron
* Date: Feb 15, 2019
* Name: RandomTestAdventurer
* Description:  A random test generators for adventurer card.  We write here a 
* test suite that checks whether playing the adventurer card properly draws
* a maximum of two treasures from the deck as well as discarding the 
* adventurer card.  The input variables that we vary in order to achieve this
* are the number of players as well as the seed of the initialization.
* Additionally, we randomize the players starting hand and starting deck
* so that the number of treasures in both the hand and the deck vary for
* each run. 
****************************************************************************/  
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

//Function prototype for custom assert method
int asserttrue(int x, int y);
void formatOutput(int, int, char*);

int main()
{
    int correctTreasure = 0; //check if number of treasures is within scope
    int disCardTrue = 1;     //check if Adventurer was discarded
    int drewCorTreasure = 0; //accumulator for treasure draw test
    int discardCardTest = 0; //accumulator for discard test
    int totalTests = 0;      //total random tests generated
    struct gameState baseGame, testGame;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		 sea_hag, tribute, smithy, council_room};
    time_t t;                //seed for random

    srand((unsigned) time(&t));

    //loop to vary the seed for the initialization
    for (int i = 1; i <= 1000; i++)
    {
        //loop to vary the number of players from 2 to 4
        for (int j = 2; j <= 4; j++)
        {
            //changes starting hand size from 2 to 10 within realistic expectations
            for (int a = 2; a <= 10; a++)
            {
                //initialize and copy game
                initializeGame(j, k, i, &baseGame);
                memcpy(&testGame, &baseGame, sizeof(struct gameState));
 
                //set starting hand size
                testGame.handCount[0] = a;
                
                //randomize starting hand contents
                for (int b = 0; b < testGame.handCount[0]; b++)
                    testGame.hand[0][b] = 1 + rand() % 6;

                //randomize starting deck contents
                for (int b = 0; b < testGame.deckCount[0]; b++)
                {
                    int randNum = rand() % 100;
                    
                    if (randNum <= 95 )
                        testGame.deck[0][b] = copper;
                    else
                        testGame.deck[0][b] = sea_hag;
                }  
                    
                //set default treasure values; some peril here in that they both
                //have the same value so if no treasure is drawn it will report a
                //false positive for a misfunctioning card
                int TreasurePre = 0;
                int TreasurePost = 0;

                //uses gainCard() function to add an adventurer card to the existing hand
                //the 2 as the third argument is a flag to put the card in the hand
                //the 0 as the third argument is the player number
                gainCard(adventurer, &testGame, 2, 0); 

                //We check here the number of cards in the hand and deck
                //for comparison after the function has run
                for (int z = 0; z < testGame.handCount[0]; z++)
                {
                    if (testGame.hand[0][z] == 1 || testGame.hand[0][z] == 4 || testGame.hand[0][z] == 6) 
                        TreasurePre++;
                }

                //play adventurer from the last hand position
                cardEffect(adventurer, 0, 0, 0, &testGame, testGame.handCount[0]-1, 0);

                //check cards for new treasures and presence of Adventurer card
                for (int z = 0; z < testGame.handCount[0]; z++)
                {
                    if (testGame.hand[0][z] == 1 || testGame.hand[0][z] == 4 || testGame.hand[0][z] == 6)
                        TreasurePost++;
        
                    if (testGame.hand[0][z] == 7)
                    { 
                        disCardTrue = 0; 
                    }
                }

                //test that treasure difference is 2 or fewer
                if (TreasurePost-TreasurePre >= 0 && TreasurePost-TreasurePre <= 2)
                    correctTreasure = 1;

                //assert that the correctTreasure and disCard flags are set
                drewCorTreasure += asserttrue(correctTreasure, 1);
                discardCardTest += asserttrue(disCardTrue, 1);
 
                totalTests++;    
            }
        }
    }

    formatOutput(drewCorTreasure, totalTests, "DREW CORRECT TREASURE");
    formatOutput(discardCardTest, totalTests, "DISCARD ADVENTURER");

    return 0;
}

/****************************************************************************
 * * Name: assertrue
 * * Description: Per requirements a helper function that takes two ints and
 * * compares them for equality.  Defaults to returning that the test did fail,
 * * but returns false if they are equal.
 * ****************************************************************************/
int asserttrue(int x, int y)
{
    int fail = 1;

    if(x == y)
        fail = 0;

    return fail;
}

/****************************************************************************
 * * Name: formatOutput
 * * Description: Formats the output of the random cards tests for easier
 * * reading.  Receives the value of the accumulator, the total number of tests
 * * and a message.
 * ****************************************************************************/
void formatOutput (int failingTests, int totalTests, char* message)
{
    if (failingTests)
    {
        printf("%s FOUND FAILING TESTS!!\n", message);
        printf("%d PASSING TESTS, %d FAILING TESTS\n", totalTests-failingTests, failingTests);
    }
    else
        printf("%s -- ALL TESTS PASSED!!\n", message);
}

