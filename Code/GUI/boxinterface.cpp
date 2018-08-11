
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
    }

    HIDDisconnect();

    Debug("Thread complete");
}


//Attempt a connection to the box
bool Box::HIDConnect()
{
    if (handle == NULL)
    {
        Debug("Attempting connection");
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


bool Box::receive(int timeout)
{
    if (!mutex.tryLock(200))
    {
        return false;
    }

    if (!HIDConnect())
    {
        return false;
    }

    int n = hid_read_timeout(handle, rxBuf, HID_REPORT_SIZE, timeout);

    bool result = false;

    if (n == HID_REPORT_SIZE)
    {
        //qDebug() << "Received:" << QByteArray((const char*) rxBuf, rxBuf[1] + 2);
        result = true;
    }
    else
    {
        qDebug() << "No data.";
    }

    Sleep(10);

    mutex.unlock();

    return result;
}


bool Box::transmit(int tries)
{
    bool result = false;
    int n = -1;

    if (!mutex.tryLock(200))
    {
        return false;
    }

    // First byte must always be zero
    txBuf[0] = 0;

    while (tries > 0)
    {
        tries--;

        // Try to first ensure that we are connected
        if (!HIDConnect()) continue;

        n = hid_write(handle, txBuf, HID_REPORT_SIZE + 1);

        // Transmission was not successful
        if (n != (HID_REPORT_SIZE + 1))
        {
            HIDDisconnect();
        }
        else
        {
            // Transmission was successful
            result = true;
            break;
        }
    }

    // Ensure some gap is left
    Sleep(10);

    mutex.unlock();

    if (result)
    {
        //qDebug() << "Transmitted:" << QByteArray((const char*) &(txBuf[1]), txBuf[2] + 2);
    }
    else
    {
        qDebug() << "Transmit failed.";
    }

    return result;
}


bool Box::RequestBoxInfo(int tries)
{
    bool result = true;

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

    return result;
}


/* Request box status
 */
bool Box::RequestBoxStatus()
{
    encodeRequestBoxStatusPacket(&txBuf[1]);

    // Send the request and await response
    if (!txRx()) return false;

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
    encodeRequestBoxSettingsPacket(&txBuf[1]);

    // Send the request and await response
    if (!txRx()) return false;

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
    encodeRequestBoxVersionPacket(&txBuf[1]);

    // Send the request and await response
    if (!txRx()) return false;

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
    /*
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
    */

    return false;
}


bool Box::WriteSettings(BoxSettings_t settings)
{
    if (downloading || uploading) return false;

    encodeSetBoxSettingsPacket(&txBuf[1],
            settings.pwmLocked,
            settings.pwmUnlocked);

    if (!transmit()) return false;

    return RequestBoxInfo();
}


bool Box::ReadClueData(int clueIndex, Clue_t *c, int tries)
{
    //Read out the clue data
    if (!RequestClueInfo(clueIndex, c, tries))
    {
        return false;
    }

    for (int i = 0; i < NUM_CLUE_LINES; i++)
    {
        if (!RequestClueHint(clueIndex, c, i, tries))
        {
            return false;
        }
    }

    return true;
}


bool Box::WriteClueData(int clueIndex, Clue_t *c, int tries)
{
    //Write the clue data
    if (!SetClueInfo(clueIndex, c, tries))
    {
        return false;
    }

    for (int i=0; i<NUM_CLUE_LINES; i++)
    {
        if (!SetClueHint(clueIndex, c, i, tries))
        {
            return false;
        }
    }

    return true;
}


bool Box::SetClueInfo(int clueIndex, Clue_t *c, int tries)
{
    bool result = false;

    if (!c) return false;

    Debug("SetClueInfo @ index " + QString::number(clueIndex));

    while (tries > 0)
    {
        tries--;

        encodeClueInfoPacket(&txBuf[1], clueIndex, &c->waypoint, c->checksum);

        if (!transmit()) continue;

        // TODO - Logic here to test that the data were transmitted correctly
        result = true;
        break;
    }

    return result;
}


bool Box::RequestClueInfo(int clueIndex, Clue_t *c, int tries)
{
    bool result = false;

    if (!c) return false;

    uint8_t idx;
    Waypoint_t wpTmp;
    uint32_t chk;

    Debug("RequestClueInfo @ index " + QString::number(clueIndex));

    while (tries > 0)
    {
        tries--;

        encodeRequestClueInfoPacket(&txBuf[1], clueIndex);

        // Request and response
        if (!txRx()) continue;

        if (decodeClueInfoPacket(rxBuf, &idx, &wpTmp, &chk))
        {
            c->checksum = chk;
            c->waypoint = wpTmp;

            result = true;
            break;
        }
        else
        {
            Debug("Error decoding ClueInfoPacket");
        }

    }

    return result;
}


bool Box::RequestClueHint(int clueIndex, Clue_t *c, int line, int tries)
{
    bool result = false;

    if (!c) return false;

    uint8_t idxTmp;
    uint8_t lineTmp;

    ClueLine_t textTmp;

    Debug("RequestClueHint @ index " + QString::number(clueIndex) + ", line " + QString::number(line));

    while (tries > 0)
    {
        tries--;

        encodeRequestClueLinePacket(&txBuf[1], clueIndex, line);

        // Request and response
        if (!txRx()) continue;

        // Zero out the line buffer first
        memset(&textTmp.text, 0, sizeof(textTmp));

        if (decodeClueLineTextPacket(rxBuf, &idxTmp, &lineTmp, &textTmp))
        {
            // Extract clue line text

            if ((idxTmp == clueIndex) &&
                (lineTmp == line))
            {
                // Copy the text data across
                for (int i = 0; i < CLUE_LINE_LEN_MAX; i++)
                {
                    c->lines[line].text[i] = textTmp.text[i];
                }

                result = true;
                break;
            }
            else
            {
                Debug("Mismatch in returned packet:");
                Debug("Index: " + QString::number(clueIndex) + " - " + QString::number(idxTmp));
                Debug("Line: " + QString::number(line) + " - " + QString::number(lineTmp));
            }
        }
        else
        {
            Debug("Error decoding ClueLineTextPacket");
        }
    }

    return result;
}


bool Box::SetClueHint(int clueIndex, Clue_t *c, int line, int tries)
{
    bool result = false;

    if (!c) return false;

    QString text = Clue_GetLineText(c, line);

    Debug("SetClueHint @ " + QString::number(clueIndex) + "," + QString::number(line) + " to - " + text);

    Clue_t clueTmp;

    while (tries > 0)
    {
        tries--;

        encodeClueLineTextPacket(&txBuf[1], clueIndex, line, &c->lines[line]);

        // Send the clue text
        if (!transmit()) continue;

        // Now request it back again
        if (!RequestClueHint(clueIndex, &clueTmp, line, tries)) continue;

        // The text should match!
        QString txt = Clue_GetLineText(&clueTmp, line);

        if (txt != text)
        {
            Debug("Text does not match:");
            Debug("Sent: " + text);
            Debug("Read: " + txt);

            continue;
        }

        // Success!
        result = true;
        break;
    }

    return result;
}


/* Send commands to the box */
bool Box::Unlock()
{
    if (downloading || uploading) return false;

    return false;
}

bool Box::Lock()
{
    if (downloading || uploading) return false;

    return false;
}


bool Box::SkipToNext()
{
    if (downloading || uploading) return false;

    encodeNextCluePacket(&txBuf[1]);

    if (!transmit()) return false;

    return RequestBoxInfo();
}


bool Box::SkipToPrevious()
{
    if (downloading || uploading) return false;

    encodePrevCluePacket(&txBuf[1]);

    if (!transmit()) return false;

    return RequestBoxInfo();
}

bool Box::SetNumberOfClues(int nClues, int tries)
{
    bool result = false;

    while (tries > 0)
    {
        tries--;

        encodeSetClueCountPacket(&txBuf[1], (uint8_t) nClues);

        if (!transmit()) continue;

        if (!RequestBoxInfo(tries)) continue;

        if (nClues == settings.totalClues)
        {
            Debug("Set total clues to " + QString::number(nClues));
            result = true;
            break;
        }
        else
        {
            Debug("Clue count mismatch:");
            Debug("Sent: " + QString::number(nClues));
            Debug("Read: " + QString::number(settings.totalClues));
        }
    }

    return result;
}
