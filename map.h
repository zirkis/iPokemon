#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <fstream>

#include<QtWidgets>
#include "tile.h"
#include "ressourcemanager.h"

class Map
{
public:
    void load(const QString& level);
    void calculate(const int& heroPosX,const int& heroPosY);
    Tile *getTiles(const int& i)const;
    RessourceManager ressourceManager;
    int result[11][15];

    bool canHeroMovesLeft;
    bool canHeroMovesRight;
    bool canHeroMovesUp;
    bool canHeroMovesDown;
    bool canHeroMeetPkm;

private:
    Tile *m_tiles[100];
    int tabMap1[20][20];
    QString m_level;
};

#endif // MAP_H
