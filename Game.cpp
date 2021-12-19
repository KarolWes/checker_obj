//
// Created by karolwes on 09.11.2021.
//

#include <iostream>
#include <algorithm>
#include "Game.h"

Game::Game(int window_x, int window_y, int size, int start_x, int start_y) : player1(12), player2(12), w_x(window_x),
                                                                             w_y(window_y) {


    ev_queue = al_create_event_queue();
    timer = al_create_timer(1.0 / 60);
    display = al_create_display(w_x, w_y);

    // drivers and event handling
    al_install_keyboard();
    al_install_mouse();
    al_register_event_source(ev_queue, al_get_keyboard_event_source());
    al_register_event_source(ev_queue, al_get_mouse_event_source());
    al_register_event_source(ev_queue, al_get_display_event_source(display));
    al_register_event_source(ev_queue, al_get_timer_event_source(timer));
    al_start_timer(timer);
    title_font = al_load_ttf_font("data/LittleLordFontleroyNF.ttf", 90, 0);
    title_small_font = al_load_ttf_font("data/LittleLordFontleroyNF.ttf", 60, 0);

    round = 1;
    sel_x = -1;
    sel_y = -1;
    move_x = -1;
    move_y = -1;
    cont = false;
    generateBoard(size, start_x, start_y);
    startup();
    surrender = new Button(190, 90, w_x - 200, board[0][0]->getYDraw() + 200, "Surrender");
    tie = new Button(190, 90, w_x - 200, board[0][0]->getYDraw() + 300, "Tie");
    endRound = new Button(190, 90, w_x - 200, board[0][0]->getYDraw() + 400, "END ROUND");
    playAgain = new Button(200,100, w_x/2-100, w_y/2-100, "Play again");


}

void Game::startup() {
    allPawns.push_back(new Pawn(0, 0, -1, board.at(0).at(0)));
    allPawns.push_back(new Pawn(2, 0, -1, board.at(0).at(2)));
    allPawns.push_back(new Pawn(4, 0, -1, board.at(0).at(4)));
    allPawns.push_back(new Pawn(6, 0, -1, board.at(0).at(6)));

    allPawns.push_back(new Pawn(1, 1, -1, board.at(1).at(1)));
    allPawns.push_back(new Pawn(3, 1, -1, board.at(1).at(3)));
    allPawns.push_back(new Pawn(5, 1, -1, board.at(1).at(5)));
    allPawns.push_back(new Pawn(7, 1, -1, board.at(1).at(7)));

    allPawns.push_back(new Pawn(0, 2, -1, board.at(2).at(0)));
    allPawns.push_back(new Pawn(2, 2, -1, board.at(2).at(2)));
    allPawns.push_back(new Pawn(4, 2, -1, board.at(2).at(4)));
    allPawns.push_back(new Pawn(6, 2, -1, board.at(2).at(6)));

    allPawns.push_back(new Pawn(1, 5, 1, board.at(5).at(1)));
    allPawns.push_back(new Pawn(3, 5, 1, board.at(5).at(3)));
    allPawns.push_back(new Pawn(5, 5, 1, board.at(5).at(5)));
    allPawns.push_back(new Pawn(7, 5, 1, board.at(5).at(7)));

    allPawns.push_back(new Pawn(0, 6, 1, board.at(6).at(0)));
    allPawns.push_back(new Pawn(2, 6, 1, board.at(6).at(2)));
    allPawns.push_back(new Pawn(4, 6, 1, board.at(6).at(4)));
    allPawns.push_back(new Pawn(6, 6, 1, board.at(6).at(6)));

    allPawns.push_back(new Pawn(1, 7, 1, board.at(7).at(1)));
    allPawns.push_back(new Pawn(3, 7, 1, board.at(7).at(3)));
    allPawns.push_back(new Pawn(5, 7, 1, board.at(7).at(5)));
    allPawns.push_back(new Pawn(7, 7, 1, board.at(7).at(7)));

}

void Game::generateBoard(int size, int start_x, int start_y) {
    for (int i = 0; i < 8; i++) {
        vector<Slot *> tmp;
        for (int j = 0; j < 8; j++) {
            Slot *slot = new Slot(size, start_x + j * size, start_y + i * size, j, i);
            tmp.push_back(slot);
        }
        board.push_back(tmp);
    }
}

