#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace consts {
  // Number of pixels per meter in game
  const float kPixelScale = 32.0f;

  // Current version of the game... self explanatory
  const string kGameVersion = "1.0";

  // Target number of game updates per second
  const float kUpsPerSec = 100.0f;

  // Number of velocity integration iterations to perform per timestep
  // Recommended 5-8
  const int kVelocityIterations = 6;

  // Number of position integration iterations to perform per timestep
  // Recommended 2-4
  const int kPositionIterations = 2;
}

#endif // CONSTANTS_H
