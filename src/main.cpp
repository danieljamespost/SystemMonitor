#include <iostream>

#include "ncurses_display.h"
#include "process.h"
#include "system.h"

int main()
{
    System system;
    NCursesDisplay::Display(system);
}