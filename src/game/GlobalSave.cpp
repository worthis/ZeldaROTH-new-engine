#include "GlobalSave.h"

GlobalSave GlobalSave::instance = GlobalSave();

GlobalSave *GlobalSave::getInstance()
{
    return &instance;
}
GlobalSave::GlobalSave()
{
    init();
    load();
}

GlobalSave::~GlobalSave()
{
}

void GlobalSave::init()
{
    full = false;
    ultime = false;
    rush = false;
    bestTime = -1;
}

void GlobalSave::load()
{
    ifstream f("saves/records.dat", ios::in | ios::binary);
    if (!f.is_open())
    {
        return;
    }
    f.read((char *)&full, sizeof(bool));
    f.read((char *)&ultime, sizeof(bool));
    f.read((char *)&rush, sizeof(bool));
    f.read((char *)&bestTime, sizeof(int));

    f.close();
}

void GlobalSave::save()
{
    ofstream f("saves/records.dat", ios::out | ios::binary);
    f.write((char *)&full, sizeof(bool));
    f.write((char *)&ultime, sizeof(bool));
    f.write((char *)&rush, sizeof(bool));
    f.write((char *)&bestTime, sizeof(int));
    f.close();
}

void GlobalSave::erase()
{
    remove("saves/records.dat");
    init();
}

void GlobalSave::update(Save *sv, bool endGame)
{
    bool needToSave = false;

    if (endGame)
    {
        if (!full && sv->getCompletion() == 100)
        {
            full = true;
            needToSave = true;
        }
        if (!ultime && !sv->getDeaths() && sv->getMaxLife() <= 20 && !sv->getMedaillons(0) && !sv->getMedaillons(1) && !sv->getMedaillons(2) && sv->getMaxMagic() <= 32 && !sv->getFlacons(0) && !sv->getFlacons(1) && !sv->getFlacons(2) && !sv->getBouclier())
        {
            ultime = true;
            needToSave = true;
        }
        if (sv->getTime() < bestTime || bestTime == -1)
        {
            bestTime = sv->getTime();
            if (!rush && bestTime < 7200)
            {
                rush = true;
            }
            needToSave = true;
        }
    }

    if (needToSave)
    {
        save();
    }
}

bool GlobalSave::isFull()
{
    return full;
}

bool GlobalSave::isUltime()
{
    return ultime;
}

bool GlobalSave::isRush()
{
    return rush;
}

int GlobalSave::getBestTime()
{
    return bestTime;
}
