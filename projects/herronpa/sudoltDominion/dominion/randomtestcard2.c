/****************************************************************************
* Author: Parick M. Herron
* Date: Feb 14, 2019
* Name: randomtestcard2
* Description:  A random test generator for Village card.  The Village card
* allows the player to draw a card, increases their action count by two and
* then discard the Village card.  We check all of these functions below. We
* create randomness in the initialization value, the number of players and
* the number of starting actions that the player has prior to playing the
* Village card.
****************************************************************************/  
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

//Function prototype for custom assert method
int asserttrue(int, int);
void formatOutput(int, int, char*);

int main()
{
    int deckDrawFalse = 1; //drew from deck count
    int handCountTest = 0; //accumulator for drawing cards
    int actCountTest = 0; //accumulator for action test
    int drewFromDeckTest = 0; //accumulator for drawing from deck 
    int totalTests = 0; //total random tests run
    struct gameState baseGame, testGame;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		 sea_hag, tribute, smithy, council_room};

    //set up variables for storing hand and action counts
    int HandCountPre = -1;
    int HandCountPost = -10;
    int ActCountPre = -1;
    int ActCountPost = -10;

    
    //Varies the seed for initialization of the game
    for (int i = 1; i <= 1000; i++)
    {
        //Varies the number of players from two to four
        for (int j = 2; j <= 4; j++)
        { 
            //varies the starting actions of the player from zero to ten
            //this is well beyond the realistic range for the game
            for (int y = 0; y <= 10; y++)
            {
            // initialize a game state and player cards and copy it
            initializeGame(j, k, i, &baseGame);
            memcpy(&testGame, &baseGame, sizeof(struct gameState));

            //uses gainCard() function to add a village card to the existing hand
            //the 2 as the third argument is a flag to put the card in the hand
            //the 0 as the third argument is the player number
            gainCard(village, &testGame, 2, 0); 

            //Estblish starting hand count and actions
            HandCountPre = testGame.handCount[0];
            testGame.numActions = y;
            ActCountPre = testGame.numActions; 

            //play village from the last hand position
            cardEffect(village, 0, 0, 0, &testGame, testGame.handCount[0]-1, 0);

            //Check new hand, deck and action counts
            HandCountPost = testGame.handCount[0];
            ActCountPost = testGame.numActions;

            if (testGame.hand[0][testGame.handCount[0]-1] != 7)
                deckDrawFalse = 0; 

             handCountTest += asserttrue(HandCountPost-HandCountPre, 0);

             //The player should have two additional actions
             actCountTest += asserttrue(ActCountPost-ActCountPre, 2);

             //check that Village card is no longer in hand
             drewFromDeckTest += asserttrue(deckDrawFalse, 0);
  
             totalTests++;
            }
        }
    }

    formatOutput(handCountTest, totalTests, "DRAW/DISCARD");
    formatOutput(actCountTest, totalTests, "INCREASE ACTIONS");
    formatOutput(drewFromDeckTest, totalTests, "DREW FROM DECK");
  
    return 0;
}

/****************************************************************************
* Name: assertrue
* Description: Per requirements a helper function that takes two ints and
* compares them for equality.  Defaults to returning that the test did fail,
* but returns false if they are equal.
****************************************************************************/
int asserttrue(int x, int y)
{
    int fail = 1;

    if(x == y)
        fail = 0;

    return fail;
}

/****************************************************************************
* Name: formatOutput
* Description: Formats the output of the random cards tests for easier
* reading.  Receives the value of the accumulator, the total number of tests
* and a message.
****************************************************************************/
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

