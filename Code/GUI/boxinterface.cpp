
#include <stdio.h>
#include <QStringList>
#include <qdebug.h>

#include "boxinterface.h"
#include "debug.h"
#include "boxpackets.h"
#include "box_defines.h"

#include "waypoints.h"

#define TIMEOUT 50

#define MAX_TRIES 5

Box::Box()
{
    handle = NULL;
    running = false;
    connected = false;

    // Clear data initially
    memset(&status, 0, sizeof(BoxStatus_t));
    memset(&settings, 0, sizeof(BoxSettings_t));
    memset(&version, 0, sizeof(BoxVersion_t));
}


// Polling thread in the background
void Box::run()
{
    int attempts = 0;
    int cursor = 0;
    bool result = false;

    running = true;

    while (running)
    {
        Sleep(200);

        // Don't poll in the middle of a transfer
        if (downloading || uploading)
        {
            continue;
        }

        if (mutex.tryLock(100))
        {
            continue;
        }

        switch (cursor++)
        {
        default:
            result = false;
            cursor = 0;
            break;
        case 0:
            result = RequestBoxStatus();
            break;
        case 1:
            result = RequestBoxSettings();
            break;
        case 2:
            result = RequestBoxVersion();
            break;
        }

        if (result)
        {
            attempts = 5;
        }
        else if (attempts > 0)
        {
            attempts--;
        }

        connected = attempts > 0;

        mutex.unlock();
    }

    HIDDisconnect();

    Debug("Thread complete");
}


//Attempt a connection to the box
bool Box::HIDConnect()
{
    if (handle == NULL)
    {
        handle = hid_open(HID_VID, HID_PID, NULL);
    }

    if (!handle)
    {
        Debug("HIDConnect() failed");
    }

    return (handle != NULL);
}


//Disconnect the box
void Box::HIDDisconnect()
{
    if (handle != NULL)
    {
        hid_close(handle);
    }

    handle = NULL;
}

bool Box::RequestBoxInfo(int tries)
{
    bool result = true;

    if (!mutex.tryLock(100)) return false;

    for (int i = 0; i < tries; i ++)
    {
        result = true;

        Sleep(20);
        result &= RequestBoxStatus();

        Sleep(20);
        result &= RequestBoxSettings();

        Sleep(20);
        result &= RequestBoxVersion();

        if (result)
        {
            // All information read successfully
            break;
        }
    }

    mutex.unlock();

    return result;
}


/* Request box status
 */
bool Box::RequestBoxStatus()
{
    int res;

    if (HIDConnect() == false)
    {
        return false; //Connection failure
    }

    txBuf[0] = 0x00;

    encodeRequestBoxStatusPacket(&txBuf[1]);

    res = hid_write(handle, txBuf, HID_REPORT_SIZE+1);

    //HID write was not successful
    if (res == -1)
    {
        HIDDisconnect();
        Debug("HID Write Failed (-1)");
        return false;
    }

    Sleep(20);

    //Read out the feature report
    res = hid_read_timeout(handle, rxBuf, HID_REPORT_SIZE, TIMEOUT);

    if (res != HID_REPORT_SIZE)
    {
        HIDDisconnect();
        Debug("HID Read Failed (res = " + QString::number(res) + ")");
        return false;
    }

    BoxStatus_t tmpStatus;

    //read was successful, decode the data
    if (decodeBoxStatusPacketStructure(rxBuf, &tmpStatus))
    {
        status = tmpStatus;

        //Debug("Read box status");
        return true;
    }
    else
    {
        Debug("BOX_INFO message failed");
        return false;
    }
}


bool Box::RequestBoxSettings()
{
    int res;

    if (!HIDConnect())
    {
        return false;
    }

    txBuf[0] = 0x00;

    encodeRequestBoxSettingsPacket(&txBuf[1]);

    res = hid_write(handle, txBuf, HID_REPORT_SIZE + 1);

    if (res == -1)
    {
        HIDDisconnect();
        Debug("RequestBoxSettings failed");
        return false;
    }

    Sleep(20);

    res = hid_read_timeout(handle, rxBuf, HID_REPORT_SIZE, TIMEOUT);

    if (res != HID_REPORT_SIZE)
    {
        HIDDisconnect();
        return false;
    }

    BoxSettings_t tmpSettings;

    if (decodeBoxSettingsPacketStructure(rxBuf, &tmpSettings))
    {
        settings = tmpSettings;

        //Debug("Read box settings");
        return true;
    }
    else
    {
        return false;
    }
}


