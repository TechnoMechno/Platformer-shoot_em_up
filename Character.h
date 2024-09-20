#pragma once
#include "Actor.h"
#include "CharacterStates.h"
#include "Components/AnimSpriteComponent.h"
#include "Game.h"

class Character : public Actor{
    private:
        CharacterState currentState = CharacterState::IDLE;
        bool is_shooting = false;
        bool state_changed = false;
        AnimSpriteComponent *spriteComponent;

    public:
        Character(Game *game);
        ~Character();
        void setState(CharacterState state);
        CharacterState getState() { return currentState; };

        bool is_Shooting() { return is_shooting; };
        void setShooting(bool shooting) { is_shooting = shooting; };
        SpriteComponent* getSprite();

        void moveX(int velX){
            pos_x += velX;
        }
        void moveY(int velY){
            pos_y += velY;
        }
};