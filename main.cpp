#include <iostream>
#include "Game.h"

using namespace std;

int main() {
    //init
    int window_x = 1200, window_y = 960;
    al_init();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_init_primitives_addon();

    //Allegro variables




    cout << "Welcome to the checker!" << endl;
    int size = 100;
    int start_x = 100;
    int start_y = 100;
    Game game(window_x, window_y, size, start_x, start_y);
    game.play();
    game.endGame();

    return 0;
}
