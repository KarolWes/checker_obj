//
// Created by karolwes on 30.10.2021.
//

#include "BasePawn.h"
#include <cmath>
#include <algorithm>

BasePawn::BasePawn() {}

BasePawn::BasePawn(int x, int y) : x(x), y(y) {}

BasePawn::BasePawn(int x, int y, int owner, Slot *thisSlot) : x(x), y(y), owner(owner), thisSlot(thisSlot) {
    attacks = 0;
    thisSlot->setVacant(false);
}

BasePawn::~BasePawn() {
    this->thisSlot = NULL;
}

int BasePawn::getAttacks() const {
    return attacks;
}

void BasePawn::setAttacks(int attacks) {
    BasePawn::attacks = attacks;
}

int BasePawn::getX() const {
    return x;
}

int BasePawn::getY() const {
    return y;
}

int BasePawn::getOwner() const {
    return owner;
}

Slot *BasePawn::getThisSlot() const {
    return thisSlot;
}

bool BasePawn::operator==(const BasePawn &rhs) const {
    return x == rhs.x &&
           y == rhs.y;
}

bool BasePawn::operator!=(const BasePawn &rhs) const {
    return !(rhs == *this);
}

void BasePawn::setX(int x) {
    BasePawn::x = x;
}

void BasePawn::setY(int y) {
    BasePawn::y = y;
}

int BasePawn::canMove(int target_x, int target_y,
                      vector<vector<Slot *> > *board, vector<BasePawn *> *allPawns) {
    int result;
    int tmp;
    int dir_x;
    int dir_y;
    toBeat = NULL;
    tmp = abs(this->x - target_x);
    dir_x = (this->x - target_x) / tmp;
    tmp = abs(this->y - target_y);
    dir_y = (this->y - target_y) / tmp;//move direction

    if (tmp - abs(this->x - target_x) == 0) {//if diagonal
        int m = 1;

        while (btw(this->y - m * dir_y) && btw(this->x - m * dir_x)
               && m < tmp && board->at(this->y - m * dir_y).at(this->x - m * dir_x)->isVacant()) {
            m++;
        }//move until slots are empty
        if (m == tmp) {
            result = 0;
//            fin = 1;
//            fin_inner = 1;
        } else {//beat
            int distToOccupiedSlot = m;
            int beat_x = this->x - m * dir_x;
            int beat_y = this->y - m * dir_y;
            toBeat = findPawn(beat_x, beat_y, allPawns);
            if (toBeat->getOwner() != this->owner) {//pawn belongs to opponent
                m++;
                while (btw(this->y - m * dir_y) && btw(this->x - m * dir_x)
                       && m < tmp && board->at(this->y - m * dir_y).at(
                        this->x - m * dir_x)->isVacant()) { //move until slots are empty & ! target
                    m++;
                }
                if (m == tmp) {//if target
                    result = 1;
                } else { result = -1; } // pawn belongs to player
            } else { result = -1; } // multiple occupied slots
        }
    } else { result = -1; } // not diagonal
    return result;
}

void BasePawn::draw(APic *skin) {
    al_draw_bitmap(skin, thisSlot->getXDraw() + 5, thisSlot->getYDraw() + 5, 0);
//    if(attacks > 0){
//        al_draw_rectangle(thisSlot->getXDraw(), thisSlot->getYDraw(), thisSlot->getXDraw()+thisSlot->getSize(), thisSlot->getYDraw()+thisSlot->getSize(),
//                          al_map_rgb(255,0,0), 4);
//    }
}




BasePawn *BasePawn::findPawn(int x, int y, vector<BasePawn *> *allPawns) const {
    BasePawn compPawn(x, y);
    BasePawn *res = NULL;
    for (auto pawn: *allPawns) {
        if (*pawn == compPawn) {
            res = pawn;
        }
    }
    return res;
}

BasePawn *BasePawn::findPawn(Slot *slot, vector<BasePawn *> *allPawns) const {
    return BasePawn::findPawn(slot->getXId(), slot->getYId(), allPawns);
}

bool BasePawn::btw(int n, int l, int u) {
    if (n >= l && n < u) {
        return true;
    } else {
        return false;
    }
}

bool BasePawn::btw(int n) {
    BasePawn::btw(n, 0, BOARD_SIZE);
}

void BasePawn::setSkin(APic *newSkin) {
    skin = newSkin;
}

ALLEGRO_BITMAP *BasePawn::getSkin() const {
    return skin;
}

void BasePawn::move(Slot *target, vector<BasePawn *> *allPawns) {
    this->x = target->getXId();
    this->y = target->getYId();
    this->thisSlot->setVacant(true);
    this->thisSlot = target;
    this->thisSlot->setVacant(false);
    if(toBeat != NULL){//delete beaten pawn
        this->attacks = 0;
        toBeat->getThisSlot()->setVacant(true);
        allPawns->erase(find(allPawns->begin(), allPawns->end(), toBeat));
        delete toBeat;
        for(BasePawn *p: *allPawns){
            p->setAttacks(0);
        }
    }
}

bool BasePawn::isQueen() const {
    return queen;
}





