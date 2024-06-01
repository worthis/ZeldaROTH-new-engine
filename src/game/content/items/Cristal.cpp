#include "Cristal.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

Cristal::Cristal(int i, int j, int num) : id(num)
{

    x = i;
    y = j - 10;
    persistent = false;

    image = ResourceManager::getInstance()->loadImage("data/images/items/items.png", true);
    chrono.reset();

    // for quadtree operations:
    width = 12;
    height = 26;

    box.setX(x);
    box.setY(y + 10);
    box.setW(12);
    box.setH(16);

    ready = false;
}

Cristal::~Cristal()
{
    ResourceManager::getInstance()->free(image);
}

void Cristal::loop()
{
    if (!ready)
    {
        if (chrono.getElapsedTime() >= vanim)
        {
            anim++;
            if (anim > animMax)
            {
                ready = true;
            }
            chrono.reset();
        }
    }
}

void Cristal::draw(int offsetX, int offsetY)
{
    if (!alive)
    {
        return;
    }

    int dstX = x - offsetX;
    int dstY = y - offsetY;

    if (ready)
    {
        dstY += 10;
    }
    else
    {
        if (anim <= 10)
            dstY += anim;
        else if (anim <= 14)
            dstY += 10 - (anim - 10);
        else if (anim <= 18)
            dstY += 6 + (anim - 14);
        else
            dstY += 10;
    }

    WindowManager::getInstance()->draw(image, 24, 3, 6, 4, dstX + 3, y - offsetY + 24);
    WindowManager::getInstance()->draw(image, 32, 30, 12, 16, dstX, dstY);
}

void Cristal::action()
{
    if (!ready)
        return;
    getLink()->trouveObjet(TI_CRISTAL, id);
    alive = false;
}

bool Cristal::isPickable()
{
    return false;
}
