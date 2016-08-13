#include "statefight.h"

StateFight::StateFight(GameManager *gamemnr)
{
    GameMnr = gamemnr;
}

void StateFight::Initialize()
{
    m_screen = GameMnr->getScreen();
    m_frame = new QPixmap(832,576);
    painter = new QPainter(m_frame);
    state = "BEGIN";

    int randomId = (rand()%251)+1;
    m_pokemon = GameMnr->getFactoryPkm()->create(randomId);
    choice = 0;
    moveChoice = 0;
    analyseState = 0;
    Draw();
}

void StateFight::Update(QKeyEvent *event)
{
    if (event->key() == Qt::Key_W){
        if (state == "BEGIN"){
            if (choice == 3){
                GameMnr->PopState();
                GameMnr->GetCurrentState()->Draw();
            }
            else if (choice == 0){
                DrawMovesMenu();
                state = "MOVES";
            }
            else if (choice == 1){
                GameMnr->PushState(GameMnr->getTabStates(5));
            }
            else if (choice == 2){
                GameMnr->PushState(GameMnr->getTabStates(4));
            }
        }
        else if (state == "MOVES"){
            if (GameMnr->getPlayer().getTeamPokemon(0).getMove(moveChoice)->getPp()){
                state = "ROUND1";
                PlayerAttacks();
            }
        }
        else if (state == "ROUND1"){
            CalculateDammage();
            Draw();
            state = "ANALYSE1";
            AnalyseLastMove();
        }
        else if (state == "ANALYSE1" || state == "ANALYSE2"){
            AnalyseLastMove();
        }
        else if (state == "ROUND2"){
            CalculatePlayerDammage();
            Draw();
            state = "ANALYSE2";
            AnalyseLastMove();
        }
        else if (state == "END"){
            CalculateExp();
            state = "EXP";
        }
        else if (state == "EXP"){
            GameMnr->PopState();
            GameMnr->GetCurrentState()->Draw();
        }
    }
    else if (event->key() == Qt::Key_X && state == "MOVES")
    {
        Draw();
        state = "BEGIN";
    }
    else if (event->key() == Qt::Key_Right){
        if (state == "BEGIN"){
            if (choice == 0)
                choice = 1;
            else if (choice == 2)
                choice = 3;
            Draw();
        }
        else if (state == "MOVES" && moveChoice < GameMnr->getPlayer().getTeamPokemon(0).getNbMoves()-1){
            if (moveChoice == 0)
                moveChoice = 1;
            else if (moveChoice == 2)
                moveChoice = 3;
            DrawMovesMenu();
        }
    }
    else if (event->key() == Qt::Key_Left){
        if (state == "BEGIN"){
            if (choice == 1)
                choice = 0;
            if (choice == 3)
                choice = 2;
            Draw();
        }
        else if (state == "MOVES"){
            if (moveChoice == 1)
                moveChoice = 0;
            else if (moveChoice == 3)
                moveChoice = 2;
            DrawMovesMenu();
        }
    }
    else if (event->key() == Qt::Key_Down){
        if (state == "BEGIN"){
            if (choice == 0)
                choice = 2;
            if (choice == 1)
                choice = 3;
            Draw();
        }
        else if (state == "MOVES" && moveChoice < GameMnr->getPlayer().getTeamPokemon(0).getNbMoves()-2){
            if (moveChoice == 0)
                moveChoice = 2;
            else if (moveChoice == 1)
                moveChoice = 3;
            DrawMovesMenu();
        }
    }
    else if (event->key() == Qt::Key_Up){
        if (state == "BEGIN"){
            if (choice == 2)
                choice = 0;
            if (choice == 3)
                choice = 1;
            Draw();
        }
        else if (state == "MOVES"){
            if (moveChoice == 2)
                moveChoice = 0;
            else if (moveChoice == 3)
                moveChoice = 1;
            DrawMovesMenu();
        }
    }

}

