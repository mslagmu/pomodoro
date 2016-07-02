#include "chrono.h"
#include "ui_chrono.h"

Chrono::Chrono(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Chrono)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Dialog );
}

Chrono::~Chrono()
{
    delete ui;
}
