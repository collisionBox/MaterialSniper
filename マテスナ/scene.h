#pragma once
#include "game.h"
#include "sceneBase.h"
//Game.h
#if 1

class Scene 
{
public:
	~Scene();
	static Scene& GetInstance()
	{
		static Scene instance;
		return instance;
	}
	void SetScene(SceneBase* scene) { nowScene = scene; }

	void Draw();
	int Update(float& gameTime, float& deltaTime);
	class SceneBase* nowScene;
};
#define GAMEINSTANCE Scene::GetInstance()
#endif // 0
