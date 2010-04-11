#include "config.h"

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef CURSES_HAVE_CURSES_H
#include <curses.h>
#elif CURSES_HAVE_NCURSES_H
#include <ncurses.h>
#elif CURSES_HAVE_NCURSES_NCURSES_H
#include <ncurses/ncurses.h>
#elif CURSES_HAVE_NCURSES_CURSES_H
#include <ncurses/curses.h>
#else
#error No curses include file found
#endif

/**
 * TODO
 */
int main_int(WINDOW *p_window)
{
    enum
    {
        ROW_STRING = 0
      , ROW_DEC
      , ROW_HEX
      , ROW_ASCII
      , ROW_NUM
    };
    static const char ROW_STRING_PFX[] = "S: ";
    static const char ROW_DEC_PFX[] = "D: ";
    static const char ROW_HEX_PFX[] = "H: ";
    static const char ROW_ASCII_PFX[] = "A: ";

    int c;
    char buf[1024];
    char *p_buf;

    if(ERR == cbreak())
    {
        fprintf(stderr, "%s: cbreak failed\n", __func__);
        return -1;
    }

    if(ERR == noecho())
    {
        fprintf(stderr, "%s: noecho failed\n", __func__);
        return -1;
    }

    if(ERR == nonl())
    {
        fprintf(stderr, "%s: nonl failed\n", __func__);
        return -1;
    }

    if(ERR == intrflush(p_window, FALSE))
    {
        fprintf(stderr, "%s: intrflush failed\n", __func__);
        return -1;
    }

    if(ERR == keypad(p_window, TRUE))
    {
        fprintf(stderr, "%s: keypad failed\n", __func__);
        return -1;
    }

    p_buf = buf;
    *p_buf = '\0';
    while(ERR != (c = wgetch(p_window)))
    {
        int max_y;
        int max_x;

        if(KEY_BACKSPACE == c)
        {
            if(p_buf <= buf)
                continue;

            /* take a char off the end of buf */
            --p_buf;
            *p_buf = '\0';
        }
        else
        {
            if(p_buf >= (buf
                        + (sizeof(buf) / (sizeof(buf[0]))) - 1 /* NUL byte */))
                continue;

            /* add char onto end of buf */
            *p_buf = c;
            ++p_buf;
            *p_buf = '\0';
        }

        /* verify window height */
        getmaxyx(p_window, max_y, max_x);
        if(max_y < ROW_NUM)
        {
            fprintf(stderr, "%s: max_y too small: %d\n", __func__, max_y);
            return -1;
        }

        /* print string */
        mvwaddnstr(p_window, ROW_STRING, 0 /*start of line*/, ROW_STRING_PFX,
                -1 /*n up to EOL*/);
        waddnstr(p_window, buf, -1 /*n up to EOL*/);

        refresh();
    }

    return 0;
}

int main(void)
{
    WINDOW *p_window;
    int rc;

    if(!(p_window = initscr()))
    {
        fprintf(stderr, "%s: initscr failed\n", __func__);
        return EXIT_FAILURE;
    }

    rc = main_int(p_window);
    if(ERR == endwin())
    {
        fprintf(stderr, "%s: endwin failed\n", __func__);
        return EXIT_FAILURE;
    }

    if(rc)
    {
        fprintf(stderr, "%s: main_int failed\n", __func__);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
