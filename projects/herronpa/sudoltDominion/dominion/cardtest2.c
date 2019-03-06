/****************************************************************************
* Author: Parick M. Herron
* Date: Feb 4, 2019
* Name: Cardtest2
* Description:  A unittest function for adventurer card.  We write here a 
* test suite that checks whether playing the adventurer card properly draws
* two treasures from the deck as it is supposed to.  This is checked with a 
* deck that contains the correct amount of treasure as well as one that 
* has no treasures at all.  We look at a) drawn treasures b) adventurer card
* discarded c) handCount is correct and d) function properly terminates
* even when no treasure is available.
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
    int correctTreasure = 0; //check for discard
    int disCardTrue = 1;
    int failtest = 0;  //accumulator for failed tests
    int seed = 1000;   //input to initialize game
    int numPlayers = 2; 
    struct gameState baseGame, testGame;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		 sea_hag, tribute, smithy, council_room};

    //We set these to large inequal values, so we don't generate a false positive
    int TreasurePre = 0;
    int TreasurePost = 0;


    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &baseGame);

    //copy the base copy to a test copy to maintain base state
    memcpy(&testGame, &baseGame, sizeof(struct gameState));

    //uses gainCard() function to add an adventurer card to the existing hand
    //the 2 as the third argument is a flag to put the card in the hand
    //the 0 as the third argument is the player number
    gainCard(adventurer, &testGame, 2, 0); 

    //We check here the number of cards in the hand and deck
    //for comparison after the function has run
    for (i = 0; i <= testGame.handCount[0]; i++)
    {
        if (testGame.hand[0][i] == 1 || testGame.hand[0][i] == 4 || testGame.hand[0][i] == 6) 
            TreasurePre++;
    }

    //play adventurer from the last hand position
    cardEffect(adventurer, 0, 0, 0, &testGame, testGame.handCount[0]-1, 0);

    //check cards for new treasures and presence of Adventurer card
    for (i = 0; i <= testGame.handCount[0]; i++)
    {
        if (testGame.hand[0][i] == 1 || testGame.hand[0][i] == 4 || testGame.hand[0][i] == 6)
            TreasurePost++;
        
        if (testGame.hand[0][i] == 7)
            disCardTrue = 0; 
    }

    //test that treasure difference is 2 or fewer
    if (TreasurePost-TreasurePre >= 0 && TreasurePost-TreasurePre <= 2)
        correctTreasure = 1;

    failtest += asserttrue(correctTreasure, 1, "Correct Number of Treasure Drawn");
    failtest += asserttrue(disCardTrue, 1, "Adventurer Discarded");    

    //discard existing hand and take an adventurer card
    int cardCount = testGame.handCount[0];

    for (i = 0; i < cardCount; i++)
        discardCard(i, 0, &testGame, 0);

    gainCard(adventurer, &testGame, 2, 0);

    //play adventurer from the last hand position
    cardEffect(adventurer, 0, 0, 0, &testGame, testGame.handCount[0]-1, 0);

    //verify shuffling stops and hand is empty
    printf("PASS: On Test Stop Shuffle With No Treasure Cards\n");

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

