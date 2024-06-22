#include "MapDonjon.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"
#include "../../../engine/texts/TextManager.h"

#include "../../../config/ConfigurationManager.h"

#include "../../MainController.h"

MapDonjon::MapDonjon() : anim(0), animMax(1), vanim(480), started(false), xLink(0), yLink(0), offsetSkin(0)
{
    lastLang = ConfigurationManager::getInstance()->getLang();

    loadDonjonImages();

    imageLink = ResourceManager::getInstance()->loadImage("data/images/maps/link.png", true);
    imageBoussole = ResourceManager::getInstance()->loadImage("data/images/maps/boussole.png", true);

    for (int i = 0; i < 5; i++)
        imageEtages[i] = 0;
    for (int i = 0; i < 5; i++)
        imageEtagesN[i] = 0;
    previousMapId = -1;
}

MapDonjon::~MapDonjon()
{
    ResourceManager::getInstance()->free(imageMap);
    ResourceManager::getInstance()->free(imageLevel);
    ResourceManager::getInstance()->free(imageLevel2);
    ResourceManager::getInstance()->free(imageLink);
    ResourceManager::getInstance()->free(imageBoussole);
    for (int i = 0; i < 5; i++)
        ResourceManager::getInstance()->free(imageEtages[i]);
    for (int i = 0; i < 5; i++)
        ResourceManager::getInstance()->free(imageEtagesN[i]);
}

void MapDonjon::handleActions(Action *action)
{
    if (!started)
        return;
    if (action->isAction(DISPLAY_MAP) || action->isAction(QUIT_GAME))
    {
        started = false;
        MainController::getInstance()->getGameController()->hideMap();
        AudioManager::getInstance()->playSound(TS_MENU2);
        return;
    }

    if (MainController::getInstance()->getGameController()->getSceneController()->getScene()->getCoffre(mapId - 11, 0))
    {

        int old = etage;
        int min = getEtageMin();
        int max = getEtageMax();

        if (action->isAction(PUSH_UP))
        {
            if (++etage > max)
                etage = min;
        }
        if (action->isAction(PUSH_DOWN))
        {
            if (--etage < min)
                etage = max;
        }

        if (old != etage)
        {
            AudioManager::getInstance()->playSound(TS_MENU3);
            // prepareMap();
            anim = 0;
            chrono.reset();
        }
    }
}

