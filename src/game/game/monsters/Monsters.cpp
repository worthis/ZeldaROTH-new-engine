#include "Monsters.h"

#include "../../MainController.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/audio/AudioManager.h"
#include "../../../engine/texts/TextManager.h"

#include "../../content/ennemis/Ennemi001.h"
#include "../../content/ennemis/Ennemi002.h"
#include "../../content/ennemis/Ennemi003.h"
#include "../../content/ennemis/Ennemi004.h"
#include "../../content/ennemis/Ennemi005.h"
#include "../../content/ennemis/Ennemi006.h"
#include "../../content/ennemis/Ennemi008.h"
#include "../../content/ennemis/Ennemi009.h"
#include "../../content/ennemis/Ennemi010.h"
#include "../../content/ennemis/Ennemi011.h"
#include "../../content/ennemis/Ennemi012.h"
#include "../../content/ennemis/Ennemi013.h"
#include "../../content/ennemis/Ennemi014.h"
#include "../../content/ennemis/Ennemi015.h"
#include "../../content/ennemis/Ennemi016.h"
#include "../../content/ennemis/Ennemi018.h"
#include "../../content/ennemis/Ennemi019.h"
#include "../../content/ennemis/Ennemi021.h"
#include "../../content/ennemis/Ennemi022.h"
#include "../../content/ennemis/Ennemi023.h"
#include "../../content/ennemis/Ennemi024.h"
#include "../../content/ennemis/Ennemi025.h"
#include "../../content/ennemis/Ennemi026.h"
#include "../../content/ennemis/Ennemi027.h"
#include "../../content/ennemis/Ennemi028.h"
#include "../../content/ennemis/Ennemi029.h"
#include "../../content/ennemis/Ennemi030.h"
#include "../../content/ennemis/Ennemi031.h"
#include "../../content/ennemis/Ennemi032.h"
#include "../../content/ennemis/Ennemi033.h"
#include "../../content/ennemis/Ennemi034.h"
#include "../../content/ennemis/Ennemi035.h"
#include "../../content/ennemis/Ennemi037.h"
#include "../../content/ennemis/Ennemi038.h"
#include "../../content/ennemis/Ennemi039.h"
#include "../../content/ennemis/Ennemi040.h"
#include "../../content/ennemis/Ennemi041.h"
#include "../../content/ennemis/Ennemi042.h"
#include "../../content/ennemis/Ennemi043.h"
#include "../../content/ennemis/Ennemi044.h"
#include "../../content/ennemis/Ennemi045.h"
#include "../../content/ennemis/Ennemi046.h"
#include "../../content/ennemis/Ennemi047.h"
#include "../../content/ennemis/Ennemi048.h"
#include "../../content/ennemis/Ennemi050.h"
#include "../../content/ennemis/Ennemi053.h"

Monsters::Monsters() : page(0) {
    image = ResourceManager::getInstance()->loadImage("data/images/menus/cadres.png");
    for (int i = 0; i < 4; i++) {
        texts[i] = 0;
    }
    for (int i = 0; i < NB_MONSTERS; i++) {
        ennemis[i] = 0;
    }
}

Monsters::~Monsters() {
    ResourceManager::getInstance()->free(image);
    for (int i = 0; i < 4; i++) {
        delete texts[i];
    }
    for (int i = 0; i < NB_MONSTERS; i++) {
        delete ennemis[i];
    }
}

void Monsters::init() {
    page = 0;

    for (int i = 0; i < 4; i++) {
        delete texts[i];
    }

    for (int i = 0; i < 4; i++) {
        texts[i] = TextManager::getInstance()->getText(147 + i);
    }
    initPage();
}

