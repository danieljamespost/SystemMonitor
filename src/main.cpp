#include <iostream>

#include "ncurses_display.h"
#include "process.h"
#include "system.h"

int main() {
  System system;
  // for (Process proc : system.Processes()) {
  // std::cout << "pid: " << proc.Pid() << "\n";
  // std::cout << "user: " << proc.User() << "\n";
  // std::cout << "command: " << proc.Command() << "\n";
  // std::cout << "cpu: " << proc.CpuUtilization() << "\n";
  // std::cout << "ram: " << proc.Ram() << "\n";
  // std::cout << "uptime: " << proc.UpTime() << "\n";
  // std::cout << "\n\n";
  //}
  // bool isGreater = system.Processes()[0] < system.Processes()[1];
  // std::cout << "greater: " << isGreater << "\n\n";
  NCursesDisplay::Display(system);
}