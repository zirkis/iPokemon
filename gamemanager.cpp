#include "gamemanager.h"

GameManager::GameManager(QLabel *screen)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("PokeBase.db");
    m_screen = screen;
    m_tabStates[1] = new StatePause(this);
    m_tabStates[2] = new StateFight(this);
    m_tabStates[3] = new StateExploration(this);
    m_tabStates[4] = new StateTeam(this);
    m_tabStates[5] = new StateBag(this);
    m_tabStates[6] = new StatePokemon(this);

    m_factory = new FactoryPkm(m_db);
    m_player.setTeam(m_factory);
    PushState(*m_tabStates[3]);
}
// ===========================================================================================
// Add a new state (become the current one)
// ===========================================================================================
void GameManager::PushState( GameState& state )
{
    //state.SetGameManager ( (*this) );

    // set current state
    States.push( &state );
    States.top()->Initialize();
}

// ===========================================================================================
// Set the current state
// ===========================================================================================
void GameManager::SetState( GameState& state )
{
    //state.SetGameManager ( (*this) );

    // Delete the actual current state (if any)
    PopState ();

    // Add the new state
    PushState( state );
}

// ===========================================================================================
// Delete the current state
// ===========================================================================================
void GameManager::PopState()
{
    if ( !States.empty() )
    {
        States.top()->Release();
        States.pop();
    }
}

GameState &GameManager::getTabStates(const int &i)
{
    return *m_tabStates[i];
}
QLabel *GameManager::getScreen()const
{
    return m_screen;
}
QPixmap GameManager::getFrame()const
{
    return m_frame;
}
Hero GameManager::getPlayer()const
{
    return m_player;
}
FactoryPkm *GameManager::getFactoryPkm()const
{
    return m_factory;
}
RessourceManager GameManager::getRscMng()const
{
    return m_ressourcemng;
}
QSqlDatabase GameManager::getDb()const
{
    return m_db;
}

int GameManager::getPokemonSelected()const
{
    return m_pokemonSelected;
}
void GameManager::setFrame(QPixmap frame)
{
    m_frame = frame;
}
void GameManager::setPokemonSelected(int &i)
{
    m_pokemonSelected = i;
}
