#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWebView>
#include <QWebFrame>
#include <QFileDialog>
#include <qmath.h>
#include <QMessageBox>
#include <QFileInfo>
#include <QDebug>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QKeyEvent>
#include <QProgressDialog>
#include "qledindicator/qledindicator.h"

#include "waypoints.h"
#include "boxinterface.h"

#include "ILI9340_font.h"

#include "debug.h"

//Global var
Box box;
WaypointList waypoints;

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


    return s;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    downloading = false;
    uploading = false;

    clueTableBusy = false;

    connect(ui->webView->page()->mainFrame(),SIGNAL(javaScriptWindowObjectCleared()),
            this,
            SLOT(jsCleared()));

    connect(ui->saveButton,SIGNAL(clicked()),this,SLOT(saveClues()));
    connect(ui->loadButton,SIGNAL(clicked()),this,SLOT(loadClues()));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(clearMap()));
    connect(ui->fitMap,SIGNAL(clicked()),this,SLOT(jsFitMapToClues()));

    connect(ui->selectFirst,SIGNAL(released()),&waypoints,SLOT(SelectFirst()));
    connect(ui->selectLast,SIGNAL(released()),&waypoints,SLOT(SelectLast()));
    connect(ui->selectNext,SIGNAL(released()),&waypoints,SLOT(SelectNext()));
    connect(ui->selectPrev,SIGNAL(released()),&waypoints,SLOT(SelectPrev()));

    connect(ui->setThreshold,SIGNAL(clicked()),this,SLOT(setThreshold()));

    connect(ui->moveDown,SIGNAL(clicked()),&waypoints,SLOT(MoveClueDown()));
    connect(ui->moveUp,SIGNAL(clicked()),&waypoints,SLOT(MoveClueUp()));
    connect(ui->makeFirst,SIGNAL(clicked()),&waypoints,SLOT(MoveClueFirst()));
    connect(ui->makeLast,SIGNAL(clicked()),&waypoints,SLOT(MoveClueLast()));

    //Box commands
    connect(ui->boxUnlock,SIGNAL(clicked()),&box,SLOT(Unlock()));
    connect(ui->boxLock,SIGNAL(clicked()),&box,SLOT(Lock()));
    connect(ui->boxSkipToNextClue,SIGNAL(clicked()),&box,SLOT(SkipToNext()));
    connect(ui->boxSkipToPrevClue,SIGNAL(clicked()),&box,SLOT(SkipToPrevious()));
    connect(ui->boxUpload,SIGNAL(clicked()),this,SLOT(uploadClues()));
    connect(ui->boxDownload,SIGNAL(clicked()),this,SLOT(downloadClues()));

    connect(&waypoints,SIGNAL(clueUpdated()),this,SLOT(updateClues()));

    setupClueTable();

    connect(ui->clueTable,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(cluesEdited(QTableWidgetItem*)));

    QUrl url("qrc:/mapview.html");

    ui->webView->load(url);

    jsCleared();

    updateClueList();

    setWindowTitle("Reverse Geocache");

    //start the box interface
    box.start();

    refreshTimer = new QTimer(this);
    connect(refreshTimer,SIGNAL(timeout()),this,SLOT(refreshDisplay()));
    refreshTimer->start(500); //2Hz

    //Add options to clue type box
    ui->clueType->addItem("No extra hint");
    ui->clueType->addItem("Show distance");
    ui->clueType->addItem("Warmer / Coolor");
    ui->clueType->addItem("Show heading (deg)");
    ui->clueType->addItem("Cardinal directions");

    connect(ui->clueType,SIGNAL(currentIndexChanged(int)),this,SLOT(clueTypeChanged(int)));
    connect(ui->centerText,SIGNAL(clicked()),this,SLOT(clueOptionsChanged()));

    ui->clueTable->clear();

    updateClues();
}

void MainWindow::cancelUploadDownload()
{
    downloading = false;
    uploading = false;
}

