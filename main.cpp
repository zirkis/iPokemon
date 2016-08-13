#include <QApplication>
#include <QCoreApplication>
#include <QDir>
#include <QtWidgets>
#include <stdio.h>

#include <window.h>

int main(int argc, char *argv[])
{
    srand((unsigned)time(NULL));

    QApplication app(argc, argv);
    //QFontDatabase::addApplicationFont(":/font/font/pkmnfl.ttf");
    Window fenetre;
    fenetre.setFixedHeight(576);
    fenetre.setFixedWidth(832);
    fenetre.setWindowTitle("iPokemon");
    fenetre.show();

    return app.exec();
}
