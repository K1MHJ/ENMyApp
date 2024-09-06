#pragma once
#include <Core/EntryPoint.h>

class MainApp : public Application {
public:
  MainApp(const ApplicationSpecification &specification)
      : Application(specification) {
    InitApp();
  }
  ~MainApp() {}
  void InitApp();
  void MFunc();
};