void StateFight::Draw()
{

    painter->fillRect(0,0,832,576,Qt::white);

    painter->drawImage(QPoint(0,0),GameMnr->getRscMng().fightBackground->scaled(832,405,Qt::IgnoreAspectRatio));

    QImage *sprite = new QImage("/users/Benjamin/iPokemon/sprite/" + QString::number(m_pokemon->getNumber()) + ".png");
    painter->drawImage(QPoint(480,0+(30-m_pokemon->getHeight()/1.25)),sprite->scaled(288,288,Qt::IgnoreAspectRatio));

    QImage *spriteBack = new QImage("/users/Benjamin/iPokemon/sprite/back/" + QString::number(GameMnr->getPlayer().getTeamPokemon(0).getNumber())+ ".png");
    painter->drawImage(QPoint(100,150+(65-GameMnr->getPlayer().getTeamPokemon(0).getHeight()/2)),spriteBack->scaled(256,256,Qt::IgnoreAspectRatio));

    painter->drawImage(QPoint(0,405),GameMnr->getRscMng().fightBar->scaled(832,171,Qt::IgnoreAspectRatio));

    painter->drawImage(QPoint(405,410),GameMnr->getRscMng().fightMenu->scaled(427,166,Qt::IgnoreAspectRatio));

    painter->drawImage(QPoint(430,275),GameMnr->getRscMng().fightPlayerStatus->scaled(375,130,Qt::IgnoreAspectRatio));

    painter->drawImage(QPoint(35,48),GameMnr->getRscMng().fightPkmStatus->scaled(400,130,Qt::IgnoreAspectRatio));

    if (m_pokemon->getSexe() == "male")
        painter->drawImage(QPoint(72+m_pokemon->getName().length()*17,76),GameMnr->getRscMng().fightMale->scaled(23,28,Qt::KeepAspectRatio));
    else
        painter->drawImage(QPoint(72+m_pokemon->getName().length()*17,76),GameMnr->getRscMng().fightFemale->scaled(23,28,Qt::KeepAspectRatio));

    if (GameMnr->getPlayer().getTeamPokemon(0).getSexe() == "male")
        painter->drawImage(QPoint(493+GameMnr->getPlayer().getTeamPokemon(0).getName().length()*17,292),GameMnr->getRscMng().fightMale->scaled(23,28,Qt::KeepAspectRatio));
    else
        painter->drawImage(QPoint(493+GameMnr->getPlayer().getTeamPokemon(0).getName().length()*17,292),GameMnr->getRscMng().fightFemale->scaled(23,28,Qt::KeepAspectRatio));

    for (int i=0;i<(77*GameMnr->getPlayer().getTeamPokemon(0).getExpPercent())/100;i++)
        painter->drawImage(QPoint(547+i*3,391),GameMnr->getRscMng().fightExp->scaled(3,7));

    switch (choice){
        case 0:
            painter->drawImage(QPoint(435,450),GameMnr->getRscMng().fightArrow->scaled(30,30,Qt::KeepAspectRatio));
            break;
        case 1:
            painter->drawImage(QPoint(640,450),GameMnr->getRscMng().fightArrow->scaled(30,30,Qt::KeepAspectRatio));
            break;
        case 2:
            painter->drawImage(QPoint(435,510),GameMnr->getRscMng().fightArrow->scaled(30,30,Qt::KeepAspectRatio));
            break;
        case 3:
            painter->drawImage(QPoint(640,510),GameMnr->getRscMng().fightArrow->scaled(30,30,Qt::KeepAspectRatio));
            break;
    }

    if (float(GameMnr->getPlayer().getTeamPokemon(0).getPv())/float(GameMnr->getPlayer().getTeamPokemon(0).getPvMax())<0.125)
        painter->drawImage(QPoint(605,334),GameMnr->getRscMng().hpRed->scaled(169*(float(GameMnr->getPlayer().getTeamPokemon(0).getPv())/float(GameMnr->getPlayer().getTeamPokemon(0).getPvMax())),11));
    else if (float(GameMnr->getPlayer().getTeamPokemon(0).getPv())/float(GameMnr->getPlayer().getTeamPokemon(0).getPvMax())<0.5)
        painter->drawImage(QPoint(605,334),GameMnr->getRscMng().hpYellow->scaled(169*(float(GameMnr->getPlayer().getTeamPokemon(0).getPv())/float(GameMnr->getPlayer().getTeamPokemon(0).getPvMax())),11));
    else
        painter->drawImage(QPoint(605,334),GameMnr->getRscMng().hpGreen->scaled(171*(float(GameMnr->getPlayer().getTeamPokemon(0).getPv())/float(GameMnr->getPlayer().getTeamPokemon(0).getPvMax())),12));

    if (float(m_pokemon->getPv())/float(m_pokemon->getPvMax())<0.125)
        painter->drawImage(QPoint(182,122),GameMnr->getRscMng().hpRed->scaled(169*(float(m_pokemon->getPv())/float(m_pokemon->getPvMax())),11));
    else if (float(m_pokemon->getPv())/float(m_pokemon->getPvMax())<0.5)
        painter->drawImage(QPoint(182,122),GameMnr->getRscMng().hpYellow->scaled(169*(float(m_pokemon->getPv())/float(m_pokemon->getPvMax())),11));
    else
        painter->drawImage(QPoint(182,122),GameMnr->getRscMng().hpGreen->scaled(169*(float(m_pokemon->getPv())/float(m_pokemon->getPvMax())),12));


    painter->setPen(*GameMnr->getRscMng().penShadow);
    painter->setFont(*GameMnr->getRscMng().fontFL35);
    painter->drawText(70,80,255,80,Qt::AlignLeft,m_pokemon->getName().toUpper());
    painter->drawText(493,296,255,80,Qt::AlignLeft,GameMnr->getPlayer().getTeamPokemon(0).getName().toUpper());
    painter->setFont(*GameMnr->getRscMng().fontFL30);
    painter->drawText(332,86,255,80,Qt::AlignLeft,QString::number(m_pokemon->getLevel()));
    painter->drawText(758,300,255,80,Qt::AlignLeft,QString::number(GameMnr->getPlayer().getTeamPokemon(0).getLevel()));
    painter->drawText(523,361,255,80,Qt::AlignRight,QString::number(GameMnr->getPlayer().getTeamPokemon(0).getPv())+"/"+QString::number(GameMnr->getPlayer().getTeamPokemon(0).getPvMax()));


    painter->setPen(*GameMnr->getRscMng().penDarkGrey);
    painter->setFont(*GameMnr->getRscMng().fontFL35);
    painter->drawText(67,78,255,80,Qt::AlignLeft,m_pokemon->getName().toUpper());
    painter->drawText(490,293,255,80,Qt::AlignLeft,GameMnr->getPlayer().getTeamPokemon(0).getName().toUpper());

    painter->setFont(*GameMnr->getRscMng().fontFL30);
    painter->drawText(329,83,255,80,Qt::AlignLeft,QString::number(m_pokemon->getLevel()));
    painter->drawText(755,297,255,80,Qt::AlignLeft,QString::number(GameMnr->getPlayer().getTeamPokemon(0).getLevel()));
    painter->drawText(520,358,255,80,Qt::AlignRight,QString::number(GameMnr->getPlayer().getTeamPokemon(0).getPv())+"/"+QString::number(GameMnr->getPlayer().getTeamPokemon(0).getPvMax()));

    painter->setPen(*GameMnr->getRscMng().penGrey);
    painter->setFont(*GameMnr->getRscMng().fontFL40);
    painter->drawText(43,482,"What will");
    painter->drawText(43,542,GameMnr->getPlayer().getTeamPokemon(0).getName().toUpper()+" do?");
    painter->setPen(*GameMnr->getRscMng().penWhite);
    painter->drawText(40,480,"What will");
    painter->drawText(40,540,GameMnr->getPlayer().getTeamPokemon(0).getName().toUpper()+" do?");

    m_screen->setPixmap(*m_frame);
}

