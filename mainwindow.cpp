#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QResource>
#include <QCloseEvent>
#include <QTextStream>
#include <QColorDialog>
#include <QTime>
#include "constants.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),tray(this),config("pomodoro"),chrono(this,this)
{
   //QResource::registerResource("resource.rcc");

   tray.setObjectName("tray");
   ui->setupUi(this);
   stepsNames << "Inactif" << "Travail" << "Courte Pause" << "Longue Pause";

   ui->workTime->setValue(config.value("worktime",25).toInt());
   ui->shortTime->setValue(config.value("shorttime",5).toInt());
   ui->longTime->setValue(config.value("longtime",15).toInt());
   ui->cycle->setValue(config.value("cycle",4).toInt());

   colorNames[STOPED] = "white";
   changeColorButton(ui->workColor,WORK,config.value("workColor","red").toString());
   changeColorButton(ui->shortColor,SHORT,config.value("shortColor","yellow").toString());
   changeColorButton(ui->longColor,LONG,config.value("longColor","green").toString());

   chrono.setTextColor(config.value("textColor","black").toString());


   //colorName[WORK]   = config.value("shorttime",5)

   tray.setIcon(QIcon(":/images/logo.png"));

   setWindowIcon(QIcon(":/images/logo.png"));
   //setWindowFlags(Qt::FramelessWindowHint);

   tray.setContextMenu(0);

   //tray.show();
   on_reset_clicked();


   chrono.setGeometry(1000,0,84,20);

}

void MainWindow::on_start_clicked() {
    if ( step == STOPED ) {
        nextStep();
    }
    timer = startTimer(1000);
}

void MainWindow::setStep(int s) {
    QTime now (QTime::currentTime());
    step=s;
    chrono.setStep(step,colorNames[s]);
    QTime e = now.addSecs(stepTime[s]*60);
    QString time;
    QTextStream(&time) << "" << qSetFieldWidth(2) << right << qSetPadChar('0')
                       << e.hour() << qSetFieldWidth(1) << ":" << qSetFieldWidth(2)
                       <<  e.minute() << qSetFieldWidth(1) << ":" << qSetFieldWidth(2)
                       << e.second();
    chrono.setEnd(time);
}

void MainWindow::nextStep(){
    int s = step;
    if ( s == STOPED ) {
        setStep(WORK);
    }
    if ( s == WORK  && nbcycle < cycle ) {
        setStep(SHORT);
        nbcycle += 1;
    }

    if ( s == WORK  && nbcycle == cycle ) {
        setStep(LONG);
        nbcycle = 0;
    }

    if ( s==LONG || s == SHORT ) setStep(WORK);

    secondes = 60;
    minutes = stepTime[step]-1;
    ui->step->setText(QString("<html><head/><body><p align=\"center\">%1</p></body></html>").arg(stepsNames[step]));
    //tray.showMessage("Changement",stepsNames[step]);

}


void MainWindow::on_stop_clicked() {
    killTimer(timer);
}

void MainWindow::on_skip_clicked() {
    nextStep();
}



void MainWindow::changeColorButton(QPushButton * b,int step, QString  name) {
    b->setStyleSheet(QString("background-color:%1").arg(name));
    colorNames[step] = name;
}

void MainWindow::on_workColor_clicked() {
    QColor color = QColorDialog::getColor(Qt::white, this, "Choisir la couleur.");
    if ( ! color.isValid())  return ;
    changeColorButton(ui->workColor,WORK,color.name());

}

void MainWindow::on_shortColor_clicked() {
    QColor color = QColorDialog::getColor(Qt::white, this, "Choisir la couleur.");
    if ( ! color.isValid())  return ;
    changeColorButton(ui->shortColor,SHORT,color.name());
}

void MainWindow::on_longColor_clicked() {
    QColor color = QColorDialog::getColor(Qt::white, this, "Choisir la couleur.");
    if ( ! color.isValid())  return ;
    changeColorButton(ui->longColor,LONG,color.name());
}

void MainWindow::on_textColor_clicked() {
    QColor color = QColorDialog::getColor(Qt::white, this, "Choisir la couleur.");
    if ( ! color.isValid())  return ;
    //ui->textColor->setStyleSheet(QString("background-color:%1").arg(color.name()));
    chrono.setTextColor(color.name());
    chrono.setStep(step,colorNames[step]);
}

void MainWindow::on_tray_activated ( QSystemTrayIcon::ActivationReason reason ){
    this->setVisible(!this->isVisible());
}

void MainWindow::on_reset_clicked() {
    stepTime[STOPED] = 0;
    nbcycle = 0;
    minutes = stepTime[WORK];
    secondes = 0;
    setStep(STOPED);
    displayTime();
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
    config.setValue("workcolor",colorNames[WORK]);
    config.setValue("longcolor",colorNames[LONG]);
    config.setValue("short",colorNames[SHORT]);
    config.setValue("textColor",chrono.textColor());
}


void MainWindow::closeEvent(QCloseEvent * event){
    chrono.hide();
    event->accept();
}

void MainWindow::displayTime(){
    QString time;
    QTextStream(&time) << "" << qSetFieldWidth(2) << right << qSetPadChar('0') << minutes << qSetFieldWidth(1) << ":" << qSetFieldWidth(2) <<  secondes ;
    this->setWindowTitle(QString("%3 %1:%2").arg(minutes,2).arg(secondes,2).arg(stepsNames[step]));
    ui->clock->setText(time);
    chrono.setTime(time);
}

void MainWindow::on_showPopup_stateChanged(int state){
    chrono.set_visible(state==2);
    chrono.setStep(step,colorNames[step]);
}



void MainWindow::timerEvent(QTimerEvent *event){

    secondes = secondes-1;
    if (secondes < 0) {
        minutes= minutes-1;
        secondes = 59;
    }
    if (minutes ==0 && secondes==0) nextStep();

    displayTime();
}

MainWindow::~MainWindow()
{
    delete ui;

}
