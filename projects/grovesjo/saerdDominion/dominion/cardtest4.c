/////////////////////////////////////////////////////////////////////////////////
// Name: Joshua Kevin Groves
// Date: 10 February 2019
// File: cardtest4.c
// Description: Unit test for remodel implementation function
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
	int k[10] = {adventurer, gardens, remodel, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy};

	printf ("Starting unit test for remodel implementation\n");
	
	initializeGame(numPlayers, k, seed, &G);
	int memcmpResult;
	int i;
	int j;
	int remodelResult;
	int testingPlayer = G.whoseTurn;
	int gainingCard = smithy;
	int trashingCard = estate;
	G.hand[testingPlayer][0] = remodel;
	G.hand[testingPlayer][1] = trashingCard;
	
	printf ("Testing appropriate user choices\n");
	
	//test if any changes to game state
	struct gameState preCall;
	memcpy(&preCall, &G, sizeof(struct gameState));

	remodelResult = cardEffect(remodel, 1, gainingCard, -1, &G, 0, 0);
	simpleIntTest(0, remodelResult, "cardEffectReturn");
	
	//test game state
	int changedSupplies = 0;
	for(i=0; i<26; i++){
		if(preCall.supplyCount[i] != G.supplyCount[i])
			changedSupplies++;
	}
	simpleIntTest(1, changedSupplies, "Only1SupplyChanged");
	simpleIntTest(preCall.supplyCount[gainingCard]-1,G.supplyCount[gainingCard],"AppropriateSupplyDecremented1");
	
	
	//test current player
	simpleIntTest(preCall.deckCount[testingPlayer], G.deckCount[testingPlayer], "NoChangePlayerDeckCount");
	simpleIntTest(preCall.handCount[testingPlayer]-2, G.handCount[testingPlayer], "PlayerHandCount");
	simpleIntTest(preCall.discardCount[testingPlayer]+1, G.discardCount[testingPlayer], "PlayerDiscardCount");
	simpleIntTest(gainingCard, G.discard[testingPlayer][G.discardCount[testingPlayer]-1], "ConfirmedGainedCard");
	
	
	
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

	printf ("----------------------------------\n");
	printf ("Testing appropriate, but unlikely user choices\n");	
	
	gainingCard = copper;
	trashingCard = gold;
	G.handCount[testingPlayer] = 5;
	G.hand[testingPlayer][0] = remodel;
	G.hand[testingPlayer][1] = trashingCard;
	
	
	//test if any changes to game state
	struct gameState preCall1;
	memcpy(&preCall1, &G, sizeof(struct gameState));

	remodelResult = cardEffect(remodel, 1, gainingCard, -1, &G, 0, 0);
	simpleIntTest(0, remodelResult, "cardEffectReturn");
	
	//test game state
	changedSupplies = 0;
	for(i=0; i<26; i++){
		if(preCall1.supplyCount[i] != G.supplyCount[i])
			changedSupplies++;
	}
	simpleIntTest(1, changedSupplies, "Only1SupplyChanged");
	simpleIntTest(preCall1.supplyCount[gainingCard]-1,G.supplyCount[gainingCard],"AppropriateSupplyDecremented1");
	
	
	//test current player
	simpleIntTest(preCall1.deckCount[testingPlayer], G.deckCount[testingPlayer], "NoChangePlayerDeckCount");
	simpleIntTest(preCall1.handCount[testingPlayer]-2, G.handCount[testingPlayer], "PlayerHandCount");
	simpleIntTest(preCall1.discardCount[testingPlayer]+1, G.discardCount[testingPlayer], "PlayerDiscardCount");
	simpleIntTest(gainingCard, G.discard[testingPlayer][G.discardCount[testingPlayer]-1], "ConfirmedGainedCard");	
	
	
	
	printf ("----------------------------------\n");
	printf ("Testing inappropriate user choices\n");

	gainingCard = smithy;
	trashingCard = copper;
	G.handCount[testingPlayer] = 5;
	G.hand[testingPlayer][0] = remodel;
	G.hand[testingPlayer][1] = trashingCard;
	
	//test if any changes to game state
	struct gameState preCall2;
	memcpy(&preCall2, &G, sizeof(struct gameState));

	remodelResult = cardEffect(remodel, 1, gainingCard, -1, &G, 0, 0);
	simpleIntTest(-1, remodelResult, "successfullyCaughtBadInput");
	
	//test game state
	memcmpResult = memcmp(preCall2.supplyCount, G.supplyCount, sizeof(int) * (treasure_map + 1));
	simpleIntTest(0, memcmpResult, "NoChangedSupplyPiles");	
		
	//test current player
	simpleIntTest(preCall2.deckCount[testingPlayer], G.deckCount[testingPlayer], "NoChangePlayerDeckCount");
	simpleIntTest(preCall2.handCount[testingPlayer], G.handCount[testingPlayer], "PlayerHandCount");
	simpleIntTest(preCall2.discardCount[testingPlayer], G.discardCount[testingPlayer], "PlayerDiscardCount");		
	
	return 0;
	
}
	