void StateFight::DrawMovesMenu()
{
    painter->setPen(*GameMnr->getRscMng().penDarkGrey);
    painter->setFont(*GameMnr->getRscMng().fontFL37);
    painter->drawImage(QPoint(0,410),GameMnr->getRscMng().fightAttacksMenu->scaled(832,163,Qt::IgnoreAspectRatio));

    painter->drawText(QPoint(65,475),GameMnr->getPlayer().getTeamPokemon(0).getMove(0)->getName().toUpper());
    if (GameMnr->getPlayer().getTeamPokemon(0).getMove(1) != 0){
        painter->drawText(QPoint(300,475),GameMnr->getPlayer().getTeamPokemon(0).getMove(1)->getName().toUpper());
    }
    else
    {
        painter->drawText(QPoint(300,475),"-");
    }
    if (GameMnr->getPlayer().getTeamPokemon(0).getMove(2) != 0){
        painter->drawText(QPoint(65,535),GameMnr->getPlayer().getTeamPokemon(0).getMove(2)->getName().toUpper());
    }
    else{
        painter->drawText(QPoint(65,535),"-");

    }
    if (GameMnr->getPlayer().getTeamPokemon(0).getMove(3) != 0){
        painter->drawText(QPoint(300,535),GameMnr->getPlayer().getTeamPokemon(0).getMove(3)->getName().toUpper());
    }
    else{
        painter->drawText(QPoint(300,535),"-");
    }

    switch (moveChoice){
        case 0:
            painter->drawImage(QPoint(40,447),GameMnr->getRscMng().fightArrow->scaled(30,30,Qt::KeepAspectRatio));
            break;
        case 1:
            painter->drawImage(QPoint(275,447),GameMnr->getRscMng().fightArrow->scaled(30,30,Qt::KeepAspectRatio));
            break;
        case 2:
            painter->drawImage(QPoint(40,507),GameMnr->getRscMng().fightArrow->scaled(30,30,Qt::KeepAspectRatio));
            break;
        case 3:
            painter->drawImage(QPoint(275,507),GameMnr->getRscMng().fightArrow->scaled(30,30,Qt::KeepAspectRatio));
            break;
    }

    painter->setFont(*GameMnr->getRscMng().fontFL42);

    painter->drawText(QPoint(665,540),GameMnr->getPlayer().getTeamPokemon(0).getMove(moveChoice)->getType().toUpper());

    painter->drawText(QPoint(701,481),QString::number(GameMnr->getPlayer().getTeamPokemon(0).getMove(moveChoice)->getPp()));
    painter->drawText(QPoint(762,481),QString::number(GameMnr->getPlayer().getTeamPokemon(0).getMove(moveChoice)->getPpMax()));

    m_screen->setPixmap(*m_frame);
}
void StateFight::PlayerAttacks()
{
    painter->drawImage(QPoint(0,405),GameMnr->getRscMng().fightBar->scaled(832,171,Qt::IgnoreAspectRatio));
    painter->setPen(*GameMnr->getRscMng().penGrey);
    painter->setFont(*GameMnr->getRscMng().fontFL40);
    painter->drawText(43,482,GameMnr->getPlayer().getTeamPokemon(0).getName().toUpper()+ " used");
    painter->drawText(43,542,GameMnr->getPlayer().getTeamPokemon(0).getMove(moveChoice)->getName().toUpper()+"!");
    painter->setPen(*GameMnr->getRscMng().penWhite);
    painter->drawText(40,480,GameMnr->getPlayer().getTeamPokemon(0).getName().toUpper()+ " used");
    painter->drawText(40,540,GameMnr->getPlayer().getTeamPokemon(0).getMove(moveChoice)->getName().toUpper()+"!");
    m_screen->setPixmap(*m_frame);
}
void StateFight::PokemonAttacks()
{
    randomMove = rand()%4;
    painter->drawImage(QPoint(0,405),GameMnr->getRscMng().fightBar->scaled(832,171,Qt::IgnoreAspectRatio));
    painter->setPen(*GameMnr->getRscMng().penGrey);
    painter->setFont(*GameMnr->getRscMng().fontFL40);
    painter->drawText(43,482,m_pokemon->getName().toUpper()+ " used");
    painter->drawText(43,542,m_pokemon->getMove(randomMove)->getName().toUpper()+"!");
    painter->setPen(*GameMnr->getRscMng().penWhite);
    painter->drawText(40,480,m_pokemon->getName().toUpper()+ " used");
    painter->drawText(40,540,m_pokemon->getMove(randomMove)->getName().toUpper()+"!");
    m_screen->setPixmap(*m_frame);
}

