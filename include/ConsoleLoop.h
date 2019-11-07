#ifndef CONSOLELOOP_H
#define CONSOLELOOP_H

//#include "DebugOverlay.h"
#include "GameState.h"

class DebugOverlay;

class ConsoleLoop : public GameState {
  ConsoleLoop(Game &game);

  // This is how the main loop do
  virtual void Update(const sf::Time &deltaTime, sf::Window &window) override;

  // This is how the drawing do
  virtual void Draw(sf::RenderWindow &window) override;

  virtual const string ToString() const override;

  virtual ~ConsoleLoop();
};

#endif // CONSOLELOOP_H
