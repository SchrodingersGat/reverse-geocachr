#include "waypoints.h"
#include "display_constants.h"
#include <QSettings>

//Global settings
const QString SETTING_NUM_CLUES = "NumberOfClues";
const QString SETTING_WELCOME_MSG = "WelcomeMsg";
const QString SETTING_CLUE = "Clue";
const QString SETTING_COMPLETE_MSG = "CompleteMsg";

//Titles for the various settings
const QString SETTING_CLUE_LAT = "Latitude";
const QString SETTING_CLUE_LNG = "Longitude";
const QString SETTING_CLUE_THRESHOLD = "Threshold";
const QString SETTING_CLUE_TYPE = "Type";
const QString SETTING_CLUE_OPTIONS = "Options";
const QString SETTING_CLUE_LINE = "Line_";

#include "debug.h"
#include "ILI9340_font.h"

ClueList::ClueList()
{
    Reset();
}

void ClueList::Reset()
{
    clues.clear();
    Clue_Init(&welcomeMessage);
    Clue_Init(&completeMessage);

    currentClue = BOX_WELCOME_MSG;

    emit clueUpdated();
}

bool ClueList::IsClueSelected()
{
    if (currentClue > 0 && currentClue <= clues.count()) return true;

    return false;
}

uint8_t ClueList::ClueIndex()
{
    return currentClue;
}

uint8_t ClueList::ClueCount()
{
    return clues.count();
}

Clue_t* ClueList::GetCurrentClue()
{
    if (currentClue > BOX_COMPLETE_MSG) currentClue = BOX_WELCOME_MSG;
    if ((currentClue > clues.count()) && (currentClue < BOX_COMPLETE_MSG)) currentClue = BOX_WELCOME_MSG;

    return GetClueAtIndex(currentClue);
}

Clue_t* ClueList::GetClueAtIndex(uint8_t index)
{
    if (index == BOX_WELCOME_MSG) return &welcomeMessage;
    if (index == BOX_COMPLETE_MSG) return &completeMessage;

    if (index <= clues.count()) {
        return &(clues[index - 1]);
    }

    return NULL;
}

QString ClueList::CurrentClueTitle()
{
    switch (currentClue)
    {
    case BOX_WELCOME_MSG:
        return "Welcome Message";
    case BOX_COMPLETE_MSG:
        return "Completion Message";
    default:
        return "Clue " + QString::number(currentClue) + " of " + QString::number(clues.count());
    }
}

QString ClueList::CurrentClueHeader()
{
    switch (currentClue)
    {
    case BOX_WELCOME_MSG:
        return "Reverse Geocache";
    case BOX_COMPLETE_MSG:
        return "Congratulations!";
    default:
        return "Clue " + QString::number(currentClue) + " of " + QString::number(clues.count());
    }
}

QString ClueList::CurrentClueFooter()
{
    switch (currentClue)
    {
    case BOX_WELCOME_MSG:
        return "";
    case BOX_COMPLETE_MSG:
        return "Complete!";
        break;
    }

    Clue_t *c = GetCurrentClue();

    if (c == NULL)
    {
        return "";
    }

    switch (c->waypoint.type)
    {
    default:
    case CLUE_NO_HINT:
        return "";
    case CLUE_SHOW_LOCATION:
        return QString::number(c->waypoint.lat,'f',8) + ", " + QString::number(c->waypoint.lng,'f',8);
    case CLUE_SHOW_DISTANCE:
        return "Distance: 1.234 km";
    case CLUE_WARMER_COOLER:
        return "Getting warmer!";
    case CLUE_SHOW_HEADING:
        return "Heading: 135 degrees";
    case CLUE_SHOW_CARDINAL:
        return "Head WNW";
    }
}

void ClueList::SelectFirst()
{
    if (clues.count() == 0) currentClue = BOX_WELCOME_MSG;
    else currentClue = 1;

    emit clueUpdated();
}

void ClueList::SelectLast()
{
    if (clues.count() == 0) currentClue = BOX_COMPLETE_MSG;
    else currentClue = clues.count();

    emit clueUpdated();
}

void ClueList::SelectPrev()
{
    if (currentClue >= BOX_COMPLETE_MSG)
    {
        currentClue = clues.count();
    }
    else if (currentClue > BOX_WELCOME_MSG)
    {
        currentClue--;
    }

    emit clueUpdated();
}

void ClueList::SelectClue(uint8_t index)
{
    if (index >= BOX_COMPLETE_MSG)
    {
        currentClue = BOX_COMPLETE_MSG;
    }
    else if (index > clues.count())
    {
        currentClue = BOX_WELCOME_MSG;
    }
    else
    {
        currentClue = index;
    }

    emit clueUpdated();
}

void ClueList::SelectNext()
{
    if (currentClue < clues.count())
    {
        currentClue++;
    }
    else
    {
        currentClue = BOX_COMPLETE_MSG;
    }

    emit clueUpdated();
}

//Swap the current clue with the one after it
void ClueList::MoveClueDown()
{

    if (currentClue == BOX_WELCOME_MSG || currentClue == BOX_COMPLETE_MSG) return;
    if (clues.count() < 2) return; //needs at least two clues

    if (currentClue >= clues.count()) return;

    Clue_t c = clues[currentClue];

    clues.removeAt(currentClue);
    clues.insert(currentClue + 1, c);

    currentClue++;

    emit clueUpdated();
}

