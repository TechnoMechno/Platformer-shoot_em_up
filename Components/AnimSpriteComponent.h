#pragma once
#include "SpriteComponent.h"
#include "../CharacterStates.h"

class Character;

class AnimSpriteComponent: public SpriteComponent{
    private:
        std::vector<SDL_Texture *> mAnimTextures;
        // Animation framerate
        float mAnimSpeed;
        float mFrameDuration = 150;
        Uint32 mCurrentTime;
        Uint32 mLastFrame;
        Uint32 mLastFrameTime = 0;
        int mNumFrames;

        CharacterState owner_state;
        Character *mOwner;

        // Private methods
        void setFrame();

    public:
        AnimSpriteComponent(Character *owner, int frameW, int frameH, int drawOrder = 100);

        // Update animation every frame (overriden from component)
        void Update(float deltaTime) override;
};