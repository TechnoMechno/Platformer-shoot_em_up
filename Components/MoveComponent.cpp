#include "MoveComponent.h"
#include "../Actor.h"
#include "../Character.h"

MoveComponent::MoveComponent(Character *owner, int updateOrder)
:Component(owner, updateOrder){

}

void MoveComponent::Update(float deltaTime){
    updatePhysics(deltaTime);
}

void MoveComponent::updatePhysics(float deltaTime){
    Character *characterOwner = dynamic_cast<Character *>(mOwner);
    int gameWidth = characterOwner->GetGame()->getScreenWidth();
    int gameHeight = characterOwner->GetGame()->getScreenHeight();

    // Apply gravity if on ground
    if (!onGround){
        velY += GRAVITY;
    }
    characterOwner->moveY(velY);
    characterOwner->moveX(velX);
    

    // Collision with the ground
    if (characterOwner->GetY() >= 700){
        characterOwner->SetY(700);
        velY = 0;
        onGround = true;
    }
    else{
        onGround = false;
    }
    // Left Right boundaries
    if (characterOwner->GetX() < 0){
        characterOwner->SetX(0);
    }
    else if(characterOwner->GetX() > gameWidth - characterOwner->GetWidth()){
        characterOwner->SetX(gameWidth - characterOwner->GetWidth());
    }
}

void MoveComponent::ProcessInput_Events(SDL_Event &event) {
    if(event.type == SDL_KEYDOWN){
        switch(event.key.keysym.sym){
            case SDLK_w:
                jump();
            break;
        }
    }
}
void MoveComponent::ProcessInput_Continuous(const Uint8* keyState) {
    Character *characterOwner = dynamic_cast<Character *>(mOwner);
    if (keyState[SDL_SCANCODE_A]) {
        run(-1); // Move left;
        characterOwner->getSprite()->setFlip(SDL_FLIP_HORIZONTAL);
    }
    else if (keyState[SDL_SCANCODE_D])
    {
        run(1);  // Move right
        characterOwner->getSprite()->setFlip(SDL_FLIP_NONE);
    }
    else
    {
        velX = 0;
        if(onGround){
            characterOwner->setState(CharacterState::IDLE);
        }
    }
}

void MoveComponent::jump(){
    Character *characterOwner = dynamic_cast<Character *>(mOwner);
    if(onGround){
        characterOwner->setState(CharacterState::JUMPING);
        velY = -JUMP_FORCE;
        onGround = false;
    }
}

void MoveComponent::run(int direction){
    Character *characterOwner = dynamic_cast<Character *>(mOwner);
    if(onGround){
        characterOwner->setState(CharacterState::RUNNING); 
    }
    velX = speed * direction; // direction is 1, -1 or 0
}