#ifndef _WAYPOINTS_H
#define _WAYPOINTS_H


#include <QList>
#include <QString>
#include <stdint.h>

#include <QObject>

#include "waypoint.h"

class ClueList : public QObject {
    Q_OBJECT
public:
    ClueList();

    //Functions
    void Reset();

    QString CurrentClueTitle();
    QString CurrentClueHeader();
    QString CurrentClueFooter();

    Clue_t* GetCurrentClue();
    Clue_t* GetClueAtIndex(uint8_t index);

    bool SaveToFile(QString filename);
    bool LoadFromFile(QString filename);

    bool DeleteClue(uint8_t index);

    bool AddClue(Clue_t c);
    bool ValidWaypoint(double lat, double lng);


    bool IsClueSelected();
    uint8_t ClueIndex();
    uint8_t ClueCount();

    //Public Data
    Clue_t welcomeMessage;
    QList<Clue_t> clues;
    Clue_t completeMessage;

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

extern ClueList clues;

//Other waypoint functions
void Clue_SetLineText(Clue_t *c, uint8_t line, QString text);
QString Clue_GetLineText(Clue_t *c, uint8_t line);
QString escapeClueString(QString text);

#endif // CLUE_LIST_H

