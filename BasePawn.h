//
// Created by karolwes on 30.10.2021.
//

#ifndef CHECKER_OBJ_BASEPAWN_H
#define CHECKER_OBJ_BASEPAWN_H


#include "Slot.h"
#include <vector>

using namespace std;

class BasePawn : public Drawable{

protected:
    int x;
    int y;
    int owner;
    int attacks;
    bool queen;
public:
    bool isQueen() const;

protected:
    Slot *thisSlot;
    APic *skin=NULL;
    void setSkin(APic *newSkin);
    void setAttacks(int attacks);
    BasePawn *toBeat;

public:
    BasePawn();
    BasePawn(int x, int y);
    BasePawn(int x, int y, int owner, Slot *thisSlot);
    virtual ~BasePawn();

    bool operator==(const BasePawn &rhs) const;
    bool operator!=(const BasePawn &rhs) const;

    int getX() const;
    int getY() const;
    int getAttacks() const;
    int getOwner() const;
    Slot *getThisSlot() const;
    ALLEGRO_BITMAP *getSkin() const;


    void setX(int x);
    void setY(int y);

    virtual int canMove(int target_x, int target_y, vector<vector<Slot *> > *board,
                        vector<BasePawn *> *allPawns);
    void move(Slot *target, vector<BasePawn *> *allPawns);
    void draw(APic *skin);


    BasePawn *findPawn(int x, int y, vector<BasePawn *> *allPawns) const;
    BasePawn *findPawn(Slot *slot, vector<BasePawn *> *allPawns) const;
    virtual bool forceAttacks(vector<vector<Slot *> > *board, vector<BasePawn *> *allPawns){return false;};
    bool btw(int n, int l, int u); // between lower(inclusive) and upper bound(exclusive)
    bool btw(int n); // lower bound is 0, upper bound is BOARD_SIZE

};


#endif //CHECKER_OBJ_BASEPAWN_H
