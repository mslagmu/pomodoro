#include "chrono.h"
#include "ui_chrono.h"
#include <QDebug>

void Chrono::setTime(QString t){
    ui->clock->setText(t);
}



void Chrono::mousePressEvent(QMouseEvent *event){
    owner->setVisible(! owner->isVisible());
}

void Chrono::set_visible(bool s){
    _visible =s;
}

void Chrono::setStep(int s, QString color){
    setStyleSheet(QString("background-color: %1").arg(color));
    this->setVisible((s!=STOPED) && _visible);
}

Chrono::Chrono(QWidget *Owner, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Chrono),
    owner(Owner)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Dialog );
}

Chrono::~Chrono()
{
    delete ui;
    //delete owner;
}