void Monsters::initPage() {
    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    switch (page) {
        case 0 :
            if (scene->getMonsters(4) && !ennemis[4]) ennemis[4] = (Ennemi*)(new Ennemi004(152 + 8, 8 + 8));
            if (scene->getMonsters(53) && !ennemis[53]) ennemis[53] = (Ennemi*)(new Ennemi053(208 + 8, 8 + 8));
            if (scene->getMonsters(11) && !ennemis[11]) ennemis[11] = (Ennemi*)(new Ennemi011(264 + 8, 8 + 8, true));
            if (scene->getMonsters(12) && !ennemis[12]) ennemis[12] = (Ennemi*)(new Ennemi012(16 + 16, 48 + 16));
            if (scene->getMonsters(10) && !ennemis[10]) ennemis[10] = (Ennemi*)(new Ennemi010(96 + 16, 48 + 16));
            if (scene->getMonsters(9) && !ennemis[9]) ennemis[9] = (Ennemi*)(new Ennemi009(176 + 16, 48 + 12));
            if (scene->getMonsters(8) && !ennemis[8]) ennemis[8] = (Ennemi*)(new Ennemi008(256 + 16, 48 + 12));
            if (scene->getMonsters(1) && !ennemis[1]) ennemis[1] = (Ennemi*)(new Ennemi001(16 + 16, 112 + 12));
            if (scene->getMonsters(6) && !ennemis[6]) ennemis[6] = (Ennemi*)(new Ennemi006(96 + 16, 112 + 2));
            if (scene->getMonsters(5) && !ennemis[5]) ennemis[5] = (Ennemi*)(new Ennemi005(176 + 16, 112 + 12));
            if (scene->getMonsters(16) && !ennemis[16]) ennemis[16] = (Ennemi*)(new Ennemi016(256 + 16, 112 + 12));
            if (scene->getMonsters(15) && !ennemis[15]) ennemis[15] = (Ennemi*)(new Ennemi015(16 + 12, 176 + 6));
            if (scene->getMonsters(3) && !ennemis[3]) ennemis[3] = (Ennemi*)(new Ennemi003(96 + 10, 176 + 16));
            if (scene->getMonsters(13) && !ennemis[13]) ennemis[13] = (Ennemi*)(new Ennemi013(176 + 16, 176 + 16));
            if (scene->getMonsters(14) && !ennemis[14]) ennemis[14] = (Ennemi*)(new Ennemi014(252 + 8, 176 + 16));
            break;
        case 1 :
            if (scene->getMonsters(18) && !ennemis[18]) ennemis[18] = (Ennemi*)(new Ennemi018(16 + 16, 48 + 16));
            if (scene->getMonsters(26) && !ennemis[26]) ennemis[26] = (Ennemi*)(new Ennemi026(96 + 16, 48 + 12));
            if (scene->getMonsters(21) && !ennemis[21]) ennemis[21] = (Ennemi*)(new Ennemi021(176 + 16, 48 + 16));
            if (scene->getMonsters(27) && !ennemis[27]) ennemis[27] = (Ennemi*)(new Ennemi027(256 + 16, 48 + 16));
            if (scene->getMonsters(32) && !ennemis[32]) ennemis[32] = (Ennemi*)(new Ennemi032(16 + 16, 112 + 12));
            if (scene->getMonsters(22) && !ennemis[22]) ennemis[22] = (Ennemi*)(new Ennemi022(96 + 16, 112 + 12));
            if (scene->getMonsters(30) && !ennemis[30]) ennemis[30] = (Ennemi*)(new Ennemi030(176 + 16, 112 + 12));
            if (scene->getMonsters(23) && !ennemis[23]) ennemis[23] = (Ennemi*)(new Ennemi023(256 + 11, 112 + 16));
            if (scene->getMonsters(42) && !ennemis[42]) ennemis[42] = (Ennemi*)(new Ennemi042(16 + 11, 176 + 16));
            if (scene->getMonsters(37) && !ennemis[37]) ennemis[37] = (Ennemi*)(new Ennemi037(96 + 16, 176 + 12));
            if (scene->getMonsters(41) && !ennemis[41]) ennemis[41] = (Ennemi*)(new Ennemi041(176 + 16, 176 + 13));
            if (scene->getMonsters(29) && !ennemis[29]) ennemis[29] = (Ennemi*)(new Ennemi029(256 + 16, 176 + 11));
            break;
        case 2 :
            if (scene->getMonsters(2) && !ennemis[2]) ennemis[2] = (Ennemi*)(new Ennemi002(16 + 13, 48 + 12));
            if (scene->getMonsters(25) && !ennemis[25]) ennemis[25] = (Ennemi*)(new Ennemi025(96 + 10, 48 + 9));
            if (scene->getMonsters(33) && !ennemis[33]) ennemis[33] = (Ennemi*)(new Ennemi033(176 + 13, 48 + 12));
            if (scene->getMonsters(34) && !ennemis[34]) ennemis[34] = (Ennemi*)(new Ennemi034(256 + 12, 48 + 12));
            if (scene->getMonsters(38) && !ennemis[38]) ennemis[38] = (Ennemi*)(new Ennemi038(16 + 13, 112 + 12));
            if (scene->getMonsters(39) && !ennemis[39]) ennemis[39] = (Ennemi*)(new Ennemi039(96 + 12, 112 + 12));
            if (scene->getMonsters(44) && !ennemis[44]) ennemis[44] = (Ennemi*)(new Ennemi044(176 + 13, 112 + 8));
            if (scene->getMonsters(46) && !ennemis[46]) ennemis[46] = (Ennemi*)(new Ennemi046(256 + 13, 112 + 8));
            if (scene->getMonsters(47) && !ennemis[47]) ennemis[47] = (Ennemi*)(new Ennemi047(16 + 13, 176 + 8));
            if (scene->getMonsters(48) && !ennemis[48]) ennemis[48] = (Ennemi*)(new Ennemi048(96 + 13, 176 + 8));
            break;
        case 3 :
            if (scene->getMonsters(19) && !ennemis[19]) ennemis[19] = (Ennemi*)(new Ennemi019(16 + 8, 48 + 8));
            if (scene->getMonsters(24) && !ennemis[24]) ennemis[24] = (Ennemi*)(new Ennemi024(112 + 8, 40 + 8, false));
            if (scene->getMonsters(28) && !ennemis[28]) ennemis[28] = (Ennemi*)(new Ennemi028(176 + 8, 48 + 4));
            if (scene->getMonsters(31) && !ennemis[31]) ennemis[31] = (Ennemi*)(new Ennemi031(240 + 8, 48 + 8));
            if (scene->getMonsters(35) && !ennemis[35]) ennemis[35] = (Ennemi*)(new Ennemi035(16 + 8, 112 + 8));
            if (scene->getMonsters(40) && !ennemis[40]) ennemis[40] = (Ennemi*)(new Ennemi040(80 + 5, 108 + 8));
            if (scene->getMonsters(43) && !ennemis[43]) ennemis[43] = (Ennemi*)(new Ennemi043(160 + 8, 112 + 8));
            if (scene->getMonsters(45) && !ennemis[45]) ennemis[45] = (Ennemi*)(new Ennemi045(224 + 8, 104 + 6));
            if (scene->getMonsters(50) && !ennemis[50]) ennemis[50] = (Ennemi*)(new Ennemi050(16 + 8, 176 + 6));
            break;
    }

}

