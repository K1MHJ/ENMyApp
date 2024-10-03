#include "Game.h"
#include "Renderer/Renderer2D.h"
#include "SfmlPF.h"
#include <SFML/Graphics.hpp>
using namespace sf;

struct pxl {
  unsigned char r;
  unsigned char g;
  unsigned char b;
  unsigned char t;
};
std::vector<pxl> Pxls = {{255, 0, 0, 255}, {255, 0, 255, 255}};
constexpr static int ROW = 32;
constexpr static int COL = 32;
constexpr static float SCALE = 10.0;
constexpr static float OffsetX = 2;
constexpr static float OffsetY = 2;
Texture tex;
Sprite spr;
Image img;
pxl *pxlPtr;
Uint8 map[ROW][COL];


void InitMap() {
  for (int i = 0; i < ROW; i++) {
    for (int j = 0; j < COL; j++) {
      map[i][j] = 0;
      pxl *ptr = pxlPtr + i * COL + j;
      *ptr = {255, 255, 255, 255};
    }
  }
}
Uint8 GetMap(int row, int col) { return map[row][col]; }
void SetMap(int row, int col, Uint8 val) {
  map[row][col] = val;
  pxl *ptr = pxlPtr + row * COL + col;
  if (val < 2) {
    *ptr = Pxls[val];
  } else {
    *ptr = {0, 0, 0, 255};
  }
}

Game::Game() {}
void Game::Init() {
  int i, j;
  m_mt = std::mt19937(100);
  img.create(COL, ROW, {255, 255, 255, 255});
  pxlPtr = (pxl *)img.getPixelsPtr();
  InitMap();
  tex.loadFromImage(img);
  spr.setTexture(tex);
  spr.setScale(SCALE, SCALE);
  
  

}
void Game::Draw() {
  SetMap(2, 2, 0);
  SetMap(ROW - 1, COL - 1, 1);

  tex.loadFromImage(img);
  spr.setTexture(tex);
  spr.setScale(SCALE, SCALE);
  spr.setPosition(OffsetX, OffsetY);
  Application &app = Application::Get();
  sf::RenderWindow *m_window =
      static_cast<sf::RenderWindow *>(app.GetWindow().GetNativeWindow());
  Renderer2D::DrawLineRectangle(OffsetX, OffsetY, COL * SCALE, ROW * SCALE,
                                {0, 0, 0, 255});
  m_window->draw(spr);
}
void Game::Update() {}
