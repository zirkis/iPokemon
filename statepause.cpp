#include "statepause.h"

StatePause::StatePause(GameManager *gamemnr)
{
    GameMnr = gamemnr;
}

void StatePause::Initialize()
{
    m_screen = GameMnr->getScreen();
    choiceSelected = 0;
    Draw();
}
void StatePause::Update(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space){
        GameMnr->PopState();
        GameMnr->GetCurrentState()->Draw();
    }
    else if (event->key() == Qt::Key_Down){
        if (choiceSelected < 6){
            choiceSelected++;
            Draw();
        }
        else if (choiceSelected == 6){
            choiceSelected = 0;
            Draw();
        }
    }
    else if (event->key() == Qt::Key_Up){
        if (choiceSelected >0){
            choiceSelected--;
            Draw();
        }
        else if (choiceSelected == 0){
            choiceSelected = 6;
            Draw();
        }
    }
    else if (event->key() == Qt::Key_W){
        switch (choiceSelected){
        case 1:
            GameMnr->PushState(GameMnr->getTabStates(4));
            break;
        case 2:
            GameMnr->PushState(GameMnr->getTabStates(5));
            break;
        case 6:
            GameMnr->PopState();
            GameMnr->GetCurrentState()->Draw();
            break;
        }
    }
    else if (event->key() == Qt::Key_X)
    {
        GameMnr->PopState();
        GameMnr->GetCurrentState()->Draw();
    }

}
void StatePause::Draw()
{
    m_frame = GameMnr->getFrame();
    painter = new QPainter(&m_frame);

    painter->setFont(*GameMnr->getRscMng().fontFL40);
    painter->setPen(*GameMnr->getRscMng().penGrey);

    painter->fillRect(612,10,210,435,Qt::white);

    painter->drawImage(QPoint(604,0),GameMnr->getRscMng().frameLU->scaled(25,25,Qt::KeepAspectRatio));
    painter->drawImage(QPoint(804,0),GameMnr->getRscMng().frameRU->scaled(25,25,Qt::KeepAspectRatio));
    for (int i=0;i<16;i++){
        if (i<7){
            painter->drawImage(QPoint(629+i*25,0),GameMnr->getRscMng().frameMU->scaled(25,25,Qt::KeepAspectRatio));
            painter->drawImage(QPoint(629+i*25,425),GameMnr->getRscMng().frameMB->scaled(25,25,Qt::KeepAspectRatio));
        }
        painter->drawImage(QPoint(604,25+i*25),GameMnr->getRscMng().frameLM->scaled(25,25,Qt::KeepAspectRatio));
        painter->drawImage(QPoint(804,25+i*25),GameMnr->getRscMng().frameRM->scaled(25,25,Qt::KeepAspectRatio));
    }
    painter->drawImage(QPoint(604,425),GameMnr->getRscMng().frameLB->scaled(25,25,Qt::KeepAspectRatio));
    painter->drawImage(QPoint(804,425),GameMnr->getRscMng().frameRB->scaled(25,25,Qt::KeepAspectRatio));

    painter->drawText(647,35,255,80,Qt::AlignLeft,"POKEDEX");
    painter->drawText(647,92,255,80,Qt::AlignLeft,"POKEMON");
    painter->drawText(647,149,255,80,Qt::AlignLeft,"BAG");
    painter->drawText(647,206,255,80,Qt::AlignLeft,"RED");
    painter->drawText(647,263,255,80,Qt::AlignLeft,"SAVE");
    painter->drawText(647,320,255,80,Qt::AlignLeft,"OPTION");
    painter->drawText(647,377,255,80,Qt::AlignLeft,"EXIT");

    QPolygon triangle;
    QPainterPath path;
    triangle << QPoint(631, 39+choiceSelected*57) << QPoint(631, 59+choiceSelected*57) << QPoint(641, 49+choiceSelected*57);
    path.addPolygon(triangle);
    painter->drawConvexPolygon(triangle);
    painter->fillPath(path,QColor(100,100,100));

    m_screen->setPixmap(m_frame);

    painter->end();
}

void StatePause::Release()
{

}
