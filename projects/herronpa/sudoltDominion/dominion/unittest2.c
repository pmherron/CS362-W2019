/****************************************************************************
* Author: Pattrick M. Herron
* Date: Feb 3, 2019
* Name: Unittest2
* Description: A unit test that verified the functionality of the 
* kingdomCards() function inside of dominion.c  The function takes in ten
* different cards and assigns them to an integer array.  The function
* should return the array with the cards in the correct order.  We verify
* hear that every card in the game when sent to the function is correctly
* assigned in the array and that the array is correct.
****************************************************************************/ 
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

    //Create a deck using kingdomCards() function for the first 10 cards

    int* testDeck = kingdomCards(curse, estate, duchy, province, copper, silver,
                 gold, adventurer, council_room, feast);

    failtest += asserttrue(testDeck[0], 0, "Curse Card");
    failtest += asserttrue(testDeck[1], 1, "Estate Card");
    failtest += asserttrue(testDeck[2], 2, "Duchy Card");
    failtest += asserttrue(testDeck[3], 3, "Province Card");
    failtest += asserttrue(testDeck[4], 4, "Copper Card");
    failtest += asserttrue(testDeck[5], 5, "Silver Card");
    failtest += asserttrue(testDeck[6], 6, "Gold Card");
    failtest += asserttrue(testDeck[7], 7, "Adventurer Card");
    failtest += asserttrue(testDeck[8], 8, "Council Room Card");
    failtest += asserttrue(testDeck[9], 9, "Feast Card");


    //Create a deck using kingdomCards() function for the next 10 cards
    
    testDeck = kingdomCards(gardens, mine, remodel, smithy, village, baron,
                 great_hall, minion, steward, tribute);

    failtest += asserttrue(testDeck[0], 10, "Gardens Card");
    failtest += asserttrue(testDeck[1], 11, "Mine Card");
    failtest += asserttrue(testDeck[2], 12, "Remodel Card");
    failtest += asserttrue(testDeck[3], 13, "Smithy Card");
    failtest += asserttrue(testDeck[4], 14, "Village Card");
    failtest += asserttrue(testDeck[5], 15, "Baron Card");
    failtest += asserttrue(testDeck[6], 16, "Great Hall Card");
    failtest += asserttrue(testDeck[7], 17, "Minion Card");
    failtest += asserttrue(testDeck[8], 18, "Steward Card");
    failtest += asserttrue(testDeck[9], 19, "Tribute Card");

    //Create a deck using kingdomCards() function for the remaining 7 cards
    //Also adds three cards randomly as 10 cards are required for a deck

    testDeck = kingdomCards(ambassador, cutpurse, embargo, outpost, salvager, sea_hag,
                 treasure_map, curse, gardens, baron);

    failtest += asserttrue(testDeck[0], 20, "Ambassador Card");
    failtest += asserttrue(testDeck[1], 21, "Cutpurse Card");
    failtest += asserttrue(testDeck[2], 22, "Embargo Card");
    failtest += asserttrue(testDeck[3], 23, "Outpost Card");
    failtest += asserttrue(testDeck[4], 24, "Salvager Card");
    failtest += asserttrue(testDeck[5], 25, "Sea Hag Card");
    failtest += asserttrue(testDeck[6], 26, "Treasure Map Card");
    failtest += asserttrue(testDeck[7], 0, "Curse Card (Again)");
    failtest += asserttrue(testDeck[8], 10, "Gardens Card (Again)");
    failtest += asserttrue(testDeck[9], 15, "Baron Card (Again)");

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

