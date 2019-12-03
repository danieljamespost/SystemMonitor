#include "os.h"

#include <string>

#include "linux_parser.h"

using std::string;

OS::OS() {
  kernel_ = LinuxParser::Kernel();
  name_ = LinuxParser::OperatingSystem();
}

string OS::Kernel() { return kernel_; }
string OS::Name() { return name_; }
