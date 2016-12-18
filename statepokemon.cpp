#include "statepokemon.h"

StatePokemon::StatePokemon(GameManager *gamemnr)
{
    GameMnr = gamemnr;
}

void StatePokemon::Initialize()
{
    m_screen = GameMnr->getScreen();
    m_frame = new QPixmap(832,576);
    painter = new QPainter(m_frame);
    state = "INFO";
    pokemonSelected = GameMnr->getPokemonSelected();
    Draw();
}

void StatePokemon::Update(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Right){
        if (state == "INFO"){
            state = "SKILLS";
            Draw();
        }
        else if (state == "SKILLS"){
            state = "MOVES";
            Draw();
        }
    }
    else if (event->key() == Qt::Key_Left){
        if (state == "SKILLS"){
            state = "INFO";
            Draw();
        }
        else if (state == "MOVES"){
            state = "SKILLS";
            Draw();
        }
    }
    else if (event->key() == Qt::Key_X){
        GameMnr->PopState();
        GameMnr->GetCurrentState()->Draw();
    }

}

void StatePokemon::Draw()
{
    painter->setFont(*GameMnr->getRscMng().fontFL40);
    painter->setPen(*GameMnr->getRscMng().penDarkGrey);
    if (state == "INFO"){
        painter->drawImage(QPoint(0,0),GameMnr->getRscMng().pokemonInfoBackground->scaled(832,576));
        if (GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getNumber() > 99)
            painter->drawText(QPoint(585,111),QString::number(GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getNumber()).toUpper());
        else if (GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getNumber() > 9)
            painter->drawText(QPoint(585,111),"0" +QString::number(GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getNumber()).toUpper());
        else
            painter->drawText(QPoint(585,111), "00"+QString::number(GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getNumber()).toUpper());
        painter->drawText(QPoint(585,164),GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getName().toUpper());
        painter->drawImage(QPoint(585,182),(new QImage("/users/Benjamin/iPokemon/type/"+GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getTypeStr(0)+".png"))->scaled(110,46));
        if (GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getType(1) != 0)
            painter->drawImage(QPoint(710,182),(new QImage("/users/Benjamin/iPokemon/type/"+GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getTypeStr(1)+".png"))->scaled(110,46));
        painter->drawText(QPoint(585,273),GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getOrginalTrainer());
        painter->drawText(QPoint(585,330),QString::number(GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getId()));
        painter->drawText(QPoint(585,383),"NONE");
        painter->drawText(QPoint(25,455),GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getNature().toUpper() + " nature.");
        painter->drawText(QPoint(25,510),"Met in " +GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getPlaceFound().toUpper() + " at Lv " + QString::number(GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getLvlWhenFound()) + ".");

    }
    else if (state == "SKILLS"){
        painter->drawImage(QPoint(0,0),GameMnr->getRscMng().pokemonSkillsBackground->scaled(832,576));
        painter->drawText(QRect(620,83,200,100),Qt::AlignRight,QString::number(GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getPv())+"/"+QString::number(GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getPvMax()));
        if (float(GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getPv())/float(GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getPvMax())<0.125)
            painter->drawImage(QPoint(635,121),GameMnr->getRscMng().hpRed->scaled(169*(float(GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getPv())/float(GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getPvMax())),12));
        else if (float(GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getPv())/float(GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getPvMax())<0.5)
            painter->drawImage(QPoint(635,121),GameMnr->getRscMng().hpYellow->scaled(169*(float(GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getPv())/float(GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getPvMax())),12));
        else
            painter->drawImage(QPoint(635,121),GameMnr->getRscMng().hpGreen->scaled(169*(float(GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getPv())/float(GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getPvMax())),12));

        painter->drawText(QRect(620,147,200,100),Qt::AlignRight,QString::number(GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getAttack()));
        painter->drawText(QRect(620,195,200,100),Qt::AlignRight,QString::number(GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getDefense()));
        painter->drawText(QRect(620,242,200,100),Qt::AlignRight,QString::number(GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getSpeAttack()));
        painter->drawText(QRect(620,290,200,100),Qt::AlignRight,QString::number(GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getSpeDefense()));
        painter->drawText(QRect(620,338,200,100),Qt::AlignRight,QString::number(GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getSpeed()));
        painter->drawText(QRect(620,388,200,100),Qt::AlignRight,QString::number(GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getExp()));
        painter->drawText(QRect(620,433,200,100),Qt::AlignRight,QString::number(GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getExpToNextLvl()));

        for (int i=0;i<(32*GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getExpPercent())/100;i++)
            painter->drawImage(QPoint(579+i*7,473),GameMnr->getRscMng().pokemonExp->scaled(7,11));

        painter->drawText(QRect(247,480,300,100),GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getAbility());
        painter->drawText(QRect(25,530,800,100),GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getAbilityDescription());
    }
    else if (state == "MOVES"){
        painter->drawImage(QPoint(0,0),GameMnr->getRscMng().pokemonMovesBackground->scaled(832,576));

        painter->drawText(QPoint(560,120),GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getMove(0)->getName().toUpper());
        painter->drawText(QPoint(680,155),"PP"+QString::number(GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getMove(0)->getPp())+"/"+QString::number(GameMnr->getPlayer().getTeamPokemon(0).getMove(0)->getPpMax()));
        painter->drawImage(QPoint(423,74),(new QImage ("/users/Benjamin/iPokemon/type/"+GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getMove(0)->getType()+".png"))->scaled(103,43));

        if (GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getMove(1) != NULL){
            painter->drawText(QPoint(560,220),GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getMove(1)->getName().toUpper());
            painter->drawText(QPoint(680,255),"PP"+QString::number(GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getMove(1)->getPp())+"/"+QString::number(GameMnr->getPlayer().getTeamPokemon(0).getMove(1)->getPpMax()));
            painter->drawImage(QPoint(423,174),(new QImage ("/users/Benjamin/iPokemon/type/"+GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getMove(1)->getType()+".png"))->scaled(103,43));
        }
        if (GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getMove(2) != NULL){
            painter->drawText(QPoint(560,320),GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getMove(2)->getName().toUpper());
            painter->drawText(QPoint(680,355),"PP"+QString::number(GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getMove(2)->getPp())+"/"+QString::number(GameMnr->getPlayer().getTeamPokemon(0).getMove(2)->getPpMax()));
            painter->drawImage(QPoint(423,274),(new QImage ("/users/Benjamin/iPokemon/type/"+GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getMove(2)->getType()+".png"))->scaled(103,43));
        }
        if (GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getMove(3) != NULL){
            painter->drawText(QPoint(560,420),GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getMove(3)->getName().toUpper());
            painter->drawText(QPoint(680,455),"PP"+QString::number(GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getMove(3)->getPp())+"/"+QString::number(GameMnr->getPlayer().getTeamPokemon(0).getMove(3)->getPpMax()));
            painter->drawImage(QPoint(423,374),(new QImage ("/users/Benjamin/iPokemon/type/"+GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getMove(3)->getType()+".png"))->scaled(103,43));
        }
    }
    painter->setPen(*GameMnr->getRscMng().penGrey);
    painter->drawText(QPoint(45,106),QString::number(GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getLevel()));
    painter->drawText(QPoint(133,106),GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getName().toUpper());

    painter->setPen(*GameMnr->getRscMng().penWhite);
    painter->drawText(QPoint(42,104),QString::number(GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getLevel()));
    painter->drawText(QPoint(130,104),GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getName().toUpper());

    if (GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getSexe() == "male")
        painter->drawImage(QPoint(360,72),GameMnr->getRscMng().male->scaled(29,35,Qt::KeepAspectRatio));
    else
        painter->drawImage(QPoint(360,72),GameMnr->getRscMng().female->scaled(29,35,Qt::KeepAspectRatio));

    painter->drawImage(QPoint(340,295),(new QImage("/users/Benjamin/iPokemon/item/"+GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getPokeball()+".png"))->scaled(40,40));
    QImage *sprite = new QImage("/users/Benjamin/iPokemon/sprite/"+ QString::number(GameMnr->getPlayer().getTeamPokemon(pokemonSelected-1).getNumber()) + ".png");
    painter->drawImage(QPoint(80,100),sprite->mirrored(true,false).scaled(256,256,Qt::KeepAspectRatio));

     m_screen->setPixmap(*m_frame);
}

void StatePokemon::Release()
{

}
