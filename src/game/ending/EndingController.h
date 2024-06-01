/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENDINGCONTROLLER_H__
#define __ENDINGCONTROLLER_H__

#include "../../engine/common/Common.h"
#include "../../engine/window/Event.h"

#include "../../engine/renderer/SimpleTransition.h"

#include "story/StoryController.h"
#include "score/ScoreController.h"
#include "credits/CreditsController.h"
#include "final/FinalController.h"

enum EndingStep
{
    END_STORY,
    END_SCORE,
    END_CREDITS,
    END_END
};

class EndingController
{
public:
    EndingController();
    ~EndingController();

    void launch();

    void handleEvents(Event *event);
    void loop();
    void draw();

    void setStep(EndingStep newStep);

private:
    void setInternalStep(EndingStep newStep); // set step without transition

    EndingStep step;
    EndingStep nextStep;

    SimpleTransition transition;

    StoryController story;
    ScoreController score;
    CreditsController credits;
    FinalController final;
};

#endif // EndingController.h
