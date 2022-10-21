#pragma once

#include "environment.h"
class Game 
{
public:
    void game(float& gameTime, float& deltaTime);
    void Update(float& gameTime, float& deltaTime);
    void Draw();
    void Init();

    Sean* nowSean;
    Sean* nextSean;

    Aim aim;
    Target target;
    Bullet bullet;
    Director director;
};