bool Box::RequestBoxVersion()
{
    int res = -1;

    if (!HIDConnect())
    {
        return false;
    }

    txBuf[0] = 0x00;
    encodeRequestBoxVersionPacket(&txBuf[1]);

    res = hid_write(handle, txBuf, HID_REPORT_SIZE + 1);

    if (res == -1)
    {
        HIDDisconnect();
        Debug("RequestBoxVersion write failed");
        return false;
    }

    Sleep(20);

    res = hid_read_timeout(handle, rxBuf, HID_REPORT_SIZE, TIMEOUT);

    if (res != HID_REPORT_SIZE)
    {
        HIDDisconnect();
        return false;
    }

    BoxVersion_t tmpVersion;

    if (decodeBoxVersionPacketStructure(rxBuf, &tmpVersion))
    {
        version = tmpVersion;

        //Debug("Read box version");
        return true;
    }
    else
    {
        return false;
    }

}


bool Box::ResetIntoBootloader()
{
    int res = -1;

    if (downloading || uploading) return false;

    if (!mutex.tryLock(100))
        return false;

    if (!HIDConnect())
    {
        mutex.unlock();
        return false;
    }

    txBuf[0] = 0x00;
    encodeResetPacket(&txBuf[1]);

    res = hid_write(handle, txBuf, HID_REPORT_SIZE + 1);

    if (res != HID_REPORT_SIZE)
    {
        HIDDisconnect();
        Debug("ResetIntoBootloader - hid_write() failed");
        mutex.unlock();
        return false;
    }

    mutex.unlock();

    return true;
}


bool Box::WriteSettings(BoxSettings_t settings)
{
    int res = -1;

    if (downloading || uploading) return false;

    if (!mutex.tryLock(100))
    {
        return false;
    }

    if (!HIDConnect())
    {
        mutex.unlock();
        return false;
    }

    txBuf[0] = 0;

    encodeSetBoxSettingsPacket(&txBuf[1],
            settings.pwmLocked,
            settings.pwmUnlocked);

    res = hid_write(handle, txBuf, HID_REPORT_SIZE + 1);

    if (res == -1)
    {
        HIDDisconnect();
        Debug("Box::WriteSettings - hid_write() failed");
        mutex.unlock();
        return false;
    }

    mutex.unlock();
    return RequestBoxInfo();
}


bool Box::ReadClueData(int clueIndex, Clue_t *c, int tries)
{
    if (!mutex.tryLock(100))
    {
        return false;
    }

    //Read out the clue data
    if (RequestClueInfo(clueIndex, c, tries) == false)
    {
        mutex.unlock();
        return false;
    }

    for (int i=0;i<NUM_CLUE_LINES;i++)
    {
        if (RequestClueHint(clueIndex, c, i, tries) == false)
        {
            mutex.unlock();
            return false;
        }
    }

    mutex.unlock();

    return true;
}


bool Box::WriteClueData(int clueIndex, Clue_t *c, int tries)
{
    if (!mutex.tryLock(100))
    {
        return false;
    }

    //Write the clue data
    if (SetClueInfo(clueIndex, c, tries) == false)
    {
        mutex.unlock();
        return false;
    }

    for (int i=0; i<NUM_CLUE_LINES; i++)
    {
        if (SetClueHint(clueIndex, c, i, tries) == false)
        {
            mutex.unlock();
            return false;
        }
    }

    mutex.unlock();

    return true;
}


bool Box::SetClueInfo(int clueIndex, Clue_t *c, int tries)
{
    bool result = false;

    do
    {
        result = SetClueInfo(clueIndex, c);
        tries--;
        Sleep(20);
    } while (result == false && tries > 0);

    return result;
}


bool Box::SetClueInfo(int clueIndex, Clue_t *c)
{
    Debug("SetClueInfo - "  + QString::number(clueIndex));

    if (c == NULL) {
        Debug("Clue pointer is NULL");
        return false;
    }

    int res = -1;
    int i = 0;

    if (!HIDConnect()) {
        return false;
    }

    txBuf[i++] = 0;

    encodeClueInfoPacket(&txBuf[1], clueIndex, &c->waypoint, c->checksum);

    res = hid_write(handle, rxBuf, HID_REPORT_SIZE + 1);

    if (res != (HID_REPORT_SIZE + 1))
    {
        HIDDisconnect();
        Debug("HIDWrite failed");
        return false;
    }

    Clue_t c_tmp;

    if (!RequestClueInfo(clueIndex, &c_tmp))
    {
        Debug("RequestClueInfo failed");
        return false;
    }

    //for now, assume they are the same
//    return (w->checksum == w_tmp.checksum);

    return true;
}


