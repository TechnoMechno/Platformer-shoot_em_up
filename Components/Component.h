#pragma once
#include "../Actor.h"
#include <SDL.h>
class Component{
	protected:
		// Owning actor
		class Actor* mOwner;
		// Update order of component
		int mUpdateOrder;
	public:
		// Constructor
		// (the lower the update order, the earlier the component updates)
		Component(Actor* owner, int updateOrder = 100);
		// Destructor
		virtual ~Component();
		// Update this component by delta time
		virtual void Update(float deltaTime);

		int GetUpdateOrder() const { return mUpdateOrder; }
		
		virtual void ProcessInput_Events(SDL_Event &event) {}
		virtual void ProcessInput_Continuous(const Uint8* keyState) {}
};
