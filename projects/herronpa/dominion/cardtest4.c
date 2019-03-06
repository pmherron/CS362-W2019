/****************************************************************************
* Author: Parick M. Herron
* Date: Feb 4, 2019
* Name: Cardtest2
* Description:  A unittest function for Great Hall card.  The Great Hall card
* allows the player to draw a card, increase their action count by one and
* then discard the Great Hall card.  We check all of these functions below.
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
    int deckDrawFalse = 1; //drew from deck count
    int failtest = 0;  //accumulator for failed tests
    int seed = 1000;   //input to initialize game
    int numPlayers = 2; 
    struct gameState baseGame, testGame;
    int k[10] = {adventurer, embargo, great_hall, minion, mine, cutpurse,
		 sea_hag, tribute, smithy, council_room};

    int HandCountPre = -1;
    int HandCountPost = -1;
    int ActCountPre = -1;
    int ActCountPost = -1;

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &baseGame);

    //copy the base copy to a test copy to maintain base state
    memcpy(&testGame, &baseGame, sizeof(struct gameState));

    //uses gainCard() function to add a smithy card to the existing hand
    //the 2 as the third argument is a flag to put the card in the hand
    //the 0 as the third argument is the player number
    gainCard(great_hall, &testGame, 2, 0); 

    //We check here the number of cards in the hand and deck
    //for comparison after the function has run
    HandCountPre = testGame.handCount[0];
    ActCountPre = testGame.numActions; 

    //play Great Hall from the last hand position
    cardEffect(great_hall, 0, 0, 0, &testGame, testGame.handCount[0]-1, 0);

    //Check new hand and deck counts
    HandCountPost = testGame.handCount[0];
    ActCountPost = testGame.numActions;

    if (testGame.hand[0][testGame.handCount[0]-1] != 16)
        deckDrawFalse = 0; 

    //Since we gain +1 card and discard one card, net change in hand should be zero.
    failtest += asserttrue(HandCountPost-HandCountPre, 0, "Net Zero Card Change");

    //The action count should be increased by one.
    failtest += asserttrue(ActCountPost-ActCountPre, 1, "Gained One Action");

    //The Great Hall card should no longer be in the player's hand
    failtest += asserttrue(deckDrawFalse, 0, "Discarded Great Hall Card");

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

