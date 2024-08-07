#include "Ennemi003.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

#include "../../algo/AStar.h"

#include "../../game/scene/Scene.h"

#include "../../MainController.h"

Ennemi003::Ennemi003(int i, int j) : anim(0), animMax(2), vanim(180)
{
    image = ResourceManager::getInstance()->loadImage("data/images/ennemis/ennemi3.png", true);
    chrono.reset();

    type = 3;

    x = i;
    y = j;

    // for quadtree operations:
    width = 28;
    height = 17;

    box.setX(x + 2);
    box.setY(y + 1);
    box.setW(24);
    box.setH(16);

    startX = x;
    startY = y;
    startDir = direction;

    life = 2;
    maxLife = 2;
    recul = 32;
    vitesseRecul = 4;
    maxGel = 128;

    items.addType(TI_PETIT_COEUR, 20);
    items.addType(TI_RUBIS_BLEU, 10);
    items.addType(TI_BOMBE, 10);

    forceEnn = 1;
}

Ennemi003::~Ennemi003()
{
    ResourceManager::getInstance()->free(image);
}

void Ennemi003::reset()
{
    Ennemi::reset();
    chrono.reset();
    x = startX;
    y = startY;
    direction = startDir;
    anim = 0;
    checkPosition();
}

void Ennemi003::ennLoop()
{

    // retrieve target position ( = link ^^)
    Link *link = getLink();

    int dstX = link->getX() + 8;
    int dstY = link->getY() + 24;

    int dist = abs(x + 8 - dstX) + abs(y + 17 - dstY);
    if (dist <= maxDist)
    {
        pair<int, int> dir = AStar::getInstance()->resolvePath(this, dstX, dstY, direction);

        move(dir.first, dir.second);

        if (link->getBoundingBox()->intersect(getBoundingBox()))
        {
            testDegatOnLink(&box, direction, forceEnn, TA_PHYSIC, TE_NORMAL);
        }
    }
    else
    {
        idle = true;
    }

    if (chrono.getElapsedTime() >= vanim)
    {
        anim++;
        if (anim > animMax)
        {
            anim = 0;
        }
        chrono.reset();
    }
}

void Ennemi003::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    WindowManager::getInstance()->draw(image, anim * width, 0, width, height, dstX, dstY);
}

int Ennemi003::getX()
{
    return x;
}

int Ennemi003::getY()
{
    return y;
}

BoundingBox *Ennemi003::getBoundingBox()
{
    box.setX(x);
    box.setY(y + 1);
    return &box;
}
