#define SDL_MAIN_HANDLED
#include "core/game.h"
#include <iostream>

/**
 * Main function
 */
int main() {

  Core::Game g;
  g.initGame();
  g.run();
  g.quit();

  return 0;
}
