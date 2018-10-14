#include "mainwindow.h"
#include <QTime>
#include <QtDebug>
#include <QColor>
#include <QStyle>
#include <QPalette>
//    connect(okienkoset, &QDialog::finished, this, &MainWindow::zamknijOkienSettimeSlot);
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    centralWidget = new QTextEdit(this);
    //  centralWidget->setTextBackgroundColor("yellow");

    QPalette p = centralWidget->palette();
    p.setColor(QPalette::Base, QColor(255, 255, 153));
    centralWidget->setPalette(p);
    centralWidget->setFontPointSize(12);

    setCentralWidget(centralWidget);


    time = new QMenu(tr("&Time"));
    options = new QMenu(tr("&Options"));
    help = new QMenu(tr("&Help"));
    menuBar()->addMenu(time);
    menuBar()->addMenu(options);
    menuBar()->addMenu(help);

    about = new QAction(tr("&About"), this);

    newSet = new QAction(tr("&Set"), this);
    newUnset = new QAction(tr("&Unset"), this);
    ukryj = new QAction(tr("&Hide"),this);
    readOnly = new QAction(tr("&ReadOnly"),this);
    readWrite = new QAction(tr("Read&Write"),this);
    newSet->setStatusTip(tr("Set time"));
    connect(newSet, &QAction::triggered, this, &MainWindow::newSetSlot);

    newUnset->setStatusTip(tr("Unset time"));
    connect(newUnset, &QAction::triggered, this, &MainWindow::newUnsetSlot);

    ukryj->setStatusTip(tr("Hide"));
    connect(ukryj, &QAction::triggered, this, &MainWindow::ukryjSlot);


    readOnly->setStatusTip(tr("ReadOnly"));
    connect(readOnly, &QAction::triggered, this, &MainWindow::readOnlySlot);

    readWrite->setStatusTip(tr("ReadWrite"));
    connect(readWrite, &QAction::triggered, this, &MainWindow::readWriteSlot);

    connect(about, &QAction::triggered, this, &MainWindow::aboutSlot);


    time->addAction(newSet);
    time->addAction(newUnset);
    options->addAction(ukryj);
    options->addAction(readOnly);
    options->addAction(readWrite);
    help->addAction(about);


    okienkoset = new QDialog;
    formlayout = new QFormLayout;
    formlayout->setSpacing(10);
    tedit = new QTimeEdit;
    spinBoxminuty = new QSpinBox;
    spinBoxminuty->setMaximum(86400);
    checkbox01 = new QCheckBox("&set fixed time:", this);
    checkbox02 = new QCheckBox("&minutes:", this);


    formlayout->addRow(checkbox01, tedit);
    formlayout->addRow(checkbox02, spinBoxminuty);
    okienkoset->setLayout(formlayout);
    okienkoset->setWindowFlag(Qt::WindowStaysOnTopHint); // zawsze na pierwszym planie

    tedit->setTime(QTime::currentTime());


    timer01 = new QTimer(this);


    connect(timer01, &QTimer::timeout, this, &MainWindow::sprtimer01Slot);


    fileToolBar = addToolBar(tr("Set"));
    fileToolBar->addAction(newSet);
    fileToolBar = addToolBar(tr("Unset"));
    fileToolBar->addAction(newUnset);
    fileToolBar = addToolBar(tr("Hide"));
    fileToolBar->addAction(ukryj);

    timer02 = new QTimer(this); // interwaly czasowe dlatego musi byc inny timer niz wyzej

    connect(timer02, &QTimer::timeout, this, &MainWindow::sprtimer02Slot);

}

MainWindow::~MainWindow()
{
    delete options;
    delete  timer01;
    delete  tedit;
    delete centralWidget;
}

void MainWindow::newSetSlot()
{
    QString message = tr("Set");
    statusBar()->showMessage(message);
    okienkoset->show();
    timer01->stop();
    timer02->stop();
}

void MainWindow::newUnsetSlot()
{
    QString message = tr("Unset");
    statusBar()->showMessage(message);
    tedit->setTime(QTime::currentTime());
    timer01->stop();
    timer02->stop();
    checkbox01->setChecked(false);
    checkbox02->setChecked(false);
}

void MainWindow::ukryjSlot()
{
    if(checkbox01->isChecked() ) {
        timer01->setInterval(500);
        timer01->start();
    } else {
        timer01->stop();
    }
    if(checkbox02->isChecked() ) {
        timer02->setInterval(spinBoxminuty->text().toInt() * 1000 * 60);
        timer02->start();
    } else {
        timer02->stop();
    }


    if(checkbox01->isChecked() or checkbox02->isChecked())
        this->hide();
    else
    {
        QString message = ("First set the alarm.");
        statusBar()->showMessage(message);
    }
}





void MainWindow::readOnlySlot()
{
    centralWidget->setReadOnly(true);
}

void MainWindow::readWriteSlot()
{
    centralWidget->setReadOnly(false);
}


void MainWindow::sprtimer01Slot()
{
    if(checkbox01->isChecked() ) {
        if((QTime::currentTime()).toString("hh::mm") == (tedit->time()).toString("hh::mm")) {
            statusBar()->showMessage("alarm");
            this->setWindowFlag(Qt::WindowStaysOnTopHint); // zawsze na pierwszym planie
            this->show();
        } else {
            QString message = (tedit->time()).toString();
            statusBar()->showMessage(message);
        }
    }
}

void MainWindow::sprtimer02Slot()
{
    if(checkbox02->isChecked() ) {
        statusBar()->showMessage("alarm");
        this->setWindowFlag(Qt::WindowStaysOnTopHint); // zawsze na pierwszym planie

        this->show();
    }
}

void MainWindow::aboutSlot()
{
    QDialog *dialogabout = new QDialog;
    QVBoxLayout *laybout = new QVBoxLayout(dialogabout);
    QTextEdit *txtabout = new QTextEdit(dialogabout);
    txtabout->setWindowFlag(Qt::WindowStaysOnTopHint); // zawsze na pierwszym planie
    QString string("<b>reminder 1.0</b><br>"
                   "Built on Sep 20 2018 14:17:40<br>"
                   "<br>"
                   "Copyright 2008-2018<br>"
                   " Janusz Wieczorek wieczoj@gmail.com.<br>"
                   " All rights reserved.<br>"
                   "reminder 1.0<br>"
                   "The program is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE WARRANTY OF DESIGN,<br>"
                   " MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.<br>");

    txtabout->setText(string);
    laybout->addWidget(txtabout);
    dialogabout->show();
}

//void MainWindow::zamknijOkienSettimeSlot()
//{

//}

