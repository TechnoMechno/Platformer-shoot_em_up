#include "Ground.h"
#include "Game.h"

Ground::Ground(class Game* game)
:Actor(game){
  
    SetWidth(1440);
    this->SetHeight(48);
    pos_x = 0;
    pos_y = 900 - GetHeight() * 1.8;
    SpriteComponent *sprite = new SpriteComponent(this, 48, 48);
    this->SetScale(1.5);
    sprite->SetTexture(game->GetTexture("Assets/Sprite/Terrain/Ground/ground_spritesheet.png"));
    num_sprite = 1440 / 48;
    sprite->SetFrame(2);

    int space = 0;
    for (int i = 0; i < num_sprite; i++)
    {
        SpriteComponent *tmp = new SpriteComponent(*sprite);
        space += 48;
        tmp->SetOffset(space, 0);
        sprite_vec.push_back(tmp);
    }
}

Ground::~Ground(){
    if(sprite){
        delete sprite;
        sprite = nullptr;
    }
    for (SpriteComponent* sprite : sprite_vec) {
        delete sprite;  // Free the memory pointed to by sprite
    }
    sprite_vec.clear();  // Clear the vector after deleting all pointers
}

SpriteComponent* Ground::getSprite(){
    return sprite;
}