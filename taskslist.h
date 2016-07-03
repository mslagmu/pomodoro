#ifndef TASKSLIST_H
#define TASKSLIST_H

#include <QListWidget>
#include <QWidget>

class TasksList : public QListWidget
{
     Q_OBJECT
public:
    //TasksList();
    TasksList(QWidget *view = 0): QListWidget(view){};
};

#endif // TASKSLIST_H
