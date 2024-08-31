#include "MazeApp.h"
#include "LogoLayer.h"
#include "MazeLayer.h"
#include <functional>

Application *CreateApplication(ApplicationCommandLineArgs args) {
  ApplicationSpecification spec;
  spec.Name = "Maze";
  spec.WorkingDirectory = "";
  spec.CommandLineArgs = args;
  spec.Width = 600;
  spec.Height = 600;
  return new MazeApp(spec);
}
void MazeApp::InitApp() {
  PushLayer(new LogoLayer());
  std::function<void()> fn = &MainThread;
  SubmitToMainThread(fn);
}
void MainThread() { CORE_INFO("InitApp"); }
