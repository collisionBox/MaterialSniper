#pragma once

#include "environment.h"
#include "textBitmap.h"
#if 0
class Aim;
class Target;
class Bullet;
class Director;

class Game
{
public:
    Aim aim;
    Target target;
    Bullet bullet;
    Director director;
    void Init();
    void Update(float& gameTime, float& deltaTime);

};
#else
//TestScene.h
class TextBitmap;
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
    TextBitmap text;
private:
    class Aim aim;
    class Target target;
    class Bullet bullet;
    class Director director;
};

#define GAMEINSTANCE Game::GetInstance()
#endif // 1


