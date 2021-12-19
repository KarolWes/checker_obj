//
// Created by karolwes on 30.10.2021.
//

#ifndef CHECKER_OBJ_QUEEN_H
#define CHECKER_OBJ_QUEEN_H


#include "BasePawn.h"

class Queen: public BasePawn {
public:
    virtual ~Queen();

    Queen(int x, int y, int owner, Slot *thisSlot);
    int canMove(int target_x, int target_y, vector<vector<Slot *> > *board,
                vector<BasePawn *> *allPawns) override;
    bool forceAttacks(vector<vector<Slot *> > *board, vector<BasePawn *> *allPawns) override;
    bool checkAttack(int dir_x, int dir_y, vector<vector<Slot *> > *board, vector<BasePawn *> *allPawns);
};


#endif //CHECKER_OBJ_QUEEN_H
