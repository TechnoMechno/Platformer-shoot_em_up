// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Game.h"

int main(int argc, char** argv)
{
	Game game;
	bool success = game.Initialize();
	if (success)
	{
		game.RunLoop();
	}
	game.Shutdown();
	return 0;
}



// #include <SDL.h>
// #include <iostream>

// const int SCREEN_WIDTH = 800;
// const int SCREEN_HEIGHT = 600;
// const int GRAVITY = 2;
// const int MOVE_SPEED = 10;
// const int JUMP_FORCE = 25;

// struct Character {
//     SDL_Rect rect;  // The position and size of the character
//     int velocityY = 0;  // Vertical velocity
//     int velocityX = 0;  // Horizontal velocity
//     bool onGround = false;  // Is the character on the ground?
// };

// void initSDL(SDL_Window** window, SDL_Renderer** renderer) {
//     if (SDL_Init(SDL_INIT_VIDEO) < 0) {
//         std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
//         exit(1);
//     }

//     *window = SDL_CreateWindow("SDL Platformer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
//                                SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
//     if (!(*window)) {
//         std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
//         exit(1);
//     }

//     *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//     if (!(*renderer)) {
//         std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
//         exit(1);
//     }

//     SDL_SetRenderDrawColor(*renderer, 0xFF, 0xFF, 0xFF, 0xFF);
// }

// void closeSDL(SDL_Window* window, SDL_Renderer* renderer) {
//     SDL_DestroyRenderer(renderer);
//     SDL_DestroyWindow(window);
//     SDL_Quit();
// }

// void updatePhysics(Character& character) {
//     character.rect.y += character.velocityY;  // Update vertical position
//     character.rect.x += character.velocityX;  // Update horizontal position

//     if (!character.onGround) {  // Apply gravity if not on ground
//         character.velocityY += GRAVITY;
//     }

//     // Collision with the ground
//     if (character.rect.y > SCREEN_HEIGHT - character.rect.h) {
//         character.rect.y = SCREEN_HEIGHT - character.rect.h;
//         character.velocityY = 0;
//         character.onGround = true;
//     }

//     // Left and right boundaries
//     if (character.rect.x < 0) {
//         character.rect.x = 0;
//     } else if (character.rect.x > SCREEN_WIDTH - character.rect.w) {
//         character.rect.x = SCREEN_WIDTH - character.rect.w;
//     }
// }

// void handleEvents(bool& running, Character& character) {
//     SDL_Event e;

	
//     while (SDL_PollEvent(&e) != 0) {
//         if (e.type == SDL_QUIT) {
//             running = false;
//         } else if (e.type == SDL_KEYDOWN) {
//             switch (e.key.keysym.sym) {
//                 case SDLK_SPACE:
//                     if (character.onGround) {
//                         character.velocityY = -JUMP_FORCE;  // Apply jump force
//                         character.onGround = false;
//                     }
//                     break;
//             }
//         }
//     }

//     // Update horizontal movement based on current key states
//     const Uint8* keystates = SDL_GetKeyboardState(NULL);
//     if (keystates[SDL_SCANCODE_LEFT]) {
//         character.velocityX = -MOVE_SPEED;  // Move left
//     } else if (keystates[SDL_SCANCODE_RIGHT]) {
//         character.velocityX = MOVE_SPEED;  // Move right
//     } else {
//         character.velocityX = 0;  // Stop moving when no left/right keys are pressed
//     }
// }

// void render(SDL_Renderer* renderer, const Character& character) {
//     SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
//     SDL_RenderClear(renderer);
//     SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
//     SDL_RenderFillRect(renderer, &character.rect);
//     SDL_RenderPresent(renderer);
// }

// int main(int argc, char* args[]) {
//     SDL_Window* window = nullptr;
//     SDL_Renderer* renderer = nullptr;

//     initSDL(&window, &renderer);

//     Character character = {{300, 300, 50, 50}};  // Initialize character

//     bool running = true;
//     while (running) {
//         handleEvents(running, character);
//         updatePhysics(character);
//         render(renderer, character);
//     }

//     closeSDL(window, renderer);
//     return 0;
// }