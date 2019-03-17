/////////////////////////////////////////////////////////////////////////////////
// Name: Joshua Kevin Groves
// Date: 10 February 2019
// File: unittest4.c
// Description: Unit test for isGameOver() function
/////////////////////////////////////////////////////////////////////////////////

#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <string.h>
#include "dominion_helpers.h"

int simpleIntTest(int aData, int bData, const char* testName){
	int result = 0;
	if(aData==bData){
		result = 1;		
		printf("%s: passed\n", testName);
	}
	else
		printf("%s: FAILED; Expected: %d; Actual: %d\n", testName, aData, bData);			
	return result;
}

int main (int argc, char** argv) {
	int seed = 20;
	int numPlayers = 2;
	struct gameState G;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy};

	printf ("Starting unit test for is game over function\n");
	
	initializeGame(numPlayers, k, seed, &G);
	int memcmpResult;
	int i;
	int gameOver;
	
	//test if any changes to game state
	struct gameState preCall;
	memcpy(&preCall, &G, sizeof(struct gameState));
	gameOver = isGameOver(&G);
	memcmpResult = memcmp(&preCall, &G, sizeof(struct gameState));
	simpleIntTest(0, memcmpResult, "NoGameStateChanges");
	
	//only estates depleted
	G.supplyCount[estate] = 0;
	gameOver = isGameOver(&G);
	simpleIntTest(0, gameOver, "NoEstatesElseFull");
	
	G.supplyCount[estate] = 20;
	G.supplyCount[province] = 0;
	gameOver = isGameOver(&G);
	simpleIntTest(1, gameOver, "NoProvinces");
	
	G.supplyCount[province] = 20;
	G.supplyCount[smithy] = 0;
	G.supplyCount[adventurer] = 0;	
	gameOver = isGameOver(&G);
	simpleIntTest(0, gameOver, "2Depleted");
	
	G.supplyCount[province] = 0;
	G.supplyCount[smithy] = 0;
	G.supplyCount[adventurer] = 20;	
	gameOver = isGameOver(&G);
	simpleIntTest(1, gameOver, "provinceandsmithydepleted");

	G.supplyCount[province] = 20;
	G.supplyCount[smithy] = 0;
	G.supplyCount[adventurer] = 0;
	G.supplyCount[minion] = 0;	
	gameOver = isGameOver(&G);
	simpleIntTest(1, gameOver, "3depleted");	
	
	for(i=0; i<25; i++){
		G.supplyCount[i] = 0;
	}
	gameOver = isGameOver(&G);
	simpleIntTest(1, gameOver, "Alldepleted");
	
	
	
	
	
	return 0;
}
	
	