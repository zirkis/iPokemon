#include "map.h"

using namespace std;

void Map::load(const QString &level)
{
    m_level = "/users/Benjamin/iPokemon/" + level + ".txt";

    ifstream map1(m_level.toStdString().c_str());

    string buffer;

    int x=0;
    int y=0;

    while(map1>>buffer)
    {
        tabMap1[x][y]= atoi(buffer.c_str());
        y++;
        if (y==20){
            x++;
            y=0;
        }
    }

}
void Map::calculate(const int &heroPosX, const int &heroPosY)
{

    int elt=0;
    int row=0;
    int column=0;

    for (int i=heroPosX-5; i<heroPosX+6;i++){
        for (int j=heroPosY-7;j<heroPosY+8;j++){
            result[row][column]=tabMap1[i][j];
            column++;
            if (column == 15){
                column=0;
                row++;
            }
            elt++;
        }
    }
    if(tabMap1[heroPosX][heroPosY]==4){
        int numb = rand()%16;
        if (numb>5)
            canHeroMeetPkm = true;
        else
            canHeroMeetPkm = false;
    }
    else{
        canHeroMeetPkm = false;
    }

    if (ressourceManager.getTiles(tabMap1[heroPosX-1][heroPosY]).getCrossable())
        canHeroMovesUp = true;
    else
        canHeroMovesUp = false;

    if (ressourceManager.getTiles(tabMap1[heroPosX+1][heroPosY]).getCrossable())
        canHeroMovesDown = true;
    else
        canHeroMovesDown = false;

    if (ressourceManager.getTiles(tabMap1[heroPosX][heroPosY+1]).getCrossable())
        canHeroMovesRight = true;
    else
        canHeroMovesRight = false;

    if (ressourceManager.getTiles(tabMap1[heroPosX][heroPosY-1]).getCrossable())
        canHeroMovesLeft = true;
    else
        canHeroMovesLeft = false;
}

Tile *Map::getTiles(const int& i)const
{
    return m_tiles[i];
}

