#ifndef STATEBAG_H
#define STATEBAG_H

#include <gamestate.h>
#include <gamemanager.h>

class GameManager;

class StateBag : public GameState
{
public:
    StateBag(GameManager *gamemnr);
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
};

#endif // STATEBAG_H
