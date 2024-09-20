#pragma once
#include "Component.h"
#include <SDL.h>

class SpriteComponent : public Component{
    protected:
        SDL_Texture *mTexture; // The SpriteSheet
        SDL_Rect srcRect;
        SDL_Rect destRect;
        SDL_RendererFlip flip_state = SDL_FLIP_NONE;
        SDL_Point offset;

        int mDrawOrder;
        int mTextureWidth;
        int mTextureHeight;

        int mCurrentFrame;
        int mFrameWidth;
        int mFrameHeight;

    public:

        // Lower draw order = further back
        SpriteComponent(class Actor *owner, int frameW, int frameH, int drawOrder = 100);

        // Copy constructor
        SpriteComponent(const SpriteComponent& rhs);

        ~SpriteComponent();

        // Draw the current frame onto the screen
        virtual void Draw(SDL_Renderer *renderer);

        void SetOffset(int x, int y) {
            offset.x = x;
            offset.y = y;
        }
        // Setter
        virtual void SetTexture(SDL_Texture *texture);

        void setFlip(SDL_RendererFlip flip);

        // Getter
        int GetDrawOrder() const { return mDrawOrder; }
        int GetTexHeight() const { return mTextureHeight; }
        int GetTexWidth() const { return mTextureWidth; }

        void SetFrame(int frame) { mCurrentFrame = frame; }
};