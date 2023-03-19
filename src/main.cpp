#include <iostream>
#include <SDL2/SDL.h> 

int main(){

  if(SDL_Init(SDL_INIT_EVERYTHING) > 0){
    std::cout << "Shit failed" << std::endl; 
  }

  std::string hello = "Hello world"; 
  std::cout << hello << std::endl; 
  SDL_Quit(); 
  return 0; 
}