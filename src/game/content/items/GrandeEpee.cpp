#include "GrandeEpee.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

GrandeEpee::GrandeEpee(int i, int j)
{
    x = i;
    y = j;
    persistent = true;
    alive = true;
    ready = true;

    image = ResourceManager::getInstance()->loadImage("data/images/items/items.png", true);
    chrono.reset();

    // for quadtree operations:
    width = 10;
    height = 22;

    box.setX(x + 1);
    box.setY(y + 6);
    box.setW(8);
    box.setH(16);
}

GrandeEpee::~GrandeEpee()
{
    ResourceManager::getInstance()->free(image);
}

void GrandeEpee::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    WindowManager::getInstance()->draw(image, 131, 48, 10, 22, dstX, dstY);
}

void GrandeEpee::action()
{
    getLink()->trouveObjet(TI_EPEE_5);
    alive = false;
}

bool GrandeEpee::isPickable() { return false; }
