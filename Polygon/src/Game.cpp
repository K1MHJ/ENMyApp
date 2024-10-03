#include "Game.h"
#include "Renderer/Renderer2D.h"
#include "SfmlPF.h"
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

typedef struct {
  float x;
  float y;
} Point;

std::vector<Point> points;
float minx, miny;
float maxx, maxy;
float wndx, wndy;
float scale;
unsigned int frame = 0;

Game::Game() {}
void Game::Init() {
  int i, j;
  m_mt = std::mt19937(100);
  wndx = wndy = 500;

  points.push_back({234.92100, -565.37400});
  points.push_back({-143.07900, -91.37400});
  points.push_back({-493.07900, -315.37400});
  points.push_back({-655.07900, 170.62700});
  points.push_back({-505.07900, 387.62700});
  points.push_back({-185.07900, 208.62700});
  points.push_back({30.92100, 565.62700});
  points.push_back({429.92100, 441.62700});
  points.push_back({654.92100, 66.62700});
  points.push_back(points[0]);

  maxy = maxx = -10000000;
  miny = minx = 10000000;

  for (auto p : points) {
    if (minx > p.x)
      minx = p.x;
    if (miny > p.y)
      miny = p.y;
    if (maxx < p.x)
      maxx = p.x;
    if (maxy < p.y)
      maxy = p.y;
  }
  scale = wndx / (maxx - minx);
  scale = std::min(scale, wndy / (maxy - miny));
}
void Game::Draw() {
  Application &app = Application::Get();
  sf::RenderWindow *m_window =
      static_cast<sf::RenderWindow *>(app.GetWindow().GetNativeWindow());
  Renderer2D::DrawLineRectangle(0, 0, 100, 100, {0, 0, 0, 255});
  Point p = points[0];
  p.x -= minx;
  p.y -= miny;
  for (int i = 1; i < points.size(); ++i) {
    Point p2 = points[i];
    p2.x -= minx;
    p2.y -= miny;
    Renderer2D::DrawLine(p.x * scale, p.y * scale, p2.x * scale, p2.y * scale,
                         1, {0, 0, 0, 255});
    p = p2;
  }
  Renderer2D::DrawLine(frame * 10, 0, frame * 10, 100, 1, {255, 0, 0, 255});
}
void Game::Update() { frame++; }
