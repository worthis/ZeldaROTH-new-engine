#include "TransitionMaps.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../MainController.h"
#include "../../content/link/Link.h"
#include "../scene/Scene.h"

TransitionMaps::TransitionMaps() : offset(0), offsetMax(0), offsetX(0), offsetY(0), direction(N), map1(0), map2(0),
                                   box1(0), box2(0), alpha(0)
{
    filterForest = ResourceManager::getInstance()->loadImage("data/images/tileset/foret.png");

    SDL_SetTextureBlendMode(filterForest->getImage(), SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(filterForest->getImage(), 128);
}

TransitionMaps::~TransitionMaps()
{
    ResourceManager::getInstance()->free(filterForest);
}

void TransitionMaps::loop()
{

    if (map1->getId() == 1 || map2->getId() == 1)
    {
        if (map1->getId() == 1)
        {
            alpha -= 4;
            if (alpha < 0)
                alpha = 0;
        }
        if (map2->getId() == 1)
        {
            alpha += 4;
            if (alpha > 128)
                alpha = 128;
        }
        SDL_SetTextureAlphaMod(filterForest->getImage(), alpha);
    }

    offset += 8;

    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Link *link = scene->getLink();

    switch (direction)
    {
    case N:
        box1->setH(240 - offset);
        box2->setY(map2->getH() - offset);
        box2->setH(offset);
        if (offset <= 80)
        {
            link->setY(link->getY() - 4);
        }
        break;
    case S:
        box1->setY(map1->getH() - 240 + offset);
        box1->setH(240 - offset);
        box2->setH(offset);
        if (offset <= 80)
        {
            link->setY(link->getY() + 4);
        }
        break;
    case W:
        box1->setW(320 - offset);
        box2->setX(map2->getW() - offset);
        box2->setW(offset);
        if (offset <= 80)
        {
            link->setX(link->getX() - 4);
        }
        break;
    case E:
        box1->setX(map1->getW() - 320 + offset);
        box1->setW(320 - offset);
        box2->setW(offset);
        if (offset <= 80)
        {
            link->setX(link->getX() + 4);
        }
        break;
    }
    if (offset >= offsetMax)
    {

        scene->setMap(map2); // setMap delete map1
        switch (direction)
        {
        case N:
            link->setX(link->getX() - offsetX * 320);
            link->setY(map2->getH() - 40);
            break;
        case S:
            link->setX(link->getX() - offsetX * 320);
            link->setY(8);
            break;
        case W:
            link->setX(map2->getW() - 32);
            link->setY(link->getY() - offsetY * 240);
            break;
        case E:
            link->setX(16);
            link->setY(link->getY() - offsetY * 240);
            break;
        }
        box1->setX(box2->getX());
        box1->setY(box2->getY());
        box1->setW(box2->getW());
        box1->setH(box2->getH());
        delete box2;
        box2 = 0;

        scene->getAnimationInGame()->testAnim();
        map2->launch();
        link->startNewMap();

        if (alpha != 128)
        {
            alpha = 128;
            SDL_SetTextureAlphaMod(filterForest->getImage(), alpha);
        }
        MainController::getInstance()->getGameController()->setStep(GAME_MAIN);
    }
}

void TransitionMaps::draw()
{

    int dstX1 = 0;
    int dstX2 = 0;
    int dstY1 = 0;
    int dstY2 = 0;
    switch (direction)
    {
    case N:
        dstY1 = offset;
        dstY2 = 0;
        break;
    case S:
        dstY1 = 0;
        dstY2 = 240 - offset;
        break;
    case W:
        dstX1 = offset;
        dstX2 = 0;
        break;
    case E:
        dstX1 = 0;
        dstX2 = 320 - offset;
        break;
    }

    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Link *link = scene->getLink();

    List toDraw1;

    map1->draw(&toDraw1, box1, dstX1, dstY1);

    List toDraw2;

    map2->draw(&toDraw2, box2, dstX2, dstY2);

    link->draw(box1->getX() - dstX1, box1->getY() - dstY1);

    map1->drawAir(box1->getX(), box1->getY(), box1->getW(), box1->getH(), dstX1, dstY1);
    map2->drawAir(box2->getX(), box2->getY(), box2->getW(), box2->getH(), dstX2, dstY2);

    // filter forest transition
    if (map1->getId() == 1)
    {
        WindowManager::getInstance()->draw(filterForest, (box1->getX() / 2) % 256, (box1->getY() / 2) % 256, 320, 240, 0, 0);
    }
    else if (map2->getId() == 1)
    {
        WindowManager::getInstance()->draw(filterForest, (box2->getX() / 2) % 256, (box2->getY() / 2) % 256, 320, 240, 0, 0);
    }

    scene->getHud()->draw();
}

void TransitionMaps::init()
{
    offset = 0;

    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    map1 = scene->getMap();
    box1 = scene->getCamera()->getBoundingBox();

    // direction
    Link *link = scene->getLink();
    int x = link->getX();
    int y = link->getY();

    int offX = getOffsetXForMap(map1);
    int offY = getOffsetYForMap(map1);

    if (y <= 0 && offY > 0)
        direction = N;
    else if (y >= map1->getH() - 32 && offY < 18 - (map1->getH() / 240))
        direction = S;
    else if (x <= 8 && offX > 0)
        direction = W;
    else if (x >= map1->getW() - 32 && offX < 18 - (map1->getW() / 320))
        direction = E;

    if (direction == N || direction == S)
    {
        offsetMax = 240;
    }
    else
    {
        offsetMax = 320;
    }

    // second map
    map2 = new Map(getSecondMapId(x, y), scene->getMetronome());
    map2->load();

    offsetX = getOffsetXForMap(map2) - offX;
    offsetY = getOffsetYForMap(map2) - offY;

    box2 = new BoundingBox();
    switch (direction)
    {
    case N:
        box2->setX(box1->getX() - offsetX * 320);
        box2->setY(map2->getH());
        box2->setW(320);
        box2->setH(0);
        break;
    case S:
        box2->setX(box1->getX() - offsetX * 320);
        box2->setY(0);
        box2->setW(320);
        box2->setH(0);
        break;
    case W:
        box2->setX(map2->getW());
        box2->setY(box1->getY() - offsetY * 240);
        box2->setW(0);
        box2->setH(240);
        break;
    case E:
        box2->setX(0);
        box2->setY(box1->getY() - offsetY * 240);
        box2->setW(0);
        box2->setH(240);
        break;
    }

    if (map1->getId() == 1 || map2->getId() == 1)
    {
        if (map1->getId() == 1)
            alpha = 128;
        if (map2->getId() == 1)
            alpha = 0;
        SDL_SetTextureAlphaMod(filterForest->getImage(), alpha);
    }
}

int TransitionMaps::getOffsetXForMap(Map *map)
{
    switch (map->getId())
    {
    case 1:
        return 13;
    case 2:
        return 8;
    case 3:
        return 6;
    case 4:
        return 5;
    case 5:
        return 0;
    case 6:
        return 7;
    case 7:
        return 0;
    case 8:
        return 13;
    case 9:
        return 0;
    case 10:
        return 0;
    case 11:
        return 8;
    default:
        return -1;
    }
}

int TransitionMaps::getOffsetYForMap(Map *map)
{
    switch (map->getId())
    {
    case 1:
        return 0;
    case 2:
        return 3;
    case 3:
        return 7;
    case 4:
        return 3;
    case 5:
        return 3;
    case 6:
        return 0;
    case 7:
        return 0;
    case 8:
        return 5;
    case 9:
        return 7;
    case 10:
        return 11;
    case 11:
        return 11;
    default:
        return -1;
    }
}

int TransitionMaps::getSecondMapId(int x, int y)
{
    switch (map1->getId())
    {
    case 1:
        if (direction == W && y / 240 < 1)
            return 6;
        if (direction == W && y / 240 >= 1)
            return 2;
        if (direction == S)
            return 8;
        break;
    case 2:
        if (direction == N)
            return 6;
        if (direction == S)
            return 3;
        if (direction == W)
            return 4;
        if (direction == E && y / 240 < 2)
            return 1;
        if (direction == E && y / 240 >= 2)
            return 8;
        break;
    case 3:
        if (direction == N && x / 320 < 2)
            return 4;
        if (direction == N && x / 320 >= 2)
            return 2;
        if (direction == W)
            return 9;
        if (direction == E)
            return 8;
        break;
    case 4:
        if (direction == N)
            return 7;
        if (direction == S)
            return 3;
        if (direction == W)
            return 5;
        if (direction == E)
            return 2;
        break;
    case 5:
        if (direction == N)
            return 7;
        if (direction == S)
            return 9;
        if (direction == E)
            return 4;
        break;
    case 6:
        if (direction == S)
            return 2;
        if (direction == W)
            return 7;
        if (direction == E)
            return 1;
        break;
    case 7:
        if (direction == S && x / 320 < 5)
            return 5;
        if (direction == S && x / 320 >= 5)
            return 4;
        if (direction == E)
            return 6;
        break;
    case 8:
        if (direction == N)
            return 1;
        if (direction == W && y / 240 < 2)
            return 2;
        if (direction == W && y / 240 >= 2)
            return 3;
        break;
    case 9:
        if (direction == N)
            return 5;
        if (direction == S)
            return 10;
        if (direction == E)
            return 3;
        break;
    case 10:
        if (direction == N)
            return 9;
        if (direction == E)
            return 11;
        break;
    case 11:
        if (direction == W)
            return 10;
        break;
    default:
        break;
    }
    return -1;
}
