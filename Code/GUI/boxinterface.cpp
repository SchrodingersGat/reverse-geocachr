
#include <stdio.h>
#include <QStringList>

#include "boxinterface.h"
#include "debug.h"
#include "boxpackets.h"
#include "box_defines.h"

#include "waypoints.h"

#define TIMEOUT 300

#define MAX_TRIES 5

Box::Box()
{
    handle = NULL;
    running = false;
    connected = false;

    memset(&boxVersion, 0, sizeof(boxVersion));
    memset(&boxSettings, 0, sizeof(boxSettings));
    memset(&boxStatus, 0, sizeof(boxStatus));
}

/* USB HID connection thread (polls every second)
 */
void Box::run()
{
    int attempts = 0;
    int cursor = 0;
    bool result = false;

    running = true;


    while (running)
    {
        Sleep(200);

        switch (cursor)
        {
        default:
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

        cursor = (cursor + 1) % 3;

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

    for (int i = 0; i < tries; i ++)
    {
        result &= RequestBoxStatus();
        result &= RequestBoxSettings();
        result &= RequestBoxVersion();

        if (result)
            break;
    }

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
    if (res == -1) {
        HIDDisconnect();
        Debug("HID Write Failed (-1)");
        return false;
    }

    //Read out the feature report
    res = hid_read_timeout(handle, rxBuf, HID_REPORT_SIZE, TIMEOUT);

    if (res != HID_REPORT_SIZE)
    {
        Debug("HID Read Failed (res = " + QString::number(res) + ")");
        return false;
    }

    //read was successful, decode the data
    if (decodeBoxStatusPacketStructure(rxBuf, &boxStatus))
    {
        Debug("Read box status");
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
        Debug("RequestBoxSettings failed");
        return false;
    }

    res = hid_read_timeout(handle, rxBuf, HID_REPORT_SIZE, TIMEOUT);

    if (res != HID_REPORT_SIZE)
    {
        return false;
    }

    if (decodeBoxSettingsPacketStructure(rxBuf, &boxSettings))
    {
        Debug("Read box settings");
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
        Debug("RequestBoxVersion write failed");
        return false;
    }

    res = hid_read_timeout(handle, rxBuf, HID_REPORT_SIZE, TIMEOUT);

    if (res != HID_REPORT_SIZE)
    {
        return false;
    }

    if (decodeBoxVersionPacketStructure(rxBuf, &boxVersion))
    {
        Debug("Read box version");
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

    if (!HIDConnect())
    {
        return false;
    }

    txBuf[0] = 0x00;
    encodeResetPacket(&txBuf[1]);

    res = hid_write(handle, txBuf, HID_REPORT_SIZE + 1);

    if (res != HID_REPORT_SIZE)
    {
        Debug("ResetIntoBootloader - hid_write() failed");
        return false;
    }

    return true;
}

bool Box::ReadClueData(int clueIndex, Clue_t *c, int tries) {

    //Read out the clue data
    if (RequestClueInfo(clueIndex, c, tries) == false) return false;

    for (int i=0;i<NUM_CLUE_LINES;i++) {
        if (RequestClueHint(clueIndex, c, i, tries) == false) return false;
    }

    return true;
}

bool Box::WriteClueData(int clueIndex, Clue_t *c, int tries) {

    //Write the clue data
    if (SetClueInfo(clueIndex, c, tries) == false) return false;

    for (int i=0;i<NUM_CLUE_LINES;i++) {
        if (SetClueHint(clueIndex, c, i, tries) == false) return false;
    }

    return true;
}

bool Box::SetClueInfo(int clueIndex, Clue_t *c, int tries)
{
    bool result = false;

    do
    {
        result = SetClueInfo(clueIndex, c);
        tries--;
        Sleep(10);
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

    encodeClueInfoPacket(&txBuf[1],clueIndex,&c->waypoint);

    res = hid_write(handle, rxBuf, HID_REPORT_SIZE + 1);

    if (res != (HID_REPORT_SIZE + 1)) {
        Debug("HIDWrite failed");
        return false;
    }

    Clue_t c_tmp;

    if (!this->RequestClueInfo(clueIndex, &c_tmp)) {
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
        Sleep(10);
    } while (result == false && tries > 0);

    return result;
}

/* Request information on a particular clue */
bool Box::RequestClueInfo(int clueIndex, Clue_t *c)
{
    int res = -1;
    int i = 0;

    Debug("RequestClueInfo - " + QString::number(clueIndex));

    if (c == NULL) {
        Debug("Waypoint pointer is NULL");
        return false;
    }

    if (HIDConnect() == false) {
        return false;
    }

    //Write clue info to the box
    txBuf[i++] = 0;

    encodeRequestClueInfoPacket(&txBuf[1],clueIndex);

    res = hid_write(handle, txBuf, HID_REPORT_SIZE+1);

    if (res == -1) {//write failed
        Debug("HIDWrite failed");
        HIDDisconnect();
        return false;
    }

    //read the dataz back
    res = hid_read_timeout(handle,rxBuf,HID_REPORT_SIZE,TIMEOUT);

    HIDDisconnect();

    if (res != HID_REPORT_SIZE) {//read failed
        Debug("HIDRead failed");
        return false;
    }

    else
    {
        uint8_t index;
        Waypoint_t wp_tmp;
        if (decodeClueInfoPacket(rxBuf,&index,&wp_tmp))
        {
            return true;
        } else {
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
        Sleep(10);
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

    if (res != (HID_REPORT_SIZE + 1)) {
        Debug("HIDWrite failed");
        return false;
    }

    //read the dataz back
    res = hid_read_timeout(handle,rxBuf,HID_REPORT_SIZE,TIMEOUT);

    if (res != HID_REPORT_SIZE) {
        Debug("HIDRead failed");
        return false;
    } else {

        uint8_t index_tmp;
        uint8_t line_tmp;
        clue_line text_tmp;
        if (decodeClueLinePacket(rxBuf,&index_tmp,&line_tmp,text_tmp))
        {
            //Extract clue line text
            if ((index_tmp == clueIndex) &&
                (line_tmp == line))
            {
                //Copy the text data acrosss
                memcpy(c->lines[line],text_tmp,sizeof(clue_line));
            }

            return true;
        } else {
            Debug("Response doesn't match");
            return false;
        }
    }

    return false;
}

bool Box::SetClueHint(int clueIndex, Clue_t *c, int line, int tries)
{
    bool result = false;

    do
    {
        result = SetClueHint(clueIndex, c, line);
        tries--;
        Sleep(10); //give up control for a bit
    } while (result == false && tries > 0);

    return result;
}

bool Box::SetClueHint(int clueIndex, Clue_t *c, int line)
{
    Debug("SetClueHint - " + QString::number(clueIndex) + " / " + QString::number(line));

    if (c == NULL) {
        Debug("Waypoint pointer is NULL");
        return false;
    }

    if (line > NUM_CLUE_LINES) {
        Debug("Line number (" + QString::number(line) + ") invalid");
        return false;
    }

    int res = -1;

    int i = 0;

    if (HIDConnect() == false) {
        return false;
    }

    QString clueText = Clue_GetLineText(c,line);

    txBuf[i++] = 0;

    encodeClueLinePacket(&txBuf[1],clueIndex,line,c->lines[line]);

    res = hid_write(handle, txBuf, HID_REPORT_SIZE + 1);

    //Couldn't transmit the data
    if (res == -1) {
        Debug("HIDWrite failed");
        return false;
    }

    //Make a temp waypoint and read it back
    Clue_t c_tmp;

    if (RequestClueHint(clueIndex, &c_tmp, line, MAX_TRIES) == false) {
        Debug("RequestClueHint failed!");
        return false;
    }

    QString clue2 = Clue_GetLineText(&c_tmp, line);

    if (clueText != clue2) {
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
    return false;
}

bool Box::Lock()
{
    return false;
}

bool Box::SkipToNext()
{
    int res;
    int i = 0;
    if (HIDConnect() == false) return false;

    txBuf[i++] = 0x00;

    encodeNextCluePacket(&txBuf[1]);

    res = hid_write(handle, txBuf, HID_REPORT_SIZE + 1);

    if (res == -1) return false;

    return RequestBoxInfo();
}

bool Box::SkipToPrevious()
{
    int res;

    int i = 0;

    if (HIDConnect() == false) return false;

    txBuf[i++] = 0x00;
    encodeNextCluePacket(&txBuf[1]);

    res = hid_write(handle, txBuf, HID_REPORT_SIZE + 1);

    if (res == -1) return false;

    return RequestBoxInfo();
}

bool Box::SetNumberOfClues(int nClues, int tries)
{
    bool result = false;

    do
    {
        result = SetNumberOfClues(nClues);
        tries--;
        Sleep(10);
    } while (!result && tries > 0);

    return result;
}

bool Box::SetNumberOfClues(int nClues)
{
    Debug("Setting number of clues - " + QString::number(nClues));

    if (nClues < 0 || nClues > MAX_CLUES) {
        Debug("Number of clues invalid");
        return false;
    }

    int res;

    int i = 0;

    if (HIDConnect() == false) {
        return false;
    }

    txBuf[i++] = 0x00;
    encodeSetClueCountPacket(&txBuf[1],nClues & 0xFF);

    res = hid_write(handle, txBuf, HID_REPORT_SIZE + 1);

    if (res != (HID_REPORT_SIZE + 1)) {
        Debug("HIDWrite failed");
        return false;
    }

    if (!RequestBoxInfo()) {
        Debug("RequestBoxInfo failed");
        return false;
    }

    if (nClues != boxStatus.totalClues) {
        Debug("Clue count mismatch " + QString::number(nClues));
        return false;
    }

    return true;
}
