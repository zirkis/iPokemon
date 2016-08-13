#include "hero.h"

Hero::Hero()
{
    m_posX=10;
    m_posY=10;

    m_looks[0] = new QImage("/users/Benjamin/iPokemon/heroStandingDown.png");
    m_looks[1] = new QImage("/users/Benjamin/iPokemon/heroStandingLeft.png");
    m_looks[2] = new QImage("/users/Benjamin/iPokemon/heroStandingRight.png");
    m_looks[3] = new QImage("/users/Benjamin/iPokemon/heroStandingUp.png");

    m_looks[4] = new QImage("/users/Benjamin/iPokemon/heroWalkingLeft.png");
    m_looks[5] = new QImage("/users/Benjamin/iPokemon/heroWalkingRight.png");
    m_looks[6] = new QImage("/users/Benjamin/iPokemon/heroWalkingDown.png");
    m_looks[7] = new QImage("/users/Benjamin/iPokemon/heroWalkingUp.png");

    setLook(0);


    m_name = "RED";
    m_id = (rand()%(65535-10000))+10000;
}
void Hero::setTeam(FactoryPkm* factory)
{
    m_team[0] = factory->create(8);
    m_team[1] = factory->create(5);
    m_team[2] = factory->create(24);
    m_team[3] = factory->create(1);
    m_team[4] = NULL;
    m_team[5] = NULL;
    m_team[6] = factory->create(1);
}


void Hero::setLook(const int &i)
{
    m_look = m_looks[i];
}

void Hero::moveLeft()
{
    m_posY-=1;
    setLook(1);
}
void Hero::moveRight()
{
    m_posY+=1;
    setLook(2);
}
void Hero::moveUp()
{
    m_posX-=1;
    setLook(3);
}
void Hero::moveDown()
{
    m_posX+=1;
    setLook(0);
}

void Hero::standLeft()
{
    setLook(4);
}
void Hero::standRight()
{
    setLook(5);
}
void Hero::standDown()
{
    setLook(6);
}
void Hero::standUp()
{
    setLook(7);
}

QImage* Hero::getLook()const
{
    return m_look;
}
int Hero::getPosX() const
{
    return m_posX;
}
int Hero::getPosY() const
{
    return m_posY;
}
Pokemon &Hero::getTeamPokemon(const int &number)
{
    return *m_team[number];
}
int Hero::getNbPokemon()const
{
    int cpt = 0;
    for (int i=0; i<6;i++){
        if (m_team[i] != 0)
            cpt ++;
    }
    return cpt;
}
QString Hero::getName()const
{
    return m_name;
}
void Hero::switchPokemon(const int &pkm1, const int &pkm2)
{
    *m_team[6] = *m_team[pkm1-1];
    *m_team[pkm1-1] = *m_team[pkm2-1];
    *m_team[pkm2-1] = *m_team[6];
}
