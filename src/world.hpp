#include <SDL2/SDL.h>
#include <iostream>

class World {
public:
  int mapX = 8, mapY = 8;
  int map[8][8] = {
    { 1, 1, 1, 1, 1, 1, 1, 1, },
    { 1, 0, 0, 0, 1, 0, 0, 1, },
    { 1, 0, 0, 0, 0, 0, 0, 1, },
    { 1, 0, 0, 0, 0, 0, 0, 1, },
    { 1, 1, 1, 0, 0, 1, 0, 1, },
    { 1, 0, 0, 0, 0, 1, 0, 1, },
    { 1, 0, 0, 0, 0, 1, 0, 1, },
    { 1, 1, 1, 1, 1, 1, 1, 1, },
  };
  SDL_Renderer* renderer;

  World(SDL_Renderer* renderer) {
    this->renderer = renderer;
    std::cout << "World created" << std::endl;
  }

  void draw() {
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        if (map[j][i] == 1) { //They are flipped because of the way the map is stored
          SDL_Rect rect = { i * 64, j * 64, 64, 64 };
          SDL_RenderDrawRect(renderer, &rect);
        }
        else {
          SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
          SDL_Rect rect = { i * 64, j * 64, 64, 64 };
          SDL_RenderDrawRect(renderer, &rect);
        }
      }
    }
  }
};