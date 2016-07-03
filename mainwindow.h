#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QSettings>
#include "chrono.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void timerEvent(QTimerEvent *event);
    void nextStep();
    void closeEvent(QCloseEvent * event);

private slots:
    void on_start_clicked();
    void on_stop_clicked();
    void on_skip_clicked();
    void on_reset_clicked();
    void on_saveconfig_clicked();
    void on_workTime_valueChanged(int v);
    void on_longTime_valueChanged(int v);
    void on_shortTime_valueChanged(int v);
    void on_cycle_valueChanged(int v);
    void on_showPopup_stateChanged(int state);
    void on_tray_activated ( QSystemTrayIcon::ActivationReason reason );


private:
    Ui::MainWindow *ui;
    int minutes;
    int secondes;
    int stepTime[10],cycle,nbcycle;
    int timer;
    int step;
    QStringList stepsNames;
    QSystemTrayIcon tray;
    QSettings config;
    void saveConfig();
    void setStep(int s);
    void displayTime();
    Chrono chrono;

};

#endif // MAINWINDOW_H
