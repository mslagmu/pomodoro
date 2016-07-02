#ifndef CHRONO_H
#define CHRONO_H

#include <QWidget>

namespace Ui {
class Chrono;
}

class Chrono : public QWidget
{
    Q_OBJECT

public:
    explicit Chrono(QWidget *parent = 0);
    ~Chrono();

private:
    Ui::Chrono *ui;
};

#endif // CHRONO_H
