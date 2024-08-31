#include "LogoLayer.h"
#include "MazeLayer.h"
#include "Renderer/Renderer2D.h"
#include <SFML/Graphics.hpp>
#include <string>

LogoLayer::LogoLayer() : Layer("LogoLayer") {
  m_time = 0;
}

bool LogoLayer::OnAppUpdate(AppUpdateEvent &e) { return true; }
bool LogoLayer::OnKeyPressed(KeyPressedEvent &e) {
  switch (e.GetKeyCode()) {
  case sf::Keyboard::A:
    break;
  }
  return true;
}

void LogoLayer::OnAttach() {
  PROFILE_FUNCTION();
  Application &app = Application::Get();
  m_window = static_cast<sf::RenderWindow *>(app.GetWindow().GetNativeWindow());
  Renderer2D::Init(m_window);
  CORE_INFO("Attach");
  Renderer2D::Clear(0, 0, 0);
}

void LogoLayer::OnDetach() {
  PROFILE_FUNCTION();
  CORE_INFO("Detach");
}

void LogoLayer::OnUpdate(Timestep& ts) {
  PROFILE_FUNCTION();
  m_time += ts.GetMilliseconds();
  Color color_blue{255, 255, 255, 255};
  AppUpdateEvent e;
  Application::Get().OnEvent(e);
  Renderer2D::Clear(0, 0, 0);
  Renderer2D::BeginScene();
  Renderer2D::DrawFillRectangle(0, 0, 100, 100, color_blue);
  Renderer2D::EndScene();

  if (m_time >= 1000) {
    Application &app = Application::Get();
    app.PopLayer(this);
    app.PushLayer(new MazeLayer());
  }
}

void LogoLayer::OnGuiRender() { PROFILE_FUNCTION(); }

void LogoLayer::OnEvent(Event &e) {
  EventDispatcher dispatcher(e);
  dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(OnKeyPressed));
  dispatcher.Dispatch<AppUpdateEvent>(BIND_EVENT_FN(OnAppUpdate));
}
