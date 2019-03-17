/////////////////////////////////////////////////////////////////////////////////
// Name: Joshua Kevin Groves
// Date: 2 March 2019
// File: randomtestcard2.c
// Description: Random test for Village implementation function
/////////////////////////////////////////////////////////////////////////////////

#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <string.h>
#include "dominion_helpers.h"
#include <time.h>


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

int simpleIntRangeInclusiveTest(int low, int high, int test, const char* testName){
	int result = 0;
	if(test>=low && test<=high){
		result = 1;		
		printf("%s: passed\n", testName);
	}
	else
		printf("%s: FAILED; Expected in Range: %d - %d; Actual: %d\n", testName, low, high, test);			
	return result;
}

int getRandIntInRangeInclusive(int lower, int upper){
	int result;
	int range = upper - lower;
	range++;
	srand(time(NULL));
	result = rand() % range + lower;
	return result;
}

int main (int argc, char** argv) {
	int numTests = 12;
	int currTest;
	for(currTest = 0; currTest < numTests; currTest++){

		int seed = getRandIntInRangeInclusive(1, 100);
		int numPlayers = getRandIntInRangeInclusive(2, 4);
		struct gameState G;
	
		//build random kingdom card set
		int k[10];		
		k[0] = village;
		
		int i;
		int z;
		for(i=1; i<10; i++){
			int valid = 0;
			int temp;
			while(valid == 0){
				temp = getRandIntInRangeInclusive(7, 26);
				for(z=0; z<10; z++){
					if(k[z] == temp){
						valid = 0;
						z += 10;
					}
					else
						valid = 1;
				}
			}
			k[i] = temp;
		}
	
		initializeGame(numPlayers, k, seed, &G);
	
		//rebuild player decks to make random decks, hands, and discard piles
		
		for(i=0; i<numPlayers; i++){
			//undo initial card deals
			G.deckCount[i] = 0;
			G.handCount[i] = 0;
			G.discardCount[i] = 0;
			G.supplyCount[copper] += 7;
			G.supplyCount[estate] += 3;
			
			int deckSize = getRandIntInRangeInclusive(8,30);
			int vicPointsNum = getRandIntInRangeInclusive(0,8);		
			int coinNum = getRandIntInRangeInclusive(0,deckSize-vicPointsNum);
			int actionNum = deckSize - coinNum - vicPointsNum;
			
			for(z=0; z<coinNum; z++){
				int success = -1;
				while(success != 0){
					int gaining = getRandIntInRangeInclusive(4,6);
					success = gainCard(gaining, &G, 0, i);
				}
			}
	
			for(z=0; z<vicPointsNum; z++){
				int success = -1;
				while(success != 0){					
					int gaining = getRandIntInRangeInclusive(1,3);
					success = gainCard(gaining, &G, 0, i);
				}
			} 		
	
			for(z=0; z<actionNum; z++){
				int success = -1;
				while(success != 0){			
					int gaining = getRandIntInRangeInclusive(0,9);
					success = gainCard(k[gaining], &G, 0, i);
				}
			} 			
	
			
			//move all cards from discard to deck then shuffle
			for (z = 0; z < G.discardCount[i]; z++){
				G.deck[i][z] = G.discard[i][z];
				G.discard[i][z] = -1;
			}
			
			G.deckCount[i] = G.discardCount[i];
			G.discardCount[i] = 0;
	
			shuffle(i, &G);
			
			//build hand and discardPile
			int handSize = getRandIntInRangeInclusive(2,5);
			int discardSize = getRandIntInRangeInclusive(0,deckSize-handSize);
	
			for(z=0; z<discardSize; z++){
				G.discard[i][G.discardCount[i]] = G.deck[i][G.deckCount[i]-1];
				G.discardCount[i]++;
				G.deckCount[i]--;
			}
			
			for(z=0; z<handSize; z++){
				G.hand[i][G.handCount[i]] = G.deck[i][G.deckCount[i]-1];
				G.handCount[i]++;
				G.deckCount[i]--;
			}
	
		}

		int memcmpResult;
		int j;
		int testingPlayer = G.whoseTurn;
		int randHandPos = getRandIntInRangeInclusive(0,G.handCount[testingPlayer]-1);
		G.hand[testingPlayer][randHandPos] = village;
	
	
		//test if any changes to game state
		struct gameState preCall;
		memcpy(&preCall, &G, sizeof(struct gameState));


		printf("------------------------------------------------------------------------\n");
		printf ("Starting unit test for village implementation - Iteration %d\n", currTest);
		printf("Total Number of Players: %d\n", numPlayers);
		
		
		cardEffect(village, -1, -1, -1, &G, randHandPos, 0);
	
		//test game state
		memcmpResult = memcmp(preCall.supplyCount, G.supplyCount, sizeof(int) * (treasure_map + 1));
		simpleIntTest(0, memcmpResult, "NoChangeSupplyPiles");
	

		//test current player
		//hand count +1 for drawn but then -1 for discard village card
		simpleIntTest(preCall.handCount[testingPlayer], G.handCount[testingPlayer], "PostHandCount");
		if(preCall.deckCount[testingPlayer]>0){
			simpleIntTest(preCall.deckCount[testingPlayer]-1, G.deckCount[testingPlayer], "RemainingDeckCount");
			simpleIntTest(preCall.discardCount[testingPlayer], G.discardCount[testingPlayer], "DiscardedCount");	
			if(randHandPos == 0)
				simpleIntTest(preCall.deck[testingPlayer][preCall.deckCount[testingPlayer]-1], G.hand[testingPlayer][0],"SameCardDrawnFromDeck");
			else
				simpleIntTest(preCall.deck[testingPlayer][preCall.deckCount[testingPlayer]-1], G.hand[testingPlayer][randHandPos],"SameCardDrawnFromDeck");
		}
		else{
			simpleIntTest(preCall.discardCount[testingPlayer]-1, G.deckCount[testingPlayer],"RemainingDeckCount");
			simpleIntTest(0, G.discardCount[testingPlayer], "DiscardedCount");			
		}
			
		simpleIntTest(preCall.numActions+2, G.numActions, "+2Actions");
		
		
		//test other players changes
		for(j=0; j < numPlayers; j++){
			if(j != testingPlayer){
				printf("-----Player %d Tests-----\n",j);
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
	
	}
	return 0;
}
