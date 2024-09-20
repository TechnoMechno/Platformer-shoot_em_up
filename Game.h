#pragma once
#include <SDL.h>
#include <iostream>
#include "Actor.h"
#include "Math.h"
#include <vector>
#include <unordered_map>



class Game{
    private:
        // Helper functions for the game loop
        void ProcessInput();
        void UpdateGame();
        void RenderGame();

        void LoadData();
        void UnloadData();

        //----- Variables ------
        int SCREEN_WIDTH;
	    int SCREEN_HEIGHT;
        // Game should continue to run
        bool mIsRunning;
        

        // Actor vectors
        std::vector<Actor *> mActors; // contains active actors
        bool mUpdatingActors;

        // All sprite components in game
        std::vector<class SpriteComponent *> mSprites;

        // Map of textures loaded
	    std::unordered_map<std::string, SDL_Texture*> mTextures;

        // Window created by SDL
        SDL_Window *mWindow;
        SDL_Renderer *mRenderer; // SDL renderer

        // Calculate delta time
        Uint32 mTicksCount = 0;
    public:
        Game();
        bool Initialize();
        void RunLoop();
        void Shutdown();
        

        // Actor methods
        void AddActor(Actor *);
        void RemoveActor(Actor *);

        // Sprite methods
        void AddSprite(class SpriteComponent *sprite);
        void RemoveSprite(class SpriteComponent *sprite);

        int getScreenWidth() { return SCREEN_WIDTH; }
        int getScreenHeight() { return SCREEN_HEIGHT; }

        SDL_Texture *GetTexture(const std::string &fileName);

};