void MainWindow::downloadClues()
{
    int MAX_TRIES = 5;

    if (uploading || downloading) return;

    if (!box.connected) return;

    QMessageBox confirm;
    confirm.setWindowTitle("Upload?");
    confirm.setText("Do you want to upload clues from the box?\nThis will overwrite clues on the map.");
    confirm.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);

    int res = confirm.exec();

    if (res != QMessageBox::Ok) return;

    downloading = true;

    QProgressDialog dialog("Downloading...","Cancel", 0, ((box.info.totalClues + 2) * NUM_CLUE_LINES), this);
    dialog.setWindowModality(Qt::WindowModal);

    connect(&dialog,SIGNAL(canceled()),this,SLOT(cancelUploadDownload()));
    connect(&dialog,SIGNAL(rejected()),this,SLOT(cancelUploadDownload()));
    connect(&dialog,SIGNAL(accepted()),this,SLOT(cancelUploadDownload()));

    dialog.show();

    bool result = true;

    //Set the number of clues to zero
    result = box.SetNumberOfClues(0, MAX_TRIES);

    //Download each of the waypoints
    if (result)
    {
        /*
        for (int i=0;i<box.waypoints.count();i++)
        {
            if (!downloading) break;

            QApplication::processEvents();

            result = box.SetClueInfo(i, &box.waypoints[i], MAX_TRIES);

//            qDebug() << "Download Clue Info:" << result;

            if (!result) //Couldn't set the box info
            {
                break;
            }

            for (int j=0;j<NUM_LINES;j++)
            {
                if (!downloading) break;

                dialog.setValue(dialog.value() + 1);

                QApplication::processEvents();

                result = box.SetClueHint(i, &box.waypoints[i], j, MAX_TRIES);

//                qDebug() << "Download Clue Hint:" << result;

                if (!result) break;

                Sleep(20);
            }

            if (!result) break;

            Sleep(10);
        }

        box.SetNumberOfClues(box.waypoints.count());

        */
    }

    if (result) //good so far
    {
        //Download the welcome message

        /*
        for (int i=0;i<NUM_LINES;i++)
        {
            if (!downloading) break;

            result = box.SetClueHint(START_MESSAGE, &box.welcomeMessage, i, MAX_TRIES);

            if (!result) break;

            dialog.setValue(dialog.value() + 1);

            QApplication::processEvents();

            Sleep(20);
        }

        */
    }

    if (result) //good so far
    {
        /*
        for (int i=0;i<NUM_LINES;i++)
        {
            if (!downloading) break;

            result = box.SetClueHint(END_MESSAGE, &box.completeMessage, i, MAX_TRIES);

            if (!result) break;

            dialog.setValue(dialog.value() + 1);

            QApplication::processEvents();

            Sleep(20);
        }
        */
    }

    //Finally, set the number of clues!!!
    if (result)
    {
//        result = box.SetNumberOfClues(box.waypoints.count(), MAX_TRIES);
    }


    dialog.cancel();
    dialog.hide();

    downloading = false;

    QMessageBox msg_box;

    msg_box.setStandardButtons(QMessageBox::Ok);

    if (result)
    {
        msg_box.setWindowTitle("Success!");
        msg_box.setText("Downloaded waypoints to box");
    }
    else
    {
        msg_box.setWindowTitle("Download Failed");
        msg_box.setText("Error downloading clues");
    }

    msg_box.exec();
}

void MainWindow::uploadClues()
{

    int MAX_TRIES = 5;

    if (downloading || uploading) return;

    if (!box.connected) return;

    QMessageBox confirm;
    confirm.setWindowTitle("Upload?");
    confirm.setText("Do you want to upload clues from the box?\nThis will overwrite clues on the map.");
    confirm.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);

    int res = confirm.exec();

    if (res != QMessageBox::Ok) return;

    /*
    uploading = true;

    QProgressDialog dialog("Uploading...","Cancel", 0, ((box.info.totalClues + 2) * NUM_CLUE_LINES), this);
    dialog.setWindowModality(Qt::WindowModal);

    connect(&dialog,SIGNAL(canceled()),this,SLOT(cancelUploadDownload()));
    connect(&dialog,SIGNAL(rejected()),this,SLOT(cancelUploadDownload()));
    connect(&dialog,SIGNAL(accepted()),this,SLOT(cancelUploadDownload()));

    dialog.show();

    //Clear the local waypoints...

    box.waypoints.clear();

    bool result = true;

    */

    /*
    for (int i=0;i<box.numberOfClues;i++)
    {
        Waypoint w;

        if (!uploading) break;

        result = box.RequestClueInfo(i, &w, MAX_TRIES);

        if (!result) break;

        for (int j=0;j<NUM_LINES;j++)
        {
            result = box.RequestClueHint(i, &w, j, MAX_TRIES);
            if (!result) break;

            dialog.setValue(dialog.value() + 1);
            QApplication::processEvents();

            Sleep(20);

        }

        if (!result) break;

        box.waypoints.append(w);

        Sleep(20);
    }

    */

    /*
    //All clues have been uploaded
    //Now get the welcome message
    if (result)
    {
        for (int i=0;i<NUM_LINES;i++)
        {
            result = box.RequestClueHint(START_MESSAGE, &box.welcomeMessage, i, MAX_TRIES);

            if (!result) break;

            dialog.setValue(dialog.value() + 1);
            QApplication::processEvents();
            Sleep(20);
        }
    }

    if (result)
    {
        for (int i=0;i<NUM_LINES;i++)
        {
            result = box.RequestClueHint(END_MESSAGE, &box.completeMessage, i, MAX_TRIES);

            if (!result) break;

            dialog.setValue(dialog.value() + 1);
            QApplication::processEvents();
            Sleep(20);
        }
    }

    dialog.cancel();
    dialog.close();

    uploading = false;

    QMessageBox b;

    b.setStandardButtons(QMessageBox::Ok);

    if (result)
    {
        b.setWindowTitle("Success!");
        b.setText("Uploaded waypoints from box");
    }
    else
    {
        b.setWindowTitle("Upload Failed");
        b.setText("Error uploading clues");
    }

    b.exec();

    this->refreshDisplay();
    this->updateClueList();
    this->redrawMap();

    */
}

