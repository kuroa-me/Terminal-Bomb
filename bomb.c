#include "bomb.h"

#include <curses.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static void finish(int sig);
int add_bombl();
int add_bombs();
int add_explo();

int color_changer(char str) {
  switch (str) {
    case 'P':
      attron(A_BOLD);
      attron(COLOR_PAIR(1));
      break;
    case 'R':
      attroff(A_BOLD);
      attron(COLOR_PAIR(1));
      break;
    case 'Y':
      attron(A_BOLD);
      attron(COLOR_PAIR(2));
    case 'O':
      attroff(A_BOLD);
      attron(COLOR_PAIR(2));
      break;
    default:
      attroff(A_BOLD);
      attron(COLOR_PAIR(0));
  }
  return OK;
}

int my_mvaddstr(int y, int x, char *str) {
  for (; x < 0; ++x) {
    if (*str == '\0') return ERR;
  }
  for (; *str != '\0'; ++x, ++str) {
    if (*str != ' ') {
      color_changer(*str);
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
  // Init color pairs
  start_color();
  init_pair(0, COLOR_WHITE, COLOR_BLACK);
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_YELLOW, COLOR_BLACK);

  int total = 4;
  for (; total > 0; --total) {
    if (total % 2)
      add_bombl();
    else
      add_bombs();
    refresh();
    usleep(300000);
    clear();
  }
  add_explo();
  refresh();
  usleep(500000);

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
    my_mvaddstr(y + i, x, bombl[i]);
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
    my_mvaddstr(y + i, x, bombs[i]);
  }

  return OK;
}

int add_explo() {
  static char *bombs[EXPLO_HEIGHT] = {
      EXPLO1,  EXPLO2,  EXPLO3,  EXPLO4,  EXPLO5,  EXPLO6,  EXPLO7,  EXPLO8,
      EXPLO9,  EXPLO10, EXPLO11, EXPLO12, EXPLO13, EXPLO14, EXPLO15, EXPLO16,
      EXPLO17, EXPLO18, EXPLO19, EXPLO20, EXPLO21, EXPLO22, EXPLO23, EXPLO24};

  int i, y, x;
  // Find start point
  y = LINES / 2 - EXPLO_HEIGHT / 2;
  x = COLS / 2 - EXPLO_WIDTH / 2;

  for (i = 0; i < EXPLO_HEIGHT; i++) {
    my_mvaddstr(y + i, x, bombs[i]);
  }

  return OK;
}

static void finish(int sig) {
  // system("reset");
  endwin();
  // No scroll back clear
  system("clear && printf '\e[3J'");
  exit(0);
}