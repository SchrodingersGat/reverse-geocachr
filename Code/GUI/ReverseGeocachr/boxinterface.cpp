#include <QDebug>
#include <stdio.h>
#include <QStringList>

#include "boxinterface.h"

#include "box_messages.h"

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
    running = true;

    while (running)
    {
        connected = RequestBoxInfo();

        Sleep(1000);
    }

    HIDDisconnect();

//    qDebug() << "Thread complete";
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

    if (HIDConnect() == false) return false; //Connection failure

    writeBuf[0] = 0x00;
    writeBuf[1] = BOX_MSG_SYSTEM_INFO;

    res = hid_write(handle,writeBuf,HID_REPORT_SIZE+1);


    //HID write was not successful
    if (res == -1)
    {
        HIDDisconnect();
//        qDebug() << "write failed";
        return false;
    }

    //Read out the feature report
    res = hid_read_timeout(handle, readBuf, HID_REPORT_SIZE, TIMEOUT);

    if (res != HID_REPORT_SIZE)
    {
//        qDebug() << "Read failed" << res;
        return false;
    }
    else //read was successful, decode the data
    {
        if (readBuf[i++] == BOX_MSG_SYSTEM_INFO)
        {
        }
    }

    return true;
}

bool Box::SetBoxInfo(int tries)
{
    bool result = false;

    do
    {
        result = SetBoxInfo();
        tries--;
        Sleep(10);
    } while (result == false && tries > 0);

    return result;
}

bool Box::SetBoxInfo()
{
    return false;
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

bool Box::RequestClueInfo(int clueIndex, Waypoint *w, int tries)
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
*/

/* Request information on a particular clue */

/*
bool Box::RequestClueInfo(int clueIndex, Waypoint *w)
{
    int res = -1;
    int i = 0;

    if (w == NULL) return false;

    if (HIDConnect() == false) return false;

    //Write clue info to the box
    writeBuf[i++] = 0;
    writeBuf[i++] = BOX_MSG_GET_CLUE_INFO;
    writeBuf[i++] = clueIndex;

    res = hid_write(handle, writeBuf, HID_REPORT_SIZE+1);

    if (res == -1) //write failed
    {
        HIDDisconnect();
        return false;
    }

    //read the dataz back
    res = hid_read_timeout(handle,readBuf,HID_REPORT_SIZE,TIMEOUT);

    HIDDisconnect();

    if (res != HID_REPORT_SIZE) //read failed
    {
        return false;
    }

    else
    {

        int index = readBuf[1];
        QString data = QString::fromLocal8Bit((const char*) &readBuf[2]);
        qDebug() << "Clue:" << index << data;

        if (readBuf[0] == BOX_MSG_GET_CLUE_INFO)
        {
            QStringList split = data.split(",");

            if (split.count() == 5)
            {
                bool latOk = false;
                bool lngOk = false;
                bool thresholdOk = false;
                bool typeOk = false;
                bool optionsOk = false;

                double lat = split.at(0).toDouble(&latOk);
                double lng = split.at(1).toDouble(&lngOk);
                int threshold = split.at(2).toInt(&thresholdOk);
                int type = split.at(3).toInt(&typeOk);
                int options = split.at(4).toInt(&optionsOk);

                if (latOk && lngOk && thresholdOk && typeOk && optionsOk)
                {
                    w->lng = lng;
                    w->lat = lat;
                    w->threshold = threshold;
                    w->type = type;
                    w->options = options;

                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }

    return true;
}

bool Box::RequestClueHint(int clueIndex, Waypoint *w, int line, int tries)
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


bool Box::RequestClueHint(int clueIndex, Waypoint *w, int line)
{
    if (w == NULL) return false;
    if (line >= NUM_LINES) return false;

    int res = -1;

    int i = 0;

    if (HIDConnect() == false)
    {
        return false;
    }

//    qDebug() << "Requesting Clue Hint" << clueIndex << line;

    //Write clue info to the box
    writeBuf[i++] = 0;
    writeBuf[i++] = BOX_MSG_GET_CLUE_LINE;
    writeBuf[i++] = clueIndex;
    writeBuf[i++] = line;

    res = hid_write(handle, writeBuf, HID_REPORT_SIZE+1);

    if (res != (HID_REPORT_SIZE + 1))
    {
//        qDebug() << "write failed" << res;
        return false;
    }

    //read the dataz back
    res = hid_read_timeout(handle,readBuf,HID_REPORT_SIZE,TIMEOUT);

    if (res != HID_REPORT_SIZE) //read failed
    {
//        qDebug() << "read failed";
        return false;
    }

    else
    {
        int i = 0;

        if (readBuf[i++] == BOX_MSG_GET_CLUE_LINE)
        {
            int index = readBuf[i++];
            int lineNum = readBuf[i++];

//            qDebug() << "response:" << index << lineNum;

            if (index == clueIndex && line == lineNum)
            {

                QString data = QString::fromLocal8Bit((const char*) &readBuf[i]);
  //              qDebug() << "Clue Line:" << index << line << data;

                w->clue[line] = data;

                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
//            qDebug() << "wrong msg returned" << "0x" + QString::number(readBuf[0],16);
            return false;
        }
    }

    return false;
}

bool Box::SetClueHint(int clueIndex, Waypoint *w, int line, int tries)
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

bool Box::SetClueHint(int clueIndex, Waypoint *w, int line)
{
    if (w == NULL) return false;
    if (line > NUM_LINES) return false;

    int res = -1;

    int i = 0;

    if (HIDConnect() == false) return false;

//    qDebug() << "saving clue line" << clueIndex << line << w->clue[line];

    writeBuf[i++] = 0;
    writeBuf[i++] = BOX_MSG_SET_CLUE_LINE;
    writeBuf[i++] = clueIndex;
    writeBuf[i++] = line;

    //Append the clue line
    for (int j=0;j<w->clue[line].size();j++)
    {
        writeBuf[i++] = (unsigned char) w->clue[line].at(j).toLatin1();
    }

    //Append a zero
    writeBuf[i++] = 0;

    res = hid_write(handle, writeBuf, HID_REPORT_SIZE + 1);

    //Couldn't transmit the data
    if (res == -1) return false;

    //Make a temp waypoint and read it back
    Waypoint wtemp;

    if (RequestClueHint(clueIndex, &wtemp, line, MAX_TRIES) == false)
    {
//        qDebug() << "Couldn't RequestClueHint";
        return false;
    }

    if (w->clue[line] == wtemp.clue[line])
    {
//        qDebug() << "Match!";
        return true;
    }
    else
    {
//        qDebug() << "No match";
//        qDebug() << w->clue[line] << "->" << wtemp.clue[line];
//        qDebug() << w->clue[line].length() << wtemp.clue[line].length();
    }

    return false;
}
*/

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
