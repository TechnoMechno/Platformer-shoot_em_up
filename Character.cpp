#include "Character.h"
#include "Game.h"
#include "Components/AnimSpriteComponent.h"
#include "Components/MoveComponent.h"

Character::Character(Game* game)
        :Actor(game)
{
            // Assign sprite to player
            this->SetWidth(58);
            this->SetHeight(64);
            spriteComponent = new AnimSpriteComponent(this, 58, 64);
            this->SetScale(1.5);

            spriteComponent->SetTexture(game->GetTexture("Assets/Sprite/Character/Player/Ragdoll/player_sheet.png"));
            MoveComponent *move = new MoveComponent(this);


}

Character::~Character(){
      if (spriteComponent) {
        delete spriteComponent;
        spriteComponent = nullptr; // Good practice to set deleted pointers to nullptr
    }
}

void Character::setState(CharacterState state){
    currentState = state;
}

SpriteComponent* Character::getSprite(){
    return spriteComponent;
}
