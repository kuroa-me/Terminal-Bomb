#include "bomb.h"

#include <curses.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static void finish(int sig);
int add_bombl();
int add_bombs();

int my_mvaddstr(int y, int x, char *str) {
  for (; x < 0; ++x) {
    if (*str == '\0') return ERR;
  }
  for (; *str != '\0'; ++x, ++str) {
    if (*str != ' ') {
      if (mvaddch(y, x, *str) == ERR) return ERR;
    }
  }
  return OK;
}

int main(int argc, char *argv[]) {
  signal(SIGINT, finish);
  // Initialize curses
  initscr();
  noecho();
  curs_set(0);
  nodelay(stdscr, TRUE);
  leaveok(stdscr, TRUE);
  scrollok(stdscr, FALSE);

  char *temp = malloc(100);

  int total = 10;
  for( ; total>0; --total){
    if(total%2) add_bombs();
    else add_bombl();
    sprintf(temp, "%d", total%2);
    addstr(temp);
    refresh();
    usleep(400000);
    clear();
  }

  // Clean up
  finish(0);
}

int add_bombl() {
  // Create set of bomb lines
  static char *bombl[BOMBL_HEIGHT] = {
      BOMBL1,  BOMBL2,  BOMBL3,  BOMBL4,  BOMBL5,  BOMBL6,  BOMBL7,  BOMBL8,
      BOMBL9,  BOMBL10, BOMBL11, BOMBL12, BOMBL13, BOMBL14, BOMBL15, BOMBL16,
      BOMBL17, BOMBL18, BOMBL19, BOMBL20, BOMBL21, BOMBL22, BOMBL23, BOMBL24};

  int i, y, x;
  // Find start point
  y = LINES / 2 - BOMBL_HEIGHT / 2;
  x = COLS / 2 - BOMBL_WIDTH / 2;

  for (i = 0; i < BOMBL_HEIGHT; i++) {
    mvaddstr(y + i, x, bombl[i]);
  }

  return OK;
}

int add_bombs() {
  static char *bombs[BOMBS_HEIGHT] = {
      BOMBS1,  BOMBS2,  BOMBS3,  BOMBS4,  BOMBS5,  BOMBS6,  BOMBS7,  BOMBS8,
      BOMBS9,  BOMBS10, BOMBS11, BOMBS12, BOMBS13, BOMBS14, BOMBS15, BOMBS16,
      BOMBS17, BOMBS18, BOMBS19, BOMBS20, BOMBS21, BOMBS22};

  int i, y, x;
  // Find start point
  y = LINES / 2 - BOMBS_HEIGHT / 2;
  x = COLS / 2 - BOMBS_WIDTH / 2;

  for (i = 0; i < BOMBS_HEIGHT; i++) {
    mvaddstr(y + i, x, bombs[i]);
  }

  return OK;
}

static void finish(int sig) {
  //system("reset");
  endwin();
  // No scroll back clear
  system("clear && printf '\e[3J'");
  exit(0);
}
