#include "Score.h"

#include "../../MainController.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/texts/TextManager.h"
#include "../../../engine/audio/AudioManager.h"

Score::Score() {
    fond = ResourceManager::getInstance()->loadImage("data/images/ending/arbre.png");
    for (int i = 0; i < 12; i++) {
        texts[i] = 0;
    }
}

Score::~Score() {
    ResourceManager::getInstance()->free(fond);
    for (int i = 0; i < 12; i++) {
        delete texts[i];
    }
}

void Score::init() {

    for (int i = 0; i < 12; i++) {
        delete texts[i];
        texts[i] = 0;
    }

    Save* save = MainController::getInstance()->getGameController()->getSave();

    texts[0] = TextManager::getInstance()->getText(327);
    texts[1] = TextManager::getInstance()->getText(328);

    int time = save->getTime();

    ostringstream os;
    int hours = time / 3600;
    int minutes = (time % 3600) / 60;
    int seconds = time % 60;
    if (hours < 10) os << "0";
    os << hours << ":";
    if (minutes < 10) os << "0";
    os << minutes << ":";
    if (seconds < 10) os << "0";
    os << seconds;
    texts[2] = new Text(os.str());

    texts[3] = TextManager::getInstance()->getText(save->getDeaths() < 2 ? 329 : 330);

    texts[4] = TextManager::getInstance()->getText(331);

    texts[5] = TextManager::getInstance()->getText(332);

    texts[6] = TextManager::getInstance()->getText(333);

    texts[7] = TextManager::getInstance()->getText(334);


    Link* link = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink();
    Status* status = link->getStatus();
    Inventory* inventory = link->getInventory();

    if (status->getNbDeaths() == 0
        && status->getMaxLife() == 20
        && status->getMaxMagic() == 32
        && !inventory->hasObject(FLACON_1)
        && !inventory->hasObject(FLACON_2)
        && !inventory->hasObject(FLACON_3)
        && !inventory->hasMedaillons(0)
        && !inventory->hasMedaillons(1)
        && !inventory->hasMedaillons(2)
        && !link->getBouclier()) {

        texts[9] = TextManager::getInstance()->getText(336);

    } else {
        int completion = save->getCompletion();

        if (completion == 100) {
            texts[9] = TextManager::getInstance()->getText(361);
        } else if (completion >= 95) {
            texts[9] = TextManager::getInstance()->getText(337);
        } else if (completion >= 90) {
            texts[9] = TextManager::getInstance()->getText(338);
        } else if (completion >= 85) {
            texts[9] = TextManager::getInstance()->getText(339);
        } else {
            texts[9] = TextManager::getInstance()->getText(340);
        }
    }

    int line = 10;

    if (time < 7200) {
        texts[line++] = TextManager::getInstance()->getText(341);
    }

    if (status->getNbDeaths() >= 50) {
        texts[line] = TextManager::getInstance()->getText(342);
    } else if (status->getNbDeaths() >= 20) {
        texts[line] = TextManager::getInstance()->getText(343);
    }

    texts[8] = TextManager::getInstance()->getText(texts[10] ? 344 : 335);

}

void Score::handleActions(Action* action) {
    if (action->isAction(ACTION)) {
        AudioManager::getInstance()->playSound(TS_MENU1);
        MainController::getInstance()->getEndingController()->setStep(END_CREDITS);
    }
}

void Score::draw() {
    for (int j = 0; j < 3; j++) {
        for (int i = 0; i < 7; i++) {
            WindowManager::getInstance()->draw(fond, 0, 0, 48, 96, i * 48, j * 96);
        }
    }

    int letterSize = TextManager::getInstance()->getWSpace();

    // SCORES :
    Text* text = texts[0];
    int size = text->getLength() * letterSize;
    text->display(160 - (size / 2), 10);

    // TEMPS DE JEU :
    text = texts[1];
    size = text->getLength() * letterSize;
    text->display(10, 30);

    texts[2]->display(10 + size + letterSize, 30);

    // MORT N FOIS
    texts[3]->display(10, 50);

    // 1/4 COEURS
    texts[4]->display(10, 70);

    // OBJETS
    texts[5]->display(10, 90);

    // MONSTERS
    texts[6]->display(10, 110);

    // COMPLETION
    texts[7]->display(10, 130);

    // RANK
    texts[8]->display(10, 150);
    texts[9]->display(10, 170);
    if (texts[10]) texts[10]->display(10, 190);
    if (texts[11]) texts[11]->display(10, 210);

}
