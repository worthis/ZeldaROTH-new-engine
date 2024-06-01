/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __CRISTAL_H__
#define __CRISTAL_H__

#include "../types/Item.h"

class Cristal : public Item
{
public:
    Cristal(int x, int y, int id);
    ~Cristal();

    void loop();
    void draw(int offsetX, int offsetY);

    void action();

    bool isPickable();

private:
    int id;
};

#endif // Cristal.h
