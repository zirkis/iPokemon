#ifndef STATEFIGHT_H
#define STATEFIGHT_H

#include <gamestate.h>
#include <gamemanager.h>
#include <pokemon.h>

class GameManager;

class StateFight : public GameState
{
public:
    StateFight(GameManager *gamemnr);
    void Initialize ();
    void Update (QKeyEvent *event);
    void Draw ();
    void Release();

    void DrawMovesMenu();
    void PlayerAttacks();
    void PokemonAttacks();
    void CalculateDammage();
    void CalculatePlayerDammage();
    void AnalyseLastMove();
    bool isPokemonDead();
    void CalculateExp();
private:
    GameManager *GameMnr;
    QPixmap *m_frame;
    QPainter *painter;
    QLabel *m_screen;
    Pokemon *m_pokemon;
    int choice;
    int moveChoice;
    QString state;
    int analyseState;
    float lastMoveAnalyses[2];
    int randomMove;
};

#endif // STATEFIGHT_H
