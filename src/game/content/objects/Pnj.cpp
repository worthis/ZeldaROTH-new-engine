#include "Pnj.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../MainController.h"
#include "../../game/scene/Scene.h"

#include "../../algo/AStar.h"

Pnj::Pnj(int i, int j, int tp, int txt) : type(tp), texte(txt), anim(0), animMax(0), vanim(480), w(0), h(0),
                                          displayW(0), displayH(0), idle(true), direction(S), stop(false)
{
    x = i;
    y = j;

    image = 0;

    ostringstream os;
    os << type;
    image = ResourceManager::getInstance()->loadImage("data/images/npcs/personnage" + os.str() + ".png", true);

    // for quadtree operations:
    width = 16;
    height = 16;

    w = width;
    h = height;

    displayW = w;
    displayH = h;

    init();

    box.setX(x);
    box.setY(y);
    box.setW(width);
    box.setH(height);

    chrono.reset();
}

Pnj::~Pnj()
{
    ResourceManager::getInstance()->free(image);
}

void Pnj::init()
{
    switch (type)
    {
    case 1:
        idle = false;
        height = 25;
        animMax = 1;
        vanim = 240;
        break;
    case 2:
        height = 24;
        h = height;
        displayH = h;
        animMax = 1;
        break;
    case 3:
        height = 23;
        h = height;
        displayH = h;
        animMax = 1;
        break;
    case 4:
        idle = false;
        height = 17;
        h = height;
        displayH = h;
        animMax = 3;
        vanim = 240;
        break;
    case 5:
        idle = false;
        width = 13;
        w = width;
        displayW = w;
        animMax = 1;
        vanim = 240;
        break;
    case 6:
        idle = false;
        width = 15;
        w = width;
        displayW = w;
        animMax = 1;
        vanim = 240;
        break;
    case 7:
        height = 25;
        h = height;
        displayH = h;
        animMax = 1;
        break;
    case 8:
        height = 16 * 3 - 7;
        h = 23;
        displayH = h;
        animMax = 1;
        break;
    case 9:
        height = 27;
        h = height;
        displayH = h;
        animMax = 1;
        break;
    case 10:
        height = 26;
        h = height;
        displayH = h;
        animMax = 3;
        break;
    case 11:
        idle = false;
        height = 24;
        animMax = 1;
        vanim = 240;
        break;
    case 12:
        height = 25;
        h = height;
        displayH = h;
        animMax = 1;
        break;
    case 13:
        idle = false;
        height = 25;
        animMax = 1;
        vanim = 240;
        break;
    case 14:
        idle = false;
        height = 25;
        animMax = 1;
        vanim = 240;
        break;
    case 15:
        idle = false;
        height = 23;
        h = height;
        displayH = h;
        animMax = 1;
        break;
    case 16:
        height = 48;
        h = height;
        displayH = h;
        width = 32;
        w = width;
        displayW = w;
        animMax = 1;
        break;
    case 17:
        height = 25;
        h = height;
        displayH = h;
        width = 18;
        w = width;
        displayW = w;
        animMax = 1;
        break;
    case 18:
        height = 24;
        h = height;
        displayH = h;
        animMax = 1;
        break;
    case 19:
        height = 25;
        h = height;
        displayH = h;
        animMax = 1;
        break;
    case 20:
        height = 26;
        h = height;
        displayH = h;
        animMax = 3;
        break;
    case 21:
        height = 25;
        h = height;
        displayH = h;
        width = 17;
        w = width;
        displayW = w;
        animMax = 1;
        break;
    case 22:
        height = 29;
        h = height;
        displayH = h;
        animMax = 3;
        break;
    case 23:
        idle = false;
        height = 25;
        animMax = 1;
        vanim = 240;
        break;
    case 24:
        height = 21;
        h = height;
        displayH = h;
        animMax = 1;
        break;
    case 25:
        height = 25;
        h = height;
        displayH = h;
        animMax = 1;
        break;
    case 26:
        height = 30;
        h = height;
        displayH = h;
        width = 39;
        w = width;
        displayW = w;
        animMax = 3;
        vanim = 240;
        break;
    case 27:
        height = 17;
        h = height;
        displayH = h;
        animMax = 1;
        break;
    case 28:
        height = 35;
        h = height;
        displayH = h;
        width = 25;
        w = width;
        displayW = w;
        animMax = 4;
        vanim = 240;
        break;
    case 29:
        height = 27;
        h = height;
        displayH = h;
        width = 21;
        w = width;
        displayW = w;
        animMax = 4;
        vanim = 240;
        break;
    case 30:
        height = 17;
        h = height;
        displayH = h;
        animMax = 1;
        break;
    case 31:
        height = 17;
        h = height;
        displayH = h;
        animMax = 1;
        break;
    }
}

