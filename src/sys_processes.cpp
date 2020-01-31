#include "sys_processes.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "linux_parser.h"

std::vector<Process>& SystemProcesses::All() { return processes_; }

void SystemProcesses::Update()
{
    running_ = LinuxParser::RunningProcesses();
    total_ = LinuxParser::TotalProcesses();
    processes_.clear();

    char* user(getenv("USER"));
    for (int pid : LinuxParser::Pids()) {
        Process process(pid);

        // if $USER is set, only show processes for that user
        if (user != NULL) {
            if (process.User() == user) {
                processes_.push_back(process);
            }
        } else {
            processes_.push_back(process);
        }
    }
}
