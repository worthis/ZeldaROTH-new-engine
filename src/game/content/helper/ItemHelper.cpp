#include "ItemHelper.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

#include "../items/PetitCoeur.h"
#include "../items/RubisVert.h"
#include "../items/RubisBleu.h"
#include "../items/RubisRouge.h"
#include "../items/Arrow.h"
#include "../items/Bomb.h"
#include "../items/MagiePetit.h"
#include "../items/MagieGrand.h"
#include "../items/QuartCoeur.h"
#include "../items/PetiteCle.h"
#include "../items/PetiteEpee.h"
#include "../items/GrandeEpee.h"
#include "../items/Cristal.h"
#include "../items/Triforce.h"

ItemHelper ItemHelper::instance = ItemHelper();

ItemHelper::ItemHelper() : image(0)
{
}

ItemHelper::~ItemHelper()
{
}

void ItemHelper::close()
{
    ResourceManager::getInstance()->free(image);
}

ItemHelper *ItemHelper::getInstance()
{
    return &instance;
}

Item *ItemHelper::createItem(TypeItem type, int x, int y, int id, bool withAnim)
{
    y -= 8;
    switch (type)
    {
    case TI_BOMBE:
        return new Bomb(x - 6, y);
    case TI_FLECHE:
        return new Arrow(x - 2, y);
    case TI_MAGIE_BEAUCOUP:
        return new MagieGrand(x - 4, y);
    case TI_MAGIE_PEU:
        return new MagiePetit(x - 4, y);
    case TI_PETIT_COEUR:
        return new PetitCoeur(x - 4, y);
    case TI_QUART_COEUR:
        return new QuartCoeur(x - 8, y, id);
    case TI_RUBIS_BLEU:
        return new RubisBleu(x - 4, y);
    case TI_RUBIS_ROUGE:
        return new RubisRouge(x - 4, y);
    case TI_RUBIS_VERT:
        return new RubisVert(x - 4, y);
    case TI_CLE:
        return new PetiteCle(x - 4, y, id);
    case TI_EPEE_1:
        return new PetiteEpee(x - 4, y);
    case TI_EPEE_5:
        return new GrandeEpee(x - 5, y - 6);
    case TI_CRISTAL:
        return new Cristal(x - 6, y, id);
    case TI_TRIFORCE:
        return new Triforce(x - 13, y - 5);
    default:
        return 0;
    }
}

void ItemHelper::drawItem(TypeItem type, int x, int y)
{
    if (image == 0)
    {
        image = ResourceManager::getInstance()->loadImage("data/images/items/items.png", true);
    }

    switch (type)
    {
    case TI_QUART_COEUR:
        WindowManager::getInstance()->draw(image, 45, 0, 16, 14, x - 8, y - 7);
        break;
    case TI_FLACON_1:
    case TI_FLACON_2:
    case TI_FLACON_3:
        WindowManager::getInstance()->draw(image, 30, 14, 16, 16, x - 8, y - 8);
        break;
    case TI_CRISTAL:
        WindowManager::getInstance()->draw(image, 30, 30, 16, 16, x - 8, y - 8);
        break;
    case TI_BOUCLIER_1:
        WindowManager::getInstance()->draw(image, 0, 95, 8, 10, x - 4, y - 5);
        break;
    case TI_EPEE_1:
        WindowManager::getInstance()->draw(image, 36, 95, 6, 16, x - 3, y - 8);
        break;
    case TI_EPEE_3:
        WindowManager::getInstance()->draw(image, 42, 95, 6, 16, x - 3, y - 8);
        break;
    case TI_EPEE_5:
        WindowManager::getInstance()->draw(image, 48, 95, 7, 16, x - 3, y - 8);
        break;
    case TI_CARTE_DONJON:
        WindowManager::getInstance()->draw(image, 32, 63, 16, 16, x - 8, y - 8);
        break;
    case TI_GANT:
        WindowManager::getInstance()->draw(image, 64, 0, 16, 16, x - 8, y - 8);
        break;
    case TI_GANT2:
        WindowManager::getInstance()->draw(image, 64, 16, 16, 16, x - 8, y - 8);
        break;
    case TI_ARC:
        WindowManager::getInstance()->draw(image, 64, 32, 16, 16, x - 8, y - 8);
        break;
    case TI_ARC_FEE:
        WindowManager::getInstance()->draw(image, 64, 48, 16, 16, x - 8, y - 8);
        break;
    case TI_PALMES:
        WindowManager::getInstance()->draw(image, 30, 46, 16, 17, x - 8, y - 9);
        break;
    case TI_MARTEAU:
        WindowManager::getInstance()->draw(image, 64, 96, 16, 16, x - 8, y - 8);
        break;
    case TI_LANTERNE:
        WindowManager::getInstance()->draw(image, 80, 0, 16, 16, x - 8, y - 8);
        break;
    case TI_POTION_ROUGE:
        WindowManager::getInstance()->draw(image, 112, 0, 16, 16, x - 8, y - 8);
        break;
    case TI_POTION_VERTE:
        WindowManager::getInstance()->draw(image, 112, 16, 16, 16, x - 8, y - 8);
        break;
    case TI_POTION_BLEUE:
        WindowManager::getInstance()->draw(image, 112, 48, 16, 16, x - 8, y - 8);
        break;
    case TI_BOUSSOLE:
        WindowManager::getInstance()->draw(image, 96, 16, 16, 16, x - 8, y - 8);
        break;
    case TI_CLE_BOSS:
        WindowManager::getInstance()->draw(image, 96, 32, 16, 16, x - 8, y - 8);
        break;
    case TI_CLE:
        WindowManager::getInstance()->draw(image, 96, 48, 16, 16, x - 8, y - 8);
        break;
    case TI_GRAPPIN:
        WindowManager::getInstance()->draw(image, 96, 64, 16, 16, x - 8, y - 8);
        break;
    case TI_BAGUETTE_FEU:
        WindowManager::getInstance()->draw(image, 96, 96, 16, 16, x - 8, y - 8);
        break;
    case TI_RUBIS_ROUGE:
        WindowManager::getInstance()->draw(image, 0, 35, 8, 14, x - 4, y - 7);
        break;
    case TI_BAGUETTE_GLACE:
        WindowManager::getInstance()->draw(image, 128, 16, 16, 16, x - 8, y - 8);
        break;
    case TI_TRIFORCE:
        WindowManager::getInstance()->draw(image, 128, 86, 26, 26, x - 13, y - 16);
        break;
    case TI_LIVRE:
        WindowManager::getInstance()->draw(image, 128, 70, 16, 16, x - 8, y - 8);
        break;
    case TI_MEDAILLON_1:
        WindowManager::getInstance()->draw(image, 144, 0, 16, 16, x - 8, y - 8);
        break;
    case TI_MEDAILLON_2:
        WindowManager::getInstance()->draw(image, 144, 16, 16, 16, x - 8, y - 8);
        break;
    case TI_MEDAILLON_3:
        WindowManager::getInstance()->draw(image, 144, 32, 16, 16, x - 8, y - 8);
        break;
    default:
        return;
    }
}
