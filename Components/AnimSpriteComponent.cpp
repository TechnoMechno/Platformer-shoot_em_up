#include "AnimSpriteComponent.h"
#include "../Character.h"
#include <iostream>

AnimSpriteComponent::AnimSpriteComponent(Character *owner, int frameW, int frameH, int drawOrder)
            : SpriteComponent(static_cast<Actor*>(owner), frameW, frameH)
            , mOwner(owner)
        {
            owner_state = mOwner->getState();
            setFrame();
        }

void AnimSpriteComponent::Update(float deltaTime) {
            // Check state changes
            if (owner_state != mOwner->getState()){
                owner_state = mOwner->getState();
                setFrame();
            }
            
            std::cout << mCurrentFrame << std::endl;
            std::cout << "Num frames: " << mNumFrames << std::endl;
            // Animation wloop
            mCurrentTime = SDL_GetTicks();
            if (mCurrentTime > mLastFrameTime + mFrameDuration){
                mCurrentFrame = mCurrentFrame + 1;
                mLastFrameTime = mCurrentTime;

                if(mCurrentFrame == mLastFrame){
                    mCurrentFrame -= mNumFrames;
                }
            }
    } 

void AnimSpriteComponent::setFrame(){
            switch(owner_state){
                case CharacterState::IDLE:
                    if(mOwner->is_Shooting()){
                        mCurrentFrame = 0;
                        mNumFrames = 4;
                        mFrameDuration = 150;
                        break;
                    }
                    else{
                        mCurrentFrame = 0;
                        mNumFrames = 4;
                        mFrameDuration = 150;
                    break;
                    }
                    
                case CharacterState::RUNNING:
                    mCurrentFrame = 4;
                    mNumFrames = 8;
                    mFrameDuration = 70;
                    break;
                case CharacterState::JUMPING:
                    mCurrentFrame = 12;
                    mNumFrames = 1;
                    break;
                case CharacterState::FALLING:
                    mCurrentFrame = 13;
                    mNumFrames = 1;
                    break;
                case CharacterState::ROLLING:
                    mCurrentFrame = 28;
                    mNumFrames = 8;
                    mFrameDuration = 70;
                    break;
            }

            mLastFrame = mCurrentFrame + mNumFrames;
}