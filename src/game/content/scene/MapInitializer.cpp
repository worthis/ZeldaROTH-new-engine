#include "MapInitializer.h"

#include "Map.h"

#include "../../MainController.h"

#include "../objects/Pierre.h"
#include "../objects/Pancarte.h"
#include "../objects/Pnj.h"
#include "../objects/Poule.h"
#include "../objects/Coffre.h"
#include "../objects/PiegePics.h"
#include "../objects/PiegeFeu.h"
#include "../objects/PiegeDemi.h"
#include "../objects/Jarre.h"
#include "../objects/Sphere.h"
#include "../objects/Caisse.h"
#include "../objects/Interrupteur.h"
#include "../objects/PiegeMain.h"
#include "../objects/TalkableArea.h"

#include "../ennemis/Ennemi001.h"
#include "../ennemis/Ennemi002.h"
#include "../ennemis/Ennemi003.h"
#include "../ennemis/Ennemi004.h"
#include "../ennemis/Ennemi005.h"
#include "../ennemis/Ennemi006.h"
#include "../ennemis/Ennemi008.h"
#include "../ennemis/Ennemi009.h"
#include "../ennemis/Ennemi010.h"
#include "../ennemis/Ennemi011.h"
#include "../ennemis/Ennemi012.h"
#include "../ennemis/Ennemi013.h"
#include "../ennemis/Ennemi014.h"
#include "../ennemis/Ennemi015.h"
#include "../ennemis/Ennemi016.h"
#include "../ennemis/Ennemi018.h"
#include "../ennemis/Ennemi019.h"
#include "../ennemis/Ennemi021.h"
#include "../ennemis/Ennemi022.h"
#include "../ennemis/Ennemi023.h"
#include "../ennemis/Ennemi024.h"
#include "../ennemis/Ennemi025.h"
#include "../ennemis/Ennemi026.h"
#include "../ennemis/Ennemi027.h"
#include "../ennemis/Ennemi028.h"
#include "../ennemis/Ennemi029.h"
#include "../ennemis/Ennemi030.h"
#include "../ennemis/Ennemi031.h"
#include "../ennemis/Ennemi032.h"
#include "../ennemis/Ennemi033.h"
#include "../ennemis/Ennemi034.h"
#include "../ennemis/Ennemi035.h"
#include "../ennemis/Ennemi037.h"
#include "../ennemis/Ennemi038.h"
#include "../ennemis/Ennemi039.h"
#include "../ennemis/Ennemi040.h"
#include "../ennemis/Ennemi041.h"
#include "../ennemis/Ennemi042.h"
#include "../ennemis/Ennemi043.h"
#include "../ennemis/Ennemi044.h"
#include "../ennemis/Ennemi045.h"
#include "../ennemis/Ennemi046.h"
#include "../ennemis/Ennemi047.h"
#include "../ennemis/Ennemi048.h"
#include "../ennemis/Ennemi050.h"
#include "../ennemis/Ennemi053.h"

/*
#include "../objects/Switch.h"
#include "../objects/Stele.h"
#include "../objects/Tombe.h"
*/

MapInitializer::MapInitializer(Map* m) : map(m) {
}

MapInitializer::~MapInitializer() {
}


void MapInitializer::addEnnemi(Ennemi* ennemi) {
    map->addEnnemi(ennemi);
}

void MapInitializer::addItem(Item* item) {
    map->addItem(item);
}

void MapInitializer::addObject(Object* object) {
    map->addObject(object);
}

void MapInitializer::ouvrePorte(int x, int y, int type) {
    map->ouvrePorte(x, y, type);
}


