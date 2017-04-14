#ifndef GAMESTATE_H
#define GAMESTATE_H

class Game;

// Usually going on an std::stack of GameStates, an instance of GameState represents a
// specific mode the Game is currently in.
class GameState {
  public:

    // Creates a GameState with no attributes
    GameState();

    // The GameState should be created with a Game to operate on
    GameState(Game* game);

    // This method should be called during every update in the main Game loop
    virtual void Update();

    virtual ~GameState();

  protected:

    // Holds the game that cerated the GameState
    Game *game_;

  private:

};

#endif // GAMESTATE_H
