/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __GLOBALSAVE_H__
#define __GLOBALSAVE_H__

#include "Save.h"

class GlobalSave {
    public :
        static GlobalSave* getInstance();

        void save();
        void erase();

        void update(Save* save, bool endGame);

        bool isFull();
        bool isUltime();
        bool isRush();
        int getBestTime();

    private :
        GlobalSave();
        ~GlobalSave();
        static GlobalSave instance;

        void init();
        void load();

        bool full;
        bool ultime;
        bool rush;
        int bestTime;

};

#endif  // GlobalSave.h
