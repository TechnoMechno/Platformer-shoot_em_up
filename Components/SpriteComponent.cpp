#include "SpriteComponent.h"
#include "../Actor.h"
#include "../Game.h"

SpriteComponent::SpriteComponent(class Actor *owner, int frameW, int frameH, int drawOrder)
    :Component(owner)
    ,mDrawOrder(drawOrder)
    ,mFrameWidth(frameW)
    ,mFrameHeight(frameH)
    ,mCurrentFrame(0)
    ,mTextureWidth(0)
	,mTextureHeight(0)
{
    // Add sprite to game's sprite map
    mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::SpriteComponent(const SpriteComponent& rhs)
:Component(rhs.mOwner)
, mDrawOrder(rhs.GetDrawOrder())
,mFrameWidth(rhs.mFrameWidth)
,mFrameHeight(rhs.mFrameHeight)
,mCurrentFrame(rhs.mCurrentFrame)
,mTextureWidth(rhs.mTextureWidth)
,mTextureHeight(rhs.mTextureHeight)
,mTexture(rhs.mTexture)
{
 mOwner->GetGame()->AddSprite(this);
    offset.x = 0;
    offset.y = 0;
}

SpriteComponent::~SpriteComponent(){
    // Remove sprite from game's sprite map
    mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer * renderer){
    // If there is a texture
    if (mTexture){
        // Set size of destination and source rectangles
        srcRect.y = 0;
        srcRect.x = mCurrentFrame * mFrameWidth;
        srcRect.w = mFrameWidth;
        srcRect.h = mFrameHeight;


        // Scale width/height of rectangle by owner's scale
        destRect.w = static_cast<float>(mFrameWidth * mOwner->GetScale());
        destRect.h = static_cast<float>(mFrameWidth * mOwner->GetScale());

        // Center the rectangle aronud the position of the owner
        destRect.x = static_cast<float>(mOwner->GetX() + offset.x - destRect.w / 2);
        destRect.y = static_cast<float>(mOwner->GetY() +offset.y - destRect.h / 2);
        
        // Draw onto buffer
        SDL_RenderCopyEx(renderer, mTexture, &srcRect, &destRect, 0, NULL, flip_state);
    }
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	mTexture = texture;
	// Set width/height
	SDL_QueryTexture(texture, nullptr, nullptr, &mTextureWidth, &mTextureHeight);
}

void SpriteComponent::setFlip(SDL_RendererFlip flip){
    flip_state = flip;
}