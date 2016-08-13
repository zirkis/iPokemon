#include "window.h"
#include <iostream>
#include <fstream>
#include <QTextStream>
#include <QDebug>

using namespace std;

Window::Window()
{
    screen = new QLabel;
    setCentralWidget(screen);
    mng = new GameManager(screen);
}

void Window::keyPressEvent(QKeyEvent *event)
{
    mng->GetCurrentState()->Update(event);
}
