#include "process.h"

#include <unistd.h>

#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

void Process::init() {
  vector<string> cpuData = LinuxParser::CpuUtilization(pid_);
  hz_ = sysconf(_SC_CLK_TCK);
  utime_ = std::stof(cpuData[0]);
  stime_ = std::stof(cpuData[1]);
  cutime_ = std::stof(cpuData[2]);
  cstime_ = std::stof(cpuData[3]);
  starttime_ = std::stof(cpuData[4]);
}

int Process::Pid() { return pid_; }

float Process::CpuUtilization() {
  vector<string> cpuData = LinuxParser::CpuUtilization(pid_);
  long uptime = LinuxParser::UpTime();
  hz_ = sysconf(_SC_CLK_TCK);
  utime_ = std::stof(cpuData[0]);
  stime_ = std::stof(cpuData[1]);
  cutime_ = std::stof(cpuData[2]);
  cstime_ = std::stof(cpuData[3]);
  starttime_ = std::stof(cpuData[4]);

  float total_time = utime_ + stime_;
  total_time = total_time + cutime_ + cstime_;
  float seconds = uptime - (starttime_ / hz_);
  float cpu_usage = 100 * ((total_time / hz_) / seconds);

  return cpu_usage;
}

string Process::Command() { return LinuxParser::Command(pid_); }

string Process::Ram() {
  int ram = stoi(LinuxParser::Ram(pid_)) / 1000;

  std::ostringstream mem;
  mem << ram << " Mb";

  return mem.str();
}

string Process::User() {
  user_ = LinuxParser::User(pid_);
  return user_;
}

long int Process::UpTime() {
  return LinuxParser::UpTime(pid_);
}

bool Process::operator>(Process const& a) const {
  int aRam = std::stoi(LinuxParser::Ram(a.pid_));
  int ram = std::stoi(LinuxParser::Ram(pid_));
  return ram > aRam;
}

bool Process::operator=(Process const& a) const {
  int aRam = std::stoi(LinuxParser::Ram(a.pid_));
  int ram = std::stoi(LinuxParser::Ram(pid_));
  return ram == aRam;
}
