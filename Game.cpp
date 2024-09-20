// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Game.h"
#include <algorithm>
#include "Character.h"
#include "Ground.h"
#include "SDL_image.h"
#include "Components/SpriteComponent.h"
#include "Components/InputComponent.h"


Game::Game()
:mWindow(nullptr)
,mRenderer(nullptr)
,mIsRunning(true)
,mUpdatingActors(false)
,SCREEN_WIDTH(1440)
,SCREEN_HEIGHT(900)
{
	
}

bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	
	mWindow = SDL_CreateWindow("Quik Football", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}
	
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}
	
	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
		return false;
	}

	LoadData();

	mTicksCount = SDL_GetTicks();
	
	return true;
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		RenderGame();
	}
}

void Game::ProcessInput()
{
    SDL_Event event;
    // Handle all discrete events in the event loop.
    while (SDL_PollEvent(&event))
    {
        switch (event.type) {
            case SDL_QUIT:
                mIsRunning = false;
                break;
            default:
                // Distribute the event to all actors for individual event processing
                mUpdatingActors = true;
                for (auto actor : mActors) {
                    actor->ProcessInput_Events(event);
                }
                mUpdatingActors = false;
                break;
        }
    }

    // After all discrete events are handled, check continuous keystates.
    const Uint8* keyState = SDL_GetKeyboardState(NULL);
    if (keyState[SDL_SCANCODE_ESCAPE]) {
        mIsRunning = false; // Handle ESC here if you want an immediate response
    }

    // Handle continuous input for all actors
    mUpdatingActors = true;
    for (auto actor : mActors) {
        actor->ProcessInput_Continuous(keyState);
    }
    mUpdatingActors = false;
}

void Game::UpdateGame()
{
	// Compute delta time
	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();

	// Update all actors
	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;
}

void Game::RenderGame()
{
	// 1. Clear the back buffer to a color
	SDL_SetRenderDrawColor(
		mRenderer,
		0,   // R
		0,   // G
		0, // B
		255  // A
	);

	SDL_RenderClear(mRenderer);
	// 2. Draw all sprite components
	for (auto sprite : mSprites){
		sprite->Draw(mRenderer);
	}

	// 3. Swap the fornt buffer and back buffer
	SDL_RenderPresent(mRenderer);
}

void Game::LoadData()
{
	// Create player
	Character* player = new Character(this);
	Vector2 player_pos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	player->SetX(SCREEN_WIDTH / 2);
	player->SetY(SCREEN_HEIGHT / 2);

	// Ground*ground = new Ground(this);
}

void Game::UnloadData()
{
	// Delete actors
	// Because ~Actor calls RemoveActor, have Geto use a different style loop
	while (!mActors.empty())
	{
		delete mActors.back();
	}

}

SDL_Texture* Game::GetTexture(const std::string& fileName){
	SDL_Texture *texture = nullptr;

	// Is the texture already in the map?
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end()){
		texture = iter->second;
	}
	else{
		// Load img file into SDL_Surface
		SDL_Surface *surf = IMG_Load(fileName.c_str());
		if(!surf){
			SDL_Log("Failed to load texture file %s", fileName.c_str());
			return nullptr;
		}

		// Create texture from surface
		texture = SDL_CreateTextureFromSurface(mRenderer, surf);
		SDL_FreeSurface(surf); // Get rid of old loaded surface
		if (!texture){
			SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
			return nullptr;
		}

		// Insert new texture into map
		mTextures.emplace(fileName.c_str(), texture);
	}

	return texture;
}

void Game::Shutdown()
{
	UnloadData();
	IMG_Quit();
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::AddActor(Actor* actor)
{
	mActors.emplace_back(actor);
}

void Game::RemoveActor(Actor* actor)
{
	auto iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void Game::AddSprite(SpriteComponent* sprite){
	// Find the insertion point in the sorted vector
	// (The first element with a higher draw order than me)
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for ( ;
		iter != mSprites.end();
		++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	// Inserts element before position of iterator
	mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	// (We can't swap because it ruins ordering)
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}
