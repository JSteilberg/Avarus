#include "MainLoop.h"

MainLoop::MainLoop()
{
  //ctor
}

MainLoop::MainLoop(Game *game) : GameState(game) {
}

void MainLoop::Update() {
}

MainLoop::~MainLoop()
{
  //dtor
}
