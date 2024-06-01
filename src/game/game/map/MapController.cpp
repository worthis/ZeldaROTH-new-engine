#include "MapController.h"

MapController::MapController() {
}

MapController::~MapController() {
}

void MapController::launch() {
    switch (step) {
        case MAP_OVERWORLD : overworld.launch(); break;
        case MAP_DONJON : donjon.launch(); break;
    }
}

void MapController::handleActions(Action* action) {
    switch (step) {
        case MAP_OVERWORLD : overworld.handleActions(action); break;
        case MAP_DONJON : donjon.handleActions(action); break;
    }
}

void MapController::loop() {
    switch (step) {
        case MAP_OVERWORLD : overworld.loop(); break;
        case MAP_DONJON : donjon.loop(); break;
    }
}

void MapController::draw() {
    switch (step) {
        case MAP_OVERWORLD : overworld.draw(); break;
        case MAP_DONJON : donjon.draw(); break;
    }
}

void MapController::setStep(int mapId, bool withTp) {
    if (mapId < 12) {
        step = MAP_OVERWORLD;
    } else {
        step = MAP_DONJON;
    }
}
