#include <iostream>

#include "ncurses_display.h"
#include "process.h"
#include "system.h"

int main() {
  System system;
  for (Process proc : system.Processes()) {
    std::cout << proc.Pid() << ": " << proc.CpuUtilization() << "\n";
  }
  // NCursesDisplay::Display(system);
}