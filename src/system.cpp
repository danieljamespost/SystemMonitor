#include "system.h"

#include <unistd.h>

#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"
#include "processor.h"
#include "sys_processes.h"

using std::size_t;
using std::string;
using std::vector;

Processor& System::Cpu() { return cpu_; }

vector<Process>& System::Processes() {
  processes_.Update();
  return processes_.All();
}

std::string System::Kernel() { return os_.Kernel(); }

float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

std::string System::OperatingSystem() { return os_.Name(); }

int System::RunningProcesses() { return processes_.Running(); }

int System::TotalProcesses() { return processes_.Total(); }

long int System::UpTime() { return LinuxParser::UpTime(); }
