/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __PETITEEPEE_H__
#define __PETITEEPEE_H__

#include "../types/Item.h"

class PetiteEpee : public Item {
    public :
        PetiteEpee(int x, int y);
        ~PetiteEpee();

        void draw(int offsetX, int offsetY);

        void action();

        bool isPickable();

};

#endif  // PetiteEpee.h
