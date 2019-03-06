/****************************************************************************
* Author: Parick M. Herron
* Date: Feb 4, 2019
* Name: Cardtest1
* Description:  A unittest function for smithy card.  The unit test makes
* a few checks against the behavior of the card in that it verifies that
* we draw three new cards, we discard the Smith card, we deplete the deck
* by three cards and that we have only drawn cards that are avialable from
* our deck.
****************************************************************************/  
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

//Function prototype for custom assert method
int asserttrue(int x, int y, char* message);

int main()
{
    int i = 0;  //loop index
    int noDiscard = 0; //check for discard
    int deckDrawFalse = 0; //drew from deck count
    int failtest = 0;  //accumulator for failed tests
    int seed = 1000;   //input to initialize game
    int numPlayers = 2; 
    struct gameState baseGame, testGame;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		 sea_hag, tribute, smithy, council_room};

    int HandCountPre = -1;
    int HandCountPost = -1;
    int DeckCountPre = -1;
    int DeckCountPost = -1;

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &baseGame);

    //copy the base copy to a test copy to maintain base state
    memcpy(&testGame, &baseGame, sizeof(struct gameState));

    //uses gainCard() function to add a smithy card to the existing hand
    //the 2 as the third argument is a flag to put the card in the hand
    //the 0 as the third argument is the player number
    gainCard(smithy, &testGame, 2, 0); 

    //We check here the number of cards in the hand and deck
    //for comparison after the function has run
    HandCountPre = testGame.handCount[0];
    DeckCountPre = testGame.deckCount[0]; 

    //play smithy from the last hand position
    cardEffect(smithy, 0, 0, 0, &testGame, testGame.handCount[0]-1, 0);

    //Check new hand and deck counts
    HandCountPost = testGame.handCount[0];
    DeckCountPost = testGame.deckCount[0];

    //Since we gain +3 cards and discard one card, net change in hand should be 2
    failtest += asserttrue(HandCountPost-HandCountPre, 2, "Gained Three Cards");

    //The deck should have three fewer cards
    failtest += asserttrue(DeckCountPre-DeckCountPost, 3, "Removed Three Deck Cards");

    //Check that smithy card has been removed from hand
    for (i = 0; i < testGame.handCount[0]; i++)
        if (testGame.hand[0][i] == 13)
            noDiscard++;
   
    failtest += asserttrue(noDiscard, 0, "Removed Smithy Card");

    //check that all new cards are either copper or estate from a fresh deck
    for (i = 0; i < testGame.handCount[0]; i++)
        if ((testGame.hand[0][i] != 1) && (testGame.hand[0][i] != 4))
            deckDrawFalse++;

    failtest += asserttrue(deckDrawFalse, 0, "All Draws From Deck");

    //check accumulator state for overall test suite results
    if(failtest)
        printf("TEST SUITE FOUND FAILING TESTS!!\n");
    else
        printf("ALL TESTS PASSED!!\n");


    return 0;
}

/****************************************************************************
* Name: assertrue
* Description: Per requirements a helper function that takes two ints and
* compares them for equality.  Also receives a string to output specifically
* which test is being run
****************************************************************************/
int asserttrue(int x, int y, char* message)
{
    int fail;

    if(x == y)
    {
        printf("PASS: On Test %s\n", message);
        fail = 0;
    }
    else
    {
        printf("FAIL: On Test %s\n", message);
        fail = 1;
    }

    return fail;
}

