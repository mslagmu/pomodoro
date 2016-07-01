#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>

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

private slots:
    void on_start_clicked();
    void on_stop_clicked();
    void on_skip_clicked();
    void on_reset_clicked();
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

};

#endif // MAINWINDOW_H
