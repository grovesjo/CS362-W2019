/////////////////////////////////////////////////////////////////////////////////
// Name: Joshua Kevin Groves
// Date: 10 February 2019
// File: unittest1.c
// Description: Unit test for discardCard() function
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

	printf ("Starting unit test for discard card function\n");
	
	initializeGame(numPlayers, k, seed, &G);
	int memcmpResult;
	// both players draw cards
	int i;
	int j;
	int cardstoDraw = 5;
	for(i = 0; i < cardstoDraw; i++){
		for(j=0; j < numPlayers; j++){
			drawCard(j, &G);
		}
	}

	int testingPlayer = 0;
	
	for(i=0; i<cardstoDraw +1; i++){
		printf("Beginning iteration %d\n", i);
		// make copy of gamestate before call
		struct gameState preCall;
		memcpy(&preCall, &G, sizeof(struct gameState));
	
		discardCard(0, testingPlayer, &G, 0);

		//test game state
		memcmpResult = memcmp(preCall.supplyCount, G.supplyCount, sizeof(int) * (treasure_map + 1));
		simpleIntTest(0, memcmpResult, "NoChangeSupplyPiles");
		simpleIntTest(preCall.playedCardCount +1, G.playedCardCount, "PlayedCardCountIncremented");
	
		//test current player changes
		simpleIntTest(preCall.handCount[testingPlayer]-1, G.handCount[testingPlayer], "CurPlayerHandDecrement");
		simpleIntTest(preCall.discardCount[testingPlayer], G.discardCount[testingPlayer], "NoChangeDiscardPileCount");
		simpleIntTest(preCall.deckCount[testingPlayer], G.deckCount[testingPlayer], "NoChangeDeckPileCount");
		
		//test other players changes
		for(j=0; j < numPlayers; j++){
			if(j != testingPlayer){
				simpleIntTest(preCall.handCount[j], G.handCount[j], "NoChangeOPHandCount");
				memcmpResult = memcmp(preCall.hand[j], G.hand[j], sizeof(int) * G.handCount[j]);	
				simpleIntTest(0,memcmpResult,"NoChangeOPHand");
				simpleIntTest(preCall.discardCount[j], G.discardCount[j], "NoChangeOPDiscardPileCount");
				simpleIntTest(preCall.deckCount[j], G.deckCount[j], "NoChangeOPDeckPileCount");
			}
		}

		printf("-----------------\n");
	}
		
	for(i = 0; i < cardstoDraw; i++){
			drawCard(testingPlayer, &G);
	}
	
	printf("Testing removing medial position\n");
	// make copy of gamestate before call
	struct gameState preCall2;
	memcpy(&preCall2, &G, sizeof(struct gameState));
	
	discardCard(G.handCount[testingPlayer]/2, testingPlayer, &G, 0);

	//test game state
	memcmpResult = memcmp(preCall2.supplyCount, G.supplyCount, sizeof(int) * (treasure_map + 1));
	simpleIntTest(0, memcmpResult, "NoChangeSupplyPiles");
	simpleIntTest(preCall2.playedCardCount +1, G.playedCardCount, "PlayedCardCountIncremented");
	
	//test current player changes
	simpleIntTest(preCall2.handCount[testingPlayer]-1, G.handCount[testingPlayer], "CurPlayerHandDecrement");
	simpleIntTest(preCall2.discardCount[testingPlayer], G.discardCount[testingPlayer], "NoChangeDiscardPileCount");
	simpleIntTest(preCall2.deckCount[testingPlayer], G.deckCount[testingPlayer], "NoChangeDeckPileCount");
	
	//test other players changes
	for(j=0; j < numPlayers; j++){
		if(j != testingPlayer){
			simpleIntTest(preCall2.handCount[j], G.handCount[j], "NoChangeOPHandCount");
			memcmpResult = memcmp(preCall2.hand[j], G.hand[j], sizeof(int) * G.handCount[j]);	
			simpleIntTest(0,memcmpResult,"NoChangeOPHand");
			simpleIntTest(preCall2.discardCount[j], G.discardCount[j], "NoChangeOPDiscardPileCount");
			simpleIntTest(preCall2.deckCount[j], G.deckCount[j], "NoChangeOPDeckPileCount");
		}
	}

	printf("-----------------\n");
	
	
	printf("Testing removing terminal position\n");
	// make copy of gamestate before call
	struct gameState preCall3;
	memcpy(&preCall3, &G, sizeof(struct gameState));
	
	discardCard(G.handCount[testingPlayer]-1, testingPlayer, &G, 0);
	
	//test game state
	memcmpResult = memcmp(preCall3.supplyCount, G.supplyCount, sizeof(int) * (treasure_map + 1));
	simpleIntTest(0, memcmpResult, "NoChangeSupplyPiles");
	simpleIntTest(preCall3.playedCardCount +1, G.playedCardCount, "PlayedCardCountIncremented");
	
	//test current player changes
	simpleIntTest(preCall3.handCount[testingPlayer]-1, G.handCount[testingPlayer], "CurPlayerHandDecrement");
	simpleIntTest(preCall3.discardCount[testingPlayer], G.discardCount[testingPlayer], "NoChangeDiscardPileCount");
	simpleIntTest(preCall3.deckCount[testingPlayer], G.deckCount[testingPlayer], "NoChangeDeckPileCount");
	
	//test other players changes
	for(j=0; j < numPlayers; j++){
		if(j != testingPlayer){
			simpleIntTest(preCall3.handCount[j], G.handCount[j], "NoChangeOPHandCount");
			memcmpResult = memcmp(preCall3.hand[j], G.hand[j], sizeof(int) * G.handCount[j]);	
			simpleIntTest(0,memcmpResult,"NoChangeOPHand");
			simpleIntTest(preCall3.discardCount[j], G.discardCount[j], "NoChangeOPDiscardPileCount");
			simpleIntTest(preCall3.deckCount[j], G.deckCount[j], "NoChangeOPDeckPileCount");
		}
	}

	printf("-----------------\n");
	
	printf("Testing Trash Flag\n");
	// make copy of gamestate before call
	struct gameState preCall4;
	memcpy(&preCall4, &G, sizeof(struct gameState));
	
	discardCard(G.handCount[testingPlayer]-1, testingPlayer, &G, 1);
	
	//test game state
	memcmpResult = memcmp(preCall4.supplyCount, G.supplyCount, sizeof(int) * (treasure_map + 1));
	simpleIntTest(0, memcmpResult, "NoChangeSupplyPiles");
	simpleIntTest(preCall4.playedCardCount, G.playedCardCount, "PlayedCardCountNotIncremented");
	memcmpResult = memcmp(preCall4.playedCards, G.playedCards, sizeof(int) * G.playedCardCount);
	simpleIntTest(0, memcmpResult, "NoChangePlayedCardsArray");
	
	//test current player changes
	simpleIntTest(preCall4.handCount[testingPlayer]-1, G.handCount[testingPlayer], "CurPlayerHandDecrement");
	simpleIntTest(preCall4.discardCount[testingPlayer], G.discardCount[testingPlayer], "NoChangeDiscardPileCount");
	simpleIntTest(preCall4.deckCount[testingPlayer], G.deckCount[testingPlayer], "NoChangeDeckPileCount");
	
	//test other players changes
	for(j=0; j < numPlayers; j++){
		if(j != testingPlayer){
			simpleIntTest(preCall4.handCount[j], G.handCount[j], "NoChangeOPHandCount");
			memcmpResult = memcmp(preCall4.hand[j], G.hand[j], sizeof(int) * G.handCount[j]);	
			simpleIntTest(0,memcmpResult,"NoChangeOPHand");
			simpleIntTest(preCall4.discardCount[j], G.discardCount[j], "NoChangeOPDiscardPileCount");
			simpleIntTest(preCall4.deckCount[j], G.deckCount[j], "NoChangeOPDeckPileCount");
		}
	}

	printf("-----------------\n");
	
	
	return 0;
}
