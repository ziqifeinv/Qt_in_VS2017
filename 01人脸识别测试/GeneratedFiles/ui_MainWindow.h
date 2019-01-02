/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QPushButton *open_image;
    QPushButton *close;
    QPushButton *pushButton;
    QLabel *label_2;
    QLabel *status_out;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QStringLiteral("MainWindowClass"));
        MainWindowClass->resize(924, 558);
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(13, 11, 701, 501));
        open_image = new QPushButton(centralWidget);
        open_image->setObjectName(QStringLiteral("open_image"));
        open_image->setGeometry(QRect(790, 330, 75, 23));
        close = new QPushButton(centralWidget);
        close->setObjectName(QStringLiteral("close"));
        close->setGeometry(QRect(790, 370, 75, 23));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(790, 290, 75, 23));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(730, 10, 54, 12));
        status_out = new QLabel(centralWidget);
        status_out->setObjectName(QStringLiteral("status_out"));
        status_out->setGeometry(QRect(730, 30, 181, 16));
        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 924, 23));
        MainWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindowClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindowClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindowClass->setStatusBar(statusBar);

        retranslateUi(MainWindowClass);
        QObject::connect(open_image, SIGNAL(clicked()), MainWindowClass, SLOT(on_OpenImage_Click()));
        QObject::connect(close, SIGNAL(clicked()), MainWindowClass, SLOT(on_close_click()));
        QObject::connect(pushButton, SIGNAL(clicked()), MainWindowClass, SLOT(on_openVidio_click()));

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "MainWindow", nullptr));
        label->setText(QString());
        open_image->setText(QApplication::translate("MainWindowClass", "\346\211\223\345\274\200\345\233\276\347\211\207", nullptr));
        close->setText(QApplication::translate("MainWindowClass", "\345\205\263\351\227\255", nullptr));
        pushButton->setText(QApplication::translate("MainWindowClass", "\346\211\223\345\274\200\350\247\206\351\242\221", nullptr));
        label_2->setText(QApplication::translate("MainWindowClass", "\347\212\266\346\200\201\357\274\232", nullptr));
        status_out->setText(QApplication::translate("MainWindowClass", "\350\277\231\351\207\214\344\274\232\346\230\276\347\244\272\346\221\204\345\203\217\345\244\264\347\212\266\346\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
