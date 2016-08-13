#ifndef STATEPOKEMON_H
#define STATEPOKEMON_H

#include <gamestate.h>
#include <gamemanager.h>

class GameManager;

class StatePokemon : public GameState
{
public:
    StatePokemon(GameManager *gamemnr);
    void Initialize ();
    void Update (QKeyEvent *event);
    void Draw ();
    void Release();

private:
    GameManager *GameMnr;
    QPixmap *m_frame;
    QPainter *painter;
    QLabel *m_screen;
    QString state;
    int pokemonSelected;
};

#endif // STATEPOKEMON_H
