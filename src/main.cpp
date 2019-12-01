#include <iostream>

#include "format.h"
#include "ncurses_display.h"
#include "system.h"

int main() {
  System system;
  // system.Cpu().Utilization();
  NCursesDisplay::Display(system);
}