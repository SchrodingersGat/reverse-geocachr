#include "waypoints.h"

#include <QSettings>

//Global settings
const QString SETTING_NUM_CLUES = "NumberOfClues";
const QString SETTING_WELCOME_MSG = "WelcomeMsg";
const QString SETTING_CLUE = "Clue";
const QString SETTING_COMPLETE_MSG = "CompleteMsg";

//Titles for the various settings
const QString SETTING_CLUE_LAT = "Latitude";
const QString SETTING_CLUE_LNG = "Longitude";
const QString SETTING_CLUE_THRESHOLD = "Threshold";
const QString SETTING_CLUE_TYPE = "Type";
const QString SETTING_CLUE_OPTIONS = "Options";
const QString SETTING_CLUE_LINE = "Line_";

#include "waypoint.h"

WaypointList::WaypointList() {

    Reset();
}

void WaypointList::Reset() {

    waypoints.clear();
    Waypoint_Init(&welcomeMessage);
    Waypoint_Init(&completeMessage);

    currentClue = BOX_WELCOME_MSG;
}

Waypoint_t* WaypointList::GetCurrentClue() {
    if (currentClue > BOX_COMPLETE_MSG) currentClue = BOX_WELCOME_MSG;
    if ((currentClue > waypoints.count()) && (currentClue < BOX_COMPLETE_MSG)) currentClue = BOX_WELCOME_MSG;

    return GetClueAtIndex(currentClue);
}

Waypoint_t* WaypointList::GetClueAtIndex(uint8_t index) {

    if (index == BOX_WELCOME_MSG) return &welcomeMessage;
    if (index == BOX_COMPLETE_MSG) return &completeMessage;

    if (index <= waypoints.count()) {
        return &(waypoints[index - 1]);
    }

    return NULL;
}

QString WaypointList::CurrentClueTitle() {
    switch (currentClue) {
    case BOX_COMPLETE_MSG:
        return "Welcome Message";
    case BOX_WELCOME_MSG:
        return "Completion Message";
    default:
        return "Clue " + QString::number(currentClue) + " of " + QString::number(waypoints.count());
    }
}

QString WaypointList::CurrentClueHeader() {
    switch (currentClue) {
    case BOX_WELCOME_MSG:
        return "Reverse Geocache";
    case BOX_COMPLETE_MSG:
        return "Congratulations!";
    default:
        return "Clue " + QString::number(currentClue) + " of " + QString::number(waypoints.count());
    }
}

QString WaypointList::CurrentClueFooter() {
    switch (currentClue) {
    case BOX_WELCOME_MSG:
        return "";
    case BOX_COMPLETE_MSG:
        return "Complete!";
        break;
    }

    Waypoint_t *w = GetCurrentClue();

    if (w == NULL) {
        return "";
    }

    switch (w->type) {
    default:
    case CLUE_NO_HINT:
        return "";
    case CLUE_SHOW_DISTANCE:
        return "Distance: 1.234 km";
    case CLUE_WARMER_COOLER:
        return "Getting warmer!";
    case CLUE_SHOW_HEADING:
        return "Heading: 135 degrees";
    case CLUE_SHOW_CARDINAL:
        return "Head WNW";
    }
}

void WaypointList::SelectFirst() {
    currentClue = BOX_WELCOME_MSG;
}

void WaypointList::SelectLast() {
    currentClue = BOX_COMPLETE_MSG;
}

void WaypointList::SelectPrev() {
    if (currentClue >= BOX_COMPLETE_MSG) {
        currentClue = waypoints.count();
    } else if (currentClue > BOX_WELCOME_MSG) {
        currentClue--;
    }
}

void WaypointList::SelectClue(uint8_t index) {
    if (index >= BOX_COMPLETE_MSG) {
        currentClue = BOX_COMPLETE_MSG;
    } else if (index > waypoints.count()) {
        currentClue = BOX_WELCOME_MSG;
    } else {
        currentClue = index;
    }
}

void WaypointList::SelectNext() {
    if (currentClue < waypoints.count()) {
        currentClue++;
    } else {
        currentClue = BOX_COMPLETE_MSG;
    }
}

bool WaypointList::SaveToFile(QString filename) {

    /*
    QSettings settings(filename, QSettings::IniFormat);

    if (!settings.isWritable()) return;

    settings.clear();

    //Number of clues
    settings.setValue(SETTING_NUM_CLUES, box.waypoints.count());

    //Welcome Message
    settings.beginGroup(SETTING_WELCOME_MSG);
    box.welcomeMessage.save(&settings);
    settings.endGroup();

    //Completion message
    settings.beginGroup(SETTING_COMPLETE_MSG);
    box.completeMessage.save(&settings);
    settings.endGroup();

    Waypoint *w;

    //For each of the clues
    for (int i=0;i<box.waypoints.count();i++)
    {
        settings.beginGroup(SETTING_CLUE + "_" + QString::number(i));

        w = &box.waypoints[i];
        w->save(&settings);

        settings.endGroup();
    }
    */
    return false;
}

bool WaypointList::LoadFromFile(QString filename) {

    /*
    QFileInfo check(filename);

    if (!check.exists() || !check.isFile()) return;

    QSettings settings(filename, QSettings::IniFormat);

    bool ok;

    int nClues = settings.value(SETTING_NUM_CLUES,0).toInt(&ok);

    if (!ok)
    {
        nClues = 0;
        //error msg here
    }

    if (nClues == 0)
    {
        //error msg here
    }

    box.waypoints.clear();

    //Welcome message
    settings.beginGroup(SETTING_WELCOME_MSG);
    box.welcomeMessage.load(&settings);
    settings.endGroup();

    settings.beginGroup(SETTING_COMPLETE_MSG);
    box.completeMessage.load(&settings);
    settings.endGroup();

    Waypoint w;

    //Each clue
    for (int i=0;i<nClues;i++)
    {
        settings.beginGroup(SETTING_CLUE+"_"+QString::number(i));

        if (w.load(&settings))
        {
            box.waypoints.append(w);
        }

        settings.endGroup();
    }
    */
    return false;
}

bool WaypointList::ValidWaypoint(double lat, double lng) {

    for (int i=0;i<waypoints.count();i++) {
        //if (Waypoint_Distance(lat,lng,&waypoints[i]) < 250) {
        //    return false;
        //}
    }

    return true;
}

bool WaypointList::AddWaypoint(Waypoint_t wp) {

    if (waypoints.count() >= BOX_MAX_CLUES) return false;

    if (!ValidWaypoint(wp.lat,wp.lng)) return false;

    waypoints.append(wp);

    //Select the given waypoint
    SelectClue(waypoints.count());

    return true;
}
