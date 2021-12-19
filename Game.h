//
// Created by karolwes on 09.11.2021.
//

#ifndef CHECKER_OBJ_GAME_H
#define CHECKER_OBJ_GAME_H
#include "Slot.h"
#include "Pawn.h"
#include "Queen.h"
#include "BasePawn.h"
#include "Button.h"


class Game {

private:
    bool running = true;
    int player1 = 12;
    int player2 = 12;
    int m_x;
    int m_y;
    int w_x;
    int w_y;
    int sel_x, sel_y;
    int move_x, move_y;
    int round;
    int gameState = 0; // 0 = game; 1 = win; 2 = tie; 3 = surrender
    bool cont;
    vector<BasePawn *> allPawns;
    vector<vector<Slot *> > board;
    ALLEGRO_EVENT event;
    ALLEGRO_EVENT_QUEUE *ev_queue;
    ALLEGRO_TIMER *timer;
    AColor background = al_map_rgb(0, 102, 0);
    AColor gold = al_map_rgb(179, 179, 0);
    ADisp *display;
    ALLEGRO_FONT* title_font;
    ALLEGRO_FONT* title_small_font;
    Button *surrender;
    Button *endRound;
    Button *tie;
    Button *playAgain;
    BasePawn *pawn;

public:
    Game(int window_x, int window_y, int size, int start_x, int start_y);
    void startup();
    void drawBoard();
    void generateBoard(int size,int start_x,int start_y);
    void drawInterface(int start_y);
    void play();
    void endGame();
    void menageInterface(int m_x, int m_y);
    void menageGameState();
    bool selectSlot(int i, int j);
    void endOfTurn();
    void forcedAttacks();
    void evolve();
};


#endif //CHECKER_OBJ_GAME_H
