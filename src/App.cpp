#include "TopLayer.h"
#include "SfmlPF.h"
#include <Core/EntryPoint.h>

class MyApp : public Application {
public:
  MyApp(const ApplicationSpecification &specification)
      : Application(specification) {
    PushLayer(new TopLayer());
  }
  ~MyApp() {}
};
Application *CreateApplication(ApplicationCommandLineArgs args) {
  ApplicationSpecification spec;
  spec.Name = "AppTemplate";
  spec.WorkingDirectory = "";
  spec.CommandLineArgs = args;
  spec.Width = 600;
  spec.Height = 800;

  return new MyApp(spec);
}
