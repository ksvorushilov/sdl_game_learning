
#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdlib.h>

#include "sdl_const.h"

#include "manager.h"
#include "const.h"
#include "ui_and_engine.h"

int engine_init() // argument for compatibility
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) // init, returns 0 on success, -1 on failure.
    {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError()); // gets error message from SDL.
        return EXIT_FAILURE;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0"); // 0 - nearest, no blur
    SDL_ShowCursor(SDL_DISABLE);                     // hide system mouse cursor

    return EXIT_SUCCESS;
}

game_window_t engine_create_window(int w, int h)
{
    game_window_t w_container = {0};
    w_container.window = SDL_CreateWindow(WINDOW_TITLE,
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          w * SCREEN_CELL_WIDTH,
                                          h * SCREEN_CELL_HEIGHT,
                                          0); // create window, returns pointer to window on success, NULL on failure.
    if (w_container.window == NULL)
    {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
    }
    return w_container;
}

game_renderer_t engine_create_renderer(game_window_t window) // argment for compatibility
{
    game_renderer_t r_container = {0};
    r_container.renderer = SDL_CreateRenderer(window.window, -1, 0);
    if (r_container.renderer == NULL)
    {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
    }
    return r_container;
}
void engine_destroy_renderer(game_renderer_t renderer)
{
    SDL_DestroyRenderer(renderer.renderer);
}
void engine_destroy_window(game_window_t window)
{
    SDL_DestroyWindow(window.window);
}
void engine_quit()
{
    SDL_ShowCursor(SDL_ENABLE); // show system mouse cursor
    SDL_Quit();
}
