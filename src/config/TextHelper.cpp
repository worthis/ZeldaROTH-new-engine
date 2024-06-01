#include "TextHelper.h"

#include "../engine/resources/ResourceManager.h"

#include "../game/MainController.h"
#include "../game/keys/KeyBinder.h"

TextHelper::TextHelper()
{
    setWSpace(6);
    setWSize(8);
    setHSize(16);
    image = ResourceManager::getInstance()->loadImage("data/images/texts/font.png", true);
    setImage(image);
}

TextHelper::~TextHelper()
{
    ResourceManager::getInstance()->free(image);
}

void TextHelper::setLanguage(int i)
{
    switch (i)
    {
    case 0:
        setTextfile("data/texts/french.txt");
        break;
    case 1:
        setTextfile("data/texts/english.txt");
        break;
    case 2:
        setTextfile("data/texts/spanish.txt");
        break;
    default:
        setTextfile("data/texts/english.txt");
        break;
    }
}

string TextHelper::getVariableValue(int textId, int varId)
{
    ostringstream os;
    int tmp;

    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Link *link = scene->getLink();
    Inventory *inventory = link->getInventory();
    Status *status = link->getStatus();

    switch (textId)
    {
    case 89:
        tmp = 4 - inventory->nbQuartCoeur();
        os << tmp;
        return os.str();
    case 207:
        tmp = 7 - inventory->nbCristaux();
        os << tmp;
        return os.str();
    case 250:
        tmp = 7 - scene->getMonstersForPrice();
        os << tmp;
        return os.str();
    case 329:
    case 330:
        tmp = status->getNbDeaths();
        os << tmp;
        return os.str();
    case 331:
        tmp = inventory->totalQuartCoeur();
        os << tmp;
        return os.str();
    case 332:
        tmp = 18;

        if (inventory->hasObject(ARC_FEE))
            tmp++;
        if (inventory->hasObject(GANTS_2))
            tmp++;
        if (link->getBouclier())
            tmp++;
        if (inventory->hasObject(FLACON_1))
            tmp++;
        if (inventory->hasObject(FLACON_2))
            tmp++;
        if (inventory->hasObject(FLACON_2))
            tmp++;
        if (link->getEpee() == 5)
            tmp++;
        if (status->getMaxMagic() == 64)
            tmp++;

        for (int i = 0; i < 3; i++)
        {
            if (inventory->hasMedaillons(i))
                tmp++;
        }

        for (int i = 1; i < NB_COFFRES; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (scene->getCoffre(i, j))
                    tmp++;
            }
        }

        os << tmp;
        return os.str();
    case 333:
        tmp = 0;
        for (int i = 0; i < NB_MONSTERS; i++)
        {
            if (scene->getMonsters(i))
                tmp++;
        }
        os << tmp;
        return os.str();
    case 334:
        tmp = MainController::getInstance()->getGameController()->getSave()->getCompletion();
        os << tmp;
        return os.str();
    }
    return "";
}

string TextHelper::getCommonValue(string tag)
{
    if (tag == "EPEE")
    {
        Text *tmp = KeyBinder::getInstance()->getTextForType(BT_EPEE);
        string result = tmp->getText();
        delete tmp;
        return result;
    }
    if (tag == "CARTE")
    {
        Text *tmp = KeyBinder::getInstance()->getTextForType(BT_CARTE);
        string result = tmp->getText();
        delete tmp;
        return result;
    }
    if (tag == "ACTION")
    {
        Text *tmp = KeyBinder::getInstance()->getTextForType(BT_ACTION);
        string result = tmp->getText();
        delete tmp;
        return result;
    }
    if (tag == "MONSTERS")
    {
        Text *tmp = KeyBinder::getInstance()->getTextForType(BT_MONSTERS);
        string result = tmp->getText();
        delete tmp;
        return result;
    }
    if (tag == "center")
    {
        return "[center]";
    }
    else if (tag == "/center")
    {
        return "[/center]";
    }
    return "";
}
