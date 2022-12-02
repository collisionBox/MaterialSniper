#pragma once

#include "environment.h"
//TestScene.h
class TextBitmap;
class Game : public SceneBase
{
public:
    Game();
    ~Game();
    SceneBase* Update(float& gameTime, float& deltaTime);
    void Draw();
    void Init();

    TextBitmap text;
private:
    class Aim aim;
    class Target target;
    class Bullet bullet;
};

#define GAMEINSTANCE Game::GetInstance()


