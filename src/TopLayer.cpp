#include "TopLayer.h"
#include "Renderer/Renderer2D.h"
#include <SFML/Graphics.hpp>
#include <string>

TopLayer::TopLayer() : Layer("TopLayer") {}

bool TopLayer::OnAppUpdate(AppUpdateEvent &e) { return true; }
bool TopLayer::OnKeyPressed(KeyPressedEvent &e) {
  switch (e.GetKeyCode()) {
  case sf::Keyboard::A:
    break;
  }
  return true;
}

void TopLayer::OnAttach() {
  PROFILE_FUNCTION();
  Application &app = Application::Get();
  m_window = static_cast<sf::RenderWindow *>(app.GetWindow().GetNativeWindow());
  Renderer2D::Init(m_window);
  CORE_INFO("Attach");
  Renderer2D::Clear(0, 0, 0);
}

void TopLayer::OnDetach() { PROFILE_FUNCTION(); }

void TopLayer::OnUpdate(Timestep ts) {
  char text[256];
  PROFILE_FUNCTION();
  Renderer2D::Clear(0, 0, 0);
  Renderer2D::BeginScene();
  snprintf(text, 256, "Hello~ World!");
  Renderer2D::DrawText(text, 0, 0, 30, sf::Color::Yellow);
  Renderer2D::EndScene();
}

void TopLayer::OnGuiRender() { PROFILE_FUNCTION(); }

void TopLayer::OnEvent(Event &e) {
  EventDispatcher dispatcher(e);
  dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(OnKeyPressed));
  dispatcher.Dispatch<AppUpdateEvent>(BIND_EVENT_FN(OnAppUpdate));
}