void Game::drawBoard() {
    drawInterface(board[0][0]->getYDraw());
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j]->draw();
        }
    }
    for (BasePawn *p: allPawns) {
        p->draw(p->getSkin());
    }
}


void Game::play() {
    while (running) {
        if(gameState == 0){
            if(!cont){
                forcedAttacks();
            }
            else{
                pawn->findPawn(sel_x, sel_y, &allPawns)->forceAttacks(&board, &allPawns);
            }

            al_wait_for_event(ev_queue, &event);
            if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                running = false;

            }
            if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
                m_x = event.mouse.x;
                m_y = event.mouse.y;
                menageInterface(m_x, m_y);

                for (int i = 0; i < 8; i++) {
                    for (int j = 0; j < 8; j++) {
                        if (!board.at(i).at(j)->isVacant() && pawn->findPawn(j,i,&allPawns)->getAttacks()>0){
                            al_draw_rectangle(board.at(i).at(j)->getXDraw(), board.at(i).at(j)->getYDraw(), board.at(i).at(j)->getXDraw() + board.at(i).at(j)->getSize(), board.at(i).at(j)->getYDraw() + board.at(i).at(j)->getSize(), al_map_rgb(0, 0, 255), 4);
                        }
                        if (board[i][j]->isActive(m_x, m_y)) {
                            if (selectSlot(i, j)) {
                                pawn = pawn->findPawn(sel_x, sel_y, &allPawns);
                                int can;
                                if (pawn != NULL) {
                                    can = pawn->canMove(move_x, move_y, &board, &allPawns);
                                }
                                if (!cont && can == 0) {
                                    pawn->move(board[move_y][move_x], &allPawns);
                                    endOfTurn();
                                } else if (can == 1) {
                                    pawn->move(board[move_y][move_x], &allPawns);

                                    if(round == 1){
                                        player2 -= 1;
                                        cout << "p2 " << player2 << endl;
                                        if (player2 == 0) {
                                            cout << "Game over\n";
                                            gameState = 1;
                                        }
                                    }else{
                                        player1 -= 1;
                                        cout << "p1 " << player1 << endl;
                                        if (player1 == 0) {
                                            cout << "Game over\n";
                                            gameState = 1;
                                        }
                                    }

                                    sel_x = move_x;
                                    sel_y = move_y;
                                    move_x = -1;
                                    move_y = -1;
                                    cont = true;
                                } else {
                                    cout << "mistake\n";
                                }
                            }
                        }
                    }
                }
            }
            if (event.type == ALLEGRO_EVENT_TIMER) {
                al_clear_to_color(background);
                drawBoard();
                al_flip_display();
            }
        }
        else{
            menageGameState();
        }
    }
}

void Game::endGame() {
    board.clear();
    allPawns.clear();


    al_destroy_display(display);
    al_uninstall_keyboard();
    al_uninstall_mouse();
    al_destroy_timer(timer);
}

bool Game::selectSlot(int i, int j) {
    BasePawn *pawn = NULL;
    if (!cont) {
        if (!board[i][j]->isVacant()) {
            pawn = pawn->findPawn(j, i, &allPawns);
        }
        if (pawn != NULL) {
            if (!board[i][j]->isVacant() && sel_x == -1 && sel_y == -1 && pawn->getOwner() == round) {
                sel_x = j;
                sel_y = i;
                move_x = -1;
                move_y = -1;
                board[i][j]->draw();
            } else if (!board[i][j]->isVacant() && pawn->getOwner() == round) {
                sel_x = j;
                sel_y = i;
                move_x = -1;
                move_y = -1;
                board[i][j]->draw();
            }
        } else {
            if (sel_x != -1) {
                move_x = j;
                move_y = i;
                board[i][j]->draw();
            }
        }
        if (!board[i][j]->isVacant() && pawn->getOwner() == round * (-1)) {
            board[i][j]->isActive(-1, -1);
            sel_x = -1;
            sel_y = -1;
            move_x = -1;
            move_y = -1;
        }
    } else {
        if (board[i][j]->isVacant()) {
            move_y = i;
            move_x = j;
            board[i][j]->draw();
        } else {
            move_x = -1;
            move_y = -1;
        }
    }
//    cout << "Sel: " << sel_x << " " << sel_y << "; Move: " << move_x << " " << move_y << endl;
    if (sel_x != -1 && sel_y != -1 && move_x != -1 && move_y != -1) {
        return true;
    } else {
        return false;
    }
}

