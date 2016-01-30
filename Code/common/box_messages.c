#include "box_messages.h"

#include <string.h>
#include <stdio.h>

/**
Packet a message for a particular clue
**/

void Form_BoxInfo_Message(HIDBuffer buf, BoxInfo_t *info) {

	uint8_t i = 0;

	buf[i++] = BOX_MSG_SYSTEM_INFO;

	sprintf(&buf[i],
			"%u,%u,%u,%u,%u,%u,%u,%u",
			info->serialNumber,
			info->versionMajor,
			info->versionMinor,
			info->boardRevision,
			info->status,
			info->charge,
			info->currentClue,
			info->totalClues);
}

bool Decode_BoxInfo_Message(HIDBuffer buf, BoxInfo_t *info) {

	BoxInfo_t tmpInfo;
	uint8_t match = 0;

	match = sscanf(&buf[1],"%u,%u,%u,%u,%u,%u,%u,%u",
			&tmpInfo.serialNumber,
			&tmpInfo.versionMajor,
			&tmpInfo.versionMinor,
			&tmpInfo.boardRevision,
			&tmpInfo.status,
			&tmpInfo.charge,
			&tmpInfo.currentClue,
			&tmpInfo.totalClues);

	if (match == 8) {
		memcpy(info, &tmpInfo, sizeof(BoxInfo_t));
		return true;
	} else {
		return false;
	}

}

void Form_Waypoint_Message(HIDBuffer buf, uint8_t id, Waypoint_t *w) {

    uint8_t i = 0;

    buf[i++] = BOX_MSG_CLUE_INFO;

    buf[i++] = id;

    sprintf(&buf[i], "%.10f,%.10f,%u,%u,%u",
                     w->lat,
                     w->lng,
                     w->threshold,
                     w->type,
                     w->options);
}

//Read out waypoint info from a buffer
//Ignore the first two bytes of the buffer, as we've already read them to determine the pointer
bool Decode_Waypoint_Message(HIDBuffer buf, Waypoint_t *w) {

	double lat = 0;
	double lng = 0;

	uint16_t threshold = 0;
	uint8_t type = 0;
	uint8_t options = 0;

	uint8_t match = 0;

	match = sscanf(&buf[2], "%lf,%lf,%u,%u,%u",
							&lat,
							&lng,
							&threshold,
							&type,
							&options);

	if (match == 5) {
		w->lat = lat;
		w->lng = lng;
		w->threshold = threshold;
		w->type = type;
		w->options = options;

		return true;
	} else {
		return false;
	}
}

/**
Form a message for a particular line of a particular clue
**/
void Form_WaypointClue_Message(HIDBuffer buf, uint8_t id, uint8_t line, Waypoint_t *w) {

    //Store a waypoint clue info into a buffer
    //Buffer must be long enough!

    uint8_t i = 0;
    uint8_t j = 0;

    buf[i++] = BOX_MSG_CLUE_LINE;

    if (line >= NUM_CLUE_LINES) line = 0;

    buf[i++] = id;
    buf[i++] = line;

    for (j=0;j<CLUE_LINE_LEN_MAX;j++) {
        buf[i++] = w->lines[line][j];
    }

}

void Decode_WaypointClue_Message(HIDBuffer buf, uint8_t line, Waypoint_t *w) {

	Waypoint_SetLine(w, line, (char*) &buf[3]);
}