void MapDonjon::loop()
{
    if (!started)
        return;
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

void MapDonjon::draw()
{

    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();

    WindowManager::getInstance()->draw(imageMap, 0, 0, 320, 240, 0, 0);
    TextManager::getInstance()->getText(215 + mapId - 12)->display(120 + 2, 24 + 2);

    if (scene->getCoffre(mapId - 11, 0))
    {

        WindowManager::getInstance()->draw(imageLink, 0, offsetSkin, 14, 12, 24 + 1, 64 + (2 - scene->getMap()->getEtage()) * 16 + 2);

        if (scene->getCoffre(mapId - 11, 1) && bossIsAlive())
        {
            WindowManager::getInstance()->draw(imageBoussole, 2, 0, 8, 8, 72 + 4, 64 + (2 - getEtageBoss()) * 16 + 4);
        }

        drawMap();

        ItemHelper::getInstance()->drawItem(TI_CARTE_DONJON, 28 + 8, 192 + 8);

        int min = getEtageMin();
        int max = getEtageMax();
        WindowManager::getInstance()->draw(imageLevel, 0, (2 - max) * 16, 32, (max - min + 1) * 16, 40, 64 + (2 - max) * 16);
        WindowManager::getInstance()->draw(imageLevel2, 0, (2 - etage) * 16, 32, 16, 40, 64 + (2 - etage) * 16);

        if (anim == 0 && scene->getMap()->getEtage() == etage)
        {
            WindowManager::getInstance()->draw(imageLink, 0, offsetSkin, 14, 12, xLink - 6, yLink - 4);
        }
    }
    if (scene->getCoffre(mapId - 11, 1))
    {
        ItemHelper::getInstance()->drawItem(TI_BOUSSOLE, 48 + 8, 192 + 8);
    }
    if (scene->getCoffre(mapId - 11, 2))
    {
        ItemHelper::getInstance()->drawItem(TI_CLE_BOSS, 68 + 8, 192 + 8);
    }
}

void MapDonjon::launch()
{

    if (ConfigurationManager::getInstance()->isFrench() != wasFrench)
    {
        int currentLang = ConfigurationManager::getInstance()->getLang();
        if (lastLang != currentLang)
        {
            lastLang = currentLang;

            ResourceManager::getInstance()->free(imageMap);
            ResourceManager::getInstance()->free(imageLevel);
            ResourceManager::getInstance()->free(imageLevel2);

            loadDonjonImages();
        }
    }

    offsetSkin = ConfigurationManager::getInstance()->getSkin() * 15;

    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    mapId = scene->getMap()->getId();
    etage = scene->getMap()->getEtage();

    if (scene->getCoffre(mapId - 11, 0))
    {
        loadImages();
    }

    anim = 0;
    chrono.reset();

    started = true;
}

void MapDonjon::drawMap()
{

    int w = getWidth();
    int h = getHeight();
    int dx = getOffsetX();
    int dy = getOffsetY();

    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();

    for (int j = 0; j < h; j++)
    {
        for (int i = 0; i < w; i++)
        {
            WindowManager::getInstance()->draw(scene->getRooms(mapId - 12, i + dx, j + dy) ? imageEtages[2 - etage] : imageEtagesN[2 - etage],
                                               i * 16, j * 16, 16, 16,
                                               128 + (((10 - w) / 2) + i) * 16,
                                               48 + (((10 - h) / 2) + j) * 16);
        }
    }

    if (scene->getMap()->getEtage() == etage)
    {
        Link *link = scene->getLink();
        xLink = 128 + (((10 - w) / 2)) * 16 + ((link->getX() - getOffsetX() * 320) / 20);
        yLink = 48 + (((10 - h) / 2)) * 16 + ((link->getY() - getOffsetY() * 240) / 15);
        if (mapId == 61)
        {
            xLink = 128 + (((10 - w) / 2)) * 16 + (((link->getX() % (320 * 7)) - getOffsetX() * 320) / 20);
        }
    }

    if (scene->getCoffre(mapId - 11, 1))
    {
        switch (mapId)
        {
        case 12:
            if (etage == 0)
            {
                if (!scene->getCoffre(mapId - 11, 4))
                {
                    WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                       128 + ((10 - w) / 2) * 16 + 7,
                                                       48 + (((10 - h) / 2) + 3) * 16 + 7 + 4);
                }
                if (!scene->getCoffre(mapId - 11, 5))
                {
                    WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                       128 + (((10 - w) / 2) + 1) * 16 + 8 + 7,
                                                       48 + ((10 - h) / 2) * 16 + 7);
                }
                if (!scene->getCoffre(mapId - 11, 6))
                {
                    WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                       128 + (((10 - w) / 2) + 3) * 16 + 7,
                                                       48 + (((10 - h) / 2) + 4) * 16 + 7);
                }
                if (!scene->getCoffre(mapId - 11, 2))
                {
                    WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                       128 + ((10 - w) / 2) * 16 + 7,
                                                       48 + (((10 - h) / 2) + 1) * 16 + 7);
                }

                if (!scene->getLink()->getInventory()->hasObject(GANTS))
                { // gants
                    WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                       128 + (((10 - w) / 2) + 3) * 16 + 7,
                                                       48 + (((10 - h) / 2) + 1) * 16 + 7);
                }
            }
            else if (etage == -1)
            {
                if (bossIsAlive())
                { // boss
                    WindowManager::getInstance()->draw(imageBoussole, 2, 0, 8, 8,
                                                       128 + (((10 - w) / 2) + 1) * 16 + 4 + 8,
                                                       48 + ((10 - h) / 2) * 16 + 4);
                }
            }
            break;
        case 13:
            if (!scene->getCoffre(mapId - 11, 2))
            {
                WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                   128 + (((10 - w) / 2) + 3) * 16 + 7,
                                                   48 + (((10 - h) / 2) + 1) * 16 + 7 - 4);
            }
            if (!scene->getCoffre(mapId - 11, 4))
            {
                WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                   128 + ((10 - w) / 2) * 16 + 7,
                                                   48 + (((10 - h) / 2) + 1) * 16 + 7);
            }
            if (!scene->getCoffre(mapId - 11, 5))
            {
                WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                   128 + ((10 - w) / 2) * 16 + 7,
                                                   48 + (((10 - h) / 2) + 5) * 16 + 7);
            }
            if (!scene->getCoffre(mapId - 11, 6))
            {
                WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                   128 + (((10 - w) / 2) + 3) * 16 + 7,
                                                   48 + (((10 - h) / 2) + 3) * 16 + 7);
            }
            if (!scene->getCoffre(mapId - 11, 7))
            {
                WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                   128 + (((10 - w) / 2) + 5) * 16 + 7 - 4,
                                                   48 + (((10 - h) / 2) + 3) * 16 + 7 - 2);
            }
            if (!scene->getCoffre(mapId - 11, 8))
            {
                WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                   128 + (((10 - w) / 2) + 6) * 16 + 7,
                                                   48 + (((10 - h) / 2) + 1) * 16 + 7);
            }
            if (!scene->getLink()->getInventory()->hasObject(GRAPPIN))
            { // grappin
                WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                   128 + (((10 - w) / 2) + 3) * 16 + 7 - 4,
                                                   48 + (((10 - h) / 2) + 5) * 16 + 7 - 2);
            }
            if (bossIsAlive())
            { // boss
                WindowManager::getInstance()->draw(imageBoussole, 2, 0, 8, 8,
                                                   128 + (((10 - w) / 2) + 3) * 16 + 4,
                                                   48 + (((10 - h) / 2) + 4) * 16 + 4);
            }
            break;
        case 14:
            if (etage == 0)
            {
                if (!scene->getCoffre(mapId - 11, 4))
                {
                    WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                       128 + (((10 - w) / 2) + 1) * 16 + 7,
                                                       48 + (((10 - h) / 2) + 3) * 16 + 7);
                }
                if (!scene->getCoffre(mapId - 11, 5))
                {
                    WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                       128 + (((10 - w) / 2) + 4) * 16 + 7,
                                                       48 + (((10 - h) / 2) + 1) * 16 + 7);
                }
                if (!scene->getLink()->getInventory()->hasObject(LANTERNE))
                { // lanterne
                    WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                       128 + (((10 - w) / 2) + 2) * 16 + 7,
                                                       48 + (((10 - h) / 2) + 1) * 16 + 7);
                }
                if (bossIsAlive())
                { // boss
                    WindowManager::getInstance()->draw(imageBoussole, 2, 0, 8, 8,
                                                       128 + (((10 - w) / 2) + 3) * 16 + 4,
                                                       48 + (((10 - h) / 2) + 3) * 16 + 4);
                }
            }
            else if (etage == 1)
            {
                if (!scene->getCoffre(mapId - 11, 2))
                {
                    WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                       128 + (((10 - w) / 2) + 2) * 16 + 7,
                                                       48 + ((10 - h) / 2) * 16 + 7);
                }
                if (!scene->getCoffre(mapId - 11, 6))
                {
                    WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                       128 + (((10 - w) / 2) + 1) * 16 + 7,
                                                       48 + ((10 - h) / 2) * 16 + 7);
                }
                if (!scene->getCoffre(mapId - 11, 7))
                {
                    WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                       128 + (((10 - w) / 2) + 2) * 16 + 7,
                                                       48 + (((10 - h) / 2) + 1) * 16 + 7);
                }
                if (!scene->getCoffre(mapId - 11, 8))
                {
                    WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                       128 + (((10 - w) / 2) + 3) * 16 + 7,
                                                       48 + (((10 - h) / 2) + 2) * 16 + 7);
                }
            }
            break;
        case 15:
            if (etage == 0)
            {
                if (!scene->getCoffre(mapId - 11, 2))
                {
                    WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                       128 + (((10 - w) / 2) + 3) * 16 + 7,
                                                       48 + (((10 - h) / 2) + 2) * 16 + 7);
                }
                if (!scene->getCoffre(mapId - 11, 4))
                {
                    WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                       128 + ((10 - w) / 2) * 16 + 7,
                                                       48 + (((10 - h) / 2) + 3) * 16 + 7);
                }
                if (!scene->getLink()->getInventory()->hasObject(PALMES))
                { // palmes
                    WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                       128 + ((10 - w) / 2) * 16 + 7,
                                                       48 + (((10 - h) / 2) + 2) * 16 + 7);
                }
                if (bossIsAlive())
                { // boss
                    WindowManager::getInstance()->draw(imageBoussole, 2, 0, 8, 8,
                                                       128 + (((10 - w) / 2) + 2) * 16 + 4,
                                                       48 + (((10 - h) / 2) + 2) * 16 + 4);
                }
            }
            else if (etage == 1)
            {
                if (!scene->getCoffre(mapId - 11, 5))
                {
                    WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                       128 + (((10 - w) / 2) + 1) * 16 + 7,
                                                       48 + (((10 - h) / 2) + 1) * 16 + 7);
                }
                if (!scene->getCoffre(mapId - 11, 6))
                {
                    WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                       128 + (((10 - w) / 2) + 1) * 16 + 7,
                                                       48 + (((10 - h) / 2) + 3) * 16 + 7);
                }
            }
            break;
        case 16:
            if (etage == -2)
            {
                if (!scene->getCoffre(mapId - 11, 2))
                {
                    WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                       128 + (((10 - w) / 2) + 5) * 16 + 7,
                                                       48 + ((10 - h) / 2) * 16 + 7);
                }
                if (!scene->getCoffre(mapId - 11, 4))
                {
                    WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                       128 + (((10 - w) / 2) + 2) * 16 + 7,
                                                       48 + ((10 - h) / 2) * 16 + 7);
                }
                if (!scene->getLink()->getInventory()->hasObject(MARTEAU))
                { // marteau
                    WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                       128 + (((10 - w) / 2) + 1) * 16 + 7,
                                                       48 + (((10 - h) / 2) + 1) * 16 + 7);
                }
                if (bossIsAlive())
                { // boss
                    WindowManager::getInstance()->draw(imageBoussole, 2, 0, 8, 8,
                                                       128 + (((10 - w) / 2) + 5) * 16 + 4,
                                                       48 + (((10 - h) / 2) + 3) * 16 + 4);
                }
            }
            break;
        case 17:
            if (etage == 0)
            {
                if (!scene->getCoffre(mapId - 11, 2))
                {
                    WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                       128 + (((10 - w) / 2) + 4) * 16 + 7,
                                                       48 + (((10 - h) / 2) + 7) * 16 + 7);
                }
                if (!scene->getCoffre(mapId - 11, 4))
                {
                    WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                       128 + ((10 - w) / 2) * 16 + 7,
                                                       48 + (((10 - h) / 2) + 2) * 16 + 7);
                }
                if (!scene->getCoffre(mapId - 11, 5))
                {
                    WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                       128 + (((10 - w) / 2) + 2) * 16 + 7,
                                                       48 + (((10 - h) / 2) + 7) * 16 + 7);
                }
                if (!scene->getCoffre(mapId - 11, 6))
                {
                    WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                       128 + (((10 - w) / 2) + 6) * 16 + 7,
                                                       48 + (((10 - h) / 2) + 2) * 16 + 7);
                }
                if (!scene->getLink()->getInventory()->hasObject(BAGUETTE_FEU))
                { // baguette feu
                    WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                       128 + (((10 - w) / 2) + 3) * 16 + 7,
                                                       48 + ((10 - h) / 2) * 16 + 7);
                }
            }
            else if (etage == 1)
            {
                if (bossIsAlive())
                { // boss
                    WindowManager::getInstance()->draw(imageBoussole, 2, 0, 8, 8,
                                                       128 + ((10 - w) / 2) * 16 + 4,
                                                       48 + (((10 - h) / 2) + 6) * 16 + 4);
                }
            }
            break;
        case 18:
            if (etage == 0)
            {
                if (!scene->getCoffre(mapId - 11, 4))
                {
                    WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                       128 + (((10 - w) / 2) + 3) * 16 + 7,
                                                       48 + (((10 - h) / 2) + 2) * 16 + 7);
                }
                if (!scene->getLink()->getInventory()->hasObject(BAGUETTE_GLACE))
                { // baguette glace
                    WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                       128 + ((10 - w) / 2) * 16 + 7,
                                                       48 + (((10 - h) / 2) + 4) * 16 + 7);
                }
            }
            else if (etage == 1)
            {
                if (!scene->getCoffre(mapId - 11, 2))
                {
                    WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                       128 + ((10 - w) / 2) * 16 + 7,
                                                       48 + (((10 - h) / 2) + 4) * 16 + 7);
                }
                if (!scene->getCoffre(mapId - 11, 5))
                {
                    WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                       128 + (((10 - w) / 2) + 1) * 16 + 7,
                                                       48 + (((10 - h) / 2) + 4) * 16 + 7);
                }
                if (bossIsAlive())
                { // boss
                    WindowManager::getInstance()->draw(imageBoussole, 2, 0, 8, 8,
                                                       128 + (((10 - w) / 2) + 2) * 16 + 4,
                                                       48 + (((10 - h) / 2) + 1) * 16 + 4);
                }
            }
            break;
        case 19:
            if (etage == 0)
            {
                if (!scene->getCoffre(mapId - 11, 2))
                {
                    WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                       128 + (((10 - w) / 2) + 2) * 16 + 7,
                                                       48 + ((10 - h) / 2) * 16 + 7);
                }
                if (!scene->getCoffre(mapId - 11, 4))
                {
                    WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                       128 + ((10 - w) / 2) * 16 + 7,
                                                       48 + (((10 - h) / 2) + 7) * 16 + 7);
                }
                if (scene->getLink()->getEpee() < 5)
                { // excalibur
                    WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                       128 + (((10 - w) / 2) + 1) * 16 + 7,
                                                       48 + ((10 - h) / 2) * 16 + 7);
                }
                if (bossIsAlive())
                { // boss
                    WindowManager::getInstance()->draw(imageBoussole, 2, 0, 8, 8,
                                                       128 + (((10 - w) / 2) + 1) * 16 + 4,
                                                       48 + (((10 - h) / 2) + 3) * 16 + 4);
                }
            }
            break;
        case 20:
            if (etage == 1)
            {
                if (bossIsAlive())
                { // boss
                    WindowManager::getInstance()->draw(imageBoussole, 2, 0, 8, 8,
                                                       128 + ((10 - w) / 2) * 16 + 4,
                                                       48 + ((10 - h) / 2) * 16 + 4);
                }
            }
            if (etage == -2)
            {
                if (!scene->getCoffre(mapId - 11, 2))
                {
                    WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                       128 + (((10 - w) / 2) + 3) * 16 + 7,
                                                       48 + (((10 - h) / 2) + 6) * 16 + 7);
                }
                if (!scene->getCoffre(mapId - 11, 6))
                {
                    WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                       128 + (((10 - w) / 2) + 1) * 16 + 7,
                                                       48 + (((10 - h) / 2) + 1) * 16 + 7);
                }
                if (!scene->getCoffre(mapId - 11, 7))
                {
                    WindowManager::getInstance()->draw(imageBoussole, 0, 0, 2, 2,
                                                       128 + (((10 - w) / 2) + 2) * 16 + 7,
                                                       48 + (((10 - h) / 2) + 2) * 16 + 7);
                }
            }
            break;
        default:
            return;
        }
    }
}

