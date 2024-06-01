#include "Ennemi050.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../algo/AStar.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../effects/FumeeBlanche.h"

Ennemi050::Ennemi050(int i, int j) : anim(0), animMax(1), vanim(180) {
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi50.png", true);
    chrono.reset();

    type = 50;

    x = i;
    y = j;

    // for quadtree operations:
    width = 52;
    height = 36;

    box.setX(x+10);
    box.setY(y+4);
    box.setW(32);
    box.setH(32);

    startX = x;
    startY = y;
    startDir = direction;

    life = 100;
    maxLife = 100;
    recul = 8;
    vitesseRecul = 4;

    isBoss = true;
    stunnable = false;

    forceEnn = 20;
}

Ennemi050::~Ennemi050() {
    ResourceManager::getInstance()->free(image);
}

void Ennemi050::reset() {
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    anim = 0;
    checkPosition();
}

bool Ennemi050::isResetable() {
    return alive;
}

void Ennemi050::ennLoop() {

    // retrieve target position ( = link ^^)
    Link* link = getLink();

    int dstX = link->getX() + 8;
    int dstY = link->getY() + 24;

    pair<int, int> dir = AStar::getInstance()->resolvePath(this, dstX, dstY, direction);

    move(dir.first, dir.second);

    testDegatOnLink(getBoundingBox(), direction, forceEnn, TA_PHYSIC, TE_NORMAL);


    if (chrono.getElapsedTime() >= vanim) {
        if (!gel) anim++;
        if (anim > animMax) {
            anim = 0;
        }
        chrono.reset();
    }
}

void Ennemi050::draw(int offsetX, int offsetY) {
    if (!alive) {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    WindowManager::getInstance()->draw(image, direction == N ? 0 : width, anim * height, width, height, dstX, dstY);
}

int Ennemi050::getX() {
    return x;
}

int Ennemi050::getY() {
    return y;
}

BoundingBox* Ennemi050::getBoundingBox() {
    box.setX(x+10);
    box.setY(y+4);
    return &box;
}

bool Ennemi050::hasEffect(TypeAttack type, TypeEffect effect, Direction dir) {
    Link* link = getLink();
    return ((type == TA_SWORD || type == TA_SWORD_HOLD) && link->getEpee() >= 5)
        || (type == TA_ARROW && link->getInventory()->hasObject(ARC_FEE));
}

void Ennemi050::giveItem(int x, int y) {
    AudioManager::getInstance()->playSound(TS_KILLENNEMY);
    Map* map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
    map->addEffect(new FumeeBlanche(x, y));
    map->addItem(ItemHelper::getInstance()->createItem(TI_TRIFORCE, x, y));
}
