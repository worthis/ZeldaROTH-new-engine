#include "TextArea.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"
#include "../../../engine/texts/TextManager.h"

#include "../../MainController.h"

#include "../../content/link/Link.h"

TextArea::TextArea() : step(TEXT_OFF), anim(0), animMax(0), vanim(40), ready(false), text(0), id(0)
{
    image = ResourceManager::getInstance()->loadImage("data/images/texts/cadre.png", true);
    imageCoeur = ResourceManager::getInstance()->loadImage("data/images/status/coeur.png", true);
}

TextArea::~TextArea()
{
    ResourceManager::getInstance()->free(image);
    ResourceManager::getInstance()->free(imageCoeur);
    delete text;
}

void TextArea::handleActions(Action *action)
{
    if (action->isAction(ACTION) ||
        action->isAction(HIT))
    {
        if (ready)
        {
            if (text->hasNext())
            {
                text->next();
                start();
                AudioManager::getInstance()->playSound(TS_TEXTNEXT);
            }
            else if (hasLogicalNext())
            {
                start();
                AudioManager::getInstance()->playSound(TS_TEXTNEXT);
            }
            else
            {
                stop();
                AudioManager::getInstance()->playSound(TS_TEXTEND);
            }
        }
        else
        {
            anim = animMax;
            ready = true;
        }
        return;
    }
    if (ready)
    {
        if (action->isAction(PUSH_UP))
        {
            int newId = -1;
            switch (id)
            {
            case 85:
                newId = id + 2;
                break;
            case 86:
            case 87:
            case 212:
            case 214:
                newId = id - 1;
                break;
            case 211:
            case 213:
                newId = id + 1;
                break;
            default:
                break;
            }
            if (newId != -1)
            {
                setTextId(newId);
                AudioManager::getInstance()->playSound(TS_MENU3);
            }
            return;
        }
        if (action->isAction(PUSH_DOWN))
        {
            int newId = -1;
            switch (id)
            {
            case 85:
            case 86:
            case 211:
            case 213:
                newId = id + 1;
                break;
            case 87:
                newId = id - 2;
                break;
            case 212:
            case 214:
                newId = id - 1;
                break;
            default:
                break;
            }
            if (newId != -1)
            {
                setTextId(newId);
                AudioManager::getInstance()->playSound(TS_MENU3);
            }
            return;
        }
        if (action->isAction(PUSH_LEFT))
        {
            int newId = -1;
            switch (id)
            {
            case 170:
            case 272:
            case 277:
            case 282:
            case 284:
            case 286:
            case 288:
            case 290:
            case 292:
            case 302:
            case 304:
            case 306:
            case 311:
            case 324:
                newId = id + 1;
                break;
            case 171:
            case 273:
            case 278:
            case 283:
            case 285:
            case 287:
            case 289:
            case 291:
            case 293:
            case 303:
            case 305:
            case 307:
            case 312:
            case 325:
                newId = id - 1;
                break;
            default:
                break;
            }
            if (newId != -1)
            {
                setTextId(newId);
                AudioManager::getInstance()->playSound(TS_MENU3);
            }
            return;
        }
        if (action->isAction(PUSH_RIGHT))
        {
            int newId = -1;
            switch (id)
            {
            case 170:
            case 272:
            case 277:
            case 282:
            case 284:
            case 286:
            case 288:
            case 290:
            case 292:
            case 302:
            case 304:
            case 306:
            case 311:
            case 324:
                newId = id + 1;
                break;
            case 171:
            case 273:
            case 278:
            case 283:
            case 285:
            case 287:
            case 289:
            case 291:
            case 293:
            case 303:
            case 305:
            case 307:
            case 312:
            case 325:
                newId = id - 1;
                break;
            default:
                break;
            }
            if (newId != -1)
            {
                setTextId(newId);
                AudioManager::getInstance()->playSound(TS_MENU3);
            }
            return;
        }
    }
}

void TextArea::loop()
{
    if (!ready)
    {
        if (chrono.getElapsedTime() >= vanim)
        {
            do
            {
                ready = (++anim == animMax);
            } while (!ready && text->charAtInBox(anim) == ' ');
            AudioManager::getInstance()->playSound(TS_TEXT, 1);
            chrono.reset();
        }
    }
}

void TextArea::draw()
{
    WindowManager::getInstance()->draw(image, 0, 0, 8, 8, 8, 16 * 9 + 8);
    WindowManager::getInstance()->draw(image, 24, 0, 8, 8, 16 * 19, 16 * 9 + 8);
    WindowManager::getInstance()->draw(image, 0, 24, 8, 8, 8, 16 * 14);
    WindowManager::getInstance()->draw(image, 24, 24, 8, 8, 16 * 19, 16 * 14);

    for (int i = 16; i < 16 * 19; i += 16)
    {
        WindowManager::getInstance()->draw(image, 8, 0, 16, 8, i, 16 * 9 + 8);
        WindowManager::getInstance()->draw(image, 8, 24, 16, 8, i, 16 * 14);
    }

    for (int j = 16 * 10; j < 16 * 14; j += 16)
    {
        WindowManager::getInstance()->draw(image, 0, 8, 8, 16, 8, j);
        WindowManager::getInstance()->draw(image, 24, 8, 8, 16, 16 * 19, j);
    }

    text->displayBox(16, 16 * 10, anim);

    drawAdditionalContent();
}

