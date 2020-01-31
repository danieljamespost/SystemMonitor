#include "format.h"

#include <sstream>
#include <string>

using std::string;

string Format::ElapsedTime(long secondsTotal)
{
    int hours = 60 * 60;
    int min = 60;

    int hoursElap = secondsTotal / hours;
    int minElap = (secondsTotal - (hoursElap * hours)) / min;
    int secElap = secondsTotal - ((hoursElap * hours) + (minElap * min));

    std::ostringstream out;
    out << hoursElap << ":" << minElap << ":" << secElap;

    return out.str();
}