/*

    Zelda Navi's Quest

    Copyright (C) 2013-2014  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __FUMEEROSE_H__
#define __FUMEEROSE_H__

#include "../../../engine/common/Common.h"

#include "../../../engine/resources/WImage.h"

#include "../../../engine/util/time/Chrono.h"

#include "../CommonGame.h"

#include "../types/Effect.h"

class FumeeRose : public Effect
{
public:
    FumeeRose(int x, int y);
    ~FumeeRose();

    void loop();
    void draw(int offsetX, int offsetY);

    int getX();
    int getY();

private:
    int x;
    int y;

    int anim;
    int animMax;
    int vanim;

    WImage *image;

    Chrono chrono;
};

#endif // FumeeRose.h
