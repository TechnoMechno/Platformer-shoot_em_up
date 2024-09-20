#include "Actor.h"
#include "Components/SpriteComponent.h"
#include <vector>

class Ground: public Actor{
    private:
        std::vector<SpriteComponent*> sprite_vec;
        SpriteComponent *sprite;
        int num_sprite;

    public:
        Ground(class Game *game);
        SpriteComponent* getSprite();
        ~Ground();
};