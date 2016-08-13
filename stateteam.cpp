#include "stateteam.h"

StateTeam::StateTeam(GameManager *gamemnr)
{
    GameMnr = gamemnr;
}
void StateTeam::Initialize()
{
    m_screen = GameMnr->getScreen();
    pkmSelected = 1;
    switchSelected = -1;
    choice = 0;
    m_frame = new QPixmap(832,576);
    painter = new QPainter(m_frame);
    state = "SELECTION";
    Draw();
}
void StateTeam::Update(QKeyEvent *event)
{
     if (event->key() == Qt::Key_Down){
         if (pkmSelected <= GameMnr->getPlayer().getNbPokemon() && state == "SELECTION"){
             pkmSelected++;
             Draw();
         }
         else if (switchSelected < GameMnr->getPlayer().getNbPokemon() && state == "SWITCH"){
             switchSelected++;
             if (switchSelected == pkmSelected)
                 switchSelected++;
             if (switchSelected == pkmSelected+1 && switchSelected >GameMnr->getPlayer().getNbPokemon())
                 switchSelected-=2;
             Draw();
         }
         else if (state == "MENU" && choice < 3){
             choice++;
             Draw();
         }


    }
    else if (event->key() == Qt::Key_Up){
            if (pkmSelected > 1 && state == "SELECTION"){
                pkmSelected--;
                Draw();
            }
            else if (switchSelected > 1 && state == "SWITCH"){
                switchSelected--;
                if (switchSelected == pkmSelected)
                    switchSelected--;
                if (switchSelected == 0)
                    switchSelected+=2;
                Draw();
            }
            else if (state == "MENU" && choice > 0){
                choice--;
                Draw();
            }

    }
    else if (event->key() == Qt::Key_W){
         if (pkmSelected != GameMnr->getPlayer().getNbPokemon()+1 && state == "SELECTION"){
             state = "MENU";
             Draw();
         }
         else if (pkmSelected == GameMnr->getPlayer().getNbPokemon()+1 && state == "SELECTION"){
             GameMnr->PopState();
             GameMnr->GetCurrentState()->Draw();
         }
         else if (choice == 3 && state == "MENU"){
             state = "SELECTION";
             Draw();
             choice = 0;
         }
         else if (choice == 1 && state == "MENU"){
             state = "SWITCH";
             if (pkmSelected != GameMnr->getPlayer().getNbPokemon())
                switchSelected = pkmSelected+1;
             else
                 switchSelected = 1;
             Draw();
         }
         else if (choice == 0 && state == "MENU"){
             GameMnr->setPokemonSelected(pkmSelected);
             GameMnr->PushState(GameMnr->getTabStates(6));
         }
         else if (state == "SWITCH"){
             if (pkmSelected != switchSelected)
                 GameMnr->getPlayer().switchPokemon(pkmSelected,switchSelected);
             pkmSelected = switchSelected;
             switchSelected = -1;
             choice = 0;
             state = "SELECTION";
             Draw();
         }
    }
    else if (event->key() == Qt::Key_X)
    {
         if (state == "SELECTION"){
             GameMnr->PopState();
             GameMnr->GetCurrentState()->Draw();
         }
         else if (state == "MENU"){
             choice = 0;
             state = "SELECTION";
             Draw();
         }
         else if (state == "SWITCH"){
             switchSelected = -1;
             state = "MENU";
             Draw();
         }
    }
}
void StateTeam::Draw()
{
    painter->setFont(*GameMnr->getRscMng().fontFL32);
    painter->setPen(*GameMnr->getRscMng().penWhite);

    painter->drawImage(QPoint(0,0),GameMnr->getRscMng().menuPokemon->scaled(832,576,Qt::IgnoreAspectRatio));
    if (pkmSelected == 1 || switchSelected == 1)
        painter->drawImage(QPoint(2,68),GameMnr->getRscMng().menuPokemonSquareSel->scaled(300,200,Qt::IgnoreAspectRatio));
    else
        painter->drawImage(QPoint(2,68),GameMnr->getRscMng().menuPokemonSquare->scaled(300,200,Qt::IgnoreAspectRatio));

    painter->setPen(*GameMnr->getRscMng().penGrey);
    painter->drawText(108,142,200,80,Qt::AlignLeft,GameMnr->getPlayer().getTeamPokemon(0).getName().toUpper());
    painter->drawText(168,176,60,80,Qt::AlignLeft,QString::number(GameMnr->getPlayer().getTeamPokemon(0).getLevel()));
    painter->drawText(163,234,60,80,Qt::AlignLeft,QString::number(GameMnr->getPlayer().getTeamPokemon(0).getPv()));
    painter->drawText(231,234,60,80,Qt::AlignLeft,QString::number(GameMnr->getPlayer().getTeamPokemon(0).getPvMax()));

    painter->setPen(*GameMnr->getRscMng().penWhite);
    painter->drawText(105,140,200,80,Qt::AlignLeft,GameMnr->getPlayer().getTeamPokemon(0).getName().toUpper());
    painter->drawText(165,174,60,80,Qt::AlignLeft,QString::number(GameMnr->getPlayer().getTeamPokemon(0).getLevel()));
    painter->drawText(160,232,60,80,Qt::AlignLeft,QString::number(GameMnr->getPlayer().getTeamPokemon(0).getPv()));
    painter->drawText(228,232,60,80,Qt::AlignLeft,QString::number(GameMnr->getPlayer().getTeamPokemon(0).getPvMax()));

    if (float(GameMnr->getPlayer().getTeamPokemon(0).getPv())/float(GameMnr->getPlayer().getTeamPokemon(0).getPvMax())<0.125)
        painter->drawImage(QPoint(108,210),GameMnr->getRscMng().hpRed->scaled(169*(float(GameMnr->getPlayer().getTeamPokemon(0).getPv())/float(GameMnr->getPlayer().getTeamPokemon(0).getPvMax())),11));
    else if (float(GameMnr->getPlayer().getTeamPokemon(0).getPv())/float(GameMnr->getPlayer().getTeamPokemon(0).getPvMax())<0.5)
        painter->drawImage(QPoint(108,210),GameMnr->getRscMng().hpYellow->scaled(169*(float(GameMnr->getPlayer().getTeamPokemon(0).getPv())/float(GameMnr->getPlayer().getTeamPokemon(0).getPvMax())),11));
    else
        painter->drawImage(QPoint(108,210),GameMnr->getRscMng().hpGreen->scaled(169*(float(GameMnr->getPlayer().getTeamPokemon(0).getPv())/float(GameMnr->getPlayer().getTeamPokemon(0).getPvMax())),11));

    if (GameMnr->getPlayer().getTeamPokemon(0).getSexe() == "male")
        painter->drawImage(QPoint(250,170),GameMnr->getRscMng().male->scaled(23,28,Qt::KeepAspectRatio));
    else
        painter->drawImage(QPoint(250,170),GameMnr->getRscMng().female->scaled(23,28,Qt::KeepAspectRatio));

    QImage *menuPokemonIcons = new QImage("/users/Benjamin/iPokemon/sprite/icons/" + QString::number(GameMnr->getPlayer().getTeamPokemon(0).getNumber()) + ".gif");
    painter->drawImage(QPoint(-5,95),menuPokemonIcons->scaled(95,95,Qt::KeepAspectRatio));

    for (int i=0; i<GameMnr->getPlayer().getNbPokemon()-1;i++){
        QImage *menuPokemonIcons = new QImage("/users/Benjamin/iPokemon/sprite/icons/" + QString::number(GameMnr->getPlayer().getTeamPokemon(i+1).getNumber()) + ".gif");
        if (pkmSelected-2 == i || switchSelected-2 == i)
            painter->drawImage(QPoint(300,29+87*i),GameMnr->getRscMng().menuPokemonRectSel->scaled(525,85,Qt::IgnoreAspectRatio));
        else
            painter->drawImage(QPoint(300,29+87*i),GameMnr->getRscMng().menuPokemonRect->scaled(525,85,Qt::IgnoreAspectRatio));

        painter->setPen(*GameMnr->getRscMng().penGrey);
        painter->drawText(403,55+87*i,200,80,Qt::AlignLeft,GameMnr->getPlayer().getTeamPokemon(i+1).getName().toUpper());
        painter->drawText(473,89+87*i,60,80,Qt::AlignLeft,QString::number(GameMnr->getPlayer().getTeamPokemon(i+1).getLevel()).toUpper());
        painter->drawText(691,84+87*i,60,80,Qt::AlignLeft,QString::number(GameMnr->getPlayer().getTeamPokemon(i+1).getPv()));
        painter->drawText(755,84+87*i,60,80,Qt::AlignLeft,QString::number(GameMnr->getPlayer().getTeamPokemon(i+1).getPvMax()));

        painter->setPen(*GameMnr->getRscMng().penWhite);
        painter->drawText(400,53+87*i,200,80,Qt::AlignLeft,GameMnr->getPlayer().getTeamPokemon(i+1).getName().toUpper());
        painter->drawText(470,87+87*i,60,80,Qt::AlignLeft,QString::number(GameMnr->getPlayer().getTeamPokemon(i+1).getLevel()).toUpper());
        painter->drawText(688,82+87*i,60,80,Qt::AlignLeft,QString::number(GameMnr->getPlayer().getTeamPokemon(i+1).getPv()));
        painter->drawText(752,82+87*i,60,80,Qt::AlignLeft,QString::number(GameMnr->getPlayer().getTeamPokemon(i+1).getPvMax()));

        if (GameMnr->getPlayer().getTeamPokemon(i+1).getSexe() == "male")
            painter->drawImage(QPoint(560,82+87*i),GameMnr->getRscMng().male->scaled(23,28,Qt::KeepAspectRatio));
        else
            painter->drawImage(QPoint(560,82+87*i),GameMnr->getRscMng().female->scaled(23,28,Qt::KeepAspectRatio));

        painter->drawImage(QPoint(290,18+87*i),menuPokemonIcons->scaled(95,95,Qt::KeepAspectRatio));

        if (float(GameMnr->getPlayer().getTeamPokemon(i+1).getPv())/float(GameMnr->getPlayer().getTeamPokemon(i+1).getPvMax())<0.125)
            painter->drawImage(QPoint(635,61+87*i),GameMnr->getRscMng().hpRed->scaled(166*(float(GameMnr->getPlayer().getTeamPokemon(i+1).getPv())/float(GameMnr->getPlayer().getTeamPokemon(i+1).getPvMax())),11));
        else if (float(GameMnr->getPlayer().getTeamPokemon(i+1).getPv())/float(GameMnr->getPlayer().getTeamPokemon(i+1).getPvMax())<0.5)
            painter->drawImage(QPoint(635,61+87*i),GameMnr->getRscMng().hpYellow->scaled(166*(float(GameMnr->getPlayer().getTeamPokemon(i+1).getPv())/float(GameMnr->getPlayer().getTeamPokemon(i+1).getPvMax())),11));
        else
            painter->drawImage(QPoint(635,61+87*i),GameMnr->getRscMng().hpGreen->scaled(166*(float(GameMnr->getPlayer().getTeamPokemon(i+1).getPv())/float(GameMnr->getPlayer().getTeamPokemon(i+1).getPvMax())),11));
    }

    if (pkmSelected == GameMnr->getPlayer().getNbPokemon()+1)
        painter->drawImage(QPoint(635,476),GameMnr->getRscMng().menuPokemonCancelSel->scaled(193,89));
    else
        painter->drawImage(QPoint(635,476),GameMnr->getRscMng().menuPokemonCancel->scaled(193,89));

    painter->setFont(*GameMnr->getRscMng().fontFL40);
    painter->setPen(*GameMnr->getRscMng().penGrey);
    if (state == "SELECTION")
        painter->drawText(32,504,600,80,Qt::AlignLeft,"Choose a POKéMON.");
    else if (state == "MENU"){
        painter->setFont(*GameMnr->getRscMng().fontFL40);
        painter->drawImage(QPoint(0,465),GameMnr->getRscMng().menuPokemonBottom->scaled(832,105));
        painter->drawImage(QPoint(8,465),GameMnr->getRscMng().menuPokemonFrame->scaled(470,104));
        painter->drawText(32,504,600,80,Qt::AlignLeft,"Do what with this PKMN?");

        painter->fillRect(510,290,315,270,Qt::white);
        painter->drawImage(QPoint(500,285),GameMnr->getRscMng().frameLU->scaled(25,25,Qt::KeepAspectRatio));
        for (int i=0;i<12;i++){
            painter->drawImage(QPoint(525+i*25,285),GameMnr->getRscMng().frameMU->scaled(25,25,Qt::KeepAspectRatio));
            painter->drawImage(QPoint(525+i*25,550),GameMnr->getRscMng().frameMB->scaled(25,25,Qt::KeepAspectRatio));
            if (i<10){
            painter->drawImage(QPoint(500,310+i*25),GameMnr->getRscMng().frameLM->scaled(25,25,Qt::KeepAspectRatio));
            painter->drawImage(QPoint(804,310+i*25),GameMnr->getRscMng().frameRM->scaled(25,25,Qt::KeepAspectRatio));
            }
        }
        painter->drawImage(QPoint(804,285),GameMnr->getRscMng().frameRU->scaled(25,25,Qt::KeepAspectRatio));
        painter->drawImage(QPoint(500,550),GameMnr->getRscMng().frameLB->scaled(25,25,Qt::KeepAspectRatio));
        painter->drawImage(QPoint(804,550),GameMnr->getRscMng().frameRB->scaled(25,25,Qt::KeepAspectRatio));

        painter->drawImage(QPoint(530,325+choice*55),GameMnr->getRscMng().bagArrow->scaled(40,40,Qt::KeepAspectRatio));
        painter->drawText(560,330,600,80,Qt::AlignLeft,"SUMMARY");
        painter->drawText(560,385,600,80,Qt::AlignLeft,"SWITCH");
        painter->drawText(560,440,600,80,Qt::AlignLeft,"ITEM");
        painter->drawText(560,495,600,80,Qt::AlignLeft,"CANCEL");

    }


    m_screen->setPixmap(*m_frame);
}
void StateTeam::Release()
{

}