void TextArea::start()
{
    chrono.reset();
    anim = 0;
    animMax = text->getLengthInBox();
    ready = false;
}

void TextArea::stop()
{
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Map *map = scene->getMap();
    Link *link = scene->getLink();
    if (link->getAnimation() == TROUVE_SIMPLE || link->getAnimation() == TROUVE_DOUBLE)
    {
        link->setAnimation(IDLE);
    }
    // int tmp = 0;

    switch (id)
    {
    case 83:
        scene->setAvancement(AV_INTRO_OK);
        scene->getAnimationInGame()->stop();
        MainController::getInstance()->getGameController()->displayText(84);
        AudioManager::getInstance()->playMusic(25);
        return;
    case 86:
        MainController::getInstance()->getGameController()->saveData();
    case 87:
        AudioManager::getInstance()->stopMusic();
        MainController::getInstance()->setStep(LOGO);
        return;
    case 173:
        if (scene->getMap()->getId() == 4)
        {
            link->trouveObjet(TI_FLACON_1);
        }
        else if (scene->getMap()->getId() == 7)
        {
            link->trouveObjet(TI_FLACON_2);
        }
        else if (scene->getMap()->getId() == 8)
        {
            link->trouveObjet(TI_FLACON_3);
        }
        link->getStatus()->updateRupees(-100);
        return;
    case 213:
        AudioManager::getInstance()->playSound(TS_TELEPORT);
        if (map->getId() == 12)
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(1, 46 * 16 + 8, 23 * 16 + 8, S, false, true);
        else if (map->getId() == 13)
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(3, 93 * 16 + 8, 37 * 16 + 8, S, false, true);
        else if (map->getId() == 14)
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(6, 28 * 16, 3 * 16 + 8, S, false, true);
        else if (map->getId() == 15)
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(7, 14 * 16 + 8, 18 * 16 + 8, S, false, true);
        else if (map->getId() == 16)
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(8, 48 * 16 + 8, 10 * 16 + 8, S, false, true);
        else if (map->getId() == 17)
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(9, 39 * 16, 39 * 16 + 8, S, false, true);
        else if (map->getId() == 18)
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(3, 27 * 16 + 8, 36 * 16, S, false, true);
        else if (map->getId() == 19)
            MainController::getInstance()->getGameController()->getTeleportController()->setTeleport(11, 143 * 16, 4 * 16, S, false, true);
        MainController::getInstance()->getGameController()->setStep(GAME_TELEPORT);
        return;
    case 214:
        scene->getMap()->testAnimRoom();
        break;
    case 224:
        scene->setAvancement(AV_ZELDA_SUIT);
        break;
    case 226:
        scene->setAvancement(AV_ZELDA_MARCHE);
        scene->getAnimationInGame()->testAnim();
        break;
    case 228:
    case 240:
        link->getStatus()->updateLife(link->getStatus()->getMaxLife() - link->getStatus()->getLife());
        break;
    case 233:
        MainController::getInstance()->getGameController()->saveData(true);
        MainController::getInstance()->setStep(ENDING);
        return;
    case 237:
        link->trouveObjet(TI_MEDAILLON_1);
        return;
    case 238:
        link->trouveObjet(TI_MEDAILLON_2);
        return;
    case 239:
        link->trouveObjet(TI_MEDAILLON_3);
        return;
    case 242:
        link->trouveObjet(TI_DOUBLE_MAGIE);
        return;
    case 252:
        for (int i = 0; i < 6; i++)
        {
            if (!link->getInventory()->hasQuartCoeur(26 + i))
            {
                link->trouveObjet(TI_QUART_COEUR, 26 + i);
                return;
            }
        }
        break;
    case 264:
        scene->setAvancement(AV_MAIRE_VU);
        break;
    case 279:
        if (map->getId() == 32)
        {
            link->trouveObjet(TI_POTION_ROUGE);
            link->getStatus()->updateRupees(-60);
        }
        if (map->getId() == 38)
        {
            link->trouveObjet(TI_POTION_VERTE);
            link->getStatus()->updateRupees(-40);
        }
        if (map->getId() == 43)
        {
            link->trouveObjet(TI_POTION_BLEUE);
            link->getStatus()->updateRupees(-160);
        }
        return;
    case 299:
        link->trouveObjet(TI_ARC);
        link->getStatus()->updateRupees(-50);
        map->setSol(13 * 16, 5 * 16, 2847);
        return;
    case 302:
        link->trouveObjet(TI_EPEE_3);
        return;
    case 304:
        link->trouveObjet(TI_GANT2);
        return;
    case 306:
        link->trouveObjet(TI_ARC_FEE);
        return;
    case 318:
        scene->setAvancement(AV_AUTORISATION_OK);
        break;
    default:
        break;
    }

    MainController::getInstance()->getGameController()->setStep(GAME_MAIN);
}

