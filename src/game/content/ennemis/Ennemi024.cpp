#include "Ennemi024.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

#include "../effects/FumeeBlanche.h"

#include "../helper/ProjectileHelper.h"

Ennemi024::Ennemi024(int i, int j, bool water) : anim(0), animMax(1), vanim(180), cooldown(0), inWater(water) {
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi24.png", true);
    chrono.reset();

    type = 24;

    x = i;
    y = j;

    // for quadtree operations:
    width = 32;
    height = water ? 38 : 48;

    box.setX(x);
    box.setY(water ? y : y + 16);
    box.setW(32);
    box.setH(32);

    life = 10;
    maxLife = 10;
    recul = 8;
    vitesseRecul = 4;

    isBoss = true;
    stunnable = false;

    vitesse = water ? 2 : 1;

    forceEnn = 2;
}

Ennemi024::~Ennemi024() {
    ResourceManager::getInstance()->free(image);
}

void Ennemi024::reset() {
    Ennemi::reset();
    chrono.reset();
    anim = 0;
    cooldown = 0;
}

bool Ennemi024::isResetable() {
    return alive;
}

void Ennemi024::ennLoop() {

    // move
    int randomValue = (int)((float)rand() / RAND_MAX * (100));
    switch (randomValue) {
        case 1 : moveX(-vitesse);direction=W; break;
        case 2 : moveX(vitesse); direction=E; break;
        case 3 : moveY(-vitesse);direction=N; break;
        case 4 : moveY(vitesse); direction=S; break;
        default :
            if (randomValue < 10) break;
            switch (direction) {
                case N : moveY(-vitesse); break;
                case S : moveY(vitesse); break;
                case W : moveX(-vitesse); break;
                case E : moveX(vitesse); break;
            }
            break;
    }

    testDegatOnLink(getBoundingBox(), direction, forceEnn, TA_PHYSIC, TE_NORMAL);

    if (chrono.getElapsedTime() >= vanim) {
        anim++;
        if (anim > animMax) {
            anim = 0;
        }
        cooldown++;
        if (cooldown == 16) {

            // retrieve target position ( = link ^^)
            Link* link = getLink();

            int dstX = link->getX() + 8;
            int dstY = link->getY() + 24;

            // throw proj and play sound
            double anglx = 0;
            double angly = 0;
            int origx = x + 16;
            int origy = y + 24;
            int destx = dstX;
            int desty = dstY - 8;

            double coef1 = 0;
            double coef2 = 0;

            if ((destx-origx) == 0) {anglx=0; angly=12;}
            else if ((desty-origy) == 0) {anglx=12; angly=0;}
            else {
                coef1=((double)(desty-origy))/((double)(destx-origx));
                coef2=((double)(destx-origx))/((double)(desty-origy));
                anglx=(sqrt(12/(1+(coef1*coef1))));
                angly=(sqrt(12/(1+(coef2*coef2))));
            }
            if (destx - origx < 0) anglx = -anglx;
            if (desty - origy < 0) angly = -angly;

            if (anglx>4) anglx=4;
            if (angly>4) angly=4;
            if (anglx<-4) anglx=-4;
            if (angly<-4) angly=-4;

            ProjectileHelper::getInstance()->addProjectile(TP_BOULE_FEU, origx, origy, anglx, angly);
            AudioManager::getInstance()->playSound(TS_THROW);
            cooldown = 0;
        }
        chrono.reset();
    }
}

void Ennemi024::draw(int offsetX, int offsetY) {
    if (!alive) {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    if (inWater) {
        WindowManager::getInstance()->draw(image, 64 + anim * width, 0, 32, 31, dstX, dstY);
        WindowManager::getInstance()->draw(image, 64 + anim * 36, 32, 36, 19, dstX-2, dstY+18);
    } else {
        WindowManager::getInstance()->draw(image, anim * width, 0, 32, 48, dstX, dstY);
    }

}

void Ennemi024::moveX(int dx) {
    Map* map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();

    int oldX = x;

    BoundingBox* bb = getBoundingBox();
    bb->setX(x + dx);

    if (map->checkCollisions(bb, this, true, false, true, false)) {
        x += dx;
    }

    if (x != oldX) checkPosition();
}

void Ennemi024::moveY(int dy) {
    Map* map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();

    int oldY = y;

    BoundingBox* bb = getBoundingBox();
    bb->setY((inWater ? y : y + 16) + dy);

    if (map->checkCollisions(bb, this, false, false, true, false)) {
        y += dy;
    }

    if (y != oldY) checkPosition();
}

int Ennemi024::getX() {
    return x;
}

int Ennemi024::getY() {
    return y;
}

BoundingBox* Ennemi024::getBoundingBox() {
    box.setX(x);
    box.setY(inWater ? y : y + 16);
    return &box;
}

void Ennemi024::giveItem(int i, int j) {
    AudioManager::getInstance()->playSound(TS_KILLENNEMY);
    Map* map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
    map->addEffect(new FumeeBlanche(i, j));
    map->addItem(ItemHelper::getInstance()->createItem(TI_CRISTAL, 70*16, 70*16 + 8, 1));
}

bool Ennemi024::isToAvoid(Collision c) {
    if (inWater) return c != EAU && c != EAU_PROF;
    else return Collisionable::isToAvoid(c);
}
