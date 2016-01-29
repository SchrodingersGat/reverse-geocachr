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

    bool IsClueSelected();
    uint8_t ClueIndex();
    uint8_t ClueCount();

    //Public Data
    Waypoint_t welcomeMessage;
    QList<Waypoint_t> waypoints;
    Waypoint_t completeMessage;

public slots:

    //Set which clue is selected
    void SelectClue(uint8_t index);
    void SelectNext();
    void SelectPrev();
    void SelectLast();
    void SelectFirst();

    //Move clues around
    void MoveClueUp();
    void MoveClueDown();
    void MoveClueFirst();
    void MoveClueLast();

private:
    //Private data / functions
    uint8_t currentClue;

signals:
    void clueUpdated();

};

extern WaypointList waypoints;

//Other waypoint functions
void Waypoint_SetLineText(Waypoint_t *w, uint8_t line, QString text);
QString Waypoint_GetLineText(Waypoint_t *w, uint8_t line);
QString escapeClueString(QString text);
#endif // CLUE_LIST_H

