//
// Created by karolwes on 23.11.2021.
//

#ifndef CHECKER_OBJ_BUTTON_H
#define CHECKER_OBJ_BUTTON_H


#include "Slot.h"
#include <string>

using namespace std;

class Button: public Slot{
private:
    const char *text;
    AColor background = al_map_rgb(179, 179, 0);
    AColor font = al_map_rgb(102, 0, 0);
    ALLEGRO_FONT *machine_font ;

public:
    Button(int x_size, int y_size, float xDraw, float yDraw, const char *text);
    void clearFocus();
    void draw() override;
};


#endif //CHECKER_OBJ_BUTTON_H