int MapDonjon::getWidth()
{
    switch (mapId)
    {
    case 12:
    case 19:
        return 4;
    case 13:
        return 7;
    case 14:
    case 15:
    case 18:
        return 5;
    case 16:
        if (etage == 0)
            return 1;
        if (etage == -1)
            return 2;
        return 6;
    case 17:
        return 7 - etage * 6;
    case 20:
        if (etage == 1)
            return 1;
        if (etage == 0)
            return 5;
        if (etage == -1)
            return 2;
        return 5;
    default:
        return 0;
    }
}

int MapDonjon::getHeight()
{
    switch (mapId)
    {
    case 12:
    case 14:
    case 15:
    case 18:
        return 5;
    case 13:
    case 20:
        return 7;
    case 16:
        return 6;
    case 17:
    case 19:
        return 10;
    default:
        return 0;
    }
}

int MapDonjon::getOffsetX()
{
    switch (mapId)
    {
    case 12:
        return etage * (-4);
    case 13:
    case 19:
        return 0;
    case 14:
    case 18:
        return etage * 5;
    case 15:
        return etage * 5 - etage * etage;
    case 16:
        if (etage == 0)
            return 0;
        if (etage == -1)
            return 1;
        return 3;
    case 17:
        return etage * 7;
    case 20:
        if (etage == 1)
            return 0;
        if (etage == 0)
            return 1;
        if (etage == -1)
            return 6;
        return 8;
    default:
        return 0;
    }
}

