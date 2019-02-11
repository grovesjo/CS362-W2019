/////////////////////////////////////////////////////////////////////////////////
// Name: Joshua Kevin Groves
// Date: 10 February 2019
// File: cardtest2.c
// Description: Unit test for adventurer implementation function
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

	printf ("Starting unit test for adventurer implementation\n");
	
	initializeGame(numPlayers, k, seed, &G);
	int memcmpResult;
	int i;
	int j;
	int testingPlayer = G.whoseTurn;
	G.hand[testingPlayer][0] = adventurer;
	
	// load deck
	G.deckCount[testingPlayer] = 0;
	for(i=0; i<10; i++){
		G.deck[testingPlayer][i] = estate;
		G.deckCount[testingPlayer]++;
	}
	G.deck[testingPlayer][7] = copper;
	G.deck[testingPlayer][4] = silver;
	
	//test if any changes to game state
	struct gameState preCall;
	memcpy(&preCall, &G, sizeof(struct gameState));

	cardEffect(adventurer, -1, -1, -1, &G, 0, 0);

	//test game state
	memcmpResult = memcmp(preCall.supplyCount, G.supplyCount, sizeof(int) * (treasure_map + 1));
	simpleIntTest(0, memcmpResult, "NoChangeSupplyPiles");

	//test current player
	simpleIntTest(7, G.handCount[testingPlayer], "HandCount+2");
	simpleIntTest(4, G.deckCount[testingPlayer], "RemainingDeckCount");
	simpleIntTest(4, G.discardCount[testingPlayer], "DiscardedNonTreasure");
	simpleIntTest(silver, G.hand[testingPlayer][G.handCount[testingPlayer]-1],"LastCardinHandSilver");
	simpleIntTest(copper, G.hand[testingPlayer][G.handCount[testingPlayer]-2],"NextToLastCardinHandCopper");	

	
	//test other players changes
	for(j=0; j < numPlayers; j++){
		if(j != testingPlayer){
			simpleIntTest(preCall.handCount[j], G.handCount[j], "NoChangeOPHandCount");
			memcmpResult = memcmp(preCall.hand[j], G.hand[j], sizeof(int) * G.handCount[j]);	
			simpleIntTest(0,memcmpResult,"NoChangeOPHand");

			simpleIntTest(preCall.discardCount[j], G.discardCount[j], "NoChangeOPDiscardPileCount");
			memcmpResult = memcmp(preCall.discard[j], G.discard[j], sizeof(int) * G.discardCount[j]);
			simpleIntTest(0,memcmpResult,"NoChangeOPDiscard");						

			simpleIntTest(preCall.deckCount[j], G.deckCount[j], "NoChangeOPDeckPileCount");
			memcmpResult = memcmp(preCall.deck[j], G.deck[j], sizeof(int) * G.deckCount[j]);
			simpleIntTest(0,memcmpResult,"NoChangeOPDeck");	
		}
	}
	
	G.hand[testingPlayer][0] = adventurer;
	
	// run an iteration to test gold
	// load deck
	G.deckCount[testingPlayer] = 0;
	G.handCount[testingPlayer] = 5;
	G.discardCount[testingPlayer] = 0;
	for(i=0; i<10; i++){
		G.deck[testingPlayer][i] = estate;
		G.deckCount[testingPlayer]++;
	}
	G.deck[testingPlayer][7] = silver;
	G.deck[testingPlayer][4] = gold;
	
	cardEffect(adventurer, -1, -1, -1, &G, 0, 0);

	//test current player
	simpleIntTest(7, G.handCount[testingPlayer], "HandCount+2Gold");
	simpleIntTest(4, G.deckCount[testingPlayer], "RemainingDeckCountGold");
	simpleIntTest(4, G.discardCount[testingPlayer], "DiscardedNonTreasureGold");
	simpleIntTest(gold, G.hand[testingPlayer][G.handCount[testingPlayer]-1],"LastCardinHandGold");
	simpleIntTest(silver, G.hand[testingPlayer][G.handCount[testingPlayer]-2],"NextToLastCardinHandSilver");
	
	return 0;
}