bool Box::RequestClueInfo(int clueIndex, Clue_t *c, int tries)
{
    bool result = false;

    do
    {
        result = RequestClueInfo(clueIndex, c);
        tries--;
        Sleep(20);
    } while (result == false && tries > 0);

    return result;
}


/* Request information on a particular clue */
bool Box::RequestClueInfo(int clueIndex, Clue_t *c)
{
    int res = -1;
    int i = 0;

    Debug("RequestClueInfo - " + QString::number(clueIndex));

    if (c == NULL)
    {
        Debug("Waypoint pointer is NULL");
        return false;
    }

    if (HIDConnect() == false)
    {
        return false;
    }

    //Write clue info to the box
    txBuf[i++] = 0;

    encodeRequestClueInfoPacket(&txBuf[1], clueIndex);

    res = hid_write(handle, txBuf, HID_REPORT_SIZE+1);

    if (res == -1)
    {
        Debug("HIDWrite failed");
        HIDDisconnect();
        return false;
    }

    Sleep(20);

    //read the dataz back
    res = hid_read_timeout(handle, rxBuf, HID_REPORT_SIZE,TIMEOUT);

    //HIDDisconnect();

    if (res != HID_REPORT_SIZE)
    {
        HIDDisconnect();
        Debug("HIDRead failed");
        return false;
    }

    else
    {
        uint8_t index;
        Waypoint_t wp_tmp;

        uint32_t checksum;

        if (decodeClueInfoPacket(rxBuf, &index, &wp_tmp, &checksum))
        {
            // Copy waypoint and checksum information
            c->checksum = checksum;
            c->waypoint = wp_tmp;

            return true;
        }
        else
        {
            Debug("Decode_Waypoint_Message failed");
        }

        return false;
    }

    return true;
}


bool Box::RequestClueHint(int clueIndex, Clue_t *c, int line, int tries)
{
    bool result = false;

    do
    {
        result = RequestClueHint(clueIndex, c, line);
        tries--;
        Sleep(20);
    } while (result == false && tries > 0);

    return result;
}


bool Box::RequestClueHint(int clueIndex, Clue_t *c, int line)
{
    Debug("RequestClueHint() - " + QString::number(clueIndex) + " / " + QString::number(line));

    if (c == NULL) {
        Debug("Waypoint pointer is NULL");
        return false;
    }

    if (line >= NUM_CLUE_LINES) {
        Debug("Line number incorrect");
        return false;
    }

    int res = -1;

    int i = 0;

    if (HIDConnect() == false) {
        return false;
    }

    //Write clue info to the box
    txBuf[i++] = 0;

    encodeRequestClueLinePacket(&txBuf[1],clueIndex,line);

    res = hid_write(handle, txBuf, HID_REPORT_SIZE+1);

    if (res != (HID_REPORT_SIZE + 1))
    {
        HIDDisconnect();
        Debug("HIDWrite failed");
        return false;
    }

    Sleep(20);

    //read the dataz back
    res = hid_read_timeout(handle, rxBuf, HID_REPORT_SIZE, TIMEOUT);

    if (res != HID_REPORT_SIZE)
    {
        HIDDisconnect();
        Debug("HIDRead failed");
        return false;
    }

    uint8_t index_tmp;
    uint8_t line_tmp;
    ClueLine_t text_tmp;

    if (decodeClueLineTextPacket(rxBuf, &index_tmp, &line_tmp, &text_tmp))
    {
        //Extract clue line text
        if ((index_tmp == clueIndex) &&
            (line_tmp == line))
        {
            //Copy the text data acrosss
            c->lines[line] = text_tmp;
        }

        qDebug() << "Read clue line @" << clueIndex << "," << line;
        qDebug() << Clue_GetLineText(text_tmp);

        return true;
    }
    else
    {
        Debug("Response doesn't match @ index" + QString::number(clueIndex));

        qDebug() << "ID:" << MSG_CLUE_LINE << rxBuf[0];
        qDebug() << "Index:" << clueIndex << "-" << index_tmp;
        qDebug() << "Line:" << line << "-" << line_tmp;

        return false;
    }
}


bool Box::SetClueHint(int clueIndex, Clue_t *c, int line, int tries)
{
    bool result = false;

    do
    {
        result = SetClueHint(clueIndex, c, line);
        tries--;
        Sleep(20); //give up control for a bit
    } while (result == false && tries > 0);

    return result;
}


