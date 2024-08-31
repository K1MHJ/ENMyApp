#include "MazeLayer.h"
#include "Renderer/Renderer2D.h"
#include <SFML/Graphics.hpp>
#include <string>

MazeLayer::MazeLayer() : Layer("MazeLayer") {}

bool MazeLayer::OnAppUpdate(AppUpdateEvent &e) { return true; }
bool MazeLayer::OnKeyPressed(KeyPressedEvent &e) {
  switch (e.GetKeyCode()) {
  case sf::Keyboard::A:
    break;
  }
  return true;
}

void MazeLayer::OnAttach() {
  PROFILE_FUNCTION();
  Application &app = Application::Get();
  m_window = static_cast<sf::RenderWindow *>(app.GetWindow().GetNativeWindow());
  Renderer2D::Init(m_window);
  CORE_INFO("Attach");
  Renderer2D::Clear(0, 0, 0);
}

void MazeLayer::OnDetach() { PROFILE_FUNCTION(); }

void MazeLayer::OnUpdate(Timestep ts) {
  Color color_blue{0,100,0,255};
  PROFILE_FUNCTION();
  Renderer2D::Clear(0, 0, 0);
  Renderer2D::BeginScene();
  Renderer2D::DrawFillRectangle(0, 0, 100, 100, color_blue);
  // snprintf(text, 256, "Hello~ World!");
  // Renderer2D::DrawText(text, 0, 0, 30, sf::Color::Yellow);
  Renderer2D::EndScene();
}

void MazeLayer::OnGuiRender() { PROFILE_FUNCTION(); }

void MazeLayer::OnEvent(Event &e) {
  EventDispatcher dispatcher(e);
  dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(OnKeyPressed));
  dispatcher.Dispatch<AppUpdateEvent>(BIND_EVENT_FN(OnAppUpdate));
}
