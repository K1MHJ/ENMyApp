#pragma once
#include <Core/EntryPoint.h>

void MainThread();
class MazeApp : public Application {
public:
  MazeApp(const ApplicationSpecification &specification)
      : Application(specification) {
    InitApp();
  }
  ~MazeApp() {}
  void InitApp();
  void MFunc();
};
