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
    void setEnd(QString e);
    void set_visible(bool v);
    void setTextColor(QString c);
    QString textColor();

private:
    Ui::Chrono *ui;
    QWidget * owner;
    bool _visible=true;
    QString _textColor;
};

#endif // CHRONO_H
