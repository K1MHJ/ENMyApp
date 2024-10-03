#pragma once
#include "SfmlPF.h"
#include <Core/EntryPoint.h>
#include <SFML/Graphics.hpp>

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
