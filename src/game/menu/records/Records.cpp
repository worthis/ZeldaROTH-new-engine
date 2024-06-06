#include "Records.h"

#include "../../MainController.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/audio/AudioManager.h"
#include "../../../engine/texts/TextManager.h"
#include "../../../config/ConfigurationManager.h"
#include "../../GlobalSave.h"

Records::Records() : full(false), rush(false), ultime(false), line(3), column(0),
                     helpFull(false), helpRush(false), helpUltime(false), confirm(false), subLine(1), skin(0)
{

    image = ResourceManager::getInstance()->loadImage("data/images/menus/cadres.png");
    link = ResourceManager::getInstance()->loadImage("data/images/menus/curseur.png", true);
    fairy = ResourceManager::getInstance()->loadImage("data/images/menus/fee.png", true);
    rangs = ResourceManager::getInstance()->loadImage("data/images/menus/rangs.png");

    for (int i = 0; i < 22; i++)
    {
        texts[i] = 0;
    }
}

Records::~Records()
{
    ResourceManager::getInstance()->free(image);
    ResourceManager::getInstance()->free(link);
    ResourceManager::getInstance()->free(fairy);
    ResourceManager::getInstance()->free(rangs);

    for (int i = 0; i < 22; i++)
    {
        delete texts[i];
    }
}

void Records::init()
{

    for (int i = 0; i < 22; i++)
    {
        delete texts[i];
    }

    texts[0] = TextManager::getInstance()->getText(3);
    texts[1] = TextManager::getInstance()->getText(60);
    texts[2] = TextManager::getInstance()->getText(61);
    texts[3] = TextManager::getInstance()->getText(62);
    texts[4] = TextManager::getInstance()->getText(63);
    texts[5] = TextManager::getInstance()->getText(13);
    texts[6] = TextManager::getInstance()->getText(5);

    skin = ConfigurationManager::getInstance()->getSkin();

    confirm = false;

    GlobalSave *gs = GlobalSave::getInstance();
    full = gs->isFull();
    ultime = gs->isUltime();
    rush = gs->isRush();

    int time = gs->getBestTime();
    if (time == -1)
    {
        texts[7] = new Text("??:??:??");
    }
    else
    {
        ostringstream os;
        int hours = time / 3600;
        int minutes = (time % 3600) / 60;
        int seconds = time % 60;
        if (hours < 10)
            os << "0";
        os << hours << ":";
        if (minutes < 10)
            os << "0";
        os << minutes << ":";
        if (seconds < 10)
            os << "0";
        os << seconds;
        texts[7] = new Text(os.str());
    }

    texts[8] = TextManager::getInstance()->getText(7);
    texts[9] = TextManager::getInstance()->getText(8);
    texts[10] = TextManager::getInstance()->getText(9);

    texts[11] = TextManager::getInstance()->getText(full ? 65 : 64);
    texts[12] = TextManager::getInstance()->getText(ultime ? 66 : 64);
    texts[13] = TextManager::getInstance()->getText(rush ? 67 : 64);

    texts[14] = TextManager::getInstance()->getText(68);
    texts[15] = TextManager::getInstance()->getText(69);
    texts[16] = TextManager::getInstance()->getText(70);
    texts[17] = TextManager::getInstance()->getText(71);
    texts[18] = TextManager::getInstance()->getText(72);
    texts[19] = TextManager::getInstance()->getText(73);
    texts[20] = TextManager::getInstance()->getText(74);
    texts[21] = TextManager::getInstance()->getText(75);

    subLine = 1;
}

