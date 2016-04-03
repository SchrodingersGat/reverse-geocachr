/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWebKitWidgets/QWebView>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "lcdwidget.h"
#include "qledindicator/qledindicator.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_5;
    QLabel *editClues_4;
    QSpacerItem *verticalSpacer_3;
    QLabel *editClues_6;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_4;
    QPushButton *loadButton;
    QPushButton *saveButton;
    QPushButton *moveUp;
    QPushButton *makeFirst;
    QPushButton *moveDown;
    QPushButton *makeLast;
    QPushButton *fitMap;
    QPushButton *pushButton;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_4;
    QGridLayout *gridLayout_5;
    QLineEdit *boxCharge;
    QLineEdit *boxVersion;
    QLabel *latString_2;
    QLabel *latString_3;
    QLineEdit *nBoxClues;
    QSpacerItem *horizontalSpacer_5;
    QLabel *latString_4;
    QLabel *boxStatus;
    QLedIndicator *boxConnectionIndicator;
    QLabel *boxClueString;
    QGridLayout *gridLayout_3;
    QPushButton *boxSkipToPrevClue;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *boxSkipToNextClue;
    QPushButton *boxDownload;
    QPushButton *boxUpload;
    QPushButton *boxUnlock;
    QPushButton *boxLock;
    QSpacerItem *verticalSpacer;
    QLabel *boxStatus_3;
    QLabel *boxStatus_2;
    QWebView *webView;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    LCDWidget *LCD;
    QGroupBox *editClues;
    QVBoxLayout *verticalLayout_3;
    QLabel *clueIndexDescriptor;
    QHBoxLayout *horizontalLayout;
    QPushButton *selectFirst;
    QPushButton *selectPrev;
    QLabel *selection;
    QPushButton *selectNext;
    QPushButton *selectLast;
    QTableWidget *clueTable;
    QGridLayout *gridLayout_2;
    QLabel *latString;
    QLineEdit *latitude;
    QLabel *lngString;
    QLineEdit *longitude;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lngString_2;
    QLineEdit *threshold;
    QLabel *lngString_3;
    QPushButton *setThreshold;
    QCheckBox *centerText;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lngString_4;
    QComboBox *clueType;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_2;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1159, 710);
        MainWindow->setMinimumSize(QSize(1159, 710));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setMinimumSize(QSize(260, 141));
        groupBox_3->setMaximumSize(QSize(260, 16777215));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        groupBox_3->setFont(font);
        verticalLayout_5 = new QVBoxLayout(groupBox_3);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        editClues_4 = new QLabel(groupBox_3);
        editClues_4->setObjectName(QStringLiteral("editClues_4"));
        editClues_4->setMaximumSize(QSize(251, 41));
        QFont font1;
        font1.setPointSize(9);
        font1.setBold(false);
        font1.setWeight(50);
        editClues_4->setFont(font1);

        verticalLayout_5->addWidget(editClues_4);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_3);

        editClues_6 = new QLabel(groupBox_3);
        editClues_6->setObjectName(QStringLiteral("editClues_6"));
        editClues_6->setFont(font1);

        verticalLayout_5->addWidget(editClues_6);


        verticalLayout_2->addWidget(groupBox_3);

        groupBox_6 = new QGroupBox(centralWidget);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setMinimumSize(QSize(260, 171));
        groupBox_6->setMaximumSize(QSize(260, 171));
        groupBox_6->setFont(font);
        gridLayout_4 = new QGridLayout(groupBox_6);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        loadButton = new QPushButton(groupBox_6);
        loadButton->setObjectName(QStringLiteral("loadButton"));
        QFont font2;
        font2.setPointSize(8);
        font2.setBold(false);
        font2.setWeight(50);
        loadButton->setFont(font2);

        gridLayout_4->addWidget(loadButton, 0, 0, 1, 1);

        saveButton = new QPushButton(groupBox_6);
        saveButton->setObjectName(QStringLiteral("saveButton"));
        saveButton->setFont(font2);

        gridLayout_4->addWidget(saveButton, 0, 1, 1, 1);

        moveUp = new QPushButton(groupBox_6);
        moveUp->setObjectName(QStringLiteral("moveUp"));
        moveUp->setFont(font2);

        gridLayout_4->addWidget(moveUp, 1, 0, 1, 1);

        makeFirst = new QPushButton(groupBox_6);
        makeFirst->setObjectName(QStringLiteral("makeFirst"));
        makeFirst->setFont(font2);

        gridLayout_4->addWidget(makeFirst, 1, 1, 1, 1);

        moveDown = new QPushButton(groupBox_6);
        moveDown->setObjectName(QStringLiteral("moveDown"));
        moveDown->setFont(font2);

        gridLayout_4->addWidget(moveDown, 2, 0, 1, 1);

        makeLast = new QPushButton(groupBox_6);
        makeLast->setObjectName(QStringLiteral("makeLast"));
        makeLast->setFont(font2);

        gridLayout_4->addWidget(makeLast, 2, 1, 1, 1);

        fitMap = new QPushButton(groupBox_6);
        fitMap->setObjectName(QStringLiteral("fitMap"));
        fitMap->setFont(font2);

        gridLayout_4->addWidget(fitMap, 3, 0, 1, 1);

        pushButton = new QPushButton(groupBox_6);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setFont(font2);

        gridLayout_4->addWidget(pushButton, 3, 1, 1, 1);


        verticalLayout_2->addWidget(groupBox_6);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setMinimumSize(QSize(260, 251));
        groupBox->setMaximumSize(QSize(260, 16777215));
        groupBox->setFont(font);
        verticalLayout_4 = new QVBoxLayout(groupBox);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(6);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        boxCharge = new QLineEdit(groupBox);
        boxCharge->setObjectName(QStringLiteral("boxCharge"));
        boxCharge->setEnabled(true);
        boxCharge->setMaximumSize(QSize(60, 16777215));
        boxCharge->setFont(font2);
        boxCharge->setAlignment(Qt::AlignCenter);
        boxCharge->setReadOnly(true);

        gridLayout_5->addWidget(boxCharge, 2, 1, 1, 1);

        boxVersion = new QLineEdit(groupBox);
        boxVersion->setObjectName(QStringLiteral("boxVersion"));
        boxVersion->setEnabled(true);
        boxVersion->setMaximumSize(QSize(60, 16777215));
        boxVersion->setFont(font2);
        boxVersion->setAlignment(Qt::AlignCenter);
        boxVersion->setReadOnly(true);

        gridLayout_5->addWidget(boxVersion, 3, 1, 1, 1);

        latString_2 = new QLabel(groupBox);
        latString_2->setObjectName(QStringLiteral("latString_2"));
        latString_2->setFont(font1);
        latString_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(latString_2, 2, 0, 1, 1);

        latString_3 = new QLabel(groupBox);
        latString_3->setObjectName(QStringLiteral("latString_3"));
        latString_3->setFont(font1);
        latString_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(latString_3, 3, 0, 1, 1);

        nBoxClues = new QLineEdit(groupBox);
        nBoxClues->setObjectName(QStringLiteral("nBoxClues"));
        nBoxClues->setEnabled(true);
        nBoxClues->setMaximumSize(QSize(60, 16777215));
        nBoxClues->setFont(font2);
        nBoxClues->setAlignment(Qt::AlignCenter);
        nBoxClues->setReadOnly(true);

        gridLayout_5->addWidget(nBoxClues, 1, 1, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_5, 1, 2, 1, 1);

        latString_4 = new QLabel(groupBox);
        latString_4->setObjectName(QStringLiteral("latString_4"));
        latString_4->setMinimumSize(QSize(50, 0));
        latString_4->setFont(font1);
        latString_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(latString_4, 1, 0, 1, 1);

        boxStatus = new QLabel(groupBox);
        boxStatus->setObjectName(QStringLiteral("boxStatus"));
        boxStatus->setFont(font1);

        gridLayout_5->addWidget(boxStatus, 0, 0, 1, 2);

        boxConnectionIndicator = new QLedIndicator(groupBox);
        boxConnectionIndicator->setObjectName(QStringLiteral("boxConnectionIndicator"));
        boxConnectionIndicator->setMinimumSize(QSize(20, 20));
        boxConnectionIndicator->setMaximumSize(QSize(20, 20));

        gridLayout_5->addWidget(boxConnectionIndicator, 0, 2, 1, 1);


        verticalLayout_4->addLayout(gridLayout_5);

        boxClueString = new QLabel(groupBox);
        boxClueString->setObjectName(QStringLiteral("boxClueString"));
        QFont font3;
        font3.setPointSize(9);
        font3.setBold(true);
        font3.setWeight(75);
        boxClueString->setFont(font3);

        verticalLayout_4->addWidget(boxClueString);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        boxSkipToPrevClue = new QPushButton(groupBox);
        boxSkipToPrevClue->setObjectName(QStringLiteral("boxSkipToPrevClue"));
        boxSkipToPrevClue->setFont(font2);

        gridLayout_3->addWidget(boxSkipToPrevClue, 0, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 0, 1, 1, 1);

        boxSkipToNextClue = new QPushButton(groupBox);
        boxSkipToNextClue->setObjectName(QStringLiteral("boxSkipToNextClue"));
        boxSkipToNextClue->setFont(font2);

        gridLayout_3->addWidget(boxSkipToNextClue, 0, 2, 1, 1);

        boxDownload = new QPushButton(groupBox);
        boxDownload->setObjectName(QStringLiteral("boxDownload"));
        boxDownload->setFont(font2);

        gridLayout_3->addWidget(boxDownload, 1, 2, 1, 1);

        boxUpload = new QPushButton(groupBox);
        boxUpload->setObjectName(QStringLiteral("boxUpload"));
        boxUpload->setFont(font2);

        gridLayout_3->addWidget(boxUpload, 2, 2, 1, 1);

        boxUnlock = new QPushButton(groupBox);
        boxUnlock->setObjectName(QStringLiteral("boxUnlock"));
        boxUnlock->setFont(font2);

        gridLayout_3->addWidget(boxUnlock, 2, 0, 1, 1);

        boxLock = new QPushButton(groupBox);
        boxLock->setObjectName(QStringLiteral("boxLock"));
        boxLock->setFont(font2);

        gridLayout_3->addWidget(boxLock, 1, 0, 1, 1);


        verticalLayout_4->addLayout(gridLayout_3);


        verticalLayout_2->addWidget(groupBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        boxStatus_3 = new QLabel(centralWidget);
        boxStatus_3->setObjectName(QStringLiteral("boxStatus_3"));
        boxStatus_3->setFont(font1);

        verticalLayout_2->addWidget(boxStatus_3);

        boxStatus_2 = new QLabel(centralWidget);
        boxStatus_2->setObjectName(QStringLiteral("boxStatus_2"));
        boxStatus_2->setFont(font1);

        verticalLayout_2->addWidget(boxStatus_2);


        gridLayout->addLayout(verticalLayout_2, 0, 0, 1, 1);

        webView = new QWebView(centralWidget);
        webView->setObjectName(QStringLiteral("webView"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(webView->sizePolicy().hasHeightForWidth());
        webView->setSizePolicy(sizePolicy1);
        webView->setMinimumSize(QSize(490, 550));
        webView->setUrl(QUrl(QStringLiteral("about:blank")));

        gridLayout->addWidget(webView, 0, 1, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(271, 20));
        label->setMaximumSize(QSize(271, 20));
        label->setFont(font);

        verticalLayout->addWidget(label);

        LCD = new LCDWidget(centralWidget);
        LCD->setObjectName(QStringLiteral("LCD"));
        LCD->setMinimumSize(QSize(320, 240));
        LCD->setMaximumSize(QSize(320, 240));

        verticalLayout->addWidget(LCD);

        editClues = new QGroupBox(centralWidget);
        editClues->setObjectName(QStringLiteral("editClues"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(editClues->sizePolicy().hasHeightForWidth());
        editClues->setSizePolicy(sizePolicy2);
        editClues->setMinimumSize(QSize(321, 391));
        editClues->setMaximumSize(QSize(321, 391));
        editClues->setFont(font);
        verticalLayout_3 = new QVBoxLayout(editClues);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        clueIndexDescriptor = new QLabel(editClues);
        clueIndexDescriptor->setObjectName(QStringLiteral("clueIndexDescriptor"));
        clueIndexDescriptor->setFont(font3);
        clueIndexDescriptor->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(clueIndexDescriptor);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        selectFirst = new QPushButton(editClues);
        selectFirst->setObjectName(QStringLiteral("selectFirst"));
        selectFirst->setMaximumSize(QSize(30, 16777215));
        selectFirst->setFont(font2);

        horizontalLayout->addWidget(selectFirst);

        selectPrev = new QPushButton(editClues);
        selectPrev->setObjectName(QStringLiteral("selectPrev"));
        selectPrev->setMaximumSize(QSize(30, 16777215));
        selectPrev->setFont(font2);

        horizontalLayout->addWidget(selectPrev);

        selection = new QLabel(editClues);
        selection->setObjectName(QStringLiteral("selection"));
        selection->setFont(font2);
        selection->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(selection);

        selectNext = new QPushButton(editClues);
        selectNext->setObjectName(QStringLiteral("selectNext"));
        selectNext->setMaximumSize(QSize(30, 16777215));
        selectNext->setFont(font2);

        horizontalLayout->addWidget(selectNext);

        selectLast = new QPushButton(editClues);
        selectLast->setObjectName(QStringLiteral("selectLast"));
        selectLast->setMaximumSize(QSize(30, 16777215));
        selectLast->setFont(font2);

        horizontalLayout->addWidget(selectLast);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 1);
        horizontalLayout->setStretch(2, 2);
        horizontalLayout->setStretch(3, 1);
        horizontalLayout->setStretch(4, 1);

        verticalLayout_3->addLayout(horizontalLayout);

        clueTable = new QTableWidget(editClues);
        if (clueTable->columnCount() < 1)
            clueTable->setColumnCount(1);
        if (clueTable->rowCount() < 7)
            clueTable->setRowCount(7);
        clueTable->setObjectName(QStringLiteral("clueTable"));
        clueTable->setFont(font2);
        clueTable->setRowCount(7);
        clueTable->setColumnCount(1);
        clueTable->horizontalHeader()->setVisible(false);
        clueTable->verticalHeader()->setVisible(false);

        verticalLayout_3->addWidget(clueTable);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        latString = new QLabel(editClues);
        latString->setObjectName(QStringLiteral("latString"));
        latString->setFont(font2);

        gridLayout_2->addWidget(latString, 0, 0, 1, 1);

        latitude = new QLineEdit(editClues);
        latitude->setObjectName(QStringLiteral("latitude"));
        latitude->setEnabled(true);
        latitude->setFont(font2);
        latitude->setAlignment(Qt::AlignCenter);
        latitude->setReadOnly(true);

        gridLayout_2->addWidget(latitude, 0, 1, 1, 1);

        lngString = new QLabel(editClues);
        lngString->setObjectName(QStringLiteral("lngString"));
        lngString->setFont(font2);

        gridLayout_2->addWidget(lngString, 1, 0, 1, 1);

        longitude = new QLineEdit(editClues);
        longitude->setObjectName(QStringLiteral("longitude"));
        longitude->setEnabled(true);
        longitude->setFont(font2);
        longitude->setAlignment(Qt::AlignCenter);
        longitude->setReadOnly(true);

        gridLayout_2->addWidget(longitude, 1, 1, 1, 1);


        verticalLayout_3->addLayout(gridLayout_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        lngString_2 = new QLabel(editClues);
        lngString_2->setObjectName(QStringLiteral("lngString_2"));
        lngString_2->setFont(font2);

        horizontalLayout_2->addWidget(lngString_2);

        threshold = new QLineEdit(editClues);
        threshold->setObjectName(QStringLiteral("threshold"));
        threshold->setEnabled(true);
        threshold->setFont(font2);
        threshold->setAlignment(Qt::AlignCenter);
        threshold->setReadOnly(true);

        horizontalLayout_2->addWidget(threshold);

        lngString_3 = new QLabel(editClues);
        lngString_3->setObjectName(QStringLiteral("lngString_3"));
        lngString_3->setFont(font2);

        horizontalLayout_2->addWidget(lngString_3);

        setThreshold = new QPushButton(editClues);
        setThreshold->setObjectName(QStringLiteral("setThreshold"));
        setThreshold->setFont(font2);

        horizontalLayout_2->addWidget(setThreshold);

        centerText = new QCheckBox(editClues);
        centerText->setObjectName(QStringLiteral("centerText"));
        centerText->setFont(font2);

        horizontalLayout_2->addWidget(centerText);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        lngString_4 = new QLabel(editClues);
        lngString_4->setObjectName(QStringLiteral("lngString_4"));
        lngString_4->setFont(font2);

        horizontalLayout_3->addWidget(lngString_4);

        clueType = new QComboBox(editClues);
        clueType->setObjectName(QStringLiteral("clueType"));
        clueType->setMinimumSize(QSize(125, 0));
        clueType->setFont(font2);

        horizontalLayout_3->addWidget(clueType);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout_3->addLayout(horizontalLayout_3);


        verticalLayout->addWidget(editClues);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        gridLayout->addLayout(verticalLayout, 0, 2, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1159, 21));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Instructions", 0));
        editClues_4->setText(QApplication::translate("MainWindow", "Double-Click on the map to add a clue\n"
"Right-Click on a clue to delete it", 0));
        editClues_6->setText(QApplication::translate("MainWindow", "Edit clue options and preview clues\n"
"Save clues to file or download to box", 0));
        groupBox_6->setTitle(QApplication::translate("MainWindow", "Clue Options", 0));
#ifndef QT_NO_TOOLTIP
        loadButton->setToolTip(QApplication::translate("MainWindow", "Load clues from file", 0));
#endif // QT_NO_TOOLTIP
        loadButton->setText(QApplication::translate("MainWindow", "Load", 0));
#ifndef QT_NO_TOOLTIP
        saveButton->setToolTip(QApplication::translate("MainWindow", "Save clues to file", 0));
#endif // QT_NO_TOOLTIP
        saveButton->setText(QApplication::translate("MainWindow", "Save", 0));
#ifndef QT_NO_TOOLTIP
        moveUp->setToolTip(QApplication::translate("MainWindow", "Move Clue Up", 0));
#endif // QT_NO_TOOLTIP
        moveUp->setText(QApplication::translate("MainWindow", "Move Up", 0));
#ifndef QT_NO_TOOLTIP
        makeFirst->setToolTip(QApplication::translate("MainWindow", "Move the selected clue to the first position", 0));
#endif // QT_NO_TOOLTIP
        makeFirst->setText(QApplication::translate("MainWindow", "Make First", 0));
#ifndef QT_NO_TOOLTIP
        moveDown->setToolTip(QApplication::translate("MainWindow", "Move Clue Down", 0));
#endif // QT_NO_TOOLTIP
        moveDown->setText(QApplication::translate("MainWindow", "Move Down", 0));
#ifndef QT_NO_TOOLTIP
        makeLast->setToolTip(QApplication::translate("MainWindow", "Move the selected clue to the last position", 0));
#endif // QT_NO_TOOLTIP
        makeLast->setText(QApplication::translate("MainWindow", "Make Last", 0));
#ifndef QT_NO_TOOLTIP
        fitMap->setToolTip(QApplication::translate("MainWindow", "Zoom to show all clues", 0));
#endif // QT_NO_TOOLTIP
        fitMap->setText(QApplication::translate("MainWindow", "Fit Map", 0));
#ifndef QT_NO_TOOLTIP
        pushButton->setToolTip(QApplication::translate("MainWindow", "Remove ALL clues from the map", 0));
#endif // QT_NO_TOOLTIP
        pushButton->setText(QApplication::translate("MainWindow", "Clear", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Box Options", 0));
        latString_2->setText(QApplication::translate("MainWindow", "Battery", 0));
        latString_3->setText(QApplication::translate("MainWindow", "Version", 0));
        latString_4->setText(QApplication::translate("MainWindow", "Clues", 0));
        boxStatus->setText(QApplication::translate("MainWindow", "Connected via USB", 0));
        boxClueString->setText(QApplication::translate("MainWindow", "Clue <x> of <y>", 0));
#ifndef QT_NO_TOOLTIP
        boxSkipToPrevClue->setToolTip(QApplication::translate("MainWindow", "Skip to the previous clue", 0));
#endif // QT_NO_TOOLTIP
        boxSkipToPrevClue->setText(QApplication::translate("MainWindow", "< Skip", 0));
#ifndef QT_NO_TOOLTIP
        boxSkipToNextClue->setToolTip(QApplication::translate("MainWindow", "Skip to the next clue", 0));
#endif // QT_NO_TOOLTIP
        boxSkipToNextClue->setText(QApplication::translate("MainWindow", "Skip >", 0));
#ifndef QT_NO_TOOLTIP
        boxDownload->setToolTip(QApplication::translate("MainWindow", "Download clues from computer to geocache box", 0));
#endif // QT_NO_TOOLTIP
        boxDownload->setText(QApplication::translate("MainWindow", "Download", 0));
#ifndef QT_NO_TOOLTIP
        boxUpload->setToolTip(QApplication::translate("MainWindow", "Upload clues from geocache box to computer", 0));
#endif // QT_NO_TOOLTIP
        boxUpload->setText(QApplication::translate("MainWindow", "Upload", 0));
#ifndef QT_NO_TOOLTIP
        boxUnlock->setToolTip(QApplication::translate("MainWindow", "Move Clue Down", 0));
#endif // QT_NO_TOOLTIP
        boxUnlock->setText(QApplication::translate("MainWindow", "Unlock", 0));
#ifndef QT_NO_TOOLTIP
        boxLock->setToolTip(QApplication::translate("MainWindow", "Move Clue Down", 0));
#endif // QT_NO_TOOLTIP
        boxLock->setText(QApplication::translate("MainWindow", "Lock", 0));
        boxStatus_3->setText(QApplication::translate("MainWindow", "Reverse Geocache Software ", 0));
        boxStatus_2->setText(QApplication::translate("MainWindow", "Version: 1.0.0", 0));
        label->setText(QApplication::translate("MainWindow", "LCD Display Preview", 0));
#ifndef QT_NO_TOOLTIP
        LCD->setToolTip(QApplication::translate("MainWindow", "This is what the box display will show", 0));
#endif // QT_NO_TOOLTIP
        editClues->setTitle(QApplication::translate("MainWindow", "Edit Clues", 0));
        clueIndexDescriptor->setText(QApplication::translate("MainWindow", "Clue descriptor goes here", 0));
#ifndef QT_NO_TOOLTIP
        selectFirst->setToolTip(QApplication::translate("MainWindow", "Select Previous", 0));
#endif // QT_NO_TOOLTIP
        selectFirst->setText(QApplication::translate("MainWindow", "<<", 0));
#ifndef QT_NO_TOOLTIP
        selectPrev->setToolTip(QApplication::translate("MainWindow", "Select Previous", 0));
#endif // QT_NO_TOOLTIP
        selectPrev->setText(QApplication::translate("MainWindow", "<", 0));
        selection->setText(QApplication::translate("MainWindow", "Clue <x> of <y>", 0));
#ifndef QT_NO_TOOLTIP
        selectNext->setToolTip(QApplication::translate("MainWindow", "Select Next", 0));
#endif // QT_NO_TOOLTIP
        selectNext->setText(QApplication::translate("MainWindow", ">", 0));
#ifndef QT_NO_TOOLTIP
        selectLast->setToolTip(QApplication::translate("MainWindow", "Select Next", 0));
#endif // QT_NO_TOOLTIP
        selectLast->setText(QApplication::translate("MainWindow", ">>", 0));
        latString->setText(QApplication::translate("MainWindow", "Latitude: ", 0));
        lngString->setText(QApplication::translate("MainWindow", "Longitude:", 0));
        lngString_2->setText(QApplication::translate("MainWindow", "Threshold:", 0));
        lngString_3->setText(QApplication::translate("MainWindow", "m", 0));
#ifndef QT_NO_TOOLTIP
        setThreshold->setToolTip(QApplication::translate("MainWindow", "Set the clue distance threshold", 0));
#endif // QT_NO_TOOLTIP
        setThreshold->setText(QApplication::translate("MainWindow", "Set", 0));
        centerText->setText(QApplication::translate("MainWindow", "Center Text", 0));
        lngString_4->setText(QApplication::translate("MainWindow", "Clue Type:", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
