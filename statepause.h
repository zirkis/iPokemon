#ifndef STATEPAUSE_H
#define STATEPAUSE_H

#include <gamestate.h>
#include <gamemanager.h>
#include <ressourcemanager.h>

class GameManager;

class StatePause : public GameState
{
public:
    StatePause(GameManager *gamemnr);
    void Initialize ();
    void Update (QKeyEvent *event);
    void Draw ();
    void Release();
private:
    GameManager *GameMnr;
    QPixmap m_frame;
    QPainter *painter;
    QLabel *m_screen;
    int choiceSelected;
};

#endif // STATEPAUSE_H