void MapInitializer::init() {
    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Link* link = scene->getLink();
    Inventory* inventory = link->getInventory();

    /*if (scene->getAvancement() == AV_GARDE_MOVE) {
        scene->setAvancement(AV_GARDE_OUT);
    }*/

    //int tmp = 0;
    switch (map->getId()) {
        case 1 :
            addObject(new Pierre(16*23, 16*6, 1, map));
            addObject(new Pierre(16*42, 16*10, 1, map));
            addObject(new Pierre(16*22, 16*18, 1, map));
            addObject(new Pierre(16*40, 16*21, 1, map));
            addObject(new Pierre(16*32, 16*26, 1, map));
            addObject(new Pierre(16*36, 16*39, 1, map));
            addObject(new Pierre(16*56, 16*41, 1, map));
            addObject(new Pierre(16*21, 16*46, 1, map));
            addObject(new Pierre(16*4, 16*54, 1, map));
            addObject(new Pierre(16*5, 16*55, 1, map));
            addObject(new Pierre(16*5, 16*56, 1, map));
            addObject(new Pierre(16*4, 16*57, 1, map));
            addObject(new Pierre(16*42, 16*65, 1, map));
            addObject(new Pierre(16*29, 16*71, 1, map));
            addObject(new Pierre(16*14, 16*4, 2, map));
            addObject(new Pierre(16*15, 16*5, 2, map));
            addObject(new Pierre(16*6, 16*24, 2, map));
            addObject(new Pierre(16*12, 16*40, 2, map));
            addObject(new Pancarte(16*28, 16*45, 151, map));
            addObject(new Pancarte(16*48, 16*29, 152, map));

            if (!inventory->hasQuartCoeur(0)) {
                addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 11*16 + 8, 13*16 + 8, 0));
            }
            if (!inventory->hasQuartCoeur(1)) {
                addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 12*16, 34*16 + 8, 1));
            }
            if (!inventory->hasQuartCoeur(2)) {
                addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 13*16, 29*16, 2));
            }
            if (!inventory->hasQuartCoeur(3)) {
                addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 14*16, 71*16 + 8, 3));
            }

            if (!link->getEpee()) {
                addItem(ItemHelper::getInstance()->createItem(TI_EPEE_1, 51*16 + 8, 66*16));
            }

            addEnnemi(new Ennemi003(53*16+2, 46*16-1));
            addEnnemi(new Ennemi003(46*16+2, 38*16-1));
            addEnnemi(new Ennemi003(53*16+2, 63*16-1));
            addEnnemi(new Ennemi003(35*16+2, 8*16-1));

            addEnnemi(new Ennemi004(4*16, 32*16-1));
            addEnnemi(new Ennemi004(10*16, 67*16-1));
            addEnnemi(new Ennemi004(14*16, 53*16-1));
            addEnnemi(new Ennemi004(27*16, 70*16-1));

            if (scene->getCoffre(0, 0)) {
                ouvrePorte(50, 1, 0);
            }

            break;
        case 2 :
            addObject(new Pierre(16*20, 16*28, 1, map));
            addObject(new Pierre(16*26, 16*9, 1, map));
            addObject(new Pierre(16*46, 16*51, 1, map));
            addObject(new Pierre(16*66, 16*9, 1, map));
            addObject(new Pierre(16*92, 16*28, 1, map));

            addObject(new Pierre(16*53, 16*15, 2, map));
            addObject(new Pierre(16*61, 16*45, 2, map));
            addObject(new Pierre(16*96, 16*51, 2, map));

            addObject(new Pancarte(16*34, 16*9, 153, map));
            addObject(new Pancarte(16*48, 16*49, 154, map));
            addObject(new Pancarte(16*87, 16*48, 155, map));
            addObject(new Pancarte(16*94, 16*10, 156, map));

            if (!inventory->hasQuartCoeur(4)) {
                addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 34*16 + 8, 16*16 + 8, 4));
            }
            if (!inventory->hasQuartCoeur(5)) {
                addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 12*16 + 8, 29*16 + 8, 5));
            }
            if (!inventory->hasQuartCoeur(6)) {
                addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 11*16 + 8, 4*16 + 8, 6));
            }
            if (!inventory->hasQuartCoeur(7)) {
                addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 65*16 + 8, 54*16 + 8, 7));
            }

            addEnnemi(new Ennemi008(70*16,25*16));
            addEnnemi(new Ennemi008(33*16,20*16));
            addEnnemi(new Ennemi008(20*16,21*16));
            addEnnemi(new Ennemi008(88*16,28*16));
            addEnnemi(new Ennemi008(45*16,37*16));

            addEnnemi(new Ennemi053(76*16,44*16));
            addEnnemi(new Ennemi053(54*16,43*16));
            addEnnemi(new Ennemi053(10*16,44*16));
            addEnnemi(new Ennemi053(25*16,33*16));
            addEnnemi(new Ennemi053(78*16,13*16));
            addEnnemi(new Ennemi053(49*16,21*16));
            break;
        case 3 :
            addObject(new Pierre(16*9, 16*5, 1, map));
            addObject(new Pierre(16*21, 16*7, 1, map));
            addObject(new Pierre(16*38, 16*11, 1, map));
            addObject(new Pierre(16*88, 16*40, 1, map));

            addObject(new Pierre(16*61, 16*12, 2, map));

            addObject(new Pancarte(16*2, 16*22, 157, map));
            addObject(new Pancarte(16*3, 16*49, 157, map));
            addObject(new Pancarte(16*12, 16*6, 158, map));
            addObject(new Pancarte(16*30, 16*45, 159, map));
            addObject(new Pancarte(16*90, 16*38, 160, map));
            addObject(new Pancarte(16*94, 16*4, 161, map));
            addObject(new Pancarte(16*120, 16*5, 161, map));
            addObject(new Pancarte(16*134, 16*44, 162, map));

            if (!inventory->hasQuartCoeur(8)) {
                addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 90*16, 25*16 + 8, 8));
            }
            if (!inventory->hasQuartCoeur(9)) {
                addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 69*16, 37*16, 9));
            }
            addEnnemi(new Ennemi009(16*16,9*16));
            addEnnemi(new Ennemi009(53*16,7*16));
            addEnnemi(new Ennemi009(91*16,34*16));

            addEnnemi(new Ennemi010(33*16,22*16));
            addEnnemi(new Ennemi010(57*16,43*16));
            addEnnemi(new Ennemi010(61*16,18*16));
            addEnnemi(new Ennemi010(79*16,24*16));
            addEnnemi(new Ennemi010(100*16,42*16));

            if (scene->getCoffre(0, 1)) {
                ouvrePorte(121, 10, 0);
            }

            if (scene->getCoffre(0, 2)) {
                ouvrePorte(49, 36, 1);
            }
            break;
        case 4 :
            addObject(new Pancarte(16*4, 16*50, 163, map));
            addObject(new Pancarte(16*26, 16*49, 164, map));
            addObject(new Pancarte(16*30, 16*3, 165, map));
            addObject(new Pancarte(16*37, 16*52, 166, map));

            addObject(new Pnj(16*28, 16*15+8, 7, 170));
            addObject(new Pnj(16*15, 16*27, 9, 167));
            addObject(new Pnj(16*42, 16*35, 10, 168));
            addObject(new Pnj(16*28+8, 16*33, 11, 169));

            addObject(new Poule(16*42, 16*38));
            addObject(new Poule(16*43, 16*37));
            addObject(new Poule(16*44, 16*39));
            addObject(new Poule(16*46, 16*35));
            addObject(new Poule(16*44, 16*35));
            break;
        case 5 :
            addObject(new Pierre(16*7, 16*38, 1, map));
            addObject(new Pierre(16*18, 16*26, 1, map));
            addObject(new Pierre(16*48, 16*56, 1, map));

            addObject(new Pierre(16*15, 16*53, 2, map));

            addObject(new Pancarte(16*41, 16*55, 176, map));
            addObject(new Pancarte(16*46, 16*51, 177, map));
            addObject(new Pancarte(16*90, 16*48, 178, map));

            if (scene->getAvancement() == AV_ZELDA_SUIT) {
                addObject(new Pnj(16*63+8, 16*16+9, 15, 224));
            }

            if (!inventory->hasQuartCoeur(10)) {
                addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 15*16 + 8, 8*16 + 8, 10));
            }
            if (!inventory->hasQuartCoeur(11)) {
                addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 58*16 + 8, 46*16 + 8, 11));
            }

            break;
        case 6 :
            addObject(new Pierre(16*12, 16*17, 1, map));
            addObject(new Pierre(16*13, 16*39, 1, map));
            addObject(new Pierre(16*22, 16*20, 1, map));
            addObject(new Pierre(16*48, 16*28, 1, map));
            addObject(new Pierre(16*71, 16*7, 1, map));
            addObject(new Pierre(16*86, 16*10, 1, map));
            addObject(new Pierre(16*96, 16*28, 1, map));
            addObject(new Pierre(16*110, 16*38, 1, map));
            addObject(new Pierre(16*115, 16*4, 1, map));

            addObject(new Pierre(16*43, 16*24, 2, map));
            addObject(new Pierre(16*52, 16*3, 2, map));
            addObject(new Pierre(16*70, 16*33, 2, map));
            addObject(new Pierre(16*113, 16*35, 2, map));

            addObject(new Pancarte(16*8, 16*36, 179, map));
            addObject(new Pancarte(16*25, 16*7, 180, map));
            addObject(new Pancarte(16*50, 16*36, 181, map));

            if (!inventory->hasQuartCoeur(12)) {
                addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 36*16 + 8, 27*16 + 8, 12));
            }
            if (!inventory->hasQuartCoeur(13)) {
                addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 59*16 + 8, 19*16 + 8, 13));
            }
            if (!inventory->hasQuartCoeur(14)) {
                addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 110*16, 17*16, 14));
            }

            addEnnemi(new Ennemi005(92*16,32*16-10));
            addEnnemi(new Ennemi005(101*16,25*16-10));
            addEnnemi(new Ennemi005(107*16,25*16-10));
            addEnnemi(new Ennemi005(64*16,9*16-10));
            addEnnemi(new Ennemi005(32*16,18*16-10));

            addEnnemi(new Ennemi006(52*16,22*16-21));
            addEnnemi(new Ennemi006(101*16,12*16-21));
            addEnnemi(new Ennemi006(23*16,33*16-21));
            addEnnemi(new Ennemi006(12*16,7*16-21));
            break;
        case 7 :
            addObject(new Pierre(16*30, 16*3, 1, map));
            addObject(new Pierre(16*32, 16*23, 1, map));
            addObject(new Pierre(16*57, 16*12, 1, map));
            addObject(new Pierre(16*62, 16*29, 1, map));
            addObject(new Pierre(16*72, 16*17, 1, map));
            addObject(new Pierre(16*91, 16*12, 1, map));

            addObject(new Pierre(16*43, 16*35, 2, map));
            addObject(new Pierre(16*77, 16*3, 2, map));
            addObject(new Pierre(16*84, 16*28, 2, map));
            addObject(new Pierre(16*130, 16*34, 2, map));
            addObject(new Pierre(16*131, 16*35, 2, map));
            addObject(new Pierre(16*132, 16*35, 2, map));
            addObject(new Pierre(16*133, 16*34, 2, map));

            addObject(new Pancarte(16*11, 16*28, 182, map));
            addObject(new Pancarte(16*19, 16*35, 183, map));
            addObject(new Pancarte(16*61, 16*20, 184, map));
            addObject(new Pancarte(16*111, 16*36, 185, map));
            addObject(new Pancarte(16*128, 16*36, 186, map));

            if (!inventory->hasQuartCoeur(15)) {
                addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 42*16+8, 12*16+8, 15));
            }
            if (!inventory->hasQuartCoeur(16)) {
                addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 57*16+8, 32*16+8, 16));
            }
            if (!inventory->hasQuartCoeur(17)) {
                addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 70*16+8, 7*16+8, 17));
            }
            if (!inventory->hasQuartCoeur(18)) {
                addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 127*16+8, 4*16+8, 18));
            }
            if (!inventory->hasQuartCoeur(19)) {
                addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 133*16, 22*16, 19));
            }
            if (!inventory->hasQuartCoeur(20)) {
                addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 8*16, 42*16, 20));
            }

            addObject(new Pnj(16*113+8, 16*20+8, 12, 170));
            addObject(new Pnj(16*123, 16*32+8, 13, 187));
            addObject(new Pnj(16*108, 16*16+8, 14, 188));

            addEnnemi(new Ennemi013(83*16,35*16-4));
            addEnnemi(new Ennemi013(80*16,9*16-4));
            addEnnemi(new Ennemi013(71*16,28*16-4));
            addEnnemi(new Ennemi013(54*16,8*16-4));
            addEnnemi(new Ennemi013(40*16,15*16-4));
            addEnnemi(new Ennemi013(9*16,34*16-4));

            addEnnemi(new Ennemi014(65*16-12,15*16));
            addEnnemi(new Ennemi014(35*16-12,25*16));
            addEnnemi(new Ennemi014(54*16-12,28*16));
            addEnnemi(new Ennemi014(37*16-12,8*16));

            if (scene->getCoffre(0, 3)) {
                ouvrePorte(132, 24, 0);
            }
            break;
        case 8 :
            addObject(new Pierre(16*12, 16*83, 3, map));
            addObject(new Pierre(16*27, 16*41, 3, map));
            addObject(new Pierre(16*37, 16*57, 3, map));
            addObject(new Pierre(16*47, 16*45, 3, map));
            addObject(new Pierre(16*47, 16*47, 3, map));
            addObject(new Pierre(16*49, 16*37, 3, map));
            addObject(new Pierre(16*55, 16*69, 3, map));

            addObject(new Pancarte(16*5, 16*75, 189, map));
            addObject(new Pancarte(16*34, 16*27, 190, map));
            addObject(new Pancarte(16*34, 16*75, 191, map));
            addObject(new Pancarte(16*51, 16*12, 192, map));

            if (!inventory->hasQuartCoeur(21)) {
                addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 40*16+8, 45*16+8, 21));
            }

            addObject(new Pnj(16*20, 16*76 + 7, 1, 193));
            addObject(new Pnj(16*50, 16*78, 2, 170));

            if (scene->getAvancement() < AV_GARDE_DEPLACE) {
                addObject(new Pnj(16*30 + 8, 16*24 + 9, 3, 194));
            } else {
                addObject(new Pnj(16*28, 16*26, 3, 196));
            }

            addObject(new Pnj(16*8+8, 16*53+8-1, 4, 198));
            addObject(new Pnj(16*52+2, 16*33+8, 5, 199));
            addObject(new Pnj(16*50+8, 16*58+8, 6, 200));

            addEnnemi(new Ennemi011(13*16,57*16));
            addEnnemi(new Ennemi011(26*16,19*16));
            addEnnemi(new Ennemi011(34*16,81*16));
            addEnnemi(new Ennemi011(47*16,46*16));

            addEnnemi(new Ennemi012(40*16,19*16));
            addEnnemi(new Ennemi012(51*16,17*16));

            break;
        case 9 :
            addObject(new Pierre(16*84, 16*12, 1, map));
            addObject(new Pierre(16*98, 16*51, 1, map));
            addObject(new Pierre(16*102, 16*15, 1, map));

            addObject(new Pierre(16*27, 16*18, 2, map));
            addObject(new Pierre(16*28, 16*18, 2, map));
            addObject(new Pierre(16*66, 16*34, 2, map));
            addObject(new Pierre(16*90, 16*30, 2, map));
            addObject(new Pierre(16*91, 16*30, 2, map));
            addObject(new Pierre(16*92, 16*30, 2, map));
            addObject(new Pierre(16*93, 16*30, 2, map));
            addObject(new Pierre(16*93, 16*29, 2, map));

            addObject(new Pancarte(16*36, 16*43, 201, map));
            addObject(new Pancarte(16*98, 16*48, 202, map));
            addObject(new Pancarte(16*106, 16*22, 202, map));

            if (!inventory->hasQuartCoeur(22)) {
                addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 42*16, 34*16, 22));
            }
            if (!inventory->hasQuartCoeur(23)) {
                addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 70*16, 36*16, 23));
            }
            if (!inventory->hasQuartCoeur(24)) {
                addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 91*16+8, 29*16+8, 24));
            }

            addEnnemi(new Ennemi015(30*16,44*16));
            addEnnemi(new Ennemi015(48*16,30*16));
            addEnnemi(new Ennemi015(68*16,13*16));
            addEnnemi(new Ennemi015(68*16,52*16));

            if (scene->getCoffre(0, 4)) {
                ouvrePorte(27, 7, 0);
            }
            if (scene->getCoffre(0, 5)) {
                ouvrePorte(38, 38, 1);
            }
            break;
        case 10 :
            addObject(new Pierre(16*132, 16*6, 1, map));

            addEnnemi(new Ennemi016(40*16,5*16-8));
            addEnnemi(new Ennemi016(61*16,12*16-8));
            addEnnemi(new Ennemi016(92*16,12*16-8));
            addEnnemi(new Ennemi016(93*16,11*16-8));
            addEnnemi(new Ennemi016(94*16,10*16-8));
            addEnnemi(new Ennemi016(150*16,5*16-8));
            addEnnemi(new Ennemi016(151*16,6*16-8));
            addEnnemi(new Ennemi016(152*16,7*16-8));
            addEnnemi(new Ennemi016(153*16,8*16-8));
            addEnnemi(new Ennemi016(154*16,9*16-8));
            break;
        case 11 :
            addObject(new Pierre(16*93, 16*12, 1, map));
            addObject(new Pierre(16*128, 16*7, 1, map));

            addObject(new Pancarte(16*140, 16*5, 203, map));
            addObject(new Pancarte(16*154, 16*10, 204, map));

            addEnnemi(new Ennemi016(41*16,12*16-8));
            addEnnemi(new Ennemi016(55*16,12*16-8));
            addEnnemi(new Ennemi016(65*16,12*16-8));
            addEnnemi(new Ennemi016(77*16,6*16-8));
            addEnnemi(new Ennemi016(78*16,7*16-8));
            addEnnemi(new Ennemi016(79*16,8*16-8));
            addEnnemi(new Ennemi016(80*16,9*16-8));
            addEnnemi(new Ennemi016(81*16,10*16-8));

            if (scene->getCoffre(0, 6)) {
                ouvrePorte(155, 3, 0);
            }
            break;
        case 12 :
            if (!inventory->hasCristal(0)) {
                addEnnemi(new Ennemi019(118*16, 3*16));
            }
            addObject(new Coffre(49 * 16 + 8, 67 * 16, 0, scene->getCoffre(1, 0), TI_CARTE_DONJON));
            addObject(new Coffre(69 * 16 + 8, 52 * 16, 0, scene->getCoffre(1, 1), TI_BOUSSOLE));
            addObject(new Coffre(9 * 16 + 8, 22 * 16, 0, scene->getCoffre(1, 2), TI_CLE_BOSS));
            if (scene->getCoffre(1, 2) == 2) ouvrePorte(119, 13, 0);

            addObject(new Coffre(69 * 16, 21 * 16 + 8, 1, inventory->hasObject(GANTS), TI_GANT));

            addObject(new Coffre(9 * 16 + 8, 54 * 16 + 8, 0, scene->getCoffre(1, 4), TI_CLE, 4));
            addObject(new Coffre(39 * 16 + 8, 7 * 16, 0, scene->getCoffre(1, 5), TI_CLE, 5));
            addObject(new Coffre(69 * 16 + 8, 67 * 16, 0, scene->getCoffre(1, 6), TI_CLE, 6));

            if (scene->getCoffre(1, 7)) ouvrePorte(29, 58, 0);
            if (scene->getCoffre(1, 8)) ouvrePorte(58, 21, 1);
            if (scene->getCoffre(1, 9)) ouvrePorte(58, 51, 1);

            if (scene->getCoffre(1, 10)) ouvrePorte(9, 58, 2);
            if (scene->getCoffre(1, 11)) ouvrePorte(18, 66, 3);

            addEnnemi(new Ennemi001(29*16+8,5*16+6));
            addEnnemi(new Ennemi001(49*16+8,5*16+6));
            addEnnemi(new Ennemi001(39*16+8,18*16+6));
            addEnnemi(new Ennemi001(39*16+8,41*16+6));
            addEnnemi(new Ennemi001(110*16+8,22*16+6));
            addEnnemi(new Ennemi001(130*16+8,22*16+6));
            addEnnemi(new Ennemi001(110*16+8,37*16+6));
            addEnnemi(new Ennemi001(130*16+8,37*16+6));
            addEnnemi(new Ennemi001(89*16+8,52*16+6));
            addEnnemi(new Ennemi001(149*16+8,52*16+6));
            addEnnemi(new Ennemi001(119*16+8,52*16+6));

            addEnnemi(new Ennemi004(5*16,66*16));
            addEnnemi(new Ennemi004(40*16,50*16));
            addEnnemi(new Ennemi004(5*16,48*16));
            addEnnemi(new Ennemi004(72*16,49*16));
            addEnnemi(new Ennemi004(72*16,55*16));
            addEnnemi(new Ennemi004(73*16,69*16));

            addEnnemi(new Ennemi018(27*16,40*16+2));
            addEnnemi(new Ennemi018(32*16,49*16+2));
            addEnnemi(new Ennemi018(52*16,40*16+2));

            addObject(new PiegePics(108*16, 49*16, S));
            addObject(new PiegePics(111*16, 52*16, S));
            addObject(new PiegePics(114*16, 55*16, S));
            addObject(new PiegePics(125*16, 49*16, S));
            addObject(new PiegePics(128*16, 52*16, S));
            addObject(new PiegePics(131*16, 55*16, S));

            addObject(new Jarre(23*16, 21*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(23*16, 22*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(23*16, 23*16, 1, TI_PETIT_COEUR, map));

            addObject(new Jarre(39*16, 24*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(40*16, 24*16, 1, TI_PETIT_COEUR, map));

            addObject(new Jarre(112*16, 2*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(127*16, 2*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(112*16, 12*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(127*16, 12*16, 1, TI_PETIT_COEUR, map));
            break;
        case 13 :
            if (!inventory->hasCristal(1)) {
                addEnnemi(new Ennemi024(69*16, 63*16, true));
            }
            addObject(new Coffre(69 * 16 + 8, 82 * 16, 0, scene->getCoffre(2, 0), TI_CARTE_DONJON));
            addObject(new Coffre(129 * 16 + 8, 82 * 16, 0, scene->getCoffre(2, 1), TI_BOUSSOLE));
            addObject(new Coffre(69 * 16 + 8, 18 * 16, 0, scene->getCoffre(2, 2), TI_CLE_BOSS));
            if (scene->getCoffre(2, 2) == 2) ouvrePorte(69, 73, 0);

            addObject(new Coffre(63 * 16, 79 * 16, 1, inventory->hasObject(GRAPPIN), TI_GRAPPIN));

            addObject(new Coffre(9 * 16 + 8, 22 * 16, 0, scene->getCoffre(2, 4), TI_CLE, 4));
            addObject(new Coffre(9 * 16 + 8, 82 * 16, 0, scene->getCoffre(2, 5), TI_CLE, 5));
            addObject(new Coffre(69 * 16 + 8, 52 * 16, 0, scene->getCoffre(2, 6), TI_CLE, 6));
            addObject(new Coffre(103 * 16, 50 * 16, 0, scene->getCoffre(2, 7), TI_CLE, 7));
            addObject(new Coffre(129 * 16 + 8, 22 * 16, 0, scene->getCoffre(2, 8), TI_CLE, 8));

            if (scene->getCoffre(2, 9)) ouvrePorte(29, 73, 0);
            if (scene->getCoffre(2, 10)) ouvrePorte(38, 21, 1);
            if (scene->getCoffre(2, 11)) ouvrePorte(49, 73, 0);
            if (scene->getCoffre(2, 12)) ouvrePorte(58, 81, 1);
            if (scene->getCoffre(2, 13)) ouvrePorte(89, 43, 0);

            addEnnemi(new Ennemi009(109*16+8,82*16-8));
            addEnnemi(new Ennemi009(109*16+8,35*16-8));
            addEnnemi(new Ennemi009(29*16+8,35*16-8));
            addEnnemi(new Ennemi009(29*16+8,52*16-8));
            addEnnemi(new Ennemi009(49*16+8,52*16-8));
            addEnnemi(new Ennemi009(89*16+8,52*16-8));

            addEnnemi(new Ennemi022(89*16+8,82*16-7));
            addEnnemi(new Ennemi022(104*16,65*16-7));
            addEnnemi(new Ennemi022(115*16,68*16-7));
            addEnnemi(new Ennemi022(49*16+8,22*16-7));
            addEnnemi(new Ennemi022(89*16+8,25*16-7));
            addEnnemi(new Ennemi022(54*16+8,32*16-7));
            addEnnemi(new Ennemi022(84*16+8,32*16-7));
            addEnnemi(new Ennemi022(25*16,65*16-7));
            addEnnemi(new Ennemi022(34*16,69*16-7));

            addEnnemi(new Ennemi023(114*16+3,52*16-1));
            addEnnemi(new Ennemi023(109*16+3,22*16-1));
            addEnnemi(new Ennemi023(29*16+3,22*16-1));

            addObject(new PiegePics(72*16, 22*16, S));
            addObject(new PiegePics(70*16, 26*16, S));
            addObject(new PiegePics(68*16, 30*16, S));
            addObject(new PiegePics(66*16, 34*16, S));

            addObject(new Sphere(109*16+8, 97*16));
            addObject(new Sphere(109*16+8, 7*16));
            addObject(new Sphere(29*16+8, 7*16));
            addObject(new Sphere(26*16, 77*16));
            addObject(new Sphere(28*16, 82*16));
            addObject(new Sphere(46*16, 82*16));

            addObject(new Jarre(77*16, 87*16, 1, TI_FLECHE, map));
            addObject(new Jarre(82*16, 85*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(83*16, 85*16, 1, TI_BOMBE, map));
            addObject(new Jarre(104*16, 87*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(115*16, 87*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(109*16, 67*16, 1, TI_FLECHE, map));
            addObject(new Jarre(110*16, 67*16, 1, TI_BOMBE, map));
            addObject(new Jarre(117*16, 47*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(117*16, 57*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(104*16, 40*16, 1, TI_FLECHE, map));
            addObject(new Jarre(115*16, 40*16, 1, TI_FLECHE, map));
            addObject(new Jarre(104*16, 17*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(115*16, 17*16, 1, TI_BOMBE, map));
            addObject(new Jarre(84*16, 72*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(95*16, 72*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(24*16, 42*16, 1, TI_FLECHE, map));
            addObject(new Jarre(35*16, 42*16, 1, TI_FLECHE, map));
            addObject(new Jarre(24*16, 17*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(35*16, 17*16, 1, TI_BOMBE, map));
            addObject(new Jarre(29*16, 96*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(30*16, 96*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(29*16, 97*16, 1, TI_FLECHE, map));
            addObject(new Jarre(30*16, 97*16, 1, TI_FLECHE, map));
            addObject(new Jarre(29*16, 98*16, 1, TI_BOMBE, map));
            addObject(new Jarre(30*16, 98*16, 1, TI_BOMBE, map));
            break;
        case 14 :
            if (!inventory->hasCristal(2)) {
                addEnnemi(new Ennemi028(69*16, 49*16-6));
            }
            addObject(new Coffre(69 * 16 + 8, 67 * 16, 0, scene->getCoffre(3, 0), TI_CARTE_DONJON));
            addObject(new Coffre(29 * 16 + 8, 37 * 16, 0, scene->getCoffre(3, 1), TI_BOUSSOLE));
            addObject(new Coffre(149 * 16 + 8, 7 * 16, 0, scene->getCoffre(3, 2), TI_CLE_BOSS));
            if (scene->getCoffre(3, 2) == 2) ouvrePorte(69, 58, 0);

            addObject(new Coffre(49 * 16, 21 * 16 + 8, 1, inventory->hasObject(LANTERNE), TI_LANTERNE));

            addObject(new Coffre(29 * 16 + 8, 52 * 16, 0, scene->getCoffre(3, 4), TI_CLE, 4));
            addObject(new Coffre(89 * 16 + 8, 22 * 16, 0, scene->getCoffre(3, 5), TI_CLE, 5));
            addObject(new Coffre(129 * 16 + 8, 7 * 16, 0, scene->getCoffre(3, 6), TI_CLE, 6));
            addObject(new Coffre(149 * 16 + 8, 22 * 16, 0, scene->getCoffre(3, 7), TI_CLE, 7));
            addObject(new Coffre(169 * 16 + 8, 37 * 16, 0, scene->getCoffre(3, 8), TI_CLE, 8));

            if (scene->getCoffre(3, 9)) ouvrePorte(9, 28, 0);
            if (scene->getCoffre(3, 10)) ouvrePorte(18, 66, 1);
            if (scene->getCoffre(3, 11)) ouvrePorte(49, 13, 0);
            if (scene->getCoffre(3, 12)) ouvrePorte(78, 6, 1);
            if (scene->getCoffre(3, 13)) ouvrePorte(109, 43, 0);

            if (scene->getCoffre(3, 14)) {
                ouvrePorte(29, 43, 0);
                map->setSol(27*16, 41*16, 1415);
                map->setSol(32*16, 41*16, 1415);
            }
            if (scene->getCoffre(3, 15)) {
                ouvrePorte(49, 28, 0);
                map->setSol(47*16, 26*16, 1415);
                map->setSol(52*16, 26*16, 1415);
            }
            if (scene->getCoffre(3, 16)) {
                ouvrePorte(109, 58, 0);
                map->setSol(107*16, 63*16, 1415);
                map->setSol(112*16, 63*16, 1415);
            }
            if (scene->getCoffre(3, 17)) {
                ouvrePorte(149, 13, 0);
                map->setSol(143*16, 26*16, 1415);
                map->setSol(147*16, 18*16, 1415);
                map->setSol(152*16, 18*16, 1415);
                map->setSol(156*16, 26*16, 1415);
            }

            if (scene->getCoffre(3, 18)) ouvrePorte(138, 25, 3);
            if (scene->getCoffre(3, 19)) ouvrePorte(158, 25, 3);


            addEnnemi(new Ennemi025(49*16-6+8,52*16-14));
            addEnnemi(new Ennemi025(69*16-6+8,37*16-14));
            addEnnemi(new Ennemi025(169*16-6+8,7*16-14));
            addEnnemi(new Ennemi025(129*16-6+8,22*16-14));
            addEnnemi(new Ennemi025(169*16-6+8,22*16-14));
            addEnnemi(new Ennemi025(109*16-6+8,52*16-14));

            addEnnemi(new Ennemi026(29*16+8,63*16));
            addEnnemi(new Ennemi026(39*16+8,63*16));
            addEnnemi(new Ennemi026(29*16+8,71*16));
            addEnnemi(new Ennemi026(39*16+8,71*16));
            addEnnemi(new Ennemi026(7*16,38*16));
            addEnnemi(new Ennemi026(10*16,44*16));
            addEnnemi(new Ennemi026(7*16,51*16));
            addEnnemi(new Ennemi026(5*16,22*16));
            addEnnemi(new Ennemi026(19*16+8,18*16));
            addEnnemi(new Ennemi026(34*16,22*16));
            addEnnemi(new Ennemi026(36*16,11*16));
            addEnnemi(new Ennemi026(44*16,11*16));

            addEnnemi(new Ennemi027(89*16+8,37*16-1));
            addEnnemi(new Ennemi027(89*16+8,52*16-1));
            addEnnemi(new Ennemi027(69*16+8,7*16-1));
            addEnnemi(new Ennemi027(69*16+8,22*16-1));
            addEnnemi(new Ennemi027(109*16+8,37*16-1));
            addEnnemi(new Ennemi027(129*16+8,37*16-1));
            addEnnemi(new Ennemi027(189*16+8,37*16-1));
            addEnnemi(new Ennemi027(189*16+8,52*16-1));

            addObject(new Jarre(4*16, 62*16, 1, TI_FLECHE, map));
            addObject(new Jarre(15*16, 62*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(4*16, 72*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(15*16, 72*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(44*16, 17*16, 1, TI_MAGIE_PEU, map));
            addObject(new Jarre(55*16, 17*16, 1, TI_MAGIE_PEU, map));
            addObject(new Jarre(84*16, 2*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(95*16, 2*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(84*16, 12*16, 1, TI_MAGIE_PEU, map));
            addObject(new Jarre(95*16, 12*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(84*16, 62*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(95*16, 62*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(84*16, 72*16, 1, TI_FLECHE, map));
            addObject(new Jarre(95*16, 72*16, 1, TI_BOMBE, map));
            addObject(new Jarre(144*16, 32*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(155*16, 32*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(144*16, 42*16, 1, TI_MAGIE_PEU, map));
            addObject(new Jarre(155*16, 42*16, 1, TI_MAGIE_PEU, map));
            break;
        case 15 :
            if (!inventory->hasCristal(3)) {
                addEnnemi(new Ennemi031(49*16, 32*16));
            }
            addObject(new Coffre(9 * 16 + 8, 67 * 16, 0, scene->getCoffre(4, 0), TI_CARTE_DONJON));
            addObject(new Coffre(89 * 16 + 8, 67 * 16, 0, scene->getCoffre(4, 1), TI_BOUSSOLE));
            addObject(new Coffre(69 * 16 + 8, 37 * 16, 0, scene->getCoffre(4, 2), TI_CLE_BOSS));
            if (scene->getCoffre(4, 2) == 2) ouvrePorte(49, 43, 0);

            addObject(new Coffre(9 * 16, 35 * 16 + 8, 1, inventory->hasObject(PALMES), TI_PALMES));

            addObject(new Coffre(9 * 16 + 8, 52 * 16, 0, scene->getCoffre(4, 4), TI_CLE, 4));
            addObject(new Coffre(109 * 16 + 8, 7 * 16, 0, scene->getCoffre(4, 5), TI_CLE, 5));
            addObject(new Coffre(109 * 16 + 8, 37 * 16, 0, scene->getCoffre(4, 6), TI_CLE, 6));

            if (scene->getCoffre(4, 7)) ouvrePorte(58, 51, 1);
            if (scene->getCoffre(4, 8)) ouvrePorte(129, 13, 0);
            if (scene->getCoffre(4, 9)) ouvrePorte(149, 28, 0);

            addEnnemi(new Ennemi021(85*16, 21*16+1));
            addEnnemi(new Ennemi021(94*16, 21*16+1));
            addEnnemi(new Ennemi021(85*16, 32*16+1));
            addEnnemi(new Ennemi021(94*16, 32*16+1));
            addEnnemi(new Ennemi021(30*16, 19*16+1));
            addEnnemi(new Ennemi021(40*16, 25*16+1));
            addEnnemi(new Ennemi021(50*16, 19*16+1));
            addEnnemi(new Ennemi021(60*16, 25*16+1));
            addEnnemi(new Ennemi021(70*16, 19*16+1));

            addEnnemi(new Ennemi029(40*16, 10*16-10));
            addEnnemi(new Ennemi029(50*16, 4*16-10));
            addEnnemi(new Ennemi029(60*16, 10*16-10));
            addEnnemi(new Ennemi029(89*16+8, 7*16-10));
            addEnnemi(new Ennemi029(29*16+8, 67*16-10));
            addEnnemi(new Ennemi029(69*16+8, 67*16-10));
            addEnnemi(new Ennemi029(149*16+8, 22*16-10));
            addEnnemi(new Ennemi029(129*16+8, 7*16-10));

            addEnnemi(new Ennemi030(89*16+8, 52*16-8));
            addEnnemi(new Ennemi030(9*16+8, 7*16-8));
            addEnnemi(new Ennemi030(9*16+8, 22*16-8));
            addEnnemi(new Ennemi030(29*16+8, 52*16-8));
            addEnnemi(new Ennemi030(127*16+8, 39*16-8));
            addEnnemi(new Ennemi030(129*16+8, 37*16-8));
            addEnnemi(new Ennemi030(131*16+8, 35*16-8));
            addEnnemi(new Ennemi030(149*16+8, 7*16-8));

            addObject(new Caisse(82*16, 4*16, 3));
            addObject(new Caisse(82*16, 5*16, 3));
            addObject(new Caisse(82*16, 9*16, 3));
            addObject(new Caisse(82*16, 10*16, 3));
            addObject(new Caisse(83*16, 5*16, 3));
            addObject(new Caisse(83*16, 6*16, 3));
            addObject(new Caisse(83*16, 7*16, 3));
            addObject(new Caisse(83*16, 8*16, 3));
            addObject(new Caisse(83*16, 9*16, 3));

            addObject(new PiegePics(35*16, 2*16, S));
            addObject(new PiegePics(45*16, 2*16, S));
            addObject(new PiegePics(55*16, 2*16, S));
            addObject(new PiegePics(65*16, 2*16, S));

            addObject(new Jarre(24*16, 2*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(75*16, 2*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(24*16, 12*16, 1, TI_MAGIE_PEU, map));
            addObject(new Jarre(75*16, 12*16, 1, TI_MAGIE_PEU, map));
            addObject(new Jarre(24*16, 62*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(35*16, 62*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(24*16, 72*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(35*16, 72*16, 1, TI_MAGIE_PEU, map));
            addObject(new Jarre(64*16, 62*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(75*16, 62*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(64*16, 72*16, 1, TI_MAGIE_PEU, map));
            addObject(new Jarre(75*16, 72*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(124*16, 2*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(135*16, 2*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(124*16, 12*16, 1, TI_MAGIE_PEU, map));
            addObject(new Jarre(135*16, 12*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(124*16, 32*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(135*16, 32*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(124*16, 42*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(135*16, 42*16, 1, TI_MAGIE_PEU, map));
            break;
        case 16 :
            if (!inventory->hasCristal(4)) {
                addEnnemi(new Ennemi035(169*16, 48*16));
            }
            addObject(new Coffre(149 * 16 + 8, 67 * 16, 0, scene->getCoffre(5, 0), TI_CARTE_DONJON));
            addObject(new Coffre(129 * 16 + 8, 52 * 16, 0, scene->getCoffre(5, 1), TI_BOUSSOLE));
            addObject(new Coffre(169 * 16 + 8, 7 * 16, 0, scene->getCoffre(5, 2), TI_CLE_BOSS));
            if (scene->getCoffre(5, 2) == 2) ouvrePorte(169, 58, 0);

            addObject(new Coffre(89 * 16, 21 * 16 + 8, 1, inventory->hasObject(MARTEAU), TI_MARTEAU));

            addObject(new Coffre(109 * 16 + 8, 7 * 16, 0, scene->getCoffre(5, 4), TI_CLE, 4));

            if (scene->getCoffre(5, 5)) ouvrePorte(158, 6, 1);
            if (scene->getCoffre(5, 6)) ouvrePorte(129, 13, 0);

            addObject(new Interrupteur(129*16, 22*16, 0, scene->getCoffre(5, 6), map));

            addObject(new Sphere(75*16, 27*16));
            addObject(new Sphere(109*16+8, 37*16));
            addObject(new Sphere(169*16+8, 82*16));

            addObject(new PiegeMain(140*16, 7*16));
            addObject(new PiegeMain(170*16, 22*16));
            addObject(new PiegeMain(170*16, 67*16));
            addObject(new PiegeMain(110*16, 67*16));
            addObject(new PiegeMain(140*16, 30*16));

            addEnnemi(new Ennemi012(78*16,80*16));
            addEnnemi(new Ennemi012(70*16,63*16));
            addEnnemi(new Ennemi012(84*16,56*16));
            addEnnemi(new Ennemi012(70*16,35*16));
            addEnnemi(new Ennemi012(78*16,19*16));
            addEnnemi(new Ennemi012(83*16,13*16));

            addEnnemi(new Ennemi032(26*16,63*16-7));
            addEnnemi(new Ennemi032(33*16,63*16-7));
            addEnnemi(new Ennemi032(46*16,3*16-7));
            addEnnemi(new Ennemi032(53*16,3*16-7));
            addEnnemi(new Ennemi032(174*16,34*16-7));
            addEnnemi(new Ennemi032(174*16,40*16-7));
            addEnnemi(new Ennemi032(109*16+8,52*16-7));
            addEnnemi(new Ennemi032(149*16+8,52*16-7));
            addEnnemi(new Ennemi032(149*16+8,82*16-7));
            addEnnemi(new Ennemi032(129*16+8,67*16-7));

            addEnnemi(new Ennemi033(49*16-3+8,67*16-9));
            addEnnemi(new Ennemi033(49*16-3+8,7*16-9));
            addEnnemi(new Ennemi033(149*16-3+8,37*16-9));
            addEnnemi(new Ennemi033(92*16-3,37*16-9));
            addEnnemi(new Ennemi033(109*16-3+8,67*16-9));
            addEnnemi(new Ennemi033(109*16-3+8,82*16-9));

            addEnnemi(new Ennemi034(169*16-4+8,37*16-9));
            addEnnemi(new Ennemi034(49*16-4+8,22*16-9));
            addEnnemi(new Ennemi034(149*16-4+8,7*16-9));

            addObject(new Jarre(24*16, 62*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(35*16, 62*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(44*16, 2*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(55*16, 2*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(104*16, 62*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(115*16, 62*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(104*16, 72*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(115*16, 72*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(122*16, 41*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(123*16, 41*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(122*16, 42*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(123*16, 42*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(164*16, 17*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(175*16, 17*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(164*16, 62*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(175*16, 62*16, 1, TI_PETIT_COEUR, map));
            addObject(new Jarre(164*16, 72*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(175*16, 72*16, 1, TI_NO_ITEM, map));
            break;
        case 17 :
            if (!inventory->hasCristal(5)) {
                addEnnemi(new Ennemi040(149*16-8-3, 94*16-10));
            }
            addObject(new Coffre(29 * 16 + 8, 142 * 16, 0, scene->getCoffre(6, 0), TI_CARTE_DONJON));
            addObject(new Coffre(109 * 16 + 8, 142 * 16, 0, scene->getCoffre(6, 1), TI_BOUSSOLE));
            addObject(new Coffre(89 * 16 + 8, 112 * 16, 0, scene->getCoffre(6, 2), TI_CLE_BOSS));
            if (scene->getCoffre(6, 2) == 2) ouvrePorte(149, 103, 0);

            addObject(new Coffre(69 * 16, 6 * 16 + 8, 1, inventory->hasObject(BAGUETTE_FEU), TI_BAGUETTE_FEU));

            addObject(new Coffre(9 * 16 + 8, 37 * 16, 0, scene->getCoffre(6, 4), TI_CLE, 4));
            addObject(new Coffre(49 * 16 + 8, 112 * 16, 0, scene->getCoffre(6, 5), TI_CLE, 5));
            addObject(new Coffre(129 * 16 + 8, 37 * 16, 0, scene->getCoffre(6, 6), TI_CLE, 6));

            if (scene->getCoffre(6, 7)) ouvrePorte(78, 111, 1);
            if (scene->getCoffre(6, 8)) ouvrePorte(98, 96, 1);
            if (scene->getCoffre(6, 9)) ouvrePorte(118, 96, 1);

            if (scene->getCoffre(6, 10)) {
                ouvrePorte(38, 126, 1);
                map->setSol(19*16, 119*16, 1415);
            }
            if (scene->getCoffre(6, 11)) {
                ouvrePorte(69, 13, 0);
                map->setSol(77*16, 17*16, 1415);
                map->setSol(62*16, 27*16, 1415);
                map->setSol(77*16, 27*16, 1415);
            }
            if (scene->getCoffre(6, 12)) {
                ouvrePorte(69, 28, 0);
                map->setSol(62*16, 32*16, 1415);
                map->setSol(77*16, 32*16, 1415);
                map->setSol(62*16, 42*16, 1415);
                map->setSol(77*16, 42*16, 1415);
            }
            if (scene->getCoffre(6, 13)) {
                ouvrePorte(69, 43, 0);
                map->setSol(63*16, 52*16, 1415);
                map->setSol(76*16, 52*16, 1415);
            }
            if (scene->getCoffre(6, 14)) {
                ouvrePorte(69, 58, 0);
                map->setSol(68*16, 62*16, 1415);
                map->setSol(71*16, 62*16, 1415);
            }
            if (scene->getCoffre(6, 15)) {
                ouvrePorte(58, 96, 1);
                ouvrePorte(78, 96, 1);
                map->setSol(69*16, 97*16, 1415);
                map->setSol(70*16, 97*16, 1415);
            }
            if (scene->getCoffre(6, 16)) {
                ouvrePorte(58, 126, 1);
                map->setSol(62*16, 125*16, 1415);
                map->setSol(62*16, 129*16, 1415);
            }
            if (scene->getCoffre(6, 17)) {
                ouvrePorte(78, 126, 1);
                map->setSol(77*16, 125*16, 1415);
                map->setSol(77*16, 129*16, 1415);
            }
            if (scene->getCoffre(6, 18)) {
                ouvrePorte(69, 133, 0);
                map->setSol(68*16, 137*16, 1415);
                map->setSol(71*16, 137*16, 1415);
            }
            if (scene->getCoffre(6, 19)) {
                ouvrePorte(98, 126, 1);
                map->setSol(102*16, 107*16, 1415);
                map->setSol(137*16, 107*16, 1415);
                map->setSol(102*16, 132*16, 1415);
                map->setSol(137*16, 132*16, 1415);
            }

            addObject(new PiegePics(16*16, 117*16, S));

            addObject(new PiegeFeu(62*16, 17*16));
            addObject(new PiegeFeu(69*16+8, 37*16));
            addObject(new PiegeFeu(64*16, 72*16));
            addObject(new PiegeFeu(75*16, 72*16));
            addObject(new PiegeFeu(57*16, 122*16));
            addObject(new PiegeFeu(57*16, 132*16));
            addObject(new PiegeFeu(82*16, 122*16));
            addObject(new PiegeFeu(82*16, 132*16));
            addObject(new PiegeFeu(42*16, 137*16));
            addObject(new PiegeFeu(97*16, 137*16));
            addObject(new PiegeFeu(117*16, 116*16));
            addObject(new PiegeFeu(123*16, 116*16));
            addObject(new PiegeFeu(117*16, 122*16));
            addObject(new PiegeFeu(123*16, 122*16));

            addEnnemi(new Ennemi037(29*16+8, 120*16-10));
            addEnnemi(new Ennemi037(109*16+8, 120*16-10));
            addEnnemi(new Ennemi037(69*16+8, 127*16-10));
            addEnnemi(new Ennemi037(49*16+8, 75*16-10));
            addEnnemi(new Ennemi037(89*16+8, 75*16-10));
            addEnnemi(new Ennemi037(49*16+8, 97*16-10));
            addEnnemi(new Ennemi037(29*16+8, 97*16-10));
            addEnnemi(new Ennemi037(9*16+8, 97*16-10));
            addEnnemi(new Ennemi037(89*16+8, 97*16-10));
            addEnnemi(new Ennemi037(109*16+8, 97*16-10));
            addEnnemi(new Ennemi037(129*16+8, 97*16-10));
            addEnnemi(new Ennemi037(9*16+8, 60*16-10));
            addEnnemi(new Ennemi037(129*16+8, 60*16-10));

            addEnnemi(new Ennemi038(49*16-3+8,142*16-9));
            addEnnemi(new Ennemi038(89*16-3+8,142*16-9));
            addEnnemi(new Ennemi038(49*16-3+8,52*16-9));
            addEnnemi(new Ennemi038(89*16-3+8,52*16-9));
            addEnnemi(new Ennemi038(9*16-3+8,82*16-9));
            addEnnemi(new Ennemi038(29*16-3+8,82*16-9));
            addEnnemi(new Ennemi038(109*16-3+8,82*16-9));
            addEnnemi(new Ennemi038(129*16-3+8,82*16-9));

            addEnnemi(new Ennemi039(49*16-4+8,127*16-9));
            addEnnemi(new Ennemi039(89*16-4+8,127*16-9));
            addEnnemi(new Ennemi039(69*16-4+8,82*16-9));

            addObject(new Jarre(27*16, 123*16, 1, TI_MAGIE_PEU, map));
            addObject(new Jarre(28*16, 123*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(29*16, 123*16, 1, TI_MAGIE_PEU, map));
            addObject(new Jarre(30*16, 123*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(31*16, 123*16, 1, TI_MAGIE_PEU, map));
            addObject(new Jarre(32*16, 123*16, 1, TI_NO_ITEM, map));

            addObject(new Jarre(64*16, 77*16, 1, TI_MAGIE_PEU, map));
            addObject(new Jarre(75*16, 77*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(64*16, 87*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(75*16, 87*16, 1, TI_MAGIE_PEU, map));

            addObject(new Jarre(64*16, 137*16, 1, TI_MAGIE_PEU, map));
            addObject(new Jarre(75*16, 137*16, 1, TI_MAGIE_PEU, map));

            addObject(new Jarre(107*16, 123*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(108*16, 123*16, 1, TI_MAGIE_PEU, map));
            addObject(new Jarre(109*16, 123*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(110*16, 123*16, 1, TI_MAGIE_PEU, map));
            addObject(new Jarre(111*16, 123*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(112*16, 123*16, 1, TI_MAGIE_PEU, map));

            addObject(new Jarre(144*16, 107*16, 1, TI_MAGIE_PEU, map));
            addObject(new Jarre(155*16, 107*16, 1, TI_MAGIE_PEU, map));
            break;
        case 18 :
            if (!inventory->hasCristal(6)) {
                addEnnemi(new Ennemi043(149*16, 19*16));
            }
            addObject(new Coffre(149 * 16 + 8, 52 * 16, 0, scene->getCoffre(7, 0), TI_CARTE_DONJON));
            addObject(new Coffre(169 * 16 + 8, 49 * 16, 0, scene->getCoffre(7, 1), TI_BOUSSOLE));
            addObject(new Coffre(109 * 16 + 8, 67 * 16, 0, scene->getCoffre(7, 2), TI_CLE_BOSS));
            if (scene->getCoffre(7, 2) == 2) ouvrePorte(149, 28, 0);

            addObject(new Coffre(9 * 16, 66 * 16 + 8, 1, inventory->hasObject(BAGUETTE_GLACE), TI_BAGUETTE_GLACE));

            addObject(new Coffre(69 * 16 + 8, 36 * 16, 0, scene->getCoffre(7, 4), TI_CLE, 4));
            addObject(new Coffre(129 * 16 + 8, 67 * 16, 0, scene->getCoffre(7, 5), TI_CLE, 5));

            if (scene->getCoffre(7, 6)) ouvrePorte(89, 58, 0);
            if (scene->getCoffre(7, 7)) ouvrePorte(109, 58, 0);

            if (scene->getCoffre(7, 8)) {
                ouvrePorte(18, 66, 1);
                map->setSol(17*16, 65*16, 1414);
                map->setSol(17*16, 69*16, 1414);
            }
            if (scene->getCoffre(7, 9)) {
                ouvrePorte(178, 66, 1);
                map->setSol(182*16, 65*16, 1414);
                map->setSol(182*16, 69*16, 1414);
            }
            if (scene->getCoffre(7, 10)) {
                ouvrePorte(189, 58, 0);
                map->setSol(188*16, 62*16, 1414);
                map->setSol(191*16, 62*16, 1414);
            }

            if (scene->getCoffre(7, 11)) ouvrePorte(169, 37, 2);

            addObject(new Caisse(182*16, 5*16, 2));
            addObject(new Caisse(182*16, 9*16, 2));
            addObject(new Caisse(183*16, 5*16, 2));
            addObject(new Caisse(183*16, 6*16, 2));
            addObject(new Caisse(183*16, 7*16, 2));
            addObject(new Caisse(183*16, 8*16, 2));
            addObject(new Caisse(183*16, 9*16, 2));

            addObject(new PiegePics(127*16, 3*16, S));
            addObject(new PiegePics(132*16, 3*16, S));
            addObject(new PiegePics(137*16, 3*16, S));
            addObject(new PiegePics(142*16, 3*16, S));
            addObject(new PiegePics(147*16, 3*16, S));
            addObject(new PiegePics(152*16, 3*16, S));
            addObject(new PiegePics(157*16, 3*16, S));
            addObject(new PiegePics(162*16, 3*16, S));
            addObject(new PiegePics(167*16, 3*16, S));
            addObject(new PiegePics(172*16, 3*16, S));

            addEnnemi(new Ennemi002(29*16-3+8,45*16-10));
            addEnnemi(new Ennemi002(85*16-3+8,45*16-10));
            addEnnemi(new Ennemi002(93*16-3+8,45*16-10));
            addEnnemi(new Ennemi002(85*16-3+8,30*16-10));
            addEnnemi(new Ennemi002(93*16-3+8,30*16-10));
            addEnnemi(new Ennemi002(5*16-3+8,45*16-10));
            addEnnemi(new Ennemi002(13*16-3+8,45*16-10));
            addEnnemi(new Ennemi002(5*16-3+8,30*16-10));
            addEnnemi(new Ennemi002(13*16-3+8,30*16-10));
            addEnnemi(new Ennemi002(159*16-3+8,67*16-10));

            addEnnemi(new Ennemi041(29*16+8,67*16-8));
            addEnnemi(new Ennemi041(69*16+8,67*16-8));
            addEnnemi(new Ennemi041(29*16+8,7*16-8));
            addEnnemi(new Ennemi041(69*16+8,7*16-8));
            addEnnemi(new Ennemi041(129*16+8,44*16-8));
            addEnnemi(new Ennemi041(109*16+8,29*16-8));
            addEnnemi(new Ennemi041(109*16+8,35*16-8));
            addEnnemi(new Ennemi041(114*16+8,45*16-8));
            addEnnemi(new Ennemi041(109*16+8,53*16-8));

            addEnnemi(new Ennemi042(89*16+8-5,7*16-3));
            addEnnemi(new Ennemi042(9*16+8-5,7*16-3));
            addEnnemi(new Ennemi042(189*16+8-5,7*16-3));
            addEnnemi(new Ennemi042(109*16+8-5,7*16-3));
            addEnnemi(new Ennemi042(169*16+8-5,36*16-3));
            break;
        case 19 :
            if (link->getEpee() < 5) {
                addEnnemi(new Ennemi045(28*16-1, 47*16));
            }
            addObject(new Coffre(49 * 16 + 8, 142 * 16, 0, scene->getCoffre(8, 0), TI_CARTE_DONJON));
            addObject(new Coffre(29 * 16 + 8, 97 * 16, 0, scene->getCoffre(8, 1), TI_BOUSSOLE));
            addObject(new Coffre(49 * 16 + 8, 7 * 16, 0, scene->getCoffre(8, 2), TI_CLE_BOSS));
            if (scene->getCoffre(8, 2) == 2) ouvrePorte(29, 58, 0);

            if (link->getEpee() < 5) {
                addItem(ItemHelper::getInstance()->createItem(TI_EPEE_5, 30*16, 5*16-2));
            }

            addObject(new Coffre(9 * 16 + 8, 112 * 16, 0, scene->getCoffre(8, 4), TI_CLE, 4));
            addObject(new Coffre(69 * 16 + 8, 97 * 16, 0, scene->getCoffre(8, 5), TI_CLE, 5));

            if (scene->getCoffre(8, 6)) ouvrePorte(29, 133, 0);
            if (scene->getCoffre(8, 7)) ouvrePorte(38, 96, 1);

            addEnnemi(new Ennemi044(51*16-3,144*16-10));
            addEnnemi(new Ennemi044(25*16-3,70*16-10));
            addEnnemi(new Ennemi044(34*16-3,70*16-10));
            addEnnemi(new Ennemi044(45*16-3,70*16-10));
            addEnnemi(new Ennemi044(54*16-3,70*16-10));
            addEnnemi(new Ennemi044(49*16+8-3,112*16-10));
            addEnnemi(new Ennemi044(69*16+8-3,112*16-10));
            addEnnemi(new Ennemi044(29*16+8-3,112*16-10));
            addEnnemi(new Ennemi044(9*16+8-3,97*16-10));
            addEnnemi(new Ennemi044(49*16+8-3,97*16-10));
            addEnnemi(new Ennemi044(44*16-3,37*16-10));
            addEnnemi(new Ennemi044(46*16-3,39*16-10));
            addEnnemi(new Ennemi044(49*16+8-3,41*16-10));
            addEnnemi(new Ennemi044(53*16-3,39*16-10));
            addEnnemi(new Ennemi044(55*16-3,37*16-10));
            break;
        case 20 :
            addEnnemi(new Ennemi050(9*16-10, 2*16-4));

            addObject(new Coffre(49 * 16 + 8, 37 * 16, 0, scene->getCoffre(9, 0), TI_CARTE_DONJON));
            addObject(new Coffre(29 * 16 + 8, 52 * 16, 0, scene->getCoffre(9, 1), TI_BOUSSOLE));
            addObject(new Coffre(229 * 16 + 8, 97 * 16, 0, scene->getCoffre(9, 2), TI_CLE_BOSS));
            if (scene->getCoffre(9, 2)) ouvrePorte(218, 96, 1);
            if (scene->getCoffre(9, 2) == 2) ouvrePorte(9, 13, 0);

            addObject(new Coffre(29 * 16 + 8, 7 * 16, 0, scene->getCoffre(9, 4), TI_CLE, 4));
            addObject(new Coffre(49 * 16 + 8, 7 * 16, 0, scene->getCoffre(9, 5), TI_CLE, 5));
            addObject(new Coffre(189 * 16 + 8, 22 * 16, 0, scene->getCoffre(9, 6), TI_CLE, 6));

            if (scene->getCoffre(9, 8)) ouvrePorte(29, 43, 0);
            if (scene->getCoffre(9, 9)) ouvrePorte(38, 36, 1);
            if (scene->getCoffre(9, 10)) ouvrePorte(198, 36, 1);
            if (scene->getCoffre(9, 11)) ouvrePorte(38, 51, 1);
            if (scene->getCoffre(9, 12)) ouvrePorte(98, 51, 1);
            if (scene->getCoffre(9, 13)) ouvrePorte(218, 18, 3);
            if (scene->getCoffre(9, 14)) ouvrePorte(69, 13, 4);
            if (scene->getCoffre(9, 15)) ouvrePorte(210, 24, 5);

            addObject(new Sphere(49*16 + 8, 97*16));

            addObject(new Interrupteur(22*16, 57*16, 0, scene->getCoffre(9, 11), map, false));
            addObject(new Interrupteur(117*16, 57*16, 0, scene->getCoffre(9, 12), map, false));

            addObject(new Jarre(22*16, 47*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(37*16, 47*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(22*16, 57*16, 0, TI_INTERRUPTEUR, map));
            addObject(new Jarre(37*16, 57*16, 0, TI_NO_ITEM, map));

            addObject(new Jarre(102*16, 47*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(117*16, 47*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(102*16, 57*16, 0, TI_NO_ITEM, map));
            addObject(new Jarre(117*16, 57*16, 0, TI_INTERRUPTEUR, map));

            if (scene->getAvancement() < AV_ZELDA_ARRIVEE) {
                addObject(new Pnj(16*209+8, 16*18+9, 15, 224));
            } else if (scene->getAvancement() == AV_ZELDA_ARRIVEE) {
                addObject(new Pnj(16*9+8, 16*20+9, 15, 227));
            }

            addObject(new PiegeDemi(2*16, 2*16));
            addObject(new PiegeDemi(17*16, 2*16));
            addObject(new PiegeDemi(125*16, 77*16));
            addObject(new PiegeDemi(154*16, 77*16));
            addObject(new PiegeDemi(167*16, 100*16));
            addObject(new PiegeDemi(214*16, 40*16));
            addObject(new PiegeDemi(224*16, 40*16));
            addObject(new PiegeDemi(235*16, 17*16));
            addObject(new PiegeDemi(244*16, 55*16));
            addObject(new PiegeDemi(255*16, 34*16));

            addEnnemi(new Ennemi046(49*16+8-3,52*16-11));
            addEnnemi(new Ennemi046(69*16+8-3,52*16-11));
            addEnnemi(new Ennemi046(89*16+8-3,52*16-11));
            addEnnemi(new Ennemi046(49*16+8-3,22*16-11));
            addEnnemi(new Ennemi046(27*16-3,22*16-11));
            addEnnemi(new Ennemi046(32*16-3,22*16-11));
            addEnnemi(new Ennemi046(26*16-3,78*16-11));
            addEnnemi(new Ennemi046(33*16-3,78*16-11));
            addEnnemi(new Ennemi046(89*16+8-3,22*16-11));
            addEnnemi(new Ennemi046(89*16+8-3,37*16-11));
            addEnnemi(new Ennemi046(106*16-3,78*16-11));
            addEnnemi(new Ennemi046(113*16-3,78*16-11));

            addEnnemi(new Ennemi047(69*16+8-3,30*16-11));
            addEnnemi(new Ennemi047(29*16+8-3,37*16-11));
            addEnnemi(new Ennemi047(29*16+8-3,75*16-11));
            addEnnemi(new Ennemi047(109*16+8-3,30*16-11));
            addEnnemi(new Ennemi047(109*16+8-3,75*16-11));
            addEnnemi(new Ennemi047(129*16+8-3,82*16-11));
            addEnnemi(new Ennemi047(149*16+8-3,82*16-11));
            addEnnemi(new Ennemi047(189*16+8-3,37*16-11));
            addEnnemi(new Ennemi047(165*16-3,45*16-11));
            addEnnemi(new Ennemi047(174*16-3,45*16-11));
            addEnnemi(new Ennemi047(169*16+8-3,48*16-11));
            addEnnemi(new Ennemi047(189*16+8-3,97*16-11));
            addEnnemi(new Ennemi047(29*16+8-3,97*16-11));
            addEnnemi(new Ennemi047(109*16+8-3,97*16-11));

            addEnnemi(new Ennemi048(209*16+8-3,37*16-11));
            addEnnemi(new Ennemi048(169*16+8-3,97*16-11));
            addEnnemi(new Ennemi048(169*16+8-3,75*16-11));
            addEnnemi(new Ennemi048(249*16+8-3,75*16-11));
            break;
        case 21 :
            if (!inventory->hasQuartCoeur(25)) {
                addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 30*16, 11*16, 25));
            }

            addObject(new Sphere(8*16, 39*16));

            addEnnemi(new Ennemi018(25*16,1*16+2));
            addEnnemi(new Ennemi018(34*16,1*16+2));
            addEnnemi(new Ennemi018(4*16,37*16+2));

            addEnnemi(new Ennemi023(9*16+3,10*16-1));
            addEnnemi(new Ennemi023(9*16+3,20*16-1));
            addEnnemi(new Ennemi023(29*16+3,30*16-1));
            break;
        case 22 :
            addObject(new Coffre(29 * 16, 45 * 16, 1, inventory->hasObject(LIVRE), TI_LIVRE));

            if (scene->getCoffre(0, 7)) ouvrePorte(18, 6, 1);

            addObject(new Interrupteur(22*16, 5*16, 0, scene->getCoffre(0, 7), map));

            addEnnemi(new Ennemi012(9*16,37*16));
            addEnnemi(new Ennemi012(49*16,37*16));
            addEnnemi(new Ennemi012(9*16,67*16));
            addEnnemi(new Ennemi012(49*16,67*16));
            addEnnemi(new Ennemi012(29*16+8,7*16));
            addEnnemi(new Ennemi012(49*16+8,7*16));
            addEnnemi(new Ennemi012(69*16+8,30*16));
            addEnnemi(new Ennemi012(69*16+8,45*16));
            break;
        case 23 :
        case 24 :
        case 25 :
        case 26 :
            addObject(new Pnj(16*9, 16*4 + 8, 16, 237));
            break;
        case 27 :
            addObject(new Coffre(13 * 16, 11 * 16, 0, link->getBouclier(), TI_BOUCLIER_1));
            addObject(new Jarre(4*16, 4*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(4*16, 5*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(4*16, 6*16, 0, TI_PETIT_COEUR, map));
            break;
        case 28 :
            // coeurs 26 -> 31
            addObject(new Pnj(16*9+8, 16*6, 8, 244));
            break;
        case 29 :
            addObject(new Pnj(16*19+8, 16*7, 21, 255));
            break;
        case 30 :
            // coeurs 32
            addObject(new Pnj(16*14, 16*11-13, 22, 272));
            addObject(new Coffre(6 * 16, 6 * 16 + 8, 0, true, TI_NO_ITEM));
            addObject(new Coffre(8 * 16, 6 * 16 + 8, 0, true, TI_NO_ITEM));
            addObject(new Coffre(10 * 16, 6 * 16 + 8, 0, true, TI_NO_ITEM));
            break;
        case 31 :
            addObject(new Jarre(14*16, 11*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(15*16, 11*16, 0, TI_RUBIS_BLEU, map));
            addObject(new Jarre(14*16, 12*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(15*16, 12*16, 0, TI_RUBIS_BLEU, map));
            break;
        case 32 :
            addObject(new Pnj(16*9+8-1, 16*7-7, 17, 276));
            break;
        case 33 :
            addObject(new Pnj(16*9+8, 16*3, 18, 280));
            addObject(new Pnj(16*13, 16*7-7, 19, 281));

            addObject(new TalkableArea(16*9+8, 16*6, 280));

            if (!inventory->hasQuartCoeur(33)) {
                addItem(ItemHelper::getInstance()->createItem(TI_QUART_COEUR, 5*16, 3*16, 33));
            }
            break;
        case 34 :
            map->setSol(5*16, 5*16, 2851);
            map->setSol(7*16, 5*16, 2852);
            map->setSol(9*16, 5*16, inventory->hasObject(ARC_FEE) ? 2850 : 2849);
            map->setSol(11*16, 5*16, 2848);
            map->setSol(13*16, 5*16, inventory->hasObject(ARC) ? 2847 : 2853);

            addObject(new Pnj(16*13, 16*10 + 6, 20, 296));

            addObject(new TalkableArea(16*5, 16*6, 282));
            addObject(new TalkableArea(16*7, 16*6, 284));
            addObject(new TalkableArea(16*9, 16*6, 286));
            addObject(new TalkableArea(16*11, 16*6, 288));
            addObject(new TalkableArea(16*13, 16*6, 290));
            break;
        case 35 :
            addObject(new Pnj(16*6 - 11, 16*4 + 2 - 8, 26, 300));
            break;
        case 36 :
            addObject(new Pnj(16*9 + 8, 16*4 + 11, 24, 308));
            break;
        case 37 :
            // coeurs 34
            addObject(new Pnj(16*14, 16*11-13, 22, 272));
            addObject(new Coffre(6 * 16, 6 * 16, 0, true, TI_NO_ITEM));
            addObject(new Coffre(8 * 16, 6 * 16, 0, true, TI_NO_ITEM));
            addObject(new Coffre(10 * 16, 6 * 16, 0, true, TI_NO_ITEM));
            addObject(new Coffre(6 * 16, 8 * 16, 0, true, TI_NO_ITEM));
            addObject(new Coffre(8 * 16, 8 * 16, 0, true, TI_NO_ITEM));
            addObject(new Coffre(10 * 16, 8 * 16, 0, true, TI_NO_ITEM));
            break;
        case 38 :
            addObject(new Pnj(16*9 + 8, 16*6 + 7, 25, 310));
            break;
        case 39 :
            addObject(new Pnj(16*9 + 8, 16*4 + 7, 23, 313));
            addObject(new Jarre(14*16, 12*16, 0, TI_PETIT_COEUR, map));
            addObject(new Jarre(15*16, 12*16, 0, TI_PETIT_COEUR, map));
            break;
        case 40 :
            addObject(new Pnj(16*9 + 8, 16*6 -1, 31, 314));
            break;
        case 41 :
            // coeurs 35
            addObject(new Pnj(16*14, 16*11-1, 27, 272));
            addObject(new Coffre(6 * 16, 6 * 16, 0, true, TI_NO_ITEM));
            addObject(new Coffre(8 * 16, 6 * 16, 0, true, TI_NO_ITEM));
            addObject(new Coffre(10 * 16, 6 * 16, 0, true, TI_NO_ITEM));
            addObject(new Coffre(6 * 16, 8 * 16, 0, true, TI_NO_ITEM));
            addObject(new Coffre(8 * 16, 8 * 16, 0, true, TI_NO_ITEM));
            addObject(new Coffre(10 * 16, 8 * 16, 0, true, TI_NO_ITEM));
            addObject(new Coffre(6 * 16, 10 * 16, 0, true, TI_NO_ITEM));
            addObject(new Coffre(8 * 16, 10 * 16, 0, true, TI_NO_ITEM));
            addObject(new Coffre(10 * 16, 10 * 16, 0, true, TI_NO_ITEM));
            break;
        case 42 :
            addObject(new Pnj(16*9 + 8 - 5, 16*6 + 5, 29, 315));
            break;
        case 43 :
            addObject(new Pnj(16*9, 16*6-3, 28, 323));
            map->setSol(16*9, 16*7, map->getSol(16*9, 16*7), MURRET);
            addObject(new Jarre(4*16, 12*16, 1, TI_MAGIE_PEU, map));
            addObject(new Jarre(5*16, 12*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(14*16, 12*16, 1, TI_NO_ITEM, map));
            addObject(new Jarre(15*16, 12*16, 1, TI_MAGIE_PEU, map));
            break;
        case 44 :
            addObject(new Pnj(16*9 + 8, 16*6-1, 30, 326));
            break;
    }
}
