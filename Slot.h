//
// Created by karolwes on 12.10.2021.
//

#ifndef CHECKER_OBJ_SLOT_H
#define CHECKER_OBJ_SLOT_H

#include "Drawable.h"


class Slot: public Drawable{

protected:
    int x_size;
    int y_size;
    float x_draw;
    float y_draw;
    int x_id;
    int y_id;
    AColor filling;
    bool vacant;
    bool active;
    bool edge;

public:
    Slot(int size, float xDraw, float yDraw, int xId, int yId);
    void setVacant(bool vacant);
    int getSize() const;
    float getXDraw() const;
    float getYDraw() const;
    bool isVacant() const;
    bool isActive(int x, int y);
    bool isEdge() const;
    int getXId() const;
    int getYId() const;

    void draw();


};


#endif //CHECKER_OBJ_SLOT_H
