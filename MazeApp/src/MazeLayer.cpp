#include "MazeLayer.h"
#include "Cell.h"
#include "FindPathLayer.h"
#include "Renderer/Renderer2D.h"
#include <SFML/Graphics.hpp>
#include <queue>
#include <random>

bool maze_done;
int r0, c0;
std::mt19937 m_mt;

bool visited[ROW * COL];
std::queue<std::pair<int, int>> history;
bool fixed[ROW * COL];
bool fixedCount = 0;

static uint64_t gtime = 0;
constexpr const int FPS = 200;
constexpr const int SPF = 1000 / (double)FPS;

Cell cells[ROW][COL];
std::vector<std::vector<int>> graph;
void DFS(int col, int row);
class Ground {
  int m_last_row;
  int m_last_col;

public:
  bool reset = false;
  Ground() {
    m_last_row = -1;
    m_last_col = -1;
  }
  void Init() {
    maze_done = false;
    reset = true;
    for (int i = 0; i < ROW; i++) {
      cells[i][0].block[LEFT] = true;
      cells[i][COL - 1].block[RIGHT] = true;
    }
    for (int i = 0; i < COL; i++) {
      cells[0][i].block[UP] = true;
      cells[ROW - 1][i].block[DOWN] = true;
    }
    m_mt = std::mt19937(200);
  }
  void Draw() {
    for (int r = 0; r < ROW; r++) {
      for (int c = 0; c < COL; c++) {
        cells[r][c].Draw(r, c);
      }
    }
  }
  void Update() {
    CORE_INFO("1111");
    if (reset) {
      graph.resize(ROW * COL);
      r0 = m_mt() % ROW;
      c0 = m_mt() % COL;
      visited[r0 * COL + c0] = true;
      history.push(std::make_pair(r0 * COL + c0, 0));
      fixed[r0 * COL + c0] = false;
      DFS(c0, r0);
      reset = false;
    } else {
      if (!history.empty()) {
        std::pair<int, int> h = history.front();
        history.pop();
        int r = h.first / COL;
        int c = h.first % COL;
        if (m_last_col >= 0 && m_last_row >= 0) {
          if (c > m_last_col) {
            cells[r][m_last_col].wall[RIGHT] = false;
            cells[r][c].wall[LEFT] = false;
          } else if (c < m_last_col) {
            cells[r][m_last_col].wall[LEFT] = false;
            cells[r][c].wall[RIGHT] = false;
          }
          if (r > m_last_row) {
            cells[m_last_row][c].wall[DOWN] = false;
            cells[r][c].wall[UP] = false;
          } else if (r < m_last_row) {
            cells[m_last_row][c].wall[UP] = false;
            cells[r][c].wall[DOWN] = false;
          }
        }
        m_last_row = r;
        m_last_col = c;
        if (h.second == 0) {
          cells[r][c].FillColor = Colors[PINK];
        } else if (h.second == 1) {
          cells[r][c].FillColor = Colors[BLUE];
        };
      } else {
        CORE_INFO("done");
        maze_done = true;
      }
    }
  }
};
Ground ground;

MazeLayer::MazeLayer() : Layer("MazeLayer") {}
void MazeLayer::OnUpdate(Timestep &ts) {
  PROFILE_FUNCTION();
  gtime += ts.GetMilliseconds();
  if (gtime >= SPF) {
    gtime = gtime % SPF;
    if (!maze_done) {
      ground.Update();
      Renderer2D::BeginScene();
      Renderer2D::Clear(255, 255, 255);
      ground.Draw();
      Renderer2D::EndScene();
    } else {
      Application &app = Application::Get();
      app.PopLayer(this);
      FindPathLayer *newLayer = new FindPathLayer();
      for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
          newLayer->cells[i][j] = cells[i][j];
        }
      }
      app.PushLayer(newLayer);
    }
  }
}

void MazeLayer::OnGuiRender() { PROFILE_FUNCTION(); }

void MazeLayer::OnEvent(Event &e) {
  EventDispatcher dispatcher(e);
  dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(OnKeyPressed));
  dispatcher.Dispatch<AppUpdateEvent>(BIND_EVENT_FN(OnAppUpdate));
}

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
  CORE_INFO("Attach");
  Application &app = Application::Get();
  m_window = static_cast<sf::RenderWindow *>(app.GetWindow().GetNativeWindow());
  Renderer2D::Init(m_window);
  ground.Init();
  Renderer2D::BeginScene();
  Renderer2D::Clear(255, 255, 255);
  ground.Draw();
  Renderer2D::EndScene();
}

void MazeLayer::OnDetach() { PROFILE_FUNCTION(); }

void DFS(int col, int row) {
  std::vector<int> openPath;
  for (int i = 0; i < 4; i++) {
    int r2, c2;
    r2 = row;
    c2 = col;
    switch (i) {
    case 0:
      r2 -= 1;
      break;
    case 1:
      r2 += 1;
      break;
    case 2:
      c2 -= 1;
      break;
    case 3:
      c2 += 1;
      break;
    }
    if (0 <= r2 && r2 < ROW && 0 <= c2 && c2 < COL) {
      int g = r2 * COL + c2;
      if (!visited[g]) {
        openPath.push_back(g);
      }
    }
  }
  if (openPath.size() > 0) {
    history.push(std::make_pair(row * COL + col, 0));
    int r, c;
    int next = openPath[m_mt() % openPath.size()];
    r = next / COL;
    c = next % COL;
    graph[row * COL + col].push_back(next);
    visited[next] = true;
    DFS(c, r);
  } else {
    history.push(std::make_pair(row * COL + col, 1));
    for (int i = 0; i < graph.size(); i++) {
      for (auto &it : graph[i]) {
        if (it == row * COL + col && visited[i]) {
          int r, c;
          r = i / COL;
          c = i % COL;
          DFS(c, r);
          return;
        }
      }
    }
  }
}
