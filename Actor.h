// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include <vector>
#include "Math.h"
#include <SDL.h>

class Actor {
	protected:
		// Transform
		int pos_x;
		int pos_y;
		int width;
		int height;
		float mScale;
		std::vector<class Component *> mComponents;
		class Game *mGame;

	public:
		Actor(class Game* game);
		virtual ~Actor();

		// Update function called from Game (not overridable)
		void Update(float deltaTime);

		// Updates all the components attached to the actor (not overridable)
		void UpdateComponents(float deltaTime);
		// Any actor-specific update code (overridable)
		virtual void UpdateActor(float deltaTime);

		// Getters/setters
		int GetX() { return pos_x; }
		int GetY() { return pos_y; }

		void SetX(int x) { pos_x = x; }
		void SetY(int y) { pos_y = y; }

		const float& GetScale() const { return mScale; }
		void SetScale(const float& scale) { mScale = scale; }

		void SetWidth(int w) { width = w; }
		void SetHeight(int h) { height = h; }

		int GetWidth() { return width; }
		int GetHeight() { return height; }

		class Game* GetGame() { return mGame; }

		// Add/remove components
		void AddComponent(class Component* component);
		void RemoveComponent(class Component* component);

		// ProcessInput function called from Game (not overridable)
		void ProcessInput_Events(SDL_Event &event);
		virtual void ProcessInput_Continuous(const Uint8* keyState);

		// Any actor_specific input code (overridable)
		virtual void ActorInput(SDL_Event &event) {}
};