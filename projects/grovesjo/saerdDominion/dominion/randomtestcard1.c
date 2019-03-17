/////////////////////////////////////////////////////////////////////////////////
// Name: Joshua Kevin Groves
// Date: 2 March 2019
// File: randomtestcard3.c
// Description: Random test for Council Room implementation function
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
		k[0] = council_room;
		
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
			
			int deckSize = getRandIntInRangeInclusive(9,30);
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
		G.hand[testingPlayer][randHandPos] = council_room;
	
	
		//test if any changes to game state
		struct gameState preCall;
		memcpy(&preCall, &G, sizeof(struct gameState));


		printf("------------------------------------------------------------------------\n");
		printf ("Starting unit test for Council Room implementation - Iteration %d\n", currTest);
		printf("Total Number of Players: %d\n", numPlayers);
		
		
		cardEffect(council_room, -1, -1, -1, &G, randHandPos, 0);
	
		//test game state
		memcmpResult = memcmp(preCall.supplyCount, G.supplyCount, sizeof(int) * (treasure_map + 1));
		simpleIntTest(0, memcmpResult, "NoChangeSupplyPiles");
	
		//test player
		simpleIntTest(preCall.numBuys+1, G.numBuys, "Buys+1");
		//+4 cards drawn, but Council Room gets discarded so net change is +3
		simpleIntTest(preCall.handCount[testingPlayer]+3, G.handCount[testingPlayer], "+4HandCount");
		simpleIntTest(preCall.deckCount[testingPlayer]+preCall.discardCount[testingPlayer]-4,G.deckCount[testingPlayer]+G.discardCount[testingPlayer],"RemainingDecksBalance");
	
		
		//test other players changes
		for(j=0; j < numPlayers; j++){
			if(j != testingPlayer){
				printf("-----Player %d Tests-----\n",j);
				//test hand
				simpleIntTest(preCall.handCount[j]+1, G.handCount[j], "OtherPlayer+1toHand");
	
				//test discard pile
				if(preCall.deckCount[j]>0){
					simpleIntTest(preCall.discardCount[j], G.discardCount[j], "NoChangeOPDiscardPileCount");
					memcmpResult = memcmp(preCall.discard[j], G.discard[j], sizeof(int) * G.discardCount[j]);
					simpleIntTest(0,memcmpResult,"NoChangeOPDiscard");						
					//test deck
					simpleIntTest(preCall.deckCount[j]-1, G.deckCount[j], "OtherPlayer-1toDeck");
				}
				else{
					//test discard
					simpleIntTest(0, G.discardCount[j], "NoCardsinOPDiscardAfterShuffle");
					//test deck number
					simpleIntTest(preCall.discardCount[j]-1,G.deckCount[j],"DiscardPileShuffledIntoDeck-1forHand");
				}
	
			}
		}
	
	}
	return 0;
}