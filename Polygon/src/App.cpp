#include "App.h"
#include "AppLayer.h"
#include <functional>

Application *CreateApplication(ApplicationCommandLineArgs args) {
  ApplicationSpecification spec;
  spec.Name = "Polygon";
  spec.WorkingDirectory = "";
  spec.CommandLineArgs = args;
  spec.Width = 360 * 2;
  spec.Height = 360 * 2;
  return new MainApp(spec);
}
void MainApp::InitApp() {
  PushLayer(new AppLayer());
  std::function<void()> fn = [&]() { return MFunc(); };
  SubmitToMainThread(fn);
}
void MainApp::MFunc() { CORE_INFO("InitApp"); }
