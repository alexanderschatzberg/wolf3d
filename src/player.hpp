#include <SDL2/SDL.h>
#include <iostream>

struct Keys {
  bool w, a, s, d;
};

class Player {
public:
  SDL_Color color;
  SDL_Renderer* renderer;
  float x, y; //Position
  int width, height; //Size
  Keys keys; //Keyboard input

  Player(SDL_Renderer* renderer, float x, float y, int w, int h, SDL_Color color) {
    this->renderer = renderer;
    this->color = color;
    this->x = x;
    this->y = y;
    this->width = w;
    this->height = h;
    this->keys = { false, false, false, false };
  }

  void draw() {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = { (int)x, (int)y, width, height };
    SDL_RenderFillRect(renderer, &rect);
  }

  void move(Uint32 deltaTime) {

    float speed = 0.6f * (float)deltaTime;

    if (keys.w) {
      y -= speed;
    }
    if (keys.s) {
      y += speed;
    }
    if (keys.a) {
      x -= speed;
    }
    if (keys.d) {
      x += speed;
    }

    std::cout << "x: " << x << " y: " << y << std::endl;
  }

  void updateKeys(SDL_Keycode key, bool pressed) {
    if (key == SDLK_w) {
      keys.w = pressed;
    }
    if (key == SDLK_s) {
      keys.s = pressed;
    }
    if (key == SDLK_a) {
      keys.a = pressed;
    }
    if (key == SDLK_d) {
      keys.d = pressed;
    }
  }
};