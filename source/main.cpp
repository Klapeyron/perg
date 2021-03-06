#include <ncurses.h>
#include <vector>
#include <string>

#include "ApplicationController.hpp"
#include "Region.hpp"
#include "Termkey.hpp"

int main(int argc, char ** argv)
{
  Termkey::init();
  initscr();
  keypad(stdscr, TRUE);
  start_color();
  init_pair(1, COLOR_BLACK, COLOR_RED);
  init_pair(2, COLOR_BLACK, COLOR_YELLOW);
  noecho();

  ApplicationController applicationController(Region::windowToRegion(stdscr));
  for (int i = 1; i < argc; i++)
    applicationController.openFile(argv[i]);
  applicationController.run();

  endwin();
}
