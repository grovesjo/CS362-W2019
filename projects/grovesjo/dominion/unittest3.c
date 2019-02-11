/////////////////////////////////////////////////////////////////////////////////
// Name: Joshua Kevin Groves
// Date: 10 February 2019
// File: unittest3.c
// Description: Unit test for scoreFor() function
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

	printf ("Starting unit test for score for function\n");
	
	initializeGame(numPlayers, k, seed, &G);
	int memcmpResult;
	int i;
	int scorePlayer;
	
	struct gameState preCall;
	memcpy(&preCall, &G, sizeof(struct gameState));
	
	scorePlayer = scoreFor(G.whoseTurn, &G);

	memcmpResult = memcmp(&preCall, &G, sizeof(struct gameState));
	simpleIntTest(0, memcmpResult, "NoGameStateChanges");
	
	simpleIntTest(3,scorePlayer, "BeginningNormalGame");
	
	//cards only in deck
	G.handCount[G.whoseTurn] = 0;
	G.discardCount[G.whoseTurn] = 0;
	G.deckCount[G.whoseTurn] = 10;

	for(i=0; i<G.deckCount[G.whoseTurn]; i++)
		G.deck[G.whoseTurn][i] = estate;
	
	scorePlayer = scoreFor(G.whoseTurn, &G);
	simpleIntTest(10, scorePlayer, "10EstatesinDeckOnly");
	
	for(i=0; i<G.deckCount[G.whoseTurn]; i++)
		G.deck[G.whoseTurn][i] = duchy;
	
	scorePlayer = scoreFor(G.whoseTurn, &G);
	simpleIntTest(30, scorePlayer, "10DuchyinDeckOnly");
	
	for(i=0; i<G.deckCount[G.whoseTurn]; i++)
		G.deck[G.whoseTurn][i] = province;
	
	scorePlayer = scoreFor(G.whoseTurn, &G);
	simpleIntTest(60, scorePlayer, "10ProvinceinDeckOnly");

	//mixed in deck
	G.deck[G.whoseTurn][0] = estate;
	G.deck[G.whoseTurn][1] = estate;
	G.deck[G.whoseTurn][2] = estate;
	G.deck[G.whoseTurn][3] = estate;
	G.deck[G.whoseTurn][4] = duchy;
	G.deck[G.whoseTurn][5] = duchy;
	G.deck[G.whoseTurn][6] = duchy;
	G.deck[G.whoseTurn][7] = province;
	G.deck[G.whoseTurn][8] = province;
	G.deck[G.whoseTurn][9] = province;	
	
	scorePlayer = scoreFor(G.whoseTurn, &G);
	simpleIntTest(31, scorePlayer, "MixedinDeckOnly");

	//mixed with curses
	G.deck[G.whoseTurn][0] = curse;
	G.deck[G.whoseTurn][1] = curse;
	scorePlayer = scoreFor(G.whoseTurn, &G);
	simpleIntTest(27, scorePlayer, "MixedinDeckOnlyCurses");
	
	//cards only in hand
	G.handCount[G.whoseTurn] = 10;
	G.discardCount[G.whoseTurn] = 0;
	G.deckCount[G.whoseTurn] = 0;

	for(i=0; i<G.handCount[G.whoseTurn]; i++)
		G.hand[G.whoseTurn][i] = estate;
	
	scorePlayer = scoreFor(G.whoseTurn, &G);
	simpleIntTest(10, scorePlayer, "10EstatesinHandOnly");
	
	for(i=0; i<G.handCount[G.whoseTurn]; i++)
		G.hand[G.whoseTurn][i] = duchy;
	
	scorePlayer = scoreFor(G.whoseTurn, &G);
	simpleIntTest(30, scorePlayer, "10DuchyinHandOnly");
	
	for(i=0; i<G.handCount[G.whoseTurn]; i++)
		G.hand[G.whoseTurn][i] = province;
	
	scorePlayer = scoreFor(G.whoseTurn, &G);
	simpleIntTest(60, scorePlayer, "10ProvinceinHandOnly");

	//mixed in hand
	G.hand[G.whoseTurn][0] = estate;
	G.hand[G.whoseTurn][1] = estate;
	G.hand[G.whoseTurn][2] = estate;
	G.hand[G.whoseTurn][3] = estate;
	G.hand[G.whoseTurn][4] = duchy;
	G.hand[G.whoseTurn][5] = duchy;
	G.hand[G.whoseTurn][6] = duchy;
	G.hand[G.whoseTurn][7] = province;
	G.hand[G.whoseTurn][8] = province;
	G.hand[G.whoseTurn][9] = province;	
	
	scorePlayer = scoreFor(G.whoseTurn, &G);
	simpleIntTest(31, scorePlayer, "MixedinHandOnly");

	//mixed with curses
	G.hand[G.whoseTurn][0] = curse;
	G.hand[G.whoseTurn][1] = curse;
	scorePlayer = scoreFor(G.whoseTurn, &G);
	simpleIntTest(27, scorePlayer, "MixedinHandOnlyCurses");
	
	//cards only in discard
	G.handCount[G.whoseTurn] = 0;
	G.discardCount[G.whoseTurn] = 10;
	G.deckCount[G.whoseTurn] = 0;

	for(i=0; i<G.discardCount[G.whoseTurn]; i++){
		G.discard[G.whoseTurn][i] = estate;
		G.deck[G.whoseTurn][i] = -1;
		G.hand[G.whoseTurn][i] = -1;
	}

	scorePlayer = scoreFor(G.whoseTurn, &G);
	simpleIntTest(10, scorePlayer, "10EstatesinDiscardOnly");
	
	for(i=0; i<G.discardCount[G.whoseTurn]; i++)
		G.discard[G.whoseTurn][i] = duchy;
	
	scorePlayer = scoreFor(G.whoseTurn, &G);
	simpleIntTest(30, scorePlayer, "10DuchyinDiscardOnly");
	
	for(i=0; i<G.discardCount[G.whoseTurn]; i++)
		G.discard[G.whoseTurn][i] = province;
	
	scorePlayer = scoreFor(G.whoseTurn, &G);
	simpleIntTest(60, scorePlayer, "10ProvinceinDiscardOnly");

	//mixed in deck
	G.discard[G.whoseTurn][0] = estate;
	G.discard[G.whoseTurn][1] = estate;
	G.discard[G.whoseTurn][2] = estate;
	G.discard[G.whoseTurn][3] = estate;
	G.discard[G.whoseTurn][4] = duchy;
	G.discard[G.whoseTurn][5] = duchy;
	G.discard[G.whoseTurn][6] = duchy;
	G.discard[G.whoseTurn][7] = province;
	G.discard[G.whoseTurn][8] = province;
	G.discard[G.whoseTurn][9] = province;	
	
	scorePlayer = scoreFor(G.whoseTurn, &G);
	simpleIntTest(31, scorePlayer, "MixedinDiscardOnly");

	//mixed with curses
	G.discard[G.whoseTurn][0] = curse;
	G.discard[G.whoseTurn][1] = curse;
	scorePlayer = scoreFor(G.whoseTurn, &G);
	simpleIntTest(27, scorePlayer, "MixedinDiscardOnlyCurses");
	

	//cards in all three locations
	G.hand[G.whoseTurn][0] = estate;
	G.hand[G.whoseTurn][1] = estate;
	G.hand[G.whoseTurn][2] = estate;
	G.hand[G.whoseTurn][3] = estate;
	G.hand[G.whoseTurn][4] = duchy;
	G.hand[G.whoseTurn][5] = duchy;
	G.hand[G.whoseTurn][6] = duchy;
	G.hand[G.whoseTurn][7] = province;
	G.hand[G.whoseTurn][8] = province;
	
	G.deck[G.whoseTurn][0] = estate;
	G.deck[G.whoseTurn][1] = estate;
	G.deck[G.whoseTurn][2] = estate;
	G.deck[G.whoseTurn][3] = estate;
	G.deck[G.whoseTurn][4] = duchy;
	G.deck[G.whoseTurn][5] = duchy;
	G.deck[G.whoseTurn][6] = duchy;
	G.deck[G.whoseTurn][7] = province;
	G.deck[G.whoseTurn][8] = province;
	G.deck[G.whoseTurn][9] = province;
	G.deck[G.whoseTurn][10] = province;	
	
	G.discard[G.whoseTurn][0] = estate;
	G.discard[G.whoseTurn][1] = estate;
	G.discard[G.whoseTurn][2] = estate;
	G.discard[G.whoseTurn][3] = estate;
	G.discard[G.whoseTurn][4] = duchy;
	G.discard[G.whoseTurn][5] = duchy;
	G.discard[G.whoseTurn][6] = duchy;
	G.discard[G.whoseTurn][7] = province;
	G.discard[G.whoseTurn][8] = province;
	G.discard[G.whoseTurn][9] = province;	
	
	G.handCount[G.whoseTurn] = 9;
	G.discardCount[G.whoseTurn] = 10;
	G.deckCount[G.whoseTurn] = 11;
	scorePlayer = scoreFor(G.whoseTurn, &G);
	simpleIntTest(93, scorePlayer, "MixedinAllPiles");
	
	//test for no victory points
	for(i=0; i<10; i++){
		G.discard[G.whoseTurn][i] = smithy;
		G.deck[G.whoseTurn][i] = smithy;		
		G.hand[G.whoseTurn][i] = smithy;		
	}
	
	G.handCount[G.whoseTurn] = 10;
	G.discardCount[G.whoseTurn] = 10;
	G.deckCount[G.whoseTurn] = 10;
	scorePlayer = scoreFor(G.whoseTurn, &G);
	simpleIntTest(0, scorePlayer, "NoVictoryPoints");
	
	//test gardens
	G.handCount[G.whoseTurn] = 10;
	G.discardCount[G.whoseTurn] = 10;
	G.deckCount[G.whoseTurn] = 10;
	G.hand[G.whoseTurn][9] = gardens;
	
	scorePlayer = scoreFor(G.whoseTurn, &G);
	simpleIntTest(3, scorePlayer, "Gardens30Cards1Garden");
	
	//test gardens
	G.handCount[G.whoseTurn] = 10;
	G.discardCount[G.whoseTurn] = 10;
	G.deckCount[G.whoseTurn] = 10;
	G.hand[G.whoseTurn][9] = gardens;
	G.discard[G.whoseTurn][9] = gardens;
	
	scorePlayer = scoreFor(G.whoseTurn, &G);
	simpleIntTest(6, scorePlayer, "Gardens30Cards2Gardens");
	
	//test great hall	
	G.hand[G.whoseTurn][9] = great_hall;
	G.discard[G.whoseTurn][9] = great_hall;
	G.deck[G.whoseTurn][9] = great_hall;
	
	scorePlayer = scoreFor(G.whoseTurn, &G);
	simpleIntTest(3, scorePlayer, "GreatHall");
	
	return 0;	
}
	
	