/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __PIEGEPICS_H__
#define __PIEGEPICS_H__

#include "../types/Object.h"

class PiegePics : public Object
{
public:
    PiegePics(int x, int y, Direction dir);
    ~PiegePics();

    void loop();

    void draw(int offsetX, int offsetY);

    BoundingBox *getBoundingBox();

    bool isResetable();
    void reset();

private:
    void moveX(int dx);
    void moveY(int dy);

    Direction direction;

    int x0;
    int y0;
    Direction dir0;

    int force;
};

#endif // PiegePics.h
