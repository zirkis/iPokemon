#include "stateexploration.h"

StateExploration::StateExploration(GameManager *gamemnr)
{
    GameMnr = gamemnr;
    m_player = gamemnr->getPlayer();
}

void StateExploration::Initialize()
{
    m_map.load("level1");
    thread_movement = new QTimer(this);
    connect(thread_movement, SIGNAL(timeout()),this, SLOT(slot_movement()));
    dx=0;
    dy=0;
    row=0;
    col=0;
    m_screen = GameMnr->getScreen();
    m_frame = new QPixmap(832,576);
    painter = new QPainter(m_frame);
    Draw();
}

void StateExploration::Update(QKeyEvent *event)
{
    if (!thread_movement->isActive()){
        if (event->key() == Qt::Key_Left){
            if (m_map.canHeroMovesLeft){
                direction = 1;
                thread_movement->start(10);
                m_player.standLeft();
            }
            else{
                m_player.setLook(1);
                Draw();
            }
        }

        else if (event->key() == Qt::Key_Right){
            if (m_map.canHeroMovesRight){
                direction = 2;
                thread_movement->start(10);
                m_player.standRight();
            }
            else{
                m_player.setLook(2);
                Draw();
            }
        }
        else if (event->key() == Qt::Key_Down){
            if (m_map.canHeroMovesDown){
                direction = 3;
                thread_movement->start(10);
                m_player.standDown();
            }
            else{
                m_player.setLook(0);
                Draw();
            }
        }
        else if (event->key() == Qt::Key_Up){
            if (m_map.canHeroMovesUp){
                direction = 4;
                thread_movement->start(10);
                m_player.standUp();
            }
            else{
                m_player.setLook(3);
                Draw();
            }
        }
        else if (event->key() == Qt::Key_Space){
            GameMnr->setFrame(*m_frame);
            GameMnr->PushState(GameMnr->getTabStates(1));
        }
    }

}

void StateExploration::Draw()
{
    m_map.calculate(m_player.getPosX(),m_player.getPosY());

    row=0;
    col=0;
    for (int i=0;i<165;i++){
        painter->drawImage(QPoint(row*64+dx-64,col*64+dy-64),m_map.ressourceManager.getTiles(m_map.result[col][row]).getLook());
        col++;
        if (col == 11){
            col=0;
            row++;
        }
    }

    painter->drawImage(QPoint(384,256),*(m_player.getLook()));
    m_screen->setPixmap(*m_frame);
}
void StateExploration::Release()
{

}

void StateExploration::slot_movement()
{
    if (direction == 1){
        dx+=8;
        Draw();
        if (dx%64==0){
            thread_movement->stop();
            dx=0;
            m_player.moveLeft();
            Draw();
            if (m_map.canHeroMeetPkm){
                GameMnr->setFrame(*m_frame);
                GameMnr->PushState(GameMnr->getTabStates(2));
            }
        }
    }

    else if (direction == 2){
        dx-=8;
        Draw();
        if (dx%(-64)==0){
            thread_movement->stop();
            dx=0;
            m_player.moveRight();
            Draw();
            if (m_map.canHeroMeetPkm){
                GameMnr->setFrame(*m_frame);
                GameMnr->PushState(GameMnr->getTabStates(2));
            }
        }
    }

    else if (direction == 3){
        dy-=8;
        Draw();
        if (dy%(-64)==0){
            thread_movement->stop();
            dy=0;
            m_player.moveDown();
            Draw();
            if (m_map.canHeroMeetPkm){
                GameMnr->setFrame(*m_frame);
                GameMnr->PushState(GameMnr->getTabStates(2));
            }
        }
    }
    else if (direction == 4){
        dy+=8;
        Draw();
        if (dy%64==0){
            thread_movement->stop();
            dy=0;
            m_player.moveUp();
            Draw();
            if (m_map.canHeroMeetPkm){
                GameMnr->setFrame(*m_frame);
                GameMnr->PushState(GameMnr->getTabStates(2));
            }
        }
    }
}
