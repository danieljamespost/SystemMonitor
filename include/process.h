#ifndef PROCESS_H
#define PROCESS_H

#include <string>

class Process {
public:
    Process(int pid)
        : pid_(pid)
    {
        init();
    };
    int Pid();
    std::string User();
    std::string Command();
    float CpuUtilization();
    std::string Ram();
    long int UpTime();

private:
    void init();
    const int pid_;
    std::string user_ = std::string();
    long hz_ = 0;
    float utime_ = 0.0;
    float stime_ = 0.0;
    float cutime_ = 0.0;
    float cstime_ = 0.0;
    float starttime_ = 0.0;
    float cpu_usage_ = 0.0;
};

#endif
