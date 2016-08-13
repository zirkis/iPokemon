#ifndef RESSOURCEMANAGER_H
#define RESSOURCEMANAGER_H

#include <tile.h>

class RessourceManager
{
public:
    RessourceManager();
    Tile getTiles(int i)const;

    // Fonts
    QFont *fontFL45;
    QFont *fontFL42;
    QFont *fontFL40;
    QFont *fontFL37;
    QFont *fontFL35;
    QFont *fontFL32;
    QFont *fontFL30;

    // Pens
    QPen *penGrey;
    QPen *penDarkGrey;
    QPen *penWhite;
    QPen *penBlack;
    QPen *penShadow;

    // State Pause
    QImage *frameLU;
    QImage *frameMU;
    QImage *frameRU;
    QImage *frameLM;
    QImage *frameLB;
    QImage *frameRM;
    QImage *frameRB;
    QImage *frameMB;

    // State Team
    QImage *menuPokemon;
    QImage *menuPokemonBottom;
    QImage *menuPokemonFrame;
    QImage *menuPokemonSquare;
    QImage *menuPokemonSquareSel;
    QImage *menuPokemonRect;
    QImage *menuPokemonRectSel;
    QImage *menuPokemonCancel;
    QImage *menuPokemonCancelSel;
    QImage *hpRed;
    QImage *hpYellow;
    QImage *hpGreen;
    QImage *male;
    QImage *female;

    // State Fight
    QImage *fightBackground;
    QImage *fightBar;
    QImage *fightMenu;
    QImage *fightPlayerStatus;
    QImage *fightPkmStatus;
    QImage *fightArrow;
    QImage *fightAttacksMenu;
    QImage *fightExp;
    QImage *fightMale;
    QImage *fightFemale;

    // State Bag
    QImage *backgroundBag;
    QImage *bagItem;
    QImage *bagKey;
    QImage *bagBall;
    QImage *bagLeft;
    QImage *bagMiddle;
    QImage *bagRight;
    QImage *bagArrow;
    QImage *bagArrowLeft;
    QImage *bagArrowRight;

    // State Pokemon
    QImage *pokemonInfoBackground;
    QImage *pokemonSkillsBackground;
    QImage *pokemonMovesBackground;
    QImage *pokemonExp;

    // Types
//    QImage *typeNormal;
//    QImage *typeFight;
//    QImage *typeFlying;
//    QImage *typePoison;
//    QImage *typeGround;
//    QImage *typeRock;
//    QImage *typeBug;
//    QImage *typeGhost;
//    QImage *typeSteel;
//    QImage *typeUnknown;
//    QImage *typeFire;
//    QImage *typeWater;
//    QImage *typeGrass;
//    QImage *typeElectr;
//    QImage *typePsychc;
//    QImage *typeIce;
//    QImage *typeDragon;
//    QImage *typeDark;




private:
    Tile *tiles[17];


};

#endif // RESSOURCEMANAGER_H
