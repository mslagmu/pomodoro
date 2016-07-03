#ifndef CHRONO_H
#define CHRONO_H

#include <QWidget>
#include "constants.h"

namespace Ui {
class Chrono;
}

class Chrono : public QWidget
{
    Q_OBJECT

protected:
    void mousePressEvent(QMouseEvent *event);

public:
    explicit Chrono(QWidget *Owner,QWidget *parent = 0);
    ~Chrono();

    void setTime(QString t);
    void setStep(int s,QString color);
    void set_visible(bool v);

private:
    Ui::Chrono *ui;
    QWidget * owner;
    bool _visible=true;
};

#endif // CHRONO_H
