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
ClueList clues;

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

    connect(ui->saveButton,SIGNAL(released()),this,SLOT(saveClues()));
    connect(ui->loadButton,SIGNAL(released()),this,SLOT(loadClues()));
    connect(ui->pushButton,SIGNAL(released()),this,SLOT(clearMap()));
    connect(ui->fitMap,SIGNAL(released()),this,SLOT(jsFitMapToClues()));

    connect(ui->selectFirst,SIGNAL(released()),&clues,SLOT(SelectFirst()));
    connect(ui->selectLast,SIGNAL(released()),&clues,SLOT(SelectLast()));
    connect(ui->selectNext,SIGNAL(released()),&clues,SLOT(SelectNext()));
    connect(ui->selectPrev,SIGNAL(released()),&clues,SLOT(SelectPrev()));

    connect(ui->setThreshold,SIGNAL(released()),this,SLOT(setThreshold()));

    connect(ui->moveDown,SIGNAL(released()),&clues,SLOT(MoveClueDown()));
    connect(ui->moveUp,SIGNAL(released()),&clues,SLOT(MoveClueUp()));
    connect(ui->makeFirst,SIGNAL(released()),&clues,SLOT(MoveClueFirst()));
    connect(ui->makeLast,SIGNAL(released()),&clues,SLOT(MoveClueLast()));

    //Box commands
    connect(ui->boxUnlock,SIGNAL(released()),&box,SLOT(Unlock()));
    connect(ui->boxLock,SIGNAL(released()),&box,SLOT(Lock()));
    connect(ui->boxSkipToNextClue,SIGNAL(released()),&box,SLOT(SkipToNext()));
    connect(ui->boxSkipToPrevClue,SIGNAL(released()),&box,SLOT(SkipToPrevious()));
    connect(ui->boxUpload,SIGNAL(released()),this,SLOT(uploadClues()));
    connect(ui->boxDownload,SIGNAL(released()),this,SLOT(downloadClues()));

    connect(ui->bootload, SIGNAL(released()), this, SLOT(bootload()));
    connect(ui->clearText, SIGNAL(released()), this, SLOT(clearText()));

    connect(&clues,SIGNAL(clueUpdated()),this,SLOT(updateClues()));

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
    ui->clueType->addItem("Show location");
    ui->clueType->addItem("Warmer / Coolor");
    ui->clueType->addItem("Show heading (deg)");
    ui->clueType->addItem("Cardinal directions");

    connect(ui->clueType,SIGNAL(currentIndexChanged(int)),this,SLOT(clueTypeChanged(int)));
    connect(ui->centerText,SIGNAL(released()),this,SLOT(clueOptionsChanged()));

    ui->clueTable->clear();

    updateClues();
}

void MainWindow::incrementProgress() {
    if (downloadProgress != NULL && downloadProgress->isVisible()) {

        if (downloadProgress->value() < downloadProgress->maximum()) {
            downloadProgress->setValue(downloadProgress->value() + 1);
        }

        QApplication::processEvents();
    }
}

void MainWindow::cancelUploadDownload()
{
    downloading = false;
    uploading = false;

    if (downloadProgress != NULL && downloadProgress->isVisible()) {
        downloadProgress->cancel();
        downloadProgress->close();
    }
}

void MainWindow::downloadClues() {
    if (downloading || uploading) return;

    if (!box.connected) return;

    QMessageBox confirm;

    if (clues.ClueCount() == 0){
        confirm.setWindowTitle("No Clues!");
        confirm.setText("Make some clues before downloading");
        confirm.setStandardButtons(QMessageBox::Ok);

        confirm.exec();

        return;
    }

    confirm.setWindowTitle("Download?");
    confirm.setText("Do you want to download clues to the box?");
    confirm.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);

    int res = confirm.exec();

    if (res != QMessageBox::Ok) return;

    res = downloadAllClues();

    QMessageBox mb;
    mb.setStandardButtons(QMessageBox::Ok);

    if (!res) {
        mb.setWindowTitle("Download Failed");
        mb.setText("Error downloading clues to box");
    } else {
        mb.setWindowTitle("Download Success");
        mb.setText("Clues were successfully downloaded to box");
    }

    mb.exec();
}

void MainWindow::clearText()
{
    QTableWidgetItem *item;

    for (int i=0;i<NUM_CLUE_LINES;i++)
    {
        item = ui->clueTable->item(i,0);

        if (item == NULL)
            continue;

        item->setText("");
    }

    saveCurrentClue();
    updateClues();
}

void MainWindow::bootload()
{
    QMessageBox mbox;
    mbox.setWindowTitle("Bootload?");
    mbox.setText("Are you sure you want to place the box into bootload mode?");
    mbox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    mbox.setButtonText(QMessageBox::Ok, "Bootload");

    if (mbox.exec() == QMessageBox::Ok)
    {
        box.ResetIntoBootloader();
    }
}

