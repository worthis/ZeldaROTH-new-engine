/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __HUD_H__
#define __HUD_H__

#include "../../../engine/resources/WImage.h"

#include "../link/Status.h"
#include "../link/Inventory.h"

class Hud
{
public:
    Hud(Status *status, Inventory *inventory, int lang);
    ~Hud();

    void loop();
    void draw();

    void setBossLife(int life, int maxLife);
    void reset();

    void displayEtage();

private:
    void drawLife();
    void drawMagic();
    void drawItems();
    void drawObject();
    void drawBonus();
    void drawBoss();
    void drawEtage();

    void drawNombre(int val, int max, int x, int y, int nb);

    Status *status;
    Inventory *inventory;
    int currentLang;
    int animBoss;
    int bossLife;
    int bossMaxLife;
    bool removeBoss;
    int etage;
    int displayEtg;

    WImage *image;
    WImage *chiffres;
    WImage *level;
};

#endif // Hud.h
