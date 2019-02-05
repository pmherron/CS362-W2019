/****************************************************************************
* Author: Pattrick M. Herron
* Date: Feb 3, 2019
* Name: Unittest4
* Description: A unit test that verifies the functionality of the getCost()
* function.  It checks the cost of the card in the official Dominion rules
* versus the value returned by the function to make sure that all cars are
* appropriately costed.
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

    //Each unit test makes an assertion that the cost of the card
    //returned by the function
    failtest += asserttrue(getCost(curse), 0, "Curse Cost");
    failtest += asserttrue(getCost(estate), 2, "Estate Cost");
    failtest += asserttrue(getCost(duchy), 5, "Duchy Cost");
    failtest += asserttrue(getCost(province), 8, "Province Cost");
    failtest += asserttrue(getCost(copper), 0, "Copper Cost");
    failtest += asserttrue(getCost(silver), 3, "Silver Cost");
    failtest += asserttrue(getCost(gold), 6, "Gold Cost");
    failtest += asserttrue(getCost(adventurer), 6, "Adventurer Cost");
    failtest += asserttrue(getCost(council_room), 5, "Council Cost");
    failtest += asserttrue(getCost(feast), 4, "Feast Cost");
    failtest += asserttrue(getCost(gardens), 4, "Gardens Cost");
    failtest += asserttrue(getCost(mine), 5, "Mine Cost");
    failtest += asserttrue(getCost(remodel), 4, "Remodel Cost");
    failtest += asserttrue(getCost(smithy), 4, "Smithy Cost");
    failtest += asserttrue(getCost(village), 3, "Village Cost");
    failtest += asserttrue(getCost(baron), 4, "Baron Cost");
    failtest += asserttrue(getCost(great_hall), 3, "Great Hall Cost");
    failtest += asserttrue(getCost(minion), 5, "Minion Cost");
    failtest += asserttrue(getCost(steward), 3, "Steward Cost");
    failtest += asserttrue(getCost(tribute), 5, "Curse Cost");
    failtest += asserttrue(getCost(ambassador), 3, "Ambassador Cost");
    failtest += asserttrue(getCost(cutpurse), 4, "Cutpurse Cost");
    failtest += asserttrue(getCost(embargo), 2, "Embargo Cost");
    failtest += asserttrue(getCost(outpost), 5, "Outpost Cost");
    failtest += asserttrue(getCost(salvager), 4, "Salvager Cost");
    failtest += asserttrue(getCost(sea_hag), 4, "Sea Hag Cost");
    failtest += asserttrue(getCost(treasure_map), 4, "Treasure Map Cost");

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

