#pragma once

#include "SfmlPF.h"
#include <Events/KeyEvent.h>
#include <SFML/Graphics.hpp>

class MazeLayer : public Layer {
public:
  MazeLayer();
  virtual ~MazeLayer() = default;

  virtual void OnAttach() override;
  virtual void OnDetach() override;

  void OnUpdate(Timestep ts) override;
  virtual void OnGuiRender() override;
  void OnEvent(Event &e) override;

private:
  sf::RenderWindow *m_window;
  bool OnKeyPressed(KeyPressedEvent &e);
  bool OnAppUpdate(AppUpdateEvent &e);
};
