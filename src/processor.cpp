#include "processor.h"

#include <iostream>
#include <string>
#include <vector>

#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
  std::vector<std::string> cpuData = LinuxParser::CpuUtilization();

  float user = std::stof(cpuData[0]);
  float nice = std::stof(cpuData[1]);
  float system = std::stof(cpuData[2]);
  float idle = std::stof(cpuData[3]);
  float iowait = std::stof(cpuData[4]);
  float irq = std::stof(cpuData[5]);
  float softirq = std::stof(cpuData[6]);
  float steal = std::stof(cpuData[7]);
  float guest = std::stof(cpuData[8]);
  float guestNice = std::stof(cpuData[9]);

  float prevIdleTotal = idle_ + iowait_;
  float idleTotal = idle + iowait;

  float prevNonIdleTotal = user_ + nice_ + system_ + irq_ + softirq_ + steal_;
  float nonIdleTotal = user + nice + system + irq + softirq + steal;

  float prevTotal = prevIdleTotal + prevNonIdleTotal;
  float total = idleTotal + nonIdleTotal;

  //// differentiate : actual value minus the previous one;
  float totald = total - prevTotal;
  float idled = idleTotal - prevIdleTotal;

  float cpuPercentage = (totald - idled) / totald;

  user_ = user;
  nice_ = nice;
  system_ = system;
  idle_ = idle;
  iowait_ = iowait;
  irq_ = irq;
  softirq_ = softirq;
  steal_ = steal;
  guest_ = guest;
  guestNice_ = guestNice;

  return cpuPercentage;
}