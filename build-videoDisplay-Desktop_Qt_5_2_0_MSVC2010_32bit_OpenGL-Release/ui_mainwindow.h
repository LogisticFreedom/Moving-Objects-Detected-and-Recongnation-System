/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QWidget *centralWidget;
    QLabel *motionVideo;
    QLabel *originalVideo;
    QLabel *sailencyMapVideo;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLCDNumber *fpsLCD;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QPushButton *openVideoButton;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QComboBox *algorithmChoice;
    QPushButton *selectButton;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *playButton;
    QPushButton *stopButton;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(837, 679);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        motionVideo = new QLabel(centralWidget);
        motionVideo->setObjectName(QStringLiteral("motionVideo"));
        motionVideo->setGeometry(QRect(100, 360, 54, 12));
        originalVideo = new QLabel(centralWidget);
        originalVideo->setObjectName(QStringLiteral("originalVideo"));
        originalVideo->setGeometry(QRect(90, 70, 54, 12));
        sailencyMapVideo = new QLabel(centralWidget);
        sailencyMapVideo->setObjectName(QStringLiteral("sailencyMapVideo"));
        sailencyMapVideo->setGeometry(QRect(470, 70, 54, 12));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(90, 40, 101, 16));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(470, 40, 91, 16));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(100, 330, 71, 16));
        fpsLCD = new QLCDNumber(centralWidget);
        fpsLCD->setObjectName(QStringLiteral("fpsLCD"));
        fpsLCD->setGeometry(QRect(530, 380, 161, 51));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(530, 460, 164, 91));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        openVideoButton = new QPushButton(widget);
        openVideoButton->setObjectName(QStringLiteral("openVideoButton"));

        verticalLayout_2->addWidget(openVideoButton);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        algorithmChoice = new QComboBox(widget);
        algorithmChoice->setObjectName(QStringLiteral("algorithmChoice"));

        horizontalLayout_3->addWidget(algorithmChoice);

        selectButton = new QPushButton(widget);
        selectButton->setObjectName(QStringLiteral("selectButton"));

        horizontalLayout_3->addWidget(selectButton);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        playButton = new QPushButton(widget);
        playButton->setObjectName(QStringLiteral("playButton"));

        horizontalLayout->addWidget(playButton);


        horizontalLayout_2->addLayout(horizontalLayout);

        stopButton = new QPushButton(widget);
        stopButton->setObjectName(QStringLiteral("stopButton"));

        horizontalLayout_2->addWidget(stopButton);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 837, 23));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", 0));
        motionVideo->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        originalVideo->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        sailencyMapVideo->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        label->setText(QApplication::translate("MainWindow", "Original Video", 0));
        label_2->setText(QApplication::translate("MainWindow", "Saliency Map", 0));
        label_3->setText(QApplication::translate("MainWindow", "Motion Map", 0));
        openVideoButton->setText(QApplication::translate("MainWindow", "Open Video", 0));
        algorithmChoice->clear();
        algorithmChoice->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "DIVOG", 0)
         << QApplication::translate("MainWindow", "SR", 0)
         << QApplication::translate("MainWindow", "NEW FT", 0)
         << QApplication::translate("MainWindow", "Itti", 0)
        );
        selectButton->setText(QApplication::translate("MainWindow", "Apply", 0));
        playButton->setText(QApplication::translate("MainWindow", "Play", 0));
        stopButton->setText(QApplication::translate("MainWindow", "Stop", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File(&F)", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
