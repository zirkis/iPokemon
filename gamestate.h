#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <QtWidgets>

class GameState : public QWidget
{
public:
    virtual void Initialize () = 0;
    virtual void Update (QKeyEvent *event) = 0;
    virtual void Draw () = 0;
    virtual void Release() = 0;
};

#endif // GAMESTATE_H
