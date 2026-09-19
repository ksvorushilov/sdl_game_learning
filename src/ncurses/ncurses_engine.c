
#include <stdint.h>
#include <stdlib.h>

#include <ncurses.h>

#include "types.h"
#include "ncurses_render.h"

bool engine_configure_kb_input(game_window_t window);

int engine_init() // argument for compatibility
{
    set_escdelay(50); // for clean esc readings. Some keypad keys have esc sequences
    initscr();
    cbreak();    //  line buffering disable
    noecho();    //  turn off displaying input symbols
    curs_set(0); // hides cursor

    if (has_colors() == false)
    {
        return EXIT_FAILURE;
    }

    start_color();
    init_colors();
    refresh(); // Linux compatibility
    return EXIT_SUCCESS;
}

game_window_t engine_create_window(int w, int h)
{
    game_window_t w_container = {0};

    w_container.window = newwin(h, w * SYMBOLS_PER_CELL, 0, 0);
    if (w_container.window != NULL)
    {
        engine_configure_kb_input(w_container); // no suitable place during init stage
    }

    return w_container;
}

game_renderer_t engine_create_renderer(game_window_t window) //for compatibility
{
    (void)window;
    static int dummy;
    return (game_renderer_t){.renderer = &dummy};
}
void engine_destroy_renderer(game_renderer_t renderer)
{
    if (renderer.renderer == NULL)
    {
        return;
    }
    free(renderer.renderer);
}
void engine_destroy_window(game_window_t window)
{
   
    if (window.window != NULL)
    {
        delwin(window.window);
        window.window = NULL;
    }

}
void engine_quit()
{
    endwin();
}

bool engine_configure_kb_input(game_window_t window)
{
    if (keypad(window.window, true) == ERR) // enable keypad functionality
    {
        return false;
    }
    if (nodelay(window.window, true) == ERR) // non-blocking input
    {
        return false;
    }
    return true;
}