//Swap the current clue with the one before it
void ClueList::MoveClueUp()
{
    if (currentClue == BOX_WELCOME_MSG || currentClue == BOX_COMPLETE_MSG) return;

    if (clues.count() < 2) return;  //Needs at least two clues

    if (currentClue <= 1) return; //There are no clues before this one!

    Clue_t c = clues[currentClue];

    clues.removeAt(currentClue);
    clues.insert(currentClue - 1, c);

    currentClue--;

    emit clueUpdated();
}

void ClueList::MoveClueFirst()
{
    if (currentClue == BOX_WELCOME_MSG || currentClue == BOX_COMPLETE_MSG) return;

    if (clues.count() < 2) return; //needs at least two clues

    emit clueUpdated();
}

void ClueList::MoveClueLast()
{
    if (currentClue == BOX_WELCOME_MSG || currentClue == BOX_COMPLETE_MSG) return;

    if (clues.count() < 2) return; //needs at least two clues

    emit clueUpdated();
}

bool ClueList::SaveToFile(QString filename)
{

    /*
    QSettings settings(filename, QSettings::IniFormat);

    if (!settings.isWritable()) return;

    settings.clear();

    //Number of clues
    settings.setValue(SETTING_NUM_CLUES, box.clues.count());

    //Welcome Message
    settings.beginGroup(SETTING_WELCOME_MSG);
    box.welcomeMessage.save(&settings);
    settings.endGroup();

    //Completion message
    settings.beginGroup(SETTING_COMPLETE_MSG);
    box.completeMessage.save(&settings);
    settings.endGroup();

    Waypoint *w;

    //For each of the clues
    for (int i=0;i<box.clues.count();i++)
    {
        settings.beginGroup(SETTING_CLUE + "_" + QString::number(i));

        w = &box.waypoints[i];
        w->save(&settings);

        settings.endGroup();
    }
    */
    return false;
}

bool ClueList::LoadFromFile(QString filename)
{

    /*
    QFileInfo check(filename);

    if (!check.exists() || !check.isFile()) return;

    QSettings settings(filename, QSettings::IniFormat);

    bool ok;

    int nClues = settings.value(SETTING_NUM_CLUES,0).toInt(&ok);

    if (!ok)
    {
        nClues = 0;
        //error msg here
    }

    if (nClues == 0)
    {
        //error msg here
    }

    box.clues.clear();

    //Welcome message
    settings.beginGroup(SETTING_WELCOME_MSG);
    box.welcomeMessage.load(&settings);
    settings.endGroup();

    settings.beginGroup(SETTING_COMPLETE_MSG);
    box.completeMessage.load(&settings);
    settings.endGroup();

    Waypoint w;

    //Each clue
    for (int i=0;i<nClues;i++)
    {
        settings.beginGroup(SETTING_CLUE+"_"+QString::number(i));

        if (w.load(&settings))
        {
            box.clues.append(w);
        }

        settings.endGroup();
    }
    */
    return false;
}

bool ClueList::ValidWaypoint(double lat, double lng)
{
    for (int i=0;i<clues.count();i++)
    {
        if (Waypoint_Distance(lat,lng,&(clues[i].waypoint)) < 250)
        {
            return false;
        }
    }

    return true;
}

bool ClueList::DeleteClue(uint8_t index)
{
    //This one is special in that index is zero offset

    if (index < clues.count())
    {
        clues.removeAt(index);
        return true;
    }

    return false;
}

bool ClueList::AddClue(Clue_t c)
{
    if (clues.count() >= BOX_MAX_CLUES) return false;

    if (!ValidWaypoint(c.waypoint.lat,c.waypoint.lng)) return false;

    clues.append(c);

    //Select the given waypoint
    SelectClue(clues.count());

    return true;
}

void Clue_SetLineText(Clue_t *c, uint8_t line, QString text)
{
    if (c == NULL || line >= NUM_CLUE_LINES) return;

    text = escapeClueString(text);

    for (int i=0;i<CLUE_LINE_LEN_MAX;i++)
    {
        if (i >= text.count()) c->lines[line][i] = 0;
        else c->lines[line][i] = (uint8_t) text.at(i).toLatin1();
    }

    //ensure the last char is zero-terminated
    c->lines[line][CLUE_LINE_LEN_MAX - 1] = 0;
}

QString Clue_GetLineText(Clue_t *c, uint8_t line)
{
    if (c == NULL || line >= NUM_CLUE_LINES) return "";

    QString text = "";

    for (int i=0;i<CLUE_LINE_LEN_MAX;i++)
    {
        if (c->lines[line][i] != 0)
        {
            text.append(QChar((char) c->lines[line][i]));
        }
    }

    return text;
}

QString escapeClueString(QString clue)
{
    QString s = "";
    QChar c;

    for (int i=0;i<clue.size();i++)
    {
        c = clue.at(i);

        if (c >= ' ' && c < 127)
        {
            s += c;
        }
    }

    if (s.length() >= CLUE_LINE_LEN_MAX)
    {
        s.truncate(CLUE_LINE_LEN_MAX - 1);
    }

    while (line_width(s.toLocal8Bit().data()) > LINE_MAX_WIDTH)
    {
        s.chop(1);
    }

    return s;
}
