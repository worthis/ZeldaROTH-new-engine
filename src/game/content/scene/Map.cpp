#include "Map.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../MainController.h"

#include "../helper/MapHelper.h"
#include "../helper/ProjectileHelper.h"

#include "../types/Poussable.h"

#include "../objects/Interrupteur.h"
#include "../effects/Feuilles.h"
#include "../effects/Debris.h"
#include "../objects/Pnj.h"
#include "../objects/Interrupteur.h"
#include "../objects/Coffre.h"
#include "../objects/Poule.h"
#include "../objects/Sphere.h"
#include "../objects/PiegeDemi.h"
#include "../objects/PiegePics.h"

Map::Map(int level, Metronome* metronome) : metronome(metronome), map(level),
w(0), h(0), music(0), effects(0),
ennemis(0), items(0), projectiles(0), objects(0), oldMetronomeValue(0) {

    ostringstream os;
    for (int i = 0; i < NB_IMAGES; i++) {
        os << (i + 1);
        string filename = "data/images/tileset/image" + os.str() + ".png";
        images[i] = ResourceManager::getInstance()->loadImage(filename, true);
        os.str("");
    }

    initializer = new MapInitializer(this);
}

Map::~Map() {
    for (int i = 0; i < NB_IMAGES; i++) {
        ResourceManager::getInstance()->free(images[i]);
    }
    delete effects;
    delete ennemis;
    delete items;
    delete projectiles;
    delete objects;
    delete initializer;
}

void Map::load() {

    for (int j = 0; j < MAX_CASE_Y; j++) {
        for (int i = 0; i < MAX_CASE_X; i++) {
            sol[i][j] = -1;
            air[i][j] = -1;
            mur[i * 2][j * 2] = HERBE;
            mur[i * 2 + 1][j * 2] = HERBE;
            mur[i * 2][j * 2 + 1] = HERBE;
            mur[i * 2 + 1][j * 2 + 1] = HERBE;
        }
    }

    loadFromFile();


    bounds.setX(0);
    bounds.setY(0);
    bounds.setW(w);
    bounds.setH(h);

    delete effects;
    effects = new Quadtree();
    effects->setBox(0, 0, w, h);

    delete ennemis;
    ennemis = new Quadtree();
    ennemis->setBox(0, 0, w, h);

    delete items;
    items = new Quadtree();
    items->setBox(0, 0, w, h);

    delete projectiles;
    projectiles = new Quadtree();
    projectiles->setBox(0, 0, w, h);

    delete objects;
    objects = new Quadtree();
    objects->setBox(0, 0, w, h);

    init();
}

void Map::loadFromFile() {
    ostringstream oss;
    oss << map;
    string result = "data/maps/map" + oss.str() + ".dat";
    ifstream file(result.c_str());

    file >> w;
    file >> h;
    file >> music;

    for (int i=0; i<w/16; i++){
        for (int j=0; j<h/16; j++){
            file >> sol[i][j];
            file >> mur[i*2][j*2];
            file >> mur[i*2+1][j*2];
            file >> mur[i*2][j*2+1];
            file >> mur[i*2+1][j*2+1];
        }
    }

    int cpt = 0;
    int a;
    int b;

    file >> cpt;
    for (int i=0; i<cpt; i++) {
        file >> a;
        file >> b;
        file >> air[a][b];
    }

    file.close();
}

int Map::getW() {
    return w;
}

int Map::getH() {
    return h;
}

int Map::getId() {
    return map;
}

void Map::launch() {

    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();

    if (scene->getAvancement() != AV_START) {

        int musicToPlay = music;

        int special = scene->getAnimationInGame()->getSpecialMusicId();

        if (special > 0) {
            musicToPlay = special;
        }

        if (scene->getLink()->getStatus()->getLife() <= 0) {
            musicToPlay = 3;
        }

        AudioManager::getInstance()->playMusic(musicToPlay);

    }

    launchRoom();
}

void Map::launchRoom() {
    if (map >= 12) { // indoor only
        Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
        Link* link = scene->getLink();


        bounds.setX(320 * (link->getX() / 320));
        bounds.setY(240 * (link->getY() / 240));
        bounds.setW(320);
        bounds.setH(240);

        // handle big rooms
        switch (map) {
            case 12 :
                if (bounds.getX() >= 320*5 && bounds.getX() <= 320*6 && bounds.getY() == 0) {
                    bounds.setX(320*5 + 160);
                    break;
                }
                if (bounds.getX() >= 320 && bounds.getX() <= 320*2 && bounds.getY() == 0) {
                    bounds.setX(320);
                    bounds.setW(640);
                    break;
                }
                if (bounds.getX() >= 320 && bounds.getX() <= 320*2 && bounds.getY() == 240*4) {
                    bounds.setX(320);
                    bounds.setW(640);
                    break;
                }
                if (bounds.getX() >= 320*5 && bounds.getX() <= 320*6 && bounds.getY() == 240*3) {
                    bounds.setX(320*5);
                    bounds.setW(640);
                    break;
                }
                if (bounds.getX() >= 320 && bounds.getX() <= 320*2
                    && bounds.getY() >= 240 && bounds.getY() <= 240*3) {
                    bounds.setX(320);
                    bounds.setY(240);
                    bounds.setW(640);
                    bounds.setH(720);
                    break;
                }
                if (bounds.getX() >= 320*5 && bounds.getX() <= 320*6
                    && bounds.getY() >= 240 && bounds.getY() <= 240*2) {
                    bounds.setX(320*5);
                    bounds.setY(240);
                    bounds.setW(640);
                    bounds.setH(480);
                    break;
                }
                break;
            case 13 :
                if (bounds.getX() == 320 && bounds.getY() >= 240 && bounds.getY() <= 240 * 2) {
                    bounds.setY(240);
                    bounds.setH(480);
                    break;
                }
                if (bounds.getX() == 320*2 && bounds.getY() >= 240*3 && bounds.getY() <= 240*4) {
                    bounds.setY(240*3);
                    bounds.setH(480);
                    break;
                }
                if (bounds.getX() == 320*4 && bounds.getY() >= 240*3 && bounds.getY() <= 240*4) {
                    bounds.setY(240*3);
                    bounds.setH(480);
                    break;
                }
                if (bounds.getX() == 320*5 && bounds.getY() >= 240 && bounds.getY() <= 240 * 2) {
                    bounds.setY(240);
                    bounds.setH(480);
                    break;
                }
                if (bounds.getX() >= 320*2 && bounds.getX() <= 320*4
                    && bounds.getY() >= 240 && bounds.getY() <= 240*2) {
                    bounds.setX(320*2);
                    bounds.setY(240);
                    bounds.setW(960);
                    bounds.setH(480);
                    break;
                }
                break;
            case 14 :
                if (bounds.getX() <= 320*1 && bounds.getY() == 240*1) {
                    bounds.setX(0);
                    bounds.setW(640);
                    break;
                }
                if (bounds.getX() >= 320 && bounds.getX() <= 320*2 && (bounds.getY() == 0 || bounds.getY() == 240*4)) {
                    bounds.setX(320);
                    bounds.setW(640);
                    break;
                }
                if (bounds.getX() >= 320*5 && bounds.getX() <= 320*6 && bounds.getY() == 240*2) {
                    bounds.setX(320*5);
                    bounds.setW(640);
                    break;
                }
                if ((bounds.getX() == 0 || bounds.getX() == 320*4 || bounds.getX() == 320*9)
                    && bounds.getY() >= 240*2 && bounds.getY() <= 240*3) {
                    bounds.setY(240*2);
                    bounds.setH(480);
                    break;
                }
                if (bounds.getX() == 320*3 && bounds.getY() <= 240) {
                    bounds.setY(0);
                    bounds.setH(480);
                    break;
                }
                break;
            case 15 :
                if (bounds.getX() >= 320 && bounds.getX() <= 320*3 && bounds.getY() <= 240) {
                    bounds.setX(320);
                    bounds.setW(960);
                    break;
                }
                if (bounds.getX() == 320 * 4 && bounds.getY() >= 240 && bounds.getY() <= 240 * 2) {
                    bounds.setY(240);
                    bounds.setH(480);
                    break;
                }
                if (bounds.getX() == 320 * 2 && bounds.getY() >= 240 * 3) {
                    bounds.setY(240*3);
                    bounds.setH(480);
                    break;
                }
                break;
            case 16 :
                if (bounds.getX() >= 320*6 && bounds.getX() <= 320*7 && bounds.getY() == 0) {
                    bounds.setX(320*6);
                    bounds.setW(640);
                    break;
                }
                if (bounds.getX() >= 320*5 && bounds.getX() <= 320*7 && bounds.getY() == 240*3) {
                    bounds.setX(320*5);
                    bounds.setW(960);
                    break;
                }
                if (bounds.getX() >= 320*3 && bounds.getX() <= 320*4 && bounds.getY() <= 240*2) {
                    bounds.setX(320*3);
                    bounds.setY(0);
                    bounds.setW(640);
                    bounds.setH(720);
                    break;
                }
                if (bounds.getX() >= 320*3 && bounds.getX() <= 320*4
                    && bounds.getY() >= 240*3 && bounds.getY() <= 240*5) {
                    bounds.setX(320*3);
                    bounds.setY(240*3);
                    bounds.setW(640);
                    bounds.setH(720);
                    break;
                }
                if (bounds.getX() >= 320*6 && bounds.getX() <= 320*7
                    && bounds.getY() >= 240 && bounds.getY() <= 240*2) {
                    bounds.setX(320*6);
                    bounds.setY(240);
                    bounds.setW(640);
                    bounds.setH(480);
                    break;
                }
                break;
            case 17 :
                if ((bounds.getX() == 0 || bounds.getX() == 320 * 6) && bounds.getY() >= 240 * 3 && bounds.getY() <= 240 * 4) {
                    bounds.setY(240 * 3);
                    bounds.setH(480);
                    break;
                }
                if ((bounds.getX() == 320 * 2 || bounds.getX() == 320 * 4) && bounds.getY() >= 240 * 4 && bounds.getY() <= 240 * 5) {
                    bounds.setY(240 * 4);
                    bounds.setH(480);
                    break;
                }
                if (bounds.getX() == 320 * 3 && bounds.getY() >= 240 * 7 && bounds.getY() <= 240 * 8) {
                    bounds.setY(240 * 7);
                    bounds.setH(480);
                    break;
                }
                if (bounds.getX() <= 320 && (bounds.getY() == 240*5 || bounds.getY() == 240*6)) {
                    bounds.setX(0);
                    bounds.setW(640);
                    break;
                }
                if (bounds.getX() >= 320*5 && bounds.getX() <= 320*6 && bounds.getY() == 240 * 5) {
                    bounds.setX(320*5);
                    bounds.setW(640);
                    break;
                }
                if (bounds.getX() <= 320
                    && bounds.getY() >= 240*7 && bounds.getY() <= 240*8) {
                    bounds.setX(0);
                    bounds.setY(240*7);
                    bounds.setW(640);
                    bounds.setH(480);
                    break;
                }
                if (bounds.getX() >= 320*5 && bounds.getX() <= 320*6
                    && bounds.getY() >= 240*7 && bounds.getY() <= 240*8) {
                    bounds.setX(320*5);
                    bounds.setY(240*7);
                    bounds.setW(640);
                    bounds.setH(480);
                    break;
                }
                break;
            case 18 :
                if (bounds.getX() >= 320 && bounds.getX() <= 320*3 && bounds.getY() == 0) {
                    bounds.setX(320);
                    bounds.setW(960);
                    break;
                }
                if (bounds.getX() >= 320*6 && bounds.getX() <= 320*8 && bounds.getY() == 0) {
                    bounds.setX(320*6);
                    bounds.setW(960);
                    break;
                }
                if (bounds.getX() >= 320*7 && bounds.getX() <= 320*8 && bounds.getY() == 240*4) {
                    bounds.setX(320*7);
                    bounds.setW(640);
                    break;
                }
                if ((bounds.getX() == 0 || bounds.getX() == 320 * 4
                     || bounds.getX() == 320 * 5 || bounds.getX() == 320 * 9)
                    && bounds.getY() >= 240 && bounds.getY() <= 240 * 3) {
                    bounds.setY(240);
                    bounds.setH(720);
                    break;
                }
                if ((bounds.getX() == 320 || bounds.getX() == 320 * 2 || bounds.getX() == 320 * 6)
                    && bounds.getY() >= 240*2 && bounds.getY() <= 240 * 3) {
                    bounds.setY(240*2);
                    bounds.setH(480);
                    break;
                }
                break;
            case 19 :
                if (bounds.getX() == 320 && bounds.getY() == 240 * 4) {
                    AudioManager::getInstance()->playMusic(18);
                }
                if (bounds.getX() == 320 && bounds.getY() >= 240 && bounds.getY() <= 240 * 2) {
                    bounds.setY(240);
                    bounds.setH(480);
                    break;
                }
                if ((bounds.getX() == 320 || bounds.getX() == 320*2) && bounds.getY() >= 240 * 4 && bounds.getY() <= 240 * 5) {
                    bounds.setY(240*4);
                    bounds.setH(480);
                    break;
                }
                if ((bounds.getX() == 320 || bounds.getX() == 320*2) && bounds.getY() >= 240 * 7 && bounds.getY() <= 240 * 8) {
                    bounds.setY(240*7);
                    bounds.setH(480);
                    break;
                }
                if (bounds.getX() == 320*2 && bounds.getY() >= 240 && bounds.getY() <= 240 * 3) {
                    bounds.setY(240);
                    bounds.setH(720);
                    break;
                }
                break;
            case 20 :
                if (bounds.getX() == 320*10 && bounds.getY() == 240 && scene->getAvancement() < AV_ZELDA_SUIT) {
                    AudioManager::getInstance()->playMusic(22);
                }
                if ((bounds.getX() == 320*11 && bounds.getY() == 240)
                    || (bounds.getX() == 320*10 && bounds.getY() == 240*2)) {
                    AudioManager::getInstance()->playMusic(20);
                }
                if (scene->getAvancement() == AV_ZELDA_SUIT) {
                    BoundingBox bb = BoundingBox(0, 0, w, h);
                    List list;
                    objects->get(&bb, &list);

                    list.iterateOnFirst();
                    while (list.hasNext()) {
                        Pnj* zelda = dynamic_cast<Pnj*>(list.getNext());
                        if (zelda != 0) {
                            if (link->getX() - bounds.getX() < 48) {
                                zelda->moveTo(bounds.getX() + 8, link->getY() + 1, E);
                            } else if (link->getX() - bounds.getX() > bounds.getW() - 48) {
                                zelda->moveTo(bounds.getX() + bounds.getW() - 24, link->getY() + 1, W);
                            } else if (link->getY() - bounds.getY() < 48) {
                                zelda->moveTo(link->getX(), bounds.getY() + 1, S);
                            } else if (link->getY() - bounds.getY() > bounds.getH() - 64) {
                                zelda->moveTo(link->getX(), bounds.getY() + bounds.getH() - 31, N);
                            } else if (link->getY() % 240 == 16 * 4 + 8) {
                                zelda->moveTo(link->getX(), link->getY() + 1 + 24, N);
                            } else {
                                zelda->moveTo(link->getX(), link->getY() - 23, S);
                            }
                            break;
                        }
                    }
                }

                if (bounds.getX() >= 320*2 && bounds.getX() <= 320*4 && bounds.getY() == 240*3) {
                    bounds.setX(320*2);
                    bounds.setW(960);
                    break;
                }
                if (bounds.getX() >= 320*3 && bounds.getX() <= 320*4 && bounds.getY() == 0) {
                    bounds.setX(320*3);
                    bounds.setW(640);
                    break;
                }
                if (bounds.getX() >= 320*6 && bounds.getX() <= 320*7 && bounds.getY() == 240*5) {
                    bounds.setX(320*6);
                    bounds.setW(640);
                    break;
                }
                if (bounds.getX() >= 320*8 && bounds.getX() <= 320*9 && bounds.getY() == 240*6) {
                    bounds.setX(320*8);
                    bounds.setW(640);
                    break;
                }
                if ((bounds.getX() == 320 || bounds.getX() == 320*5 || bounds.getX() == 320*8 || bounds.getX() == 320*12)
                    && bounds.getY() >= 240 * 4 && bounds.getY() <= 240 * 5) {
                    bounds.setY(240*4);
                    bounds.setH(480);
                    break;
                }
                if ((bounds.getX() == 320*3 || bounds.getX() == 320*4 || bounds.getX() == 320*5 || bounds.getX() == 320*11)
                    && bounds.getY() >= 240 && bounds.getY() <= 240 * 2) {
                    bounds.setY(240);
                    bounds.setH(480);
                    break;
                }
                if ((bounds.getX() == 320*8 || bounds.getX() == 320*12) && bounds.getY() >= 240 * 2 && bounds.getY() <= 240 * 3) {
                    bounds.setY(240*2);
                    bounds.setH(480);
                    break;
                }
                break;
            case 21 :
                if (bounds.getX() == 0 && bounds.getY() <= 240) {
                    bounds.setY(0);
                    bounds.setH(480);
                    break;
                }
                if (bounds.getX() == 320 && bounds.getY() >= 240 && bounds.getY() <= 240 * 2) {
                    bounds.setY(240);
                    bounds.setH(480);
                    break;
                }
                break;
            case 22 :
                if (bounds.getX() >= 320 && bounds.getX() <= 320*2 && bounds.getY() == 0) {
                    bounds.setX(320);
                    bounds.setW(640);
                    break;
                }
                if (bounds.getX() == 320*3 && bounds.getY() >= 240 && bounds.getY() <= 240 * 3) {
                    bounds.setY(240);
                    bounds.setH(720);
                    break;
                }
                if (bounds.getX() <= 320*2 && bounds.getY() >= 240*2) {
                    bounds.setX(0);
                    bounds.setY(240*2);
                    bounds.setW(960);
                    bounds.setH(720);
                    break;
                }
                break;
            case 29 :
                bounds.setX(0);
                bounds.setW(640);
                break;
            case 33 :
                bounds.setY(0);
                bounds.setH(480);
                break;
            default : break;
        }

        if (map > 11 && map < 21) {
            for (int j = bounds.getY() / 240; j < (bounds.getY() + bounds.getH()) / 240; j++) {
                for (int i = bounds.getX() / 320; i < (bounds.getX() + bounds.getW()) / 320; i++) {
                    scene->setRooms(map - 12, i, j, 1);
                    if (bounds.getX() % 320 != 0) {
                        scene->setRooms(map - 12, i + 1, j, 1);
                    }
                }
            }
        }

        testAnimRoom();
    }
}

void Map::resetRoom() {
    if (map >= 12) {

        objects->resetNodes(&bounds);
        ennemis->resetNodes(&bounds);

        List toKill;
        effects->get(&bounds, &toKill);
        items->get(&bounds, &toKill);
        projectiles->get(&bounds, &toKill);

        toKill.iterateOnFirst();
        while (toKill.hasNext()) {
            Node* n = (Node*) toKill.getNext();
            if (!n->isResetable()) {
                n->killNode();
            }
        }
    }
}

BoundingBox* Map::getBounds() {
    return &bounds;
}

void Map::reset() {
    load();
    launch();
}

void Map::init() {
    initializer->init();
}

