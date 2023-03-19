#include <SDL2/SDL.h>
#include <iostream>

class World {
public:
  int mapX = 10, mapY = 10;
  int map[10][10] = {
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 1, 1, 0, 0, 1, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 1, 0, 1 },
    { 1, 0, 0, 0, 0, 1, 1, 1, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 1, 0, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
  };
  SDL_Renderer* renderer;

  World(SDL_Renderer* renderer) {
    this->renderer = renderer;
    std::cout << "World created" << std::endl;
  }

  void draw() {
    SDL_SetRenderDrawColor(renderer, 56, 64, 128, 255);

    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j++) {
        if (map[j][i] == 1) { //They are flipped because of the way the map is stored
          SDL_Rect rect = { i * 64, j * 64, 64, 64 };
          SDL_RenderDrawRect(renderer, &rect);
        }
      }
    }
  }
};