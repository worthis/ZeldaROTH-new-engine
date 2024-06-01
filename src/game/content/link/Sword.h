/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __SWORD_H__
#define __SWORD_H__

#include "../../../engine/common/Common.h"

#include "../../../engine/resources/WImage.h"

#include "../CommonGame.h"

class Sword {
    public :
        Sword(int i);
        ~Sword();

        bool hit(int offsetX, int offsetY, Direction dir, Animation anim, int step, int charge, int forceTotal);
        void draw(int offsetX, int offsetY, Direction dir, Animation anim, int step, int charge);

        int getForce();

    private :

        void drawHit(int offsetX, int offsetY, Direction dir, int step);
        void drawSpin(int offsetX, int offsetY, Direction dir, int step);
        void drawCharge(int offsetX, int offsetY, Direction dir, bool move, int step, int charge);

        int force;

        WImage* image;
        WImage* effects;
};

#endif  // Sword.h
