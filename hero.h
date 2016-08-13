#ifndef HERO_H
#define HERO_H

#include <QtWidgets>
#include <pokemon.h>
#include <factorypkm.h>
class Hero
{
public:
    Hero();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    void standLeft();
    void standRight();
    void standDown();
    void standUp();

    void setTeam(FactoryPkm* factory);
    void switchPokemon(const int& pkm1, const int& pkm2);

    QImage* getLook()const;
    void setLook(const int& i);
    int getPosX() const;
    int getPosY() const;
    Pokemon& getTeamPokemon(const int& number);    
    int getNbPokemon() const;
    QString getName()const;

private:
    int m_posX;
    int m_posY;
    QImage* m_looks[8];
    QImage *m_look;
    Pokemon *m_team[7];
    QString m_name;
    int m_id;
};

#endif // HERO_H
