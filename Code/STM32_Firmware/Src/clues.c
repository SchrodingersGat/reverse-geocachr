#include "clues.h"

void GetClue(Clue_t* clue, int index)
{
	//TODO
	switch (index)
	{
	default:
	case 0:
		Clue_SetLine(clue, 0, "Hello world");
		Clue_SetLine(clue, 1, "abcdefghijklmnopqrstuvwxyz");
		Clue_SetLine(clue, 2, "Wahahaahhahaha");
		Clue_SetLine(clue, 3, "1234567890");
		Clue_SetLine(clue, 4, "--------------------------");
		Clue_SetLine(clue, 5, "dddd");
		Clue_SetLine(clue, 6, "ABCDEFGIJ");

		clue->waypoint.lat = -42.82489;
		clue->waypoint.lng = 147.286350;

		clue->waypoint.threshold = 250;
		clue->waypoint.type = CLUE_SHOW_HEADING;

		break;
	case 1:
		Clue_SetLine(clue, 0, "This is the second clue");
		Clue_SetLine(clue, 1, "IT FINDS WHAT IT SEEKS");
		Clue_SetLine(clue, 2, "");
		Clue_SetLine(clue, 3, "");
		Clue_SetLine(clue, 4, "");
		Clue_SetLine(clue, 5, "CAN YOU BRAVE ENOUGH?");
		Clue_SetLine(clue, 6, "ooooooooooooooooooooOoo");

		clue->waypoint.lat = -42.32489;
		clue->waypoint.lng = 147.486350;

		clue->waypoint.threshold = 250;
		clue->waypoint.type = CLUE_SHOW_DISTANCE;
		break;
	}
}


