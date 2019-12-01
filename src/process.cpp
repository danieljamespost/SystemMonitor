#include "process.h"

#include <unistd.h>

#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

int Process::Pid() { return pid_; }

float Process::CpuUtilization() {
  vector<string> cpuData = LinuxParser::CpuUtilization(pid_);
  long uptime = LinuxParser::UpTime();

  long hz = sysconf(_SC_CLK_TCK);
  float utime = std::stof(cpuData[0]);
  float stime = std::stof(cpuData[1]);
  float cutime = std::stof(cpuData[2]);
  float cstime = std::stof(cpuData[3]);
  float starttime = std::stof(cpuData[4]);

  float total_time = utime + stime;
  total_time = total_time + cutime + cstime;
  float seconds = uptime - (starttime / hz);
  float cpu_usage = 100 * ((total_time / hz) / seconds);

  return cpu_usage;
}

// TODO: Return the command that generated this process
string Process::Command() { return string(); }

// TODO: Return this process's memory utilization
string Process::Ram() { return string(); }

string Process::User() {
  user_ = LinuxParser::User(pid_);
  return user_;
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return 0; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a [[maybe_unused]]) const {
  return true;
}