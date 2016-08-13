#ifndef STATEEXPLORATION_H
#define STATEEXPLORATION_H

#include <gamestate.h>
#include <map.h>
#include <hero.h>

#include <gamemanager.h>

class GameManager;

class StateExploration : public GameState
{
    Q_OBJECT
public:
    StateExploration(GameManager *gamemnr);
    void Initialize ();
    void Update (QKeyEvent *event);
    void Draw ();
    void Release();

public slots:
    void slot_movement();
private:
    Map m_map;
    Hero m_player;
    int dx;
    int dy;
    int row;
    int col;
    int direction;
    QPixmap *m_frame;
    QLabel *m_screen;
    QTimer *thread_movement;
    QPainter *painter;
    GameManager *GameMnr;
};

#endif // STATEEXPLORATION_H