int MapDonjon::getOffsetY()
{
    switch (mapId)
    {
    case 12:
    case 13:
    case 14:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
        return 0;
    case 15:
        return -etage;
    default:
        return 0;
    }
}

void MapDonjon::loadImages()
{
    if (previousMapId != mapId)
    {
        for (int i = 0; i < 5; i++)
        {
            ResourceManager::getInstance()->free(imageEtages[i]);
            imageEtages[i] = 0;
            ResourceManager::getInstance()->free(imageEtagesN[i]);
            imageEtagesN[i] = 0;
        }

        switch (mapId)
        {
        case 12:
            imageEtages[2] = ResourceManager::getInstance()->loadImage("data/images/maps/d1e0.png");
            imageEtages[3] = ResourceManager::getInstance()->loadImage("data/images/maps/d1e-1.png");
            imageEtagesN[2] = ResourceManager::getInstance()->loadImage("data/images/maps/nd1e0.png");
            imageEtagesN[3] = ResourceManager::getInstance()->loadImage("data/images/maps/nd1e-1.png");
            break;
        case 13:
            imageEtages[2] = ResourceManager::getInstance()->loadImage("data/images/maps/d2e0.png");
            imageEtagesN[2] = ResourceManager::getInstance()->loadImage("data/images/maps/nd2e0.png");
            break;
        case 14:
            imageEtages[1] = ResourceManager::getInstance()->loadImage("data/images/maps/d3e1.png");
            imageEtages[2] = ResourceManager::getInstance()->loadImage("data/images/maps/d3e0.png");
            imageEtagesN[1] = ResourceManager::getInstance()->loadImage("data/images/maps/nd3e1.png");
            imageEtagesN[2] = ResourceManager::getInstance()->loadImage("data/images/maps/nd3e0.png");
            break;
        case 15:
            imageEtages[0] = ResourceManager::getInstance()->loadImage("data/images/maps/d4e2.png");
            imageEtages[1] = ResourceManager::getInstance()->loadImage("data/images/maps/d4e1.png");
            imageEtages[2] = ResourceManager::getInstance()->loadImage("data/images/maps/d4e0.png");
            imageEtagesN[0] = ResourceManager::getInstance()->loadImage("data/images/maps/nd4e2.png");
            imageEtagesN[1] = ResourceManager::getInstance()->loadImage("data/images/maps/nd4e1.png");
            imageEtagesN[2] = ResourceManager::getInstance()->loadImage("data/images/maps/nd4e0.png");
            break;
        case 16:
            imageEtages[2] = ResourceManager::getInstance()->loadImage("data/images/maps/d5e0.png");
            imageEtages[3] = ResourceManager::getInstance()->loadImage("data/images/maps/d5e-1.png");
            imageEtages[4] = ResourceManager::getInstance()->loadImage("data/images/maps/d5e-2.png");
            imageEtagesN[2] = ResourceManager::getInstance()->loadImage("data/images/maps/nd5e0.png");
            imageEtagesN[3] = ResourceManager::getInstance()->loadImage("data/images/maps/nd5e-1.png");
            imageEtagesN[4] = ResourceManager::getInstance()->loadImage("data/images/maps/nd5e-2.png");
            break;
        case 17:
            imageEtages[1] = ResourceManager::getInstance()->loadImage("data/images/maps/d6e1.png");
            imageEtages[2] = ResourceManager::getInstance()->loadImage("data/images/maps/d6e0.png");
            imageEtagesN[1] = ResourceManager::getInstance()->loadImage("data/images/maps/nd6e1.png");
            imageEtagesN[2] = ResourceManager::getInstance()->loadImage("data/images/maps/nd6e0.png");
            break;
        case 18:
            imageEtages[1] = ResourceManager::getInstance()->loadImage("data/images/maps/d7e1.png");
            imageEtages[2] = ResourceManager::getInstance()->loadImage("data/images/maps/d7e0.png");
            imageEtagesN[1] = ResourceManager::getInstance()->loadImage("data/images/maps/nd7e1.png");
            imageEtagesN[2] = ResourceManager::getInstance()->loadImage("data/images/maps/nd7e0.png");
            break;
        case 19:
            imageEtages[2] = ResourceManager::getInstance()->loadImage("data/images/maps/d8e0.png");
            imageEtagesN[2] = ResourceManager::getInstance()->loadImage("data/images/maps/nd8e0.png");
            break;
        case 20:
            imageEtages[1] = ResourceManager::getInstance()->loadImage("data/images/maps/d9e1.png");
            imageEtages[2] = ResourceManager::getInstance()->loadImage("data/images/maps/d9e0.png");
            imageEtages[3] = ResourceManager::getInstance()->loadImage("data/images/maps/d9e-1.png");
            imageEtages[4] = ResourceManager::getInstance()->loadImage("data/images/maps/d9e-2.png");
            imageEtagesN[1] = ResourceManager::getInstance()->loadImage("data/images/maps/nd9e1.png");
            imageEtagesN[2] = ResourceManager::getInstance()->loadImage("data/images/maps/nd9e0.png");
            imageEtagesN[3] = ResourceManager::getInstance()->loadImage("data/images/maps/nd9e-1.png");
            imageEtagesN[4] = ResourceManager::getInstance()->loadImage("data/images/maps/nd9e-2.png");
            break;
        default:
            return;
        }

        previousMapId = mapId;
    }
}

