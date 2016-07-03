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

void Chrono::setEnd(QString e){
    ui->end->setText(e);
}

void Chrono::setTextColor(QString c){
    _textColor=c;
}

QString Chrono::textColor(){
    return _textColor;
}


void Chrono::setStep(int s, QString color){
    setStyleSheet(QString("QWidget{background-color: %1} QLabel {color:%2}").arg(color).arg(_textColor));
    this->setVisible((s!=STOPED) && _visible);
}

Chrono::Chrono(QWidget *Owner, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Chrono),
    owner(Owner)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint  | Qt::Sheet);
}

Chrono::~Chrono()
{
    delete ui;
    //delete owner;
}
