#include <SDL2/SDL.h>
#include <iostream>
#include "game_lib.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[])
{
    // game_t::init(
    //     "Father Junior ThunderMouth, The Truly And Only",
    //     SCREEN_WIDTH,
    //     SCREEN_HEIGHT
    // );

    game_t::run([] () {

    });

    return 0;
}