void Map::activateInter(int x, int y, bool sound) {
    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    switch (map) {
        case 16 :
            scene->setCoffre(5, 6, 1);
            if (sound) AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(129, 13, 0);
            break;
        case 20 :
            if (x == 22*16 && y == 57*16) {
                scene->setCoffre(9, 11, 1);
                if (sound) AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(38, 51, 1);
            }
            if (x == 117*16 && y == 57*16) {
                scene->setCoffre(9, 12, 1);
                if (sound) AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(98, 51, 1);
            }
            break;
        case 22 :
            scene->setCoffre(0, 7, 1);
            if (sound) AudioManager::getInstance()->playSound(TS_DOOR);
            ouvrePorte(18, 6, 1);
            break;
    }
}

bool Map::desactivateInter(int x, int y, bool sound) {
    return true;
}

void Map::allumeTorche(int x, int y) {
    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    switch (map) {
        case 14 :
            if ((x == 27 || x == 32) && y == 41) {
                if (sol[27][41] == 1415 && sol[32][41] == 1415 && mur[29 * 2 + 1][43 * 2 + 1] == MUR) {
                    scene->setCoffre(3, 14, 1);
                    AudioManager::getInstance()->playSound(TS_DOOR);
                    ouvrePorte(29, 43, 0);
                }
            }
            if ((x == 47 || x == 52) && y == 26) {
                if (sol[47][26] == 1415 && sol[52][26] == 1415 && mur[49 * 2 + 1][28 * 2 + 1] == MUR) {
                    scene->setCoffre(3, 15, 1);
                    AudioManager::getInstance()->playSound(TS_DOOR);
                    ouvrePorte(49, 28, 0);
                }
            }
            if ((x == 107 || x == 112) && y == 63) {
                if (sol[107][63] == 1415 && sol[112][63] == 1415 && mur[109 * 2 + 1][58 * 2 + 1] == MUR) {
                    scene->setCoffre(3, 16, 1);
                    AudioManager::getInstance()->playSound(TS_DOOR);
                    ouvrePorte(109, 58, 0);
                }
            }
            if (((x == 143 || x == 156) && y == 26)
                || ((x == 147 || x == 152) && y == 18)) {
                if (sol[143][26] == 1415 && sol[147][18] == 1415
                    && sol[152][18] == 1415 && sol[156][26] == 1415
                    && mur[149 * 2 + 1][13 * 2 + 1] == MUR) {
                    scene->setCoffre(3, 17, 1);
                    AudioManager::getInstance()->playSound(TS_DOOR);
                    ouvrePorte(149, 13, 0);
                }
            }
            break;
        case 17 :
            if (x == 19 && y == 119) {
                if (sol[19][119] == 1415 && mur[38 * 2 + 1][127 * 2] == MUR) {
                    scene->setCoffre(6, 10, 1);
                    AudioManager::getInstance()->playSound(TS_DOOR);
                    ouvrePorte(38, 126, 1);
                }
            }
            if ((x == 77 && y == 17)
                || ((x == 62 || x == 77) && y == 27)) {
                if (sol[77][17] == 1415
                    && sol[62][27] == 1415 && sol[77][27] == 1415
                    && mur[69 * 2 + 1][13 * 2 + 1] == MUR) {
                    scene->setCoffre(6, 11, 1);
                    AudioManager::getInstance()->playSound(TS_DOOR);
                    ouvrePorte(69, 13, 0);
                }
            }
            if ((x == 62 || x == 77) && (y == 32 || y == 42)) {
                if (sol[62][32] == 1415 && sol[77][32] == 1415
                    && sol[62][42] == 1415 && sol[77][42] == 1415
                    && mur[69 * 2 + 1][28 * 2 + 1] == MUR) {
                    scene->setCoffre(6, 12, 1);
                    AudioManager::getInstance()->playSound(TS_DOOR);
                    ouvrePorte(69, 28, 0);
                }
            }
            if ((x == 63 || x == 76) && y == 52) {
                if (sol[63][52] == 1415 && sol[76][52] == 1415
                    && mur[69 * 2 + 1][43 * 2 + 1] == MUR) {
                    scene->setCoffre(6, 13, 1);
                    AudioManager::getInstance()->playSound(TS_DOOR);
                    ouvrePorte(69, 43, 0);
                }
            }
            if ((x == 68 || x == 71) && y == 62) {
                if (sol[68][62] == 1415 && sol[71][62] == 1415
                    && mur[69 * 2 + 1][58 * 2 + 1] == MUR) {
                    scene->setCoffre(6, 14, 1);
                    AudioManager::getInstance()->playSound(TS_DOOR);
                    ouvrePorte(69, 58, 0);
                }
            }
            if ((x == 69 || x == 70) && y == 97) {
                if (sol[69][97] == 1415 && sol[70][97] == 1415
                    && mur[58 * 2 + 1][97 * 2] == MUR) {
                    scene->setCoffre(6, 15, 1);
                    AudioManager::getInstance()->playSound(TS_DOOR);
                    ouvrePorte(58, 96, 1);
                    ouvrePorte(78, 96, 1);
                }
            }
            if (x == 62 && (y == 125 || y == 129)) {
                if (sol[62][125] == 1415 && sol[62][129] == 1415
                    && mur[58 * 2 + 1][127 * 2] == MUR) {
                    scene->setCoffre(6, 16, 1);
                    AudioManager::getInstance()->playSound(TS_DOOR);
                    ouvrePorte(58, 126, 1);
                }
            }
            if (x == 77 && (y == 125 || y == 129)) {
                if (sol[77][125] == 1415 && sol[77][129] == 1415
                    && mur[78 * 2 + 1][127 * 2] == MUR) {
                    scene->setCoffre(6, 17, 1);
                    AudioManager::getInstance()->playSound(TS_DOOR);
                    ouvrePorte(78, 126, 1);
                }
            }
            if ((x == 68 || x == 71) && y == 137) {
                if (sol[68][137] == 1415 && sol[71][137] == 1415
                    && mur[69 * 2 + 1][133 * 2 + 1] == MUR) {
                    scene->setCoffre(6, 18, 1);
                    AudioManager::getInstance()->playSound(TS_DOOR);
                    ouvrePorte(69, 133, 0);
                }
            }
            if ((x == 102 || x == 137) && (y == 107 || y == 132)) {
                if (sol[102][107] == 1415 && sol[137][107] == 1415
                    && sol[102][132] == 1415 && sol[137][132] == 1415
                    && mur[98 * 2 + 1][127 * 2] == MUR) {
                    scene->setCoffre(6, 19, 1);
                    AudioManager::getInstance()->playSound(TS_DOOR);
                    ouvrePorte(98, 126, 1);
                }
            }
            break;
    }
}

void Map::eteintTorche(int x, int y) {
    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    switch (map) {
        case 18 :
            if (x == 17 && (y == 65 || y == 69)) {
                if (sol[17][65] == 1414 && sol[17][69] == 1414 && mur[18 * 2 + 1][67 * 2] == MUR) {
                    scene->setCoffre(7, 8, 1);
                    AudioManager::getInstance()->playSound(TS_DOOR);
                    ouvrePorte(18, 66, 1);
                }
            }
            if (x == 182 && (y == 65 || y == 69)) {
                if (sol[182][65] == 1414 && sol[182][69] == 1414 && mur[178 * 2 + 1][67 * 2] == MUR) {
                    scene->setCoffre(7, 9, 1);
                    AudioManager::getInstance()->playSound(TS_DOOR);
                    ouvrePorte(178, 66, 1);
                }
            }
            if ((x == 188 || x == 191) && y == 62) {
                if (sol[188][62] == 1414 && sol[191][62] == 1414 && mur[189 * 2 + 1][58 * 2 + 1] == MUR) {
                    scene->setCoffre(7, 10, 1);
                    AudioManager::getInstance()->playSound(TS_DOOR);
                    ouvrePorte(189, 58, 0);
                }
            }
            break;
    }
}

void Map::loop() {
    effects->removeDeadNodes();
    ennemis->removeDeadNodes();
    items->removeDeadNodes();
    projectiles->removeDeadNodes();
    objects->removeDeadNodes();


    List toLoop;
    effects->get(&bounds, &toLoop);
    ennemis->get(&bounds, &toLoop);
    items->get(&bounds, &toLoop);
    projectiles->get(&bounds, &toLoop);
    objects->get(&bounds, &toLoop);

    toLoop.iterateOnFirst();
    while (toLoop.hasNext()) {
        Loopable* l = (Loopable*) toLoop.getNext();
        l->loop();
    }

}

void Map::draw(List* toDraw, BoundingBox* box, int dstX, int dstY) {

    int srcX = box->getX();
    int srcY = box->getY();
    int srcW = box->getW();
    int srcH = box->getH();

    drawSol(srcX, srcY, srcW, srcH, dstX, dstY);


    effects->get(box, toDraw);
    ennemis->get(box, toDraw);
    items->get(box, toDraw);
    projectiles->get(box, toDraw);
    objects->get(box, toDraw);

    if (toDraw != 0) {
        toDraw->iterateOnFirst();
        while (toDraw->hasNext()) {
            Drawable* d = (Drawable*) toDraw->getNext();
            d->draw(srcX - dstX, srcY - dstY);
        }
    }

    drawAir(srcX, srcY, srcW, srcH, dstX, dstY);
}

void Map::drawSol(int srcX, int srcY, int srcW, int srcH, int dstX, int dstY) {

    int w = 0;
    int h = 0;
    int diffX = 0;
    int diffY = 0;

    for (int j = srcY; j < srcY + srcH; j += CASE) {
        for (int i = srcX; i < srcX + srcW; i += CASE) {

            diffX = (i % CASE);
            diffY = (j % CASE);

            int motif = getMotif(sol[i / CASE][j / CASE]);

            if (motif >= 0) {

                int im = motif / 1000;
                motif -= im * 1000;

                w = CASE - diffX;
                h = CASE - diffY;

                if (i + w > srcX + srcW) {
                    w = srcX + srcW - i;
                }
                if (j + h > srcY + srcH) {
                    h = srcY + srcH - j;
                }

                WindowManager::getInstance()->draw(
                                            images[im],
                                            (motif % 40) * CASE + diffX,
                                            (motif / 40) * CASE + diffY, w, h,
                                            dstX + i - srcX, dstY + j - srcY);
            }
            i -= diffX;
        }
        j -= diffY;
    }


}

void Map::drawAir(int srcX, int srcY, int srcW, int srcH, int dstX, int dstY) {

    int w = 0;
    int h = 0;
    int diffX = 0;
    int diffY = 0;

    for (int j = srcY; j < srcY + srcH; j += CASE) {
        for (int i = srcX; i < srcX + srcW; i += CASE) {

            diffX = (i % CASE);
            diffY = (j % CASE);

            int motif = getMotif(air[i / CASE][j / CASE]);

            if (motif >= 0) {

                int im = motif / 1000;
                motif -= im * 1000;

                w = CASE - diffX;
                h = CASE - diffY;

                if (i + w > srcX + srcW) {
                    w = srcX + srcW - i;
                }
                if (j + h > srcY + srcH) {
                    h = srcY + srcH - j;
                }

                WindowManager::getInstance()->draw(
                                            images[im],
                                            (motif % 40) * CASE + diffX, (motif / 40) * CASE + diffY, w, h,
                                            dstX + i - srcX, dstY + j - srcY);
            }
            i -= diffX;
        }
        j -= diffY;
    }

}

int Map::getMotif(int value) {
    int tmp = metronome->getValue();
    switch (value) {
        case 1 : // fleurs
            switch (tmp % 4) {
                case 0 : return 2;
                case 1 : return 1;
                case 2 : return 3;
                case 3 : return 1;
            }
            break;
        case 329 : case 330 : case 331 : case 332 : case 333 :  case 334 :
        case 335 : case 336 :
            switch (tmp % 4) {
                case 0 : return value;
                case 1 : return value + 8;
                case 2 : return value + 8 * 2;
                case 3 : return value + 8;
            }
            break;
        case 67 : case 70 : case 379 : case 382 : case 385 : case 388 :
        case 391 : case 394 : case 401 : case 404 : case 407 : case 410 :
        case 415 : case 418 :
            switch (tmp/2 % 3) {
                case 0 : return value;
                case 1 : return value + 1;
                case 2 : return value + 2;
            }
            break;
        case 353 : case 356 : case 1415 :
            switch (tmp % 4) {
                case 0 : return value;
                case 1 : return value + 1;
                case 2 : return value + 2;
                case 3 : return value + 1;
            }
            break;
        case 614 : case 619 :
            switch (tmp % 3) {
                case 0 : return value;
                case 1 : return value + 1;
                case 2 : return value + 2;
            }
            break;
        case 1421 : case 1422 : case 1423 : case 1424 : case 1425 : case 1426 : case 1427 :
        case 1428 : case 1429 : case 1430 : case 1431 : case 1432 : case 1433 :
            switch (tmp / 2 % 3) {
                case 0 : return value;
                case 1 : return value + 13;
                case 2 : return value + 26;
            }
            break;
        case 2160 : // pics
            switch (tmp % 6) {
                case 0 : return value;
                case 1 : return value + 1;
                case 2 : return value + 2;
                case 3 : return value + 3;
                case 4 : return value + 2;
                case 5 : return value + 1;
            }
            break;
        default : break;
    }
    return value;
}

short Map::getMur(int x, int y) {
    return mur[x / 8][y / 8];
}

short Map::getSol(int x, int y) {
    return sol[x / CASE][y / CASE];
}

void Map::setSol(int x, int y, short s) {
    int i = x / CASE;
    int j = y / CASE;
    sol[i][j] = s;
}

void Map::setSol(int x, int y, short s, Collision c) {
    int i = x / CASE;
    int j = y / CASE;
    sol[i][j] = s;
    mur[i * 2][j * 2] = c;
    mur[i * 2 + 1][j * 2] = c;
    mur[i * 2][j * 2 + 1] = c;
    mur[i * 2 + 1][j * 2 + 1] = c;
}

void Map::setSol(int x, int y, int w, int h, short s, Collision c) {
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            setSol(x + i * 16, y + j * 16, s, c);
        }
    }
}

void Map::addEffect(Effect* effect) {
    effects->add((Node*) effect);
}

void Map::addEnnemi(Ennemi* ennemi) {
    ennemis->add((Node*) ennemi);
}

void Map::addItem(Item* item) {
    items->add((Node*) item);
}

void Map::addProjectile(Projectile* projectile) {
    projectiles->add((Node*) projectile);
}

void Map::addObject(Object* object) {
    objects->add((Node*) object);
}

void Map::removeObject(Object* object) {
    objects->remove((Node*) object);
}

bool Map::checkCollisions(BoundingBox* box, Collisionable* object, bool checkEnnemis, bool ignoreNotIdle, bool withAvoid, bool onlyBox, bool checkObjects,
                          int safeX, int safeY, int safeW, int safeH, bool checkDanger) {

    if (box->getX() < bounds.getX() || box->getX() + box->getW() > bounds.getX() + bounds.getW() ||
        box->getY() < bounds.getY() || box->getY() + box->getH() > bounds.getY() + bounds.getH()) {
        return false;
    }

    if (onlyBox) {

        for (int j = box->getY() - (box->getY() % 8); j < box->getY() + box->getH(); j += 8) {
            for (int i = box->getX() - (box->getX() % 8); i < box->getX() + box->getW(); i += 8) {
                Collision c = (Collision)getMur(i, j);
                if (c == GRAND_MUR) {
                    return false;
                }
            }
        }

        return true;
    }

    for (int j = box->getY() - (box->getY() % 8); j < box->getY() + box->getH(); j += 8) {
        for (int i = box->getX() - (box->getX() % 8); i < box->getX() + box->getW(); i += 8) {
            Collision c = (Collision)getMur(i, j);
            if (!object->isCollision(c)
                || (withAvoid && object->isToAvoid(c))) {
                if (c == DANGER && checkDanger) {
                    Link* lk = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink();
                    if ((Collisionable*)lk == object) {
                        Direction dir = N;
                        switch (lk->getDirection()) {
                            case N : dir = S; break;
                            case S : dir = N; break;
                            case W : dir = E; break;
                            case E : dir = W; break;
                        }
                        lk->underAttack(dir, 1, TA_PHYSIC, TE_NORMAL);
                    }
                }
                return false;
            } else {
                if (c == DANGER_BAS && checkDanger) {
                    Link* lk = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink();
                    if ((Collisionable*)lk == object) {
                        Direction dir = N;
                        switch (lk->getDirection()) {
                            case N : dir = S; break;
                            case S : dir = N; break;
                            case W : dir = E; break;
                            case E : dir = W; break;
                        }
                        lk->underAttack(dir, 1, TA_PHYSIC, TE_NORMAL);
                    }
                }
            }
        }
    }

    if (checkEnnemis) {
        List enn;
        ennemis->get(box, &enn);

        enn.iterateOnFirst();
        while (enn.hasNext()) {
            Ennemi* e = (Ennemi*) enn.getNext();
            if (ignoreNotIdle && !e->isIdle()) continue;
            if (e != object && e->getBoundingBox()->intersect(box)) {
                return false;
            }
        }
    }

    if (checkObjects) {
        Link* lk = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink();
        List obj;
        objects->get(box, &obj);
        obj.iterateOnFirst();
        while (obj.hasNext()) {
            Object* o = (Object*) obj.getNext();




            if ((Collisionable*)lk == object) {

                PiegePics* pics = dynamic_cast<PiegePics*>(o);
                if (pics != 0) {
                    Direction dir = N;
                    switch (lk->getDirection()) {
                        case N : dir = S; break;
                        case S : dir = N; break;
                        case W : dir = E; break;
                        case E : dir = W; break;
                    }
                    lk->underAttack(dir, 2, TA_PHYSIC, TE_NORMAL);
                }
            }

            if (o != object && o->getBoundingBox()->intersect(box)) {
                BoundingBox safeBox;
                safeBox.setX(safeX);
                safeBox.setY(safeY);
                safeBox.setW(safeW);
                safeBox.setH(safeH);
                if (!o->getBoundingBox()->intersect(&safeBox)) {
                    return false;
                }
            }
            if (o != object && o->getSecondBoundingBox() != 0 && o->getSecondBoundingBox()->intersect(box)) {
                return false;
            }
        }
    }

    return true;
}

