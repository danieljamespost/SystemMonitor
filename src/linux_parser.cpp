#include "linux_parser.h"

#include <dirent.h>
#include <unistd.h>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

string LinuxParser::Kernel() {
  string os, kernel, version, line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

float LinuxParser::MemoryUtilization() {
  string line, key, value;
  string totalMemStr, freeMemStr;

  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "MemTotal:") {
        totalMemStr = value;
      } else if (key == "MemFree:") {
        freeMemStr = value;
      } else {
        // done reading file
        break;
      }
    }
  }

  float totalMem = std::stof(totalMemStr);
  float freeMem = std::stof(freeMemStr);

  float used = totalMem - freeMem;
  float utilization = used / totalMem;

  return utilization;
}

long LinuxParser::UpTime() {
  string totalTimeStr, idleTimeStr, line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> totalTimeStr >> idleTimeStr;
  }
  long totalTime = std::stol(totalTimeStr);
  return totalTime;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid [[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

vector<string> LinuxParser::CpuUtilization() {
  // time units in USER_HZ (typically hundredths of a second)
  // user  nice system  idle    iowait irq  softirq  steal  guest  guest_nice
  // 49637 0    92930   9236181 4743   0    3915     0      0      0

  string line, key;
  string userStr, niceStr, systemStr, idleStr, iowaitStr, irqStr, softirqStr,
      stealStr, guestStr, guestNiceStr;

  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> userStr >> niceStr >> systemStr >> idleStr >>
          iowaitStr >> irqStr >> softirqStr >> stealStr >> guestStr >>
          guestNiceStr;
      if (key != "cpu") {
        break;
      }
    }
  }
  return {userStr, niceStr,    systemStr, idleStr,  iowaitStr,
          irqStr,  softirqStr, stealStr,  guestStr, guestNiceStr};
}

vector<string> LinuxParser::CpuUtilization(int pid) {
  string utime, stime, cutime, cstime, starttime;
  string line;

  std::ostringstream filename;
  filename << kProcDirectory << pid << kStatFilename;

  std::ifstream stream(filename.str());
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);

      std::vector<std::string> tokens;
      std::string token;
      std::istringstream tokenStream(line);
      while (std::getline(tokenStream, token, ' ')) {
        tokens.push_back(token);
      }

      utime = tokens[15];
      stime = tokens[16];
      cutime = tokens[17];
      cstime = tokens[18];
      starttime = tokens[23];
    }
  }

  return {utime, stime, cutime, cstime, starttime};
}

int LinuxParser::TotalProcesses() {
  string line, key, value;
  string totalProcString;

  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "processes") {
        totalProcString = value;
      }
    }
  }

  float totalProc = std::stoi(totalProcString);

  return totalProc;
}

int LinuxParser::RunningProcesses() {
  string line, key, value;
  string runningProcString;

  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "procs_running") {
        runningProcString = value;
      }
    }
  }

  float runningProc = std::stoi(runningProcString);

  return runningProc;
}

string LinuxParser::Command(int pid) {
  string line, command;

  std::ostringstream filename;
  filename << kProcDirectory << pid << kCmdlineFilename;

  std::ifstream stream(filename.str());
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> command;
    }
  }

  return command;
}

string LinuxParser::Ram(int pid) {
  string line, key, value;
  string ramStr;

  std::ostringstream filename;
  filename << kProcDirectory << pid << kStatusFilename;

  std::ifstream stream(filename.str());
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "VmSize:") {
        ramStr = value;
      }
    }
  }
  return ramStr;
}

string LinuxParser::Uid(int pid) {
  string line, key, value;
  string uid;

  std::ostringstream filename;
  filename << kProcDirectory << pid << kStatusFilename;

  std::ifstream stream(filename.str());
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "Uid:") {
        uid = value;
      }
    }
  }

  return uid;
}

string LinuxParser::User(int pid) {
  string userId = Uid(pid);
  string line, name, password, uid;
  string user;
  std::ifstream stream(kPasswordPath);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);

      std::vector<std::string> tokens;
      std::string token;
      std::istringstream tokenStream(line);
      while (std::getline(tokenStream, token, ':')) {
        tokens.push_back(token);
      }

      name = tokens[0];
      uid = tokens[2];
      if (uid == userId) {
        user = name;
        break;
      }
    }
  }

  return user;
}

long LinuxParser::UpTime(int pid) {
  string starttimeStr;
  string line;

  std::ostringstream filename;
  filename << kProcDirectory << pid << kStatFilename;

  std::ifstream stream(filename.str());
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);

      std::vector<std::string> tokens;
      std::string token;
      std::istringstream tokenStream(line);
      while (std::getline(tokenStream, token, ' ')) {
        tokens.push_back(token);
      }

      starttimeStr = tokens[23];
    }
  }

  return stol(starttimeStr);
}
