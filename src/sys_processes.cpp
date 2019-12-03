#include "sys_processes.h"

#include <algorithm>
#include <vector>

#include "linux_parser.h"

void SystemProcesses::Update() {
  running_ = LinuxParser::RunningProcesses();
  total_ = LinuxParser::TotalProcesses();
  processes_.clear();
  for (int pid : LinuxParser::Pids()) {
    Process process(pid);
    processes_.push_back(process);
  }
  std::sort(processes_.begin(), processes_.end(), [](auto a, auto b) {
    return a.CpuUtilization() > b.CpuUtilization();
  });
}