bool Map::testDegat(BoundingBox* box, Direction dir, int force, TypeAttack type, TypeEffect effect, bool onEnnemis) {

    bool result = false;

    // on ennemi :
    if (onEnnemis) {
        List enn;
        ennemis->get(box, &enn);

        enn.iterateOnFirst();
        while (enn.hasNext()) {
            Ennemi* e = (Ennemi*) enn.getNext();
            if (e->getBoundingBox()->intersect(box)) {
                e->underAttack(dir, force, type, effect, box);
                result = true;
            }
        }
    }

    // on objects :

    List obj;
    objects->get(box, &obj);

    obj.iterateOnFirst();
    while (obj.hasNext()) {
        Object* o = (Object*) obj.getNext();
        if (o->isAttackable() && o->getBoundingBox()->intersect(box)) {
            o->underAttack(dir, force, type, effect);
            result = true;
        }
    }

    // on projectiles :

    Link* link = MainController::getInstance()->getGameController()->
            getSceneController()->getScene()->getLink();
    if ((type == TA_SWORD || type == TA_SWORD_HOLD) && link->getEpee() >= 2) {
        List proj;
        projectiles->get(box, &proj);

        proj.iterateOnFirst();
        while (proj.hasNext()) {
            Projectile* p = (Projectile*) proj.getNext();
            if (p->getBoundingBox()->intersect(box)) {
                p->renvoie(dir);
                result = true;
            }
        }
    }

    // on map :

    int x0 = box->getX();
    int beginX = x0 - (x0 % CASE);
    int x1 = box->getX() + box->getW() - 1;
    int endX = x1 - (x1 % CASE);

    int y0 = box->getY();
    int beginY = y0 - (y0 % CASE);
    int y1 = box->getY() + box->getH() - 1;
    int endY = y1 - (y1 % CASE);

    if (beginX < 0) beginX = 0;
    if (beginY < 0) beginY = 0;
    if (endX > getW()) endX = getW();
    if (endY > getH()) endY = getH();

    for (int j = beginY; j <= endY; j += CASE) {
        for (int i = beginX; i <= endX; i += CASE) {

            int x = i / CASE;
            int y = j / CASE;
            int val = sol[x][y];

            if (type == TA_SWORD || effect == TE_FEU || type == TA_SWORD_HOLD) {
                if (val == 185 || val == 187 || val == 189 || val == 553) {
                    // buissons
                    Collision c;
                    TypeDons td;
                    int tb;
                    switch (val) {
                        case 185 : c = HERBE; td = TD_BUISSON_VERT; tb = 0; break;
                        case 187 : c = HERBE; td = TD_BUISSON_ROSE; tb = 1; break;
                        case 189 : c = SABLE; td = TD_BUISSON_OCRE; tb = 2; break;
                        case 553 : c = NEIGE; td = TD_BUISSON_NEIGE; tb = 3; break;
                        default : c = HERBE; td = TD_BUISSON_VERT; tb = 0; break;
                    }

                    sol[x][y] = val + 1;

                    mur[x * 2][y * 2] = c;
                    mur[(x * 2) + 1][y * 2] = c;
                    mur[x * 2][(y * 2) + 1] = c;
                    mur[(x * 2) + 1][(y * 2) + 1] = c;

                    TypeItem t = MapHelper::getInstance()->getItemRandomizer(td)->selectType();
                    if (t != TI_NO_ITEM) {
                        addItem(ItemHelper::getInstance()->createItem(t, i + 8, j + 8));
                    }
                    addEffect(new Feuilles(x * 16 + 8 - 14, y * 16 + 8 - 22 - 8, tb));
                    AudioManager::getInstance()->playSound(TS_BUISSON);

                    result = (type == TA_SWORD || type == TA_SWORD_HOLD);
                } else if (val == 2593) {
                    // rideaux
                    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
                    AudioManager::getInstance()->playSound(TS_SURPRISE);
                    scene->setCoffre(9, 14, 1);
                    ouvrePorte(69, 13, 4);
                }
            }
            if (effect == TE_GLACE) {
                if ((getMur(i, j) == EAU || getMur(i, j) == EAU_PROF)
                       && (getMur(i + 8, j) == EAU || getMur(i + 8, j) == EAU_PROF)
                       && (getMur(i, j + 8) == EAU || getMur(i, j + 8) == EAU_PROF)
                       && (getMur(i + 8, j + 8) == EAU || getMur(i + 8, j + 8) == EAU_PROF)) {

                    sol[x][y] = 359;
                    mur[x * 2][y * 2] = GLACE;
                    mur[(x * 2) + 1][y * 2] = GLACE;
                    mur[x * 2][(y * 2) + 1] = GLACE;
                    mur[(x * 2) + 1][(y * 2) + 1] = GLACE;
                }
                switch (val) {
                    case 67 : sol[x][y] = 73; mur[x * 2][y * 2 + 1] = GLACE; mur[x * 2 + 1][y * 2 + 1] = GLACE; break;
                    case 70 : sol[x][y] = 74; mur[x * 2][y * 2 + 1] = GLACE; mur[x * 2 + 1][y * 2 + 1] = GLACE; break;
                    case 313 : sol[x][y] = 360; break;
                    case 314 : sol[x][y] = 361; mur[x * 2][y * 2 + 1] = GLACE; mur[x * 2 + 1][y * 2 + 1] = GLACE; break;
                    case 315 : sol[x][y] = 362; break;
                    case 316 : sol[x][y] = 363; mur[x * 2 + 1][y * 2] = GLACE; mur[x * 2 + 1][y * 2 + 1] = GLACE; break;
                    case 318 : sol[x][y] = 364; mur[x * 2][y * 2] = GLACE; mur[x * 2][y * 2 + 1] = GLACE; break;
                    case 319 : sol[x][y] = 365; break;
                    case 320 : sol[x][y] = 366; mur[x * 2][y * 2] = GLACE; mur[x * 2 + 1][y * 2] = GLACE; break;
                    case 321 : sol[x][y] = 367; break;
                    case 322 : sol[x][y] = 368; mur[x * 2 + 1][y * 2] = GLACE; mur[x * 2][y * 2 + 1] = GLACE; mur[x * 2 + 1][y * 2 + 1] = GLACE; break;
                    case 323 : sol[x][y] = 369; mur[x * 2][y * 2] = GLACE; mur[x * 2][y * 2 + 1] = GLACE; mur[x * 2 + 1][y * 2 + 1] = GLACE; break;
                    case 324 : sol[x][y] = 370; mur[x * 2][y * 2] = GLACE; mur[x * 2 + 1][y * 2] = GLACE; mur[x * 2 + 1][y * 2 + 1] = GLACE; break;
                    case 325 : sol[x][y] = 371; mur[x * 2][y * 2] = GLACE; mur[x * 2 + 1][y * 2] = GLACE; mur[x * 2][y * 2 + 1] = GLACE; break;
                    case 391 : sol[x][y] = 421; mur[x * 2][y * 2] = GLACE; mur[x * 2 + 1][y * 2] = GLACE; mur[x * 2][y * 2 + 1] = GLACE; break;
                    case 401 : sol[x][y] = 422; mur[x * 2][y * 2] = GLACE; mur[x * 2 + 1][y * 2] = GLACE; mur[x * 2 + 1][y * 2 + 1] = GLACE; break;
                    case 407 : sol[x][y] = 423; mur[x * 2][y * 2] = GLACE; mur[x * 2][y * 2 + 1] = GLACE; mur[x * 2 + 1][y * 2 + 1] = GLACE; break;
                    case 415 : sol[x][y] = 424; mur[x * 2 + 1][y * 2] = GLACE; mur[x * 2][y * 2 + 1] = GLACE; mur[x * 2 + 1][y * 2 + 1] = GLACE; break;
                    case 1415 : sol[x][y] = 1414; break; // torche
                    default : break;
                }
                if (val == 1415) eteintTorche(x, y);
            }
            if (type == TA_EXPLO) {
                if (val == 173 || val == 174) { // plaine
                    // fissure
                    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
                    AudioManager::getInstance()->playSound(TS_SURPRISE);
                    scene->setCoffre(0, 0, 1);
                    ouvrePorte(50, 1, 0);
                } else if (val == 476 || val == 477) { // eau
                    // fissure
                    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
                    AudioManager::getInstance()->playSound(TS_SURPRISE);
                    scene->setCoffre(0, 1, 1);
                    ouvrePorte(121, 10, 0);
                } else if (val == 480 || val == 481) { // eau prof
                    // fissure
                    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
                    AudioManager::getInstance()->playSound(TS_SURPRISE);
                    scene->setCoffre(0, 2, 1);
                    ouvrePorte(49, 36, 1);
                } else if (val == 928 || val == 929) { // sable
                    // fissure
                    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
                    AudioManager::getInstance()->playSound(TS_SURPRISE);
                    scene->setCoffre(0, 3, 1);
                    ouvrePorte(132, 24, 0);
                } else if (val == 1134 || val == 1135) { // terre
                    // fissure
                    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
                    AudioManager::getInstance()->playSound(TS_SURPRISE);
                    scene->setCoffre(0, 4, 1);
                    ouvrePorte(27, 7, 0);
                } else if (val == 1204 || val == 1205) { // herbe ocre
                    // fissure
                    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
                    AudioManager::getInstance()->playSound(TS_SURPRISE);
                    scene->setCoffre(0, 6, 1);
                    ouvrePorte(155, 3, 0);
                } else if (map > 11 && map < 21) {
                    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
                    // donjon
                    switch (map) {
                        case 12 :
                            if (val == 1332 || val == 1333 || val == 1334 || val == 1335) {
                                AudioManager::getInstance()->playSound(TS_SURPRISE);
                                scene->setCoffre(map - 11, 10, 1);
                                ouvrePorte(9, 58, 2);
                            } else if (val == 1341 || val == 1346) {
                                AudioManager::getInstance()->playSound(TS_SURPRISE);
                                scene->setCoffre(map - 11, 11, 1);
                                ouvrePorte(18, 66, 3);
                            }
                            break;
                        case 14 :
                            if (val == 1712 || val == 1717) {
                                AudioManager::getInstance()->playSound(TS_SURPRISE);
                                if (x < 149) {
                                    scene->setCoffre(map - 11, 18, 1);
                                    ouvrePorte(138, 25, 3);
                                } else {
                                    scene->setCoffre(map - 11, 19, 1);
                                    ouvrePorte(158, 25, 3);
                                }
                            }
                            break;
                        case 18 :
                            if (val == 2290) {
                                AudioManager::getInstance()->playSound(TS_SURPRISE);
                                scene->setCoffre(map - 11, 11, 1);
                                ouvrePorte(169, 37, 2);
                            }
                            break;
                        case 20 :
                            if (val == 2698 || val == 2703) {
                                AudioManager::getInstance()->playSound(TS_SURPRISE);
                                scene->setCoffre(map - 11, 13, 1);
                                ouvrePorte(218, 18, 3);
                            }
                            break;
                    }
                }
            }
            if (type == TA_MARTEAU) {
                if (val == 311) {
                    AudioManager::getInstance()->playSound(TS_PLOT);
                    setSol(x * 16, y * 16, 1, 1, 312, HERBE);
                } else if (val == 705) {
                    AudioManager::getInstance()->playSound(TS_PLOT);
                    setSol(x * 16, y * 16, 1, 1, 706, SABLE);
                } else if (val == 905) {
                    AudioManager::getInstance()->playSound(TS_PLOT);
                    setSol(x * 16, y * 16, 1, 1, 906, HERBE);
                } else if (val == 1156 || val == 1157 || val == 1158) {
                    if (map == 9) {
                        Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
                        addEffect(new Debris(38 * 16 + 8, 39 * 16 + 8, N, 2));
                        addEffect(new Debris(39 * 16 + 8, 38 * 16 + 8, N, 2));
                        addEffect(new Debris(40 * 16 + 8, 39 * 16 + 8, N, 2));
                        AudioManager::getInstance()->playSound(TS_BREAK);
                        AudioManager::getInstance()->playSound(TS_SURPRISE);
                        scene->setCoffre(0, 5, 1);
                        ouvrePorte(38, 38, 1);
                    }
                } else if (val == 2029) {
                    AudioManager::getInstance()->playSound(TS_PLOT);
                    setSol(x * 16, y * 16, 1, 1, 2030, PIERRE);
                }
            }
            if (effect == TE_FEU) {
                if (val == 1414) {
                    sol[x][y] = 1415;
                    allumeTorche(x, y);
                }
            }


        }
    }

    return result;
}

void Map::pickUpItems(BoundingBox* box) {

    List toPickUp;
    items->get(box, &toPickUp);

    toPickUp.iterateOnFirst();
    while (toPickUp.hasNext()) {
        Item* i = (Item*) toPickUp.getNext();
        if (i->getBoundingBox()->intersect(box) && i->isAlive()) {
            i->action();
        }
    }
}

Item* Map::getItem(BoundingBox* box) {
    List toPickUp;
    items->get(box, &toPickUp);

    toPickUp.iterateOnFirst();
    while (toPickUp.hasNext()) {
        Item* i = (Item*) toPickUp.getNext();
        if (i->getBoundingBox()->intersect(box) && i->isReady() && i->isAlive() && i->isPickable()) {
            return i;
        }
    }
    return 0;
}

void Map::killItems(BoundingBox* box) {
    List toPickUp;
    items->get(box, &toPickUp);

    toPickUp.iterateOnFirst();
    while (toPickUp.hasNext()) {
        Item* i = (Item*) toPickUp.getNext();
        if (i->getBoundingBox()->intersect(box) && i->isAlive()) {
            i->killNode();
        }
    }
}

void Map::killEnnemis(BoundingBox* box) {
    List toKill;
    ennemis->get(box, &toKill);

    toKill.iterateOnFirst();
    while (toKill.hasNext()) {
        Ennemi* e = (Ennemi*) toKill.getNext();
        if (e->getBoundingBox()->intersect(box) && e->isAlive()) {
            e->killNode();
        }
    }
}

Portable* Map::pickUpObject(BoundingBox* box) {

    List toPickUp;
    objects->get(box, &toPickUp);

    toPickUp.iterateOnFirst();
    while (toPickUp.hasNext()) {
        Portable* p = dynamic_cast<Portable*>(toPickUp.getNext());
        if (p != 0 && p->isCarriable() && p->getHandableBox()->intersect(box)) {
            return p;
        }
    }

    return 0;
}

void Map::pushObject(BoundingBox* box, Direction dir) {
    List toPush;
    objects->get(box, &toPush);

    toPush.iterateOnFirst();
    while (toPush.hasNext()) {
        Poussable* p = dynamic_cast<Poussable*>(toPush.getNext());
        if (p != 0) {
            p->pousse(dir);
            return;
        }
    }
}

bool Map::tryToTalk(BoundingBox* box, Direction dir) {
    List toTalk;

    // try to interact with objects or npcs
    objects->get(box, &toTalk);

    toTalk.iterateOnFirst();
    while (toTalk.hasNext()) {
        Object* p = dynamic_cast<Object*>(toTalk.getNext());
        if (p != 0 && p->action(dir)) {
            return true;
        }
    }
    return false;
}

bool Map::testTransition(int x, int y) {
    if (map > 11) return false;
    return ((x <= 8 && map != 5 && map != 7 && map != 9 && map != 10) ||
            (y <= 0 && map != 1 && map != 6 && map != 7 && map != 11) ||
            (x >= w - 24 && map != 1 && map != 8 && map != 11) ||
            (y >= h - 32 && map != 8 && map != 10 && map != 11));
}

bool Map::testInnerTransition(int x, int y) {
    if (map < 12) return false;

    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Link* link = scene->getLink();

    if (map == 20 && scene->getAvancement() < AV_ZELDA_SUIT
        && bounds.getX() == 320 * 10 && bounds.getY() == 240
        && x >= bounds.getX() + bounds.getW() - 24 && bounds.getX() + bounds.getW() < w) {
        MainController::getInstance()->getGameController()->displayText(231);
        link->setX(link->getX() - 4);
        link->setDirection(W);
        return false;
    }

    if (map == 20 && scene->getAvancement() == AV_ZELDA_SUIT && (
            (x <= bounds.getX() + 8 && bounds.getX() > 0) ||
            (y <= bounds.getY() && bounds.getY() > 0) ||
            (x >= bounds.getX() + bounds.getW() - 24 && bounds.getX() + bounds.getW() < w) ||
            (y >= bounds.getY() + bounds.getH() - 32 && bounds.getY() + bounds.getH() < h))) {

        List list;
        objects->get(&bounds, &list);

        list.iterateOnFirst();
        while (list.hasNext()) {
            Pnj* zelda = dynamic_cast<Pnj*>(list.getNext());
            if (zelda != 0) {
                int dstX = link->getX() + 8;
                int dstY = link->getY() + 24;
                int dist = abs(zelda->getX() + 8 - dstX) + abs(zelda->getY() + 23 - dstY);
                if (dist > 100) {
                    MainController::getInstance()->getGameController()->displayText(230);

                    if (x <= bounds.getX() + 8 && bounds.getX() > 0) {
                        link->setX(link->getX() + 4);
                        link->setDirection(E);
                    } else if (y <= bounds.getY() && bounds.getY() > 0) {
                        link->setY(link->getY() + 4);
                        link->setDirection(S);
                    } else if (x >= bounds.getX() + bounds.getW() - 24 && bounds.getX() + bounds.getW() < w) {
                        link->setX(link->getX() - 4);
                        link->setDirection(W);
                    } else if (y >= bounds.getY() + bounds.getH() - 32 && bounds.getY() + bounds.getH() < h) {
                        link->setY(link->getY() - 4);
                        link->setDirection(N);
                    }

                    return false;
                }
            }
        }
    }

    return ((x <= bounds.getX() + 8 && bounds.getX() > 0) ||
            (y <= bounds.getY() && bounds.getY() > 0) ||
            (x >= bounds.getX() + bounds.getW() - 24 && bounds.getX() + bounds.getW() < w) ||
            (y >= bounds.getY() + bounds.getH() - 32 && bounds.getY() + bounds.getH() < h));
}

