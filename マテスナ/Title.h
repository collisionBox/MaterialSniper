#pragma once
#include "environment.h"
class Title :
    public SceneBase
{
public:
    Title();
    ~Title();
    SceneBase* Update(float& gameTime, float& deltaTime);
    void Draw();

private:
    int titleFontHandle;
};

