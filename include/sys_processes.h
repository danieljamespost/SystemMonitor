#ifndef SYS_PROCESSES_H
#define SYS_PROCESSES_H

#include <string>
#include <vector>

#include "process.h"

class SystemProcesses {
 public:
  SystemProcesses() { Update(); }
  std::vector<Process>& All();
  int Total() { return total_; };
  int Running() { return running_; };
  void Update();

 private:
  int total_ = 0;
  int running_ = 0;
  std::vector<Process> processes_;
};

#endif