bool Map::testTeleport(int x, int y) {
    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Link* link = scene->getLink();

    switch (map) {
        case 1 :
            if (x == 46 * 16 + 8 && y == 22 * 16 + 8) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(12, 39 * 16 + 8, 72 * 16, N, false, true);
                return true;
            }
            if (x == 29 * 16 + 8 && y == 21 * 16 + 8) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(12, 9 * 16 + 8, 72 * 16, N, false, true);
                return true;
            }
            if (x == 49 * 16 + 8 && y == 7 * 16 + 8) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(16, 9 * 16 + 8, 12 * 16, N, false, true);
                return true;
            }
            if (x == 50 * 16 + 8 && y == 1 * 16 + 8) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(24, 9 * 16 + 8, 12 * 16, N, false, true);
                return true;
            }
            if (x == 29 * 16 + 8 && y == 36 * 16 + 8) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(27, 9 * 16 + 8, 12 * 16, N, false, true);
                return true;
            }
            break;
        case 2 :
            if (x == 65 * 16 + 8 && y == 39 * 16 + 8) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(28, 9 * 16 + 8, 12 * 16, N, false, true);
                return true;
            }
            break;
        case 3 :
            if (x == 93 * 16 + 8 && y == 36 * 16 + 8) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(13, 69 * 16 + 8, 87 * 16, N, false, true);
                return true;
            }
            if (x == 27 * 16 + 8 && y == 35 * 16) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(18, 49 * 16 + 8, 72 * 16, N, false, true);
                return true;
            }
            if (x == 121 * 16 + 8 && y == 10 * 16 + 8) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(21, 49 * 16 + 8, 57 * 16, N, false, true);
                return true;
            }
            if (x == 106 * 16 + 8 && y == 41 * 16 + 8) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(21, 29 * 16 + 8, 57 * 16, N, false, true);
                return true;
            }
            if (x == 49 * 16 + 8 && y == 36 * 16 + 8) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(25, 9 * 16 + 8, 12 * 16, N, false, true);
                return true;
            }
            break;
        case 4 :
            if (x == 16 * 16 + 8 && y == 15 * 16 + 8) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(29, 9 * 16 + 8, 12 * 16, N, false, true);
                return true;
            }
            if (x == 20 * 16 + 8 && y == 15 * 16 + 8) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(29, 29 * 16 + 8, 12 * 16, N, false, true);
                return true;
            }
            if (x == 35 * 16 + 8 && y == 15 * 16 + 8) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(30, 9 * 16 + 8, 12 * 16, N, false, true);
                return true;
            }
            if (x == 20 * 16 + 8 && y == 27 * 16 + 8) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(31, 9 * 16 + 8, 12 * 16, N, false, true);
                return true;
            }
            if (x == 35 * 16 + 8 && y == 27 * 16 + 8) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(32, 9 * 16 + 8, 12 * 16, N, false, true);
                return true;
            }
            if (x == 20 * 16 + 8 && y == 33 * 16 + 8) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(33, 9 * 16 + 8, 1 * 16, S, false, true);
                return true;
            }
            if (x == 20 * 16 + 8 && y == 40 * 16 + 8) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(33, 9 * 16 + 8, 27 * 16, N, false, true);
                return true;
            }
            if (x == 35 * 16 + 8 && y == 37 * 16 + 8) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(34, 9 * 16 + 8, 12 * 16, N, false, true);
                return true;
            }
            break;
        case 5 :
            if (link->getInventory()->nbCristaux() < NB_CRISTAUX && y >= 33 * 16 && y <= 34 * 16 - 8 && x >= 48 * 16 && x <= 55 * 16) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(5, link->getStartX(), link->getStartY(), link->getStartDir(), false, true);
                AudioManager::getInstance()->playSound(TS_TELEPORT);
                return true;
            }
            if (x >= 51 * 16 && x <= 52 * 16 && y == 26 * 16 + 8) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(20, 69 * 16 + 8, 57 * 16, N, false, true);
                return true;
            }
            if (x >= 51 * 16 && x <= 52 * 16 && y == 21 * 16 + 8) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(20, 9 * 16 + 8, 27 * 16, N, false, true);
                return true;
            }
            if (x == 65 * 16 + 8 && y == 18 * 16) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(20, 109 * 16 + 8, 7 * 16 + 8, S, false, true);
                AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
                return true;
            }
            break;
        case 6 :
            if (x == 28 * 16 && y == 2 * 16 + 8) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(14, 69 * 16 + 8, 72 * 16, N, false, true);
                return true;
            }
            if (x == 41 * 16 + 8 && y == 3 * 16 + 8) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(14, 89 * 16 + 8, 72 * 16, N, false, true);
                AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
                return true;
            }
            break;
        case 7 :
            if (x >= 14 * 16 && x <= 15 * 16 && y == 17 * 16 + 8) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(15, 49 * 16 + 8, 72 * 16, N, false, true);
                return true;
            }
            if (x == 132 * 16 + 8 && y == 24 * 16 + 8) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(23, 9 * 16 + 8, 12 * 16, N, false, true);
                return true;
            }
            if (x == 104 * 16 + 8 && y == 13 * 16 + 8) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(35, 9 * 16 + 8, 12 * 16, N, false, true);
                return true;
            }
            if (x == 113 * 16 + 8 && y == 13 * 16 + 8) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(36, 9 * 16 + 8, 12 * 16, N, false, true);
                return true;
            }
            if (x == 122 * 16 + 8 && y == 13 * 16 + 8) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(37, 9 * 16 + 8, 12 * 16, N, false, true);
                return true;
            }
            if (x == 104 * 16 + 8 && y == 23 * 16 + 8) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(38, 9 * 16 + 8, 12 * 16, N, false, true);
                return true;
            }
            if (x == 122 * 16 + 8 && y == 23 * 16 + 8) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(39, 9 * 16 + 8, 12 * 16, N, false, true);
                return true;
            }
            break;
        case 8 :
            if (x == 48 * 16 + 8 && y == 9 * 16 + 8) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(16, 9 * 16 + 8, 87 * 16, N, false, true);
                return true;
            }
            if (x == 8 * 16 + 8 && y == 30 * 16 + 8) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(22, 9 * 16 + 8, 12 * 16, N, false, true);
                return true;
            }
            if (x == 18 * 16 + 8 && y == 50 * 16 + 8) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(40, 9 * 16 + 8, 12 * 16, N, false, true);
                return true;
            }
            if (x == 43 * 16 + 8 && y == 39 * 16 + 8) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(41, 9 * 16 + 8, 12 * 16, N, false, true);
                return true;
            }
            if (x == 30 * 16 + 8 && y == 50 * 16 + 8) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(42, 9 * 16 + 8, 12 * 16, N, false, true);
                return true;
            }
            if (x == 14 * 16 + 8 && y == 63 * 16) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(43, 9 * 16 + 8, 12 * 16, N, false, true);
                return true;
            }
            if (x == 43 * 16 + 8 && y == 61 * 16 + 8) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(44, 9 * 16 + 8, 12 * 16, N, false, true);
                return true;
            }
            break;
        case 9 :
            if (x == 39 * 16 && y == 38 * 16) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(17, 69 * 16 + 8, 147 * 16, N, false, true);
                return true;
            }
            if (x == 38 * 16 + 8 && y == 33 * 16 + 8) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(17, 149 * 16 + 8, 117 * 16, N, false, true);
                return true;
            }
            if (x == 27 * 16 + 8 && y == 7 * 16 + 8) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(26, 9 * 16 + 8, 12 * 16, N, false, true);
                return true;
            }
            break;
        case 11 :
            if (x == 143 * 16 && y == 3 * 16 + 8) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(19, 29 * 16 + 8, 147 * 16, N, false, true);
                return true;
            }
            if (x == 155 * 16 + 8 && y == 3 * 16 + 8) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(22, 69 * 16 + 8, 72 * 16, N, false, true);
                return true;
            }
            break;
        case 12 :
            if (y >= h - 32 && x >= 320) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(1, 46 * 16 + 8, 23 * 16 + 8, S, false, true);
                return true;
            }
            if (y >= h - 32 && x < 320) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(1, 29 * 16 + 8, 22 * 16 + 8, S, false, true);
                return true;
            }
            // escaliers
            if ((x == 9 * 16 + 8 && y == 36 * 16)
                || (x == 39 * 16 + 8 && y == 29 * 16)
                || (x == 69 * 16 + 8 && y == 36 * 16)) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(12, x + 80 * 16, y + 24, S, false, false, true);
                AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
                return true;
            }
            if ((x == 89 * 16 + 8 && y == 36 * 16)
                || (x == 119 * 16 + 8 && y == 29 * 16)
                || (x == 149 * 16 + 8 && y == 36 * 16)) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(12, x - 80 * 16, y - 24, N, false, false, true);
                AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
                return true;
            }
            break;
        case 13 :
            if (y >= h - 32 - 240 && x >= 320*3 && x <= 320*4) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(3, 93 * 16 + 8, 37 * 16 + 8, S, false, true);
                return true;
            }
            break;
        case 14 :
            if (y >= h - 32 && x < 320*4) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(6, 28 * 16, 3 * 16 + 8, S, false, true);
                return true;
            }
            if (y >= h - 32 && x >= 320*4) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(6, 41 * 16 + 8, 4 * 16 + 8, S, false, true);
                return true;
            }
            // escaliers
            if ((x == 109 * 16 + 8 && y == 6 * 16)
                || (x == 109 * 16 + 8 && y == 66 * 16)
                || (x == 149 * 16 + 8 && y == 36 * 16)
                || (x == 189 * 16 + 8 && y == 6 * 16)
                || (x == 189 * 16 + 8 && y == 66 * 16)) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(14, x - 100 * 16, y + 24, S, false, false, true);
                AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
                return true;
            }
            if ((x == 9 * 16 + 8 && y == 6 * 16)
                || (x == 9 * 16 + 8 && y == 66 * 16)
                || (x == 49 * 16 + 8 && y == 36 * 16)
                || (x == 89 * 16 + 8 && y == 6 * 16)
                || (x == 89 * 16 + 8 && y == 66 * 16)) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(14, x + 100 * 16, y - 24, N, false, false, true);
                AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
                return true;
            }
            break;
        case 15 :
            if (y >= h - 32) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(7, 14 * 16 + 8, 18 * 16 + 8, S, false, true);
                return true;
            }
            // escaliers
            if (x == 149 * 16 + 8 && y == 36 * 16) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(15, x - 80 * 16, y + 24 + 15 * 16, S, false, false, true);
                AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
                return true;
            }
            if (x == 169 * 16 + 8 && y == 6 * 16) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(15, x - 40 * 16, y + 24 + 15 * 16, S, false, false, true);
                AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
                return true;
            }
            if (x == 69 * 16 + 8 && y == 51 * 16) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(15, x + 80 * 16, y - 24 - 15 * 16, N, false, false, true);
                AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
                return true;
            }
            if (x == 129 * 16 + 8 && y == 21 * 16) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(15, x + 40 * 16, y - 24 - 15 * 16, N, false, false, true);
                AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
                return true;
            }
            break;
        case 16 :
            if (y >= 240 - 32 && y < 240 && x < 320) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(1, 49 * 16 + 8, 8 * 16 + 8, S, false, true);
                return true;
            }
            if (y >= h - 32) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(8, 48 * 16 + 8, 10 * 16 + 8, S, false, true);
                return true;
            }
            // escaliers
            if ((x == 9 * 16 + 8 && y == 6 * 16)
                || (x == 9 * 16 + 8 && y == 81 * 16)) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(16, x + 20 * 16, y + 24, S, false, false, true);
                AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
                return true;
            }
            if ((x == 29 * 16 + 8 && y == 21 * 16)
                || (x == 49 * 16 + 8 && y == 81 * 16)) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(16, x + 80 * 16, y + 24, S, false, false, true);
                AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
                return true;
            }
            if ((x == 29 * 16 + 8 && y == 6 * 16)
                || (x == 29 * 16 + 8 && y == 81 * 16)) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(16, x - 20 * 16, y - 24, N, false, false, true);
                AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
                return true;
            }
            if ((x == 109 * 16 + 8 && y == 21 * 16)
                || (x == 129 * 16 + 8 && y == 81 * 16)) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(16, x - 80 * 16, y - 24, N, false, false, true);
                AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
                return true;
            }
            break;
        case 17 :
            if (y >= 240 * 8 - 32 && x > 320 * 7) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(9, 38 * 16 + 8, 34 * 16 + 8, S, false, true);
                return true;
            }
            if (y >= h - 32) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(9, 39 * 16, 39 * 16 + 8, S, false, true);
                return true;
            }
            // escaliers
            if (x == 149 * 16 + 8 && y == 111 * 16) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(17, x - 80 * 16, y + 24, S, false, false, true);
                AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
                return true;
            }
            if (x == 69 * 16 + 8 && y == 111 * 16) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(17, x + 80 * 16, y - 24, N, false, false, true);
                AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
                return true;
            }
            break;
        case 18 :
            if (y >= h - 32) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(3, 27 * 16 + 8, 36 * 16, S, false, true);
                return true;
            }
            // escaliers
            if ((x == 129 * 16 + 8 && y == 21 * 16)
                || (x == 149 * 16 + 8 && y == 36 * 16)
                || (x == 169 * 16 + 8 && y == 21 * 16)
                || (x == 189 * 16 + 8 && y == 66 * 16)) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(18, x - 100 * 16, y + 24, S, false, false, true);
                AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
                return true;
            }
            if ((x == 29 * 16 + 8 && y == 21 * 16)
                || (x == 49 * 16 + 8 && y == 36 * 16)
                || (x == 69 * 16 + 8 && y == 21 * 16)
                || (x == 89 * 16 + 8 && y == 66 * 16)) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(18, x + 100 * 16, y - 24, N, false, false, true);
                AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
                return true;
            }
            break;
        case 19 :
            if (y >= h - 32) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(11, 143 * 16, 4 * 16, S, false, true);
                return true;
            }
            break;
        case 20 :
            if (y >= 240 * 2 - 32 && x < 320) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(5, 51 * 16 + 8, 23 * 16 - 8, S, false, true);
                return true;
            }
            if (y >= 240 * 4 - 32 && x > 320*3 && x < 320*4) {
                if (scene->getAvancement() == AV_ZELDA_SUIT) {
                    link->setY(link->getY() - 4);
                    link->setDirection(N);
                    MainController::getInstance()->getGameController()->displayText(229);
                    return false;
                }
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(5, 51 * 16 + 8, 27 * 16 + 8, S, false, true);
                return true;
            }

            if (x == 109 * 16 + 8 && y == 6 * 16) {
                if (scene->getAvancement() < AV_ZELDA_ARRIVEE) {
                    if (scene->getAvancement() < AV_ZELDA_SUIT) {
                        link->setY(link->getY() + 2);
                        link->setDirection(S);
                        MainController::getInstance()->getGameController()->displayText(232);
                        return false;
                    } else {
                        List list;
                        objects->get(&bounds, &list);

                        list.iterateOnFirst();
                        while (list.hasNext()) {
                            Pnj* zelda = dynamic_cast<Pnj*>(list.getNext());
                            if (zelda != 0) {
                                int dstX = link->getX() + 8;
                                int dstY = link->getY() + 24;
                                int dist = abs(zelda->getX() + 8 - dstX) + abs(zelda->getY() + 23 - dstY);
                                if (dist > 100) {
                                    link->setY(link->getY() + 2);
                                    link->setDirection(S);
                                    MainController::getInstance()->getGameController()->displayText(230);
                                    return false;
                                }
                            }
                        }
                    }
                }
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(5, 65 * 16 + 8, 17 * 16 - 8, N, false, true);
                AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
                return true;
            }
            // escaliers
            if (x == 89 * 16 + 8 && y == 96 * 16) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(20, x + 60 * 16, y + 24, S, false, false, true);
                AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
                return true;
            }
            if (x == 129 * 16 + 8 && y == 96 * 16) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(20, x + 80 * 16, y + 24, S, false, false, true);
                AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
                return true;
            }
            if (x == 149 * 16 + 8 && y == 96 * 16) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(20, x - 60 * 16, y - 24, N, false, false, true);
                AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
                return true;
            }
            if (x == 209 * 16 + 8 && y == 96 * 16) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(20, x - 80 * 16, y - 24, N, false, false, true);
                AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
                return true;
            }
            break;
        case 21 :
            if (y >= h - 32 && x < 320 * 2) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(3, 106 * 16 + 8, 42 * 16 + 8, S, false, true);
                return true;
            }
            if (y >= h - 32 && x > 320 * 2) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(3, 121 * 16 + 8, 11 * 16 + 8, S, false, true);
                return true;
            }
            // escaliers
            if (x == 29 * 16 + 8 && y == 51 * 16) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(21, x - 20 * 16, y + 24, S, false, false, true);
                AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
                return true;
            }
            if (x == 49 * 16 + 8 && y == 51 * 16) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(21, x, y + 24 - 45 * 16, S, false, false, true);
                AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
                return true;
            }
            if (x == 9 * 16 + 8 && y == 51 * 16) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(21, x + 20 * 16, y - 24, N, false, false, true);
                AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
                return true;
            }
            if (x == 49 * 16 + 8 && y == 6 * 16) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(21, x, y - 24 + 45 * 16, N, false, false, true);
                AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
                return true;
            }
            break;
        case 22 :
            if (y >= 240 - 32 && y < 240 * 2 && x < 320) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(8, 8 * 16 + 8, 31 * 16 + 8, S, false, true);
                return true;
            }
            if (y >= h - 32 && x > 320 * 3) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(11, 155 * 16 + 8, 4 * 16 + 8, S, false, true);
                return true;
            }
            // escaliers
            if (x == 9 * 16 + 8 && y == 6 * 16) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(22, x + 20 * 16, y + 24 + 45 * 16, S, false, false, true);
                AudioManager::getInstance()->playSound(TS_ESCALIERS_DOWN);
                return true;
            }
            if (x == 29 * 16 + 8 && y == 51 * 16) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(22, x - 20 * 16, y - 24 - 45 * 16, N, false, false, true);
                AudioManager::getInstance()->playSound(TS_ESCALIERS_UP);
                return true;
            }
            break;
        case 23 :
            if (y >= h - 32) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(7, 132 * 16 + 8, 25 * 16 + 8, S, false, true);
                return true;
            }
            break;
        case 24 :
            if (y >= h - 32) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(1, 50 * 16 + 8, 2 * 16 + 8, S, false, true);
                return true;
            }
            break;
        case 25 :
            if (y >= h - 32) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(3, 49 * 16 + 8, 37 * 16 + 8, S, false, true);
                return true;
            }
            break;
        case 26 :
            if (y >= h - 32) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(9, 27 * 16 + 8, 8 * 16 + 8, S, false, true);
                return true;
            }
            break;
        case 27 :
            if (y >= h - 32) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(1, 29 * 16 + 8, 37 * 16 + 8, S, false, true);
                return true;
            }
            break;
        case 28 :
            if (y >= h - 32) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(2, 65 * 16 + 8, 40 * 16 + 8, S, false, true);
                return true;
            }
            break;
        case 29 :
            if (y >= h - 32 && x < 320) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(4, 16 * 16 + 8, 16 * 16 + 8, S, false, true);
                return true;
            }
            if (y >= h - 32 && x >= 320) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(4, 20 * 16 + 8, 16 * 16 + 8, S, false, true);
                return true;
            }
            break;
        case 30 :
            if (y >= h - 32) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(4, 35 * 16 + 8, 16 * 16 + 8, S, false, true);
                return true;
            }
            break;
        case 31 :
            if (y >= h - 32) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(4, 20 * 16 + 8, 28 * 16 + 8, S, false, true);
                return true;
            }
            break;
        case 32 :
            if (y >= h - 32) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(4, 35 * 16 + 8, 28 * 16 + 8, S, false, true);
                return true;
            }
            break;
        case 33 :
            if (y <= 0) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(4, 20 * 16 + 8, 32 * 16 + 8, N, false, true);
                return true;
            }
            if (y >= h - 32) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(4, 20 * 16 + 8, 41 * 16 + 8, S, false, true);
                return true;
            }
            break;
        case 34 :
            if (y >= h - 32) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(4, 35 * 16 + 8, 38 * 16 + 8, S, false, true);
                return true;
            }
            break;
        case 35 :
            if (y >= h - 32) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(7, 104 * 16 + 8, 14 * 16 + 8, S, false, true);
                return true;
            }
            break;
        case 36 :
            if (y >= h - 32) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(7, 113 * 16 + 8, 14 * 16 + 8, S, false, true);
                return true;
            }
            break;
        case 37 :
            if (y >= h - 32) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(7, 122 * 16 + 8, 14 * 16 + 8, S, false, true);
                return true;
            }
            break;
        case 38 :
            if (y >= h - 32) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(7, 104 * 16 + 8, 24 * 16 + 8, S, false, true);
                return true;
            }
            break;
        case 39 :
            if (y >= h - 32) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(7, 122 * 16 + 8, 24 * 16 + 8, S, false, true);
                return true;
            }
            break;
        case 40 :
            if (y >= h - 32) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(8, 18 * 16 + 8, 51 * 16 + 8, S, false, true);
                return true;
            }
            break;
        case 41 :
            if (y >= h - 32) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(8, 43 * 16 + 8, 40 * 16 + 8, S, false, true);
                return true;
            }
            break;
        case 42 :
            if (y >= h - 32) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(8, 30 * 16 + 8, 51 * 16 + 8, S, false, true);
                return true;
            }
            break;
        case 43 :
            if (y >= h - 32) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(8, 14 * 16 + 8, 64 * 16 + 8, S, false, true);
                return true;
            }
            break;
        case 44 :
            if (y >= h - 32) {
                MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(8, 43 * 16 + 8, 62 * 16 + 8, S, false, true);
                return true;
            }
            break;
        default : return false;
    }
    return false;
}