void Pnj::loop()
{
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    switch (type)
    {
    case 3:
        if (scene->getAvancement() >= AV_GARDE_DEPLACE)
        {
            if (y < 26 * 16)
            {
                direction = S;
                moveY(1);
                break;
            }
            if (x > 28 * 16)
            {
                direction = N;
                moveX(-1);
                break;
            }
        }
        if (scene->getLink()->getX() < x + 4)
        {
            direction = N;
        }
        else
        {
            direction = S;
        }
        break;
    case 15:
        if (scene->getMap()->getId() == 5)
        {
            if (scene->getAvancement() == AV_ZELDA_SUIT)
            {
                direction = E;
                scene->getLink()->setDirection(W);
                MainController::getInstance()->getGameController()->displayText(226);
            }
            else if (scene->getAvancement() == AV_ZELDA_MARCHE)
            {
                if (x > 60 * 16 + 8)
                {
                    direction = W;
                    moveX(-1);
                    break;
                }
                if (y < 23 * 16)
                {
                    direction = S;
                    moveY(1);
                    break;
                }
                if (x > 51 * 16 + 8)
                {
                    direction = W;
                    moveX(-1);
                    break;
                }
                scene->setAvancement(AV_ZELDA_ARRIVEE);
                scene->getMap()->ouvrePorteMaison(51 * 16, 22 * 16);
                AudioManager::getInstance()->playSound(TS_DOOR);
                alive = false;
                scene->getAnimationInGame()->stop();
            }
        }
        break;
    }

    if (!idle && (type != 15 || scene->getAvancement() != AV_ZELDA_MARCHE))
    {

        BoundingBox bb(x - 16 * 2, y - 16 * 2, width + 32 * 2, height + 32 * 2);
        stop = !scene->checkCollisionsWithLink(&bb);

        if (stop)
        {
            BoundingBox *bblink = scene->getLink()->getBoundingBox();
            int dN = y - (bblink->getY() + bblink->getH());
            int dS = bblink->getY() - (y + height);
            int dW = x - (bblink->getX() + bblink->getW());
            int dE = bblink->getX() - (x + width);
            if (dN >= dS && dN >= dW && dN >= dE)
                direction = N;
            if (dS >= dN && dS >= dW && dS >= dE)
                direction = S;
            if (dW >= dS && dW >= dN && dW >= dE)
                direction = W;
            if (dE >= dS && dE >= dW && dE >= dN)
                direction = E;
        }
        else if (type == 15)
        {
            if (scene->getAvancement() == AV_ZELDA_SUIT && scene->getMap()->getId() == 20)
            {

                Link *link = scene->getLink();

                int dstX = link->getX() + 8;
                int dstY = link->getY() + 24;

                int dist = abs(x + width / 2 - dstX) + abs(y + height - dstY);
                if (dist <= 200)
                {
                    pair<int, int> dir = AStar::getInstance()->resolvePath(this, dstX, dstY, direction, 200);

                    int oldX = x;
                    int oldY = y;
                    if (dir.first)
                        moveX(dir.first);
                    if (dir.second)
                        moveY(dir.second);
                    if (x > oldX && (direction == W || y == oldY))
                        direction = E;
                    if (x < oldX && (direction == E || y == oldY))
                        direction = W;
                    if (y > oldY && (direction == N || x == oldX))
                        direction = S;
                    if (y < oldY && (direction == S || x == oldX))
                        direction = N;
                }
            }
        }
        else
        {
            // move
            int randomValue = (int)((float)rand() / RAND_MAX * (100));
            switch (randomValue)
            {
            case 1:
                moveX(-1);
                direction = W;
                break;
            case 2:
                moveX(1);
                direction = E;
                break;
            case 3:
                moveY(-1);
                direction = N;
                break;
            case 4:
                moveY(1);
                direction = S;
                break;
            default:
                if (randomValue < 8)
                    break;
                switch (direction)
                {
                case N:
                    moveY(-1);
                    break;
                case S:
                    moveY(1);
                    break;
                case W:
                    moveX(-1);
                    break;
                case E:
                    moveX(1);
                    break;
                }
                break;
            }
        }
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

void Pnj::draw(int offsetX, int offsetY)
{
    if (idle)
    {
        switch (type)
        {
        case 3:
            WindowManager::getInstance()->draw(image, width * direction, h * anim, displayW, displayH, x - offsetX, y - offsetY);
            break;
        /*case 8 :
            if (animMax == 0) {
                WindowManager::getInstance()->draw(image, 0, h * 2, displayW, displayH, x - offsetX, y - offsetY);
            } else {
                WindowManager::getInstance()->draw(image, 0, h * anim, displayW, displayH, x - offsetX, y - offsetY);
            }
            break;*/
        default:
            WindowManager::getInstance()->draw(image, 0, h * anim, displayW, displayH, x - offsetX, y - offsetY);
            break;
        }
    }
    else
    {
        switch (type)
        {
        case 4:
            WindowManager::getInstance()->draw(image, 0, h * anim, displayW, displayH, x - offsetX, y - offsetY);
            break;
        case 6:
            WindowManager::getInstance()->draw(image, width * (direction % 2), h * anim, displayW, displayH, x - offsetX, y - offsetY);
            break;
        default:
            WindowManager::getInstance()->draw(image, width * direction, height * anim, width, height, x - offsetX, y - offsetY);
            break;
        }
    }
}

bool Pnj::action(Direction dir)
{
    MainController::getInstance()->getGameController()->displayText(getDynamicText());
    return true;
}

BoundingBox *Pnj::getBoundingBox()
{
    box.setX(x);
    box.setY(y);
    if (idle)
    {
        box.setW(w);
        box.setH(h);
    }
    if (type == 15)
    {
        box.setY(y + 7);
        box.setH(16);
    }
    if (type == 28)
    {
        box.setX(x + 9);
        box.setW(16);
    }
    if (type == 29)
    {
        box.setX(x + 5);
        box.setW(16);
    }
    return &box;
}

int Pnj::getDown()
{
    if (idle)
    {
        return y + displayH;
    }
    else
    {
        return y + height;
    }
}

int Pnj::getDynamicText()
{
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Link *link = scene->getLink();
    // int tmp = 0;
    switch (texte)
    {
    case 170:
        if ((scene->getMap()->getId() == 4 && link->getInventory()->hasObject(FLACON_1)) || (scene->getMap()->getId() == 7 && link->getInventory()->hasObject(FLACON_2)) || (scene->getMap()->getId() == 8 && link->getInventory()->hasObject(FLACON_3)))
        {
            return 175;
        }
        break;
    case 194:
        if (!link->getInventory()->hasObject(LIVRE))
        {
            return 197;
        }
        if (scene->getAvancement() == AV_AUTORISATION_OK)
        {
            scene->setAvancement(AV_GARDE_DEPLACE);
            return 195;
        }
        else if (scene->getAvancement() >= AV_GARDE_DEPLACE)
        {
            return 196;
        }
        break;
    case 198:
    case 199:
    case 200:
    case 314:
    case 326:
        if (!link->getInventory()->hasObject(LIVRE))
        {
            return 197;
        }
        break;
    case 224:
        if (scene->getAvancement() == AV_ZELDA_SUIT)
        {
            return 225;
        }
        break;
    case 227:
        if (link->getEpee() == 5)
        {
            return 228;
        }
        break;
    case 237:
        if ((scene->getMap()->getId() == 23 && link->getInventory()->hasMedaillons(0)) || (scene->getMap()->getId() == 24 && link->getInventory()->hasMedaillons(1)) || (scene->getMap()->getId() == 25 && link->getInventory()->hasMedaillons(2)) || (scene->getMap()->getId() == 26 && link->getStatus()->getMaxMagic() == 64))
        {

            if (link->getStatus()->getVirtualLife() >= link->getStatus()->getMaxLife())
            {
                return 241;
            }
            else
            {
                return 240;
            }
        }
        if (scene->getMap()->getId() == 26)
        {
            return 242;
        }
        if (scene->getMap()->getId() != 23)
        {
            return 237 + scene->getMap()->getId() - 23;
        }
        break;
    case 244:
        if (link->getInventory()->hasObject(ENCYCLOPEDIE))
        {
            if (link->getInventory()->hasQuartCoeur(31))
            {
                if (scene->getTotalMonsters() == 46)
                {
                    return 254;
                }
                else
                {
                    return 253;
                }
            }

            int currentNb = scene->getMonstersForPrice();

            if (currentNb >= 7)
            {
                return 252;
            }
            if (currentNb == 6)
            {
                return 251;
            }
            return 250;
        }
        else
        {
            link->getInventory()->setObject(ENCYCLOPEDIE);
        }
    case 255:
        if (scene->getAvancement() >= AV_MAIRE_VU)
        {
            if (scene->getAvancement() >= AV_MARCHANT_OK)
            {
                if (link->getInventory()->nbCristaux() == 7)
                {
                    if (scene->getAvancement() >= AV_ZELDA_ARRIVEE)
                    {
                        if (link->getEpee() < 5)
                        {
                            return 268;
                        }
                        return 271;
                    }
                    return 267;
                }
                return 266;
            }
            return 265;
        }
        break;
    case 272:
        if (scene->getMap()->getId() == 41 && !link->getInventory()->hasObject(LIVRE))
        {
            return 197;
        }

        if ((scene->getMap()->getId() == 30 && link->getInventory()->hasQuartCoeur(32)) || (scene->getMap()->getId() == 37 && link->getInventory()->hasQuartCoeur(34)) || (scene->getMap()->getId() == 41 && link->getInventory()->hasQuartCoeur(35)))
        {
            return 275;
        }
        if (scene->getMap()->areChestsClosed())
        {
            return 274;
        }
        break;
    case 276:
        if ((link->getInventory()->hasObject(FLACON_1) && link->getInventory()->getFlacon(0) == 0) || (link->getInventory()->hasObject(FLACON_2) && link->getInventory()->getFlacon(1) == 0) || (link->getInventory()->hasObject(FLACON_3) && link->getInventory()->getFlacon(2) == 0))
        {
            return 277;
        }
        break;
    case 296:
        if (scene->getAvancement() == AV_MAIRE_VU)
        {
            scene->setAvancement(AV_MARCHANT_OK);
            return 297;
        }
        break;
    case 300:
        if (link->getInventory()->nbCristaux() >= 3)
        {
            if (link->getEpee() == 1)
            {
                return 302;
            }
            if (link->getInventory()->getCurrent() == GANTS)
            {
                return 304;
            }
            if (link->getInventory()->getCurrent() == ARC && link->getInventory()->nbCristaux() == 7)
            {
                return 306;
            }
            return 301;
        }
        break;
    case 310:
        if ((link->getInventory()->hasObject(FLACON_1) && link->getInventory()->getFlacon(0) == 0) || (link->getInventory()->hasObject(FLACON_2) && link->getInventory()->getFlacon(1) == 0) || (link->getInventory()->hasObject(FLACON_3) && link->getInventory()->getFlacon(2) == 0))
        {
            return 311;
        }
        break;
    case 315:
        if (!link->getInventory()->hasObject(LIVRE))
        {
            return 197;
        }
        if (link->getEpee() == 5)
        {
            return 321;
        }
        if (scene->getAvancement() == AV_AUTORISATION_OK)
        {
            return 318;
        }
        if (scene->getAvancement() > AV_AUTORISATION_OK && scene->getAvancement() < AV_ZELDA_ARRIVEE)
        {
            return 319;
        }
        if (scene->getAvancement() == AV_ZELDA_ARRIVEE)
        {
            return 320;
        }
        break;
    case 323:
        if (!link->getInventory()->hasObject(LIVRE))
        {
            return 197;
        }
        if ((link->getInventory()->hasObject(FLACON_1) && link->getInventory()->getFlacon(0) == 0) || (link->getInventory()->hasObject(FLACON_2) && link->getInventory()->getFlacon(1) == 0) || (link->getInventory()->hasObject(FLACON_3) && link->getInventory()->getFlacon(2) == 0))
        {
            return 324;
        }
        break;
    default:
        break;
    }
    return texte;
}

void Pnj::moveX(int dx)
{
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();

    int oldX = x;

    BoundingBox *bb = getBoundingBox();
    bb->setX(bb->getX() + dx);

    if (scene->checkCollisions(bb, this, false) && scene->checkCollisionsWithLink(bb))
    {
        x += dx;
    }

    if (x != oldX)
        checkPosition();
}

void Pnj::moveY(int dy)
{
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();

    int oldY = y;

    BoundingBox *bb = getBoundingBox();
    bb->setY(bb->getY() + dy);

    if (scene->checkCollisions(bb, this, false) && scene->checkCollisionsWithLink(bb))
    {
        y += dy;
    }

    if (y != oldY)
        checkPosition();
}

void Pnj::moveTo(int i, int j, Direction dir)
{
    x = i;
    y = j;
    direction = dir;
    checkPosition();
}
