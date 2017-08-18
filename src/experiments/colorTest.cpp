#include <curses.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#include <string.h>
 
#define PROGNAME "curses_init"
#define REQD_COLOR_PAIRS (5)
#define REQD_COLS (40)
#define REQD_LINES (7)

int main(void)
{

    if (!isatty(1) || initscr() == NULL) {
        fprintf(stderr, "%s: This program must be run from a terminal!\n",
                PROGNAME);
        return EXIT_FAILURE;
    }

    scrollok(stdscr, TRUE);
    // printw("This terminal supports %d colors\n", sizeof(COLOR_PAIRS));
    start_color();
    printw("This terminal supports %d colors\n", COLORS);

    for (int i = 0; i < COLORS; i++)
    {
        /* code */
        init_pair(i, i, COLOR_BLACK);
        attron(COLOR_PAIR(i));
        printw("This is color pair %d\n", i);
    }
        
    refresh();
    attron(COLOR_PAIR(4) | A_BOLD );
    mvprintw(LINES-1,0,"Press any key to end the program...");
    refresh();
    getch();
    endwin();
}