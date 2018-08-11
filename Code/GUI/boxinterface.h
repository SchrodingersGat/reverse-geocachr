#ifndef BOXINTERFACE_H
#define BOXINTERFACE_H

#include <QThread>
#include <QMutex>
#include <QTimer>
#include <stdint.h>
#include <windows.h>

#include "hidapi/hidapi/hidapi.h"

#include "waypoint.h"
#include "boxpackets.h"

#include "box_defines.h"


class Box : public QThread
{
    Q_OBJECT

public:
    Box();

    // Box variables
    BoxStatus_t status;
    BoxSettings_t settings;
    BoxVersion_t version;

    // Cancel upload / download
    void cancel()
    {
        uploading = false;
        downloading = false;
    }

    bool connected = false;
    bool uploading = false;
    bool downloading = false;
    bool running = false;

protected:

    bool receive(int timeout = 200);
    bool transmit(int tries = 5);

    bool txRx() { return transmit() && receive(); }

    hid_device* handle = nullptr;

    HIDBuffer rxBuf;    // Buffer for reading USB data
    HIDBuffer txBuf;    // Buffer for writing USB data

    QMutex mutex;

public slots:
    void run();

    bool HIDConnect();
    void HIDDisconnect();

    bool ResetIntoBootloader();

    // Request ALL box information
    bool RequestBoxInfo(int tries = 5);

    bool RequestBoxStatus();
    bool RequestBoxSettings();
    bool RequestBoxVersion();

    bool WriteSettings(BoxSettings_t settings);

    bool ReadClueData(int clueIndex, Clue_t *c, int tries);
    bool WriteClueData(int clueIndex, Clue_t *c, int tries);

    bool RequestClueHint(int clueIndex, Clue_t *c, int line, int tries = 5);
    bool SetClueHint(int clueIndex, Clue_t *c, int line, int tries = 5);

    bool RequestClueInfo(int clueIndex, Clue_t *c, int tries = 5);
    bool SetClueInfo(int clueIndex, Clue_t *c, int tries = 5);

    bool Unlock();
    bool Lock();
    bool SkipToPrevious();
    bool SkipToNext();

    bool SetNumberOfClues(int nClues, int tries = 5);
};

extern Box box;


#endif // BOXINTERFACE_H

