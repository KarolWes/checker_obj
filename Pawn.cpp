//
// Created by karolwes on 30.10.2021.
//

#include "Pawn.h"

Pawn::Pawn(int x, int y, int owner, Slot *thisSlot) : BasePawn(x, y, owner, thisSlot) {
    APic *skin=NULL;
    if (owner == 1) {
        skin = al_load_bitmap("data/light.png");
    } else {
        skin = al_load_bitmap("data/dark.png");
    }
    assert(skin != NULL);
    setSkin(skin);
    queen = false;
}

int Pawn::canMove(int target_x, int target_y, vector<vector<Slot *>> *board,
                  vector<BasePawn *> *allPawns) {
    if (abs(this->y - target_y) == 1 && this->y - target_y == this->getOwner()){
        return BasePawn::canMove(target_x, target_y, board, allPawns);
    }
    else if((abs(this->y - target_y) == 2) &&!board->at(abs((this->y + target_y) / 2)).at(abs((this->x + target_x) / 2))->isVacant()) {
        return BasePawn::canMove(target_x, target_y, board, allPawns);
    }
    else{
        return -1;
    }
}

bool Pawn::forceAttacks(vector<vector<Slot *>> *board, vector<BasePawn *> *allPawns) {
    bool res = false;
    int x = this->getX();
    int y = this->getY();
    int owner = this->getOwner();
    if (btw(y+1)&& btw(x+1) && !board->at(y + 1).at(x + 1)->isVacant()) {
        if(findPawn(board->at(y + 1).at(x + 1), allPawns)->getOwner() != owner){
            if (btw(y + 2) && btw(x + 2) && board->at(y + 2).at(x + 2)->isVacant()) {
                this->setAttacks(1);
                res = true;
            }
        }
    }
    if (btw(y+1)&& btw(x-1)&& !board->at(y + 1).at(x - 1)->isVacant()) {
        if(findPawn(board->at(y + 1).at(x - 1), allPawns)->getOwner() != owner){
            if (btw(y + 2) && btw(x - 2) && board->at(y + 2).at(x - 2)->isVacant()) {
                this->setAttacks(1);
                res = true;
            }
        }
    }
    if (btw(y-1)&& btw(x+1)&& !board->at(y - 1).at(x + 1)->isVacant()) {
        if(findPawn(board->at(y - 1).at(x + 1), allPawns)->getOwner() != owner){
            if (btw(y - 2) && btw(x + 2) && board->at(y - 2).at(x + 2)->isVacant()) {
                this->setAttacks(1);
                res = true;
            }
        }
    }
    if (btw(y-1)&& btw(x-1)&& !board->at(y - 1).at(x - 1)->isVacant()) {
        if(findPawn(board->at(y - 1).at(x - 1), allPawns)->getOwner() != owner){
            if (btw(y - 2) && btw(x - 2) && board->at(y - 2).at(x - 2)->isVacant()) {
                this->setAttacks(1);
                res = true;
            }
        }
    }
    return res;
}

Pawn::~Pawn() {
    al_destroy_bitmap(skin);
    this->thisSlot = NULL;
}


