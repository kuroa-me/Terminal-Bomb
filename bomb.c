#include "bomb.h"

#include <curses.h>
#include <signal.h>
#include <unistd.h>

WINDOW *mywindow;

int main(int argc, char *argv[]) {
    // Initialize curses
    mywindow = initscr();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
    leaveok(stdscr, TRUE);
    scrollok(stdscr, FALSE);
    mvwprintw( mywindow, 0, 0, "Hello World %d", 123 );
    box( mywindow, ACS_VLINE, ACS_HLINE );
    getch();
    refresh();
    endwin();
    return 0;
}