void Monsters::cadre(int x, int y, int w, int h, int type) {

    // center
    for (int j = y + 16; j < y + h - 16; j += 16) {
        for (int i = x + 16; i < x + w - 16; i += 16) {
            WindowManager::getInstance()->draw(image, 16, 64, 16, 16, i, j);
        }
    }

    //top and bottom
    for (int i = x + 16; i < x + w - 16; i += 16) {
        WindowManager::getInstance()->draw(image, 16, 48, 16, 16, i, y);
        WindowManager::getInstance()->draw(image, 16, 80, 16, 16, i, y + h - 16);
    }

    //left and right
    for (int j = y + 16; j < y + h - 16; j += 16) {
        WindowManager::getInstance()->draw(image, 0, 64, 16, 16, x, j);
        WindowManager::getInstance()->draw(image, 32, 64, 16, 16, x + w - 16, j);
    }

    //top left corner
    WindowManager::getInstance()->draw(image, 0, 48, 16, 16, x, y);

    //top right corner
    WindowManager::getInstance()->draw(image, 32, 48, 16, 16, x + w - 16, y);

    //bottom left corner
    WindowManager::getInstance()->draw(image, 0, 80, 16, 16, x, y + h - 16);

    //bottom right corner
    WindowManager::getInstance()->draw(image, 32, 80, 16, 16, x + w - 16, y + h - 16);


    // monsters

    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();

    if (scene->getMonsters(type)) {
        ennemis[type]->draw(0, 0);
    }

}

void Monsters::handleActions(Action* action) {
    if (action->isAction(MONSTERS)) {
        MainController::getInstance()->getGameController()->setStep(GAME_MAIN);
        AudioManager::getInstance()->playSound(TS_MENU2);
        return;
    }
    int old = page;
    if (action->isAction(PUSH_LEFT)) {
        page = getPreviousPageFrom(page);
    } else if (action->isAction(PUSH_RIGHT)) {
        page = getNextPageFrom(page);
    }
    if (page != old) {
        initPage();
        AudioManager::getInstance()->playSound(TS_MENU3);
    }
}

