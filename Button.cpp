//
// Created by karolwes on 23.11.2021.
//

#include "Button.h"

Button::Button(int x_size, int y_size, float xDraw, float yDraw, const char *text) : Slot(x_size, xDraw, yDraw, -1, -1) {
    machine_font = al_load_ttf_font("data/Hack-Regular.ttf", 32,0);
    this->text = text;
    filling = background;
    this->y_size = y_size;
}

void Button::draw() {
    Slot::draw();
    al_draw_text(machine_font, font, x_draw + 10, y_draw + 30, 0, text);
}

void Button::clearFocus() {
    active = false;
}
