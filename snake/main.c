#include <stdio.h>
#include <stdlib.h> // EXIT_FAILURE and EXIT_SUCCESS
#include <stdbool.h>
#include <SDL2/SDL.h>


#include "const.h"
#include "font.h"
#include "game_loop.h"
#include "manager.h"
#include "menu_loop.h"
#include "snake.h"
#include "types.h" // point_2d

void input(Game *game);
void update(Game *game);
void render(Game *game);

int main(int argc, char *argv[])
{
    struct Game game = {0}; // initialize struct with null pointers is recommended to avoid undefined behavior when accessing uninitialized pointers.
    if (!sdl_initialise(&game))
    {
        sdl_cleanup(&game); // the program is terminated immediately here
        return (EXIT_FAILURE);
    }

    game.running = true;

    while (game.running)
    {
        Uint32 start_time = SDL_GetTicks();

        input(&game);
        update(&game);
        render(&game);

        Uint32 current_frame_time = SDL_GetTicks() - start_time;
        if (current_frame_time < FRAME_TIME)
            SDL_Delay(FRAME_TIME - current_frame_time);
    }

    // clean everything up
    sdl_cleanup(&game);
    return (EXIT_SUCCESS);
}

void input(Game *game)
{
    if (game->game_state == MENU)
        menu_input(game);
    else if (game->game_state == GAME)
        game_input(game);    
}

void update(Game *game)
{
    if (game->game_state == MENU)
        menu_update(game);
    else if (game->game_state == GAME)
        game_update(game); 
}

void render(Game *game)
{
    if (game->game_state == MENU)
        menu_render(game);
    else if (game->game_state == GAME)
        game_render(game); 
}