bool MainWindow::downloadAllClues() {

    downloading = true;

    downloadProgress = new QProgressDialog("Downloading Clues ...","Cancel",0,box.info.totalClues+2,this);

    downloadProgress->setWindowModality(Qt::WindowModal);

    connect(downloadProgress,SIGNAL(canceled()),this,SLOT(cancelUploadDownload()));
    connect(downloadProgress,SIGNAL(rejected()),this,SLOT(cancelUploadDownload()));
    connect(downloadProgress,SIGNAL(accepted()),this,SLOT(cancelUploadDownload()));

    downloadProgress->show();

    bool result = true;
    int TRIES = 5;

    //Invalidate the clues

    /*
    result = box.SetNumberOfClues(0, TRIES);

    if (!result) {
        cancelUploadDownload();
        return false;
    }
    */

    //Write the WELCOME message
    result = box.WriteClueData(BOX_WELCOME_MSG, &clues.welcomeMessage, TRIES);

    if (!result) {
        cancelUploadDownload();
        return false;
    }

    incrementProgress();

    //Write the COMPLETE message
    result = box.WriteClueData(BOX_COMPLETE_MSG, &clues.completeMessage, TRIES);

    if (!result) {
        cancelUploadDownload();
        return false;
    }

    incrementProgress();

    //Go through all the waypoints

    for (int i=0;i<clues.ClueCount();i++) {
        if (!downloading) {
            cancelUploadDownload();
            return false;
        }

        result = box.WriteClueData(i+1, clues.GetClueAtIndex(i+1),TRIES);

        if (!result) {
            cancelUploadDownload();
            return false;
        }

        incrementProgress();
    }

    //Write the number of clues
    result = box.SetNumberOfClues(clues.ClueCount(), TRIES);

    if (!result) {
        cancelUploadDownload();
        return false;
    }

    //Validate the clues

    cancelUploadDownload();

    return true;
}

void MainWindow::uploadClues()
{
    if (downloading || uploading) return;

    if (!box.connected) return;

    QMessageBox confirm;
    confirm.setWindowTitle("Upload?");
    confirm.setText("Do you want to upload clues from the box?\nThis will overwrite clues on the map.");
    confirm.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);

    int res = confirm.exec();

    if (res != QMessageBox::Ok) return;

    res = uploadAllClues();

    QMessageBox mb;
    mb.setStandardButtons(QMessageBox::Ok);

    if (!res) {
        mb.setWindowTitle("Upload Failed");
        mb.setText("Error uploading clues from box");

        clues.Reset();
    } else {
        mb.setWindowTitle("Upload Success");
        mb.setText("Clues were successfully uploaded from box");

        clues.SelectClue(BOX_WELCOME_MSG);
    }

    mb.exec();
}

bool MainWindow::uploadAllClues() {

    uploading = true;

    downloadProgress = new QProgressDialog("Uploading Clues ...","Cancel",0,box.info.totalClues+2,this);

    downloadProgress->setWindowModality(Qt::WindowModal);

    connect(downloadProgress,SIGNAL(canceled()),this,SLOT(cancelUploadDownload()));
    connect(downloadProgress,SIGNAL(rejected()),this,SLOT(cancelUploadDownload()));
    connect(downloadProgress,SIGNAL(accepted()),this,SLOT(cancelUploadDownload()));

    downloadProgress->show();

    //Clear the local waypoints...
    clues.Reset();

    bool result = true;

    int TRIES = 5;

    //Read out the 'welcome' message

    result = box.ReadClueData(BOX_WELCOME_MSG,&clues.welcomeMessage,TRIES);

    if (!result) {
        cancelUploadDownload();
        return false;
    }

    incrementProgress();

    //Read out the completion message
    result = box.ReadClueData(BOX_COMPLETE_MSG,&clues.completeMessage,TRIES);

    if (!result) {
        cancelUploadDownload();
        return false;
    }

    incrementProgress();

    Clue_t c;


    for (int i=0;i<box.info.totalClues;i++) {

        if (!uploading) {
            cancelUploadDownload();
            return false;
        }

        Clue_Init(&c);

        result = box.ReadClueData(i+1, &c, TRIES);

        if (!result) {
            cancelUploadDownload();
            return false;
        }

        clues.AddClue(c);

        incrementProgress();
    }

    cancelUploadDownload();

    return true;
}

