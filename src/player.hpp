#include <SDL2/SDL.h>
#include <iostream>
#include <math.h>

#define PI 3.1415926535

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
  float theta = 0; //Rotation

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

    //These values are arbitrary, they just feel right 
    float linearSpead = 0.3f * (float)deltaTime;
    float angularSpead = 3.0f * (float)deltaTime;



    if (keys.w) {
      y -= linearSpead;
    }
    if (keys.s) {
      y += linearSpead;
    }
    if (keys.a) {
      x -= linearSpead;
    }
    if (keys.d) {
      x += linearSpead;
    }

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