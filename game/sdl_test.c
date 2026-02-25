#include <stdio.h>
#include <stdlib.h> // for exit(), EXIT_FAILURE and EXIT_SUCCESS
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "const.h"
#include "font.h"

// SDL window data structure and renderer, write all to struct for better readability
struct Game
{
    SDL_Window *window;
    SDL_Renderer *renderer;
};

// Entity structure representing an object on the screen
// typedef struct
// {
//     float x, y;
//     float vx, vy;
//     int color[3];
// } Entity;

// bro suggests returning 1 for error and 0 for success.

void sdl_cleanup(struct Game *game, int exit_status);

bool sdl_initialise(struct Game *game);

int main(int argc, char *argv[])
{
    printf("Heeeeeey\n");
    struct Game game = {.window = NULL, .renderer = NULL}; // initialize struct with null pointers is recommended to avoid undefined behavior when accessing uninitialized pointers.
    if (sdl_initialise(&game))
    {
        printf("NOT SUCCESS.\n");
        sdl_cleanup(&game, EXIT_FAILURE); // the program is terminated immediately here
    }
    // SDL_RenderCopy
    SDL_Texture *alphabet[ALPHABET_LENGTH];
    // create aplhabet to be able to generate letters on screen
    generate_alphabet(game.renderer,
                      alphabet);
    // Entity rect = {100, 100, 0, 0, {0x0A, 0x0A, 0xBB}};
    Uint32 start_time = SDL_GetTicks();
    int step = 0;
    while (true)
    {
        // Phase 1: calculate the scene
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                printf("Gracefully quit.\n");
                sdl_cleanup(&game, EXIT_SUCCESS);
            }
            if (event.type == SDL_KEYDOWN)
            {
                // const Uint8 *keystate = SDL_GetKeyboardState(NULL); - chatgpt said it is too much and redundant
                // since we already have key in event
                if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                {
                    printf("Gracefully quit by pressing esc.\n");
                    sdl_cleanup(&game, EXIT_SUCCESS);
                }
            }
        }
        // phase 2: render the scene
        //  set bg colour
        SDL_SetRenderDrawColor(game.renderer, 0xA8, 0x00, 0x84, 255);

        // clear previous frame
        SDL_RenderClear(game.renderer);
        SDL_Rect rect = {50, 240, 100, 100};
        // here we can draw our own objects - which we will do
        SDL_SetRenderDrawColor(game.renderer, 0x01, 0xBC, 0x0D, 255);
        if (step > 0 || SDL_GetTicks() - start_time > 1000)
        {

            SDL_RenderCopy(game.renderer, alphabet[(int)'Y' - 'A'], NULL, &rect);

            rect.x = 150;
            SDL_RenderCopy(game.renderer, alphabet[(int)'O' - 'A'], NULL, &rect);

            rect.x = 250;
            SDL_RenderCopy(game.renderer, alphabet[(int)'U' - 'A'], NULL, &rect);
            if (step <= 0)
                step += 1;
        }

        if (step > 1 || SDL_GetTicks() - start_time > 2000)
        {
            rect.x = 450;
            SDL_RenderCopy(game.renderer, alphabet[(int)'A' - 'A'], NULL, &rect);

            rect.x = 550;
            SDL_RenderCopy(game.renderer, alphabet[(int)'R' - 'A'], NULL, &rect);

            rect.x = 650;
            SDL_RenderCopy(game.renderer, alphabet[(int)'E' - 'A'], NULL, &rect);
            if (step <= 1)
                step += 1;
        }

        if (step > 2 || SDL_GetTicks() - start_time > 3000)
        {
            rect.y = 350;

            rect.x = 250;
            SDL_RenderCopy(game.renderer, alphabet[(int)'D' - 'A'], NULL, &rect);

            rect.x = 350;
            SDL_RenderCopy(game.renderer, alphabet[(int)'O' - 'A'], NULL, &rect);

            rect.x = 450;
            SDL_RenderCopy(game.renderer, alphabet[(int)'G' - 'A'], NULL, &rect);

            if (step <= 2)
                step += 1;
        }
        rect.x = 220;
        rect.y = 500;
        rect.w = 20;
        rect.h = 20;
        if (step > 3 || SDL_GetTicks() - start_time > 4000)
        {

            SDL_RenderCopy(game.renderer, alphabet[(int)'P' - 'A'], NULL, &rect);

            rect.x += 20;
            SDL_RenderCopy(game.renderer, alphabet[(int)'R' - 'A'], NULL, &rect);

            rect.x += 20;
            SDL_RenderCopy(game.renderer, alphabet[(int)'E' - 'A'], NULL, &rect);

            rect.x += 20;
            SDL_RenderCopy(game.renderer, alphabet[(int)'S' - 'A'], NULL, &rect);

            rect.x += 20;
            SDL_RenderCopy(game.renderer, alphabet[(int)'S' - 'A'], NULL, &rect);

            rect.x += 40;
            SDL_RenderCopy(game.renderer, alphabet[(int)'E' - 'A'], NULL, &rect);

            rect.x += 20;
            SDL_RenderCopy(game.renderer, alphabet[(int)'S' - 'A'], NULL, &rect);

            rect.x += 20;
            SDL_RenderCopy(game.renderer, alphabet[(int)'C' - 'A'], NULL, &rect);

            rect.x += 40;
            SDL_RenderCopy(game.renderer, alphabet[(int)'T' - 'A'], NULL, &rect);

            rect.x += 20;
            SDL_RenderCopy(game.renderer, alphabet[(int)'O' - 'A'], NULL, &rect);

            rect.x += 40;
            SDL_RenderCopy(game.renderer, alphabet[(int)'E' - 'A'], NULL, &rect);

            rect.x += 20;
            SDL_RenderCopy(game.renderer, alphabet[(int)'X' - 'A'], NULL, &rect);

            rect.x += 20;
            SDL_RenderCopy(game.renderer, alphabet[(int)'I' - 'A'], NULL, &rect);

            rect.x += 20;
            SDL_RenderCopy(game.renderer, alphabet[(int)'T' - 'A'], NULL, &rect);

            if (step <= 3)
                step += 1;
        }

        // SDL_RenderDrawRect(game.renderer, &rect);

        // now display it on renderer
        SDL_RenderPresent(game.renderer);

        /*
        THIS IS ANOTHER APPROACH - SHOULD NOT MIX THESE TWO!
        Tere is a surface workflow vs render workflow
        SDL_Surface *screenSurface = SDL_GetWindowSurface(game.window);

        // Fill the surface white
        SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xA8, 0x00, 0x84));

        // Update the surface
        SDL_UpdateWindowSurface(game.window);
        */
        SDL_Delay(FRAME_TIME);
    }

    printf("Success.\n");
    sdl_cleanup(&game, EXIT_SUCCESS);
}

void sdl_cleanup(struct Game *game, int exit_status) // graceful shutdown.
{
    SDL_DestroyRenderer(game->renderer); // is able to process NULL, so no prior check required
    SDL_DestroyWindow(game->window);     // same thing as previous line
    SDL_Quit();                          // void SDL_Quit(void), cleans up all allocated memory by SDL
    exit(exit_status);
}

bool sdl_initialise(struct Game *game)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) // init, returns 0 on success, -1 on failure.
    {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError()); // gets error message from SDL.
        return true;
    }
    game->window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0); // create window, returns pointer to window on success, NULL on failure.
    if (game->window == NULL)
    {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        return true;
    }
    game->renderer = SDL_CreateRenderer(game->window, -1, 0);
    if (game->renderer == NULL)
    {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return true;
    }
    return false;
}
