#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>
#include <string>

using std::string;

class Game;

// Usually going on an std::stack of GameStates, an instance of GameState
// represents a specific mode the Game is currently in.
class GameState {
public:
  // Creates a GameState with no attributes
  GameState();

  // This method should be called during every update in the main Game loop
  virtual void Update(const sf::Time &deltaTime, sf::Window &window) = 0;

  virtual void Draw(sf::RenderWindow &window) = 0;

  virtual const string ToString() const = 0;

  virtual ~GameState();

protected:
  // Holds the game that cerated the GameState
  Game *game_;

private:
};

#endif // GAMESTATE_H
