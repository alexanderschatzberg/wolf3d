#include <SDL2/SDL.h>

class Ray {
public:
  float x, y, angle;
  SDL_Renderer* renderer;
  Ray(SDL_Renderer* renderer, float x, float y, float angle) {
    this->renderer = renderer;
    this->x = x;
    this->y = y;
    this->angle = angle;
  };
  void draw(float xi, float yi) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawLine(renderer, xi, yi, this->x, this->y);
  }
};