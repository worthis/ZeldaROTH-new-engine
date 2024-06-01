#include "Shield.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

Shield::Shield(int i) : level(i)
{
    ostringstream os;
    os << i;
    string filename = "data/images/link/bouclier" + os.str() + ".png";
    image = ResourceManager::getInstance()->loadImage(filename, true);
}

Shield::~Shield()
{
    ResourceManager::getInstance()->free(image);
}

int Shield::getLevel()
{
    return level;
}

void Shield::draw(int offsetX, int offsetY, Direction dir, Animation anim, int step, int charge)
{

    int dstX = offsetX;
    int dstY = offsetY;

    // IDLE, WALK, PUSH, TOUCHE, FLOTTE, NAGE, COULE, HIT_EPEE, NOYE, MORT
    switch (anim)
    {
    case IDLE:
    case WALK:
        if (charge)
        {
            switch (dir)
            {
            case N:
                dstX += 15;
                dstY += 9;
                dir = E;
                break;
            case S:
                dstX -= 3;
                dstY += 10;
                dir = W;
                break;
            default:
                return;
            }
            break;
        }
        switch (dir)
        {
        case N:
            dstX += 9;
            dstY += 9;
            if (anim == WALK)
            {
                if (step == 0 || step == 4)
                    dstY--;
                if (step == 1 || step == 6)
                    dstY -= 2;
            }
            break;
        case S:
            dstY += 14;
            if (anim == WALK)
            {
                if (step == 1 || step == 5)
                    dstY--;
                if (step == 2 || step == 6)
                    dstY -= 3;
                if (step == 3 || step == 7)
                    dstY -= 2;
            }
            break;
        case W:
            dstX -= 3;
            dstY += 8;
            if (anim == WALK)
            {
                if (step == 0 || step == 2 || step == 4 || step == 6)
                    dstY--;
                if (step == 1 || step == 5)
                    dstY -= 2;
            }
            break;
        case E:
            dstX += 15;
            dstY += 8;
            if (anim == WALK)
            {
                if (step == 0 || step == 2 || step == 4 || step == 6)
                    dstY--;
                if (step == 1 || step == 5)
                    dstY -= 2;
            }
            break;
        }
        break;
    case HIT_EPEE:
        switch (dir)
        {
        case N:
            dstX += 16;
            dstY += 12;
            if (step == 1 || step == 4)
                dstY -= 2;
            if (step == 2)
                dstY -= 4;
            if (step == 3)
                dstY -= 3;
            dir = E;
            break;
        case S:
            dstX -= 3;
            dstY += 4;
            if (step == 1)
            {
                dstY += 3;
            }
            else if (step > 1)
            {
                dstY += 5;
                dstX--;
            }
            dir = W;
            break;
        default:
            return;
        }
        break;
    case TIR_GRAPPIN:
    case TIR_LANTERNE:
        switch (dir)
        {
        case N:
            dstX += 16;
            dstY += 9;
            dir = E;
            break;
        case S:
            dstX -= 4;
            dstY += 10;
            dir = W;
            break;
        default:
            return;
        }
        break;
    case TIR_BAGUETTE_FEU:
    case TIR_BAGUETTE_GLACE:
    case TIR_MARTEAU:
        switch (dir)
        {
        case N:
            dstX += 15;
            dstY += 10;
            dir = E;
            if (step != 0)
                dstY--;
            break;
        case S:
            dstX -= 4;
            dstY += 10;
            dir = W;
            break;
        default:
            return;
        }
        break;
    default:
        return;
    }

    draw(dstX, dstY, dir);
}

void Shield::draw(int dstX, int dstY, Direction dir)
{

    int srcX = 0;
    switch (dir)
    {
    case N:
        srcX = 0;
        break;
    case S:
        srcX = 8;
        break;
    case W:
        srcX = 16;
        break;
    case E:
        srcX = 20;
        break;
    }

    int srcY = 0;

    int srcW = 0;
    switch (dir)
    {
    case N:
    case S:
        srcW = 8;
        break;
    case W:
    case E:
        srcW = 4;
        break;
    }

    int srcH = 10;

    WindowManager::getInstance()->draw(image, srcX, srcY, srcW, srcH, dstX, dstY);
}
