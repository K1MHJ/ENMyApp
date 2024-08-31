#pragma once

#include "SfmlPF.h"
#include <Events/KeyEvent.h>
#include <SFML/Graphics.hpp>

class TopLayer : public Layer {
public:
  TopLayer();
  virtual ~TopLayer() = default;

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