int MapDonjon::getEtageMin()
{
    switch (mapId)
    {
    case 12:
        return -1;
    case 13:
    case 14:
    case 15:
    case 17:
    case 18:
    case 19:
        return 0;
    case 16:
    case 20:
        return -2;
    default:
        return 0;
    }
}

int MapDonjon::getEtageMax()
{
    switch (mapId)
    {
    case 12:
    case 13:
    case 16:
    case 19:
        return 0;
    case 14:
    case 17:
    case 18:
    case 20:
        return 1;
    case 15:
        return 2;
    default:
        return 0;
    }
}

int MapDonjon::getEtageBoss()
{
    switch (mapId)
    {
    case 12:
        return -1;
    case 13:
    case 14:
    case 15:
    case 19:
        return 0;
    case 16:
        return -2;
    case 17:
    case 18:
    case 20:
        return 1;
    default:
        return 0;
    }
}

bool MapDonjon::bossIsAlive()
{
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    switch (mapId)
    {
    case 12:
        return !scene->getLink()->getInventory()->hasCristal(0);
    case 13:
        return !scene->getLink()->getInventory()->hasCristal(1);
    case 14:
        return !scene->getLink()->getInventory()->hasCristal(2);
    case 15:
        return !scene->getLink()->getInventory()->hasCristal(3);
    case 16:
        return !scene->getLink()->getInventory()->hasCristal(4);
    case 17:
        return !scene->getLink()->getInventory()->hasCristal(5);
    case 18:
        return !scene->getLink()->getInventory()->hasCristal(6);
    case 19:
        return scene->getLink()->getEpee() < 5;
    case 20:
        return true;
    default:
        return false;
    }
}

void MapDonjon::loadDonjonImages()
{
    if (ConfigurationManager::getInstance()->isFrench())
    {
        imageMap = ResourceManager::getInstance()->loadImage("data/images/maps/donjon.png");
        imageLevel = ResourceManager::getInstance()->loadImage("data/images/maps/level.png");
        imageLevel2 = ResourceManager::getInstance()->loadImage("data/images/maps/level2.png");
        return;
    }

    if (ConfigurationManager::getInstance()->isRussian())
    {
        imageMap = ResourceManager::getInstance()->loadImage("data/images/maps/donjon_ru.png");
        imageLevel = ResourceManager::getInstance()->loadImage("data/images/maps/level_ru.png");
        imageLevel2 = ResourceManager::getInstance()->loadImage("data/images/maps/level2_ru.png");
        return;
    }

    imageMap = ResourceManager::getInstance()->loadImage("data/images/maps/donjon_us.png");
    imageLevel = ResourceManager::getInstance()->loadImage("data/images/maps/level_us.png");
    imageLevel2 = ResourceManager::getInstance()->loadImage("data/images/maps/level2_us.png");
}
