/////////////////////////////////////////////////////////////////////////////////
// Name: Joshua Kevin Groves
// Date: 10 February 2019
// File: unittest2.c
// Description: Unit test for updateCoins() function
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

	printf ("Starting unit test for update coins function\n");
	
	initializeGame(numPlayers, k, seed, &G);
	int memcmpResult;
	
	int cardsinHand = 5;
	int i;
	int j;
	for(i=0; i<cardsinHand; i++){
		G.hand[G.whoseTurn][i] = smithy;
		G.handCount[G.whoseTurn]++;
	}
	
	struct gameState preCall;
	memcpy(&preCall, &G, sizeof(struct gameState));

	updateCoins(G.whoseTurn, &G, 0);
	
	//test game state changes
	memcmpResult = memcmp(preCall.supplyCount, G.supplyCount, sizeof(int) * (treasure_map + 1));
	simpleIntTest(0, memcmpResult, "NoChangeSupplyPiles");
	
	
	//test players changes
	for(j=0; j < numPlayers; j++){
		simpleIntTest(preCall.handCount[j], G.handCount[j], "NoChangePHandCount");
		memcmpResult = memcmp(preCall.hand[j], G.hand[j], sizeof(int) * G.handCount[j]);	
		simpleIntTest(0,memcmpResult,"NoChangePHand");
		simpleIntTest(preCall.discardCount[j], G.discardCount[j], "NoChangePDiscardPileCount");
		simpleIntTest(preCall.deckCount[j], G.deckCount[j], "NoChangePDeckPileCount");
	}
	
	//test no treasure in hand
	simpleIntTest(0, G.coins, "NoTreasureTest");
	
	// no coins in hand but + bonus
	updateCoins(G.whoseTurn, &G, 1);
	simpleIntTest(1, G.coins, "NoTreasureinHand+1bonus");
	
	//all one currency type
	for(i=0; i<cardsinHand; i++)
		G.hand[G.whoseTurn][i] = copper;
	updateCoins(G.whoseTurn, &G, 0);
	simpleIntTest(cardsinHand, G.coins, "AllCopper");
	
	for(i=0; i<cardsinHand; i++)
		G.hand[G.whoseTurn][i] = silver;
	updateCoins(G.whoseTurn, &G, 0);
	simpleIntTest(cardsinHand*2, G.coins, "AllSilver");	
	
	for(i=0; i<cardsinHand; i++)
		G.hand[G.whoseTurn][i] = gold;
	updateCoins(G.whoseTurn, &G, 0);
	simpleIntTest(cardsinHand*3, G.coins, "AllGold");	
	
	//mixed currency
	G.hand[G.whoseTurn][0] = copper;
	G.hand[G.whoseTurn][1] = silver;
	G.hand[G.whoseTurn][2] = silver;
	//other two hand positions are already gold
	updateCoins(G.whoseTurn, &G, 0);
	simpleIntTest(11, G.coins, "Mixed-2G2S1C");	

	//mixed with bonus
	updateCoins(G.whoseTurn, &G, 1);
	simpleIntTest(12, G.coins, "Mixed-2G2S1C+1Bonus");

	//mixed with negative bonus
	updateCoins(G.whoseTurn, &G, -1);	
	simpleIntTest(10, G.coins, "Mixed-2G2S1C-1Bonus");	
	
	return 0;
}	