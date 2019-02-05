/****************************************************************************
* Author: Pattrick M. Herron
* Date: Feb 3, 2019
* Name: Unittest3
* Description: This unit test is designed to check the whoseTurn() function
* which is a getter function that returns the value of the integer 
* whoseTurn, a member of the gameState function.  As there are no bounds on
* the return value, we simply check that the value as set is what the 
* function returns.  Additionally, we add a memory compare function to make
* sure no other aspect of gameState is altered by the whoseTurn() function.
*****************************************************************************/ 
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

//Function Prototype for Assert method
int asserttrue(int x, int y, char* message);

int main()
{
    int failtest = 0;  //accumulator for failed tests
    int seed = 1000;   //input to initialize game
    int numPlayers = 2;
    struct gameState baseGame, testGame;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &baseGame);

    //copy the base copy to a test copy to maintain base state
    memcpy(&testGame, &baseGame, sizeof(struct gameState));

    //set whoseTurn to positive integer
    testGame.whoseTurn = 2;
    failtest += asserttrue(whoseTurn(&testGame), 2, "Positive Player Turn");

    //return whoseTurn to zero
    testGame.whoseTurn = 0;
    failtest += asserttrue(whoseTurn(&testGame), 0, "Zero Player Turn");

    //compare baseGame and testGame which should be the same
    //assuming whoseTurn() does not modify gameState
    failtest += asserttrue(memcmp(&testGame, &baseGame, sizeof(struct gameState)), 0, "No GameState Mods");

    testGame.whoseTurn = -2;
    failtest += asserttrue(whoseTurn(&testGame), -2, "Negative Player Turn");

    //overall test suite message

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

