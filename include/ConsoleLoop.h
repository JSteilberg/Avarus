#ifndef CONSOLELOOP_H
#define CONSOLELOOP_H

#include "Game.h"
#include "GameState.h"
#include "Logger.h"

class DebugOverlay;

class ConsoleLoop : public GameState {
public:
  ConsoleLoop(Game *game);

  // This is how the main loop do
  virtual void Update(const sf::Time &deltaTime, sf::Window &window) override;

  // This is how the drawing do
  virtual void Draw(sf::RenderWindow &window) override;

  virtual const string ToString() const override;

  void HandleKeyEvents(sf::Window &window);

  virtual ~ConsoleLoop();

private:
  Game *game_;
};

#endif // CONSOLELOOP_H
