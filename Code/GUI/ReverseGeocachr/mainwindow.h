#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QVariant>
#include <QInputDialog>
#include <QCloseEvent>
#include <QTableWidget>
#include <QTimer>
#include <QTableWidgetItem>
#include <QSettings>

QString escapeClueString(QString clue);

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool clueTableBusy;

    QTimer *refreshTimer;
    
private:
    Ui::MainWindow *ui;

    bool downloading;
    bool uploading;

public slots:
    //Signals coming FROM the javascript side
    void jsCleared();
    void newMarkerRequested(double lat, double lng);

    void clueSelectionChanged(int clue);
    void clueMoved(int clue);
    void clueDeleted(int clue);

    //Signals TO the javascript side
    QVariant jsExecute(QString js);
    void jsAddMarker(double lat, double lng, double threshold);
    void jsSelectMarker(int selection);
    void jsClearMap() { jsExecute("deleteMarkers();"); }
    void jsUpdateMap() { jsExecute("redrawClues();"); }
    void jsFitMapToClues();

    //Local functions
    void clearMap();
    void updateClueList();
    void redrawMap();

    void loadClues();
    void saveClues();

    void setThreshold();

    void moveClueUp();
    void moveClueDown();
    void makeFirst();
    void makeLast();

    void clueTypeChanged(int newType);

    void setupClueTable();
    void reloadClueTable();

    void refreshDisplay();
    void updateLCD();

    void cluesEdited(QTableWidgetItem *item);
    void saveCurrentClue();

    bool okCancelDialog(QString title, QString msg);

    void clueOptionsChanged();

    void getMapCenter();

    void downloadClues();
    void uploadClues();

    void cancelUploadDownload();

protected:
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
