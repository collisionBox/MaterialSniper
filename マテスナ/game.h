#pragma once

#include "environment.h"

class Game : public SceneBase
{
public:
    Game();
    ~Game();
    void SetScene(SceneBase* scene) { nowSean = scene; }
    SceneBase* Update(float& gameTime, float& deltaTime);
    void Draw();
    void Init();

    class SceneBase* nowSean;
private:
    class Aim aim;
    class Target target;
    class Bullet bullet;
    class Director director;
};

#define GAMEINSTANCE Game::GetInstance()