#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QtWidgets>

//#include <stateexploration.h>
#include <gamemanager.h>

class Window : public QMainWindow
{
    Q_OBJECT
public:
    Window();
    QLabel *screen;
protected:
    void keyPressEvent(QKeyEvent *event);

private:
    GameManager *mng;
};

#endif // WINDOW_H
