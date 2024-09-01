#pragma once
#include <Core/EntryPoint.h>

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
