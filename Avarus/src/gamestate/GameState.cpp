#include "GameState.h"

GameState::GameState()
{
  //ctor
}

void GameState::Update() {

}

GameState::GameState(Game* game) {
  game_ = game;
}

GameState::~GameState()
{
  //dtor
}
