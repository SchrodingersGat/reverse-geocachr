#include "waypoint.h"

#include <math.h>

#define PI 3.14159265359

void Clue_Init(Clue_t *clue)
{
    uint8_t i = 0;

    Waypoint_Init(&clue->waypoint);
    
    for (i = 0; i < NUM_CLUE_LINES; i++)
    {
        memset(&clue->lines[i], 0, CLUE_LINE_LEN_MAX);
    }
}

void Waypoint_Init(Waypoint_t *waypoint)
{
    memset(waypoint, 0, sizeof(Waypoint_t));

    waypoint->lat = 0;
    waypoint->lng = 0;

    waypoint->threshold = WAYPOINT_THRESHOLD_DEFAULT;
    waypoint->type = CLUE_SHOW_DISTANCE;
    
    //Clue options
    waypoint->options.centerText = 0;

}

uint8_t Waypoint_Validate(Waypoint_t *waypoint)
{
    if (waypoint->threshold < WAYPOINT_THRESHOLD_MINIMUM) return 0;
    if (waypoint->threshold > WAYPOINT_THRESHOLD_MAXIMUM) return 0;
    
    //Otherwise, all is OK
    return 1;
}

uint32_t Clue_CalculateChecksum(Clue_t *clue)
{
    int i = 0;
    int idx = 0;
    // Manually construct the chekcksum for the clue

    uint32_t chk = 0;

    chk += ((uint32_t) (clue->waypoint.lat * 1000) << 20);
    chk += ((uint32_t) (clue->waypoint.lng * 1000) << 10);

    chk += clue->waypoint.type;
    chk += clue->waypoint.threshold;

    // Add in each clue character
    for (i = 0; i < NUM_CLUE_LINES; i++)
    {
        while (clue->lines[i].text[idx] != 0 && idx < CLUE_LINE_LEN_MAX)
        {
            chk += (uint32_t) ((clue->lines[i].text[idx]) << i);
            idx++;
        }
    }

    return chk;
}

//Return distance to waypoint in metres
double Waypoint_Distance(double lat, double lng, Waypoint_t *w)
{

    double dLat;
    double dLng;

    double a1;
    double a2;
    double a3;

    double c;

    dLat = w->lat - lat;
    dLat *= (PI / 180);

    dLng = w->lng - lng;
    dLng *= (PI / 180);

    a1 = sin(dLat/2);
    a1 = pow(a1,2);

    a2 = sin(dLng/2);
    a2 = pow(a2,2);

    a3 = cos(lat * PI / 180);
    a2 *= a3;
    a3 = cos(w->lat * PI / 180);
    a2 *= a3;

    a1 += a2;

    a2 = sqrt(a1);
    a3 = sqrt(1-a1);

    c = atan2(a2,a3);
    c *= 2;

    c *= 6371000;

    return c;
}


/*
 * Calculate the heading angle FROM the supplied lat/lng coord TO the waypoint
 * Return heading angle in degrees
 */
double Waypoint_Heading(double lat, double lng, Waypoint_t *w)
{
	double dLng = w->lng - lng;

	double y = sin(dLng) * cos(w->lat);
	double x = cos(lat) * sin(w->lat) -
			(sin(lat) * cos(w->lat) * cos(dLng));

	//double angle = atan2(y, x) * 180 / M_PI;
	double angle = atan2(y, x) * 180 / PI;

	while (angle < 0)
	{
		angle += 360;
	}
	while (angle > 360)
	{
		angle += 360;
	}

	return angle;
}

void Clue_SetLine(Clue_t *c, uint8_t line, char *text)
{
	uint8_t i = 0;

	uint8_t endFound = 0;

	if (line >= NUM_CLUE_LINES) return;

	for (i = 0; i < CLUE_LINE_LEN_MAX-1; i++)
	{
		if (text[i] == 0)
		{
			endFound = 1;
		}

		if (endFound == 1)
		{
            c->lines[line].text[i] = 0;
		} else
		{
            c->lines[line].text[i] = text[i];
		}
	}

	//Always zero-terminate!
    c->lines[line].text[CLUE_LINE_LEN_MAX-1] = 0;
}
