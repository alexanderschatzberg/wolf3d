#include <SDL2/SDL.h>
#include <iostream>
#include <math.h>
#include <vector>

#include "world.hpp"
#include "ray.hpp"

#define PI 3.1415926535

struct Keys {
  bool w, a, s, d;
};

struct Coord {
  float x, y;
};

class Player {
public:
  SDL_Color color;
  SDL_Renderer* renderer; //Renderer pointer from the main file
  World* world; //World pointer from the main file
  float x, y; //Position
  int width, height; //Size
  Keys keys = { false, false, false, false }; //Keyboard input
  float theta = 0; //Rotation
  float dx = 0, dy = 0; //Delta x and y
  std::vector<Ray> rays;
  float fov;

  Player(SDL_Renderer* renderer, World* world, float x, float y, int w, int h, SDL_Color color, int numRays, float fov, int height) {
    this->renderer = renderer;
    this->world = world;
    this->color = color;
    this->x = x;
    this->y = y;
    this->width = w;
    this->height = h;
    this->fov = fov;
    for (int i = 0; i < numRays; i++) {
      rays.push_back(Ray(renderer, 0, 0, theta));
    }
  }

  void castRays(float fov) {
    float offset = (this->fov) / 2; float startingPoint = this->theta - offset; float endingPoint = this->theta + offset;
    float range = endingPoint - startingPoint; float step = range / this->rays.size();
    for (float i = 0; i < this->rays.size(); i++) {
      Coord horizontalCast = checkHorizontalCast(startingPoint + (i * step), this->x, this->y);
      Coord verticalCast = checkVerticalCast(startingPoint + (i * step), this->x, this->y);

      float horizontalDistance = sqrt(pow(horizontalCast.x - this->x, 2) + pow(horizontalCast.y - this->y, 2));
      float verticalDistance = sqrt(pow(verticalCast.x - this->x, 2) + pow(verticalCast.y - this->y, 2));

      if (horizontalDistance < verticalDistance) {
        this->rays[i].x = horizontalCast.x;
        this->rays[i].y = horizontalCast.y;
      }
      else {
        this->rays[i].x = verticalCast.x;
        this->rays[i].y = verticalCast.y;
      }

      this->rays[i].theta = startingPoint + (i * step);
      this->rays[i].draw(this.x, this->y);
    }
  }

  Coord getPositionInMap(float x, float y) {
    Coord position;
    position.x = (x / 64);
    position.y = (y / 64);
    return position;
  }

  Coord checkHorizontalCast(float theta, float x, float y) {
    if (theta > PI) {
      Coord playerGridPos = getPositionInMap(x, y);
    }
  }

  Coord checkVerticalCast(float theta, float x, float y) {
    //TODO

  }


  void draw() {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = { (int)x, (int)y, width, height };
    SDL_RenderFillRect(renderer, &rect);
    castRays(this->fov);
  }

  void move(Uint32 deltaTime) {

    //These values are arbitrary, they just feel right 
    float linearSpeed = 0.07f * (float)deltaTime;
    float angularSpeed = 0.004f * (float)deltaTime;

    //This is all just basic trigonometry
    if (keys.w) {
      x += dx * linearSpeed;
      y += dy * linearSpeed;
    }
    if (keys.s) {
      x -= dx * linearSpeed;
      y -= dy * linearSpeed;
    }
    if (keys.d) {
      theta += angularSpeed;
      if (theta > 2 * PI) {
        theta -= 2 * PI;
      }
      dx = cos(theta) * 5;
      dy = sin(theta) * 5;
    }
    if (keys.a) {
      theta -= angularSpeed;
      if (theta < 0) {
        theta += 2 * PI;
      }
      dx = cos(theta) * 5;
      dy = sin(theta) * 5;
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