
#include <stdio.h>
#include <QStringList>

#include "boxinterface.h"
#include "debug.h"
#include "box_messages.h"

#include "waypoints.h"

#define TIMEOUT 300

#define MAX_TRIES 5

Box::Box()
{
    handle = NULL;
    running = false;
    connected = false;
}

/* USB HID connection thread (polls every second)
 */
void Box::run()
{
    static uint8_t cursor = 0;

    Waypoint_t w;

    running = true;

    while (running) {
        connected = RequestBoxInfo();

        Sleep(1000);

        if (connected) {

            cursor = (cursor + 1) % NUM_CLUE_LINES;

            Waypoint_SetLineText(&w, cursor, "This is line " + QString::number(cursor));
            SetClueHint(1, &w, cursor);

//            RequestClueInfo(cursor, &w);


        }
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
    bool result = false;

    do
    {
        result = RequestBoxInfo();
        tries--;
        Sleep(10);
    } while (result == false && tries > 0);

    return result;
}

/* Request box info
 */
bool Box::RequestBoxInfo()
{
    int res;
    int i = 0;

    Debug("RequestBoxInfo()");

    if (HIDConnect() == false) {
        Debug("HIDConnect() failed");
        return false; //Connection failure
    }

    writeBuf[0] = 0x00;
    writeBuf[1] = BOX_MSG_SYSTEM_INFO;

    res = hid_write(handle,writeBuf,HID_REPORT_SIZE+1);

    //HID write was not successful
    if (res == -1) {
        HIDDisconnect();
        Debug("HID Write Failed");
        return false;
    }

    //Read out the feature report
    res = hid_read_timeout(handle, readBuf, HID_REPORT_SIZE, TIMEOUT);

    if (res != HID_REPORT_SIZE) {
        Debug("HID Read Failed");
        return false;
    } else  {//read was successful, decode the data
        if (readBuf[i++] == BOX_MSG_SYSTEM_INFO) {

            if (Decode_BoxInfo_Message((char*) readBuf, &info) == false) {
                Debug("BOX_INFO message failed");
                return false;
            }
        }
    }

    return true;
}

bool Box::ReadWaypointData(int clueIndex, Waypoint_t *w, int tries) {

    //Read out the waypoint data
    if (RequestClueInfo(clueIndex, w, tries) == false) return false;

    for (int i=0;i<NUM_CLUE_LINES;i++) {
        if (RequestClueHint(clueIndex, w, i, tries) == false) return false;
    }

    return true;
}

bool Box::WriteWaypointData(int clueIndex, Waypoint_t *w, int tries) {

    /*
    //Write the waypoint data
    if (SetClueInfo(clueIndex, w, tries) == false) return false;

    for (int i=0;i<NUM_CLUE_LINES;i++) {
        if (SetClueHint(clueIndex, w, i, tries) == false) return false;
    }
    */

    return true;
}

/*
bool Box::SetClueInfo(int clueIndex, Waypoint *w, int tries)
{
    bool result = false;

    do
    {
        result = SetClueInfo(clueIndex, w);
        tries--;
        Sleep(10);
    } while (result == false && tries > 0);

    return result;
}
*/

/* Send settings for a particular clue */

/*
bool Box::SetClueInfo(int clueIndex, Waypoint *w)
{
    if (w == NULL) return false;

    int res = -1;
    int i = 0;

    if (!HIDConnect()) return false;

    qDebug() << "saving clue" << clueIndex;

    writeBuf[i++] = 0;
    writeBuf[i++] = BOX_MSG_SET_CLUE_INFO;
    writeBuf[i++] = clueIndex;

    QString info = "";

    info += QString::number(w->lat,'f',10) + ",";
    info += QString::number(w->lng,'f',10) + ",";
    info += QString::number(w->threshold) + ",";
    info += QString::number(w->type) + ",";
    info += QString::number(w->options);

    for (int j=0;j<info.count();j++)
    {
        writeBuf[i++] = (unsigned char) info.at(j).toLatin1();
    }

    writeBuf[i++] = 0;

    res = hid_write(handle, writeBuf, HID_REPORT_SIZE + 1);

    qDebug() << "res:" << res;

    if (res != (HID_REPORT_SIZE + 1))
    {
        return false;
    }

    //Now read the clue info back out to make sure it's the same

    Waypoint w_tmp;

    if (!this->RequestClueInfo(clueIndex, &w_tmp))
    {
        //Couldn't read data
        return false;
    }

    qDebug() << w->lat << w->lng;

    return true;
}
*/

bool Box::RequestClueInfo(int clueIndex, Waypoint_t *w, int tries)
{
    bool result = false;

    do
    {
        result = RequestClueInfo(clueIndex, w);
        tries--;
        Sleep(10);
    } while (result == false && tries > 0);

    return result;
}

/* Request information on a particular clue */
bool Box::RequestClueInfo(int clueIndex, Waypoint_t *w)
{
    int res = -1;
    int i = 0;

    Debug("RequestClueInfo - " + QString::number(clueIndex));

    if (w == NULL) {
        Debug("Waypoint pointer is NULL");
        return false;
    }

    if (HIDConnect() == false) {
        Debug("HIDConnect failed");
        return false;
    }

    //Write clue info to the box
    writeBuf[i++] = 0;
    writeBuf[i++] = BOX_MSG_REQUEST_CLUE_INFO;
    writeBuf[i++] = clueIndex;

    res = hid_write(handle, writeBuf, HID_REPORT_SIZE+1);

    if (res == -1) {//write failed
        Debug("HIDWrite failed");
        HIDDisconnect();
        return false;
    }

    //read the dataz back
    res = hid_read_timeout(handle,readBuf,HID_REPORT_SIZE,TIMEOUT);

    HIDDisconnect();

    if (res != HID_REPORT_SIZE) {//read failed
        Debug("HIDRead failed");
        return false;
    }

    else
    {
        if (Decode_Waypoint_Message((char*) readBuf, w)) {
            qDebug() << "success!";

            qDebug() << w->lat;
            qDebug() << w->lng;

            return true;
        } else {
            qDebug() << "fail";
        }
        return false;
    }

    return true;
}

bool Box::RequestClueHint(int clueIndex, Waypoint_t *w, int line, int tries)
{
    bool result = false;

    do
    {
        result = RequestClueHint(clueIndex, w, line);
        tries--;
        Sleep(10);
    } while (result == false && tries > 0);

    return result;
}


bool Box::RequestClueHint(int clueIndex, Waypoint_t *w, int line)
{
    Debug("RequestClueHint() - " + QString::number(clueIndex) + " / " + QString::number(line));

    if (w == NULL) {
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
        Debug("HIDConnect failed");
        return false;
    }

    //Write clue info to the box
    writeBuf[i++] = 0;
    writeBuf[i++] = BOX_MSG_REQUEST_CLUE_LINE;
    writeBuf[i++] = clueIndex;
    writeBuf[i++] = line;

    res = hid_write(handle, writeBuf, HID_REPORT_SIZE+1);

    if (res != (HID_REPORT_SIZE + 1)) {
        Debug("HIDWrite failed");
        return false;
    }

    //read the dataz back
    res = hid_read_timeout(handle,readBuf,HID_REPORT_SIZE,TIMEOUT);

    if (res != HID_REPORT_SIZE) {
        Debug("HIDRead failed");
        return false;
    } else {

        if ((readBuf[0] == BOX_MSG_CLUE_LINE) &&
            (readBuf[1] == clueIndex) &&
            (readBuf[2] == line)) {

            Decode_WaypointClue_Message((char*) readBuf, line, w);

            return true;
        } else {
            Debug("Response doesn't match");
            return false;
        }
    }

    return false;
}

bool Box::SetClueHint(int clueIndex, Waypoint_t *w, int line, int tries)
{
    bool result = false;

    do
    {
        result = SetClueHint(clueIndex, w, line);
        tries--;
        Sleep(10); //give up control for a bit
    } while (result == false && tries > 0);

    return result;
}

bool Box::SetClueHint(int clueIndex, Waypoint_t *w, int line)
{
    Debug("SetClueHint - " + QString::number(clueIndex) + " / " + QString::number(line));

    if (w == NULL) {
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
        Debug("HIDConnect failed");
        return false;
    }

    writeBuf[i++] = 0;
    writeBuf[i++] = BOX_MSG_CLUE_LINE;
    writeBuf[i++] = clueIndex;
    writeBuf[i++] = line;

    //Append the clue line
    QString clueText = Waypoint_GetLineText(w, line);

    for (int j=0;j<clueText.size();j++) {
        writeBuf[i++] = (unsigned char) clueText.at(j).toLatin1();
    }

    //Append a zero
    writeBuf[i++] = 0;

    res = hid_write(handle, writeBuf, HID_REPORT_SIZE + 1);

    //Couldn't transmit the data
    if (res == -1) {
        Debug("HIDWrite failed");
        return false;
    }

    //Make a temp waypoint and read it back
    Waypoint_t wtemp;

    if (RequestClueHint(clueIndex, &wtemp, line, MAX_TRIES) == false) {
        Debug("RequestClueHint failed!");
        return false;
    }

    QString clue2 = Waypoint_GetLineText(&wtemp, line);

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

    writeBuf[i++] = 0x00;
    writeBuf[i++] = BOX_MSG_NEXT_CLUE;

    res = hid_write(handle, writeBuf, HID_REPORT_SIZE + 1);

    if (res == -1) return false;

    return RequestBoxInfo();
}

bool Box::SkipToPrevious()
{
    int res;

    int i = 0;

    if (HIDConnect() == false) return false;

    writeBuf[i++] = 0x00;
    writeBuf[i++] = BOX_MSG_PREV_CLUE;

    res = hid_write(handle, writeBuf, HID_REPORT_SIZE + 1);

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
    if (nClues < 0 || nClues > MAX_CLUES) return false;
    int res;

    int i = 0;

//    qDebug() << "Setting clue count:" << nClues;

    if (HIDConnect() == false) return false;

    writeBuf[i++] = 0x00;
    writeBuf[i++] = BOX_MSG_SET_NUMBER_OF_CLUES;
    writeBuf[i++] = nClues & 0xFF;

    res = hid_write(handle, writeBuf, HID_REPORT_SIZE + 1);

    if (res != (HID_REPORT_SIZE + 1))
    {
//        qDebug() << "Couldn't write nClues";
        return false;
    }

    if (!RequestBoxInfo())
    {
//        qDebug() << "Couldn't read box info";
        return false;
    }

    if (nClues != info.totalClues)
    {
//        qDebug() << "Clue count mismatch" << numberOfClues;
        return false;
    }

    return true;
}
