#include <SDL2/SDL.h>
#include <stdio.h>

#include "player.hpp"

#define SCREEN_WIDTH 1280 
#define SCREEN_HEIGHT 640

int main(int argc, char** argv) {
  //Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Error: SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
    return 1;
  }

  //Create window
  SDL_Window* window = SDL_CreateWindow("WOLf 3D", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
  if (!window) {
    printf("Error: Failed to open window\nSDL Error: '%s'\n", SDL_GetError());
    return 1;
  }
  //Create renderer to draw on
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    printf("Error: Failed to create renderer\nSDL Error: '%s'\n", SDL_GetError());
    return 1;
  }

  //Create world
  World world = World(renderer);
  World* worldPtr = &world; //Create a pointer to the world so that the player can access it

  //Create player
  float x = (float)SCREEN_WIDTH / 2, y = (float)SCREEN_HEIGHT / 2;
  int width = 15, height = 15;
  Player player = Player(renderer, worldPtr, (int)x, (int)y, width, height, { 255, 0, 0, 255 });

  //Time variables for delta time
  Uint32 lastTime = 0, currentTime = 0;

  bool running = true;
  //Main loop
  while (running) {
    //Calculate delta time
    currentTime = SDL_GetTicks64();
    float deltaTime = (currentTime - lastTime);
    lastTime = currentTime;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        std::cout << "Quit" << std::endl;
        running = false;
      }
      //if the keyboard is being pressed, update the player's key state 
      if (event.type == SDL_KEYDOWN) {
        player.updateKeys(event.key.keysym.sym, true);
      }
      if (event.type == SDL_KEYUP) {
        player.updateKeys(event.key.keysym.sym, false);
      }
    }

    SDL_SetRenderDrawColor(renderer, 160, 160, 160, 255); //Paint background grey
    SDL_RenderClear(renderer); //Clear Canvas

    //Move the player according to the keyboard input
    player.move(deltaTime);

    world.draw(); //Draw world
    player.draw(); //Draw player

    SDL_RenderPresent(renderer);
  }

  SDL_StopTextInput();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
