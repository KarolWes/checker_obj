//
// Created by karolwes on 30.10.2021.
//

#include "Queen.h"

Queen::Queen(int x, int y, int owner, Slot *thisSlot) : BasePawn(x, y, owner, thisSlot) {
    APic *skin=NULL;
    if (owner == 1) {
        skin = al_load_bitmap("data/light_queen.png");
    } else {
        skin = al_load_bitmap("data/dark_queen.png");
    }
    assert(skin != NULL);
    setSkin(skin);
    queen = true;
}

int Queen::canMove(int target_x, int target_y, vector<vector<Slot *>> *board,
                   vector<BasePawn *> *allPawns) {
    return BasePawn::canMove(target_x, target_y, board, allPawns);
}

bool Queen::forceAttacks(vector<vector<Slot *> > *board, vector<BasePawn *> *allPawns) {
    bool res = false;
    res = res || checkAttack(1,1,board, allPawns);
    res = res || checkAttack(-1,1,board, allPawns);
    res = res || checkAttack(1,-1,board, allPawns);
    res = res || checkAttack(-1,-1,board, allPawns);


//    int j = 1;
//    while(btw(y+j) && btw(x+j) && board->at(y+j).at(x+j)->isVacant())
//    {
//        j+=1;
//    }
//    if (findPawn(board->at(y+j).at(x+j), allPawns)->getOwner() != owner)
//    {
//        if (btw(y+j) && btw(x+j) && board->at(y+j).at(x+j)->isVacant())
//        {
//            this->setAttacks(1);
//            res = true;
//        }
//    }
//
//
//    j = 1;
//    while(btw(y+j) && btw(x-j) && board->at(y+j).at(x-j)->isVacant())
//    {
//        j+=1;
//    }
//    if (findPawn(board->at(y+j).at(x-j), allPawns)->getOwner() != owner)
//    {
//        if (btw(y+j) && btw(x-j) && board->at(y+j).at(x-j)->isVacant())
//        {
//            this->setAttacks(1);
//            res = true;
//        }
//    }
//
//
//    j = 1;
//    while(btw(y-j) && btw(x+j) && board->at(y-j-1).at(x+j+1)->isVacant())
//    {
//        j+=1;
//    }
//    if (findPawn(board->at(y-j).at(x+j), allPawns)->getOwner() != owner)
//    {
//        if (btw(y-j) && btw(x+j) && board->at(y-j-1).at(x+j+1)->isVacant())
//        {
//            this->setAttacks(1);
//            res = true;
//        }
//    }
//
//    j = 1;
//    while(btw(y-j) && btw(x-j) && board->at(y-j-1).at(x-j-1)->isVacant())
//    {
//        j+=1;
//    }
//    if (findPawn(board->at(y-j).at(x-j), allPawns)->getOwner() != owner)
//    {
//        if (btw(y-j) && btw(x-j) && board->at(y-j-1).at(x-j-1)->isVacant())
//        {
//            this->setAttacks(1);
//            res = true;
//        }
//    }
    return res;
}

Queen::~Queen() {
    al_destroy_bitmap(skin);
    this->thisSlot = NULL;

}

bool Queen::checkAttack(int dir_x, int dir_y, vector<vector<Slot *>> *board, vector<BasePawn *> *allPawns) {
    int j = 1;
    bool res = false;
    int x = this->getX(); int y = this->getY();
    int owner = this->getOwner();
    while(btw(y+j*dir_y) && btw(x+j*dir_x) && board->at(y+j*dir_y).at(x+j*dir_x)->isVacant())
    {
        j+=1;
    }
    if(btw(y+j*dir_y) && btw(x+j*dir_x)){
        if (findPawn(board->at(y+j*dir_y).at(x+j*dir_x), allPawns)->getOwner() != owner)
        {
            if (btw(y+j*dir_y+dir_y) && btw(x+j*dir_x+dir_x) && board->at(y+j*dir_y+dir_y).at(x+j*dir_x+dir_x)->isVacant())
            {
                this->setAttacks(1);
                res = true;
            }
        }
    }
    return res;
}

