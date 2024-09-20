#pragma once
#include "Component.h"

class Character;

class MoveComponent : public Component{
    private:
        float speed = 10;
        const int GRAVITY = 2;
        const int JUMP_FORCE = 30;
        int velX = 0;
        int velY = 0;
        bool onGround = false;

    public:
        // Constructor. Lower update order to update first
        MoveComponent(Character *owner, int updateOrder = 10);
        virtual void ProcessInput_Events(SDL_Event &event) override;
        virtual void ProcessInput_Continuous(const Uint8 *keyState) override;
        

        // Update position of actor
        void Update(float deltaTime) override;

        float getVel_x() const { return velX;}
        float getVel_y() const { return velY; }
        float getSpeed() const { return speed;}
        
        void setSpeed(float speed) { this->speed = speed; }
        void setVel_x(float velx) { this->velX = velx; }
        void setVel_y(float vely) { this->velY = vely; }

        void updatePhysics(float deltaTime);

        // Character controls
        void jump();
        void run(int direction);
        void shoot();


};