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
int paint_string(WINDOW *p_window, int *p_y, int x_max, const char *p_buf)
{
    int x;

    if(ERR == mvwaddstr(p_window, *p_y, 0 /*start of line*/, "S: "))
    {
        fprintf(stderr, "%s: mvwaddstr failed\n", __func__);
        return -1;
    }

    x = getcurx(p_window);

    if(ERR == waddnstr(p_window, p_buf, x_max - x))
    {
        fprintf(stderr, "%s: waddnstr failed\n", __func__);
        return -1;
    }

    ++*p_y;
    return 0;
}

/**
 * TODO
 */
int paint_ascii(WINDOW *p_window, int *p_y, int x_max, const char *p_buf,
        const char *p_buf_end)
{
    int x;

    if(p_buf == p_buf_end)
        return 0;

    if(ERR == mvwaddstr(p_window, *p_y, 0 /*start of line*/, "A: "))
    {
        fprintf(stderr, "%s: mvwaddstr failed\n", __func__);
        return -1;
    }

    x = getcurx(p_window);

    if(((x_max - x) / 2) < (p_buf_end - p_buf))
        p_buf_end = p_buf + ((x_max - x) / 2);

    for(; p_buf < p_buf_end; ++p_buf)
    {
        if(ERR == wprintw(p_window, "%02x", (unsigned)*p_buf))
        {
            fprintf(stderr, "%s: mvwprintw failed\n", __func__);
            return -1;
        }
    }

    ++*p_y;
    return 0;
}

/**
 * TODO
 */
int paint_dec(WINDOW *p_window, int *p_y, int x_max, const char *p_buf)
{
    char *p_buf_parse_end;
    long long val;
    char buf[32 /*larger then LLONG_MAX + 1 NUL byte*/];
    int rc;

    errno = 0;
    val = strtoll(p_buf, &p_buf_parse_end, 16 /*base*/);
    if((p_buf == p_buf_parse_end) || (*p_buf_parse_end != '\0')
            || (errno == ERANGE))
        return 0;

    if((rc = snprintf(buf, sizeof(buf), "D: %lld", val)) < 0)
    {
        fprintf(stderr, "%s: snprintf failed\n", __func__);
        return -1;
    }

    /* if too long */
    if(rc > x_max)
        return 0;

    if(ERR == mvwaddstr(p_window, *p_y, 0 /*start of line*/, buf))
    {
        fprintf(stderr, "%s: mvwaddstr failed\n", __func__);
        return -1;
    }

    ++*p_y;
    return 0;
}

/**
 * TODO
 */
int paint_hex(WINDOW *p_window, int *p_y, int x_max, const char *p_buf)
{
    char *p_buf_parse_end;
    long long val;
    char buf[32 /*larger then LLONG_MAX + 1 NUL byte*/];
    int rc;

    errno = 0;
    val = strtoll(p_buf, &p_buf_parse_end, 10 /*base*/);
    if((p_buf == p_buf_parse_end) || (*p_buf_parse_end != '\0')
            || (errno == ERANGE))
        return 0;

    if((rc = snprintf(buf, sizeof(buf), "H: %llx", val)) < 0)
    {
        fprintf(stderr, "%s: snprintf failed\n", __func__);
        return -1;
    }

    /* if too long */
    if(rc > x_max)
        return 0;

    if(ERR == mvwaddstr(p_window, *p_y, 0 /*start of line*/, buf))
    {
        fprintf(stderr, "%s: mvwaddstr failed\n", __func__);
        return -1;
    }

    ++*p_y;
    return 0;
}

/**
 * TODO
 */
int paint_window(WINDOW *p_window, const char *p_buf, const char *p_buf_end)
{
    int y;
    int y_max;
    int x_max;

    /* clear screen */
    if(ERR == werase(p_window))
    {
        fprintf(stderr, "%s: werase failed\n", __func__);
        return -1;
    }

    /* verify window height */
    getmaxyx(p_window, y_max, x_max);
    y = 1;  /* paint top row last */

    if((y < y_max) && paint_ascii(p_window, &y, x_max, p_buf, p_buf_end))
    {
        fprintf(stderr, "%s: paint_ascii failed\n", __func__);
        return -1;
    }

    if((y < y_max) && paint_dec(p_window, &y, x_max, p_buf))
    {
        fprintf(stderr, "%s: paint_dec failed\n", __func__);
        return -1;
    }

    if((y < y_max) && paint_hex(p_window, &y, x_max, p_buf))
    {
        fprintf(stderr, "%s: paint_hex failed\n", __func__);
        return -1;
    }

    y = 0;  /* fill in top row */
    if((y < y_max) && paint_string(p_window, &y, x_max, p_buf))
    {
        fprintf(stderr, "%s: paint_string failed\n", __func__);
        return -1;
    }


    if(ERR == wrefresh(p_window))
    {
        fprintf(stderr, "%s: wrefresh failed\n", __func__);
        return -1;
    }

    return 0;
}

/**
 * TODO
 */
int main_int(WINDOW *p_window)
{
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
        return -1; } 
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
    if(paint_window(p_window, buf, p_buf))
    {
        fprintf(stderr, "%s: paint_window failed\n", __func__);
        return -1;
    }

    while(ERR != (c = wgetch(p_window)))
    {
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

        if(paint_window(p_window, buf, p_buf))
        {
            fprintf(stderr, "%s: paint_window failed\n", __func__);
            return -1;
        }
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
