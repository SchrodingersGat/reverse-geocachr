#ifndef BOXINTERFACE_H
#define BOXINTERFACE_H

#include <QThread>
#include <QMutex>
#include <QTimer>
#include <stdint.h>
#include <windows.h>

#include "hidapi/hidapi/hidapi.h"

#include "waypoint.h"
#include "box_messages.h"

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

    uint8_t readBuf[HID_REPORT_SIZE+1];
    uint8_t writeBuf[HID_REPORT_SIZE+1];

public slots:
    void run();

    bool HIDConnect();
    void HIDDisconnect();

    bool RequestBoxInfo(int tries);
    bool RequestBoxInfo();

    bool ReadWaypointData(int clueIndex, Waypoint_t *w, int tries);
    bool WriteWaypointData(int clueIndex, Waypoint_t *w, int tries);

    bool RequestClueHint(int clueIndex, Waypoint_t *w, int line, int tries);
    bool RequestClueHint(int clueIndex, Waypoint_t *w, int line);

    bool RequestClueInfo(int clueIndex, Waypoint_t *w, int tries);
    bool RequestClueInfo(int clueIndex, Waypoint_t *w);

    /*
    bool SetClueInfo(int clueIndex, Waypoint *w, int tries);
    bool SetClueInfo(int clueIndex, Waypoint *w);
    */

    bool SetClueHint(int clueIndex, Waypoint_t *w, int line, int tries);
    bool SetClueHint(int clueIndex, Waypoint_t *w, int line);

    bool Unlock();
    bool Lock();
    bool SkipToPrevious();
    bool SkipToNext();

    bool SetNumberOfClues(int nClues, int tries);
    bool SetNumberOfClues(int nClues);

};

extern Box box;


#endif // BOXINTERFACE_H