void MainWindow::jsFitMapToClues()
{
    if (box.info.totalClues > 0)
    {
        jsExecute("reframe();");
    }
}

void MainWindow::setupClueTable()
{
    ui->clueTable->setColumnWidth(0,ui->clueTable->width());

    ui->clueTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    for (int i=0;i<7;i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem("");
        ui->clueTable->setItem(i,0,item);
        ui->clueTable->setRowHeight(i,25);

        item = new QTableWidgetItem("");
    }
}

void MainWindow::cluesEdited(QTableWidgetItem *item)
{
    if (!clueTableBusy)
    {
        saveCurrentClue();

        updateClues();
    }
}

/* Extract clue lines from the table and save to the given waypoint */
void MainWindow::saveCurrentClue()
{
    QString line;

    Waypoint_t *w = waypoints.GetCurrentClue();

    if (w == NULL) return;

    for (int i=0;i<NUM_CLUE_LINES;i++)
    {
        if (ui->clueTable->item(i,0) == NULL)
        {
            line = "";
        }
        else
        {
            line = ui->clueTable->item(i,0)->text();

            line = escapeClueString(line);
        }

        while (line_width(line.toLocal8Bit().data()) > 310)
        {
            line.chop(1);
        }

        Waypoint_SetLineText(w, i, line);
    }
}

void MainWindow::reloadClueTable()
{
    clueTableBusy = true;

    QString line;
    Waypoint_t *w = waypoints.GetCurrentClue();

    if (w == NULL) return;

    for (int i=0;i<NUM_CLUE_LINES;i++)
    {
        if (ui->clueTable->item(i,0) == NULL)
        {
            ui->clueTable->setItem(i,0,new QTableWidgetItem(""));
        }

        line = Waypoint_GetLineText(w, i);
        ui->clueTable->item(i,0)->setText(line);

        if ((w->options & CLUE_OPTION_CENTER_TEXT) > 0) {
            ui->clueTable->item(i,0)->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
        } else {
            ui->clueTable->item(i,0)->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        }
    }

    clueTableBusy = false;
}

bool MainWindow::okCancelDialog(QString title, QString msg)
{
    QMessageBox box;
    box.setWindowTitle(title);
    box.setText(msg);

    box.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);

    return (box.exec() == QMessageBox::Ok);
}



void MainWindow::clueTypeChanged(int newType)
{
    if (newType < NUM_CLUE_TYPES)
    {
        Waypoint_t *w = waypoints.GetCurrentClue();

        w->type = newType;

        updateClues();
    }
}

void MainWindow::clueOptionsChanged()
{

    Waypoint_t *w = waypoints.GetCurrentClue();

    if (w == NULL) return;

    //Center text?
    if (ui->centerText->isChecked())
    {
        w->options |= CLUE_OPTION_CENTER_TEXT;
    }
    else
    {
        w->options &= ~CLUE_OPTION_CENTER_TEXT;
    }

    updateClues();
}

