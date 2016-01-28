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
#include "debug.h"

WaypointList::WaypointList() {

    Reset();
}

void WaypointList::Reset() {

    waypoints.clear();
    Waypoint_Init(&welcomeMessage);
    Waypoint_Init(&completeMessage);

    currentClue = BOX_WELCOME_MSG;

    emit clueUpdated();
}

bool WaypointList::IsClueSelected() {
    if (currentClue > 0 && currentClue <= waypoints.count()) return true;

    return false;
}

uint8_t WaypointList::ClueIndex() {
    return currentClue;
}

uint8_t WaypointList::ClueCount() {
    return waypoints.count();
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
    case BOX_WELCOME_MSG:
        return "Welcome Message";
    case BOX_COMPLETE_MSG:
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

    if (waypoints.count() == 0) currentClue = BOX_WELCOME_MSG;
    else currentClue = 1;

    emit clueUpdated();
}

void WaypointList::SelectLast() {

    if (waypoints.count() == 0) currentClue = BOX_COMPLETE_MSG;
    else currentClue = waypoints.count();

    emit clueUpdated();
}

void WaypointList::SelectPrev() {
    if (currentClue >= BOX_COMPLETE_MSG) {
        currentClue = waypoints.count();
    } else if (currentClue > BOX_WELCOME_MSG) {
        currentClue--;
    }

    emit clueUpdated();
}

void WaypointList::SelectClue(uint8_t index) {
    if (index >= BOX_COMPLETE_MSG) {
        currentClue = BOX_COMPLETE_MSG;
    } else if (index > waypoints.count()) {
        currentClue = BOX_WELCOME_MSG;
    } else {
        currentClue = index;
    }

    emit clueUpdated();
}

void WaypointList::SelectNext() {
    if (currentClue < waypoints.count()) {
        currentClue++;
    } else {
        currentClue = BOX_COMPLETE_MSG;
    }

    emit clueUpdated();
}

//Swap the current clue with the one after it
void WaypointList::MoveClueDown() {

    if (currentClue == BOX_WELCOME_MSG || currentClue == BOX_COMPLETE_MSG) return;
    if (waypoints.count() < 2) return; //needs at least two clues

    if (currentClue >= waypoints.count()) return;

    Waypoint_t w = waypoints[currentClue];

    waypoints.removeAt(currentClue);
    waypoints.insert(currentClue + 1, w);

    currentClue++;

    emit clueUpdated();
}

//Swap the current clue with the one before it
void WaypointList::MoveClueUp() {
    if (currentClue == BOX_WELCOME_MSG || currentClue == BOX_COMPLETE_MSG) return;

    if (waypoints.count() < 2) return;  //Needs at least two clues

    if (currentClue <= 1) return; //There are no clues before this one!

    Waypoint_t w = waypoints[currentClue];

    waypoints.removeAt(currentClue);
    waypoints.insert(currentClue - 1, w);

    currentClue--;

    emit clueUpdated();
}

void WaypointList::MoveClueFirst() {
    if (currentClue == BOX_WELCOME_MSG || currentClue == BOX_COMPLETE_MSG) return;

    if (waypoints.count() < 2) return; //needs at least two clues

    emit clueUpdated();
}

void WaypointList::MoveClueLast() {
    if (currentClue == BOX_WELCOME_MSG || currentClue == BOX_COMPLETE_MSG) return;

    if (waypoints.count() < 2) return; //needs at least two clues

    emit clueUpdated();
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

        qDebug() << i << Waypoint_Distance(lat,lng,&waypoints[i]);
        if (Waypoint_Distance(lat,lng,&waypoints[i]) < 250) {
            return false;
        }
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

void Waypoint_SetLineText(Waypoint_t *w, uint8_t line, QString text) {
    if (w == NULL || line >= NUM_CLUE_LINES) return;

    for (int i=0;i<CLUE_LINE_LEN_MAX;i++) {
        if (i >= text.count()) w->lines[line][i] = 0;
        else w->lines[line][i] = (uint8_t) text.at(i).toLatin1();
    }

    //ensure the last char is zero-terminated
    w->lines[line][CLUE_LINE_LEN_MAX - 1] = 0;
}

QString Waypoint_GetLineText(Waypoint_t *w, uint8_t line) {
    if (w == NULL || line >= NUM_CLUE_LINES) return "";

    QString text = "";

    for (int i=0;i<CLUE_LINE_LEN_MAX;i++) {
        if (w->lines[line][i] != 0) {
            text.append(QChar((char) w->lines[line][i]));
        }
    }

    return text;
}
