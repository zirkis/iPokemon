#ifndef STATETEAM_H
#define STATETEAM_H

#include <gamestate.h>
#include <gamemanager.h>

class GameManager;

class StateTeam : public GameState
{
public:
    StateTeam(GameManager *gamemnr);
    void Initialize ();
    void Update (QKeyEvent *event);
    void Draw ();
    void Release();
private:
    GameManager *GameMnr;
    QPixmap *m_frame;
    QPainter *painter;
    QLabel *m_screen;
    int pkmSelected;
    int switchSelected;
    int choice;
    QString state;
};

#endif // STATETEAM_H
