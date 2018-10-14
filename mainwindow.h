#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTextEdit>
#include <QMenuBar>
#include <QStatusBar>
#include <QTimeEdit>
#include <QTimer>
#include <QToolBar>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QDialog>
#include <QSpinBox>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QTextEdit  *centralWidget;
    QAction *newSet;
    QAction *newUnset;
    QMenu *time;
    QMenu *options;
    QMenu *help;
    QTimer *timer01;
    QTimer *timer02; // odmierzanie ustawionej ilosci minut
    QAction *ukryj;
    QToolBar *fileToolBar;
    QAction *readOnly;
    QAction *readWrite;
    QAction *about;
    QTimeEdit *tedit;

    QFormLayout *formlayout;

//    QLineEdit *edit_min_inter;
    QDialog *okienkoset;

    QCheckBox *checkbox01;
    QCheckBox *checkbox02;
    QSpinBox *spinBoxminuty;



public slots:
    void newSetSlot();
    void newUnsetSlot();
    void ukryjSlot();
    void sprtimer01Slot();
    void readOnlySlot();
    void readWriteSlot();
    void sprtimer02Slot();
//    void zamknijOkienSettimeSlot();
    void aboutSlot();

};

#endif // MAINWINDOW_H
