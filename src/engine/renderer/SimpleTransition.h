/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __SIMPLETRANSITION_H__
#define __SIMPLETRANSITION_H__

#include "../common/Common.h"

#include <SDL/SDL.h>

class SimpleTransition
{
public:
    SimpleTransition();
    ~SimpleTransition();

    void loop();
    void draw();

    bool isRunning();

    void start();

    bool isWaiting();

    void restart();

    bool isAchieved();

    void reset();

private:
    SDL_Surface *rect;
    bool run;
    int step;
    int alpha;
};

#endif // SimpleTransition.h
