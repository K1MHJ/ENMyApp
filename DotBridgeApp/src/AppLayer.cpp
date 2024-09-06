#include "AppLayer.h"
#include "Renderer/Renderer2D.h"
#include <SFML/Graphics.hpp>
#include <random>

std::mt19937 m_mt;

static uint64_t gtime = 0;
constexpr const int FPS = 1000;
constexpr const int SPF = 1000 / (double)FPS;

class Game {
public:
  Game() {}
  void Init() { m_mt = std::mt19937(200); }
  void Draw() {}
  void Update() {}
};
Game game;

AppLayer::AppLayer() : Layer("AppLayer") {}
void AppLayer::OnUpdate(Timestep &ts) {
  PROFILE_FUNCTION();
  gtime += ts.GetMilliseconds();
  if (gtime >= SPF) {
    gtime = gtime % SPF;
    game.Update();
    Renderer2D::BeginScene();
    Renderer2D::Clear(255, 255, 255);
    game.Draw();
    Renderer2D::EndScene();
  }
}

void AppLayer::OnGuiRender() { PROFILE_FUNCTION(); }

void AppLayer::OnEvent(Event &e) {
  EventDispatcher dispatcher(e);
  dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(OnKeyPressed));
  dispatcher.Dispatch<AppUpdateEvent>(BIND_EVENT_FN(OnAppUpdate));
}

bool AppLayer::OnAppUpdate(AppUpdateEvent &e) { return true; }
bool AppLayer::OnKeyPressed(KeyPressedEvent &e) {
  switch (e.GetKeyCode()) {
  case sf::Keyboard::A:
    break;
  }
  return true;
}

void AppLayer::OnAttach() {
  PROFILE_FUNCTION();
  CORE_INFO("Attach");
  Application &app = Application::Get();
  m_window = static_cast<sf::RenderWindow *>(app.GetWindow().GetNativeWindow());
  Renderer2D::Init(m_window);
  game.Init();
  Renderer2D::BeginScene();
  Renderer2D::Clear(255, 255, 255);
  game.Draw();
  Renderer2D::EndScene();
}

void AppLayer::OnDetach() { PROFILE_FUNCTION(); }
