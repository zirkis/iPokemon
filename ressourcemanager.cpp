#include "ressourcemanager.h"

RessourceManager::RessourceManager()
{
    QImage *tileset = new QImage("/users/Benjamin/iPokemon/tileset.png");
    QImage tilesTable[256];
    int cpt=0;
    for (int i=0;i<2048;i+=64){
        for (int j=0;j<512;j+=64){
            tilesTable[cpt]=tileset->copy(j,i,64,64);
            cpt++;
        }
    }

    QImage tile0 = tileset->copy(64,0,64,64);

    tiles[0]= new Tile(true,tilesTable[10]);
    tiles[1]= new Tile(true,tilesTable[0]);
    tiles[2]= new Tile(false,tilesTable[200]);
    tiles[3]= new Tile(false,tilesTable[30]);
    tiles[4]= new Tile(true,tilesTable[8]);
    tiles[5]= new Tile(false,tilesTable[6]);
    tiles[6]= new Tile(false,tilesTable[6]);
    tiles[7]= new Tile(false,tilesTable[6]);
    tiles[8]= new Tile(false,tilesTable[6]);
    tiles[9]= new Tile(false,tilesTable[6]);
    tiles[10]= new Tile(false,tilesTable[6]);
    tiles[11]= new Tile(false,tilesTable[6]);
    tiles[12]= new Tile(false,tilesTable[6]);
    tiles[13]= new Tile(false,tilesTable[6]);
    tiles[14]= new Tile(false,tilesTable[6]);
    tiles[15]= new Tile(false,tilesTable[6]);
    tiles[16]= new Tile(false,tilesTable[6]);

    fontFL45 = new QFont("Pokemon FireLeaf",45);
    fontFL42 = new QFont("Pokemon FireLeaf",42);
    fontFL40 = new QFont("Pokemon FireLeaf",40);
    fontFL37 = new QFont("Pokemon FireLeaf",37);
    fontFL35 = new QFont("Pokemon FireLeaf",35);
    fontFL32 = new QFont("Pokemon FireLeaf",32);
    fontFL30 = new QFont("Pokemon FireLeaf",30);

    penGrey = new QPen(QColor(100,100,100));
    penDarkGrey = new QPen(QColor(66,66,66));
    penWhite = new QPen((Qt::white));
    penBlack = new QPen((Qt::black));
    penShadow = new QPen(QColor(213,207,176));

    frameLU = new QImage("/users/Benjamin/iPokemon/frame/LUframe.png");
    frameMU = new QImage("/users/Benjamin/iPokemon/frame/MUframe.png");
    frameRU = new QImage("/users/Benjamin/iPokemon/frame/RUframe.png");
    frameLM = new QImage("/users/Benjamin/iPokemon/frame/LMframe.png");
    frameLB = new QImage("/users/Benjamin/iPokemon/frame/LBframe.png");
    frameRM = new QImage("/users/Benjamin/iPokemon/frame/RMframe.png");
    frameRB = new QImage("/users/Benjamin/iPokemon/frame/RBframe.png");
    frameMB = new QImage("/users/Benjamin/iPokemon/frame/MBframe.png");

    menuPokemon = new QImage("/users/Benjamin/iPokemon/menu/menuPokemon.png");
    menuPokemonBottom = new QImage("/users/Benjamin/iPokemon/menu/menuTeamBottom.png");
    menuPokemonFrame = new QImage("/users/Benjamin/iPokemon/menu/menuPokemonFrame.png");
    menuPokemonSquare = new QImage("/users/Benjamin/iPokemon/menu/menuPokemonSquare.png");
    menuPokemonSquareSel = new QImage("/users/Benjamin/iPokemon/menu/menuPokemonSquareSel.png");
    menuPokemonRect = new QImage("/users/Benjamin/iPokemon/menu/menuPokemonRect.png");
    menuPokemonRectSel = new QImage("/users/Benjamin/iPokemon/menu/menuPokemonRectSel.png");
    menuPokemonCancel = new QImage("/users/Benjamin/iPokemon/menu/menuPokemonCancel.png");
    menuPokemonCancelSel = new QImage("/users/Benjamin/iPokemon/menu/menuPokemonCancelSel.png");

    fightBackground = new QImage("/users/Benjamin/iPokemon/battleBackground/battleBackgroundgrass.png");
    fightBar = new QImage("/users/Benjamin/iPokemon/menu/fightBar.png");
    fightMenu = new QImage("/users/Benjamin/iPokemon/menu/fightMenu.png");
    fightPlayerStatus = new QImage("/users/Benjamin/iPokemon/menu/fightPlayerStatus.png");
    fightPkmStatus = new QImage("/users/Benjamin/iPokemon/menu/fightPkmStatus.png");
    fightArrow = new QImage("/users/Benjamin/iPokemon/menu/fightArrow.png");
    fightAttacksMenu = new QImage("/users/Benjamin/iPokemon/menu/fightAttacks.png");
    fightExp = new QImage("/users/Benjamin/iPokemon/menu/fightExp.png");
    fightMale = new QImage("/users/Benjamin/iPokemon/menu/fightMale.png");
    fightFemale = new QImage("/users/Benjamin/iPokemon/menu/fightFemale.png");

    hpRed = new QImage ("/users/Benjamin/iPokemon/menu/hpRed.png");
    hpYellow = new QImage ("/users/Benjamin/iPokemon/menu/hpYellow.png");
    hpGreen = new QImage ("/users/Benjamin/iPokemon/menu/hpGreen.png");
    male = new QImage ("/users/Benjamin/iPokemon/menu/male.png");
    female = new QImage ("/users/Benjamin/iPokemon/menu/female.png");


    backgroundBag = new QImage("/users/Benjamin/iPokemon/menu/backgroundBag.png");
    bagItem = new QImage("/users/Benjamin/iPokemon/menu/bagItem.png");
    bagKey = new QImage("/users/Benjamin/iPokemon/menu/bagKey.png");
    bagBall = new QImage("/users/Benjamin/iPokemon/menu/bagBall.png");
    bagLeft = new QImage("/users/Benjamin/iPokemon/menu/bagLeft.png");
    bagMiddle = new QImage("/users/Benjamin/iPokemon/menu/bagMiddle.png");
    bagRight = new QImage("/users/Benjamin/iPokemon/menu/bagRight.png");
    bagArrow = new QImage("/users/Benjamin/iPokemon/menu/bagArrow.png");
    bagArrowLeft = new QImage("/users/Benjamin/iPokemon/menu/bagArrowLeft.png");
    bagArrowRight = new QImage("/users/Benjamin/iPokemon/menu/bagArrowRight.png");

    pokemonInfoBackground = new QImage("/users/Benjamin/iPokemon/menu/pokemonView.png");
    pokemonSkillsBackground = new QImage("/users/Benjamin/iPokemon/menu/pokemonSkills.png");
    pokemonMovesBackground = new QImage("/users/Benjamin/iPokemon/menu/pokemonMoves.png");
    pokemonExp = new QImage("/users/Benjamin/iPokemon/menu/exp.png");

//    typeNormal = new QImage("/users/Benjamin/iPokemon/type/normal.png");
//    typeFight = new QImage("/users/Benjamin/iPokemon/type/fight.png");
//    typeFlying = new QImage("/users/Benjamin/iPokemon/type/flying.png");
//    typePoison = new QImage("/users/Benjamin/iPokemon/type/poison.png");
//    typeGround = new QImage("/users/Benjamin/iPokemon/type/ground.png");
//    typeRock = new QImage("/users/Benjamin/iPokemon/type/rock.png");
//    typeBug = new QImage("/users/Benjamin/iPokemon/type/bug.png");
//    typeGhost = new QImage("/users/Benjamin/iPokemon/type/ghost.png");
//    typeSteel = new QImage("/users/Benjamin/iPokemon/type/steel.png");
//    typeUnknown = new QImage("/users/Benjamin/iPokemon/type/???.png");
//    typeFire = new QImage("/users/Benjamin/iPokemon/type/fire.png");
//    typeWater = new QImage("/users/Benjamin/iPokemon/type/water.png");
//    typeGrass = new QImage("/users/Benjamin/iPokemon/type/grass.png");
//    typeElectr = new QImage("/users/Benjamin/iPokemon/type/electr.png");
//    typePsychc = new QImage("/users/Benjamin/iPokemon/type/psychc.png");
//    typeIce = new QImage("/users/Benjamin/iPokemon/type/ice.png");
//    typeDragon = new QImage("/users/Benjamin/iPokemon/type/dragon.png");
//    typeDark = new QImage("/users/Benjamin/iPokemon/type/dark.png");

}

Tile RessourceManager::getTiles(int i)const
{
    return *tiles[i];
}

