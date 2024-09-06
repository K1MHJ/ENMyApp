#include <random>

class Game {
  std::mt19937 m_mt;

public:
  Game();
  void Init();
  void Draw();
  void Update();
};