void StateFight::CalculateDammage()
{
    int damages;
    if (GameMnr->getPlayer().getTeamPokemon(0).getMove(moveChoice)->getDamageClass() == "physical")
        damages = ((GameMnr->getPlayer().getTeamPokemon(0).getLevel()*0.4+2)*GameMnr->getPlayer().getTeamPokemon(0).getAttack()*GameMnr->getPlayer().getTeamPokemon(0).getMove(moveChoice)->getPower())/(m_pokemon->getDefense()*50)+2;
    else if (GameMnr->getPlayer().getTeamPokemon(0).getMove(moveChoice)->getDamageClass() == "special")
        damages = ((GameMnr->getPlayer().getTeamPokemon(0).getLevel()*0.4+2)*GameMnr->getPlayer().getTeamPokemon(0).getSpeAttack()*GameMnr->getPlayer().getTeamPokemon(0).getMove(moveChoice)->getPower())/(m_pokemon->getSpeDefense()*50)+2;
    else
        damages = 0;
    float stab;
    if (GameMnr->getPlayer().getTeamPokemon(0).getMove(moveChoice)->getType() == GameMnr->getPlayer().getTeamPokemon(0).getTypeStr(0) || GameMnr->getPlayer().getTeamPokemon(0).getMove(moveChoice)->getType() == GameMnr->getPlayer().getTeamPokemon(0).getTypeStr(1))
        stab = 1.5;
    else
        stab = 1.0;
    float efficacy[2]={1.0,1.0};
    GameMnr->getDb().open();
    QSqlQuery query;
    query.prepare("select * from type_efficacy where damage_type_id=? and target_type_id=? or damage_type_id=? and target_type_id=?");
    query.addBindValue(GameMnr->getPlayer().getTeamPokemon(0).getMove(moveChoice)->getTypeInt());
    query.addBindValue(m_pokemon->getType(0));
    query.addBindValue(GameMnr->getPlayer().getTeamPokemon(0).getMove(moveChoice)->getTypeInt());
    query.addBindValue(m_pokemon->getType(1));
    int cpt=0;
    if(query.exec())
    {
        while(query.next())
            {
             efficacy[cpt] = query.value(2).toFloat()/100.0;
             cpt++;
            }
    }
    lastMoveAnalyses[1]=efficacy[0]*efficacy[1];
    GameMnr->getDb().close();
    int criticalRate;
    if ((rand()%16)+1 == 16){
        criticalRate = 2;
        lastMoveAnalyses[0]=1;
    }
    else{
        criticalRate = 1;
        lastMoveAnalyses[0]=0;
    }

    float randomDamage = float(((rand()%(100-84))+85))/100;

    m_pokemon->receiveDamages(damages*stab*efficacy[0]*efficacy[1]*criticalRate*randomDamage);
    GameMnr->getPlayer().getTeamPokemon(0).getMove(moveChoice)->consumePp();
}
void StateFight::AnalyseLastMove()
{
    analyseState++;
    if (!lastMoveAnalyses[0] && lastMoveAnalyses[1]!=1 && analyseState==1)
        analyseState++;
    if (analyseState == 3 || (!lastMoveAnalyses[0] && lastMoveAnalyses[1]==1) || (lastMoveAnalyses[1]==1 && analyseState==2)){
        analyseState=0;
        if (isPokemonDead()){
            state = "END";
            return;
        }
        else{
            if (state == "ANALYSE1"){
                state = "ROUND2";
                Draw();
                PokemonAttacks();
            }
            else{
                state = "BEGIN";
                Draw();
            }
            return;
        }
    }
    else{
        if (lastMoveAnalyses[0]){
            if (analyseState==1){
                painter->drawImage(QPoint(0,405),GameMnr->getRscMng().fightBar->scaled(832,171,Qt::IgnoreAspectRatio));
                painter->setPen(*GameMnr->getRscMng().penGrey);
                painter->setFont(*GameMnr->getRscMng().fontFL40);
                painter->drawText(43,482,"A critical hit!");
                painter->setPen(*GameMnr->getRscMng().penWhite);
                painter->drawText(40,480,"A critical hit!");
                m_screen->setPixmap(*m_frame);
            }
        }
        if (lastMoveAnalyses[1]>1.0){
            if (analyseState==2){
                painter->drawImage(QPoint(0,405),GameMnr->getRscMng().fightBar->scaled(832,171,Qt::IgnoreAspectRatio));
                painter->setPen(*GameMnr->getRscMng().penGrey);
                painter->setFont(*GameMnr->getRscMng().fontFL40);
                painter->drawText(43,482,"It's super effective!");
                painter->setPen(*GameMnr->getRscMng().penWhite);
                painter->drawText(40,480,"It's super effective!");
                m_screen->setPixmap(*m_frame);
            }
        }
        else if (lastMoveAnalyses[1]<1.0){
            if (analyseState==2){
                painter->drawImage(QPoint(0,405),GameMnr->getRscMng().fightBar->scaled(832,171,Qt::IgnoreAspectRatio));
                painter->setPen(*GameMnr->getRscMng().penGrey);
                painter->setFont(*GameMnr->getRscMng().fontFL40);
                painter->drawText(43,482,"It's not really effective...");
                painter->setPen(*GameMnr->getRscMng().penWhite);
                painter->drawText(40,480,"It's not really effective...");
                m_screen->setPixmap(*m_frame);
            }
        }
    }

}
void StateFight::CalculatePlayerDammage()
{
    int damages;
    if (m_pokemon->getMove(randomMove)->getDamageClass() == "physical")
        damages = ((m_pokemon->getLevel()*0.4+2)*m_pokemon->getAttack()*m_pokemon->getMove(randomMove)->getPower())/(GameMnr->getPlayer().getTeamPokemon(0).getDefense()*50)+2;
    else if (m_pokemon->getMove(randomMove)->getDamageClass() == "special")
        damages = ((m_pokemon->getLevel()*0.4+2)*m_pokemon->getSpeAttack()*m_pokemon->getMove(randomMove)->getPower())/(GameMnr->getPlayer().getTeamPokemon(0).getSpeDefense()*50)+2;
    else
        damages = 0;
    float stab;
    if (m_pokemon->getMove(randomMove)->getType() == m_pokemon->getTypeStr(0) || m_pokemon->getMove(randomMove)->getType() == m_pokemon->getTypeStr(1))
        stab = 1.5;
    else
        stab = 1.0;
    float efficacy[2]={1.0,1.0};
    GameMnr->getDb().open();
    QSqlQuery query;
    query.prepare("select * from type_efficacy where damage_type_id=? and target_type_id=? or damage_type_id=? and target_type_id=?");
    query.addBindValue(m_pokemon->getMove(moveChoice)->getTypeInt());
    query.addBindValue(GameMnr->getPlayer().getTeamPokemon(0).getType(0));
    query.addBindValue(m_pokemon->getMove(moveChoice)->getTypeInt());
    query.addBindValue(GameMnr->getPlayer().getTeamPokemon(0).getType(1));
    int cpt=0;
    if(query.exec())
    {
        while(query.next())
            {
             efficacy[cpt] = query.value(2).toFloat()/100.0;
             cpt++;
            }
    }
    lastMoveAnalyses[1]=efficacy[0]*efficacy[1];
    GameMnr->getDb().close();
    int criticalRate;
    if ((rand()%16)+1 == 16){
        criticalRate = 2;
        lastMoveAnalyses[0]=1;
    }
    else{
        criticalRate = 1;
        lastMoveAnalyses[0]=0;
    }

    float randomDamage = float(((rand()%(100-84))+85))/100;

    GameMnr->getPlayer().getTeamPokemon(0).receiveDamages(damages*stab*efficacy[0]*efficacy[1]*criticalRate*randomDamage);
    m_pokemon->getMove(randomMove)->consumePp();
}

