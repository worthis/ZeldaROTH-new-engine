#include "PetiteEpee.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

PetiteEpee::PetiteEpee(int i, int j)
{
    x = i;
    y = j;
    persistent = true;
    alive = true;
    ready = true;

    image = ResourceManager::getInstance()->loadImage("data/images/items/items.png", true);
    chrono.reset();

    // for quadtree operations:
    width = 8;
    height = 16;

    box.setX(x);
    box.setY(y);
    box.setW(8);
    box.setH(16);
}

PetiteEpee::~PetiteEpee()
{
    ResourceManager::getInstance()->free(image);
}

void PetiteEpee::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    WindowManager::getInstance()->draw(image, 132, 32, 8, 16, dstX, dstY);
}

void PetiteEpee::action()
{
    getLink()->trouveObjet(TI_EPEE_1);
    alive = false;
}

bool PetiteEpee::isPickable() { return false; }
