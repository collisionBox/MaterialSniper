#pragma once
#include "environment.h"
class Over : public SceneBase
{
public:
	Over();
	~Over();
	SceneBase* Update(float& gameTime, float& deltaTime);
    void Draw();

    TextBitmap text;
private:
    class Aim aim;
    class Target target;
    class Bullet bullet;
    class Director director;
};