void Map::testAnim(int x, int y, Direction dir) {

    // open door
    if ((getSol(x, y + 8 - 1) == 468 || getSol(x, y + 8 - 1) == 789 || getSol(x, y + 8 - 1) == 790) && dir == N) {
        ouvrePorteMaison(x, y);
        AudioManager::getInstance()->playSound(TS_DOOR);
    }


    if (map >= 12 && map < 21) {
        Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();

        // doors with keys
        if (scene->getCoffre(map - 11, 3)) {
            int i = 0;
            int j = 0;

            switch (map) {
                case 12 :
                    if (getSol(x, y + 7) == 1288 && dir == N) { i = x/16; j = ((y + 7)/16) - 3;}
                    if (getSol(x, y + 24) == 1292 && dir == S) { i = x/16; j = (y + 24)/16;}
                    if (getSol(x - 1, y + 16) == 1301 && dir == W) { i = ((x-1)/16) - 3; j = y/16;}
                    if (getSol(x + 16, y + 16) == 1307 && dir == E) { i = (x+16)/16; j = y/16;}
                    break;
                case 13 :
                    if (getSol(x, y + 7) == 1538 && dir == N) { i = x/16; j = ((y + 7)/16) - 3;}
                    if (getSol(x, y + 24) == 1542 && dir == S) { i = x/16; j = (y + 24)/16;}
                    if (getSol(x - 1, y + 16) == 1551 && dir == W) { i = ((x-1)/16) - 3; j = y/16;}
                    if (getSol(x + 16, y + 16) == 1557 && dir == E) { i = (x+16)/16; j = y/16;}
                    break;
                case 14 :
                    if (getSol(x, y + 7) == 1658 && dir == N) { i = x/16; j = ((y + 7)/16) - 3;}
                    if (getSol(x, y + 24) == 1660 && dir == S) { i = x/16; j = (y + 24)/16;}
                    if (getSol(x - 1, y + 16) == 1667 && dir == W) { i = ((x-1)/16) - 3; j = y/16;}
                    if (getSol(x + 16, y + 16) == 1672 && dir == E) { i = (x+16)/16; j = y/16;}
                    break;
                case 15 :
                    if (getSol(x, y + 7) == 1822 && dir == N) { i = x/16; j = ((y + 7)/16) - 3;}
                    if (getSol(x, y + 24) == 1824 && dir == S) { i = x/16; j = (y + 24)/16;}
                    if (getSol(x - 1, y + 16) == 1831 && dir == W) { i = ((x-1)/16) - 3; j = y/16;}
                    if (getSol(x + 16, y + 16) == 1836 && dir == E) { i = (x+16)/16; j = y/16;}
                    break;
                case 16 :
                    if (getSol(x - 1, y + 16) == 1968 && dir == W) { i = ((x-1)/16) - 3; j = y/16;}
                    if (getSol(x + 16, y + 16) == 1974 && dir == E) { i = (x+16)/16; j = y/16;}
                    break;
                case 17 :
                    if (getSol(x - 1, y + 16) == 2107 && dir == W) { i = ((x-1)/16) - 3; j = y/16;}
                    if (getSol(x + 16, y + 16) == 2112 && dir == E) { i = (x+16)/16; j = y/16;}
                    break;
                case 18:
                    if (getSol(x, y + 7) == 2240 && dir == N) { i = x/16; j = ((y + 7)/16) - 3;}
                    if (getSol(x, y + 24) == 2242 && dir == S) { i = x/16; j = (y + 24)/16;}
                    break;
                case 19 :
                    if (getSol(x, y + 7) == 2369 && dir == N) { i = x/16; j = ((y + 7)/16) - 3;}
                    if (getSol(x, y + 24) == 2369 && dir == S) { i = x/16; j = (y + 24)/16;}
                    if (getSol(x - 1, y + 16) == 2378 && dir == W) { i = ((x-1)/16) - 3; j = y/16;}
                    if (getSol(x + 16, y + 16) == 2383 && dir == E) { i = (x+16)/16; j = y/16;}
                    break;
                case 20 :
                    if (getSol(x, y + 7) == 2542 && dir == N) { i = x/16; j = ((y + 7)/16) - 3;}
                    if (getSol(x, y + 24) == 2544 && dir == S) { i = x/16; j = (y + 24)/16;}
                    if (getSol(x - 1, y + 16) == 2551 && dir == W) { i = ((x-1)/16) - 3; j = y/16;}
                    if (getSol(x + 16, y + 16) == 2556 && dir == E) { i = (x+16)/16; j = y/16;}
                    if (getSol(x - 1, y + 16) == 2666 && dir == W) { i = ((x-1)/16) - 3; j = y/16;}
                    if (getSol(x + 16, y + 16) == 2671 && dir == E) { i = (x+16)/16; j = y/16;}
                    if (getSol(x, y + 7) == 2738 && dir == N) { i = 210; j = 24;}
                    break;
            }

            if (i != 0) {
                int k = 0;
                switch (map) {
                    case 12 :
                        if (bounds.getY() == 240*4) k = 7;
                        else if (bounds.getY() == 240 && scene->getLink()->getY() < 240*2) k = 8;
                        else k = 9;
                        break;
                    case 13 :
                        if (bounds.getX() == 320 && bounds.getY() >= 240*4) k = 9;
                        else if (bounds.getY() == 240 && scene->getLink()->getX() < 320*3) k = 10;
                        else if (bounds.getX() == 320*2 && bounds.getY() >= 240*3 && scene->getLink()->getX() < 320*2+240) k = 11;
                        else if (bounds.getY() == 240*5 && scene->getLink()->getX() >= 320*2+240) k = 12;
                        else k = 13;
                        break;
                    case 14 :
                        if (bounds.getX() == 0 && bounds.getY() < 240*4) k = 9;
                        else if (bounds.getY() == 240*4) k = 10;
                        else if (bounds.getY() == 0 && bounds.getX() < 320*3) k = 11;
                        else if (bounds.getY() == 0 && bounds.getX() >= 320*3) k = 12;
                        else k = 13;
                        break;
                    case 15 :
                        if (bounds.getX() <= 320 * 3) k = 7;
                        else if (bounds.getX() == 320 * 6) k = 8;
                        else k = 9;
                        break;
                    case 16 :
                        k = 5;
                        break;
                    case 17 :
                        if (bounds.getY() == 240*7) k = 7;
                        else if (bounds.getY() == 240*6 && scene->getLink()->getX() < 320*5 + 160) k = 8;
                        else k = 9;
                        break;
                    case 18 :
                        if (bounds.getX() == 320*4) k = 6;
                        else k = 7;
                        break;
                    case 19 :
                        if (bounds.getY() >= 240*7) k = 6;
                        else k = 7;
                        break;
                    case 20 :
                        if (bounds.getX() == 320) k = 8;
                        else if (bounds.getX() == 320*2) k = 9;
                        else if (bounds.getX() == 320*9) k = 10;
                        else k = 15;
                        break;
                }
                if (k != 0) {
                    scene->setCoffre(map - 11, k, 1);
                }

                ouvrePorte(i, j, (dir == N || dir == S) ? 0 : 1);
                AudioManager::getInstance()->playSound(TS_DOOR);
                scene->setCoffre(map - 11, 3, scene->getCoffre(map - 11, 3) - 1);
            }
        }
        // boss
        if (scene->getCoffre(map - 11, 2) == 1 && dir == N) {
            int value = false;
            switch (map) {
                case 12 : value = 1324; break;
                case 13 : value = 1574; break;
                case 14 : value = 1678; break;
                case 15 : value = 1842; break;
                case 16 : value = 1985; break;
                case 17 : value = 2118; break;
                case 18 : value = 2248; break;
                case 19 : value = 2389; break;
                case 20 : value = 2562; break;
            }
            if (getSol(x, y + 7) == value) {
                ouvrePorte(x/16, ((y + 7)/16) - 3, 0);
                AudioManager::getInstance()->playSound(TS_DOOR);
                scene->setCoffre(map - 11, 2, 2);
            }
        }
    }
}

void Map::ouvrePorteMaison(int x, int y) {
    int i = x / 16;
    int j = (y + 8) / 16;

    if (map == 5) {
        setSol(51*16, y + 8 - 1 - 16, 794, MUR);
        setSol(52*16, y + 8 - 1 - 16, 795, MUR);
        setSol(51*16, y + 8 - 1, 796, PIERRE);
        setSol(52*16, y + 8 - 1, 797, PIERRE);
        mur[51 * 2][j * 2 - 3] = PIERRE;
        mur[51 * 2+1][j * 2 - 3] = PIERRE;
        mur[52 * 2][j * 2 - 3] = PIERRE;
        mur[52 * 2+1][j * 2 - 3] = PIERRE;
    } else {
        setSol(x, y + 8 - 1, 474, SOL_BOIS);
        setSol(x + 16, y + 8 - 1, 475, SOL_BOIS);

        mur[i * 2][j * 2 - 2] = MUR;
        mur[i * 2][j * 2 - 1] = MUR;
        mur[i * 2 + 3][j * 2 - 2] = MUR;
        mur[i * 2 + 3][j * 2 - 1] = MUR;
    }


}

void Map::testAnimRoom() {
    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Link* link = scene->getLink();
    switch (map) {
        case 12 :
            if (bounds.getX() == 320 * 5 + 160 && bounds.getY() == 0) {
                if (!link->getInventory()->hasCristal(0) && mur[119 * 2 + 1][13 * 2 + 1] != MUR) {
                    AudioManager::getInstance()->playSound(TS_DOOR);
                    AudioManager::getInstance()->playMusic(16);
                    fermePorte(119, 13, 0);
                } else if (!link->getInventory()->hasCristal(0) && nbEnnemis() == 0) {
                    AudioManager::getInstance()->playMusic(14);
                } else if (link->getInventory()->hasCristal(0) && mur[119 * 2 + 1][13 * 2 + 1] == MUR) {
                    AudioManager::getInstance()->playSound(TS_DOOR);
                    ouvrePorte(119, 13, 0);
                }
            }
            break;
        case 13 :
            if (bounds.getX() == 320 * 3 && bounds.getY() == 240 * 4) {
                if (!link->getInventory()->hasCristal(1) && mur[69 * 2 + 1][73 * 2 + 1] != MUR) {
                    AudioManager::getInstance()->playSound(TS_DOOR);
                    AudioManager::getInstance()->playMusic(16);
                    fermePorte(69, 73, 0);
                } else if (!link->getInventory()->hasCristal(1) && nbEnnemis() == 0) {
                    AudioManager::getInstance()->playMusic(14);
                } else if (link->getInventory()->hasCristal(1) && mur[69 * 2 + 1][73 * 2 + 1] == MUR) {
                    AudioManager::getInstance()->playSound(TS_DOOR);
                    ouvrePorte(69, 73, 0);
                }
            }
            break;
        case 14 :
            if (bounds.getX() == 320 * 3 && bounds.getY() == 240 * 3) {
                if (!link->getInventory()->hasCristal(2) && mur[69 * 2 + 1][58 * 2 + 1] != MUR) {
                    AudioManager::getInstance()->playSound(TS_DOOR);
                    AudioManager::getInstance()->playMusic(16);
                    fermePorte(69, 58, 0);
                } else if (!link->getInventory()->hasCristal(2) && nbEnnemis() == 0) {
                    AudioManager::getInstance()->playMusic(14);
                } else if (link->getInventory()->hasCristal(2) && mur[69 * 2 + 1][58 * 2 + 1] == MUR) {
                    AudioManager::getInstance()->playSound(TS_DOOR);
                    ouvrePorte(69, 58, 0);
                }
            }
            break;
        case 15 :
            if (bounds.getX() == 320 * 2 && bounds.getY() == 240 * 2) {
                if (!link->getInventory()->hasCristal(3) && mur[49 * 2 + 1][43 * 2 + 1] != MUR) {
                    AudioManager::getInstance()->playSound(TS_DOOR);
                    AudioManager::getInstance()->playMusic(16);
                    fermePorte(49, 43, 0);
                } else if (!link->getInventory()->hasCristal(3) && nbEnnemis() == 0) {
                    AudioManager::getInstance()->playMusic(17);
                } else if (link->getInventory()->hasCristal(3) && mur[49 * 2 + 1][43 * 2 + 1] == MUR) {
                    AudioManager::getInstance()->playSound(TS_DOOR);
                    ouvrePorte(49, 43, 0);
                }
            }
            if (bounds.getX() <= 320 && bounds.getY() == 240 * 3 && mur[20 * 2][52 * 2] == MUR && !nbEnnemis()) {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(18, 51, 1);
            }
            if (bounds.getX() <= 320 && bounds.getY() == 240 * 4 && mur[20 * 2][67 * 2] == MUR && !nbEnnemis()) {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(18, 66, 1);
            }
            if (bounds.getX() >= 320*3 && bounds.getY() == 240 * 4 && mur[80 * 2][67 * 2] == MUR && !nbEnnemis()) {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(78, 66, 1);
            }
            if (bounds.getX() >= 320*5 && bounds.getX() <= 320*6 && bounds.getY() == 0 && mur[120 * 2][7 * 2] == MUR && !nbEnnemis()) {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(118, 6, 1);
            }
            if (bounds.getX() >= 320*5 && bounds.getX() <= 320*6 && bounds.getY() == 240*2 && mur[120 * 2][37 * 2] == MUR && !nbEnnemis()) {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(118, 36, 1);
            }
            if (bounds.getX() == 320*7 && bounds.getY() <= 240 && mur[149 * 2 + 1][13 * 2 + 1] == MUR && !nbEnnemis()) {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(149, 13, 0);
            }
            if (bounds.getX() == 320*4 && bounds.getY() <= 240 && mur[89 * 2 + 1][13 * 2 + 1] == MUR && !nbEnnemis()) {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(89, 13, 0);
            }
            break;
        case 16 :
            if (bounds.getX() == 320 * 8 && bounds.getY() == 240 * 3) {
                if (!link->getInventory()->hasCristal(4) && mur[169 * 2 + 1][58 * 2 + 1] != MUR) {
                    AudioManager::getInstance()->playSound(TS_DOOR);
                    AudioManager::getInstance()->playMusic(16);
                    fermePorte(169, 58, 0);
                } else if (!link->getInventory()->hasCristal(4) && nbEnnemis() == 0) {
                    AudioManager::getInstance()->playMusic(15);
                } else if (link->getInventory()->hasCristal(4) && mur[169 * 2 + 1][58 * 2 + 1] == MUR) {
                    AudioManager::getInstance()->playSound(TS_DOOR);
                    ouvrePorte(169, 58, 0);
                }
            }
            if (bounds.getX() >= 320 && bounds.getX() <= 320*2 && bounds.getY() == 0 && mur[40 * 2][7 * 2] == MUR && !nbEnnemis()) {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(38, 6, 1);
            }
            if (bounds.getX() >= 320 && bounds.getX() <= 320*2 && bounds.getY() == 240 * 4 && mur[40 * 2][67 * 2] == MUR && !nbEnnemis()) {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(38, 66, 1);
            }
            if (bounds.getX() == 320*8 && bounds.getY() >= 240 && bounds.getY() <= 240*2 && mur[169 * 2 + 1][28 * 2 + 1] == MUR && !nbEnnemis()) {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(169, 28, 0);
            }
            break;
        case 17 :
            if (bounds.getX() == 320 * 7 && bounds.getY() == 240 * 6) {
                if (!link->getInventory()->hasCristal(5) && mur[149 * 2 + 1][103 * 2 + 1] != MUR) {
                    AudioManager::getInstance()->playSound(TS_DOOR);
                    AudioManager::getInstance()->playMusic(16);
                    fermePorte(149, 103, 0);
                } else if (!link->getInventory()->hasCristal(5) && nbEnnemis() == 0) {
                    AudioManager::getInstance()->playMusic(15);
                } else if (link->getInventory()->hasCristal(5) && mur[149 * 2 + 1][103 * 2 + 1] == MUR) {
                    AudioManager::getInstance()->playSound(TS_DOOR);
                    ouvrePorte(149, 103, 0);
                }
            }
            if (bounds.getX() == 320 * 2 && bounds.getY() == 240 * 9 && mur[40 * 2][142 * 2] == MUR && !nbEnnemis()) {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(38, 141, 1);
            }
            if (bounds.getX() == 320 * 4 && bounds.getY() == 240 * 9 && mur[100 * 2][142 * 2] == MUR && !nbEnnemis()) {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(98, 141, 1);
            }
            if (bounds.getX() == 320*3 && bounds.getY() == 240*5 && mur[69 * 2 + 1][73 * 2 + 1] == MUR && !nbEnnemis()) {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(69, 73, 0);
            }
            break;
        case 18 :
            if (bounds.getX() == 320 * 7 && bounds.getY() == 240) {
                if (!link->getInventory()->hasCristal(6) && mur[149 * 2 + 1][28 * 2 + 1] != MUR) {
                    AudioManager::getInstance()->playSound(TS_DOOR);
                    AudioManager::getInstance()->playMusic(16);
                    fermePorte(149, 28, 0);
                } else if (!link->getInventory()->hasCristal(6) && nbEnnemis() == 0) {
                    AudioManager::getInstance()->playMusic(15);
                } else if (link->getInventory()->hasCristal(6) && mur[149 * 2 + 1][28 * 2 + 1] == MUR) {
                    AudioManager::getInstance()->playSound(TS_DOOR);
                    ouvrePorte(149, 28, 0);
                }
            }
            if (bounds.getX() == 320 && bounds.getY() == 240 * 4 && mur[29 * 2 + 1][58 * 2 + 1] == MUR && !nbEnnemis()) {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(29, 58, 0);
            }
            if (bounds.getX() == 320 * 3 && bounds.getY() == 240 * 4 && mur[80 * 2][67 * 2] == MUR && !nbEnnemis()) {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(78, 66, 1);
            }
            break;
        case 19 :
            if (bounds.getX() == 320 && bounds.getY() == 240 * 3) {
                if (link->getEpee() < 5 && mur[29 * 2 + 1][58 * 2 + 1] != MUR) {
                    AudioManager::getInstance()->playSound(TS_DOOR);
                    AudioManager::getInstance()->playMusic(16);
                    fermePorte(29, 58, 0);
                } else if (nbEnnemis() == 0 && mur[29 * 2 + 1][43 * 2 + 1] == MUR) {
                    AudioManager::getInstance()->playMusic(19);
                    AudioManager::getInstance()->playSound(TS_DOOR);
                    ouvrePorte(29, 43, 0);
                } else if (link->getEpee() == 5 && mur[29 * 2 + 1][58 * 2 + 1] == MUR) {
                    AudioManager::getInstance()->playSound(TS_DOOR);
                    ouvrePorte(29, 58, 0);
                } else if (nbEnnemis() == 0) {
                    AudioManager::getInstance()->playMusic(19);
                }
            }
            if (bounds.getX() == 0 && bounds.getY() == 240 * 6 && mur[9 * 2 + 1][103 * 2 + 1] == MUR && !nbEnnemis()) {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(9, 103, 0);
            }
            if (bounds.getX() == 320*2 && bounds.getY() == 240 && mur[49 * 2 + 1][13 * 2 + 1] == MUR && !nbEnnemis()) {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(49, 13, 0);
            }
            if (bounds.getX() == 320*2 && bounds.getY() == 240 * 7 && mur[60 * 2][112 * 2] == MUR && !nbEnnemis()) {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(58, 111, 1);
            }
            if (bounds.getX() == 320*2 && bounds.getY() == 240 * 9 && mur[49 * 2 + 1][133 * 2 + 1] == MUR && !nbEnnemis()) {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(49, 133, 0);
            }
            if (bounds.getX() == 320*3 && bounds.getY() == 240 * 7 && mur[69 * 2 + 1][103 * 2 + 1] == MUR && !nbEnnemis()) {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(69, 103, 0);
            }
            break;
        case 20 :
            if (bounds.getX() == 0 && bounds.getY() == 0) {
                if (mur[9 * 2 + 1][13 * 2 + 1] != MUR) {
                    AudioManager::getInstance()->playSound(TS_DOOR);
                    AudioManager::getInstance()->playMusic(21);
                    fermePorte(9, 13, 0);
                } else if (nbEnnemis() == 0) {
                    AudioManager::getInstance()->playMusic(19);
                    disablePiege();
                }
            }
            if (bounds.getX() == 320 && bounds.getY() == 240 && mur[29 * 2 + 1][13 * 2 + 1] == MUR && !nbEnnemis()) {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(29, 13, 0);
            }
            if (bounds.getX() == 320*2 && bounds.getY() == 240 && mur[49 * 2 + 1][13 * 2 + 1] == MUR && !nbEnnemis()) {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(49, 13, 0);
            }
            if (bounds.getX() == 320*9 && bounds.getY() == 240*2 && mur[189 * 2 + 1][28 * 2 + 1] == MUR && !nbEnnemis()) {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(189, 28, 0);
            }
            if (bounds.getX() == 320*11 && bounds.getY() == 240*6 && mur[220 * 2][97 * 2] == MUR && scene->getCoffre(9, 2)) {
                AudioManager::getInstance()->playSound(TS_DOOR);
                ouvrePorte(218, 96, 1);
            }
            break;
    }
}

