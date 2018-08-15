#include "mainwindow.h"
#include <QApplication>

#include "waypoints.h"
#include "boxinterface.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    w.setupClueTable();

    if (clues.LoadFromFile("autosave.clue"))
    {
        w.updateClues();
        w.jsFitMapToClues();
    }

    return a.exec();
}
