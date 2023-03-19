#include <SDL2/SDL.h>
#include <iostream>
#include <math.h>
#include "world.hpp"

#define PI 3.1415926535

struct Keys {
  bool w, a, s, d;
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

  Player(SDL_Renderer* renderer, World* world, float x, float y, int w, int h, SDL_Color color) {
    this->renderer = renderer;
    this->world = world;
    this->color = color;
    this->x = x;
    this->y = y;
    this->width = w;
    this->height = h;
  }

  void castRays(int numRays) {
    //This is where the magic happens
    int /*r,*/ mx, my, mp, dof; //r = ray, mx = map x, my = map y, mp = map position, dof = depth of field
    float rx, ry, ra, xo, yo; //rx = ray x, ry = ray y, ra = ray angle, xo = x offset, yo = y offset

    //The initial angle of all the rays is the player's angle
    ra = theta;

    //Then we loop through all the rays and cast them, slapping an offset on the angle each time
    for (int i = 0; i < numRays; i++) {
      dof = 0;
      float aTan = -1 / tan(ra);

      if (ra > PI) {//If the ray is pointing down
        ry = (((int)y >> 6) << 6) - 0.00001; //Fancy bit shifting to get the y position of the map square the player is in
        rx = (y - ry) * aTan + x; //Get the x position of the ray by using the y position and the angle
        yo = -64; //The y offset is negative because the ray is pointing down
        xo = -yo * aTan; //The x offset is the y offset times the angle
      }

      if (ra < PI) {//If the ray is pointing up, we do similar stuff but with different offsets and signs
        ry = (((int)y >> 6) << 6) + 64;
        rx = (y - ry) * aTan + x;
        yo = 64;
        xo = -yo * aTan;
      }

      if (ra == 0 || ra == PI) {//If the ray is pointing straight up or down, we don't want to divide by 0
        rx = x; //So we just set the x position to the player's x position
        ry = y; //And the y position to the player's y position
        dof = 8; //And we set the depth of field to 8, which is the maximum, so the ray will go all the way to the edge of the screen
      }

      while (dof < 8) {
        mx = ((int)(rx)) >> 6; //Get the x position of the map square the ray is in
        my = (int)ry >> 6; //Get the y position of the map square the ray is in
        mp = my * world->mapX + mx; //Get the position of the map square (from the pointer) the ray is in
        if (mp < world->mapX * world->mapY && mp >= 0) { //If the ray is in the map
          if (*world->map[mp] > 0) { //If the map square the ray is in is not empty
            dof = 8; //Set the depth of field to 8, which is the maximum, so the ray will go all the way to the edge of the screen
          }
          else { //If the map square the ray is in is empty
            rx += xo; //Move the ray's x position by the x offset
            ry += yo; //Move the ray's y position by the y offset
            dof += 1; //Increase the depth of field by 1
          }
        }
        else { //If the ray is not in the map
          dof = 8; //Set the depth of field to 8, which is the maximum, so the ray will go all the way to the edge of the screen
        }
      }
    }
  }

  void draw() {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = { (int)x, (int)y, width, height };
    SDL_RenderFillRect(renderer, &rect);
    //Draw a line to show the direction, numbers are arbitrary
    SDL_RenderDrawLine(renderer, (int)x + width / 2, (int)y + height / 2, (int)x + width / 2 + dx * 13, (int)y + height / 2 + dy * 13);
    castRays(60);
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
    if (keys.a) {
      theta -= angularSpeed;
      if (theta < 0) {
        theta += 2 * PI;
      }
      dx = cos(theta) * 5;
      dy = sin(theta) * 5;
    }
    if (keys.d) {
      theta += angularSpeed;
      if (theta > 2 * PI) {
        theta -= 2 * PI;
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