void Records::handleEvents(Event *event)
{
    if (event->isPushed(KeyBinder::getInstance()->getKey(BT_ACTION)))
    {
        MainController::getInstance()->getMenuController()->setStep(MENU_MAIN);
        AudioManager::getInstance()->playSound(TS_MENU2);
        return;
    }

    if (event->isPushed(kReturn) || event->isPushed(kSpace))
    {
        if (helpFull)
        {
            helpFull = false;
            AudioManager::getInstance()->playSound(TS_MENU2);
        }
        else if (helpUltime)
        {
            helpUltime = false;
            AudioManager::getInstance()->playSound(TS_MENU2);
        }
        else if (helpRush)
        {
            helpRush = false;
            AudioManager::getInstance()->playSound(TS_MENU2);
        }
        else if (confirm)
        {
            if (subLine == 0)
            {
                GlobalSave::getInstance()->erase();
                init();
            }
            subLine = 1;
            confirm = false;
            AudioManager::getInstance()->playSound(TS_MENU2);
        }
        else if (line == 0)
        {
            helpFull = true;
            AudioManager::getInstance()->playSound(TS_MENU1);
        }
        else if (line == 1)
        {
            helpUltime = true;
            AudioManager::getInstance()->playSound(TS_MENU1);
        }
        else if (line == 2)
        {
            helpRush = true;
            AudioManager::getInstance()->playSound(TS_MENU1);
        }
        else if (line == 3)
        {
            if (column == 0)
            {
                MainController::getInstance()->getMenuController()->setStep(MENU_MAIN);
                AudioManager::getInstance()->playSound(TS_MENU2);
            }
            else
            {
                confirm = true;
                AudioManager::getInstance()->playSound(TS_MENU1);
            }
        }
        return;
    }

    if (event->isPushed(kUp) && !helpFull && !helpUltime && !helpRush)
    {
        if (confirm)
        {
            subLine--;
            if (subLine < 0)
                subLine = 1;
        }
        else
        {
            line--;
            if (line < 0)
                line = 3;
            column = 0;
        }
        AudioManager::getInstance()->playSound(TS_MENU3);
    }
    if (event->isPushed(kDown) && !helpFull && !helpUltime && !helpRush)
    {
        if (confirm)
        {
            subLine++;
            if (subLine > 1)
                subLine = 0;
        }
        else
        {
            line++;
            if (line > 3)
                line = 0;
            column = 0;
        }
        AudioManager::getInstance()->playSound(TS_MENU3);
    }
    if (!confirm && event->isPushed(kLeft) && line == 3)
    {
        column--;
        if (column < 0)
            column = 1;
        AudioManager::getInstance()->playSound(TS_MENU3);
    }
    if (!confirm && event->isPushed(kRight) && line == 3)
    {
        column++;
        if (column > 1)
            column = 0;
        AudioManager::getInstance()->playSound(TS_MENU3);
    }
}

void Records::drawCadre(int x, int y, int w, int h)
{
    // center
    for (int j = y + 16; j < y + h - 16; j += 16)
    {
        for (int i = x + 16; i < x + w - 16; i += 16)
        {
            WindowManager::getInstance()->draw(image, 16, 64, 16, 16, i, j);
        }
    }

    // top and bottom
    for (int i = x + 16; i < x + w - 16; i += 16)
    {
        WindowManager::getInstance()->draw(image, 16, 48, 16, 16, i, y);
        WindowManager::getInstance()->draw(image, 16, 80, 16, 16, i, y + h - 16);
    }

    // left and right
    for (int j = y + 16; j < y + h - 16; j += 16)
    {
        WindowManager::getInstance()->draw(image, 0, 64, 16, 16, x, j);
        WindowManager::getInstance()->draw(image, 32, 64, 16, 16, x + w - 16, j);
    }

    // top left corner
    WindowManager::getInstance()->draw(image, 0, 48, 16, 16, x, y);

    // top right corner
    WindowManager::getInstance()->draw(image, 32, 48, 16, 16, x + w - 16, y);

    // bottom left corner
    WindowManager::getInstance()->draw(image, 0, 80, 16, 16, x, y + h - 16);

    // bottom right corner
    WindowManager::getInstance()->draw(image, 32, 80, 16, 16, x + w - 16, y + h - 16);
}

void Records::drawTitle()
{
    int letterSize = TextManager::getInstance()->getWSpace();
    int size = texts[0]->getLength() * letterSize;
    int blocs = (size + 15) / 16;

    int x = 16;
    WindowManager::getInstance()->draw(image, 0, 0, 16, 16, x, 0);
    WindowManager::getInstance()->draw(image, 0, 16, 16, 16, x, 16);
    WindowManager::getInstance()->draw(image, 0, 32, 16, 16, x, 32);

    for (int i = 0; i <= blocs; i++)
    {
        x += 16;
        WindowManager::getInstance()->draw(image, 16, 0, 16, 16, x, 0);
        WindowManager::getInstance()->draw(image, 16, 64, 16, 16, x, 16);
        WindowManager::getInstance()->draw(image, 16, 32, 16, 16, x, 32);
    }

    x += 16;
    WindowManager::getInstance()->draw(image, 32, 0, 16, 16, x, 0);
    WindowManager::getInstance()->draw(image, 32, 16, 16, 16, x, 16);
    WindowManager::getInstance()->draw(image, 32, 32, 16, 16, x, 32);

    texts[0]->display(32 + 8 + ((blocs * 16) - size) / 2, 16);
}

