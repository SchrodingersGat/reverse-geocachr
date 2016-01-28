#ifndef _WAYPOINTS_H
#define _WAYPOINTS_H


#include <QList>
#include <QString>
#include <stdint.h>

#include <QObject>

#include "waypoint.h"

class WaypointList : public QObject {
    Q_OBJECT
public:
    WaypointList();

    //Functions
    void Reset();

    QString CurrentClueTitle();
    QString CurrentClueHeader();
    QString CurrentClueFooter();

    Waypoint_t* GetCurrentClue();
    Waypoint_t* GetClueAtIndex(uint8_t index);

    bool SaveToFile(QString filename);
    bool LoadFromFile(QString filename);

    bool AddWaypoint(Waypoint_t wp);
    bool ValidWaypoint(double lat, double lng);

    //Public Data
    Waypoint_t welcomeMessage;
    QList<Waypoint_t> waypoints;
    Waypoint_t completeMessage;

public slots:

    void SelectClue(uint8_t index);
    void SelectNext();
    void SelectPrev();
    void SelectLast();
    void SelectFirst();

private:
    //Private data / functions
    uint8_t currentClue;

};

extern WaypointList waypoints;

#endif // CLUE_LIST_H