void MainWindow::jsFitMapToClues()
{
    if (clues.ClueCount() > 0) {
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

    Clue_t *c = clues.GetCurrentClue();

    if (c == NULL) return;

    for (int i=0;i<NUM_CLUE_LINES;i++)
    {
        if (ui->clueTable->item(i,0) == NULL)
        {
            line = "";
        }
        else
        {
            line = ui->clueTable->item(i,0)->text();
        }

        Clue_SetLineText(c, i, line);
    }
}

void MainWindow::reloadClueTable()
{
    clueTableBusy = true;

    QString line;
    Clue_t *c = clues.GetCurrentClue();

    if (c == NULL) return;

    QTableWidgetItem *item;

    ui->clueTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (int i=0;i<NUM_CLUE_LINES;i++)
    {
        item = ui->clueTable->item(i,0);

        if (item == NULL)
        {
            item = new QTableWidgetItem("");
            ui->clueTable->setItem(i,0,item);
        }

        line = Clue_GetLineText(c, i);
        item->setText(line);

        if (c->waypoint.options.centerText) {
            item->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
        } else {
            item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
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
        Clue_t *c = clues.GetCurrentClue();

        if (c != NULL)
            c->waypoint.type = (ClueTypes) newType;

        updateClues();
    }
}

void MainWindow::clueOptionsChanged()
{

    Clue_t *c = clues.GetCurrentClue();

    if (c == NULL) return;

    //Center text?
    if (ui->centerText->isChecked())
    {
        c->waypoint.options.centerText = 1;
    }
    else
    {
        c->waypoint.options.centerText = 0;
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
        ui->nBoxClues->setText("---");
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

        ui->nBoxClues->setText(QString::number(box.info.totalClues));
    }

    ui->boxStatus->setText(connectionString);

    QString s = "Box not connected";

    if (box.connected) {
        switch (box.info.currentClue) {
        case BOX_WELCOME_MSG:
            s = "Welcome Message";
            break;
        case BOX_COMPLETE_MSG:
            s = "Completion Message";
            break;
        default:
            s = "Clue " + QString::number(box.info.currentClue) + " of " + QString::number(box.info.totalClues);
            break;
        }
    }

    ui->boxClueString->setText(s);

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
    reloadClueTable();

    ui->LCD->repaint();
    redrawMap();
}

void MainWindow::clearMap()
{
    bool result = okCancelDialog("Clear Clues","Are you sure you want to clear all clues?");

    if (!result) return;

    clues.Reset();

    redrawMap();
    updateClueList();
}

void MainWindow::updateClueList()
{
    bool clueAvailable = clues.IsClueSelected();

    ui->latitude->setEnabled(clueAvailable);
    ui->longitude->setEnabled(clueAvailable);
    ui->setThreshold->setEnabled(clueAvailable);
    ui->threshold->setEnabled(clueAvailable);
    ui->clueType->setEnabled(clueAvailable);

    Clue_t *c = clues.GetCurrentClue();

    if (c == NULL)
        return;

    Waypoint_t *w = &c->waypoint;

    //Clue options
    ui->centerText->setChecked(w->options.centerText > 0);

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
        ui->threshold->setText(QString::number(w->threshold));
        ui->clueType->setCurrentIndex(w->type);
    }

    ui->editClues->setTitle("Edit Clues (" + QString::number(clues.ClueCount()) + " clues)");
    ui->selection->setText("Edit " + clues.CurrentClueTitle());

    switch (clues.ClueIndex()) {
    case BOX_WELCOME_MSG:
        ui->clueIndexDescriptor->setText("This message is displayed before any clues");
        break;
    case BOX_COMPLETE_MSG:
        ui->clueIndexDescriptor->setText("This is displayed when the puzzle is solved");
        break;
    default:
        ui->clueIndexDescriptor->setText("This is " + clues.CurrentClueTitle());
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

    if (clues.ValidWaypoint(lat,lng) == false) {

        mb.setWindowTitle("Too Close");
        mb.setText("Too close to an existing clue (250m)");
        mb.exec();

        return;
    }

    Clue_t c;
    Clue_Init(&c);

    c.waypoint.lat = lat;
    c.waypoint.lng = lng;

    clues.AddClue(c);
}

void MainWindow::clueSelectionChanged(int clue)
{
    saveCurrentClue();

    clues.SelectClue(clue + 1); //first clue starts at 1
}

void MainWindow::clueDeleted(int clue)
{
    bool result = okCancelDialog("Delete Clue?","Are you sure you want to delete this clue?");

    if (!result) return;

    if (clues.DeleteClue(clue) == false) return;

    updateClues();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    //Stop the box thread
    box.running = false;
    box.wait();

    //Save clue list to temp file
    clues.SaveToFile("autosave.clue");

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
    if (clue <= clues.ClueCount()) {

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
                Clue_t *c = clues.GetClueAtIndex(clue + 1);

                if (c != NULL)
                {
                    c->waypoint.lat = lat;
                    c->waypoint.lng = lng;
                }
            }
        }
    }

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

void MainWindow::jsSelectMarker()
{

    QString js = "selectClue(" + QString::number(clues.ClueIndex() - 1)+");";

    jsExecute(js);

}

void MainWindow::redrawMap()
{
    jsClearMap();

    foreach (Clue_t c, clues.clues)
    {
        jsAddMarker(c.waypoint.lat,c.waypoint.lng,c.waypoint.threshold);
    }

    //set selected marker
    jsSelectMarker();
    jsUpdateMap();
}

//Set the threshold distance for the currently selected clue
void MainWindow::setThreshold()
{
    bool ok;

    Clue_t *c = clues.GetCurrentClue();

    if (c == NULL) return;

    Waypoint_t *wp = &c->waypoint;

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

    if (filename.endsWith(".clue"))
    {
        clues.LoadFromFile(filename);
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
    if (clues.clues.count() == 0) {

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
        clues.SaveToFile(filename);
        Debug("Saving clues to " + filename);
    }
}