void Game::drawInterface(int start_y) {
    al_draw_text(title_font, gold, w_x / 2 - 100, 10, 0, "Checker");
    al_draw_text(title_small_font, gold, w_x - 200, start_y, 0, "Player:");
    if (round > 0) {
        al_draw_text(title_small_font, gold, w_x - 200, start_y + 70, 0, "White");
    } else {
        al_draw_text(title_small_font, gold, w_x - 200, start_y + 70, 0, "Black");
    }

    surrender->draw();
    tie->draw();
    if (cont) {
        endRound->draw();
    }
}

void Game::menageInterface(int m_x, int m_y) {
    if (surrender->isActive(m_x, m_y)) {
        gameState = 3;
        surrender->clearFocus();
    } else if (tie->isActive(m_x, m_y)) {
        gameState = 2;
        tie->clearFocus();
    } else if (cont && endRound->isActive(m_x, m_y)) {
        endRound->clearFocus();
        endOfTurn();
    }
}

void Game::endOfTurn() {
    cont = false;
    sel_x = -1;
    sel_y = -1;
    move_y = -1;
    move_x = -1;
    round *= -1;
    for (BasePawn *p: allPawns) {
        if (p->getAttacks() > 0) {
            if(p->getOwner() == 1){
                player1 --;
            }
            else{
                player2 --;
            }
            p->getThisSlot()->setVacant(true);
            allPawns.erase(find(allPawns.begin(), allPawns.end(), p));
            delete p;
        }
    }
    if(player1 == 0){
        cout << "END GAME\n";
        gameState = 1;
    }
    if(player2 == 0){
        cout << "END GAME\n";
        gameState = 1;
    }
    evolve();
}

void Game::forcedAttacks() {
    for (BasePawn *p: allPawns) {
        if(p->getOwner() == round) {
            p->forceAttacks(&board, &allPawns);
        }
    }
}

void Game::evolve() {
    for(BasePawn *p: allPawns){
        if(!p->isQueen()){
            if((p->getOwner() == 1 && p->getY() == 0)|| (p->getOwner() == -1 && p->getY() == 7)){
                Queen *q = new Queen(p->getX(), p->getY(), p->getOwner(), p->getThisSlot());
                allPawns.erase(find(allPawns.begin(),  allPawns.end(), p));
                allPawns.push_back(q);
            }
        }
    }
}

void Game::menageGameState(){
    al_wait_for_event(ev_queue, &event);
    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        running = false;
    }
    if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
        m_x = event.mouse.x;
        m_y = event.mouse.y;
        if(playAgain->isActive(m_x, m_y)){
            gameState = 0;
            playAgain->clearFocus();
            int size = board.at(0).at(0)->getSize();
            int start_x = board.at(0).at(0)->getXDraw();
            int start_y = board.at(0).at(0)->getYDraw();
            board.clear();
            allPawns.clear();
            round = 1;
            sel_x = -1;
            sel_y = -1;
            move_x = -1;
            move_y = -1;
            cont = false;
            generateBoard(size, start_x, start_y);
            startup();
        }
    }

    if (event.type == ALLEGRO_EVENT_TIMER) {
        al_clear_to_color(background);
        switch (gameState) {
            case 1:{
                al_draw_textf(title_font, gold, w_x/2-400, 500, 0, "End of the game. Player %d wins.", round > 0 ? 1:2);
                break;
            }
            case 2:{
                al_draw_textf(title_font, gold, w_x/2-220, 500, 0, "End of the game. Tie.");
                break;
            }
            case 3:{
                al_draw_textf(title_font, gold, w_x/2-400, 500, 0, "End of the game. Player %d surrenders.", round > 0 ? 1:2);
                break;
            }
            default:{}
                //nothing here
        }
        playAgain->draw();
        al_flip_display();
    }
}