//Periodically update the box information
void MainWindow::refreshDisplay()
{
    ui->boxConnectionIndicator->setEnabled(false);
    ui->boxConnectionIndicator->setChecked(box.connected);

    QString connectionString = "Connection error";

    //Box status message
    if (!box.connected)
    {
        connectionString = "Box not connected";

        ui->boxCharge->setText("---");
        ui->boxVersion->setText("---");
    }
    else
    {
        connectionString = "Connected via USB";
        //various messages depending on box status

        //Charge indicator
        ui->boxCharge->setText(QString::number(box.info.charge) + "%");

        //Firmware info
        ui->boxVersion->setText(
                    QString::number(box.info.versionMajor) + "." +
                    QString::number(box.info.versionMinor));
    }

    ui->boxStatus->setText(connectionString);

    //Box clue status
    if (box.info.totalClues == 0)
    {
        ui->boxClueString->setText("No clues programmed");
    }
    else
    {
        QString clueString = "Clue " + QString::number(box.info.currentClue) + " of " + QString::number(box.info.totalClues);
        ui->boxClueString->setText(clueString);
    }


    //Enable box buttons based on connection status
    ui->boxLock->setEnabled(box.connected);
    ui->boxUnlock->setEnabled(box.connected);
    ui->boxSkipToNextClue->setEnabled(box.connected);
    ui->boxSkipToPrevClue->setEnabled(box.connected);
    ui->boxUpload->setEnabled(box.connected);
    ui->boxDownload->setEnabled(box.connected);
}

void MainWindow::jsCleared()
{
    ui->webView->page()->mainFrame()->addToJavaScriptWindowObject(
                "qt",
                this);
}

//Redraw all clue info
void MainWindow::updateClues() {
    updateClueList();
    redrawMap();
    reloadClueTable();

    ui->LCD->repaint();
}

void MainWindow::clearMap()
{
    bool result = okCancelDialog("Clear Clues","Are you sure you want to clear all clues?");

    if (!result) return;

    waypoints.Reset();

    redrawMap();
    updateClueList();
}

