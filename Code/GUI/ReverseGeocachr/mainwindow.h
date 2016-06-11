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
#include <QProgressDialog>

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

    QProgressDialog *downloadProgress;

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
    void jsSelectMarker();
    void jsClearMap() { jsExecute("deleteMarkers();"); }
    void jsUpdateMap() { jsExecute("redrawClues();"); }
    void jsFitMapToClues();

    void updateClues();

    //Local functions
    void clearMap();
    void updateClueList();
    void redrawMap();

    void clearText();

    void loadClues();
    void saveClues();

    void setThreshold();

    void clueTypeChanged(int newType);

    void setupClueTable();
    void reloadClueTable();

    void refreshDisplay();

    void cluesEdited(QTableWidgetItem *item);
    void saveCurrentClue();

    bool okCancelDialog(QString title, QString msg);

    void clueOptionsChanged();

    void getMapCenter();

    void downloadClues();
    bool downloadAllClues();

    void uploadClues();
    bool uploadAllClues();

    void cancelUploadDownload();

    void incrementProgress();

    void bootload();

protected:
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