void Map::addCoffre(int x, int y, TypeItem type, int id) {
    Link* link = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink();
    addObject(new Coffre(x, y, 0, false, type, id));
    BoundingBox b(x,y,16,16);
    if (b.intersect(link->getBoundingBox())) {
        link->setY(y-24);
    }
}

void Map::permuteBlocs(int step) {
    // 1 = orange up - blue down
    switch (map) {
        case 13 :
            if (step == 0) {
                setSol(27 * 16, 79 * 16, 2, 1, 1460, PIERRE);
                setSol(35 * 16, 81 * 16, 1, 3, 1460, PIERRE);
                setSol(43 * 16, 21 * 16, 1, 3, 1460, PIERRE);
                setSol(54 * 16, 81 * 16, 1, 3, 1460, PIERRE);
                setSol(73 * 16, 79 * 16, 1, 9, 1460, PIERRE);
                setSol(93 * 16, 81 * 16, 1, 5, 1460, PIERRE);
                setSol(96 * 16, 21 * 16, 1, 3, 1460, PIERRE);

                setSol(29 * 16, 81 * 16, 1, 3, 1463, MURRET);
                setSol(49 * 16, 41 * 16, 2, 1, 1463, MURRET);
                setSol(56 * 16, 81 * 16, 1, 3, 1463, MURRET);
                setSol(109 * 16, 79 * 16, 2, 1, 1463, MURRET);
            } else {
                setSol(27 * 16, 79 * 16, 2, 1, 1462, MURRET);
                setSol(35 * 16, 81 * 16, 1, 3, 1462, MURRET);
                setSol(43 * 16, 21 * 16, 1, 3, 1462, MURRET);
                setSol(54 * 16, 81 * 16, 1, 3, 1462, MURRET);
                setSol(73 * 16, 79 * 16, 1, 9, 1462, MURRET);
                setSol(93 * 16, 81 * 16, 1, 5, 1462, MURRET);
                setSol(96 * 16, 21 * 16, 1, 3, 1462, MURRET);

                setSol(29 * 16, 81 * 16, 1, 3, 1461, PIERRE);
                setSol(49 * 16, 41 * 16, 2, 1, 1461, PIERRE);
                setSol(56 * 16, 81 * 16, 1, 3, 1461, PIERRE);
                setSol(109 * 16, 79 * 16, 2, 1, 1461, PIERRE);
            }
            break;
        case 16 :
            if (step == 0) {
                setSol(90 * 16, 36 * 16, 1, 2, 1460, PIERRE);
                setSol(128 * 16, 66 * 16, 1, 3, 1460, PIERRE);
                setSol(156 * 16, 36 * 16, 1, 3, 1460, PIERRE);

                setSol(89 * 16, 18 * 16, 2, 1, 1463, MURRET);
                setSol(94 * 16, 21 * 16, 1, 3, 1463, MURRET);
                setSol(107 * 16, 48 * 16, 6, 1, 1463, MURRET);
                setSol(149 * 16, 80 * 16, 2, 1, 1463, MURRET);
            } else {
                setSol(90 * 16, 36 * 16, 1, 2, 1462, MURRET);
                setSol(128 * 16, 66 * 16, 1, 3, 1462, MURRET);
                setSol(156 * 16, 36 * 16, 1, 3, 1462, MURRET);

                setSol(89 * 16, 18 * 16, 2, 1, 1461, PIERRE);
                setSol(94 * 16, 21 * 16, 1, 3, 1461, PIERRE);
                setSol(107 * 16, 48 * 16, 6, 1, 1461, PIERRE);
                setSol(149 * 16, 80 * 16, 2, 1, 1461, PIERRE);
            }
            break;
        case 20 :
            if (step == 0) {
                setSol(47 * 16, 41 * 16, 6, 1, 1460, PIERRE);
                setSol(47 * 16, 48 * 16, 6, 1, 1460, PIERRE);

                setSol(87 * 16, 41 * 16, 6, 1, 1463, MURRET);
                setSol(87 * 16, 48 * 16, 6, 1, 1463, MURRET);
            } else {
                setSol(47 * 16, 41 * 16, 6, 1, 1462, MURRET);
                setSol(47 * 16, 48 * 16, 6, 1, 1462, MURRET);

                setSol(87 * 16, 41 * 16, 6, 1, 1461, PIERRE);
                setSol(87 * 16, 48 * 16, 6, 1, 1461, PIERRE);
            }
            break;
        case 21 :
            if (step == 0) {
                setSol(7 * 16, 40 * 16, 6, 1, 1460, PIERRE);

                setSol(7 * 16, 34 * 16, 6, 1, 1463, MURRET);
            } else {
                setSol(7 * 16, 40 * 16, 6, 1, 1462, MURRET);

                setSol(7 * 16, 34 * 16, 6, 1, 1461, PIERRE);
            }
            break;
    }
}

void Map::switchSphere(bool blue) {
    List list;
    BoundingBox* box = new BoundingBox(0, 0, w, h);
    objects->get(box, &list);

    list.iterateOnFirst();
    while (list.hasNext()) {
        Sphere* sphere = dynamic_cast<Sphere*>(list.getNext());
        if (sphere != 0) {
            sphere->setBlue(blue);
        }
    }
    delete box;
}

void Map::disablePiege() {
    List list;
    objects->get(&bounds, &list);

    list.iterateOnFirst();
    while (list.hasNext()) {
        PiegeDemi* demi = dynamic_cast<PiegeDemi*>(list.getNext());
        if (demi != 0) {
            demi->disable();
        }
    }
}

int Map::nbEnnemis() {
    List list;
    ennemis->get(&bounds, &list);
    return list.size();
}

void Map::closeChests() {
    if (map == 30) {
        int chests[3] = {0,0,0};
        int randomValue = ((int)rand()) % 3;
        chests[randomValue] = 1;

        BoundingBox b(6*16, 6*16, 5*16, 5*16);
        List list;
        objects->get(&b, &list);

        int num = 0;
        list.iterateOnFirst();
        while (list.hasNext()) {
            Coffre* coffre = dynamic_cast<Coffre*>(list.getNext());
            if (coffre != 0) {
                if (chests[num]) {
                    coffre->close(TI_QUART_COEUR, 32);
                } else {
                    coffre->close(TI_NO_ITEM);
                }
                num++;
            }
        }
    } else if (map == 37) {
        int chests[6] = {0,0,0,0,0,0};
        int randomValue = ((int)rand()) % 6;
        chests[randomValue] = 1;

        BoundingBox b(6*16, 6*16, 5*16, 5*16);
        List list;
        objects->get(&b, &list);

        int num = 0;
        list.iterateOnFirst();
        while (list.hasNext()) {
            Coffre* coffre = dynamic_cast<Coffre*>(list.getNext());
            if (coffre != 0) {
                if (chests[num]) {
                    coffre->close(TI_QUART_COEUR, 34);
                } else {
                    coffre->close(TI_NO_ITEM);
                }
                num++;
            }
        }
    } else if (map == 41) {
        int chests[9] = {0,0,0,0,0,0,0,0,0};
        int randomValue = ((int)rand()) % 9;
        chests[randomValue] = 1;

        BoundingBox b(6*16, 6*16, 5*16, 5*16);
        List list;
        objects->get(&b, &list);

        int num = 0;
        list.iterateOnFirst();
        while (list.hasNext()) {
            Coffre* coffre = dynamic_cast<Coffre*>(list.getNext());
            if (coffre != 0) {
                if (chests[num]) {
                    coffre->close(TI_QUART_COEUR, 35);
                } else {
                    coffre->close(TI_NO_ITEM);
                }
                num++;
            }
        }
    }
}

void Map::openChests(int x, int y) {
    if (map != 30 && map != 37 && map != 41) return;

    List list;
    BoundingBox b(6*16, 6*16, 5*16, 5*16);
    objects->get(&b, &list);

    list.iterateOnFirst();
    while (list.hasNext()) {
        Coffre* coffre = dynamic_cast<Coffre*>(list.getNext());
        if (coffre != 0) {
            coffre->open(true);
        }
    }
}

bool Map::areChestsClosed() {
    if (map != 30 && map != 37 && map != 41) return false;

    BoundingBox b(6*16, 6*16, 16, 16);
    List list;
    objects->get(&b, &list);

    list.iterateOnFirst();
    while (list.hasNext()) {
        Coffre* coffre = dynamic_cast<Coffre*>(list.getNext());
        if (coffre != 0) {
            return !coffre->isOpened();
        }
    }

    return false;
}

void Map::enervePoules() {
    List list;
    objects->get(&bounds, &list);

    list.iterateOnFirst();
    while (list.hasNext()) {
        Poule* poule = dynamic_cast<Poule*>(list.getNext());
        if (poule != 0) {
            poule->enerve();
        }
    }
}

void Map::displayInterruptor(int x, int y) {
    BoundingBox bb = BoundingBox(x, y, 16, 16);
    List list;
    objects->get(&bb, &list);

    list.iterateOnFirst();
    while (list.hasNext()) {
        Interrupteur* inter = dynamic_cast<Interrupteur*>(list.getNext());
        if (inter != 0) {
            inter->displayOnMap();
        }
    }
}

