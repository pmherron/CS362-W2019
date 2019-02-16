/****************************************************************************
* Author: Parick M. Herron
* Date: Feb 14, 2019
* Name: Randomcardtest1
* Description:  A random test generator for smithy card.  The random tests
* makes a few checks against the behavior of the card in that it verifies that
* we draw three new cards, we discard the Smith card, we deplete the deck
* by three cards and that we have only drawn cards that are avialable from
* our deck.  We randomize the number of players and the seed of the game
* initialization.
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
    int noDiscard = 0; //check for discard
    int deckDrawFalse = 0; //drew from deck count
    int gainCardTest = 0;  //accumulator for checking gained card tests
    int deckDrawTest = 0; //accumulator for checking discarded card tests
    int discardSmithTest = 0; //accumulator for checking smith is discarded
    int drewFromDeckTest = 0; //accumlator for drawing from deck 
    int totalTests = 0; //total random tests run 
    struct gameState baseGame, testGame;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		 sea_hag, tribute, smithy, council_room};

    //set hand and deck variables for pre and post card checking
    int HandCountPre = -1;
    int HandCountPost = -1;
    int DeckCountPre = -1;
    int DeckCountPost = -1;

    //change the seed of the initialization
    for (int i = 1; i <= 1000; i++)
    {
        //vary the number of players from 2 to 4
        for(int j = 2; j <=4; j++)
        {
            // initialize a game state and player cards
            initializeGame(j, k, i, &baseGame);

            //copy the base copy to a test copy to maintain base state
            memcpy(&testGame, &baseGame, sizeof(struct gameState));

            //uses gainCard() function to add a smithy card to the existing hand
            //the 2 as the third argument is a flag to put the card in the hand
            //the 0 as the third argument is the player number
            gainCard(smithy, &testGame, 2, 0); 

            //We check here the number of cards in the hand and deck
            //for comparison after the function has run
            HandCountPre = testGame.handCount[0];
            DeckCountPre = testGame.handCount[0]; 

            //play smithy from the last hand position
            cardEffect(smithy, 0, 0, 0, &testGame, testGame.handCount[0]-1, 0);

            //Check new hand and deck counts
            HandCountPost = testGame.handCount[0];
            DeckCountPost = testGame.handCount[0];

            //Since we gain +3 cards and discard one card, net change in hand should be 2
            gainCardTest += asserttrue(HandCountPost-HandCountPre, 2);

            //The deck should have three fewer cards
            deckDrawTest += asserttrue(DeckCountPost-DeckCountPre, 3);

            //Check that smithy card has been removed from hand
            for (int a = 0; a < testGame.handCount[0]; a++)
                if (testGame.hand[0][a] == 13)
                    noDiscard++;
   
            discardSmithTest += asserttrue(noDiscard, 0);

            //check that all new cards are either copper or estate from a fresh deck
            for (int a = 0; a < testGame.handCount[0]; a++)
                if ((testGame.hand[0][a] != 1) && (testGame.hand[0][a] != 4))
                    deckDrawFalse++;

            drewFromDeckTest += asserttrue(deckDrawFalse, 0);

            totalTests++;
         }

      }
        //check accumulator state for overall test suite results
        formatOutput(gainCardTest, totalTests, "GAINED THREE CARDS");
        formatOutput(deckDrawTest, totalTests, "DECK LOST THREE CARDS");
        formatOutput(discardSmithTest, totalTests, "SMITH CARD REMOVED");
        formatOutput(drewFromDeckTest, totalTests, "CARDS CAME FROM DECK");

     
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



