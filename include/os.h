#ifndef OS_H
#define OS_H

#include <string>

class OS {
 public:
  OS();
  std::string Kernel();
  std::string Name();

 private:
  std::string kernel_;
  std::string name_;
};

#endif
