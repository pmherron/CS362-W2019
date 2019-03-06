/****************************************************************************
* Author: Parick M. Herron
* Date: Feb 2, 2019
* Name: Unittest1
* Description:  A unittest function for the isGameOver() function inside of
* the dominion.c code.  Here we set up a fake game and initialize it with
* a deck and 2 players.  We then maninuplate the supply count of the 
* province cards specifically as well as the other supply cards to see
* whether the game accurately detects a game over state.
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

    //check the initialized game before and after isGameOver is run
    failtest += asserttrue(isGameOver(&testGame), 0, "Base Game");
    failtest += asserttrue(memcmp(&testGame, &baseGame, sizeof(struct gameState)), 0, "Base Game After Check"); 
   
    //empty province pile and check that game is over
    testGame.supplyCount[province] = 0;
    failtest += asserttrue(isGameOver(&testGame), 1, "Zero Province");

    //boundary condition of one province card remaining
    testGame.supplyCount[province] = 1;
    failtest += asserttrue(isGameOver(&testGame), 0, "One Province");

    //boundary condition of negative province cards
    testGame.supplyCount[province] = -1;
    failtest += asserttrue(isGameOver(&testGame), 1, "Negative Provinces");

    //return province supply to full and deplete two other supply piles
    testGame.supplyCount[province] = 12;
    testGame.supplyCount[0] = 0;
    testGame.supplyCount[1] = 0;
    failtest += asserttrue(isGameOver(&testGame), 0, "Two Empty Supply Piles");

    //deplete a third supply pile
    testGame.supplyCount[11] = 0;
    failtest += asserttrue(isGameOver(&testGame), 1, "Three Empty Supply Piles");

    //deplete all supply piles
    for (i=0; i < 25; i++)
        testGame.supplyCount[i] = 0;
    failtest += asserttrue(isGameOver(&testGame), 1, "All Supply Piles Empty");

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