void Map::ouvrePorte(int x, int y, int type) {
    switch (map) {
        case 1 :
            sol[x][y]=181;
            sol[x+1][y]=182;
            sol[x][y+1]=183;
            sol[x+1][y+1]=184;
            mur[x * 2 + 1][y * 2 + 1] = HERBE; mur[x * 2 + 2][y * 2 + 1] = HERBE;
            mur[x * 2 + 1][y * 2 + 2] = HERBE; mur[x * 2 + 2][y * 2 + 2] = HERBE;
            mur[x * 2 + 1][y * 2 + 3] = HERBE; mur[x * 2 + 2][y * 2 + 3] = HERBE;
            break;
        case 3 :
            sol[x][y]=181;
            sol[x+1][y]=182;
            if (type == 0) {
                sol[x][y+1]=478;
                sol[x+1][y+1]=479;
            } else if (type == 1) {
                sol[x][y+1]=482;
                sol[x+1][y+1]=483;
            }
            mur[x * 2 + 1][y * 2 + 1] = EAU; mur[x * 2 + 2][y * 2 + 1] = EAU;
            mur[x * 2 + 1][y * 2 + 2] = EAU; mur[x * 2 + 2][y * 2 + 2] = EAU;
            mur[x * 2 + 1][y * 2 + 3] = EAU; mur[x * 2 + 2][y * 2 + 3] = EAU;
            break;
        case 7 :
            sol[x][y]=181;
            sol[x+1][y]=182;
            sol[x][y+1]=930;
            sol[x+1][y+1]=931;
            mur[x * 2 + 1][y * 2 + 1] = SABLE; mur[x * 2 + 2][y * 2 + 1] = SABLE;
            mur[x * 2 + 1][y * 2 + 2] = SABLE; mur[x * 2 + 2][y * 2 + 2] = SABLE;
            mur[x * 2 + 1][y * 2 + 3] = SABLE; mur[x * 2 + 2][y * 2 + 3] = SABLE;
            break;
        case 9 :
            if (type == 0) {
                sol[x][y]=181;
                sol[x+1][y]=182;
                sol[x][y+1]=1136;
                sol[x+1][y+1]=1137;
                mur[x * 2 + 1][y * 2 + 1] = TERRE; mur[x * 2 + 2][y * 2 + 1] = TERRE;
                mur[x * 2 + 1][y * 2 + 2] = TERRE; mur[x * 2 + 2][y * 2 + 2] = TERRE;
                mur[x * 2 + 1][y * 2 + 3] = TERRE; mur[x * 2 + 2][y * 2 + 3] = TERRE;
            } else {
                sol[x][y]=1167;
                sol[x+1][y]=1168;
                sol[x+2][y]=1169;
                sol[x][y+1]=1170;
                sol[x+1][y+1]=1171;
                sol[x+2][y+1]=1172;
                sol[x][y+2]=1173;
                sol[x+1][y+2]=1174;
                sol[x+2][y+2]=1175;
                mur[x * 2 + 2][y * 2] = PIERRE; mur[x * 2 + 3][y * 2] = PIERRE;
                mur[x * 2 + 2][y * 2 + 1] = PIERRE; mur[x * 2 + 3][y * 2 + 1] = PIERRE;
                mur[x * 2 + 2][y * 2 + 2] = PIERRE; mur[x * 2 + 3][y * 2 + 2] = PIERRE;
                mur[x * 2 + 2][y * 2 + 3] = PIERRE; mur[x * 2 + 3][y * 2 + 3] = PIERRE;
                mur[x * 2 + 2][y * 2 + 4] = PIERRE; mur[x * 2 + 3][y * 2 + 4] = PIERRE;
            }
            break;
        case 11 :
            sol[x][y]=181;
            sol[x+1][y]=182;
            sol[x][y+1]=1206;
            sol[x+1][y+1]=1207;
            mur[x * 2 + 1][y * 2 + 1] = HERBE; mur[x * 2 + 2][y * 2 + 1] = HERBE;
            mur[x * 2 + 1][y * 2 + 2] = HERBE; mur[x * 2 + 2][y * 2 + 2] = HERBE;
            mur[x * 2 + 1][y * 2 + 3] = HERBE; mur[x * 2 + 2][y * 2 + 3] = HERBE;
            break;
        case 12 :
            if (type == 0) {
                sol[x][y]=1268; sol[x + 1][y]=1269;
                sol[x][y + 1]=1270; sol[x + 1][y + 1]=1271;
                sol[x][y + 2]=1263; sol[x + 1][y + 2]=1264;
                sol[x][y + 3]=1265; sol[x + 1][y + 3]=1266;
                mur[x * 2 + 1][y * 2 + 1] = PIERRE; mur[x * 2 + 2][y * 2 + 1] = PIERRE;
                mur[x * 2 + 1][y * 2 + 2] = PIERRE; mur[x * 2 + 2][y * 2 + 2] = PIERRE;
                mur[x * 2 + 1][y * 2 + 3] = PIERRE; mur[x * 2 + 2][y * 2 + 3] = PIERRE;
                mur[x * 2 + 1][y * 2 + 4] = PIERRE; mur[x * 2 + 2][y * 2 + 4] = PIERRE;
                mur[x * 2 + 1][y * 2 + 5] = PIERRE; mur[x * 2 + 2][y * 2 + 5] = PIERRE;
                mur[x * 2 + 1][y * 2 + 6] = PIERRE; mur[x * 2 + 2][y * 2 + 6] = PIERRE;
            } else if (type == 1) {
                sol[x][y]=1279;
                sol[x][y+1]=1281;
                sol[x][y+2]=1283;
                sol[x+1][y]=1280;
                sol[x+1][y+1]=1282;
                sol[x+1][y+2]=1320;

                sol[x+2][y]=1272;
                sol[x+2][y+1]=1274;
                sol[x+2][y+2]=1317;
                sol[x+3][y]=1273;
                sol[x+3][y+1]=1275;
                sol[x+3][y+2]=1277;

                mur[x * 2 + 1][y * 2 + 2] = PIERRE; mur[x * 2 + 2][y * 2 + 2] = PIERRE;
                mur[x * 2 + 1][y * 2 + 3] = PIERRE; mur[x * 2 + 2][y * 2 + 3] = PIERRE;
                mur[x * 2 + 3][y * 2 + 2] = PIERRE; mur[x * 2 + 4][y * 2 + 2] = PIERRE;
                mur[x * 2 + 3][y * 2 + 3] = PIERRE; mur[x * 2 + 4][y * 2 + 3] = PIERRE;
                mur[x * 2 + 5][y * 2 + 2] = PIERRE; mur[x * 2 + 6][y * 2 + 2] = PIERRE;
                mur[x * 2 + 5][y * 2 + 3] = PIERRE; mur[x * 2 + 6][y * 2 + 3] = PIERRE;
            } else if (type == 2) {
                sol[x][y]=1356; sol[x + 1][y]=1357;
                sol[x][y + 1]=1358; sol[x + 1][y + 1]=1359; air[x][y + 1]=1360; air[x + 1][y + 1]=1361;
                sol[x][y + 2]=1350; sol[x + 1][y + 2]=1351; air[x][y + 2]=1354; air[x + 1][y + 2]=1355;
                sol[x][y + 3]=1352; sol[x + 1][y + 3]=1353;
                mur[x * 2 + 1][y * 2 + 1] = PIERRE; mur[x * 2 + 2][y * 2 + 1] = PIERRE;
                mur[x * 2 + 1][y * 2 + 2] = PIERRE; mur[x * 2 + 2][y * 2 + 2] = PIERRE;
                mur[x * 2 + 1][y * 2 + 3] = PIERRE; mur[x * 2 + 2][y * 2 + 3] = PIERRE;
                mur[x * 2 + 1][y * 2 + 4] = PIERRE; mur[x * 2 + 2][y * 2 + 4] = PIERRE;
                mur[x * 2 + 1][y * 2 + 5] = PIERRE; mur[x * 2 + 2][y * 2 + 5] = PIERRE;
                mur[x * 2 + 1][y * 2 + 6] = PIERRE; mur[x * 2 + 2][y * 2 + 6] = PIERRE;
            } else if (type == 3) {
                sol[x][y]=1370;
                sol[x][y+1]=1372;
                sol[x][y+2]=1374;
                sol[x+1][y]=1371; air[x+1][y]=1376;
                sol[x+1][y+1]=1373; air[x+1][y+1]=1377;
                sol[x+1][y+2]=1375;

                sol[x+2][y]=1362; air[x+2][y]=1368;
                sol[x+2][y+1]=1364; air[x+2][y+1]=1369;
                sol[x+2][y+2]=1366;
                sol[x+3][y]=1363;
                sol[x+3][y+1]=1365;
                sol[x+3][y+2]=1367;

                mur[x * 2 + 1][y * 2 + 2] = PIERRE; mur[x * 2 + 2][y * 2 + 2] = PIERRE;
                mur[x * 2 + 1][y * 2 + 3] = PIERRE; mur[x * 2 + 2][y * 2 + 3] = PIERRE;
                mur[x * 2 + 3][y * 2 + 2] = PIERRE; mur[x * 2 + 4][y * 2 + 2] = PIERRE;
                mur[x * 2 + 3][y * 2 + 3] = PIERRE; mur[x * 2 + 4][y * 2 + 3] = PIERRE;
                mur[x * 2 + 5][y * 2 + 2] = PIERRE; mur[x * 2 + 6][y * 2 + 2] = PIERRE;
                mur[x * 2 + 5][y * 2 + 3] = PIERRE; mur[x * 2 + 6][y * 2 + 3] = PIERRE;
            }
            break;
        case 13 :
            if (type == 0) {
                sol[x][y]=1517; sol[x + 1][y]=1518;
                sol[x][y + 1]=1519; sol[x + 1][y + 1]=1520;
                sol[x][y + 2]=1512; sol[x + 1][y + 2]=1513;
                sol[x][y + 3]=1514; sol[x + 1][y + 3]=1515;
                mur[x * 2 + 1][y * 2 + 1] = PIERRE; mur[x * 2 + 2][y * 2 + 1] = PIERRE;
                mur[x * 2 + 1][y * 2 + 2] = PIERRE; mur[x * 2 + 2][y * 2 + 2] = PIERRE;
                mur[x * 2 + 1][y * 2 + 3] = PIERRE; mur[x * 2 + 2][y * 2 + 3] = PIERRE;
                mur[x * 2 + 1][y * 2 + 4] = PIERRE; mur[x * 2 + 2][y * 2 + 4] = PIERRE;
                mur[x * 2 + 1][y * 2 + 5] = PIERRE; mur[x * 2 + 2][y * 2 + 5] = PIERRE;
                mur[x * 2 + 1][y * 2 + 6] = PIERRE; mur[x * 2 + 2][y * 2 + 6] = PIERRE;
            } else if (type == 1) {
                sol[x][y]=1529;
                sol[x][y+1]=1531;
                sol[x][y+2]=1533;
                sol[x+1][y]=1530;
                sol[x+1][y+1]=1532;
                sol[x+1][y+2]=1570;

                sol[x+2][y]=1522;
                sol[x+2][y+1]=1524;
                sol[x+2][y+2]=1567;
                sol[x+3][y]=1523;
                sol[x+3][y+1]=1525;
                sol[x+3][y+2]=1527;

                mur[x * 2 + 1][y * 2 + 2] = PIERRE; mur[x * 2 + 2][y * 2 + 2] = PIERRE;
                mur[x * 2 + 1][y * 2 + 3] = PIERRE; mur[x * 2 + 2][y * 2 + 3] = PIERRE;
                mur[x * 2 + 3][y * 2 + 2] = PIERRE; mur[x * 2 + 4][y * 2 + 2] = PIERRE;
                mur[x * 2 + 3][y * 2 + 3] = PIERRE; mur[x * 2 + 4][y * 2 + 3] = PIERRE;
                mur[x * 2 + 5][y * 2 + 2] = PIERRE; mur[x * 2 + 6][y * 2 + 2] = PIERRE;
                mur[x * 2 + 5][y * 2 + 3] = PIERRE; mur[x * 2 + 6][y * 2 + 3] = PIERRE;
            }
            break;
        case 14 :
            if (type == 0) {
                sol[x][y]=1636; sol[x + 1][y]=1637;
                sol[x][y + 1]=1638; sol[x + 1][y + 1]=1639;
                sol[x][y + 2]=1630; sol[x + 1][y + 2]=1631;
                sol[x][y + 3]=1632; sol[x + 1][y + 3]=1633;
                mur[x * 2 + 1][y * 2 + 1] = PIERRE; mur[x * 2 + 2][y * 2 + 1] = PIERRE;
                mur[x * 2 + 1][y * 2 + 2] = PIERRE; mur[x * 2 + 2][y * 2 + 2] = PIERRE;
                mur[x * 2 + 1][y * 2 + 3] = PIERRE; mur[x * 2 + 2][y * 2 + 3] = PIERRE;
                mur[x * 2 + 1][y * 2 + 4] = PIERRE; mur[x * 2 + 2][y * 2 + 4] = PIERRE;
                mur[x * 2 + 1][y * 2 + 5] = PIERRE; mur[x * 2 + 2][y * 2 + 5] = PIERRE;
                mur[x * 2 + 1][y * 2 + 6] = PIERRE; mur[x * 2 + 2][y * 2 + 6] = PIERRE;
            } else if (type == 1) {
                sol[x][y]=1649;
                sol[x][y+1]=1651;
                sol[x][y+2]=1653;
                sol[x+1][y]=1650;
                sol[x+1][y+1]=1652;
                sol[x+1][y+2]=1654;

                sol[x+2][y]=1642;
                sol[x+2][y+1]=1644;
                sol[x+2][y+2]=1646;
                sol[x+3][y]=1643;
                sol[x+3][y+1]=1645;
                sol[x+3][y+2]=1647;

                mur[x * 2 + 1][y * 2 + 2] = PIERRE; mur[x * 2 + 2][y * 2 + 2] = PIERRE;
                mur[x * 2 + 1][y * 2 + 3] = PIERRE; mur[x * 2 + 2][y * 2 + 3] = PIERRE;
                mur[x * 2 + 3][y * 2 + 2] = PIERRE; mur[x * 2 + 4][y * 2 + 2] = PIERRE;
                mur[x * 2 + 3][y * 2 + 3] = PIERRE; mur[x * 2 + 4][y * 2 + 3] = PIERRE;
                mur[x * 2 + 5][y * 2 + 2] = PIERRE; mur[x * 2 + 6][y * 2 + 2] = PIERRE;
                mur[x * 2 + 5][y * 2 + 3] = PIERRE; mur[x * 2 + 6][y * 2 + 3] = PIERRE;
            } else if (type == 3) {
                sol[x][y]=1728;
                sol[x][y+1]=1730;
                sol[x][y+2]=1732;
                sol[x+1][y]=1729;
                sol[x+1][y+1]=1731; air[x+1][y+1]=1734;
                sol[x+1][y+2]=1733;

                sol[x+2][y]=1721;
                sol[x+2][y+1]=1723; air[x+2][y+1]=1727;
                sol[x+2][y+2]=1725;
                sol[x+3][y]=1722;
                sol[x+3][y+1]=1724;
                sol[x+3][y+2]=1726;

                mur[x * 2 + 1][y * 2 + 2] = PIERRE; mur[x * 2 + 2][y * 2 + 2] = PIERRE;
                mur[x * 2 + 1][y * 2 + 3] = PIERRE; mur[x * 2 + 2][y * 2 + 3] = PIERRE;
                mur[x * 2 + 3][y * 2 + 2] = PIERRE; mur[x * 2 + 4][y * 2 + 2] = PIERRE;
                mur[x * 2 + 3][y * 2 + 3] = PIERRE; mur[x * 2 + 4][y * 2 + 3] = PIERRE;
                mur[x * 2 + 5][y * 2 + 2] = PIERRE; mur[x * 2 + 6][y * 2 + 2] = PIERRE;
                mur[x * 2 + 5][y * 2 + 3] = PIERRE; mur[x * 2 + 6][y * 2 + 3] = PIERRE;
            }
            break;
        case 15 :
            if (type == 0) {
                sol[x][y]=1800; sol[x + 1][y]=1801;
                sol[x][y + 1]=1802; sol[x + 1][y + 1]=1803;
                sol[x][y + 2]=1794; sol[x + 1][y + 2]=1795;
                sol[x][y + 3]=1796; sol[x + 1][y + 3]=1797;
                mur[x * 2 + 1][y * 2 + 1] = PIERRE; mur[x * 2 + 2][y * 2 + 1] = PIERRE;
                mur[x * 2 + 1][y * 2 + 2] = PIERRE; mur[x * 2 + 2][y * 2 + 2] = PIERRE;
                mur[x * 2 + 1][y * 2 + 3] = PIERRE; mur[x * 2 + 2][y * 2 + 3] = PIERRE;
                mur[x * 2 + 1][y * 2 + 4] = PIERRE; mur[x * 2 + 2][y * 2 + 4] = PIERRE;
                mur[x * 2 + 1][y * 2 + 5] = PIERRE; mur[x * 2 + 2][y * 2 + 5] = PIERRE;
                mur[x * 2 + 1][y * 2 + 6] = PIERRE; mur[x * 2 + 2][y * 2 + 6] = PIERRE;
            } else if (type == 1) {
                sol[x][y]=1813;
                sol[x][y+1]=1815;
                sol[x][y+2]=1817;
                sol[x+1][y]=1814;
                sol[x+1][y+1]=1816;
                sol[x+1][y+2]=1818;

                sol[x+2][y]=1806;
                sol[x+2][y+1]=1808;
                sol[x+2][y+2]=1810;
                sol[x+3][y]=1807;
                sol[x+3][y+1]=1809;
                sol[x+3][y+2]=1811;

                mur[x * 2 + 1][y * 2 + 2] = PIERRE; mur[x * 2 + 2][y * 2 + 2] = PIERRE;
                mur[x * 2 + 1][y * 2 + 3] = PIERRE; mur[x * 2 + 2][y * 2 + 3] = PIERRE;
                mur[x * 2 + 3][y * 2 + 2] = PIERRE; mur[x * 2 + 4][y * 2 + 2] = PIERRE;
                mur[x * 2 + 3][y * 2 + 3] = PIERRE; mur[x * 2 + 4][y * 2 + 3] = PIERRE;
                mur[x * 2 + 5][y * 2 + 2] = PIERRE; mur[x * 2 + 6][y * 2 + 2] = PIERRE;
                mur[x * 2 + 5][y * 2 + 3] = PIERRE; mur[x * 2 + 6][y * 2 + 3] = PIERRE;
            }
            break;
        case 16 :
            if (type == 0) {
                sol[x][y]=1943; sol[x + 1][y]=1944;
                sol[x][y + 1]=1945; sol[x + 1][y + 1]=1946;
                sol[x][y + 2]=1938; sol[x + 1][y + 2]=1939;
                sol[x][y + 3]=1940; sol[x + 1][y + 3]=1941;
                mur[x * 2 + 1][y * 2 + 1] = PIERRE; mur[x * 2 + 2][y * 2 + 1] = PIERRE;
                mur[x * 2 + 1][y * 2 + 2] = PIERRE; mur[x * 2 + 2][y * 2 + 2] = PIERRE;
                mur[x * 2 + 1][y * 2 + 3] = PIERRE; mur[x * 2 + 2][y * 2 + 3] = PIERRE;
                mur[x * 2 + 1][y * 2 + 4] = PIERRE; mur[x * 2 + 2][y * 2 + 4] = PIERRE;
                mur[x * 2 + 1][y * 2 + 5] = PIERRE; mur[x * 2 + 2][y * 2 + 5] = PIERRE;
                mur[x * 2 + 1][y * 2 + 6] = PIERRE; mur[x * 2 + 2][y * 2 + 6] = PIERRE;
            } else if (type == 1) {
                sol[x][y]=1954;
                sol[x][y+1]=1956;
                sol[x][y+2]=1958;
                sol[x+1][y]=1981;
                sol[x+1][y+1]=1957;
                sol[x+1][y+2]=1982;

                sol[x+2][y]=1979;
                sol[x+2][y+1]=1949;
                sol[x+2][y+2]=1980;
                sol[x+3][y]=1948;
                sol[x+3][y+1]=1950;
                sol[x+3][y+2]=1952;

                mur[x * 2 + 1][y * 2 + 2] = PIERRE; mur[x * 2 + 2][y * 2 + 2] = PIERRE;
                mur[x * 2 + 1][y * 2 + 3] = PIERRE; mur[x * 2 + 2][y * 2 + 3] = PIERRE;
                mur[x * 2 + 3][y * 2 + 2] = PIERRE; mur[x * 2 + 4][y * 2 + 2] = PIERRE;
                mur[x * 2 + 3][y * 2 + 3] = PIERRE; mur[x * 2 + 4][y * 2 + 3] = PIERRE;
                mur[x * 2 + 5][y * 2 + 2] = PIERRE; mur[x * 2 + 6][y * 2 + 2] = PIERRE;
                mur[x * 2 + 5][y * 2 + 3] = PIERRE; mur[x * 2 + 6][y * 2 + 3] = PIERRE;
            }
            break;
        case 17 :
            if (type == 0) {
                sol[x][y]=2086; sol[x + 1][y]=2087;
                sol[x][y + 1]=2088; sol[x + 1][y + 1]=2089;
                sol[x][y + 2]=2080; sol[x + 1][y + 2]=2081;
                sol[x][y + 3]=2082; sol[x + 1][y + 3]=2083;
                mur[x * 2 + 1][y * 2 + 1] = PIERRE; mur[x * 2 + 2][y * 2 + 1] = PIERRE;
                mur[x * 2 + 1][y * 2 + 2] = PIERRE; mur[x * 2 + 2][y * 2 + 2] = PIERRE;
                mur[x * 2 + 1][y * 2 + 3] = PIERRE; mur[x * 2 + 2][y * 2 + 3] = PIERRE;
                mur[x * 2 + 1][y * 2 + 4] = PIERRE; mur[x * 2 + 2][y * 2 + 4] = PIERRE;
                mur[x * 2 + 1][y * 2 + 5] = PIERRE; mur[x * 2 + 2][y * 2 + 5] = PIERRE;
                mur[x * 2 + 1][y * 2 + 6] = PIERRE; mur[x * 2 + 2][y * 2 + 6] = PIERRE;
            } else if (type == 1) {
                sol[x][y]=2097;
                sol[x][y+1]=2099;
                sol[x][y+2]=2101;
                sol[x+1][y]=2098;
                sol[x+1][y+1]=2100;
                sol[x+1][y+2]=2102;

                sol[x+2][y]=2090;
                sol[x+2][y+1]=2092;
                sol[x+2][y+2]=2094;
                sol[x+3][y]=2091;
                sol[x+3][y+1]=2093;
                sol[x+3][y+2]=2095;

                mur[x * 2 + 1][y * 2 + 2] = PIERRE; mur[x * 2 + 2][y * 2 + 2] = PIERRE;
                mur[x * 2 + 1][y * 2 + 3] = PIERRE; mur[x * 2 + 2][y * 2 + 3] = PIERRE;
                mur[x * 2 + 3][y * 2 + 2] = PIERRE; mur[x * 2 + 4][y * 2 + 2] = PIERRE;
                mur[x * 2 + 3][y * 2 + 3] = PIERRE; mur[x * 2 + 4][y * 2 + 3] = PIERRE;
                mur[x * 2 + 5][y * 2 + 2] = PIERRE; mur[x * 2 + 6][y * 2 + 2] = PIERRE;
                mur[x * 2 + 5][y * 2 + 3] = PIERRE; mur[x * 2 + 6][y * 2 + 3] = PIERRE;
            }
            break;
        case 18 :
            if (type == 0) {
                sol[x][y]=2220; sol[x + 1][y]=2221;
                sol[x][y + 1]=2222; sol[x + 1][y + 1]=2223;
                sol[x][y + 2]=2214; sol[x + 1][y + 2]=2215;
                sol[x][y + 3]=2216; sol[x + 1][y + 3]=2217;
                mur[x * 2 + 1][y * 2 + 1] = PIERRE; mur[x * 2 + 2][y * 2 + 1] = PIERRE;
                mur[x * 2 + 1][y * 2 + 2] = PIERRE; mur[x * 2 + 2][y * 2 + 2] = PIERRE;
                mur[x * 2 + 1][y * 2 + 3] = PIERRE; mur[x * 2 + 2][y * 2 + 3] = PIERRE;
                mur[x * 2 + 1][y * 2 + 4] = PIERRE; mur[x * 2 + 2][y * 2 + 4] = PIERRE;
                mur[x * 2 + 1][y * 2 + 5] = PIERRE; mur[x * 2 + 2][y * 2 + 5] = PIERRE;
                mur[x * 2 + 1][y * 2 + 6] = PIERRE; mur[x * 2 + 2][y * 2 + 6] = PIERRE;
            } else if (type == 1) {
                sol[x][y]=2231;
                sol[x][y+1]=2233;
                sol[x][y+2]=2235;
                sol[x+1][y]=2232;
                sol[x+1][y+1]=2234;
                sol[x+1][y+2]=2236;

                sol[x+2][y]=2224;
                sol[x+2][y+1]=2226;
                sol[x+2][y+2]=2228;
                sol[x+3][y]=2225;
                sol[x+3][y+1]=2227;
                sol[x+3][y+2]=2229;

                mur[x * 2 + 1][y * 2 + 2] = PIERRE; mur[x * 2 + 2][y * 2 + 2] = PIERRE;
                mur[x * 2 + 1][y * 2 + 3] = PIERRE; mur[x * 2 + 2][y * 2 + 3] = PIERRE;
                mur[x * 2 + 3][y * 2 + 2] = PIERRE; mur[x * 2 + 4][y * 2 + 2] = PIERRE;
                mur[x * 2 + 3][y * 2 + 3] = PIERRE; mur[x * 2 + 4][y * 2 + 3] = PIERRE;
                mur[x * 2 + 5][y * 2 + 2] = PIERRE; mur[x * 2 + 6][y * 2 + 2] = PIERRE;
                mur[x * 2 + 5][y * 2 + 3] = PIERRE; mur[x * 2 + 6][y * 2 + 3] = PIERRE;
            } else if (type == 2) {
                sol[x][y]=2278; sol[x + 1][y]=2280;
                sol[x][y + 1]=2283; sol[x + 1][y + 1]=2285;
                mur[x * 2][y * 2] = TROU; mur[x * 2 + 1][y * 2] = TROU;
                mur[x * 2][y * 2 + 1] = TROU; mur[x * 2 + 1][y * 2 + 1] = TROU;
                mur[x * 2][y * 2 + 2] = TROU; mur[x * 2 + 1][y * 2 + 2] = TROU;
                mur[x * 2][y * 2 + 3] = TROU; mur[x * 2 + 1][y * 2 + 3] = TROU;
                mur[x * 2 + 2][y * 2] = TROU; mur[x * 2 + 3][y * 2] = TROU;
                mur[x * 2 + 2][y * 2 + 1] = TROU; mur[x * 2 + 3][y * 2 + 1] = TROU;
                mur[x * 2 + 2][y * 2 + 2] = TROU; mur[x * 2 + 3][y * 2 + 2] = TROU;
                mur[x * 2 + 2][y * 2 + 3] = TROU; mur[x * 2 + 3][y * 2 + 3] = TROU;
            }
            break;
        case 19 :
            if (type == 0) {
                sol[x][y]=2347; sol[x + 1][y]=2348;
                sol[x][y + 1]=2349; sol[x + 1][y + 1]=2350;
                sol[x][y + 2]=2341; sol[x + 1][y + 2]=2342;
                sol[x][y + 3]=2343; sol[x + 1][y + 3]=2344;
                mur[x * 2 + 1][y * 2 + 1] = PIERRE; mur[x * 2 + 2][y * 2 + 1] = PIERRE;
                mur[x * 2 + 1][y * 2 + 2] = PIERRE; mur[x * 2 + 2][y * 2 + 2] = PIERRE;
                mur[x * 2 + 1][y * 2 + 3] = PIERRE; mur[x * 2 + 2][y * 2 + 3] = PIERRE;
                mur[x * 2 + 1][y * 2 + 4] = PIERRE; mur[x * 2 + 2][y * 2 + 4] = PIERRE;
                mur[x * 2 + 1][y * 2 + 5] = PIERRE; mur[x * 2 + 2][y * 2 + 5] = PIERRE;
                mur[x * 2 + 1][y * 2 + 6] = PIERRE; mur[x * 2 + 2][y * 2 + 6] = PIERRE;
            } else if (type == 1) {
                sol[x][y]=2360;
                sol[x][y+1]=2362;
                sol[x][y+2]=2364;
                sol[x+1][y]=2361;
                sol[x+1][y+1]=2363;
                sol[x+1][y+2]=2365;

                sol[x+2][y]=2353;
                sol[x+2][y+1]=2355;
                sol[x+2][y+2]=2357;
                sol[x+3][y]=2354;
                sol[x+3][y+1]=2356;
                sol[x+3][y+2]=2358;

                mur[x * 2 + 1][y * 2 + 2] = PIERRE; mur[x * 2 + 2][y * 2 + 2] = PIERRE;
                mur[x * 2 + 1][y * 2 + 3] = PIERRE; mur[x * 2 + 2][y * 2 + 3] = PIERRE;
                mur[x * 2 + 3][y * 2 + 2] = PIERRE; mur[x * 2 + 4][y * 2 + 2] = PIERRE;
                mur[x * 2 + 3][y * 2 + 3] = PIERRE; mur[x * 2 + 4][y * 2 + 3] = PIERRE;
                mur[x * 2 + 5][y * 2 + 2] = PIERRE; mur[x * 2 + 6][y * 2 + 2] = PIERRE;
                mur[x * 2 + 5][y * 2 + 3] = PIERRE; mur[x * 2 + 6][y * 2 + 3] = PIERRE;
            }
            break;
        case 20 :
            if (type == 0) {
                if (x == 210 && y == 24) {
                    ouvrePorte(x, y, 5);
                    return;
                }
                int offset = (x >= 120 ) ? 123 : 0;
                sol[x][y]=2520+offset; sol[x + 1][y]=2521+offset;
                sol[x][y + 1]=2522+offset; sol[x + 1][y + 1]=2523+offset;
                sol[x][y + 2]=2514+offset; sol[x + 1][y + 2]=2515+offset;
                sol[x][y + 3]=2516+offset; sol[x + 1][y + 3]=2517+offset;
                mur[x * 2 + 1][y * 2 + 1] = PIERRE; mur[x * 2 + 2][y * 2 + 1] = PIERRE;
                mur[x * 2 + 1][y * 2 + 2] = PIERRE; mur[x * 2 + 2][y * 2 + 2] = PIERRE;
                mur[x * 2 + 1][y * 2 + 3] = PIERRE; mur[x * 2 + 2][y * 2 + 3] = PIERRE;
                mur[x * 2 + 1][y * 2 + 4] = PIERRE; mur[x * 2 + 2][y * 2 + 4] = PIERRE;
                mur[x * 2 + 1][y * 2 + 5] = PIERRE; mur[x * 2 + 2][y * 2 + 5] = PIERRE;
                mur[x * 2 + 1][y * 2 + 6] = PIERRE; mur[x * 2 + 2][y * 2 + 6] = PIERRE;
            } else if (type == 1) {
                int offset = (x >= 120 ) ? 123 : 0;
                sol[x][y]=2533+offset;
                sol[x][y+1]=2535+offset;
                sol[x][y+2]=2537+offset;
                sol[x+1][y]=2534+offset;
                sol[x+1][y+1]=2536+offset;
                sol[x+1][y+2]=2538+offset;

                sol[x+2][y]=2526+offset;
                sol[x+2][y+1]=2528+offset;
                sol[x+2][y+2]=2530+offset;
                sol[x+3][y]=2527+offset;
                sol[x+3][y+1]=2529+offset;
                sol[x+3][y+2]=2531+offset;

                mur[x * 2 + 1][y * 2 + 2] = PIERRE; mur[x * 2 + 2][y * 2 + 2] = PIERRE;
                mur[x * 2 + 1][y * 2 + 3] = PIERRE; mur[x * 2 + 2][y * 2 + 3] = PIERRE;
                mur[x * 2 + 3][y * 2 + 2] = PIERRE; mur[x * 2 + 4][y * 2 + 2] = PIERRE;
                mur[x * 2 + 3][y * 2 + 3] = PIERRE; mur[x * 2 + 4][y * 2 + 3] = PIERRE;
                mur[x * 2 + 5][y * 2 + 2] = PIERRE; mur[x * 2 + 6][y * 2 + 2] = PIERRE;
                mur[x * 2 + 5][y * 2 + 3] = PIERRE; mur[x * 2 + 6][y * 2 + 3] = PIERRE;
            } else if (type == 3) {
                sol[x][y]=2714;
                sol[x][y+1]=2716;
                sol[x][y+2]=2718;
                sol[x+1][y]=2715;
                sol[x+1][y+1]=2717; air[x+1][y+1]=2720;
                sol[x+1][y+2]=2719;

                sol[x+2][y]=2707;
                sol[x+2][y+1]=2709; air[x+2][y+1]=2713;
                sol[x+2][y+2]=2711;
                sol[x+3][y]=2708;
                sol[x+3][y+1]=2710;
                sol[x+3][y+2]=2712;

                mur[x * 2 + 1][y * 2 + 2] = PIERRE; mur[x * 2 + 2][y * 2 + 2] = PIERRE;
                mur[x * 2 + 1][y * 2 + 3] = PIERRE; mur[x * 2 + 2][y * 2 + 3] = PIERRE;
                mur[x * 2 + 3][y * 2 + 2] = PIERRE; mur[x * 2 + 4][y * 2 + 2] = PIERRE;
                mur[x * 2 + 3][y * 2 + 3] = PIERRE; mur[x * 2 + 4][y * 2 + 3] = PIERRE;
                mur[x * 2 + 5][y * 2 + 2] = PIERRE; mur[x * 2 + 6][y * 2 + 2] = PIERRE;
                mur[x * 2 + 5][y * 2 + 3] = PIERRE; mur[x * 2 + 6][y * 2 + 3] = PIERRE;
            } else if (type == 4) {
                air[x][y + 2]=2518; air[x + 1][y + 2]=2519;
                sol[x][y + 2]=2514; sol[x + 1][y + 2]=2515;
                sol[x][y + 3]=2516; sol[x + 1][y + 3]=2517;
                mur[x * 2 + 1][y * 2 + 4] = PIERRE; mur[x * 2 + 2][y * 2 + 4] = PIERRE;
                mur[x * 2 + 1][y * 2 + 5] = PIERRE; mur[x * 2 + 2][y * 2 + 5] = PIERRE;
                mur[x * 2 + 1][y * 2 + 6] = PIERRE; mur[x * 2 + 2][y * 2 + 6] = PIERRE;
            } else if (type == 5) {
                sol[x][y] = 2611;
                mur[x * 2][y * 2] = PIERRE; mur[x * 2 + 1][y * 2] = PIERRE;
                mur[x * 2][y * 2 + 1] = PIERRE; mur[x * 2 + 1][y * 2 + 1] = PIERRE;
            }
            break;
        case 22 :
            if (type == 1) {
                sol[x][y]=2097;
                sol[x][y+1]=2099;
                sol[x][y+2]=2101;
                sol[x+1][y]=2098;
                sol[x+1][y+1]=2100;
                sol[x+1][y+2]=2102;

                sol[x+2][y]=2090;
                sol[x+2][y+1]=2092;
                sol[x+2][y+2]=2094;
                sol[x+3][y]=2091;
                sol[x+3][y+1]=2093;
                sol[x+3][y+2]=2095;

                mur[x * 2 + 1][y * 2 + 2] = PIERRE; mur[x * 2 + 2][y * 2 + 2] = PIERRE;
                mur[x * 2 + 1][y * 2 + 3] = PIERRE; mur[x * 2 + 2][y * 2 + 3] = PIERRE;
                mur[x * 2 + 3][y * 2 + 2] = PIERRE; mur[x * 2 + 4][y * 2 + 2] = PIERRE;
                mur[x * 2 + 3][y * 2 + 3] = PIERRE; mur[x * 2 + 4][y * 2 + 3] = PIERRE;
                mur[x * 2 + 5][y * 2 + 2] = PIERRE; mur[x * 2 + 6][y * 2 + 2] = PIERRE;
                mur[x * 2 + 5][y * 2 + 3] = PIERRE; mur[x * 2 + 6][y * 2 + 3] = PIERRE;
            }
            break;
    }
}

