#include "Interrupteur.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"

#include "../../MainController.h"

Interrupteur::Interrupteur(int i, int j, int id, bool down, Map* mp, bool us) : type(id), used(down), usedTmp(false), map(mp), usable(us) {
    x = i;
    y = j;

    // for quadtree operations:
    width = 16;
    height = 16;

    // no collisions
    box.setX(0);
    box.setY(0);
    box.setW(-1);
    box.setH(-1);

    wasUsable = usable;

    // init map with motif and collisions
    if (usable) {
        displayOnMap();
    }

}

Interrupteur::~Interrupteur() {
}

void Interrupteur::loop() {
    if (used || !usable) {
        return;
    }

    BoundingBox bb(x + 4, y + 4, 8, 8);
    Link* link = MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink();

    if (!map->checkCollisions(&bb, this, false, false, false, false, true)
        || bb.intersect(link->getBoundingBox())) {
        if (type != 2) used = true; else usedTmp = true;
        map->activateInter(x, y);
        map->setSol(x, y, 2028, PIERRE);
    }
}

void Interrupteur::draw(int offsetX, int offsetY) {
}

bool Interrupteur::isResetable() {
    return !wasUsable;
}

void Interrupteur::reset() {
    usable = wasUsable;
}

void Interrupteur::displayOnMap() {
    usable = true;
    map->setSol(x, y, used ? 2028 : 2027, PIERRE);
}
