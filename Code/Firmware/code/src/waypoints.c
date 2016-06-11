/*
 * waypoints.c
 *
 *  Created on: Jul 17, 2015
 *      Author: Oliver
 */

#include "waypoints.h"
#include "box_defines.h"

Clue_t clues[BOX_MAX_CLUES + 2];
uint8_t currentWaypoint = 0;
uint8_t numberOfWaypoints = 3; //default value

Clue_t welcomeMessage;
Clue_t completeMessage;

Clue_t* GetClue(uint8_t index) {

	if (index > BOX_COMPLETE_MSG) index = BOX_WELCOME_MSG;

	return (&clues[index]);
}

void NextClue() {

	//Progress to the next clue
	if (boxInfo.currentClue < boxInfo.totalClues) {
		boxInfo.currentClue++;
	} else {
		boxInfo.currentClue = BOX_COMPLETE_MSG;
	}
}

void PrevClue() {
	if (boxInfo.currentClue == BOX_COMPLETE_MSG) {
		boxInfo.currentClue = boxInfo.totalClues;
	} else if (boxInfo.currentClue > BOX_WELCOME_MSG) {
		boxInfo.currentClue--;
	}
}

void FirstClue() {
	boxInfo.currentClue = BOX_FIRST_CLUE;
}

void LastClue() {
	boxInfo.currentClue = boxInfo.totalClues;
}
