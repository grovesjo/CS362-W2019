/////////////////////////////////////////////////////////////////////////////////
// Name: Joshua Kevin Groves
// Date: 10 February 2019
// File: cardtest3.c
// Description: Unit test for village implementation function
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

	printf ("Starting unit test for village implementation\n");
	
	initializeGame(numPlayers, k, seed, &G);
	int memcmpResult;
	int j;
	int testingPlayer = G.whoseTurn;
	G.hand[testingPlayer][0] = village;
	
	//test if any changes to game state
	struct gameState preCall;
	memcpy(&preCall, &G, sizeof(struct gameState));

	cardEffect(village, -1, -1, -1, &G, 0, 0);

	//test game state
	memcmpResult = memcmp(preCall.supplyCount, G.supplyCount, sizeof(int) * (treasure_map + 1));
	simpleIntTest(0, memcmpResult, "NoChangeSupplyPiles");
	
	//test current player
	//hand count +1 for drawn but then -1 for discard village card
	simpleIntTest(preCall.handCount[testingPlayer], G.handCount[testingPlayer], "PostHandCount");
	simpleIntTest(preCall.deckCount[testingPlayer]-1, G.deckCount[testingPlayer], "RemainingDeckCount");
	simpleIntTest(preCall.discardCount[testingPlayer], G.discardCount[testingPlayer], "DiscardedCount");
	simpleIntTest(preCall.deck[testingPlayer][G.deckCount[testingPlayer]-1], G.hand[testingPlayer][G.handCount[testingPlayer]-1],"SameCardDrawnFromDeck");
	simpleIntTest(preCall.numActions+2, G.numActions, "+2Actions");
	
	
	//test other players changes
	for(j=0; j < numPlayers; j++){
		if(j != testingPlayer){
			//test hand
			simpleIntTest(preCall.handCount[j], G.handCount[j], "NoChangeOPHandCount");
			memcmpResult = memcmp(preCall.hand[j], G.hand[j], sizeof(int) * G.handCount[j]);	
			simpleIntTest(0,memcmpResult,"NoChangeOPHand");

			//test discard pile
			simpleIntTest(preCall.discardCount[j], G.discardCount[j], "NoChangeOPDiscardPileCount");
			memcmpResult = memcmp(preCall.discard[j], G.discard[j], sizeof(int) * G.discardCount[j]);
			simpleIntTest(0,memcmpResult,"NoChangeOPDiscard");						

			//test deck
			simpleIntTest(preCall.deckCount[j], G.deckCount[j], "NoChangeOPDeckPileCount");
			memcmpResult = memcmp(preCall.deck[j], G.deck[j], sizeof(int) * G.deckCount[j]);
			simpleIntTest(0,memcmpResult,"NoChangeOPDeck");	
		}
	}

	return 0;
}