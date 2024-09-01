#include "FindPathLayer.h"
#include "Renderer/Renderer2D.h"
#include <SFML/Graphics.hpp>
#include <string>

FindPathLayer::FindPathLayer() : Layer("FindPathLayer") { m_time = 0; }
static uint64_t gtime = 0;
constexpr const int FPS = 50;
constexpr const int SPF = 1000 / (double)FPS;

bool FindPathLayer::OnAppUpdate(AppUpdateEvent &e) { return true; }
bool FindPathLayer::OnKeyPressed(KeyPressedEvent &e) {
  switch (e.GetKeyCode()) {
  case sf::Keyboard::A:
    break;
  }
  return true;
}

void FindPathLayer::OnAttach() {
  PROFILE_FUNCTION();
  CORE_INFO("Attach");
  Application &app = Application::Get();
  m_window = static_cast<sf::RenderWindow *>(app.GetWindow().GetNativeWindow());
  Renderer2D::Init(m_window);
  Renderer2D::Clear(0, 0, 0);
}

void FindPathLayer::OnDetach() {
  PROFILE_FUNCTION();
  CORE_INFO("Detach");
}

void FindPathLayer::OnUpdate(Timestep &ts) {
  PROFILE_FUNCTION();
  gtime += ts.GetMilliseconds();
  if (gtime >= SPF) {
    gtime = gtime % SPF;
    Renderer2D::BeginScene();
    Renderer2D::Clear(255, 255, 255);
    for (int r = 0; r < ROW; r++) {
      for (int c = 0; c < COL; c++) {
        cells[r][c].FillColor = Colors[GRAY];
        cells[r][c].Draw(r, c);
      }
    }
    Renderer2D::EndScene();
  }
}

void FindPathLayer::OnGuiRender() { PROFILE_FUNCTION(); }

void FindPathLayer::OnEvent(Event &e) {
  EventDispatcher dispatcher(e);
  dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(OnKeyPressed));
  dispatcher.Dispatch<AppUpdateEvent>(BIND_EVENT_FN(OnAppUpdate));
}