void Records::drawPage()
{
    for (int j = 0; j < 15; j++)
    {
        for (int i = 0; i < 20; i++)
        {
            WindowManager::getInstance()->draw(image, 16, 16, 16, 16, i * 16, j * 16);
        }
    }

    drawTitle();

    drawCadre(128, 8, 176, 32);
    drawCadre(16, 48, 240, 32);
    drawCadre(272, 48, 32, 32);
    drawCadre(16, 96, 240, 32);
    drawCadre(272, 96, 32, 32);
    drawCadre(16, 144, 240, 32);
    drawCadre(272, 144, 32, 32);
    drawCadre(16, 192, 136, 32);
    drawCadre(168, 192, 136, 32);

    int letterSize = TextManager::getInstance()->getWSpace();
    int size = texts[1]->getLength() * letterSize;
    texts[1]->display(140, 16);
    texts[7]->display(140 + size + letterSize, 16);

    texts[2]->display(44, 56);
    texts[3]->display(44, 104);
    texts[4]->display(44, 152);

    WindowManager::getInstance()->draw(rangs, full ? 0 : 17, 0, 17, 16, 280, 56);
    WindowManager::getInstance()->draw(rangs, ultime ? 0 : 17, 0, 17, 16, 280, 104);
    WindowManager::getInstance()->draw(rangs, rush ? 0 : 17, 0, 17, 16, 280, 152);

    // back
    size = texts[5]->getLength() * letterSize;
    texts[5]->display(16 + (136 - size) / 2, 200);

    // delete
    size = texts[6]->getLength() * letterSize;
    texts[6]->display(168 + (136 - size) / 2, 200);
}

void Records::drawFull()
{
    int letterSize = TextManager::getInstance()->getWSpace();
    int sizeMax = texts[11]->getLength() * letterSize;
    int size = texts[14]->getLength() * letterSize;
    if (sizeMax < size)
        sizeMax = size;

    int blocs = ((sizeMax + 15) / 16) + 1;

    drawCadre((320 - (blocs * 16)) / 2, 120 - 24, blocs * 16, 48);
    texts[11]->display((320 - (blocs * 16)) / 2 + 8, 120 - 24 + 8);
    texts[14]->display((320 - (blocs * 16)) / 2 + 8, 120 - 24 + 8 + 16);
}

void Records::drawUltime()
{
    int letterSize = TextManager::getInstance()->getWSpace();
    int sizeMax = texts[12]->getLength() * letterSize;
    for (int i = 15; i < 20; i++)
    {
        int size = texts[i]->getLength() * letterSize;
        if (sizeMax < size)
            sizeMax = size;
    }

    int blocs = ((sizeMax + 15) / 16) + 1;

    drawCadre((320 - (blocs * 16)) / 2, 120 - 56, blocs * 16, 112);
    texts[12]->display((320 - (blocs * 16)) / 2 + 8, 120 - 56 + 8);
    for (int i = 15; i < 20; i++)
    {
        texts[i]->display((320 - (blocs * 16)) / 2 + 8, 120 - 56 + 8 + 16 * (i - 14));
    }
}

void Records::drawRush()
{
    int letterSize = TextManager::getInstance()->getWSpace();
    int sizeMax = texts[13]->getLength() * letterSize;
    for (int i = 20; i < 22; i++)
    {
        int size = texts[i]->getLength() * letterSize;
        if (sizeMax < size)
            sizeMax = size;
    }

    int blocs = ((sizeMax + 15) / 16) + 1;

    drawCadre((320 - (blocs * 16)) / 2, 120 - 32, blocs * 16, 64);
    texts[13]->display((320 - (blocs * 16)) / 2 + 8, 120 - 32 + 8);
    texts[20]->display((320 - (blocs * 16)) / 2 + 8, 120 - 32 + 8 + 16);
    texts[21]->display((320 - (blocs * 16)) / 2 + 8, 120 - 32 + 8 + 16 * 2);
}

void Records::drawConfirm()
{
    int letterSize = TextManager::getInstance()->getWSpace();
    drawCadre(104, 84, 112, 72);
    // delete
    int size = texts[8]->getLength() * letterSize;
    texts[8]->display(104 + (112 - size) / 2, 9 + 84);

    // yes
    size = texts[9]->getLength() * letterSize;
    texts[9]->display(104 + (112 - size) / 2, 29 + 84);

    // no
    size = texts[10]->getLength() * letterSize;
    texts[10]->display(104 + (112 - size) / 2, 49 + 84);
}

void Records::draw()
{
    drawPage();

    WindowManager::getInstance()->draw(link, skin * 16, 0, 16, 21, 26 + 152 * column, 53 + 48 * line);

    if (helpFull)
    {
        drawFull();
    }
    if (helpUltime)
    {
        drawUltime();
    }
    if (helpRush)
    {
        drawRush();
    }
    if (confirm)
    {
        drawConfirm();
        WindowManager::getInstance()->draw(fairy, 0, 0, 16, 16, 112, 113 + 20 * subLine);
    }
}