void TextArea::setTextId(int textId)
{
    delete text;
    text = TextManager::getInstance()->getText(textId);
    text->setBox(16 * 18, 16 * 4);
    id = textId;
}

bool TextArea::hasLogicalNext()
{
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Link *link = scene->getLink();
    // int tmp = 0;
    int next = 0;
    switch (id)
    {
    case 88:
        next = link->getInventory()->nbQuartCoeur() ? 89 : 90;
        break;
    case 97:
    case 206:
    case 207:
    case 208:
    case 209:
    case 210:
        next = 211;
        break;
    case 170:
        if (link->getStatus()->getVirtualRupees() >= 100)
        {
            next = 173;
        }
        else
        {
            next = 172;
        }
        break;
    case 171:
    case 273:
    case 278:
    case 283:
    case 285:
    case 287:
    case 289:
    case 291:
    case 293:
    case 303:
    case 305:
    case 307:
    case 312:
    case 325:
        next = 174;
        break;
    case 205:
        if (scene->getAvancement() < AV_MAIRE_VU)
        {
            next = 206;
        }
        else if (link->getInventory()->nbCristaux() < 5)
        {
            next = 207;
        }
        else if (link->getInventory()->nbCristaux() == 5)
        {
            next = 208;
        }
        else if (link->getInventory()->nbCristaux() == 6)
        {
            next = 209;
        }
        else
        {
            next = 210;
        }
        break;
    case 211:
        MainController::getInstance()->getGameController()->saveData();
    case 212:
        next = 213;
        break;
    case 81:
    case 82:
    case 94:
    case 244:
    case 245:
    case 246:
    case 247:
    case 248:
    case 255:
    case 256:
    case 257:
    case 258:
    case 259:
    case 260:
    case 261:
    case 262:
    case 263:
    case 268:
    case 308:
    case 316:
    case 317:
    case 321:
        next = id + 1;
        break;
    case 269:
        if (!link->getInventory()->hasObject(GANTS_2))
        {
            next = 270;
            break;
        }
        return false;
    case 272:
        if (link->getStatus()->getVirtualRupees() >= 10)
        {
            next = 274;
            scene->getMap()->closeChests();
            link->getStatus()->updateRupees(-10);
        }
        else
        {
            next = 172;
        }
        break;
    case 277:
        if (link->getStatus()->getVirtualRupees() >= 60)
        {
            next = 279;
        }
        else
        {
            next = 172;
        }
        break;
    case 282:
        if (link->getStatus()->getVirtualRupees() >= 2)
        {
            next = 295;
            link->getStatus()->updateRupees(-2);
            link->getStatus()->updateLife(2);
        }
        else
        {
            next = 172;
        }
        break;
    case 284:
        if (link->getStatus()->getVirtualRupees() >= 20)
        {
            next = 295;
            link->getStatus()->updateRupees(-20);
            link->getStatus()->updateMagic(link->getStatus()->getMaxMagic() / 4);
        }
        else
        {
            next = 172;
        }
        break;
    case 286:
        if (link->getStatus()->getVirtualRupees() >= 10)
        {
            next = 295;
            link->getStatus()->updateRupees(-10);
            link->getStatus()->setArrows(link->getStatus()->getArrows() + 5);
        }
        else
        {
            next = 172;
        }
        break;
    case 288:
        if (link->getStatus()->getVirtualRupees() >= 10)
        {
            next = 295;
            link->getStatus()->updateRupees(-10);
            link->getStatus()->setBombs(link->getStatus()->getBombs() + 1);
        }
        else
        {
            next = 172;
        }
        break;
    case 290:
        next = 172;
        break;
    case 292:
        if (link->getStatus()->getVirtualRupees() >= 50)
        {
            next = 299;
        }
        else
        {
            next = 172;
        }
        break;
    case 311:
        if (link->getStatus()->getVirtualRupees() >= 40)
        {
            next = 279;
        }
        else
        {
            next = 172;
        }
        break;
    case 315:
        if (link->getInventory()->nbCristaux() >= 4)
        {
            next = 316;
            break;
        }
        return false;
        break;
    case 324:
        if (link->getStatus()->getVirtualRupees() >= 160)
        {
            next = 279;
        }
        else
        {
            next = 172;
        }
        break;
    default:
        return false;
    }
    setTextId(next);
    return true;
}

void TextArea::drawAdditionalContent()
{
    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Link *link = scene->getLink();
    int tmp;
    switch (id)
    {
    case 88:
        tmp = link->getInventory()->nbQuartCoeur();
        if (tmp == 0)
            tmp = 4;
        WindowManager::getInstance()->draw(imageCoeur, 16 * tmp, 0, 16, 16, 16 * 9 + 8, 16 * 12);
        break;
    default:
        break;
    }
}
