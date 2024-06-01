/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __GRANDEEPEE_H__
#define __GRANDEEPEE_H__

#include "../types/Item.h"

class GrandeEpee : public Item {
    public :
        GrandeEpee(int x, int y);
        ~GrandeEpee();

        void draw(int offsetX, int offsetY);

        void action();

        bool isPickable();

};

#endif  // GrandeEpee.h
