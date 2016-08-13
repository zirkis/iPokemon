#include "statebag.h"

StateBag::StateBag(GameManager *gamemnr)
{
    GameMnr = gamemnr;
}
void StateBag::Initialize()
{
    m_screen = GameMnr->getScreen();
    m_frame = new QPixmap(832,576);
    painter = new QPainter(m_frame);
    state = "ITEMS";
    Draw();
}
void StateBag::Update(QKeyEvent *event)
{
    if (event->key() == Qt::Key_X)
    {
         GameMnr->PopState();
         GameMnr->GetCurrentState()->Draw();
    }
    else if (event->key() == Qt::Key_Right)
    {
        if (state == "ITEMS"){
            state = "KEYS";
            Draw();
        }
        else if (state == "KEYS"){
            state = "BALLS";
            Draw();
        }
    }
    else if (event->key() == Qt::Key_Left)
    {
        if (state == "KEYS"){
            state = "ITEMS";
            Draw();
        }
        else if (state == "BALLS"){
            state = "KEYS";
            Draw();
        }
    }
}
void StateBag::Draw()
{
    painter->drawImage(QPoint(0,0),GameMnr->getRscMng().backgroundBag->scaled(832,576));
    if (state == "ITEMS"){
        painter->drawImage(QPoint(12,4),GameMnr->getRscMng().bagItem->scaled(270,103,Qt::IgnoreAspectRatio));
        painter->drawImage(QPoint(28,150),GameMnr->getRscMng().bagLeft->scaled(225,280,Qt::KeepAspectRatio));
        painter->drawImage(QPoint(230,240),GameMnr->getRscMng().bagArrowRight->scaled(50,55,Qt::KeepAspectRatio));
    }
    else if (state == "KEYS"){
        painter->drawImage(QPoint(12,4),GameMnr->getRscMng().bagKey->scaled(270,103,Qt::IgnoreAspectRatio));
        painter->drawImage(QPoint(32,139),GameMnr->getRscMng().bagMiddle->scaled(225,280,Qt::KeepAspectRatio));
        painter->drawImage(QPoint(230,240),GameMnr->getRscMng().bagArrowRight->scaled(50,55,Qt::KeepAspectRatio));
        painter->drawImage(QPoint(0,240),GameMnr->getRscMng().bagArrowLeft->scaled(50,55,Qt::KeepAspectRatio));
    }
    else if (state == "BALLS"){
        painter->drawImage(QPoint(12,4),GameMnr->getRscMng().bagBall->scaled(270,103,Qt::IgnoreAspectRatio));
        painter->drawImage(QPoint(28,146),GameMnr->getRscMng().bagRight->scaled(225,280,Qt::KeepAspectRatio));
        painter->drawImage(QPoint(0,240),GameMnr->getRscMng().bagArrowLeft->scaled(50,55,Qt::KeepAspectRatio));
    }
    painter->drawImage(QPoint(305,38),GameMnr->getRscMng().bagArrow->scaled(60,50,Qt::KeepAspectRatio));
    m_screen->setPixmap(*m_frame);
}
void StateBag::Release()
{

}
