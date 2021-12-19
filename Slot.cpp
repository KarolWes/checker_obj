//
// Created by karolwes on 12.10.2021.
//


#include "Slot.h"

Slot::Slot(int size, float xDraw, float yDraw, int xId, int yId)
        : x_size(size), y_size(size), x_draw(xDraw), y_draw(yDraw), x_id(xId), y_id(yId) {
    vacant = true;
    active = false;
    if ((x_id + y_id) % 2 == 0) {
        filling = al_map_rgb(102, 0, 0);
    } else {
        filling = al_map_rgb(255, 255, 153);
    }
    if (xId == 0 || xId == BOARD_SIZE || yId == 0 || yId == BOARD_SIZE) {
        edge = true;
    } else {
        edge = false;
    }
}


bool Slot::isVacant() const {
    return vacant;
}

bool Slot::isActive(int x, int y) {
    if (x >= x_draw && x <= x_draw + x_size && y >= y_draw && y <= y_draw + y_size) {
        active = true;
    } else {
        active = false;
    }
    return active;
}

void Slot::draw() {
    al_draw_filled_rectangle(x_draw, y_draw, x_draw + x_size, y_draw + y_size, filling);
    if (active) {
        al_draw_rectangle(x_draw, y_draw, x_draw + x_size, y_draw + y_size, al_map_rgb(255, 102, 0), 4);
    }
}

void Slot::setVacant(bool vacant) {
    Slot::vacant = vacant;
}

int Slot::getSize() const {
    return x_size;
}

float Slot::getXDraw() const {
    return x_draw;
}

float Slot::getYDraw() const {
    return y_draw;
}

bool Slot::isEdge() const {
    return edge;
}

int Slot::getXId() const {
    return x_id;
}

int Slot::getYId() const {
    return y_id;
}

