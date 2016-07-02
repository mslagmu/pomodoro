#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QResource>

#define STOPED  0
#define WORK  1
#define SHORT  2
#define LONG  3





MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),tray(this),config("pomodoro"),chrono()
{
   //QResource::registerResource("resource.rcc");

   tray.setObjectName("tray");
   ui->setupUi(this);
   stepsNames << "Inactif" << "Travail" << "Courte Pause" << "Longue Pause";

   ui->workTime->setValue(config.value("worktime",25).toInt());
   ui->shortTime->setValue(config.value("shorttime",5).toInt());
   ui->longTime->setValue(config.value("longtime",15).toInt());
   ui->cycle->setValue(config.value("cycle",4).toInt());

   tray.setIcon(QIcon(":/images/logo.png"));

   setWindowIcon(QIcon(":/images/logo.png"));
   //setWindowFlags(Qt::FramelessWindowHint);

   tray.show();
   on_reset_clicked();

   chrono.show();
   chrono.setGeometry(1000,0,100,100);

}

void MainWindow::on_start_clicked() {
    if ( step == STOPED ) {
        nextStep();
    }
    timer = startTimer(1000);
}


void MainWindow::nextStep(){
    int s = step;
    if ( s == STOPED ) {
        step=WORK;
    }
    if ( s == WORK  && nbcycle < cycle ) {
        step = SHORT;
        nbcycle += 1;
    }

    if ( s == WORK  && nbcycle == cycle ) {
        step = LONG;
        nbcycle = 0;
    }

    if ( s==LONG || s == SHORT ) step = WORK;

    secondes = 60;
    minutes = stepTime[step]-1;
    ui->step->setText(QString("<html><head/><body><p align=\"center\">%1</p></body></html>").arg(stepsNames[step]));
    tray.showMessage("Changement",stepsNames[step]);
}


void MainWindow::on_stop_clicked() {
    killTimer(timer);
}

void MainWindow::on_skip_clicked() {
    nextStep();
}

void MainWindow::on_tray_activated ( QSystemTrayIcon::ActivationReason reason ){
    this->setVisible(this->isVisible());
}

void MainWindow::on_reset_clicked() {
    stepTime[STOPED] = 0;
    nbcycle = 0;
    step = STOPED;
    ui->step->setText(QString("<html><head/><body><p align=\"center\">%1</p></body></html>").arg(stepsNames[step]));
    killTimer(timer);

}

void MainWindow::on_workTime_valueChanged(int v){
   stepTime[WORK] = v;
}

void MainWindow::on_longTime_valueChanged(int v){
   stepTime[LONG] = v;
}

void MainWindow::on_shortTime_valueChanged(int v){
   stepTime[SHORT] = v;
}

void MainWindow::on_cycle_valueChanged(int v){
   cycle=v;
}

void MainWindow::on_saveconfig_clicked(){
    saveConfig();
}


void MainWindow::saveConfig(){
    config.setValue("worktime",ui->workTime->value());
    config.setValue("longtime",ui->longTime->value());
    config.setValue("shorttime",ui->shortTime->value());
    config.setValue("cycle",ui->cycle->value());
}


void MainWindow::timerEvent(QTimerEvent *event){
    QString t;
    secondes = secondes-1;
    if (secondes < 0) {
        minutes= minutes-1;
        secondes = 59;
    }
    if (minutes ==0 && secondes==0) nextStep();
    t = QString("<html><head/><body><p align=\"center\">%1:%2</p></body></html>").arg(minutes,2).arg(secondes,2);
    this->setWindowTitle(QString("%3 %1:%2").arg(minutes,2).arg(secondes,2).arg(stepsNames[step]));
    ui->clock->setText(t);
}

MainWindow::~MainWindow()
{
    delete ui;

}
