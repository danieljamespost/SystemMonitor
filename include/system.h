#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "os.h"
#include "process.h"
#include "sys_processes.h"
#include "processor.h"

class System {
 public:
  Processor& Cpu();
  std::vector<Process>& Processes();
  float MemoryUtilization();
  long UpTime();
  int TotalProcesses();
  int RunningProcesses();
  std::string Kernel();
  std::string OperatingSystem();

 private:
  Processor cpu_ = {};
  SystemProcesses processes_;
  OS os_;
};

#endif