void MainWindow::updateClueList()
{
    bool clueAvailable = waypoints.IsClueSelected();

    ui->latitude->setEnabled(clueAvailable);
    ui->longitude->setEnabled(clueAvailable);
    ui->setThreshold->setEnabled(clueAvailable);
    ui->threshold->setEnabled(clueAvailable);
    ui->clueType->setEnabled(clueAvailable);

    Waypoint_t *w = waypoints.GetCurrentClue();

    ui->centerText->setChecked((w->options & CLUE_OPTION_CENTER_TEXT) > 0);

    if (!clueAvailable)
    {
        ui->latitude->setText("");
        ui->longitude->setText("");
        ui->threshold->clear();
    }
    else
    {
        ui->latitude->setText(QString::number(w->lat,'f',WAYPOINT_DECIMAL_PRECISION));
        ui->longitude->setText(QString::number(w->lng,'f',WAYPOINT_DECIMAL_PRECISION));
        ui->threshold->setText(QString::number(w->threshold,'f',1));
        ui->clueType->setCurrentIndex(w->type);
    }

    ui->editClues->setTitle("Edit Clues (" + QString::number(waypoints.ClueCount()) + " clues)");
    ui->selection->setText("Edit " + waypoints.CurrentClueTitle());

    switch (waypoints.ClueIndex()) {
    case BOX_WELCOME_MSG:
        ui->clueIndexDescriptor->setText("This message is displayed before any clues");
        break;
    case BOX_COMPLETE_MSG:
        ui->clueIndexDescriptor->setText("This is displayed when the puzzle is solved");
        break;
    default:
        ui->clueIndexDescriptor->setText("This is " + waypoints.CurrentClueTitle());
        break;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

QVariant MainWindow::jsExecute(QString js)
{
    QVariant result = ui->webView->page()->mainFrame()->evaluateJavaScript(js);

    return result;
}

/**
 * @brief MainWindow::newMarkerRequested
 * @param lat
 * @param lng
 */
void MainWindow::newMarkerRequested(double lat, double lng) {

    QMessageBox mb;
    mb.setStandardButtons(QMessageBox::Ok);

    if (box.info.totalClues >= BOX_MAX_CLUES){
        mb.setWindowTitle("Maximum Clues Reached");
        mb.setText("You have reached the maximum number of clues");

        mb.exec();

        return;
    }

    if (waypoints.ValidWaypoint(lat,lng) == false) {

        mb.setWindowTitle("Too Close");
        mb.setText("Too close to an existing clue (250m)");
        mb.exec();

        return;
    }

    Waypoint_t W;

    Waypoint_Init(&W);

    W.lat = lat;
    W.lng = lng;

    waypoints.AddWaypoint(W);
}

void MainWindow::clueSelectionChanged(int clue)
{
    saveCurrentClue();

    waypoints.SelectClue(clue + 1); //first clue starts at 1
}

void MainWindow::clueDeleted(int clue)
{
    bool result = okCancelDialog("Delete Clue?","Are you sure you want to delete this clue?");

    if (!result) return;

    /*

    if (clue >= 0 && clue < box.waypoints.count())
    {
        box.waypoints.removeAt(clue);
    }

    if (clue <= selected)
    {
        selectPrev();
    }

    */

    redrawMap();
    updateClueList();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    //Stop the box thread
    box.running = false;
    box.wait();

    //Save clue list to temp file
    waypoints.SaveToFile("autosave.clue");

//    qDebug() << "thread finished";
}

void MainWindow::getMapCenter()
{
    QString result = jsExecute("getMapCenter();").toString();

//    qDebug() << "Map Center:" << result;
}

//Callback from the map window when a particular clue is moved
void MainWindow::clueMoved(int clue)
{
    /*
    if (clue >= 0 && clue < box.waypoints.count())
    {
        //Get the position of the new clue
        QVariant result = jsExecute("getMarkerPosition("+
                                    QString::number(clue)+
                                    ");");

        //lat,lng returned as a comma-separated string
        QString latlng = result.toString();
        QStringList split = latlng.trimmed().split(",");

        if (split.length() == 2)
        {
            bool latOk = false;
            bool lngOk = false;

            double lat = split.at(0).toDouble(&latOk);
            double lng = split.at(1).toDouble(&lngOk);

            if (latOk && lngOk)
            {
                box.waypoints[clue].lat = lat;
                box.waypoints[clue].lng = lng;
            }
        }
    }

    */

    redrawMap();
    updateClueList();
}

void MainWindow::jsAddMarker(double lat, double lng, double threshold)
{
    QString js = "addMarker(";

    js += QString::number(lat,'f',WAYPOINT_DECIMAL_PRECISION);
    js += ",";
    js += QString::number(lng,'f',WAYPOINT_DECIMAL_PRECISION);
    js += ",";
    js += QString::number(threshold, 'f', 4);
    js += ");";

    jsExecute(js);
}

void MainWindow::jsSelectMarker(int selection)
{

    /*
    QString js = "selectClue(" + QString::number(selection)+");";

    jsExecute(js);
    */
}

void MainWindow::redrawMap()
{
    jsClearMap();

    foreach (Waypoint_t w, waypoints.waypoints)
    {
        jsAddMarker(w.lat,w.lng,w.threshold);
    }

    //set selected marker
    jsSelectMarker(box.info.currentClue);
    jsUpdateMap();
}

//Set the threshold distance for the currently selected clue
void MainWindow::setThreshold()
{
    bool ok;

    Waypoint_t *wp = waypoints.GetCurrentClue();

    if (wp == NULL) return;

    uint16_t threshold = QInputDialog::getInt(0,
                                               "Clue Threshold",
                                               "Set clue threshold distance (m)",
                                               wp->threshold,
                                               WAYPOINT_THRESHOLD_MINIMUM,
                                               WAYPOINT_THRESHOLD_MAXIMUM,
                                               1,
                                               &ok);
    if (ok)
    {
        wp->threshold = threshold;

        redrawMap();
        updateClueList();
    }
}


/* Load clues from a .clue file */
void MainWindow::loadClues()
{
    QString filename = QFileDialog::getOpenFileName(0,
                                                    "Load clues from file",
                                                    QDir::currentPath(),
                                                    "Clue files (*.clue)");

    if (filename.endsWith(".clue")){
        waypoints.LoadFromFile(filename);
    }

    updateClueList();
    redrawMap();
    jsFitMapToClues();
}

/* Save the list of clues to a .clue file
 * Uses the QSettings Library
 */
void MainWindow::saveClues()
{
    if (waypoints.waypoints.count() == 0) {

        QMessageBox mb;

        mb.setWindowTitle("No Clues to Save");
        mb.setText("No clues have been added!");
        mb.setStandardButtons(QMessageBox::Ok);
        mb.exec();
        return; //don't save if no clues
    }

    QString filename = QFileDialog::getSaveFileName(0,
                                                    "Save clues to file",
                                                    QDir::currentPath(),
                                                    "Clue files (*.clue)");

    if (filename.endsWith(".clue")) {
        waypoints.SaveToFile(filename);
    }
}
