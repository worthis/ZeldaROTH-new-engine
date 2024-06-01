#include "TalkableArea.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

#include "../../MainController.h"
#include "../../game/scene/Scene.h"

TalkableArea::TalkableArea(int i, int j, int txt) : texte(txt) {
    x = i;
    y = j;

    // for quadtree operations:
    width = 16;
    height = 16;

    box.setX(x);
    box.setY(y);
    box.setW(width);
    box.setH(height);
}

TalkableArea::~TalkableArea() {
}


void TalkableArea::loop() {}

void TalkableArea::draw(int offsetX, int offsetY) {}

bool TalkableArea::action(Direction dir) {
    MainController::getInstance()->getGameController()->displayText(getDynamicText());
    return true;
}

int TalkableArea::getDynamicText() {
    Scene* scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Link* link = scene->getLink();
    switch (texte) {
        case 282 :
            if (link->getStatus()->getVirtualLife() == link->getStatus()->getMaxLife()) {
                return 294;
            }
            break;
        case 284 :
            if (!link->getInventory()->hasObject(LANTERNE) || link->getStatus()->getVirtualMagic() == link->getStatus()->getMaxMagic()) {
                return 294;
            }
            break;
        case 286 :
            if (!link->getInventory()->hasObject(ARC) || link->getStatus()->getArrows() == link->getStatus()->getMaxArrows()) {
                return 294;
            }
            break;
        case 288 :
            if (link->getStatus()->getBombs() == link->getStatus()->getMaxBombs()) {
                return 294;
            }
            break;
        case 290 :
            if (link->getInventory()->hasObject(ARC)) {
                return 298;
            }
            if (scene->getAvancement() >= AV_MARCHANT_OK) {
                return 292;
            }
            break;
        default : break;
    }
    return texte;
}
