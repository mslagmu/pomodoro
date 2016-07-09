#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QDebug>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QString locale = QLocale::system().name();
    QTranslator translator;
    QString t_name = QString("pomodoro_") + locale +(".qm");

    translator.load(t_name,":translation");

    a.installTranslator(&translator);

    MainWindow w;
    w.show();

    return a.exec();
}