bool Box::SetClueHint(int clueIndex, Clue_t *c, int line)
{
    Debug("SetClueHint - " + QString::number(clueIndex) + " / " + QString::number(line));

    if (c == NULL)
    {
        Debug("Waypoint pointer is NULL");
        return false;
    }

    if (line > NUM_CLUE_LINES)
    {
        Debug("Line number (" + QString::number(line) + ") invalid");
        return false;
    }

    int res = -1;

    int i = 0;

    if (HIDConnect() == false)
    {
        return false;
    }

    QString clueText = Clue_GetLineText(c,line);

    txBuf[i++] = 0;

    qDebug() << "SetClueHint -" << clueIndex << "/" << line << "-" << Clue_GetLineText(c, line);

    encodeClueLineTextPacket(&txBuf[1], clueIndex, line, &c->lines[line]);

    res = hid_write(handle, txBuf, HID_REPORT_SIZE + 1);

    //Couldn't transmit the data
    if (res == -1)
    {
        HIDDisconnect();
        Debug("HIDWrite failed");
        return false;
    }

    //Make a temp waypoint and read it back
    Clue_t c_tmp;

    if (RequestClueHint(clueIndex, &c_tmp, line, MAX_TRIES) == false)
    {
        Debug("RequestClueHint failed!");
        return false;
    }

    QString clue2 = Clue_GetLineText(&c_tmp, line);

    if (clueText != clue2)
    {
        Debug("Line mismatch!");
        Debug("> " + clueText);
        Debug("> " + clue2);

        return false;
    }

    return true;
}

/* Send commands to the box */
bool Box::Unlock()
{
    if (downloading || uploading) return false;

    if (!mutex.tryLock(100))
    {
        return false;
    }

    // TODO

    mutex.unlock();

    return false;
}

bool Box::Lock()
{
    if (downloading || uploading) return false;

    if (!mutex.tryLock(100))
    {
        return false;
    }

    //TODO

    mutex.unlock();

    return false;
}


bool Box::SkipToNext()
{
    int res;

    if (downloading || uploading) return false;

    if (!mutex.tryLock(100))
    {
        return false;
    }

    if (HIDConnect() == false)
    {
        mutex.unlock();
        return false;
    }

    txBuf[0] = 0x00;

    encodeNextCluePacket(&txBuf[1]);

    res = hid_write(handle, txBuf, HID_REPORT_SIZE + 1);

    if (res == -1)
    {
        HIDDisconnect();
        mutex.unlock();
        return false;
    }

    mutex.unlock();

    return RequestBoxInfo();
}


bool Box::SkipToPrevious()
{
    int res;

    if (downloading || uploading) return false;

    if (!mutex.tryLock(100))
    {
        return false;
    }

    if (HIDConnect() == false)
    {
        mutex.unlock();
        return false;
    }

    txBuf[0] = 0x00;

    encodePrevCluePacket(&txBuf[1]);

    res = hid_write(handle, txBuf, HID_REPORT_SIZE + 1);

    if (res == -1)
    {
        HIDDisconnect();
        mutex.unlock();
        return false;
    }

    mutex.unlock();

    return RequestBoxInfo();
}

bool Box::SetNumberOfClues(int nClues, int tries)
{
    bool result = false;

    do
    {
        result = SetNumberOfClues(nClues);
        tries--;
        Sleep(20);
    } while (!result && tries > 0);

    return result;
}

bool Box::SetNumberOfClues(int nClues)
{
    Debug("Setting number of clues - " + QString::number(nClues));

    if (nClues < 0 || nClues > BOX_MAX_CLUES)
    {
        Debug("Number of clues invalid");
        return false;
    }

    int res;

    int i = 0;

    if (HIDConnect() == false)
    {
        return false;
    }

    txBuf[i++] = 0x00;
    encodeSetClueCountPacket(&txBuf[1],nClues & 0xFF);

    res = hid_write(handle, txBuf, HID_REPORT_SIZE + 1);

    if (res != (HID_REPORT_SIZE + 1))
    {
        HIDDisconnect();
        Debug("HIDWrite failed");
        return false;
    }

    if (!RequestBoxInfo())
    {
        Debug("RequestBoxInfo failed");
        return false;
    }

    if (nClues != settings.totalClues)
    {
        Debug("Clue count mismatch " + QString::number(nClues));
        return false;
    }

    return true;
}