void Map::fermePorte(int x, int y, int type) {
    switch (map) {
        case 12 :
            if (type == 0) {
                sol[x][y]=1326; sol[x + 1][y]=1327;
                sol[x][y + 1]=1328; sol[x + 1][y + 1]=1329;
                mur[x * 2 + 1][y * 2 + 1] = MUR; mur[x * 2 + 2][y * 2 + 1] = MUR;
                mur[x * 2 + 1][y * 2 + 2] = MUR; mur[x * 2 + 2][y * 2 + 2] = MUR;
                mur[x * 2 + 1][y * 2 + 3] = MUR; mur[x * 2 + 2][y * 2 + 3] = MUR;
                mur[x * 2 + 1][y * 2 + 4] = MUR; mur[x * 2 + 2][y * 2 + 4] = MUR;
                mur[x * 2 + 1][y * 2 + 5] = MUR; mur[x * 2 + 2][y * 2 + 5] = MUR;
                mur[x * 2 + 1][y * 2 + 6] = MUR; mur[x * 2 + 2][y * 2 + 6] = MUR;
            }
            break;
        case 13 :
            if (type == 0) {
                sol[x][y]=1576; sol[x + 1][y]=1577;
                sol[x][y + 1]=1578; sol[x + 1][y + 1]=1579;
                mur[x * 2 + 1][y * 2 + 1] = MUR; mur[x * 2 + 2][y * 2 + 1] = MUR;
                mur[x * 2 + 1][y * 2 + 2] = MUR; mur[x * 2 + 2][y * 2 + 2] = MUR;
                mur[x * 2 + 1][y * 2 + 3] = MUR; mur[x * 2 + 2][y * 2 + 3] = MUR;
                mur[x * 2 + 1][y * 2 + 4] = MUR; mur[x * 2 + 2][y * 2 + 4] = MUR;
                mur[x * 2 + 1][y * 2 + 5] = MUR; mur[x * 2 + 2][y * 2 + 5] = MUR;
                mur[x * 2 + 1][y * 2 + 6] = MUR; mur[x * 2 + 2][y * 2 + 6] = MUR;
            }
            break;
        case 14 :
            if (type == 0) {
                sol[x][y]=1684; sol[x + 1][y]=1685;
                sol[x][y + 1]=1686; sol[x + 1][y + 1]=1687;
                mur[x * 2 + 1][y * 2 + 1] = MUR; mur[x * 2 + 2][y * 2 + 1] = MUR;
                mur[x * 2 + 1][y * 2 + 2] = MUR; mur[x * 2 + 2][y * 2 + 2] = MUR;
                mur[x * 2 + 1][y * 2 + 3] = MUR; mur[x * 2 + 2][y * 2 + 3] = MUR;
                mur[x * 2 + 1][y * 2 + 4] = MUR; mur[x * 2 + 2][y * 2 + 4] = MUR;
                mur[x * 2 + 1][y * 2 + 5] = MUR; mur[x * 2 + 2][y * 2 + 5] = MUR;
                mur[x * 2 + 1][y * 2 + 6] = MUR; mur[x * 2 + 2][y * 2 + 6] = MUR;
            }
            break;
        case 15 :
            if (type == 0) {
                sol[x][y]=1848; sol[x + 1][y]=1849;
                sol[x][y + 1]=1850; sol[x + 1][y + 1]=1851;
                mur[x * 2 + 1][y * 2 + 1] = MUR; mur[x * 2 + 2][y * 2 + 1] = MUR;
                mur[x * 2 + 1][y * 2 + 2] = MUR; mur[x * 2 + 2][y * 2 + 2] = MUR;
                mur[x * 2 + 1][y * 2 + 3] = MUR; mur[x * 2 + 2][y * 2 + 3] = MUR;
                mur[x * 2 + 1][y * 2 + 4] = MUR; mur[x * 2 + 2][y * 2 + 4] = MUR;
                mur[x * 2 + 1][y * 2 + 5] = MUR; mur[x * 2 + 2][y * 2 + 5] = MUR;
                mur[x * 2 + 1][y * 2 + 6] = MUR; mur[x * 2 + 2][y * 2 + 6] = MUR;
            }
            break;
        case 16 :
            if (type == 0) {
                sol[x][y]=1991; sol[x + 1][y]=1992;
                sol[x][y + 1]=1993; sol[x + 1][y + 1]=1994;
                mur[x * 2 + 1][y * 2 + 1] = MUR; mur[x * 2 + 2][y * 2 + 1] = MUR;
                mur[x * 2 + 1][y * 2 + 2] = MUR; mur[x * 2 + 2][y * 2 + 2] = MUR;
                mur[x * 2 + 1][y * 2 + 3] = MUR; mur[x * 2 + 2][y * 2 + 3] = MUR;
                mur[x * 2 + 1][y * 2 + 4] = MUR; mur[x * 2 + 2][y * 2 + 4] = MUR;
                mur[x * 2 + 1][y * 2 + 5] = MUR; mur[x * 2 + 2][y * 2 + 5] = MUR;
                mur[x * 2 + 1][y * 2 + 6] = MUR; mur[x * 2 + 2][y * 2 + 6] = MUR;
            }
            break;
        case 17 :
            if (type == 0) {
                sol[x][y]=2124; sol[x + 1][y]=2125;
                sol[x][y + 1]=2126; sol[x + 1][y + 1]=2127;
                mur[x * 2 + 1][y * 2 + 1] = MUR; mur[x * 2 + 2][y * 2 + 1] = MUR;
                mur[x * 2 + 1][y * 2 + 2] = MUR; mur[x * 2 + 2][y * 2 + 2] = MUR;
                mur[x * 2 + 1][y * 2 + 3] = MUR; mur[x * 2 + 2][y * 2 + 3] = MUR;
                mur[x * 2 + 1][y * 2 + 4] = MUR; mur[x * 2 + 2][y * 2 + 4] = MUR;
                mur[x * 2 + 1][y * 2 + 5] = MUR; mur[x * 2 + 2][y * 2 + 5] = MUR;
                mur[x * 2 + 1][y * 2 + 6] = MUR; mur[x * 2 + 2][y * 2 + 6] = MUR;
            }
            break;
        case 18 :
            if (type == 0) {
                sol[x][y]=2254; sol[x + 1][y]=2255;
                sol[x][y + 1]=2256; sol[x + 1][y + 1]=2257;
                mur[x * 2 + 1][y * 2 + 1] = MUR; mur[x * 2 + 2][y * 2 + 1] = MUR;
                mur[x * 2 + 1][y * 2 + 2] = MUR; mur[x * 2 + 2][y * 2 + 2] = MUR;
                mur[x * 2 + 1][y * 2 + 3] = MUR; mur[x * 2 + 2][y * 2 + 3] = MUR;
                mur[x * 2 + 1][y * 2 + 4] = MUR; mur[x * 2 + 2][y * 2 + 4] = MUR;
                mur[x * 2 + 1][y * 2 + 5] = MUR; mur[x * 2 + 2][y * 2 + 5] = MUR;
                mur[x * 2 + 1][y * 2 + 6] = MUR; mur[x * 2 + 2][y * 2 + 6] = MUR;
            }
            break;
        case 19 :
            if (type == 0) {
                sol[x][y]=2395; sol[x + 1][y]=2396;
                sol[x][y + 1]=2397; sol[x + 1][y + 1]=2398;
                mur[x * 2 + 1][y * 2 + 1] = MUR; mur[x * 2 + 2][y * 2 + 1] = MUR;
                mur[x * 2 + 1][y * 2 + 2] = MUR; mur[x * 2 + 2][y * 2 + 2] = MUR;
                mur[x * 2 + 1][y * 2 + 3] = MUR; mur[x * 2 + 2][y * 2 + 3] = MUR;
                mur[x * 2 + 1][y * 2 + 4] = MUR; mur[x * 2 + 2][y * 2 + 4] = MUR;
                mur[x * 2 + 1][y * 2 + 5] = MUR; mur[x * 2 + 2][y * 2 + 5] = MUR;
                mur[x * 2 + 1][y * 2 + 6] = MUR; mur[x * 2 + 2][y * 2 + 6] = MUR;
            }
            break;
        case 20 :
            if (type == 0) {
                sol[x][y]=2568; sol[x + 1][y]=2569;
                sol[x][y + 1]=2570; sol[x + 1][y + 1]=2571;
                mur[x * 2 + 1][y * 2 + 1] = MUR; mur[x * 2 + 2][y * 2 + 1] = MUR;
                mur[x * 2 + 1][y * 2 + 2] = MUR; mur[x * 2 + 2][y * 2 + 2] = MUR;
                mur[x * 2 + 1][y * 2 + 3] = MUR; mur[x * 2 + 2][y * 2 + 3] = MUR;
                mur[x * 2 + 1][y * 2 + 4] = MUR; mur[x * 2 + 2][y * 2 + 4] = MUR;
                mur[x * 2 + 1][y * 2 + 5] = MUR; mur[x * 2 + 2][y * 2 + 5] = MUR;
                mur[x * 2 + 1][y * 2 + 6] = MUR; mur[x * 2 + 2][y * 2 + 6] = MUR;
            }
            break;
    }
}

int Map::getEtage() {
    switch (map) {
        case 12 : return -(bounds.getX() / (80 * 16));
        case 13 : return 0;
        case 14 : return bounds.getX() / (100 * 16);
        case 15 :
            if (bounds.getX() < 100 * 16) return 0;
            if (bounds.getX() < 160 * 16) return 1;
            return 2;
        case 16 :
            if (bounds.getX() < 20 * 16) return 0;
            if (bounds.getX() < 60 * 16) return -1;
            return -2;
        case 17 : return bounds.getX() / (140 * 16);
        case 18 : return bounds.getX() / (100 * 16);
        case 19 : return 0;
        case 20 :
            if (bounds.getX() < 20 * 16) return 1;
            if (bounds.getX() < 120 * 16) return 0;
            if (bounds.getX() < 160 * 16) return -1;
            return -2;
        case 21 :
            if (bounds.getX() >= 20 * 16 && bounds.getY() == 45 * 16) return 0;
            return -1;
        case 22 :
            if (bounds.getX() == 0 && bounds.getY() == 30 * 16) return -1;
            return 0;
        default : return 0;
    }
}
