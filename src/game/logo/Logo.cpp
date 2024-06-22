#include "Logo.h"

#include "../MainController.h"
#include "../../engine/window/WindowManager.h"
#include "../../engine/resources/ResourceManager.h"
#include "../../engine/audio/AudioManager.h"

#include "../../config/ConfigurationManager.h"

Logo::Logo() : anim(0), animMax(15), vanim(60), first(true)
{
    currentLogoFond = getLogoFond();

    image = ResourceManager::getInstance()->loadImage(currentLogoFond);
    imageLogo = ResourceManager::getInstance()->loadImage("data/images/logos/logo.png");
}

Logo::~Logo()
{
    ResourceManager::getInstance()->free(image);
    ResourceManager::getInstance()->free(imageLogo);
}

void Logo::init()
{
    string newLogoFond = getLogoFond();

    if (currentLogoFond != newLogoFond)
    {
        currentLogoFond = newLogoFond;
        ResourceManager::getInstance()->free(image);
        image = ResourceManager::getInstance()->loadImage(currentLogoFond);
    }

    anim = 0;
    chrono.reset();
}

void Logo::handleEvents(Event *event)
{
    if (anim < animMax)
        return;
    if (event->isPushed(kReturn) || event->isPushed(kSpace))
    {
        AudioManager::getInstance()->playSound(TS_MENU1);
        MainController::getInstance()->setStep(TITRE);
    }
}

void Logo::loop()
{
    if (anim == animMax)
        return;
    if (first)
    {
        if (chrono.getElapsedTime() >= 500)
        {
            first = false;
            chrono.reset();
        }
        return;
    }
    if (chrono.getElapsedTime() >= vanim)
    {
        anim++;
        chrono.reset();
    }
}

void Logo::draw()
{
    if (first)
        return;
    WindowManager::getInstance()->draw(image, 0, 0, 320, 240, 0, 0);

    WindowManager::getInstance()->draw(imageLogo, 144 * (anim % 4), 144 * (anim / 4), 144, 144, 88, 60);
}

const string Logo::getLogoFond()
{
    if (ConfigurationManager::getInstance()->isFrench())
    {
        return "data/images/logos/logo_fond.png";
    }

    if (ConfigurationManager::getInstance()->isRussian())
    {
        return "data/images/logos/logo_fond_ru.png";
    }

    return "data/images/logos/logo_fond_us.png";
}
