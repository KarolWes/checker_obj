//
// Created by karolwes on 30.10.2021.
//

#ifndef CHECKER_OBJ_PAWN_H
#define CHECKER_OBJ_PAWN_H


#include "BasePawn.h"

class Pawn: public BasePawn {

public:
    Pawn(int x, int y, int owner, Slot *thisSlot);

    int canMove(int target_x, int target_y, vector<vector<Slot *> > *board,
                vector<BasePawn *> *allPawns) override;
    bool forceAttacks(vector<vector<Slot *>> *board, vector<BasePawn *> *allPawns) override;


    virtual ~Pawn();
};


#endif //CHECKER_OBJ_PAWN_H
