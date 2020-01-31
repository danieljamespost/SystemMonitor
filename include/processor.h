#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
public:
    float Utilization();

private:
    float user_ = 0.0;
    float nice_ = 0.0;
    float system_ = 0.0;
    float idle_ = 0.0;
    float iowait_ = 0.0;
    float irq_ = 0.0;
    float softirq_ = 0.0;
    float steal_ = 0.0;
    float guest_ = 0.0;
    float guestNice_ = 0.0;
};

#endif