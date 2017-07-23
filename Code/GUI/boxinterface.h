#ifndef BOXINTERFACE_H
#define BOXINTERFACE_H

#include <QThread>
#include <QMutex>
#include <QTimer>
#include <stdint.h>
#include <windows.h>

#include "hidapi/hidapi/hidapi.h"

#include "waypoint.h"
#include "ReverseGeocacheProtocol.h"
#include "boxpackets.h"

#include "box_defines.h"

class Box : public QThread
{
    Q_OBJECT

public:
    Box();

    //Box Info
    BoxInfo_t info;

    //USB Specific stuff
    volatile bool running;
    bool connected;

private:
    QMutex mutex;

    hid_device *handle;

    HIDBuffer rxBuf;    //Buffer for reading USB messages
    HIDBuffer txBuf;    //Buffer for writing USB messages

public slots:
    void run();

    bool HIDConnect();
    void HIDDisconnect();

    bool ResetIntoBootloader();

    bool RequestBoxInfo(int tries);
    bool RequestBoxInfo();

    bool ReadClueData(int clueIndex, Clue_t *c, int tries);
    bool WriteClueData(int clueIndex, Clue_t *c, int tries);

    bool RequestClueHint(int clueIndex, Clue_t *c, int line, int tries);
    bool RequestClueHint(int clueIndex, Clue_t *c, int line);

    bool RequestClueInfo(int clueIndex, Clue_t *c, int tries);
    bool RequestClueInfo(int clueIndex, Clue_t *c);

    bool SetClueInfo(int clueIndex, Clue_t *c, int tries);
    bool SetClueInfo(int clueIndex, Clue_t *c);

    bool SetClueHint(int clueIndex, Clue_t *c, int line, int tries);
    bool SetClueHint(int clueIndex, Clue_t *c, int line);

    bool Unlock();
    bool Lock();
    bool SkipToPrevious();
    bool SkipToNext();

    bool SetNumberOfClues(int nClues, int tries);
    bool SetNumberOfClues(int nClues);

};

extern Box box;


#endif // BOXINTERFACE_H