bool StateFight::isPokemonDead()
{
    if (m_pokemon->getPv() == 0){
        painter->drawImage(QPoint(0,405),GameMnr->getRscMng().fightBar->scaled(832,171,Qt::IgnoreAspectRatio));
        painter->setPen(*GameMnr->getRscMng().penGrey);
        painter->setFont(*GameMnr->getRscMng().fontFL40);
        painter->drawText(43,482,"Wild "+ m_pokemon->getName().toUpper());
        painter->drawText(43,542, "fainted!");
        painter->setPen(*GameMnr->getRscMng().penWhite);
        painter->drawText(40,480,"Wild "+ m_pokemon->getName().toUpper());
        painter->drawText(40,540, "fainted!");
        m_screen->setPixmap(*m_frame);

        return true;
    }
    else
        return false;
}
void StateFight::CalculateExp()
{
    int exp = m_pokemon->getBaseExperience()*m_pokemon->getLevel()/7;
    GameMnr->getPlayer().getTeamPokemon(0).receiveExp(exp);
    Draw();
    painter->drawImage(QPoint(0,405),GameMnr->getRscMng().fightBar->scaled(832,171,Qt::IgnoreAspectRatio));
    painter->setPen(*GameMnr->getRscMng().penGrey);
    painter->setFont(*GameMnr->getRscMng().fontFL40);
    painter->drawText(43,482,GameMnr->getPlayer().getTeamPokemon(0).getName().toUpper() + " gained");
    painter->drawText(43,542, QString::number(exp)+" EXP. Points!");
    painter->setPen(*GameMnr->getRscMng().penWhite);
    painter->drawText(40,480,GameMnr->getPlayer().getTeamPokemon(0).getName().toUpper() + " gained");
    painter->drawText(40,540, QString::number(exp)+" EXP. Points!");
    m_screen->setPixmap(*m_frame);
}

void StateFight::Release()
{

}