void Monsters::draw() {
    int letterSize = TextManager::getInstance()->getWSpace();

    for (int j = 0; j < 15; j++) {
        for (int i = 0; i < 20; i++) {
            WindowManager::getInstance()->draw(image, 16, 16, 16, 16, i * 16, j * 16);
        }
    }

    // title

    Text* title = texts[page];
    int size = title->getLength() * letterSize;
    int blocs = (size + 15) / 16;

    int x = 16;
    WindowManager::getInstance()->draw(image, 0, 0, 16, 16, x, 0);
    WindowManager::getInstance()->draw(image, 0, 16, 16, 16, x, 16);
    WindowManager::getInstance()->draw(image, 0, 32, 16, 16, x, 32);

    for (int i = 0; i <= blocs; i++) {
        x += 16;
        WindowManager::getInstance()->draw(image, 16, 0, 16, 16, x, 0);
        WindowManager::getInstance()->draw(image, 16, 64, 16, 16, x, 16);
        WindowManager::getInstance()->draw(image, 16, 32, 16, 16, x, 32);
    }

    x += 16;
    WindowManager::getInstance()->draw(image, 32, 0, 16, 16, x, 0);
    WindowManager::getInstance()->draw(image, 32, 16, 16, 16, x, 16);
    WindowManager::getInstance()->draw(image, 32, 32, 16, 16, x, 32);

    title->display(32 + 8 + ((blocs * 16) - size) / 2, 16);

    // monsters

    switch (page) {
        case 0 :
            cadre(152,8,32,32, 4);
            cadre(208,8,32,32, 53);
            cadre(264,8,32,32, 11);
            cadre(16,48,48,48, 12);
            cadre(96,48,48,48, 10);
            cadre(176,48,48,48, 9);
            cadre(256,48,48,48, 8);
            cadre(16,112,48,48, 1);
            cadre(96,112,48,48, 6);
            cadre(176,112,48,48, 5);
            cadre(256,112,48,48, 16);
            cadre(16,176,48,48, 15);
            cadre(96,176,48,48, 3);
            cadre(176,176,48,48, 13);
            cadre(252,176,56,48, 14);
            break;
        case 1 :
            cadre(16,48,48,48,18);
            cadre(96,48,48,48,26);
            cadre(176,48,48,48,21);
            cadre(256,48,48,48,27);
            cadre(16,112,48,48,32);
            cadre(96,112,48,48,22);
            cadre(176,112,48,48,30);
            cadre(256,112,48,48,23);
            cadre(16,176,48,48,42);
            cadre(96,176,48,48,37);
            cadre(176,176,48,48,41);
            cadre(256,176,48,48,29);
            break;
        case 2 :
            cadre(16,48,48,48,2);
            cadre(96,48,48,48,25);
            cadre(176,48,48,48,33);
            cadre(256,48,48,48,34);
            cadre(16,112,48,48,38);
            cadre(96,112,48,48,39);
            cadre(176,112,48,48,44);
            cadre(256,112,48,48,46);
            cadre(16,176,48,48,47);
            cadre(96,176,48,48,48);
            break;
        case 3 :
            cadre(16,48,80,48,19);
            cadre(112,40,48,64,24);
            cadre(176,48,48,48,28);
            cadre(240,48,48,48,31);
            cadre(16,112,48,48,35);
            cadre(80,108,64,56,40);
            cadre(160,112,48,48,43);
            cadre(224,104,80,88,45);
            cadre(16,176,64,48,50);
            break;
    }
}

int Monsters::getNextPageFrom(int p) {
    int next = p + 1;

    for (int i = 0; i < 4; i ++) {
        if (next > 3) {
            next = 0;
        }
        if (!isPageEmpty(next)) {
            return next;
        }
        next++;
    }

    return p;
}

int Monsters::getPreviousPageFrom(int p) {
    int previous = p - 1;

    for (int i = 0; i < 4; i ++) {
        if (previous < 0) {
            previous = 3;
        }
        if (!isPageEmpty(previous)) {
            return previous;
        }
        previous--;
    }

    return p;
}

bool Monsters::isPageEmpty(int p) {
    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    switch (p) {
        case 0 :
            if (scene->getMonsters(4) || scene->getMonsters(53) || scene->getMonsters(11)
                 || scene->getMonsters(12) || scene->getMonsters(10) || scene->getMonsters(9)
                 || scene->getMonsters(8) || scene->getMonsters(1) || scene->getMonsters(6)
                 || scene->getMonsters(5) || scene->getMonsters(16) || scene->getMonsters(15)
                 || scene->getMonsters(3) || scene->getMonsters(13) || scene->getMonsters(14)) {
                return false;
            }
            break;
        case 1 :
            if (scene->getMonsters(18) || scene->getMonsters(26) || scene->getMonsters(21)
                 || scene->getMonsters(27) || scene->getMonsters(32) || scene->getMonsters(22)
                 || scene->getMonsters(30) || scene->getMonsters(23) || scene->getMonsters(42)
                 || scene->getMonsters(37) || scene->getMonsters(41) || scene->getMonsters(29)) {
                return false;
            }
            break;
        case 2 :
            if (scene->getMonsters(2) || scene->getMonsters(25) || scene->getMonsters(33)
                 || scene->getMonsters(34) || scene->getMonsters(38) || scene->getMonsters(39)
                 || scene->getMonsters(44) || scene->getMonsters(46) || scene->getMonsters(47)
                 || scene->getMonsters(48)) {
                return false;
            }
            break;
        case 3 :
            if (scene->getMonsters(19) || scene->getMonsters(24) || scene->getMonsters(28)
                 || scene->getMonsters(31) || scene->getMonsters(35) || scene->getMonsters(40)
                 || scene->getMonsters(43) || scene->getMonsters(45) || scene->getMonsters(50)) {
                return false;
            }
            break;
    }
    return true;
}
