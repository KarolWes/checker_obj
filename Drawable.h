//
// Created by karolwes on 30.10.2021.
//
#ifndef CHECKER_OBJ_DRAWABLE_H
#define CHECKER_OBJ_DRAWABLE_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#define  AColor ALLEGRO_COLOR
#define ADisp ALLEGRO_DISPLAY
#define APic ALLEGRO_BITMAP
#define BOARD_SIZE 8

class Drawable {
    virtual void draw(){};
};


#endif //CHECKER_OBJ_DRAWABLE_H
