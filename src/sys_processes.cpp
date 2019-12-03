#include "sys_processes.h"

#include <algorithm>
#include <vector>

#include "linux_parser.h"

std::vector<Process>& SystemProcesses::All() {
    return processes_;
}
void SystemProcesses::Update() {
  running_ = LinuxParser::RunningProcesses();
  total_ = LinuxParser::TotalProcesses();
  processes_.clear();
  for (int pid : LinuxParser::Pids()) {
    Process process(pid);
    processes_.push_back(process);
  }
  // this works locally but does not work in udacity workspace
  // std::sort(processes_.begin(), processes_.end(), [](auto a, auto b) {
  //     return a.CpuUtilization() > b.CpuUtilization();
  // });
}
