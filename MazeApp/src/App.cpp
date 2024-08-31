#include "MazeLayer.h"
#include <Core/EntryPoint.h>

class MazeApp : public Application {
public:
  MazeApp(const ApplicationSpecification &specification)
      : Application(specification) {
    PushLayer(new MazeLayer());
  }
  ~MazeApp() {}
};
Application *CreateApplication(ApplicationCommandLineArgs args) {
  ApplicationSpecification spec;
  spec.Name = "Maze";
  spec.WorkingDirectory = "";
  spec.CommandLineArgs = args;
  spec.Width = 600;
  spec.Height = 600;

  return new MazeApp(spec);
}
