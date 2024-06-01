#include "AnimationInGame.h"

#include "../../../game/MainController.h"
#include "../../../engine/audio/AudioManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/resources/ResourceManager.h"

//#include "../objects/Pnj.h"

AnimationInGame::AnimationInGame() : id(0), anim(0), running(false)  {
    image = ResourceManager::getInstance()->loadImage("data/images/intro/nuit.png");
}

AnimationInGame::~AnimationInGame() {
    ResourceManager::getInstance()->free(image);
}

void AnimationInGame::testAnim() {

    if (running) {
        return;
    }

    Avancement avancement = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getAvancement();

    link = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink();
    map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();

    switch (avancement) {
        case AV_ZELDA_MARCHE :
            startAnim(1);
            break;
        case AV_START :
            startAnim(2);
            break;
        default : break;
    }
}

void AnimationInGame::startAnim(int i) {
    id = i;

    link = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink();
    map = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap();
    camera = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getCamera();

    lmap = false;
    lcamera = false;
    llink = false;

    switch (id) {
        case 1 :
            lmap = true;
            break;
        case 2 :
            AudioManager::getInstance()->stopMusic();
            MainController::getInstance()->getGameController()->displayText(81);
            break;
        default : break;
    }

    running = true;
    anim = 0;
}

void AnimationInGame::loop() {
    if (!running) {
        return;
    }
}

void AnimationInGame::draw() {
    if (!running) {
        return;
    }

    switch (id) {
        case 2 :
            WindowManager::getInstance()->draw(image, 0, 0, 320, 240, 0, 0);
            break;
        default :
            break;
    }
}

void AnimationInGame::drawAfterHud() {
    if (!running) {
        return;
    }

    /*switch (id) {
        case 45 :
            transition.draw();
            break;
    }*/
}

int AnimationInGame::getSpecialMusicId() {
    if (!running) {
        return 0;
    }

    switch (id) {
        //case 1 : return 2;
        default : return 0;
    }
}

bool AnimationInGame::isRunning() {
    return running;
}

bool AnimationInGame::loopMap() {
    return !running || lmap;
}

bool AnimationInGame::loopCamera() {
    return !running || lcamera;
}

bool AnimationInGame::loopLink() {
    return !running || llink;
}

void AnimationInGame::stop() {
    running = false;
}
