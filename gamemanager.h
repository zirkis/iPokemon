#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <gamestate.h>
#include <stateexploration.h>
#include <statepause.h>
#include <statefight.h>
#include <stateteam.h>
#include <statebag.h>
#include <statepokemon.h>
#include <factorypkm.h>
#include <QtSql>
#include <iostream>
#include <stack>
#include <ressourcemanager.h>


class GameManager
{
public :
    GameManager(QLabel *screen);

    // Get the current state
    GameState* GetCurrentState() { return ( !States.empty() ) ? States.top() : NULL; }
    // Add a new state ( become the current one )
    void PushState( GameState& state );
    // Set the current state
    void SetState( GameState& state );
    // Delete the current state
    void PopState();

    GameState& getTabStates(const int& i);
    QLabel *getScreen() const;
    QPixmap getFrame()const;
    Hero getPlayer()const;
    FactoryPkm *getFactoryPkm()const;
    RessourceManager getRscMng()const;
    int getPokemonSelected()const;
    QSqlDatabase getDb()const;

    void setFrame(QPixmap frame);
    void setPokemonSelected(int &i);


private :
    // State manager for game states
    std::stack<GameState*> States;
    GameState* m_tabStates[10];
    QLabel *m_screen;
    QPixmap m_frame;
    Hero m_player;
    FactoryPkm *m_factory;
    QSqlDatabase m_db;
    RessourceManager m_ressourcemng;
    int m_pokemonSelected;
};

#endif // GAMEMANAGER_H
