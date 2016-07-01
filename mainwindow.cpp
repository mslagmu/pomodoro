#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

#define STOPED  0
#define WORK  1
#define SHORT  2
#define LONG  3





MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),tray(this)
{

   tray.setObjectName("tray");
   ui->setupUi(this);
   stepsNames << "Inactif" << "Travail" << "Courte Pause" << "Longue Pause";

   tray.show();

   on_reset_clicked();
/*
   nbcycle = 0;
   cycle=4;
   for (int i = 0; i< 20; i++) {
       nextStep();
       qDebug()<< stepsNames[step] << '\n';

   }
*/
}

void MainWindow::on_start_clicked() {
    if ( step == STOPED ) nextStep();
    timer = startTimer(1000);
}


void MainWindow::nextStep(){
    int s = step;
    if ( s == STOPED ) step=WORK;
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
    stepTime[WORK] = ui->workTime->value();
    stepTime[LONG] = ui->longTime->value();
    stepTime[SHORT] = ui->shortTime->value();
    stepTime[STOPED] = 0;
    cycle = ui->cycle->value();
    nbcycle = 0;
    step = STOPED;
    ui->step->setText(QString("<html><head/><body><p align=\"center\">%1</p></body></html>").arg(stepsNames[step]));
    killTimer(timer);

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
